#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int pipefd[2];
    int ret = pipe(pipefd);
    long size = fpathconf(pipefd[0],_PC_PIPE_BUF);
    printf("pipe size: %ld",size);
    return 0;
}
