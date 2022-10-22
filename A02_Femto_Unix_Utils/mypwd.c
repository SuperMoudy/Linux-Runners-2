#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_LEN 2000

// Wrapper for write, LOL :D
void print(char *buf);
void terminate(char *msg);



int main(void)
{
    char buf[BUF_LEN];
    char *buf_ptr;

    buf_ptr = getcwd(buf, BUF_LEN);

    if(buf_ptr == NULL)
    {
        terminate("Error printing working directory.");
    }

    print(buf_ptr);
    print("\n");

    return EXIT_SUCCESS;
}

void print(char *buf)
{
    int len;

    len = write(STDOUT_FILENO, buf, strlen(buf));

    if(len == -1)
    {
        terminate("Error in write.");
    }
}

void terminate(char *msg)
{
    printf("%s\n", msg);
    exit(EXIT_FAILURE);    
}
