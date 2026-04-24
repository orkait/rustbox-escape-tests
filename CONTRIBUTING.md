# Contributing

New attacks welcome. Before opening a PR, please read.

## Responsible disclosure

If your payload demonstrates a **new** escape (verdict=AC in a sandbox that used to contain similar attacks), **do not** open a public PR or issue. Email `security@orkait.com` with:

- The payload source
- The sandbox target
- The observed escape (output, side effect, whatever you found)

We will coordinate a fix across affected sandboxes and land the test here after a 90-day window (or shorter if already public).

If your payload is an expressed variant of an attack already in the repo (different language, different syscall number, different arg shape) — open a PR directly.

## Merge bar

- **One file per payload.** Must compile/interpret with just the language toolchain. No curl/git/network during the attack.
- **Manifest entry.** Add the test to `manifest.json` with a clear `expect` block. The test must fail if containment regresses.
- **Multi-language when possible.** Cross-language coverage finds runtime-specific bugs. A fork bomb belongs in every language.
- **Descriptive filename.** `fork_bomb.c` not `attack.c`.
- **No hardcoded IPs, tokens, or PII.** If you must target a specific IP, use RFC 5737 test addresses or make them configurable.
- **License compatible.** Your contribution is released under CC-BY-4.0 for payloads and MIT for runner code.

## Adding a new attack class

If your payload doesn't fit an existing attack class (kernel syscall, privilege, chroot, network, resource, execve, signal), update the README's attack-class table and briefly explain the threat model in the payload's header comment.

## Filing issues

- **Containment regression** (public): open an issue, include payload, target sandbox version, expected vs actual.
- **Suspected zero-day** (escape we've never seen): use the email address above.

## Repo structure sanity

```
payloads/<language>/<attack_name>.<ext>
manifest.json  — single source of truth for expected outcomes
run.sh         — generic runner
```

Keep it flat. No nested subdirectories under `payloads/<language>/`.

## Testing your payload locally

```bash
export RUSTBOX_API=https://rustbox-api.orkait.com
export RUSTBOX_KEY=rb_live_...
./run.sh --test your_new_test
```

Payloads that exceed their timeout are kept as-is — `timeout_sec` just bounds how long the runner waits before giving up.

## Getting an API key

Rustbox is in open beta. [Request access](https://rustbox.orkait.com) — we hand out beta keys within 24 hours.
