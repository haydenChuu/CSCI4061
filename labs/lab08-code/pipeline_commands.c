#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    // Run equivalent of 'sort -n test_cases/resources/numbers.txt | tail -n 10'

    // TODO Create pipe
    int pipe_fds[2];
    if (pipe(pipe_fds) == -1) {
        perror("pipe");
        return 1;
    }


    pid_t child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        // TODO Insert any necessary cleanup
        close(pipe_fds[0]);
        close(pipe_fds[1]);
        return 1;
    } else if (child_pid == 0) {
        // TODO Close write end of pipe
        if (close(pipe_fds[1]) == -1) {
            perror("close");
            return 1;
        }
        // TODO Run the 'tail' command, setting up input from pipe first
        if (dup2(pipe_fds[0], STDIN_FILENO) == -1) {
            perror("dup2");
            return 1;
        }
        close(pipe_fds[0]);
        execlp("tail", "tail", "-n", "10", NULL);
        perror("execlp");
        return 0;    // Not reached on successful exec()
    }

    // This code only reached by the parent
    // TODO Parent closes read end of pipe
    if (close(pipe_fds[0]) == -1) {
        perror("close");
        close(pipe_fds[1]);
        return 1;
    }
    // TODO Run 'sort' command in original process, setting up output to pipe first
    if (dup2(pipe_fds[1], STDOUT_FILENO) == -1) {
        perror("dup2");
        close(pipe_fds[1]);
        return 1;
    }
    close(pipe_fds[1]);
    execlp("sort", "sort", "-n", "test_cases/resources/numbers.txt", NULL);
    perror("execlp");
    return 0;    // Not reached on successful exec()
}
