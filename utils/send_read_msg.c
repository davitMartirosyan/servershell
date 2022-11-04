#include <sys/socket.h>

void send_msg(int fd, char* msg, int16_t size_msg)
{
    // send size of command
    if(send(fd, &size_msg, 2, 0) < 0)
    {
        perror("Error, send size of command");
        exit(EXIT_FAILURE);
    }
//    printf("Send msg size done!\n");

    // send command
    if(send(fd, msg, size_msg, 0) < 0)
    {
        perror("Error, send command");
        exit(EXIT_FAILURE);
    }
//    printf("Send msg done!\n");
}

void read_msg(int fd, char** msg, int16_t* size_msg)
{
    // read size of command output
    if (read(fd, size_msg, 2) < 0) {
        perror("Error, read size of command output");
        exit(EXIT_FAILURE);
    }
//    printf("read size of msg ~ %d\n", *size_msg);

    //read command output
    *msg = (char *)(malloc(*size_msg));
    if (read(fd, *msg, *size_msg) < 0) {
        perror("Error read command output");
        exit(EXIT_FAILURE);
    }
//    printf("read msg ~ %s\n", *msg);

}