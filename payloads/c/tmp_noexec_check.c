#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

int main(void) {
    const char *path = "/tmp/probe_exec.sh";
    FILE *f = fopen(path, "w");
    if (!f) {
        printf("CONTAINED fopen blocked errno=%d\n", errno);
        return 0;
    }
    const char *sh = "#!/bin/sh\necho PWNED_TMP\n";
    fwrite(sh, 1, strlen(sh), f);
    fclose(f);
    chmod(path, 0755);

    errno = 0;
    int rc = execl(path, path, (char *)NULL);
    int e = errno;
    if (rc == -1 && e == EACCES) {
        printf("CONTAINED noexec EACCES\n");
    } else {
        printf("ESCAPED rc=%d errno=%d\n", rc, e);
    }
    return 0;
}
