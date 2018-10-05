#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>

using std::cout;

#define  MAXLINE 4096

int main(int argc, char** argv)
{
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[4096];
    int n;

    if((listenfd=socket(AF_INET, SOCK_STREAM, 0))==-1)
    {
        cout << "create socket error: " << strerror(errno) << "(errno: " << errno << ")\n";
        exit(0);
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(6666);

    if(bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1)
    {

        cout << "bind socket error: " << strerror(errno) << "(errno: " << errno << ")\n";
        exit(0);

    }

    if(listen(listenfd, 10) == -1)
    {
        cout << "listen socket error: " << strerror(errno) << "(errno: " << errno << ")\n";
        exit(0);
    }
    cout << "======waiting for client's request======/n";
    while(1)
    {
        if((connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) == -1)
        {
            cout << "accept socket error: " << strerror(errno) << "(errno: " << errno << ")\n";
            continue;
        }
        n = recv(connfd, buff, MAXLINE, 0);
        buff[n] = '\0';
        cout << "recv msg from client: %s\n" << buff;
        close(connfd);
    }
    close(listenfd);

    return 0;
}