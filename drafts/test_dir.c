#include "minishel.h"

int main()
{
    DIR *dir;
    struct dirent *st;

    dir = opendir("/bin");
    while((st = readdir(dir)) != NULL)
    {
        printf("%s\n", st->d_name);
    }
}