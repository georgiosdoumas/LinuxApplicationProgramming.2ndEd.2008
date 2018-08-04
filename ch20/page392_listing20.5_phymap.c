#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>
int main( int argc, char *argv[] )
{
  int fd, localsystempagesize = getpagesize();
  unsigned char *addr, *waddr, count;
  size_t length;
  off_t offset;
  if (argc < 3) {
    printf( "Usage is: \n %s <length> <offset-address> \n",argv[0]);
    printf(" where <offset-addr> must be in multiples of %d [0x%x in hex] bytes (can be 0)\n", localsystempagesize, localsystempagesize);
    exit(-1);
  }
  if (argv[2][1] == 'x')  {  /* the user gave as address an hex number like : 0xhexdigits */
    sscanf( argv[2], "0x%lx", &offset );
  }
  else {             /* the user gave as address a decimal number */
    sscanf( argv[2], "%ld", &offset );
  }
  if (argv[1][1] == 'x') {    /* the user gave as length an hex number */
    sscanf( argv[1], "0x%lx", &length );
  }
  else {
    sscanf( argv[1], "%ld", &length );
  }
  printf(" Finished with cmd-line arguments, offset is %ld and length is %ld \n", offset, length);
  if( (offset % localsystempagesize) != 0 ) {
    printf(" Your given offset-address was not a multiply of %d", localsystempagesize);
    printf(" \n so it will be ignored, and a value of 0 will be assumed.\n");
    offset = 0;
  }

  fd = open( "/dev/mem", O_RDONLY );
  if (fd != -1)
  {
    addr = (unsigned char *)mmap( NULL, length, PROT_READ, MAP_SHARED, fd, offset );
    if (addr != NULL)
    {
      printf( "  mmap() call seems to succeeded and returned an address : %p \n", addr);
      waddr = addr;
      for ( count = 0 ; count < length ; count++ )
      {
        if ( (count % 16) == 0 ) {
          printf( "\n%8p : ", waddr );
        }
        printf( "%02x ", *waddr++ );
      }
      printf("   \nNow we must not forget to unmap() ! \n");
      munmap( addr, length );
    }
    else {
      printf("Unable to map memory.\n");
    }
    close(fd);
    printf("\n");
  }
  else printf(" failed to open /dev/mem or some other error \n");
  return 0;
}

/* gcc -Wall -g page392_listing20.5_phymap.c -o page392_listing20.5_phymap */
