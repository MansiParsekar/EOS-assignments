//Implement asynchronous execution in your shell i.e. if command suﬃxed with &, then shell should not wait for the child process. Ensure that process isn't left zombie.


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>

#define MAX_CMD_LEN 256
#define MAX_ARGS 10

void handle_sigchld(int sig) {
    int status;
    while (waitpid(-1, &status, WNOHANG) > 0);
}

void handle_sigint(int sig) {
}

int main(void) {
    char cmd[MAX_CMD_LEN];
    char *args[MAX_ARGS];
    int i;
    
    signal(SIGINT, handle_sigint);
    
    signal(SIGCHLD, handle_sigchld);

    while(1) {
        printf("cmd> ");
        if (fgets(cmd, sizeof(cmd), stdin) == NULL) {
            continue;
        }

        cmd[strcspn(cmd, "\n")] = 0;

        int is_async = 0;
        if (strlen(cmd) > 0 && cmd[strlen(cmd) - 1] == '&') {
            is_async = 1;
            cmd[strlen(cmd) - 1] = '\0';
        }

        i = 0;
        char *ptr = strtok(cmd, " ");
        while (ptr != NULL && i < MAX_ARGS - 1) {
            args[i++] = ptr;
            ptr = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (args[0] == NULL) {
            continue;
        }
        
        int pid = fork();
        if (pid == 0) {
            signal(SIGINT, SIG_DFL);
            
            execvp(args[0], args);
            perror("execvp");
            _exit(1);
        } else {
            if (is_async == 0) {
                waitpid(pid, NULL, 0);
            }
        }
    }

    return 0;
}

