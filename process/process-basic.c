#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void createProcessTree(int depth, int maxDepth) {
    if (depth >= maxDepth)
        return;

    pid_t left, right;

    left = fork();

    if (left < 0) {
        perror("fork failed");
        exit(1);
    } else if (left == 0) {
        // Left child process
        printf("Depth %d | PID %d | Parent %d (Left child)\n", depth + 1, getpid(), getppid());
        createProcessTree(depth + 1, maxDepth);
        exit(0);
    }

    right = fork();

    if (right < 0) {

        perror("fork failed");
        exit(1);
    } else if (right == 0) {

        printf("Depth %d | PID %d | Parent %d (Right child)\n", depth + 1, getpid(), getppid());
        createProcessTree(depth + 1, maxDepth);
        exit(0);
    }

    waitpid(left, NULL, 0);
    waitpid(right, NULL, 0);
}

int main() {

    printf("Root process PID %d\n", getpid());
    createProcessTree(0, 3);
    return 0;
}
