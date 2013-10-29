#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <arpa/inet.h>



int InitPort(char *str)
 {
   return atoi(str);
 }


int main(int argc, char *argv[])
{

   if(!argv[1])
    {
     write(1,"incorrect input data",strlen("incorrect input data"));
     return 0;
    }
   int sock, client;
   int port = InitPort(argv[1]);
   socklen_t fromlen;
   struct sockaddr_in server;
   struct sockaddr_in from;
   char buf[1024];

   sock=socket(AF_INET, SOCK_STREAM,0);
    if (sock < 0) 
     {
       perror("socket error"); exit(1);
     }
   
   memset(&server,0,sizeof(server));
   server.sin_family=AF_INET;
   server.sin_addr.s_addr = INADDR_ANY;
   server.sin_port=htons(port);

   if (bind(sock,(struct sockaddr *)&server,sizeof(server))<0) 
    {
      perror("bind error"); exit(2);
    }

   fromlen = sizeof(struct sockaddr_in);

   while(1)
      {
       listen(sock, 5);
       client = accept(sock, (struct sockaddr *) &from, &fromlen);
       if (client < 0) 
         {
          perror("accept error"); exit(2);
         }
       while (1) 
          {
           memset(buf,0,1024);
           int s=read(client,buf,1024);
           if(s==0)
               break;  
           write(client,"server response: ",strlen("server response: "));
           write(client,buf,strlen(buf));
           write(1,inet_ntoa(from.sin_addr),strlen(inet_ntoa(from.sin_addr)));
           write(1," ",strlen(" "));
           write(1,buf,strlen(buf));
          }
       close(client);
      }
   return 0;
 }
