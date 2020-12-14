#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
int main()
{
    int s, r, recarr, recsize, recchoice, sntb, x, ns, a = 0;
    printf("INPUT port number: ");
    scanf("%d", &x);
    socklen_t len;
    struct sockaddr_in server, client;
    int buff[50];
    int n;
    char choice;
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == -1)
    {
        printf("\nSocket creation error.");
        exit(0);
    }
    printf("\nSocket created.");
    server.sin_family = AF_INET;
    server.sin_port = htons(x);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    r = bind(s, (struct sockaddr *)&server, sizeof(server));
    if (r == -1)
    {
        printf("\nBinding error.");
        exit(0);
    }
    printf("\nSocket Binded.");
    r = listen(s, 1);
    if (r == -1)
    {
        close(s);
        exit(0);
    }
    printf("\nSocket Listening.");
    len = sizeof(client);
    ns = accept(s, (struct sockaddr *)&client, &len);
    if (ns == -1)
    {
        close(s);
        exit(0);
    }
    printf("\nSocket Accepting.");
    recsize = recv(ns, n, sizeof(n), 0);
    if (recsize == -1)
    {
        printf("\nSize Recieving Failed");
        close(s);
        close(ns);
        exit(0);
    }
    recarr = recv(ns, buff, sizeof(buff), 0);
    if (recarr == -1)
    {
        printf("\nArray Recieving Failed");
        close(s);
        close(ns);
        exit(0);
    }
    recchoice = recv(ns, choice, sizeof(choice), 0);
    if (recchoice == -1)
    {
        printf("\nArray Recieving Failed");
        close(s);
        close(ns);
        exit(0);
    }
    printf("Size of Array: %d", n);
    printf("Array: \n");
    for (int i = 0; i < n; i++)
        printf("%d ", buff[i]);
    printf("\n");
    printf("Choice: %c", &choice);
    scanf("%s", buff);
    sntb = send(ns, buff, sizeof(buff), 0);
    if (sntb == -1)
    {
        printf("\nMessage Sending Failed");
        close(s);
        close(ns);
        exit(0);
    }
    close(ns);
    close(s);
}