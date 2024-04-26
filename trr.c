#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main (int ac, char **av, char **env)
{
    int fd_input;
    int pipe_fd[2];
    int fd_output;
    char *cmd1 = "/usr/bin/ls";
    char *cmd2 = "/usr/bin/wc";
    int  pid1;
    int  pid2;

    fd_input = open("Makefile", O_RDONLY);
    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        exit(1);
    }

    pid1 = fork();
    if (pid1 == -1)
    {
        perror("fork");
        exit(1);
    }
    if (pid1 == 0)
    {
        //child 1
        close (pipe_fd[0]);
        dup2(fd_input, STDIN_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
        execve(cmd1, NULL, env);
    }
    return 0;
}