#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/stat.h>
int main()
{
    int s, r, recarr, sntarr, sntsize, sntchoice, x;
    printf("INPUT port number: ");
    scanf("%d", &x);
    struct sockaddr_in server;
    int buff[50];
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == -1)
    {
        printf("\nSocket creation error.");
        exit(0);
    }
    printf("\nSocket created.");
    server.sin_family = AF_INET;
    server.sin_port = htons(x);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    r = connect(s, (struct sockaddr *)&server, sizeof(server));
    if (r == -1)
    {
        printf("\nConnection error.");
        exit(0);
    }
    printf("\nSocket connected.");
    printf("\n\n");
    int n;
    printf("Enter array size: ");
    scanf("%d", &n);
    sntsize = send(s, n, sizeof(n), 0);
    if (sntsize == -1)
    {
        close(s);
        printf("\nArray Size Sending Failed");
        exit(0);
    }
    printf("Enter array elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &buff[i]);
    sntarr = send(s, buff, sizeof(buff), 0);
    if (sntarr == -1)
    {
        close(s);
        printf("\nArray Sending Failed");
        exit(0);
    }
    char choice;
    printf("1. Sort\n2. Split\n3. Exit");
    scanf("%c", &choice);
    sntchoice = send(s, buff, sizeof(buff), 0);
    if (sntchoice == -1)
    {
        close(s);
        printf("\nChoice Sending Failed");
        exit(0);
    }
    recarr = recv(s, buff, sizeof(buff), 0);
    if (recarr == -1)
    {
        printf("\nMessage Recieving Failed");
        close(s);
        exit(0);
    }
    printf("\nMessage Recieved: ");
    printf("%s", buff);
    printf("\n\n");
    close(s);
}