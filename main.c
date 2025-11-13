#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>



#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>


#define MAX_DATA 1000







int main(int argc, char *argv[]){


    int len;
    int data_len;
    int  serSock, cliSock;
    char msg[MAX_DATA];
    struct sockaddr_in server,client;



    if(argc!=2){

        printf("Usage ./prog port\n");
        exit(1);


    }


    if((serSock=socket(AF_INET, SOCK_STREAM,0))==-1)
{
    perror("socket:");
    exit(-1);

} 



server.sin_family=AF_INET;
server.sin_port = htons(atoi(argv[1]));
server.sin_addr.s_addr=INADDR_ANY;
bzero(server.sin_zero,8);


len=sizeof(struct sockaddr_in);

if((bind(serSock,(struct sockaddr*) &server,len))==-1)
{
perror("bind:");
exit(-1);

}

if((listen(serSock,10))==-1){
    perror("listen:");
    exit(-1);

}

while(1)
{

    if((cliSock=accept(serSock,(struct sockaddr*) &client, &len))==-1)
    {
        perror("accept: \n");
        exit(1);


    }
    printf("New client connected to port no %d IP address %s\n",
    ntohs(client.sin_port), inet_ntoa(client.sin_addr));

    data_len=1;
    while(data_len)
    {

        data_len=recv(cliSock,msg, MAX_DATA,0);
        if(data_len){

            send(cliSock,msg,data_len,0);

            msg[data_len]='\0';

            printf("sent mesg:%s",msg);

        }
    }

    printf("client dissconnected .\n");
    close(cliSock);


}
close(serSock);






    return 0;
}