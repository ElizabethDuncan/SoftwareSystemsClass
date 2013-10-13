CC = gcc
CFLAGS = -Wall
WRAPPERS = wraplib.o wrapstdio.c wrapsock.o wrapunix.o error.o \
writen.c readline.c

tcpcli01:	tcpcli01.o str_cli08.o ${WRAPPERS}
		${CC} ${CFLAGS} -o $@ tcpcli01.o str_cli08.o ${WRAPPERS}

tcpserv01:	tcpserv01.o str_echo08.o 
		${CC} ${CFLAGS} -o $@ tcpserv01.o str_echo08.o ${WRAPPERS}

clean:
	rm *.o *~ tcpcli01 tcpserv01