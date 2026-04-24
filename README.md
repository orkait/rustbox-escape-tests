# rustbox-escape-tests

Public adversarial regression suite for the [Rustbox](https://rustbox.orkait.com) code-execution sandbox. 148 attack payloads across 8 languages — fork bombs, kernel syscall exploits, chroot escapes, privilege escalation, network probes, info leaks, and more. Every test asserts a specific containment outcome.

**Current score on production Rustbox: 148 / 148 contained. 0 escapes.**

[![contained](https://img.shields.io/badge/contained-148%2F148-success)](https://github.com/orkait/rustbox-escape-tests)
[![license](https://img.shields.io/badge/license-MIT%20%2B%20CC--BY--4.0-blue)](#license)

---

## Purpose

Most code-execution services publish uptime SLAs and latency numbers. Few publish **what they block**. This repo is the opposite — an honest, reproducible, adversarial list of attacks that any sandbox should contain before accepting untrusted code.

If you run a sandbox, run this suite against it. If your sandbox fails, you have bugs. If it passes, great — post your score. If you want to add a new test, send a PR.

## What's in here

```
payloads/
├── c/             (~20 attacks in C: direct syscalls, setuid, mount, ptrace, bpf, ...)
├── cpp/           (same attacks expressed in C++)
├── python/        (high-level: os.*, subprocess, socket, /proc/* reads)
├── java/          (JVM-specific: Runtime.exec, reflection, thread bombs)
├── javascript/    (Bun runtime: fs, net, child_process attacks)
├── typescript/    (same as JS, typed)
├── go/            (raw syscalls via syscall.Syscall6)
└── rust/          (unsafe libc calls, raw syscalls)

manifest.json      (every test's expected containment verdict)
run.sh             (generic runner — POST payloads to any Rustbox-compatible API)
```

## Attack classes

| Class | Example payloads |
|---|---|
| **Kernel syscalls** | `ptrace_attempt.*`, `mount_attempt.*`, `clone_newuser.*`, direct `bpf()`, `io_uring_setup` |
| **Privilege escalation** | `setuid_root.*`, `setgid_root.*`, cap-set manipulation, NO_NEW_PRIVS clearing |
| **Chroot / FS escape** | `escape_chroot.*`, `read_etc_passwd.*`, `read_etc_shadow.*`, traversal via `..` |
| **Info leakage** | `/proc/cpuinfo`, `/proc/meminfo`, `/proc/1/status` (host detection) |
| **Network** | `tcp_connect.*`, `dns_lookup.*`, IMDS metadata probes, `bind()` on privileged ports |
| **Resource bombs** | `fork_bomb.*`, `memory_bomb.*`, `cpu_spin.*`, `fd_exhaustion.*`, `inode_bomb.*`, `file_size_bomb.*` |
| **Execve abuse** | `execve_setuid_binary.c` — tests `MS_NOSUID` mount-flag enforcement |
| **Signal abuse** | `sigxcpu_catch.*` — tries to catch SIGXCPU to outlive the CPU limit |

## Running against a sandbox

```bash
export RUSTBOX_API=https://rustbox-api.orkait.com
export RUSTBOX_KEY=rb_live_your_key
./run.sh                     # runs all 148 tests
./run.sh --lang c            # just one language
./run.sh --test fork_bomb_c  # single test by name
```

Output:
```
[001] fork_bomb_python        PASS (verdict=RE  expected=any-of[RE,TLE,MLE,SIG])
[002] fork_bomb_c             PASS (verdict=PLE expected=any-of[RE,TLE,MLE,SIG])
[003] ptrace_attempt_c        PASS (verdict=RE  exit=159  expected=RE)
...
[148] execve_setuid_binary_c  PASS (verdict=AC  stdout has "OK")

148 passed, 0 failed
```

The runner is sandbox-agnostic. It speaks the same REST shape Rustbox does — `POST /api/submit`, `GET /api/result/{id}` — so any sandbox exposing that interface can be graded.

## Manifest format

Every test entry in `manifest.json` declares:

```json
{
  "name": "ptrace_attempt_c",
  "file": "c/ptrace_attempt.c",
  "language": "c",
  "timeout_sec": 10,
  "expect": {
    "verdict_any": ["RE", "SIG"]
  },
  "description": "seccomp must block ptrace() [c]"
}
```

Supported assertions:
- `verdict` — exact match (`AC`, `RE`, `TLE`, `MLE`, `PLE`, `FSE`, `SIG`, `IE`)
- `verdict_any` — one-of
- `verdict_not` — must not
- `stdout_contains` — substring
- `exit_code` — exact

## Contributing

New attacks welcome. Found a sandbox technique we don't test? Open a PR.

**Responsible disclosure first.** If your test causes a **new** escape (not listed in an existing payload), email `security@orkait.com` before making it public. We'll coordinate a fix and land the test here after the 90-day window.

Merge bar:
- Payload self-contained, one file
- Compiles / runs without extra tooling (no curl / git / network during the attack itself)
- Manifest entry with clear expected behaviour
- Works across at least one language; ideally portable

## License

- **Code (runner, scripts, harness)**: [MIT](./LICENSE-MIT)
- **Test payloads and manifest**: [CC-BY-4.0](./LICENSE-CC-BY-4.0)

Use freely; attribution requested when the payloads are lifted into another sandbox's test suite.

## Related

- [Rustbox](https://rustbox.orkait.com) — the sandbox these tests run against
- [Rustbox documentation](https://rustbox.orkait.com/docs)
- [Rustbox isolation model](https://rustbox.orkait.com/docs/security) — the eight kernel layers these attacks try to defeat
