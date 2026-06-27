#include "get_next_line.h"
#include <fcntl.h>

int main(void) {
    int fd = open("example.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL) {
        printf("output: %s", line);
        free(line);
    }

    close(fd);
    return 0;
}