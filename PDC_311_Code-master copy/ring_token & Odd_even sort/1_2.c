#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void pass_token(int read_fd, int write_fd) {
    int token;
    read(read_fd, &token, sizeof(int));
    printf("Process %d received token %d\n", getpid(), token);
    token--;
    write(write_fd, &token, sizeof(int));
}

int main() {
    int pipe_fd[2];
    int num_processes = 5;
    int token = 100;

    pipe(pipe_fd);

    if (fork() == 0) {
        close(pipe_fd[1]);  // Close write end
        pass_token(pipe_fd[0], pipe_fd[1]);
        close(pipe_fd[0]);
        exit(0);
    }

    close(pipe_fd[0]);  // Close read end

    // Root process
    write(pipe_fd[1], &token, sizeof(int));

    // Wait for child process to finish
    wait(NULL);

    close(pipe_fd[1]);
    return 0;
}

