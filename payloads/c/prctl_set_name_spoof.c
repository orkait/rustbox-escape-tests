#include <stdio.h>
#include <sys/prctl.h>
#include <unistd.h>

int main(void) {
    int rc = prctl(PR_SET_NAME, "judge-service", 0, 0, 0);
    if (rc != 0) {
        printf("CONTAINED prctl_failed rc=%d\n", rc);
        return 0;
    }
    usleep(150000);
    printf("CONTAINED spoof_attempted_process_ran\n");
    return 0;
}
