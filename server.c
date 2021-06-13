#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
  struct sockaddr_in sin ; // instantiation of structutre sockadd_in
  char msg[80];
  int s =socket(AF_INET,SOCK_STREAM ,0); // (domaine, protocloe, if we use more then one protocel )
  sin.sin_family = AF_INET;
  sin.sin_port = htons(atoi(argv[1])); // host to network short of network port
  sin.sin_addr.s_addr = htonl(INADDR_ANY);    // accept any addr from client
  int b = bind(s,(struct sockaddr *)&sin,sizeof(sin)); // bind the socket with adress and port ( to change sin to sockaddr)
  
  if(listen(s,5))
  {
    perror("listen");
    return -1;
  }

  int sinlen = sizeof(sin);
  while(1)
  {
    int ac = accept(s,(struct sockaddr *)&sin,&sinlen);
    read(ac,msg,sizeof(msg));
    write(ac,msg,strlen(msg));
    close(ac);
  }
  close(s); 
}
