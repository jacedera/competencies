/*
 * ccomp2.c
 *	Simple chat server that can be connected to via nc.
 *	All this does is echo back what the client sends.
 *  Created on: May 4, 2017
 *      Author: jacedera
 */

// sys includes
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> // for close()
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h> // needed for sockaddr_in and in_addr structs

// usr includes
#include "ccomp2.h"

// defines
#define RETURN_ERROR -1
#define SOCKET_REUSABLE 1
#define EXIT_TRUE 1
#define EXIT_FALSE 0
#define RECV_LEN 1024
#define RECV_ERROR -1

// "./Comp2.o <ipaddr> <socket>
int main(int argc, char ** argv){

	// declares
	int iServSockFD = 0;				// the server socket file descriptor
	int iClientSockFD = 0;				// the client socket file descriptor
	unsigned short iPort = 0;			// the port number to bind to
	int bReusable = SOCKET_REUSABLE;	// to make the socket reusable
	//int bExit = EXIT_FALSE;				// the exit condition for the recv while-loop
	char * buf = NULL;					// the character buffer containing the received string
	char * fullBuf = NULL;				// the character buffer containing the entire string
	char * reply = NULL;				// reply to send to the client
	char * newLine = NULL;				// temp loc to store newline char address
	unsigned int iBytesRecv = 0;		// number of bytes received over the socket
	unsigned int iBytesSent = 0;		// number of bytes sent over the socket
	unsigned int iFullSize = 0;			// size of the buffer containing the entire string
	unsigned int iNumMesg = 0;			// number of 1024-byte messages received
	int bExit = EXIT_FALSE;				// exit condition


	// ip stuff, declare and nullify
	struct sockaddr_in ServerAddr = {0};	// the server address struct
	struct sockaddr_in ClientAddr = {0};	// the client address struct
	struct in_addr ServerIP = {0};			// the server IP address
	unsigned int AddrLen = 0;				// size of the sockaddr_in struct, used for accept()

	// print usage if incorrect num args is passed in
	if(argc != 3){
		printUsage(argv[0]);
		return RETURN_ERROR;
	}

	// populate the port number
	iPort = atoi(argv[2]);

	/*	Note on struct usage:
	 *  struct sockaddr_in {
     *   	sa_family_t		sin_family; 	// address family: AF_INET
     *      in_port_t		sin_port;  		// port in network byte order
     *      struct in_addr	sin_addr;   	// internet address
	 *	};
	 *
     *  struct in_addr {
     *      uint32_t		s_addr;     	// address in network byte order
     *  };
	 */

	// populate the server address struct
	if(inet_pton(AF_INET, argv[1], &ServerIP) == RETURN_ERROR){
		printf("Error in server address format. Exiting...\n");
		return RETURN_ERROR;
	}
	ServerAddr.sin_family =	AF_INET;
	ServerAddr.sin_port =	htons(iPort);
	ServerAddr.sin_addr =	ServerIP;

	// create a reusable socket and bind the socket object
	iServSockFD = socket(AF_INET, SOCK_STREAM, 0);
	if(iServSockFD == RETURN_ERROR){
		printf("Socket creation failure: %d. Exiting...\n", errno);
		return RETURN_ERROR;
	} else printf("Socket created...\n");

	if(setsockopt(iServSockFD, SOL_SOCKET, SO_REUSEADDR, &bReusable, sizeof(int)) == RETURN_ERROR){
		printf("Error creating reusable socket. Exiting...\n");
		return RETURN_ERROR;
	} else printf("Socket has been set to be reusable...\n");

	if(bind(iServSockFD, (struct sockaddr *)&ServerAddr, sizeof(struct sockaddr_in)) == RETURN_ERROR){
		printf("Error binding socket to address: %d. Exiting...\n", errno);
		return RETURN_ERROR;
	} else printf("Socket has been bound to address %s on port %d.\n", argv[1], iPort);

	// listen on the socket for any incoming connections and accept them
	if(listen(iServSockFD, 1) == RETURN_ERROR){
		printf("Error listening on socket. Exiting...\n");
		return RETURN_ERROR;
	} else printf("Listening on socket...\n");

	// accept the connection
	iClientSockFD = accept(iServSockFD, (struct sockaddr *)&ClientAddr, &AddrLen);
	if(iClientSockFD == RETURN_ERROR){
		printf("Error accepting on socket. Exiting...\n");
		return RETURN_ERROR;
	} else printf("Connected to remote user on socket...\n");

	// By this point we have created a reusable socket on a user-defined
	// ip address and port number.
	// Next step is to recv on the socket and reply
	// with the same message back to the client.

	// allocate the space for buffers
	buf = (char *)calloc(sizeof(char), RECV_LEN);
	if(!buf){
		printf("Error allocating space for temporary buffer. Exiting...\n");
		return RETURN_ERROR;
	}
	fullBuf = (char *)calloc(sizeof(char), RECV_LEN);
	if(!fullBuf){
		printf("Error allocating space for message buffer. Exiting...\n");
		free(buf);
		return RETURN_ERROR;
	}

	// recv() uses the socket file descr returned from accept() !!
	if(recv(iClientSockFD, buf, RECV_LEN, MSG_PEEK) == RETURN_ERROR){
		printf("Recv error: %d\n", errno);
		free(buf);
		return errno;
	}

	while(1){
		iFullSize = 0;
		iBytesRecv = recv(iClientSockFD, buf, RECV_LEN, 0);

		if(iBytesRecv == RETURN_ERROR){
			printf("Error on recv: %d\n", errno);
			continue;
		}




		// remove the newline and null-terminate the buffer
		/// TODO: on an abnormally large buffer newLine will be 0 because
		/// \n isn't found in buf. This will cause a segfault.
		newLine = strchr(buf, '\n');
		*newLine = '\0';

		printf("Recv: %s\n", buf);

		strcpy(fullBuf, "echo: ");
		strcat(fullBuf, buf);
		strcat(fullBuf, "\n");
		// create and send the reply buffer
		//reply = (char *)calloc(sizeof(char), 8 + iFullSize);
		//strcpy(reply, "reply: ");
		iBytesSent = send(iClientSockFD, fullBuf, strlen(fullBuf), 0);
		if(iBytesSent == RETURN_ERROR){
			printf("Error on send: %d\n", errno);
		}
		else{
			printf("Sent message: %s", fullBuf);
			printf("Bytes sent: %d\n", iBytesSent);
		}
	} // while socket still open



} // main

/// printUsage
/// \brief Prints the correct usage of the program.
/// \param name The name of the program.
void printUsage(char * name){
	printf("### Incorrect number of arguments.\n");
	printf("### Program usage: %s <ipaddr> <port>\n", name);
	return;
} // printUsage

// TODO: Edit this to recv instead of take user input.
// There is no cheating in CNO!
/// getUserInput
/// \brief Obtains a string of potentially infinite length from the user.
/// \param ofInput The input source, usually stdin because laziness.
/// \param iSize Starting size of the input string.
/// \return A pointer to the string containing user input
char * getUserInput(FILE * ofInput, size_t iSize){

	// declares
	char * szStr = NULL;	// the output string
	int iCh = 0;			// temp storage of char
	size_t len = 0;			// running length counter for output string

	// allocate the new string, return null on error
	szStr = realloc(NULL, sizeof(char)*iSize); // size is start size
	if(!szStr) return szStr;

	while(EOF != (iCh = fgetc(ofInput)) && iCh != '\n'){
		szStr[len++] = iCh;
		if(len == iSize){
			szStr = realloc(szStr, sizeof(char)*(iSize+=16));
			if(!szStr)return szStr;
		}
	} // while

	szStr[len++] = '\0';

	return realloc(szStr, sizeof(char)*len);
} // getUserInput
