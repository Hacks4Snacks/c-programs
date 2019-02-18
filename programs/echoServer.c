#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <getopt.h>
#include <arpa/inet.h>

#define BUFSIZE 5041

#define USAGE                                                                 \
"usage:\n"                                                                    \
"  echoserver [options]\n"                                                    \
"options:\n"                                                                  \
"  -p                  Port (Default: 50419)\n"                                \
"  -m                  Maximum pending connections (default: 1)\n"            \
"  -h                  Show this help message\n"                              \

/* OPTIONS DESCRIPTOR ====================================================== */
static struct option gLongOptions[] = {
  {"port",          required_argument,      NULL,           'p'},
  {"maxnpending",   required_argument,      NULL,           'm'},
  {"help",          no_argument,            NULL,           'h'},
  {NULL,            0,                      NULL,             0}
};


int main(int argc, char **argv) {
  int option_char;
  int portno = 50419; /* port to listen on */
  int maxnpending = 1;
  
  // Parse and set command line arguments
  while ((option_char = getopt_long(argc, argv, "p:m:hx", gLongOptions, NULL)) != -1) {
   switch (option_char) {
      case 'p': // listen-port
        portno = atoi(optarg);
        break;                                        
      default:
        fprintf(stderr, "%s ", USAGE);
        exit(1);
      case 'm': // server
        maxnpending = atoi(optarg);
        break; 
      case 'h': // help
        fprintf(stdout, "%s ", USAGE);
        exit(0);
        break;
    }
  }

    setbuf(stdout, NULL); // disable buffering

    if ((portno < 1025) || (portno > 65535)) {
        fprintf(stderr, "%s @ %d: invalid port number (%d)\n", __FILE__, __LINE__, portno);
        exit(1);
    }
    if (maxnpending < 1) {
        fprintf(stderr, "%s @ %d: invalid pending count (%d)\n", __FILE__, __LINE__, maxnpending);
        exit(1);
    }


  /* Socket Code Here */
    /* socket address for server
     * memset: set sin_zero to all zeros */
    struct sockaddr_in serverAddress;
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;

	/* htons: host to network short
	 * htonl: host to network long */
	serverAddress.sin_port = htons(portno);
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

	/* create a TCP socket, creation returns -1 on failure
	 * set socketoption to allow reusing port on an open connection */
	int listenSocket;
	int reuseSocket = 1;
	if ((listenSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("ERROR: Could not open socket for listening.\n");
		return 1;
	}

        if (setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, &reuseSocket, sizeof(reuseSocket)) < 0) {
            perror("ERROR: Could not resuse open port.");
	    return 1;
	}

	/* bind it to listen to the incoming connections on the created server
	 * address, will return -1 on error */
	if (bind(listenSocket, (struct sockaddr *)&serverAddress,
	          sizeof(serverAddress)) < 0) {
		perror("ERROR: Could not bind socket.\n");
		return 1;
	}
        /* max number of clients in waiting pool */
        int clientPool = 10;
        if (listen(listenSocket, clientPool) < 0) {
                perror("ERROR: Could not open socket for listening.\n");
                return 1;
        }

	/* socket address for client address */
	struct sockaddr_in clientAddress;
	unsigned int clientAddressLength = 0;

	/* keep echo server alive and listening for echo clients */
	for (;;) {
		/* one socket per data connection */
		int newSocket;
		if ((newSocket =
		          accept(listenSocket, (struct sockaddr *)&clientAddress, &clientAddressLength)) < 0) {
			perror("ERROR: Could not read from socket.\n");
			return 1;
		}

		int conn = 0;
		int len = 0; 
		int maxlen = 100;
		char buffer[maxlen];
		char *pbuffer = buffer;

		/* run as long as client connection is open */
		while ((conn = recv(newSocket, pbuffer, maxlen, 0)) > 0) {
			pbuffer += conn;
			maxlen -= conn;
			len += conn;

			/* send recieved data back to client */
			send(newSocket, buffer, len, 0);
		}
                /* data returned, close socket */
		close(newSocket);
	}

	close(listenSocket);
	return 0;
}
