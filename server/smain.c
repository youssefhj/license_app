#include "server.h"

/**
* main - Entry of the server
*
* Return: 0 on success
*/
int main(void) {

    setup(); // Build the session dependecies

    alarm(CHECK_TIME);
    signal(SIGALRM, update_tickets_box); // Check the accuracy of tickets box

    while (1) {
        process_request(); // Wait for incoming request and process it
    }

    destroy(); // End the session

}