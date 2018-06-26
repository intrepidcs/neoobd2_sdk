/*
 * Copyright (c) 2017, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <stddef.h>
#include <sys/types.h>

#include <ti/net/bsd/errnoutil.h>
#include <ti/net/slnetsock.h>

#ifdef    __cplusplus
extern "C" {
#endif

/*!
    \defgroup BSD_Socket
    \short Controls standard client/server sockets programming options and capabilities

*/
/*!

    \addtogroup BSD_Socket
    @{
*/

/* Socket structures */
#define socklen_t                           SlNetSocklen_t
#define sockaddr                            SlNetSock_Addr_t

/* must match type of _SlNetSock_Addr_t's sa_family field */
typedef uint16_t sa_family_t;

/* ss_family + pad must be large enough to hold max of
 * _SlNetSock_AddrIn6_t or _SlNetSock_AddrIn_t
 */
struct sockaddr_storage {
    sa_family_t   ss_family;
    uint8_t       pad[26];
};

/* Socket opts */
#define SOCK_STREAM                         SLNETSOCK_SOCK_STREAM
#define SOCK_DGRAM                          SLNETSOCK_SOCK_DGRAM
#define SOCK_RAW                            SLNETSOCK_SOCK_RAW
#define AF_UNSPEC                           SLNETSOCK_AF_UNSPEC
#define AF_INET                             SLNETSOCK_AF_INET
#define AF_INET6                            SLNETSOCK_AF_INET6
#define AF_RF                               SLNETSOCK_AF_RF
#define AF_PACKET                           SLNETSOCK_AF_PACKET
#define PF_UNSPEC                           SLNETSOCK_PF_UNSPEC
#define PF_INET                             SLNETSOCK_PF_INET
#define PF_INET6                            SLNETSOCK_PF_INET6
#define SOL_SOCKET                          SLNETSOCK_LVL_SOCKET
#define SO_KEEPALIVE                        SLNETSOCK_OPSOCK_KEEPALIVE
#define SO_KEEPALIVETIME                    SLNETSOCK_OPSOCK_KEEPALIVE_TIME
#define SO_LINGER                           SLNETSOCK_OPSOCK_LINGER
#define SO_RX_NO_IP_BOUNDARY                SLNETSOCK_OPSOCK_NON_IP_BOUNDARY
#define SO_RCVTIMEO                         SLNETSOCK_OPSOCK_RCV_TIMEO
#define SO_RCVBUF                           SLNETSOCK_OPSOCK_RCV_BUF
#define SO_NONBLOCKING                      SLNETSOCK_OPSOCK_NON_BLOCKING
#define MSG_OOB                             SLNETSOCK_MSG_OOB
#define MSG_PEEK                            SLNETSOCK_MSG_PEEK
#define MSG_WAITALL                         SLNETSOCK_MSG_WAITALL
#define MSG_DONTWAIT                        SLNETSOCK_MSG_DONTWAIT
#define MSG_DONTROUTE                       SLNETSOCK_MSG_DONTROUTE
#define MSG_NOSIGNAL                        SLNETSOCK_MSG_NOSIGNAL
#define SO_BROADCAST                        (200)
#define SO_REUSEADDR                        (201)
#define SO_SNDBUF                           (202)
#define TCP_NODELAY                         (203)


/* Socket shutdown opt */
#define SHUT_RD                             SLNETSOCK_SHUT_RD
#define SHUT_WR                             SLNETSOCK_SHUT_WR
#define SHUT_RDWR                           SLNETSOCK_SHUT_RDWR

/*****************************************************************************/
/* Function prototypes                                                       */
/*****************************************************************************/
/*!

    \brief Create an endpoint for communication

    The socket function creates a new socket of a certain socket type, identified
    by an integer number, and allocates system resources to it.\n
    This function is called by the application layer to obtain a socket handle.

    \param[in] Domain           Specifies the protocol family of the created socket.
                                For example:
                                   - AF_INET for network protocol IPv4
                                   - AF_INET6 for network protocol IPv6

    \param[in] Type              specifies the communication semantic, one of:
                                   - SOCK_STREAM (reliable stream-oriented service or Stream Sockets)
                                   - SOCK_DGRAM (datagram service or Datagram Sockets)
                                   - SOCK_RAW (raw protocols atop the network layer)

    \param[in] Protocol         specifies a particular transport to be used with
                                the socket. \n
                                The most common are
                                    - IPPROTO_TCP
                                    - IPPROTO_UDP
                                The value 0 may be used to select a default
                                protocol from the selected domain and type

    \return                     On success, socket handle that is used for consequent socket operations. \n
                                A successful return code should be a positive number (int16)\n
                                On error, a negative value will be returned specifying the error code.
                                   - EAFNOSUPPORT  - illegal domain parameter
                                   - EPROTOTYPE  - illegal type parameter
                                   - EACCES   - permission denied
                                   - ENSOCK  - exceeded maximal number of socket
                                   - ENOMEM  - memory allocation error
                                   - EINVAL  - error in socket configuration
                                   - EPROTONOSUPPORT  - illegal protocol parameter
                                   - EOPNOTSUPP  - illegal combination of protocol and type parameters

    \sa                         close
    \note                       belongs to \ref basic_api
    \warning
*/
int socket(int Domain, int Type, int Protocol);

/*!
    \brief Gracefully close socket

    This function causes the system to release resources allocated to a socket.  \n
    In case of TCP, the connection is terminated.

    \param[in] fd               Socket handle (received in socket)

    \return                     Zero on success, or negative error code on failure

    \sa                         socket
    \note                       belongs to \ref ext_api
    \warning
*/
static inline int close(int fd)
{
    int RetVal = (int16_t)SlNetSock_close((int16_t)fd);
    return ErrnoUtil_set(RetVal);
}

/*!
    \brief Shutting down parts of a full-duplex connection

    The shutdown Shuts down parts of a full-duplex connection according to how parameter.\n

    \param[in] fd               Socket handle (received in SlNetSock_create)
    \param[in] how              Specifies which part of a full-duplex connection to shutdown. \n
                                The options are
                                    - SHUT_RD   - further receptions will be disallowed
                                    - SHUT_WR   - further transmissions will be disallowed
                                    - SHUT_RDWR - further receptions and transmissions will be disallowed

    \return                     Zero on success, or negative error code on failure

    \sa                         SlNetSock_create SlNetSock_connect SlNetSock_accept
    \note
    \warning
*/
int shutdown(int fd, int how);


/*!
    \brief Accept a connection on a socket

    This function is used with connection-based socket types (SOCK_STREAM).\n
    It extracts the first connection request on the queue of pending
    connections, creates a new connected socket, and returns a new file
    descriptor referring to that socket.\n
    The newly created socket is not in the listening state. The
    original socket fd is unaffected by this call. \n
    The argument fd is a socket that has been created with
    socket(), bound to a local address with bind(), and is
    listening for connections after a listen(). The argument \b
    \e addr is a pointer to a sockaddr structure. This structure
    is filled in with the address of the peer socket, as known to
    the communications layer. The exact format of the address
    returned addr is determined by the socket's address family. \n
    The \b \e addrlen argument is a value-result argument: it
    should initially contain the size of the structure pointed to
    by addr, on return it will contain the actual length (in
    bytes) of the address returned.

    \param[in]  fd              Socket descriptor (handle)
    \param[out] addr            The argument addr is a pointer
                                to a sockaddr structure. This
                                structure is filled in with the
                                address of the peer socket, as
                                known to the communications
                                layer. The exact format of the
                                address returned addr is
                                determined by the socket's
                                address\n
                                sockaddr:\n - code for the
                                address format.\n -
                                socket address, the length
                                depends on the code format
    \param[out] addrlen         The addrlen argument is a value-result
                                argument: it should initially contain the
                                size of the structure pointed to by addr

    \return                     On success, a socket handle.\n
                                On a non-blocking accept a possible retrun is -1 and errno is set to EAGAIN.\n
                                On failure, errno is set and -1 is returned.\n
                                ENOMEM may be return in case there are no resources in the system
                                In this case try again later or increase MAX_CONCURRENT_ACTIONS.

    \sa                         socket  bind  listen
    \note                       Belongs to \ref server_side
    \warning
*/
int accept(int fd, struct sockaddr *addr, socklen_t *addrlen);

/*!
    \brief Assign a name to a socket

    This function gives the socket the local address addr.
    addr is addrlen bytes long. Traditionally, this is called
    When a socket is created with socket, it exists in a name
    space (address family) but has no name assigned.
    It is necessary to assign a local address before a SOCK_STREAM
    socket may receive connections.

    \param[in] fd               Socket descriptor (handle)
    \param[in] addr             Specifies the destination
                                addrs\n sockaddr:\n - code for
                                the address format.\n - socket address,
                                the length depends on the code
                                format.
    \param[in] addrlen          Contains the size of the structure pointed to by addr

    \return                     Zero on success, or -1 on failure and sets errno to the corresponding BDS error code.

    \sa                         socket  accept listen
    \note                       belongs to \ref basic_api
    \warning
*/
int bind(int fd, const struct sockaddr *addr, socklen_t addrlen);

/*!
    \brief Listen for connections on a socket

    The willingness to accept incoming connections and a queue
    limit for incoming connections are specified with listen(),
    and then the connections are accepted with accept.
    The listen() call applies only to sockets of type SOCK_STREAM
    The backlog parameter defines the maximum length the queue of
    pending connections may grow to.

    \param[in] fd               Socket descriptor (handle)
    \param[in] backlog          Specifies the listen queue depth.


    \return                     Zero on success, or -1 on failure and sets errno to the corresponding BDS error code.

    \sa                         socket  accept  bind
    \note                       Belongs to \ref server_side
    \warning
*/
int listen(int fd, int backlog);

/*!
    \brief Initiate a connection on a socket

    Function connects the socket referred to by the socket
    descriptor fd, to the address specified by addr. The addrlen
    argument specifies the size of addr. The format of the
    address in addr is determined by the address space of the
    socket. If it is of type SOCK_DGRAM, this call specifies the
    peer with which the socket is to be associated; this address
    is that to which datagrams are to be sent, and the only
    address from which datagrams are to be received.  If the
    socket is of type SOCK_STREAM, this call attempts to make a
    connection to another socket. The other socket is specified
    by address, which is an address in the communications space
    of the socket.


    \param[in] fd               Socket descriptor (handle)
    \param[in] addr             Specifies the destination addr\n
                                sockaddr:\n - code for the
                                address format.\n -
                                socket address, the length
                                depends on the code format

    \param[in] addrlen          Contains the size of the structure pointed
                                to by addr

    \return                     On success, a socket handle.\n
                                On a non-blocking connect a possible negative value is EALREADY.
                                On failure, -1 is returned and sets errno to the corresponding BDS error code.\n
                                ENOMEM may be return in case there are no resources in the system
                                In this case try again later or increase MAX_CONCURRENT_ACTIONS

    \sa                         socket
    \note                       belongs to \ref client_side
    \warning
*/
int connect(int fd, const struct sockaddr *addr, socklen_t addrlen);

/*!
    \brief Return address info about the remote side of the connection

    The getpeername() system call returns the name of the peer connected to
    socket. The addrlen argument should be initialized to indicate the
    amount of space pointed to by name.  On return it contains the actual
    size of the name returned (in bytes).  The name is truncated if the
    buffer provided is too small.

    \param[in]  fd              Socket descriptor (handle)
    \param[out] addr            returns the struct addr\n
                                SlNetSockAddrIn filled with information
                                about the peer device:\n - code for the
                                address format.\n -
                                socket address, the length
                                depends on the code format
    \param[out] addrlen         Contains the size of the structure pointed
                                to by addr

    \return                     Zero on success, or negative error code on failure

    \sa                         accept    connect
    \note
    \warning
*/
int getpeername(int fd, struct sockaddr *addr, socklen_t *addrlen);



/*!
    \brief Returns the current name for    the specified socket

    The getsockname() system call returns the current name for the specified
    socket.  The namelen argument should be initialized to indicate the
    amount of space pointed to by name.  On return it contains the actual
    size of the name returned (in bytes).

    \param[in]  fd              Socket descriptor (handle)
    \param[out] addr            returns the struct addr\n
                                SlNetSockAddrIn filled with information
                                about the peer device:\n - code for the
                                address format.\n -
                                socket address, the length
                                depends on the code format
    \param[out] addrlen         Contains the size of the structure pointed
                                to by addr

    \return                     Zero on success, or negative error code on failure

    \sa                         accept    connect
    \note
    \warning
*/
int getsockname(int fd, struct sockaddr *addr, socklen_t *addrlen);

/*!
    \brief Set socket options-

    This function manipulate the options associated with a socket.\n
    Options may exist at multiple protocol levels; they are always
    present at the uppermost socket level.\n

    When manipulating socket options the level at which the option resides
    and the name of the option must be specified.  To manipulate options at
    the socket level, level is specified as SOL_SOCKET.  To manipulate
    options at any other level the protocol number of the appropriate
    protocol controlling the option is supplied.  For example, to indicate
    that an option is to be interpreted by the TCP protocol, level should be
    set to the protocol number of TCP; \n

    The parameters optval and optlen are used to access optvalues for
    setsockopt().  For getsockopt() they identify a buffer in which the value
    for the requested option(s) are to be returned.  For getsockopt(), optlen
    is a value-result parameter, initially containing the size of the buffer
    pointed to by option_value, and modified on return to indicate the actual
    size of the value returned.  If no option value is to be supplied or
    returned, option_value may be NULL.

    \param[in] fd               Socket handle
    \param[in] level            Defines the protocol level for this option
                                - <b>SOL_SOCKET</b>   Socket level configurations (L4, transport layer)
                                - <b>IPPROTO_IP</b>   IP level configurations (L3, network layer)
    \param[in] optname          Defines the option name to interrogate
                                - <b>SOL_SOCKET</b>
                                  - <b>SO_KEEPALIVE</b>  \n
                                                 Enable/Disable periodic keep alive.
                                                 Keeps TCP connections active by enabling the periodic transmission of messages \n
                                                 Timeout is 5 minutes.\n
                                                 Default: Enabled \n
                                                 This options takes SlSockKeepalive_t struct as parameter
                                  - <b>SO_KEEPALIVETIME</b>  \n
                                                 Set keep alive timeout.
                                                 Value is in seconds \n
                                                 Default: 5 minutes \n
                                  - <b>SO_RX_NO_IP_BOUNDARY</b>  \n
                                                 Enable/Disable rx ip boundary.
                                                 In connectionless socket (udp/raw), unread data is dropped (when recvfrom len parameter < data size), Enable this option in order to read the left data on the next recvfrom iteration
                                                 Default: Disabled, IP boundary kept,  \n
                                                 This options takes SlSockRxNoIpBoundary_t struct as parameter
                                  - <b>SO_RCVTIMEO</b>  \n
                                                 Sets the timeout value that specifies the maximum amount of time an input function waits until it completes. \n
                                                 Default: No timeout \n
                                                 This options takes SlTimeval_t struct as parameter
                                  - <b>SO_RCVBUF</b>  \n
                                                 Sets tcp max recv window size. \n
                                                 This options takes SlSockWinsize_t struct as parameter
                                  - <b>SO_NONBLOCKING</b> \n
                                                 Sets socket to non-blocking operation Impacts: connect, accept, send, sendto, recv and recvfrom. \n
                                                 Default: Blocking.
                                                 This options takes SlSockNonblocking_t struct as parameter
                                - <b>IPPROTO_IP</b>
                                  - <b>IP_MULTICAST_TTL</b> \n
                                                 Set the time-to-live value of outgoing multicast packets for this socket. \n
                                                 This options takes <b>_u8</b> as parameter
                                  - <b>IP_ADD_MEMBERSHIP</b> \n
                                                 UDP socket, Join a multicast group. \n
                                                 This options takes SlSockIpMreq_t struct as parameter
                                  - <b>IP_DROP_MEMBERSHIP</b> \n
                                                 UDP socket, Leave a multicast group \n
                                                 This options takes SlSockIpMreq_t struct as parameter
                                  - <b>SO_LINGER</b> \n
                                                 Socket lingers on close pending remaining send/receive packetst\n


    \param[in] optval           Specifies a value for the option
    \param[in] optlen           Specifies the length of the
        option value

    \return                     Zero on success, or -1 on failure and sets errno to the corresponding BDS error code.

    \par Persistent
            All params are <b>Non- Persistent</b>
    \sa     getsockopt
    \note   Belongs to \ref basic_api
    \warning

*/
int setsockopt(int fd, int level, int optname, const void *optval, socklen_t optlen);


/*!
    \brief Get socket options

    This function manipulate the options associated with a socket.
    Options may exist at multiple protocol levels; they are always present at
    the uppermost socket level.\n

    When manipulating socket options the level at which the option resides
    and the name of the option must be specified.  To manipulate options at
    the socket level, level is specified as SOL_SOCKET.  To manipulate
    options at any other level the protocol number of the appropriate
    protocol controlling the option is supplied.  For example, to indicate
    that an option is to be interpreted by the TCP protocol, level should be
    set to the protocol number of TCP; \n

    The parameters optval and optlen are used to access optvalues for
    setsockopt().  For getsockopt() they identify a buffer in which the value
    for the requested option(s) are to be returned.  For getsockopt(), optlen
    is a value-result parameter, initially containing the size of the buffer
    pointed to by option_value, and modified on return to indicate the actual
    size of the value returned.  If no option value is to be supplied or
    returned, option_value may be NULL.


    \param[in]  fd              Socket handle
    \param[in]  level           Defines the protocol level for this option
    \param[in]  optname         defines the option name to interrogate
    \param[out] optval          Specifies a value for the option
    \param[out] optlen          Specifies the length of the
                                option value

    \return                     Zero on success, or -1 on failure and sets errno to the corresponding BDS error code.
    \sa     setsockopt
            Belongs to \ref ext_api
    \warning
*/
int getsockopt(int fd, int level, int optname, void *optval, socklen_t *optlen);

/*!
    \brief Read data from TCP socket

    Function receives a message from a connection-mode socket

    \param[in]  fd              Socket handle
    \param[out] buf             Points to the buffer where the
                                message should be stored.
    \param[in]  len             Specifies the length in bytes of
                                the buffer pointed to by the buffer argument.
                                Range: 1-16000 bytes
    \param[in]  flags           Specifies the type of message
                                reception.

    \return                     Return the number of bytes received,
                                or a -1 if an error occurred. Errno is set accordingly.\n
                                Using a non-blocking recv a possible errno value is EAGAIN.\n
                                errno may be set to ENOMEM in case there are no resources in the system
                                In this case try again later or increase MAX_CONCURRENT_ACTIONS

    \sa     RecvFrom
    \note                       Belongs to \ref recv_api
    \warning
    \par        Examples

    - Receiving data using TCP socket:
    \code
        sockaddr_in  Addr;
        sockaddr_in  LocalAddr;
        int AddrSize = sizeof(socklen_t);
        int SockID, newSockID;
        int Status;
        char Buf[RECV_BUF_LEN];

        LocalAddr.sin_family = AF_INET;
        LocalAddr.sin_port = htons(5001);
        LocalAddr.sin_addr.s_addr = 0;

        Addr.sin_family = AF_INET;
        Addr.sin_port = htons(5001);
        Addr.sin_addr.s_addr = htonl(SL_IPV4_VAL(10,1,1,200));

        SockID = socket(AF_INET, SOCK_STREAM, 0);
        Status = bind(SockID, (struct sockaddr *)&LocalAddr, AddrSize);
        Status = listen(SockID, 0);
        newSockID = accept(SockID, (struct sockaddr *)&Addr, (socklen_t*) &AddrSize);
        Status = recv(newSockID, Buf, 1460, 0);

    \endcode
    <br>

*/
ssize_t recv(int fd, void *pBuf, size_t Len, int flags);

/*!
    \brief Read data from socket

    Function receives a message from a connection-mode or
    connectionless-mode socket

    \param[in]  fd              Socket handle
    \param[out] buf             Points to the buffer where the message should be stored.
    \param[in]  len             Specifies the length in bytes of the buffer pointed to by the buffer argument.
                                Range: 1-16000 bytes
    \param[in]  flags           Specifies the type of message
                                reception.
    \param[in]  from            Pointer to an address structure
                                indicating the source
                                address.\n sockaddr:\n - code
                                for the address format.\n - socket address,
                                the length depends on the code
                                format
    \param[in]  fromlen         Source address structure
                                size. This parameter MUST be set to the size of the structure pointed to by addr.


    \return                     Return the number of bytes received,
                                or a -1 if an error occurred. Errno is set accordingly.\n
                                Using a non-blocking recv a possible errno value is EAGAIN.\n
                                errno will be set to EINVAL if fromlen has incorrect length. \n
                                errno may be set to ENOMEM in case there are no resources in the system
                                In this case try again later or increase MAX_CONCURRENT_ACTIONS


    \sa     recv
    \note                       Belongs to \ref recv_api
    \warning
    \par        Example

    - Receiving data:
    \code
        sockaddr_in  Addr;
        sockaddr_in  LocalAddr;
        int AddrSize = sizeof(socklen_t);
        int SockID, newSockID;
        int Status;
        char Buf[RECV_BUF_LEN];

        LocalAddr.sin_family = AF_INET;
        LocalAddr.sin_port = htons(5001);
        LocalAddr.sin_addr.s_addr = 0;

        SockID = socket(AF_INET, SOCK_STREAM, 0);
        Status = bind(SockID, (struct sockaddr *)&LocalAddr, AddrSize);
        Status = recvfrom(SockID, Buf, 1472, 0, (sockaddr_in *)&Addr, (socklen_t*)&AddrSize);

    \endcode
*/
ssize_t recvfrom(int fd, void *buf, size_t Len, int flags, struct sockaddr *from, socklen_t *fromlen);

/*!
    \brief Write data to TCP socket

    This function is used to transmit a message to another socket.
    Returns immediately after sending data to device.
    In case of TCP failure an async event SL_SOCKET_TX_FAILED_EVENT is going to
    be received.\n

    \param[in] fd               Socket handle
    \param[in] buf              Points to a buffer containing
                                the message to be sent
    \param[in] len              Message size in bytes. Range: 1-1460 bytes
    \param[in] flags            Specifies the type of message
                                transmission.

    \return                     Zero on success, or -1 on failure and sets errno to the corresponding BDS error code.

    \sa     SendTo
    \note                       Belongs to \ref send_api
    \warning
    \par        Example

    - Sending data:
    \code
        sockaddr_in  Addr;
        int AddrSize = sizeof(socklen_t);
        int SockID;
        int Status;
        char Buf[SEND_BUF_LEN];

        Addr.sin_family = AF_INET;
        Addr.sin_port = htons(5001);
        Addr.sin_addr.s_addr = htonl(SL_IPV4_VAL(10,1,1,200));

        SockID = socket(AF_INET, SOCK_STREAM, 0);
        Status = connect(SockID, (sockaddr_in*)&Addr, AddrSize);
        Status = send(SockID, Buf, 1460, 0 );
    \endcode
 */
ssize_t send(int fd, const void *pBuf, size_t Len, int flags);

/*!
    \brief Write data to socket

    This function is used to transmit a message to another socket
    (connection less socket SOCK_DGRAM,  SOCK_RAW).\n
    Returns immediately after sending data to device.\n
    In case of transmission failure an async event SL_SOCKET_TX_FAILED_EVENT is going to
    be received.

    \param[in] fd               Socket handle
    \param[in] buf              Points to a buffer containing
                                the message to be sent
    \param[in] len              message size in bytes. Range: 1-1460 bytes
    \param[in] flags            Specifies the type of message
                                transmission.
    \param[in] to               Pointer to an address structure
                                indicating the destination
                                address.\n sockaddr:\n - code
                                for the address format.\n - socket address,
                                the length depends on the code
                                format
    \param[in] tolen            Destination address structure size

    \return                     Zero on success, or -1 on failure and sets errno to the corresponding BDS error code.

    \sa     Send
    \note                       Belongs to \ref send_api
    \warning
    \par        Example

    - Sending data:
    \code
        sockaddr_in  Addr;
        int AddrSize = sizeof(socklen_t);
        int SockID;
        int Status;
        char Buf[SEND_BUF_LEN];

        Addr.sin_family = AF_INET;
        Addr.sin_port = htons(5001);
        Addr.sin_addr.s_addr = htonl(SL_IPV4_VAL(10,1,1,200));

        SockID = socket(AF_INET, SOCK_DGRAM, 0);
        Status = sendto(SockID, Buf, 1472, 0, (sockaddr_in *)&Addr, AddrSize);
    \endcode
*/
ssize_t sendto(int fd, const void *pBuf, size_t Len, int flags, const struct sockaddr *to, socklen_t tolen);

/*!
    \brief errno - returns error code for last failure of BSD API calling.

     if SL_INC_INTERNAL_ERRNO is enabled, when an error occurs the BSD API returns -1, in order to detect the specific error value,
     user should invoke this function.

    \return  Return number of last error

    \sa      bind  connect  recvfrom  recv  accept  sendto  send
    \warning
    \par        Example

    - Querying errno:
    \code
        Status = recvfrom(SockID, Buf, 1472, 0, (struct sockaddr *)&Addr, (socklen_t*)&AddrSize);
        while(Status < 0)
        {
            if(errno == EAGAIN)
            {
               Status = recvfrom(SockID, Buf, 1472, 0, (struct sockaddr *)&Addr, (socklen_t*)&AddrSize);
            }
            else if(errno)
            {
                printf("A socket error occurred..");
                return (close(SockID));
            }
        }
    \endcode
*/
#ifdef SL_INC_INTERNAL_ERRNO
#ifdef errno
#undef errno
#endif
#define errno       *(__errno())
#endif

/*!

 Close the Doxygen group.
 @}

 */

#ifdef  __cplusplus
}
#endif /* __cplusplus */
#endif /* __SOCKET_H__ */
