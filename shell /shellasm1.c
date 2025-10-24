//Improve your shell program so that it should not be terminated due to SIGINT (ctrl+C).

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>

void handle_sigint(int sig) {
}

int main(void) {
    char cmd[256];
    char *args[10], *ptr;
    int i = 0;

    signal(SIGINT, handle_sigint);

    while(1) {
        printf("cmd> ");
        if (fgets(cmd, sizeof(cmd), stdin) == NULL) {
            continue;
        }

        cmd[strcspn(cmd, "\n")] = 0;

        i = 0;
        ptr = strtok(cmd, " ");
        while (ptr != NULL) {
            args[i++] = ptr;
            ptr = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (args[0] == NULL) {
            continue;
        }

        int pid = fork();
        if(pid == 0) {
            signal(SIGINT, SIG_DFL);
            int ret = execvp(args[0], args);
            if(ret == -1) {
                perror("execvp");
            }
            _exit(1);
        } else {
            int s;
            wait(&s);
        }
    }

    return 0;
}

