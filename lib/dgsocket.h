#ifndef DG_SOCKET_H
#define DG_SOCKET_H

/** This library has one object as following
*   Create, Binding, Send message, Receive message, Close the socket
*/

#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <errno.h>
#include <netdb.h>

int dgsocket(void);
int dgbind(int, const struct sockaddr *, socklen_t);
int dgsendto(int, const void *, size_t, int, const struct sockaddr *, socklen_t);
int dgrecvfrom(int, void *, size_t, int, struct sockaddr *, socklen_t *);
int dgclose(int);

#endif /** DG_SOCKET_H */