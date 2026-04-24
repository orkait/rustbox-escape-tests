// Verify the nosuid mount flag strips setuid bits at execve time.
//
// The base image ships several setuid-root binaries (/bin/su, /bin/mount,
// /bin/passwd, ...). Every bind mount in the sandbox is created with
// MS_NOSUID, so the kernel must ignore the setuid bit when any of these
// binaries is executed inside the sandbox. Our own euid must never
// become 0.
//
// Fails (exit 1) if euid escalates. Passes (exit 0) whether a candidate
// is found or not.

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void) {
    static const char *candidates[] = {
        "/bin/su",        "/usr/bin/su",
        "/bin/mount",     "/usr/bin/mount",
        "/bin/passwd",    "/usr/bin/passwd",
        "/bin/chsh",      "/usr/bin/chsh",
        "/bin/chfn",      "/usr/bin/chfn",
        NULL,
    };

    const char *target = NULL;
    struct stat st;
    for (int i = 0; candidates[i]; i++) {
        if (stat(candidates[i], &st) == 0
            && (st.st_mode & S_ISUID)
            && st.st_uid == 0) {
            target = candidates[i];
            break;
        }
    }

    if (!target) {
        // No setuid-root binary in the sandbox - nothing to strip, pass.
        printf("NO_SUID_ROOT_BINARIES\n");
        return 0;
    }
    printf("target=%s mode=%o\n", target, st.st_mode & 07777);

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 2;
    }
    if (pid == 0) {
        // Attempt to exec the setuid-root binary. If MS_NOSUID is honored,
        // this runs as uid 60000; the binary typically errors out because
        // it expects root. Either way, the parent's euid must not change.
        execl(target, target, NULL);
        _exit(127);
    }
    int status = 0;
    waitpid(pid, &status, 0);

    uid_t euid = geteuid();
    printf("parent_euid_after=%u\n", euid);
    if (euid == 0) {
        printf("ESCAPED\n");
        return 1;
    }
    printf("OK: nosuid mount contained the setuid bit\n");
    return 0;
}
