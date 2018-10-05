#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

using std::cout;

int main(int argc, char **argv)
{
    int sockfd, n;
    char recvline[4096], sendline[4096];
    struct sockaddr_in servaddr;

    if(argc != 2)
    {
        cout << "usage: /.client <ipaddress>\n";
    }

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0 )) < 0)
    {
        cout << "create socket error: " << strerror(errno) << "(errno: " << errno << ")\n";
        exit(0);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6666);
    if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
    {

        cout << "inet_pton error for " << argv[1] << "\n";
        exit(0);
    }

    if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr) < 0))
    {

        cout << "connect socket error: " << strerror(errno) << "(errno: " << errno << ")\n";
        exit(0);
    }
    cout << "send msg to server: \n";
    fgets(sendline, 4096, stdin);
    if(send(sockfd, sendline,strlen(sendline), 0) < 0)
    {

        cout << "send msg error: " << strerror(errno) << "(errno: " << errno << ")\n";
        exit(0);
    }
    close(sockfd);
    exit(0);

}