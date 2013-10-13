#include "trout.h"
#include "util.h"
#include "variables.h"

/* Global variables stated */
int max_ttl = 30;
int nprobes = 2;
int seq = 0;
char recvbuf[BUFSIZE];
char sendbuf[BUFSIZE];
Rec *rec = (Rec *) sendbuf;
int datalen = sizeof (Rec);
u_short dport = 32768 + 668; 

/* BEGIN MAIN */
int main (int argc, char **argv)
{
  int c;
  struct addrinfo *ai;
  char *host;

  opterr = 0;
  while ( (c = getopt (argc, argv, "m:")) != -1) {
    switch (c) {
    case 'm':
      if ( (max_ttl = atoi(optarg)) <= 1) {
	err_quit ("invalid -m value");
      }
      break;
    default:
      err_quit ("unrecognizd option: %c", c);
    }
  }

  if (optind != argc - 1) {
    err_quit ("usage: trout [ -m <maxttl>] <hostname>");
  }
  host = argv[optind];
  ai = Host_serv (host, NULL, 0, 0);

  printf ("trout to %s (%s): %d hops max, %d data bytes\n",
	  ai->ai_canonname,
	  Sock_ntop_host (ai->ai_addr, ai->ai_addrlen),
	  max_ttl, datalen);

  if (ai->ai_family != AF_INET) {
    err_quit ("unknown address family %d", ai->ai_family);
  }

/* Removed to compile cleanly will -Wall tag (unused variable) */
//  Sockaddr *sasend = ai->ai_addr;
//  Sockaddr *salen = ai->ai_addrlen;
//  Sockaddr *sarecv = Calloc (1, salen);
//  Sockaddr *salast = Calloc (1, salen);
//  Sockaddr *sabind = Calloc (1, salen);

  loop_ttl ();
  exit (0);
}
