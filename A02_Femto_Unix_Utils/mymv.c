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
    int ret;

    char buf[BUF_LEN];
    int rw_count;

    if(argc == 1)
    {
        print("mymv: missing file operand\n");
        print("Usage: mymv <src> <dst>\n");
        return EXIT_FAILURE;
    }

    if(argc == 2)
    {
        print("mymv: missing destination file operand after \'");
        print(argv[1]);
        print("\'\n");
        print("Usage: mymv <src> <dst>\n");
        return EXIT_FAILURE;
    }

    // Correct usage
    src_fd = open(argv[1], O_RDONLY);

    if(src_fd == -1)
    {
        print("mymv: cannot stat \'");
        print(argv[1]);
        print("\': No such file or directory\n");
        return EXIT_FAILURE;   
    }

    // Get the file stats
    ret = fstat(src_fd, &src_stats);

    if(ret == -1)
    {
        print("mymv: cannot stat \'");
        print(argv[1]);
        print("\': I have no idea what the problem is, LOL\n");
        return EXIT_FAILURE;
    }

    src_mode = src_stats.st_mode;

    // Remove file if exists
    remove(argv[2]);

    dst_fd = open(argv[2], O_WRONLY | O_CREAT | O_APPEND, src_mode);

    if(dst_fd == -1)
    {
        print("mymv: cannot create desination file\n");
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

    remove(argv[1]);

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
