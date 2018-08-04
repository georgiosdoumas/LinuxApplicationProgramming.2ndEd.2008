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
    printf(" where <length> is a positive integer < 256 (for bigger values we get segmentation fault! Why?)\n");
    printf(" and <offset-addr> must be in multiples of %d [0x%x in hex] bytes (can be 0)\n", localsystempagesize, localsystempagesize);
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
/* 
sudo ./page392_listing20.5_phymap 252 4096
 Finished with cmd-line arguments, offset is 4096 and length is 252 
   Lets check what mmap() function achieved : 
  mmap() call seems to succeeded and returned an address : 0x7f007198f000 

0x7f007198f000 : 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
0x7f007198f010 : 18 10 00 00 06 a1 ff ff 20 10 00 00 06 a1 ff ff 
0x7f007198f020 : 28 10 00 00 06 a1 ff ff 30 10 00 00 06 a1 ff ff 
0x7f007198f030 : 38 10 00 00 06 a1 ff ff 40 10 00 00 06 a1 ff ff 
0x7f007198f040 : 48 10 00 00 06 a1 ff ff 50 10 00 00 06 a1 ff ff 
0x7f007198f050 : 58 10 00 00 06 a1 ff ff 60 10 00 00 06 a1 ff ff 
0x7f007198f060 : 68 10 00 00 06 a1 ff ff 70 10 00 00 06 a1 ff ff 
0x7f007198f070 : 78 10 00 00 06 a1 ff ff 80 10 00 00 06 a1 ff ff 
0x7f007198f080 : 88 10 00 00 06 a1 ff ff 90 10 00 00 06 a1 ff ff 
0x7f007198f090 : 98 10 00 00 06 a1 ff ff a0 10 00 00 06 a1 ff ff 
0x7f007198f0a0 : a8 10 00 00 06 a1 ff ff b0 10 00 00 06 a1 ff ff 
0x7f007198f0b0 : b8 10 00 00 06 a1 ff ff c0 10 00 00 06 a1 ff ff 
0x7f007198f0c0 : c8 10 00 00 06 a1 ff ff d0 10 00 00 06 a1 ff ff 
0x7f007198f0d0 : d8 10 00 00 06 a1 ff ff e0 10 00 00 06 a1 ff ff 
0x7f007198f0e0 : e8 10 00 00 06 a1 ff ff f0 10 00 00 06 a1 ff ff 
0x7f007198f0f0 : f8 10 00 00 06 a1 ff ff 00 11 00 00    
Now we must not forget to unmap() ! 


sudo ./page392_listing20.5_phymap 30 0x3000
 Finished with cmd-line arguments, offset is 12288 and length is 30 
   Lets check what mmap() function achieved : 
  mmap() call seems to succeeded and returned an address : 0x7f583416c000 

0x7f583416c000 : 47 00 c0 e5 b3 c7 00 00 00 00 ff 0f 10 88 b4 c7 
0x7f583416c010 : 00 00 00 00 30 00 00 00 00 00 00 00 86 b8    
Now we must not forget to unmap() !
*/ 
