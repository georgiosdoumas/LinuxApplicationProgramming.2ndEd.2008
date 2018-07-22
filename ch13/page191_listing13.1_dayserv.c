/* This is saved on a VirtualMachine I have built, that has IP 192.168.122.89
  and I then opened the firewall for port 13 */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#define MAX_BUFFER 128
#define DAYTIME_SERVER_PORT 13
#define MAX_PEND_CONN 3
int main ( void )
{
  int serverFd, connectionFd;
  struct sockaddr_in servaddr;
  char timebuffer[MAX_BUFFER+1];
  time_t currentTime;
  serverFd = socket( AF_INET, SOCK_STREAM, 0 );
  memset( &servaddr, 0, sizeof(servaddr) );
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY); /* listen to all incoming addresses */ 
  servaddr.sin_port = htons(DAYTIME_SERVER_PORT);
  bind( serverFd,(struct sockaddr *)&servaddr, sizeof(servaddr) );
  listen( serverFd, MAX_PEND_CONN );
  while ( 1 ) 
  {
    connectionFd = accept( serverFd,(struct sockaddr *)NULL, NULL );
    if (connectionFd >= 0 )  /* valid connection created? */
    {
       currentTime = time(NULL);
       snprintf( timebuffer, MAX_BUFFER, "%s\n", ctime(&currentTime) );
       write( connectionFd, timebuffer, strlen(timebuffer) );
       close( connectionFd );
    }
  }
}

/* gcc -Wall page191_listing13.1_dayserv.c -o page191_listing13.1_dayserv 
Run it as a background process so that it will not hold your terminal console : 
./page191_listing13.1_dayserv & */  
