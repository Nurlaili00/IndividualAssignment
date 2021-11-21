//CLIENT SIDE
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h> //inet_addr
#include <string.h> //strlen
#include <sys/socket.h>

#define MAX 1024
#define PORT 42
#define SA struct sockaddr

   
int main(int argc ,int sockfd, char *argv[])
{	
	int sockDesc;
	struct sockaddr_in server;
    char *message, server_reply[2000];       
        
	char buff[1024];
    bzero(buff, 1024);
    int n;
	
	//Create socket
	sockDesc = socket(AF_INET , SOCK_STREAM , 0);
	if (sockDesc == -1)
	{
		
		printf("[X] Could not create socket");
		
	}
	
	puts("[X] Socket successfully created...\n");
		
	server.sin_addr.s_addr = inet_addr("192.168.140.5"); //enter the ip address of Server 
	server.sin_family = AF_INET;
	server.sin_port = htons( 42 );

	//Connect to remote server
	if (connect(sockDesc , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		
		puts("[X] connect error");
		return 1;
		
	}
	puts("[X] Socket connect to remote server...");
	
	puts("[X] Connected");
	
	puts("\n[X] ARPA Host Name Server Protocol Client :)\n");
	

    //Send some request 
	do
	{
 
        bzero(buff, sizeof(buff));
        printf("[X] Enter your request : \n");
        n = 0;
		
		while ((buff[n++] = getchar()) != '\n');
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
       
      
    } 
	while (0);
	

    //Receive reply from server
    if( recv(sockDesc, server_reply, 2000, 0)<0)
    {
             
			 puts("[X] recv failed");
			 
    }
		
    puts("\n[X] Reply successfully received\n");
    
	puts(server_reply);
	
		
    //Resolve Hostname
	char *hostname = "www.facebook.com";
	char ipAddress[100];
	struct hostent *host;
	struct in_addr **addr_list;
	int i;
		
	if ( (host = gethostbyname( hostname ) ) == NULL) 
	{
		
		//Gethostbyname failed
		herror("gethostbyname");
		return 1;
		
	}
	
	puts("[X] Hostname: www.facebook.com");
	
	//Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
	addr_list = (struct in_addr **) host->h_addr_list;
	
	for(i = 0; addr_list[i] != NULL; i++) 
	{
		
		strcpy(ipAddress , inet_ntoa(*addr_list[i]) );
		
	}
	
	printf("[X] IP Address: %s \n" ,ipAddress);
    return 0;
	
    //Close the socket
    close(sockfd);
	
}
