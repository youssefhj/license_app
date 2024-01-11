#include "client.h"

/**
* main - Entry of the client
*
* Return: 0 on success
*/
int main(void) {
    if (get_ticket()) // Ask server for ticket to use the app
        return (1);

    app(); // The main app

    release_ticket(); // Return ticket to server

    destroy(); // End the session
    
    return (0);
}