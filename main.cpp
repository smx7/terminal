#include<iostream>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc,char* argv[])
{
    if(argc != 3)
    {
        std::cout<<"usage ip port"<<std::endl;
    }

    int listen_sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(listen_sockfd < 0)
    {
        perror("create socket error: ");
        return -1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));

    if(connect(listen_sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
        perror("connect error: ");
        return -1;
    }

    while(true)
    {
        char input[1024];
        char res[1024];

        recv(listen_sockfd,res,1024,0);
        write(1,res,1024);

        ssize_t size = read(0,input,sizeof(input));
        if(size > 0)
        {
            send(listen_sockfd,input,size,0);
        }       
    }

    return 0;

}