#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void terminate(char *msg);
void print(char *buf);

int main(int argc, char **argv)
{
    int i;
    if(argc > 1)
    {
        for(i = 1; i < argc; i++)
        {
            print(argv[1]);

            if(i != (argc - 1))
            {
                print(" ");
            }
        }
        
    }
    
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
