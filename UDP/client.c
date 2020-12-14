#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <arpa/inet.h>
int main()
{
    int s, r, recb, sntb, x;
    int sa;
    printf("INPUT port number: ");
    scanf("%d", &x);
    socklen_t len;
    struct sockaddr_in server, client;
    char buff[50];
    s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s == -1)
    {
        printf("\nSocket creation error.");
        exit(0);
    }
    printf("\nSocket created.");
    server.sin_family = AF_INET;
    server.sin_port = htons(x);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    len = sizeof(server);
    sa = sizeof(server);

    while (1)
    {
        printf("\n\n");
        printf("Type Message: ");
        scanf("%s", buff);
        sntb = sendto(s, buff, sizeof(buff), 0, (struct sockaddr *)&server, len);
        if (sntb == -1)
        {
            close(s);
            printf("\nMessage sending failed");
            exit(0);
        }
        if (!strcmp(buff, "stop"))
            break;

        recb = recvfrom(s, buff, sizeof(buff), 0, (struct sockaddr *)&server, &sa);
        if (recb == -1)
        {
            printf("\nMessage recieving failed");
            close(s);
            exit(0);
        }
        printf("\nMessage recieved:");
        printf("%s", buff);
        if (!strcmp(buff, "stop"))
            break;
    }
    close(s);
}
