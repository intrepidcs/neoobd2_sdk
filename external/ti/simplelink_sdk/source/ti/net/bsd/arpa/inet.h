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

#ifndef __INET_H__
#define __INET_H__

#ifdef    __cplusplus
extern "C" {
#endif

/*!

    \addtogroup BSD_Socket
    @{
*/

/*!
    \brief Reorder the bytes of a 32-bit unsigned value

    This function is used to Reorder the bytes of a 32-bit unsigned value from processor order to network order.

    \param [in] val             Variable to reorder

    \return                     Return the reordered variable.

    \sa     sendto  bind  connect  recvfrom  accept
*/
#define htonl                SlNetUtil_htonl

/*!
    \brief Reorder the bytes of a 32-bit unsigned value

    This function is used to Reorder the bytes of a 32-bit unsigned value from network order to processor order.

    \param[in] val              Variable to reorder

    \return                     Return the reordered variable.

    \sa     sendto  bind  connect  recvfrom  accept
*/
#define ntohl                SlNetUtil_ntohl

/*!
    \brief Reorder the bytes of a 16-bit unsigned value

    This function is used to Reorder the bytes of a 16-bit unsigned value from processor order to network order.

    \param[in] val              Variable to reorder

    \return                     Return the reordered variable.

    \sa     sendto  bind  connect  recvfrom  accept
*/
#define htons                SlNetUtil_htons

/*!
    \brief Reorder the bytes of a 16-bit unsigned value

    This function is used to Reorder the bytes of a 16-bit unsigned value from network order to processor order.

    \param[in] val              Variable to reorder

    \return                     Return the reordered variable.

    \sa     sendto  bind  connect  recvfrom  accept
*/
#define ntohs                SlNetUtil_ntohs

/*!
    \brief Converts IP address in binary representation to string representation

    This functions is used to converts IP address in binary representation
    to IP address in string representation.

    \param[in]  af       Specifies the address family of the created socket
                         For example:
                           - AF_INET for network address IPv4
                           - AF_INET6 for network address IPv6
    \param[in]  src      Pointer to an IP address structure indicating the
                         address in binary representation
    \param[out] dst      Pointer to the address string representation for IPv4
                         or IPv6 according to the address family
    \param[in]  size     Specifies the length of the StrAddress_dst, the maximum
                         length of the address in string representation for IPv4
                         or IPv6 according to the address family

    \return              strAddr on success, or NULL on failure

    \sa
    \note
    \warning
    \par    Example
    - IPv4 demo of inet_ntop()
    \code
        SlNetSock_AddrIn_t sa;
        char str[SLNETSOCK_INET_ADDRSTRLEN];

        // store this IP address in sa:
        SlNetSock_inet_pton(SLNETSOCK_AF_INET, "192.0.2.33", &(sa.sin_addr));
        // now get it back and print it
        SlNetSock_inet_ntop(SLNETSOCK_AF_INET, &(sa.sin_addr), str, SLNETSOCK_INET_ADDRSTRLEN);
    \endcode
*/
#define inet_ntop            SlNetUtil_inetNtop

/*!
    \brief Reorder the bytes of a 16-bit unsigned value

    This function is used to Reorder the bytes of a 16-bit unsigned value from network order to processor order.

    \param[in] val              Variable to reorder

    \return                     Return the reordered variable.

    \sa     sendto  bind  connect  recvfrom  accept
*/
#define inet_pton            SlNetUtil_inetPton
/*!

 Close the Doxygen group.
 @}

 */

#ifdef  __cplusplus
}
#endif /* __cplusplus */
#endif /* __INET_H__ */
