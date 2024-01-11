#include "dgsocket.h"

/**
* dgsocket - Datagram socket
*
* Return: File descriptor on success -1 failure
*/
int dgsocket() {
    return (socket(AF_INET, SOCK_DGRAM, 0));
}

/**
* dgbind - Datagram bindng name to the socket
* 
* @sockfd: Socket file descriptor
* @addr: Addresse assinged to the socket
* @addrlen: Size of the addresse 
*
* Return: 0 on success -1 on failure
*/
int dgbind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    return (bind(sockfd, addr, addrlen));
}

/**
* dgsendto - Datagram send a message on a socket
* 
* @sockfd: Socket file descriptor
* @buf: Buffer of the send message
* @len: Length in bytes of the buffer
* @flags: Specifies the type of message transmission
* @dest_addr: Addresse of the target
* @addrlen: Size of dest_addr
*
* Return: Number of bytes send on success -1 on failure
*/
int dgsendto(int sockfd, const void *buf, size_t len, int flags , const struct sockaddr *dest_addr, socklen_t addrlen) {
    return (sendto(sockfd, buf, len, flags, dest_addr, addrlen));
}

/**
* dgrecvfrom - Datagram receive form a socket
* 
* @sockfd: Socket file descriptor
* @buf: Buffer of the received message
* @len: Length in bytes of the buffer
* @flags: Specifies the type of message reception
* @src_addr: Source addresse of the message
* @addrlen: Size of src_addr
*
* Return: Number of bytes received on success -1 on failure
*/
int dgrecvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen) {
    return (recvfrom(sockfd, buf, len, flags, src_addr, addrlen));
}

/**
* dgclose - Close a file descriptor
*
* @sockfd: Socket file descriptor
*
* Return: 0 on success -1 on failure
*/
int dgclose(int sockfd) {
    return (close(sockfd));
}