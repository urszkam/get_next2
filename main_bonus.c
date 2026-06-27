#include "get_next_line_bonus.h"
#include <fcntl.h>

int main(void) {
    int fd = open("example.txt", O_RDONLY);
    int fd2 = open("example2.txt", O_RDONLY);
    int fd3 = open("example3.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL) {
        printf("output: %s", line);
        free(line);
        if (line = get_next_line(fd2))
        printf("output: %s", line);
        free(line);
        if (line = get_next_line(fd3))
        printf("output: %s", line);
        free(line);
    }

    close(fd);
    return 0;
}