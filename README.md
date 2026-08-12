*This project has been created as part of the 42 curriculum by urkamins.*

# Table of Contents
- [Description](#description)
    - [Bonus](#bonus)
- [Instructions](#instructions)
    - [Prerequisites](#prerequisites)
    - [Clone the Repository](#clone-the-repository)
    - [Usage](#usage)
    - [Cleanup](#cleanup)
- [Resources](#resources)
- [Algorithm](#algorithm)

# Description
This project focuses on implementing a C function that reads and returns one line at a time from a file descriptor.

### Bonus
The bonus part handles multiple file descriptors simultaneously using a single static variable.

# Instructions
To compile and use the get_next_line function, follow these steps:

## Prerequisites
Ensure you have the following installed on your system:

- C Compiler (e.g., GCC)

## Clone the Repository
Clone the get_next_line repository to your local machine:

```bash
git clone <url> gnl
cd gnl
```

## Usage
In the source code, include the get_next_line.h header and compile the project with the required flags and an optional [BUFFER_SIZE]:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c -o gnl
```

Then run the executable:

```bash
./gnl
```
Example of function usage in main:

```c
#include "get_next_line.h"
#include <fcntl.h>

int main(void) {
    int fd = open(<filename>, O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL) {
        // process the line
        free(line);
    }

    close(fd);
    return 0;
}
```

# Resources

- [Preprocessor options](https://gcc.gnu.org/onlinedocs/gcc/Preprocessor-Options.html#index-D) - describes usage of -D preprocessor flag.
- [Linux read man page](https://man7.org/linux/man-pages/man2/read.2.html) - reference for standard C read function.
- Linux manual - local documentation.
- [Stack Overflow](https://stackoverflow.com) - additional explanations and examples of functions implementation.

# Algorithm
1. The `get_next_line` function reads content of the file in chunks of [BUFFER_SIZE] until the chunk contains end of line(or when the content ends), so that there is no need to read all content at once
2. The content is stored in a static variable which allows to store remaining text between calls
3. A full line of the extracted content is returned and the static variable keeps only the content read after the returned line
4. The next chunk(s) of content are read and concatenated with the remaining content from the previous call
5. When there is no more content to read, NULL is returned

AI was not used in the project implementation.
