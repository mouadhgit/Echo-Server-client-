
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <netdb.h>


int main(int argc,char *argv[])
{
  struct sockaddr_in sin;
  struct hostent *hptr;
  char msg[80];
  int s = socket(AF_INET,SOCK_STREAM,0);
  sin.sin_family=AF_INET;
  sin.sin_port = htons(atoi(argv[2]));
  hptr=gethostbyname(argv[1]);

  memcpy(&sin.sin_addr,hptr->h_addr,hptr->h_length); 
  connect(s,(struct sockaddr *)&sin,sizeof(sin));

  printf("Enter the msg: ");
  gets(msg);

  write(s,msg,strlen(msg));
  bzero((char*)&msg,sizeof(msg));
  int n =read(s,msg,sizeof(msg));
  printf("%d bytes : %s \n",n,msg);
  close(s);

}