#include "get_next_line.h"
#include <fcntl.h>

int main(int argc, char **argv) {
    if (argc < 2)
        return (1);
    int fd = open(argv[1], O_RDONLY);
    char *line;
    while ((line = get_next_line(fd)) != NULL) {
        printf("output: %s", line);
        free(line);
    }
    close(fd);
    return 0;
}
