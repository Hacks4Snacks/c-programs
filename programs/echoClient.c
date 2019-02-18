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

/* Be prepared accept a response of this length */
#define BUFSIZE 5041

#define USAGE                                                                       \
    "usage:\n"                                                                      \
    "  echoclient [options]\n"                                                      \
    "options:\n"                                                                    \
    "  -s                  Server (Default: localhost)\n"                           \
    "  -p                  Port (Default: 50419)\n"                                  \
    "  -m                  Message to send to server (Default: \"hello world.\")\n" \
    "  -h                  Show this help message\n"

/* OPTIONS DESCRIPTOR ====================================================== */
static struct option gLongOptions[] = {
    {"server", required_argument, NULL, 's'},
    {"port", required_argument, NULL, 'p'},
    {"message", required_argument, NULL, 'm'},
    {"help", no_argument, NULL, 'h'},
    {NULL, 0, NULL, 0}};

/* Main ========================================================= */
int main(int argc, char **argv)
{
    int option_char = 0;
    char *hostname = "localhost";
    unsigned short portno = 50419;
    char *message = "Hello World!!";

    // Parse and set command line arguments
    while ((option_char = getopt_long(argc, argv, "s:p:m:hx", gLongOptions, NULL)) != -1)
    {
        switch (option_char)
        {
        case 's': // server
            hostname = optarg;
            break;
        case 'p': // listen-port
            portno = atoi(optarg);
            break;
        default:
            fprintf(stderr, "%s", USAGE);
            exit(1);
        case 'm': // message
            message = optarg;
            break;
        case 'h': // help
            fprintf(stdout, "%s", USAGE);
            exit(0);
            break;
        }
    }

    setbuf(stdout, NULL); // disable buffering

    if ((portno < 1025) || (portno > 65535))
    {
        fprintf(stderr, "%s @ %d: invalid port number (%d)\n", __FILE__, __LINE__, portno);
        exit(1);
    }

    if (NULL == message)
    {
        fprintf(stderr, "%s @ %d: invalid message\n", __FILE__, __LINE__);
        exit(1);
    }

    if (NULL == hostname)
    {
        fprintf(stderr, "%s @ %d: invalid host name\n", __FILE__, __LINE__);
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

    /* open socket and establish TCP connection with echo server */
    int socketN;
        if ((socketN = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
		perror("ERROR: Unable to create socket.\n");
		return 1;
	}
    if (connect(socketN, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0 ) {
	    perror("ERROR: Unable to connect to echo server");
	    return 1;
    }

    /* data to be sent to the echo server */
    send(socketN, message, strlen(message), 0);

    int conn = 0;
    int len = 0;
    int maxlen = 100;
    char buffer[maxlen];
    char* pbuffer = buffer;

    if ((conn = recv(socketN, pbuffer, maxlen, 0)) > 0 ) {
		    pbuffer += conn;
		    maxlen -= conn;
		    len += conn;
                    buffer[len] = '\0';
		    printf("%s", buffer);
    }

    close(socketN);
    return 0;
}
