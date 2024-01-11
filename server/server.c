#include "server.h"

/** Global variables */
int tickets[MAX_TICKET];
int ticket_in_use = 0;
int ssockfd;
int pid_client = 0;
struct sockaddr_in servaddr;
struct sockaddr_in cliaddr;

/**
* setup - Setup the socket
*/
void setup(void) {
    struct hostent *host_info;
    char shost[256]; // Buffer of the server host name

    if ((ssockfd = dgsocket()) < 0) {
        perror("[-] Server > dgsocket failed");
        exit(1);
    }

    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
    
    gethostname(shost, 256);

    // Get host information
    host_info = gethostbyname(shost);
    
    bcopy((void *)host_info->h_addr_list[0], (void *)&servaddr.sin_addr,  host_info->h_length);

    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    if (dgbind(ssockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("[-] Server > dgbind failed");
        exit(1);
    }

    // Empty the ticket box
    int ticket;
    for (ticket = 0 ; ticket < MAX_TICKET; ticket++)
        tickets[ticket] = 0;

    return;
}

/**
* narrate - Help to visualise the communication 
*           between the sever and the client
*
* @request: Message get by the server
* @reply: Response to the request message
*
*/
void narrate(char *request, char *reply) {
    
    printf("Server [FROM / TO] %d\n", pid_client);
    printf(">>> GET: %s\n", request);
    printf("<<< RPLY: %s\n\n", reply);
}

/**
* update_tickets_box - Check the accuracy of the tickets box
*
* @signum: Signal number
*
*/
void update_tickets_box(int signum) {
    int ticket;

    if (signum == SIGALRM) {
        alarm(0);
        
        for (ticket = 0; ticket < MAX_TICKET ; ticket++) {
            if (kill(tickets[ticket], 0) == -1) {
                tickets[ticket] = 0;
                ticket_in_use--;
            }
        }

        alarm(CHECK_TIME);
    }
}

/**
* process_hello - Process the < HELLO pid > message
*
* @request: The message sent by client
* 
* Return: The response message
*/
char *process_hello(char *request) {
    int ticket;
    char *response = (char *) malloc(MSGSIZE * sizeof(char));

    sscanf(request, "HELLO %d", &pid_client);
    for (ticket = 0; ticket < MAX_TICKET && ticket_in_use < MAX_TICKET; ticket++) {
        if (tickets[ticket] == 0) {
            tickets[ticket] = pid_client;
            ticket_in_use++;

            sprintf(response, "TICK %d.%d", pid_client, ticket);

            return (response);
        }
    }

    return ("FAIL");
}

/**
* process_bye - Process the < BYE pid.slot > message
*                 in the release situation
*
* @request: The message sent by client
*
* Return: The response message
*/
char *process_bye(char *request) {
    int slot;

    sscanf(request, "BYE %d.%d", &pid_client, &slot);
    if (tickets[slot] == pid_client) {
        tickets[slot] = 0;
        ticket_in_use--;

        return ("THNX");
    }

    return ("FAIL");
}

/**
* process_request - Process every incoming request
*/
void process_request(void) {

    char request[MSGSIZE];
    char *reply;
    socklen_t addrlen = sizeof(cliaddr);

    if (dgrecvfrom(ssockfd, request, MSGSIZE, 0, (struct sockaddr *) &cliaddr, &addrlen) < 0)
        perror("[-] Server > dgrecvfrom failed");


    if (!strncmp(request, "HELLO", 5))
        reply = process_hello(request);
    else if (!strncmp(request, "BYE", 3))
        reply = process_bye(request);
    else 
        perror("[-] Server > Unknown message");
    
    if (dgsendto(ssockfd, reply, MSGSIZE, 0, (struct sockaddr *) &cliaddr, sizeof(cliaddr)) < 0)
        perror("[-] Server > dgsendto failed");
    
    narrate(request, reply);
}

/**
* destroy - Destory the socket
*/
void destroy(void) {
    dgclose(ssockfd);
}