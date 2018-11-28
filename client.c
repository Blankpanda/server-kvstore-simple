#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>

#define PORT 8080

#define OPT_PUT 300
#define OPT_GET 301
#define OPT_DELETE 302

int main(int argc, char const *argv[]) 
{ 
	struct sockaddr_in address; 
	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	char *hello = "GET";
	char buffer[1024] = {0}; 
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

	memset(&serv_addr, '0', sizeof(serv_addr)); 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
          { 
		printf("\nConnection Failed \n"); 
		return -1; 
	}

        // Read in input 
      
        for(;;) {
             char input[1024];
             
             printf("[127.0.0.1]~>");
             scanf("%s",input);
             
          // See if they want to exit
          if(strcmp(input, "exit") == 0) {
            exit(1);
          }
          else if(strcmp(input,"PUT") == 0)
          {
               
               send(sock,"PUT",strlen("PUT"),0);
               valread = read( sock ,buffer,1024);

               int i_buffer = atoi(buffer);

               if (i_buffer == OPT_PUT)
               {
                    // TODO: this will later be in the format of PUT <KEY> <VALUE>, I just dont feel like using strok() :^)
                    // probably not though because this client is a demo
                    printf("Please enter key value pair in format Key|Value:");                   
                    scanf("%s",input);
                    
                    send(sock,input,1024,0);
               }
               
//               printf("%s\n",buffer);
          }
          else if(strcmp(input,"GET") == 0)
          {
               send(sock,"GET",strlen("GET"),0);
               valread = read( sock , buffer, 1024);

               int i_buffer = atoi(buffer);

               if (i_buffer == OPT_GET)
               {
                    printf("Please enter desired key:");
                    scanf("%s",input);

                    // NOTE: if this gets 301, the key was deleted.
                    // the servers returning a OPT_DELETE
                    // it also segfaults, but thats the hash table.
                    // TODO: error checking
                    send(sock,input,1024,0);                    
                    valread = read(sock, buffer, 1024);

                    printf("Got Value:");                    
                    puts(buffer); 
                    
               }
          }
          else if(strcmp(input,"DELETE") == 0)
          {
               send(sock,"DELETE",strlen("DELETE"),0);
               valread = read( sock , buffer, 1024);

               int i_buffer = atoi(buffer);

               if(i_buffer == OPT_DELETE)
               {
                    printf("Please enter the key to delete:");
                    scanf("%s",input);

                    send(sock,input,1024,0);                   
                    
               }

          }
          else // gunna send it to the server anyway LOL
          {
               send(sock,input,strlen(input),0);
               valread = read( sock , buffer, 1024);
          }

          fflush(stdin);        

        }

        
	return 0; 
} 
