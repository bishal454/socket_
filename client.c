#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>



#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define MAX_DATA 1024


int main(int argc , char * argv ){
    int data_len ;
    int sock ;
    char input[MAX_DATA], output[MAX_DATA];
    struct sockaddr_in client;

    if(argc!=3){
        printf("Usage ./prog IP port \n");
        exit(1);


    }


    if((sock=socket(AF_INET, SOCK_STREAM, 0))==-1){
        printf("Error Socket:");
        exit(1);

    }

client.sin_family=AF_INET;
client.sin_port=htons(atio(argv[2]));
client.sin_addr.s_addr=inet_addr(argv[1]);

bzero(client.sin_zero,8);



if((connect(sock ,(struct sockaddr *) &client, sizeof(struct  sockaddr))))
{

perror("connect:\n");
exit(1);

}

while(1){

    fgets(input ,MAX_DATA,stdin);
    send(sock ,input,strlen(input),0);
    data_len=recv(sock,output,MAX_DATA,0);
    output [data_len]="\0";
    printf("%s\n",output);

}
close(sock);
return 0;

}


