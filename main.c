#include "get_next_line.h"
#include <fcntl.h>

int main(int argc, char **argv) {
    int fd = 0;
    if (argc > 1)
        fd = open(argv[1], O_RDONLY);
    char *line;
    while ((line = get_next_line(fd)) != NULL) {
        printf("output: %s", line);
        free(line);
    }
    close(fd);
    return 0;
}
