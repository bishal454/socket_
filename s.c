#include<stdio.h>
#include<stdlib.h>
#include<errno.h> // perror()
#include<string.h> // strlen()
#include <unistd.h> // close()


#include<sys/types.h>
#include<sys/socket.h> // inet_addr()
#include<netinet/in.h> // inet_addr()
#include<arpa/inet.h> // inet_addr()

#define MAX_DATA 1000

int main(int argc, char **argv)
{

	int serSock, cliSock;
	int len;
	int data_len; 
	char msg[MAX_DATA];
	struct sockaddr_in server, client;

	if(argc!=2)
	{
		printf("Usage ./prog port\n");
		exit(1);
	}
	
	if ((serSock=socket(AF_INET, SOCK_STREAM, 0))==-1)
	{
		perror("socket: ");
		exit(-1);
	} 
	
	server.sin_family= AF_INET;
	server.sin_port= htons(atoi(argv[1]));
	server.sin_addr.s_addr= INADDR_ANY;
	bzero(&server.sin_zero, 8);
	
	// bind
	len = sizeof(struct sockaddr_in);

	if ((bind(serSock, (struct sockaddr*)&server, len))==-1)
	{
		perror("bind: ");
		exit(-1);	
	}
	
	// listen
	if ((listen(serSock, 10))==-1)
	{
		perror("listen: ");
		exit(-1);	
	}
	
	//
	while(1)
	{
		if ( (cliSock=accept(serSock, (struct sockaddr*)&client, &len))==-1)
		{
			perror("accept: \n");
			exit(1);	
		}
		
		printf("New client connected to port no %d IP address %s\n", ntohs(client.sin_port), inet_ntoa(client.sin_addr));
		
		data_len=1; 
		while(data_len)
		{
			data_len = recv(cliSock, msg, MAX_DATA, 0);
			if (data_len)
			{
				send(cliSock, msg, data_len, 0);
				msg[data_len]='\0';
				printf("Sent mesg: %s", msg);
			}
			// printf("data_len is %d\n", data_len);
		}
		
		close(cliSock);
	}
	close(serSock);

}
