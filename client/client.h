#ifndef CLIENT_H
#define CLIENT_H

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
#include "../lib/dgsocket.h"

#define PORT 5050
#define MSGSIZE 256

void setup(void);
int get_ticket(void);
void app(void);
void release_ticket(void);
void destroy(void);

#endif /** CLIENT_H */