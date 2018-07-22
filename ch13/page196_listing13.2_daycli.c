#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>  /* void *memset(void *s, int c, size_t n); */
#include <errno.h>
#include <stdlib.h>
#define MAX_BUFFER 128
#define DAYTIME_SERVER_PORT 13

int main (int argc, char* argv[])
{
  const char* target_ipaddr = "192.168.122.89" ; /* IP of my VirtualMachine on which the server executable runs */
  if(argc == 2) target_ipaddr = argv[1]; /* if user passes an IP as cmd-line argument, use that instead */
  int connectionFd, inpresult, index = 0, limit = MAX_BUFFER;
  struct sockaddr_in servaddr;
  char timebuffer[MAX_BUFFER+1];
  connectionFd = socket(AF_INET, SOCK_STREAM, 0);
  memset(&servaddr, 0, sizeof(servaddr)); /* fill the bytes of servaddr with 0'es */
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(DAYTIME_SERVER_PORT); /* Host-TO-Network-Short */
  servaddr.sin_addr.s_addr = inet_addr(target_ipaddr);
  if( connect(connectionFd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
  {
    printf("Failed to connect to %s , on port : %d, error number is %d\n", target_ipaddr, DAYTIME_SERVER_PORT, errno );
    exit(-1);
  }
  while ((inpresult=read(connectionFd, &timebuffer[index], limit)) > 0)
  {
    index += inpresult;
    limit -= inpresult;
  }
  timebuffer[index] = '\0';
  printf("\n%s\n", timebuffer);
  printf(" Closing socket connection.\n");
  close(connectionFd);
  return(0);
}

/* gcc -Wall page196_listing13.2_daycli.c -o page196_listing13.2_daycli 
Now run it under various circumstances like: 
1. Correct target IP and the server has the process of daytime running, and firewall is opened for port 13.
2. Correct target IP but the server has not the process of daytime running.
3. Correct target IP and the server has the process of daytime running, but firewall is not opened for port 13.
4. Wrong target IP passed through cmd-line , for example ./page196_listing13.2_daycli 192.168.122.88
For cases 2,3,4 different error numbers will appear. 
*/
