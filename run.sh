#!/usr/bin/env bash
# rustbox-escape-tests runner
#
# Posts each payload in manifest.json to a Rustbox-compatible API,
# waits for the verdict, and checks it against the expected outcome.
#
# Usage:
#   RUSTBOX_API=https://rustbox-api.orkait.com RUSTBOX_KEY=rb_live_... ./run.sh
#   ./run.sh --lang c
#   ./run.sh --test fork_bomb_c
#   ./run.sh --verbose

set -euo pipefail

API="${RUSTBOX_API:-https://rustbox-api.orkait.com}"
KEY="${RUSTBOX_KEY:-}"
MANIFEST="${MANIFEST:-manifest.json}"
PAYLOADS="${PAYLOADS:-payloads}"
VERBOSE=0
FILTER_LANG=""
FILTER_NAME=""

while [ $# -gt 0 ]; do
    case "$1" in
        --lang) FILTER_LANG="$2"; shift 2 ;;
        --test) FILTER_NAME="$2"; shift 2 ;;
        --verbose|-v) VERBOSE=1; shift ;;
        -h|--help) sed -n '2,12p' "$0"; exit 0 ;;
        *) echo "unknown flag: $1" >&2; exit 2 ;;
    esac
done

if [ -z "$KEY" ]; then
    echo "error: RUSTBOX_KEY not set. export RUSTBOX_KEY=rb_live_..." >&2
    exit 2
fi

if [ ! -f "$MANIFEST" ]; then
    echo "error: manifest not found at $MANIFEST" >&2
    exit 2
fi

GREEN=$'\e[32m'; RED=$'\e[31m'; YELLOW=$'\e[33m'; DIM=$'\e[2m'; RESET=$'\e[0m'

submit_and_check() {
    local name="$1" file="$2" language="$3" timeout_sec="$4" expect="$5"
    local payload_path="$PAYLOADS/$file"

    if [ ! -f "$payload_path" ]; then
        printf "${YELLOW}SKIP${RESET}  %-40s (payload missing: %s)\n" "$name" "$file"
        return 0
    fi

    local code
    code=$(cat "$payload_path")
    local body
    body=$(jq -cn --arg l "$language" --arg c "$code" '{language:$l, code:$c}')

    local resp
    resp=$(curl -s --max-time "$timeout_sec" \
        -X POST "$API/api/submit?wait=true" \
        -H "Content-Type: application/json" \
        -H "X-API-Key: $KEY" \
        -d "$body" 2>/dev/null || echo '{"verdict":null}')

    local verdict exit_code stdout
    verdict=$(echo "$resp" | jq -r '.verdict // ""')
    exit_code=$(echo "$resp" | jq -r '.exit_code // ""')
    stdout=$(echo "$resp" | jq -r '.stdout // ""')

    if [ -z "$verdict" ]; then
        printf "${RED}FAIL${RESET}  %-40s (no verdict - api error?)\n" "$name"
        [ "$VERBOSE" = 1 ] && echo "    $resp" | head -c 400
        return 1
    fi

    local ok=1 reason=""

    local expect_v expect_any expect_not expect_stdout expect_exit
    expect_v=$(echo "$expect" | jq -r '.verdict // ""')
    expect_any=$(echo "$expect" | jq -r '.verdict_any // [] | join(",")')
    expect_not=$(echo "$expect" | jq -r '.verdict_not // ""')
    expect_stdout=$(echo "$expect" | jq -r '.stdout_contains // ""')
    expect_exit=$(echo "$expect" | jq -r '.exit_code // ""')

    if [ -n "$expect_v" ] && [ "$verdict" != "$expect_v" ]; then
        ok=0; reason="verdict=$verdict want=$expect_v"
    fi
    if [ -n "$expect_any" ]; then
        local found=0
        IFS=',' read -ra VS <<<"$expect_any"
        for v in "${VS[@]}"; do [ "$verdict" = "$v" ] && found=1; done
        [ $found -eq 0 ] && { ok=0; reason="verdict=$verdict want_any=[$expect_any]"; }
    fi
    if [ -n "$expect_not" ] && [ "$verdict" = "$expect_not" ]; then
        ok=0; reason="verdict=$verdict forbidden=$expect_not"
    fi
    if [ -n "$expect_stdout" ] && ! echo "$stdout" | grep -qF -- "$expect_stdout"; then
        ok=0; reason="stdout missing: $expect_stdout"
    fi
    if [ -n "$expect_exit" ] && [ "$exit_code" != "$expect_exit" ]; then
        ok=0; reason="exit=$exit_code want=$expect_exit"
    fi

    if [ $ok -eq 1 ]; then
        printf "${GREEN}PASS${RESET}  %-40s (verdict=%s exit=%s)\n" "$name" "$verdict" "${exit_code:--}"
        return 0
    else
        printf "${RED}FAIL${RESET}  %-40s %s\n" "$name" "$reason"
        [ "$VERBOSE" = 1 ] && { echo "${DIM}    stdout:${RESET} $(echo "$stdout" | head -c 200)"; }
        return 1
    fi
}

total=0
passed=0
failed=0

tests_count=$(jq '.tests | length' "$MANIFEST")

for i in $(seq 0 $((tests_count - 1))); do
    entry=$(jq ".tests[$i]" "$MANIFEST")
    name=$(echo "$entry" | jq -r '.name')
    file=$(echo "$entry" | jq -r '.file' | sed 's|^adversarial/||')
    language=$(echo "$entry" | jq -r '.language')
    timeout_sec=$(echo "$entry" | jq -r '.timeout_sec // 30')
    expect=$(echo "$entry" | jq -c '.expect')

    if [ -n "$FILTER_LANG" ] && [ "$language" != "$FILTER_LANG" ]; then continue; fi
    if [ -n "$FILTER_NAME" ] && [ "$name" != "$FILTER_NAME" ]; then continue; fi

    total=$((total + 1))
    if submit_and_check "$name" "$file" "$language" "$timeout_sec" "$expect"; then
        passed=$((passed + 1))
    else
        failed=$((failed + 1))
    fi
done

echo
if [ $failed -eq 0 ]; then
    echo "${GREEN}${passed}/${total} contained${RESET}"
    exit 0
else
    echo "${RED}${failed}/${total} ESCAPED OR UNEXPECTED VERDICT${RESET}"
    echo "${GREEN}${passed}/${total} contained${RESET}"
    exit 1
fi
