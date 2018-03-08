#include<stdio.h>  
#include<unistd.h>  
#include<stdlib.h>  
#include<sys/types.h>  
#include<sys/socket.h>  
#include<netinet/in.h>  
#include<string.h>  

#define MAX_BUF_SIZE 1024  
#define PORT 8088  
#define SERVER_IP "172.20.10.2"

int sockfd,addrlen;
struct sockaddr_in addr;


void udp_send(char*buf,int len)
{
	sendto(sockfd, buf, len , 0, (struct sockaddr *)(&addr), addrlen);
}

void udp_init(void)
{
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
	{
			fprintf(stderr, "socket falied\n");
			exit(EXIT_FAILURE);
	}
	addrlen = sizeof(struct sockaddr_in);
	bzero(&addr, addrlen);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	
}

void dup_exit(void)
{
	close(sockfd);
}

