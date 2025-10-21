#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    // TODO Fork a child process to run the command "cat sample.txt"
    // The parent should wait and print out the child's exit code
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork() failed");
        return 1;
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            printf("Child exited with status %d\n", exit_status);
        } else {
            printf("Child did not exit correctly\n");
        }
    } else {
        execlp("cat", "cat", "sample.txt", (char *)NULL);
    }
    return 0;
}
