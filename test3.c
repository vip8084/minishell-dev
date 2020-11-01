
#include "minishel.h"

void    ft_pipe(char *path, char **comand, t_vars *vars)
{
    pid_t pid;
    int mas[2];
    int i;
    pipe(mas);
    pid = fork();
    if (pid == 0)
    {
        close(mas[0]);
        dup2(mas[1], 1);
        close(mas[1]);
        i = execve(path, comand, NULL);
        exit(0);
    }
    else
    {
        close(mas[1]);
        dup2(mas[0], 0);
        close(mas[0]);
        waitpid(pid, &i, WUNTRACED);
    } 
}

int main()
{
    pid_t pid;
    t_vars vars;
    int mas[2];
    char *comand[]={"ls", NULL};
    char *comand2[]={"cat","-e", NULL};
    int i;
    ft_pipe("/bin/ls", comand, &vars);
    ft_pipe("/bin/cat", comand2, &vars);
    pid = fork();
    if(pid == 0)
    {
        i = execve("/bin/cat", comand2, NULL);
        exit(i);
    }
    waitpid(pid, &i, WUNTRACED);
    return 0;
}