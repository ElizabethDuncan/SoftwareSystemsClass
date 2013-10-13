/* variables we might want to configure */
extern int max_ttl;
extern int nprobes;


/* other global variables */

extern int seq;
extern char recvbuf[BUFSIZE];
extern char sendbuf[BUFSIZE];

extern Rec *rec;

extern int sendfd, recvfd;
extern int pipefd[2];              /* the pipe for the alarm handler */

extern Sockaddr *sasend;    /* socket addresses for various purposes */
extern Sockaddr *sarecv;
extern Sockaddr *salast;
extern Sockaddr *sabind;

extern socklen_t salen;                    /* length of a socket address */
extern int datalen;         /* length of the data in a datagram */

extern u_short sport;                      /* source UDP port # */
extern u_short dport;        /* destination port -- hopefully unused */
                                    /* 668 = the neighbor of the beast */
extern Timeval sendtv[1];
extern Timeval recvtv[1];
extern Timeval difftv[1];
