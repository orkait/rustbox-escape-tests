#include <stdio.h>
#include <dirent.h>

int main(void) {
    DIR *d = opendir("/sys");
    if (!d) {
        perror("opendir /sys blocked");
        return 1;
    }
    struct dirent *ent;
    int count = 0;
    while ((ent = readdir(d)) != NULL && count < 10) {
        printf("  %s\n", ent->d_name);
        count++;
    }
    closedir(d);
    printf("ESCAPED\n");
    return 0;
}
