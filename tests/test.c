#include "../minishel.h"

int main()
{
    int fd;

    fd = open("a", O_WRONLY | O_TRUNC | O_CREAT,  0666);
    write(fd , "HELLO", 5);
    close(fd);
    // fd = open("a", O_WRONLY | O_CREAT | O_APPEND, 0666);
    // write(fd , "WORLD\n", 6);
    // close(fd);
}