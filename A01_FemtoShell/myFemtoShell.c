#include <stdio.h>
#include <string.h>
// Let's not go all out
#define MAX_CMD_LEN 200

int main(void)
{
    char input_cmd[MAX_CMD_LEN];

    while(1)
    {
        printf("Please, enter something > ");

        // Not safe but again, let's not go all out
        gets(input_cmd);

        if(!strcmp(input_cmd, "exit"))
        {
            printf("Good Bye :)\n");
            break;   
        }
        else
        {
            printf("You said: %s\n", input_cmd);
        }
        
    }

    return 0;
}
