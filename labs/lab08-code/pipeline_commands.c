#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    // Run equivalent of 'sort -n test_cases/resources/numbers.txt | tail -n 10'

    // TODO Create pipe

    pid_t child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        // TODO Insert any necessary cleanup
        return 1;
    } else if (child_pid == 0) {
        // TODO Close write end of pipe

        // TODO Run the 'tail' command, setting up input from pipe first

        return 0;    // Not reached on successful exec()
    }

    // This code only reached by the parent
    // TODO Parent closes read end of pipe

    // TODO Run 'sort' command in original process, setting up output to pipe first

    return 0;    // Not reached on successful exec()
}
