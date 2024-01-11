#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <signal.h>
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <errno.h>
#include <netdb.h>
#include "../lib/dgsocket.h"

#define PORT 5050
#define MAX_TICKET 5
#define MSGSIZE 256
#define CHECK_TIME 5

void setup(void);
void narrate(char *, char *);
void update_tickets_box(int);
char *process_hello(char *);
char *process_bye(char *);
void process_request(void);
void destroy(void);

#endif /** SERVER_H */