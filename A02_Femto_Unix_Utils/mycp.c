#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUF_LEN 1000

void terminate(char *msg);

void print(char *buf);

int main(int argc, char **argv)
{
    int src_fd, dst_fd;
    mode_t src_mode; // File permissions of src
    struct stat src_stats;
    int fstats_ret;

    char buf[BUF_LEN];
    int rw_count;

    if(argc == 1)
    {
        print("mycp: missing file operand\n");
        print("Usage: mycp <src> <dst>\n");
        return EXIT_FAILURE;
    }

    if(argc == 2)
    {
        print("mycp: missing destination file operand after \'");
        print(argv[1]);
        print("\'\n");
        print("Usage: mycp <src> <dst>\n");
        return EXIT_FAILURE;
    }

    // Correct usage
    src_fd = open(argv[1], O_RDONLY);

    if(src_fd == -1)
    {
        print("mycp: cannot stat \'");
        print(argv[1]);
        print("\': No such file or directory\n");
        return EXIT_FAILURE;   
    }

    // Get the file stats
    fstats_ret = fstat(src_fd, &src_stats);

    if(fstats_ret == -1)
    {
        print("mycp: cannot stat \'");
        print(argv[1]);
        print("\': I have no idea what the problem is, LOL\n");
        return EXIT_FAILURE;
    }

    src_mode = src_stats.st_mode;

    dst_fd = open(argv[2], O_WRONLY | O_CREAT | O_APPEND, src_mode);

    if(dst_fd == -1)
    {
        print("mycp: cannot create desination file\n");
        return EXIT_FAILURE;
    }

    rw_count = read(src_fd, buf, BUF_LEN);

    while(rw_count != 0 && rw_count != -1)
    {   
        write(dst_fd, buf, rw_count);

        rw_count = read(src_fd, buf, BUF_LEN);
    }
    
    close(src_fd);
    close(dst_fd);

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
