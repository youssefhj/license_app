#include "client.h"

/** Global variables */
int csockfd;
int has_ticket = 0;
struct sockaddr_in servaddr;
char ticket[MSGSIZE - 10];

/**
* setup - Setup the socket
*/
void setup(void) {
    struct hostent *host_info;
    char chost[256]; // Buffer of the client host name

    if ((csockfd = dgsocket()) < 0) {
        perror("[-] Client > dgsocket failed");
        exit(1);
    }

    memset(&servaddr, 0, sizeof(servaddr)); 

    gethostname(chost, 256);
    
    /** Get host information */
    host_info = gethostbyname(chost);

    bcopy((void *)host_info->h_addr_list[0], (void *)&servaddr.sin_addr,  host_info->h_length);

    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY;
    

    return;
}

/**
* get_ticket - Ask server for a ticket
*
* Return: 0 on success 1 on failure
*/
int get_ticket(void) {

    if (has_ticket == 1) 
        return (0);

    setup();

    char msg[MSGSIZE];

    sprintf(msg, "HELLO %d", getpid());
    if (dgsendto(csockfd, msg, MSGSIZE, 0, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        perror("[-] Client > dgsendto failed");
        exit(1);
    }

    char reply[MSGSIZE];
    socklen_t addrlen = sizeof(servaddr);

    if (dgrecvfrom(csockfd, reply, MSGSIZE, 0, (struct sockaddr *) &servaddr, &addrlen) < 0) {
        perror("[-] Client > dgrecvfrom failed");
        exit(1);
    }

    if (! strncmp("TICK", reply, 4)) {
        strcpy(ticket, reply + 5);
        has_ticket = 1;

        return (0);
    }

    if (! strncmp("FAIL", reply, 4))
        perror("[-] Client > Failed to get ticket from server");
    else
        perror("[-] Client > Unknow message");

    return (1);
}

/**
* app - Represente the main work 
*/
void app(void) {

    /**
    * In this block you can write
    * the goal of your app
    * whats this app provide to the client ?
    */
    sleep(10);
    printf("I finished execution.\n");
    printf("Time to release ticket.\n");

}

/**
* release_ticket - Return ticket to the server
*/
void release_ticket(void) {
    
    char msg[MSGSIZE];

    sprintf(msg, "BYE %s", ticket);
    if (dgsendto(csockfd, msg, MSGSIZE, 0, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        perror("[-] Client > dgsendto failed");
        exit(1);
    }

    char reply[MSGSIZE];
    socklen_t addrlen = sizeof(servaddr);

    if (dgrecvfrom(csockfd, reply, MSGSIZE, 0, (struct sockaddr *) &servaddr, &addrlen) < 0) {
        perror("[-] Client > dgrecvfrom failed");
        exit(1);
    }

    if (!strncmp(reply, "THNX", 4)) {
        puts("[+] Client > ticket released");
        has_ticket = 0;
    }
    else if (!strncmp(reply, "FAIL", 4))
        perror("[-] Client > Failed to release ticket");
    else
        perror("[-] Client > Unknown message !!");

    return;
}

/**
* destroy - Destory the socket
*/
void destroy(void) {
    dgclose(csockfd);
}