#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h>
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h>
#include <errno.h>  
#include <unistd.h>   //close  
#include <arpa/inet.h>    //close   
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros  
#define MAX 80 
#define PORT 9090 
#define SA struct sockaddr 
#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2
#define TRUE   1
#define FALSE  0  

static int getLine (char *prmpt, char *buff, size_t sz) {
    int ch, extra;

    // Get line with buffer overrun protection.
    if (prmpt != NULL) {
        printf ("%s", prmpt);
        fflush (stdout);
    }
    if (fgets (buff, sz, stdin) == NULL)
        return NO_INPUT;

    // If it was too long, there'll be no newline. In that case, we flush
    // to end of line so that excess doesn't affect the next call.
    if (buff[strlen(buff)-1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? TOO_LONG : OK;
    }

    // Otherwise remove newline and give string back to caller.
    buff[strlen(buff)-1] = '\0';
    return OK;
}

int main(int argc, char *argv[]) { 

    char buff[MAX]; 
	int n;
    int rc;

    while (TRUE)
    {
        rc = getLine ("Enter the image directory> ", buff, sizeof(buff));
        if (rc == NO_INPUT) {
            // Extra NL since my system doesn't output that on EOF.
            printf ("\nNo input\n");
            break;
        }

        if (rc == TOO_LONG) {
            printf ("Input too long [%s]\n", buff);
            break;
        }

        printf ("OK [%s]\n", buff);

        //Get Picture Size
        printf("Getting Picture Size\n");
        FILE *picture;
        // printf(buff);
        picture = fopen(buff, "r");
        if(!picture) {
            printf("ERROR: opening image\n");
            break;
        } 

        int size;
        fseek(picture, 0, SEEK_END);
        size = ftell(picture);
        fseek(picture, 0, SEEK_SET);

        int sockfd, connfd; 
        struct sockaddr_in servaddr, cli; 

        // socket create and varification 
        sockfd = socket(AF_INET, SOCK_STREAM, 0); 
        if (sockfd == -1) { 
            printf("socket creation failed...\n"); 
            exit(0); 
        } 
        else
            printf("Socket successfully created..\n"); 
        bzero(&servaddr, sizeof(servaddr)); 

        // assign IP, PORT 
        servaddr.sin_family = AF_INET; 
        servaddr.sin_addr.s_addr = inet_addr(argv[1]); 
        servaddr.sin_port = htons(PORT); 

        // connect the client socket to server socket 
        if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
            printf("connection with the server failed...\n"); 
            exit(0); 
        } 
        else
            printf("connected to the server..\n"); 

        //Send Picture Size
        printf("Sending Picture Size\n");
        write(sockfd, &size, sizeof(size));

        //Send Picture Name
        printf("Sending Picture Name\n");
        write(sockfd, buff, sizeof(buff));

        //Send Picture as Byte Array (without need of a buffer as large as the image file)
        printf("Sending Picture as Byte Array\n");
        char send_buffer[size]; // no link between BUFSIZE and the file size
        int nb = fread(send_buffer, 1, sizeof(send_buffer), picture);
        while(!feof(picture)) {
            write(sockfd, send_buffer, nb);
            nb = fread(send_buffer, 1, sizeof(send_buffer), picture);
            // no need to bzero
        }

        close(sockfd); 
    }
    
    return 0;

	// function for chat 
	// func(sockfd); 

	// close the socket 
}