
#include "../minishel.h"


int main()
{
    pid_t pid;
    t_vars vars;
    //int mas[2];
    char *comand[]={"ls", NULL};
    char *comand2[]={"cat","-e", NULL};
    char *mas[] = {"a", NULL};
    vars.envp_copy = NULL;
    // ft_redirects_revers("bin/cat", comand2, mas, &vars);
    system_funk("bin/ls", comand, &vars);
    return 0;
}