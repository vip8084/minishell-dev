
#include "../minishel.h"


void ptr_free(char **ptr)
{
    if(*ptr != NULL)
    {
        free(*ptr);
        *ptr = NULL;
    }
}
int main()
{
    char *ptr;
    ptr = ft_strdup("hello");
    printf("%s\n", ptr);
    ptr_free(&ptr);
    printf("%s\n", ptr);
    ptr_free(&ptr);
    printf("%s\n", ptr);

}