#include <stdio.h>
#include <getopt.h>
static struct option longopts[] = {
  { "start", no_argument, NULL, 's' },
  { "stop", no_argument, NULL, 't' },
  { "command", required_argument, NULL, 'c' },
  { NULL, 0, NULL, 0 }
};

int main( int argc, char *argv[] )
{
  if (argc == 1) printf(" Usage:\n %s --start [-s] | --stop [-t] | --command [-c] <cmd-name> \n", argv[0]);
  int c;
  while ( (c = getopt_long( argc, argv, "stc:", longopts, NULL)) != -1 )
  {
    switch( c )
    {
      case 's':
        printf( "Start!\n" );
        break;
      case 't':
        printf( "Stop!\n" );
        break;
      case 'c':
        printf( "Command %s!\n", optarg );
        break;
      case '?':
      default:
        printf( "Unknown option\n");
        break;
    }
  }
  return 0;
}

/* gcc -Wall page384_listing20.2_optlong.c -o page384_listing20.2_optlong  */
