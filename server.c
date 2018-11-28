// watch out, out there. They say hes a computer wiz kid ...

// TODO: send chunks to client with exit message when done
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <stdlib.h>

#include "hashtable/hash_table.h"
#define PORT 8080


#define OPT_PUT 300
#define OPT_GET 301
#define OPT_DELETE 302

#define FLG_PUT_FAIL 400
#define FLG_GET_FAIL 401
#define FLG_DELETE_FAIL 402


/* reverse:  reverse string s in place */
 void reverse(char s[])
 {
     int i, j;
     char c;
 
     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }


 /* itoa:  convert n to characters in s */
 void itoa(int n, char s[])
 {
     int i, sign;
 
     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
 }


int main(int argc, char const *argv[]) 
{
     ht_hash_table* ht = ht_new();
     
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char *hello = "Hello from server"; 
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    }
    
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen)) < 0) 
    { 
         perror("accept"); 
         exit(EXIT_FAILURE); 
    }

    for(;;)
    {
         memset(buffer,0,sizeof(buffer));
         // TODO: inet_pton()
         valread = read( new_socket , buffer, 1024); 

         puts(buffer);
         if (strcmp(buffer,"PUT") == 0)
         {
              printf("PUT operation started with client:%s\n","temp_host");

              itoa(OPT_PUT,buffer);
              send(new_socket, buffer, 1024,0);
              
              valread =  read(new_socket, buffer,1024);
              
              // TODO: thank elijah. kid knows howd'a code...
              char* key = strtok(buffer,"|");
              char* value = strtok(NULL,"|");

              ht_insert(ht,key,value);
              
              buffer[strlen(key)-1] = '\0';
              
         }
         else if (strcmp(buffer,"GET") == 0)
         {
              printf("GET operation started with client:%s\n","temp_host");

              if (ht->count != 0)
              {
                   itoa(OPT_GET,buffer);
                   send(new_socket,buffer,1024,0);
                   
                   valread = read(new_socket, buffer,1024);

                   char* value = ht_search(ht,buffer); // buffer = key emoji

                   if (value != NULL) {
                        strcpy(buffer,value);
                        send(new_socket,buffer,1024,0);
                   }
                   else
                   {
                     send(new_socket,"YOUR pickle RICK",strlen("YOUR pickle RICK"),0);
                   }


              }
              else
              {
                   send(new_socket,"buddy. we gotta talk.",strlen("buddy. we gotta talk."),0);
              }


         }
         else if (strcmp(buffer,"DELETE") == 0)
         {
              printf("DELETE operation started with client:%s\n","temp_host");

              if (ht->count != 0)
              {
                   itoa(OPT_DELETE,buffer);
                   send(new_socket,buffer,1024,0);
                   
                   valread = read(new_socket, buffer, 1024);
                   puts(buffer);
                   ht_delete(ht,buffer);
              }
              else
              {
                   send(new_socket,"buddy. we gotta talk.",strlen("buddy. we gotta talk."),0);
              }


         }
         else
         {
              printf("bad message... try again..\n");
              send(new_socket, "bad message... try again...\n",strlen("bad message... try again...\n"),0);
         }

    }
    return 0; 
} 
