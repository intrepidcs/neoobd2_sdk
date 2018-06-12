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

#include <unistd.h>  /* needed? */
#include <string.h>
#include <stdlib.h>

#include <ti/net/slnetutils.h>


/*****************************************************************************/
/* Macro declarations                                                        */
/*****************************************************************************/

#define SLNETUTIL_NORMALIZE_NEEDED 0
#if SLNETUTIL_NORMALIZE_NEEDED
    #define SLNETUTIL_NORMALIZE_RET_VAL(retVal,err) ((retVal < 0)?(retVal = err):(retVal))
#else
    #define SLNETUTIL_NORMALIZE_RET_VAL(retVal,err)
#endif

/*****************************************************************************/
/* Structure/Enum declarations                                               */
/*****************************************************************************/


/*****************************************************************************/
/* Function prototypes                                                       */
/*****************************************************************************/

static int32_t SlNetUtil_UTOA(uint16_t value, char * string, uint16_t base);
static int32_t SlNetUtil_bin2StrIpV4(SlNetSock_InAddr_t *binaryAddr, char *strAddr, uint16_t strAddrLen);
static int32_t SlNetUtil_bin2StrIpV6(SlNetSock_In6Addr_t *binaryAddr, char *strAddr, uint16_t strAddrLen);
static int32_t SlNetUtil_strTok(char **string, char *returnstring, const char *delimiter);
static int32_t SlNetUtil_str2BinIpV4(char *strAddr, SlNetSock_InAddr_t *binaryAddr);
static int32_t SlNetUtil_str2BinIpV6(char *strAddr, SlNetSock_In6Addr_t *binaryAddr);

//*****************************************************************************
//
// SlNetUtil_init - Initialize the slnetutil module
//
//*****************************************************************************
int32_t SlNetUtil_init(int32_t flags)
{
    return 0;
}


//*****************************************************************************
//
// SlNetUtil_getHostByName - Obtain the IP Address of machine on network, by
//                           machine name
//
//*****************************************************************************
int32_t SlNetUtil_getHostByName(uint32_t ifBitmap, char *name, const uint16_t nameLen, uint32_t *ipAddr, uint16_t *ipAddrLen, const uint8_t family)
{
    SlNetIf_t *netIf;
    int32_t    retVal;

    /* When ifBitmap is 0, that means automatic selection of all interfaces
       is required, enable all bits in ifBitmap                              */
    if (0 == ifBitmap)
    {
        ifBitmap = ~ifBitmap;
    }

    /* This loop tries to run get host by name on the required interface
       only if it in state enable and connected status
       When multiple interfaces, in addition to the enable and connected it
       will try to run the function on the interface from the highest
       priority until an answer will return or until no interfaces left      */
    do
    {
        /* Search for the highest priority interface according to the
           ifBitmap and the queryFlags                                       */
        netIf = SlNetIf_queryIf(ifBitmap, SLNETIF_QUERY_IF_STATE_BIT | SLNETIF_QUERY_IF_CONNECTION_STATUS_BIT);

        /* Check if the function returned NULL or the requested interface
           exists                                                            */
        if ( (NULL == netIf) || ( NULL == (netIf->ifConf)->utilGetHostByName) )
        {
            /* Interface doesn't exists, return error code                   */
            return SLNETERR_RET_CODE_INVALID_INPUT;
        }
        else
        {
            /* Disable the ifID bit from the ifBitmap after finding the netIf*/
            ifBitmap &= ~(netIf->ifID);

            /* Interface exists, return interface IP address                 */
            retVal = (netIf->ifConf)->utilGetHostByName(netIf->ifContext, name, nameLen, ipAddr, ipAddrLen, family);
            SLNETUTIL_NORMALIZE_RET_VAL(retVal, SLNETUTIL_ERR_UTILGETHOSTBYNAME_FAILED);

            /* Check retVal for error codes                                  */
            if (retVal < SLNETERR_RET_CODE_OK)
            {
                /* utilGetHostByName failed, continue to the next ifID       */
                continue;
            }
            else
            {
                /* Return success                                            */
                return netIf->ifID;
            }
        }
    }while ( ifBitmap > 0 );
    /* Interface doesn't exists, return error code                   */
    return SLNETERR_RET_CODE_INVALID_INPUT;
}


//*****************************************************************************
//
// SlNetUtil_htonl - Reorder the bytes of a 32-bit unsigned value from host
//                   order to network order(Big endian)
//
//*****************************************************************************
uint32_t SlNetUtil_htonl(uint32_t val)
{
    uint32_t i = 1;
    int8_t  *p = (int8_t *)&i;

    /* When the LSB of i stored in the smallest address of *p                */
    if (p[0] == 1) /* little endian */
    {
        /* Swap the places of the value                                      */
        p[0] = ((int8_t *)&val)[3];
        p[1] = ((int8_t *)&val)[2];
        p[2] = ((int8_t *)&val)[1];
        p[3] = ((int8_t *)&val)[0];

        /* return the reordered bytes                                        */
        return i;
    }
    else /* big endian */
    {
        /* return the input without any changes                              */
        return val;
    }
}


//*****************************************************************************
//
// SlNetUtil_ntohl - Reorder the bytes of a 32-bit unsigned value from network
//                   order(Big endian) to host order
//
//*****************************************************************************
uint32_t SlNetUtil_ntohl(uint32_t val)
{
    /* return the reordered bytes                                            */
    return SlNetUtil_htonl(val);
}


//*****************************************************************************
//
// SlNetUtil_htons - Reorder the bytes of a 16-bit unsigned value from host
//                   order to network order(Big endian)
//
//*****************************************************************************
uint16_t SlNetUtil_htons(uint16_t val)
{
    int16_t i = 1;
    int8_t *p = (int8_t *)&i;

    /* When the LSB of i stored in the smallest address of *p                */
    if (p[0] == 1) /* little endian */
    {
        /* Swap the places of the value                                      */
        p[0] = ((int8_t *)&val)[1];
        p[1] = ((int8_t *)&val)[0];

        /* return the reordered bytes                                        */
        return (uint16_t)i;
    }
    else /* big endian */
    {
        /* return the input without any changes                              */
        return val;
    }
}


//*****************************************************************************
//
// SlNetUtil_ntohs - Reorder the bytes of a 16-bit unsigned value from network
//                   order(Big endian) to host order
//
//*****************************************************************************
uint16_t SlNetUtil_ntohs(uint16_t val)
{
    /* return the reordered bytes                                            */
    return SlNetUtil_htons(val);
}

//*****************************************************************************
//
// SlNetUtil_UTOA - converts unsigned 16 bits binary number to string with
//                  maximum of 4 characters + 1 NULL terminated
//
//*****************************************************************************
static int32_t SlNetUtil_UTOA(uint16_t value, char * string, uint16_t base)
{
    uint16_t Index         = 4;
    char     tempString[5] = { 0 };
    char *   ptempString   = tempString;
    char *   pString       = string;

    /* Check if the inputs valid                                             */
    if ( (NULL == string) || ((base < 2 ) && (base > 16 )) )
    {
        return SLNETERR_RET_CODE_INVALID_INPUT;
    }

    /* If value is zero, that means that the returned string needs to be zero*/
    if (0 == value)
    {
        *ptempString = '0';
        ptempString++;
    }

    /* Run until all value digits are 0 or until Index get to 0              */
    for (; (value && (Index > 0)); Index--, value /= base)
    {
        *ptempString = "0123456789abcdef"[value % base];
        ptempString++;
    }
    /* Invalid value input                                                   */
    if (0 != value)
    {
        return SLNETERR_RET_CODE_INVALID_INPUT;
    }

    /* Reverse the string and initialize temporary array                     */
    while (Index < 4)
    {
        *(pString++) = *(--ptempString);
        *ptempString = '\0';
        *pString     = '\0';
        Index++;
    }

    return 0;
}

//*****************************************************************************
//
// SlNetUtil_bin2StrIpV4 - converts IPv4 address in binary representation to
//                         IP address in string representation
//
//*****************************************************************************
static int32_t SlNetUtil_bin2StrIpV4(SlNetSock_InAddr_t *binaryAddr, char *strAddr, uint16_t strAddrLen)
{
    uint8_t  tempOctet;
    uint32_t tempBinAddr;
    int32_t  octetIndex      = 3;
    char     tempStrOctet[4] = { 0 };

    /* Check if the strAddr buffer is at least in the minimum required size  */
    if (strAddrLen < SLNETSOCK_INET_ADDRSTRLEN)
    {
        /* Return error code                                                 */
        return SLNETERR_RET_CODE_INVALID_INPUT;
    }

    memset(strAddr, 0, sizeof(strAddr));

    /* Copy the address value for further use                                */
    memcpy(&tempBinAddr, binaryAddr, sizeof(SlNetSock_InAddr_t));

    /* Run over all octets, from the latest octet (the most significant
       octet - MSO) until the first one (the least significant octet - LSO)  */
    while ( octetIndex >= 0 )
    {
        /* Save octet on tempOctet for further usage.
           When converting from binary representation to string
           representation, the MSO of the binary number is the first char
           of the string, so it needs to copied to the first location of
           the array                                                         */
        tempOctet = ((int8_t *)&tempBinAddr)[octetIndex];

        /* Initialize the octet for validation after copying the value       */
        ((int8_t *)&tempBinAddr)[octetIndex] = 0;

        /* Convert tempOctet to string                                       */
        SlNetUtil_UTOA(tempOctet, tempStrOctet, 10);

        /* Appends the tempStrOctet to strAddr                               */
        strcat(strAddr, tempStrOctet);

        /* Appends the "." to strAddr for the first 3 octets                 */
        if ( octetIndex > 0)
        {
            strcat(strAddr, ".");
        }

        /* Move to the next octet                                            */
        octetIndex --;

    }

    /* Check if the address had only 4 octets, this was done by initializing
       each octet that was copied and than checking if the number equal to 0 */
    if ( 0 == tempBinAddr )
    {
        /* Return success                                                    */
        return SLNETERR_RET_CODE_OK;
    }
    else
    {
        /* Return error code                                                 */
        return SLNETERR_RET_CODE_INVALID_INPUT;
    }
}


//*****************************************************************************
//
// SlNetUtil_bin2StrIpV6 - converts IPv5 address in binary representation to
//                         IP address in string representation
//
//*****************************************************************************
static int32_t SlNetUtil_bin2StrIpV6(SlNetSock_In6Addr_t *binaryAddr, char *strAddr, uint16_t strAddrLen)
{
    uint8_t  tempHextet;
    int32_t  hextetIndex      = 7;
    uint32_t tempBinAddr[4]   = { 0 };
    char     tempStrHextet[5] = { 0 };

    /* Check if the strAddr buffer is at least in the minimum required size  */
    if (strAddrLen < SLNETSOCK_INET6_ADDRSTRLEN)
    {
        /* Return error code                                                 */
        return SLNETERR_RET_CODE_INVALID_INPUT;
    }

    /* Copy the address value for further use                                */
    memcpy(tempBinAddr, binaryAddr, sizeof(SlNetSock_In6Addr_t));

    /* Run over all octets, from the latest hextet (the most significant
       hextet) until the first one (the least significant hextet)            */
    while ( hextetIndex >= 0 )
    {
        /* Save hextet on tempHextet for further usage.
           When converting from binary representation to string
           representation, the most significant hextet of the binary number
           is the first char of the string, so it needs to copied to the
           first location of the array                                       */
        tempHextet = ((int16_t *)&tempBinAddr)[hextetIndex];

        /* Initialize the hextet for validation after copying the value      */
        ((int16_t *)&tempBinAddr)[hextetIndex] = 0;

        /* Convert tempHextet to string                                      */
        SlNetUtil_UTOA(tempHextet, tempStrHextet, 16);

        /* Appends the tempStrHextet to strAddr                              */
        strcat(strAddr, tempStrHextet);

        /* Appends the ":" after each hextet (without the last one)          */
        if ( hextetIndex > 0)
        {
            strcat(strAddr, ":");
        }

        /* Move to the next hextet                                           */
        hextetIndex --;

    }

    /* Check if the address had only 8 hextets, this was done by initializing
       each hextet that was copied and than checking if the number equal to 0*/
    if ( 0 == tempBinAddr )
    {
        /* Return success                                                    */
        return SLNETERR_RET_CODE_OK;
    }
    else
    {
        /* Return error code                                                 */
        return SLNETERR_RET_CODE_INVALID_INPUT;
    }
}


//*****************************************************************************
//
// SlNetUtil_inetNtop - converts IP address in binary representation to IP
//                      address in string representation
//
//*****************************************************************************
const char *SlNetUtil_inetNtop(int16_t addrFamily, const void *binaryAddr, char *strAddr, SlNetSocklen_t strAddrLen)
{
    int32_t retVal;

    /* Switch according to the address family                                */
    switch(addrFamily)
    {
        case SLNETSOCK_AF_INET:
            /* Convert from IPv4 string to numeric/binary representation     */
            retVal = SlNetUtil_bin2StrIpV4((SlNetSock_InAddr_t *)binaryAddr, strAddr, strAddrLen);

        break;
        case SLNETSOCK_AF_INET6:
            /* Convert from IPv6 string to numeric/binary representation     */
            retVal = SlNetUtil_bin2StrIpV6((SlNetSock_In6Addr_t *)binaryAddr, strAddr, strAddrLen);

        break;
        default:
            /* wrong address family - function error, return NULL error      */
            return NULL;
    }

    /* Check if conversion was successful                                    */
    if (retVal != SLNETERR_RET_CODE_OK)
    {
        /* Conversion failed, return NULL as error code                      */
        return NULL;
    }
    /* Conversion success - return strAddr for success                       */
    return strAddr;
}

//*****************************************************************************
//
// SlNetUtil_strTok - Split a string up into tokens
//
//*****************************************************************************
static int32_t SlNetUtil_strTok(char **string, char *returnstring, const char *delimiter)
{
    char * retStr;

    memset(returnstring, 0, sizeof(returnstring));
    retStr = returnstring;

    while ( (**string !='\0') && (**string != *delimiter) )
    {
        *retStr = **string;
        retStr++;
        (*string)++;
    }
    if (**string !='\0')
    {
        (*string)++;
    }
    retStr = '\0';

    return SLNETERR_RET_CODE_OK;
}

//*****************************************************************************
//
// SlNetUtil_str2BinIpV4 - converts IPv4 address in string representation to
//                         IP address in binary representation
//
//*****************************************************************************
static int32_t SlNetUtil_str2BinIpV4(char *strAddr, SlNetSock_InAddr_t *binaryAddr)
{
    int32_t   ipOctet     = 0;
    uint32_t  decNumber;
    uint32_t  ipv4Address = 0;
    char      token[4];
    char     *modifiedStr = strAddr;
    int32_t   retVal;

    /* split strAddr into tokens separated by "."                            */
    retVal = SlNetUtil_strTok(&modifiedStr, token, ".");
    if (SLNETERR_RET_CODE_OK != retVal)
    {
        return retVal;
    }

    /* run 4 times as IPv4 contain of four octets and separated by periods   */
    while(ipOctet < 4)
    {
        /* Check Whether IP is valid */
        if(token != NULL)
        {
            /* Parses the token strAddr, interpreting its content as an integral
               number of the specified base 10                               */
            decNumber = (int)strtoul(token, 0, 10);

            /* Check if the octet holds valid number between the range 0-255 */
            if (decNumber < 256)
            {
                /* Combine the interpreted number to the binary address      */
                ipv4Address |= decNumber;
                if(ipOctet < 3)
                {
                    ipv4Address = ipv4Address << 8;
                }
                /* split strAddr into tokens separated by "."                */
                SlNetUtil_strTok(&modifiedStr, token, ".");
                ipOctet++;
            }
            else
            {
                return SLNETERR_RET_CODE_INVALID_INPUT;
            }
        }
        else
        {
            return SLNETERR_RET_CODE_INVALID_INPUT;
        }
    }

    /* Copy the temporary variable to the input variable                     */
    memcpy(binaryAddr, &ipv4Address, sizeof(SlNetSock_InAddr_t));

    return SLNETERR_RET_CODE_OK;
}


//*****************************************************************************
//
// SlNetUtil_str2BinIpV6 - converts IPv6 address in string representation to
//                         IP address in binary representation
//
//*****************************************************************************
static int32_t SlNetUtil_str2BinIpV6(char *strAddr, SlNetSock_In6Addr_t *binaryAddr)
{

    int32_t   octetIndex      = 0;
    int32_t   octetTailIndex;
    uint8_t  *pLocalStr;
    uint8_t   tmp[16];
    int32_t   zeroCompressPos = -1;
    uint16_t  value           = 0;
    uint8_t   asciiCharacter  = 0;

    /* Copy the first address of the string                                  */
    pLocalStr = (uint8_t*)strAddr;

    /* Initialize tmp parameter                                              */
    memset(tmp, 0, sizeof(tmp));

    /* Check if the IP starts with "::"                                      */
    if(*pLocalStr==':')
    {
        /* If the IP starts with ":", check if it doesn't have the second ":"
           If so, return an error                                            */
        if(*++pLocalStr!=':')
        {
            return SLNETERR_RET_CODE_INVALID_INPUT;
        }
    }

    /* run over the remaining two octets                                     */
    while(*pLocalStr && (octetIndex < 16))
    {
        /* Check if the ASCII character is a number between "0" to "9"       */
        if(*pLocalStr >= '0' && *pLocalStr <= '9')
        {
            /* Each ASCII character can be max 4 bits, shift the number
              4 bits and copy the new converted number                       */
            value = (value << 4) | (*pLocalStr - '0');

            /* Set the flag for ASCII character                              */
            asciiCharacter = 1;
        }
        /* Check if the ASCII character is a hex character between "a" to "f"*/
        else if(*pLocalStr >= 'a' && *pLocalStr <= 'f')
        {
            /* Each ASCII character can be max 4 bits, shift the number
              4 bits and copy the new converted number                       */
            value = (value << 4) | ((*pLocalStr - 'a') + 10);

            /* Set the flag for ASCII character                              */
            asciiCharacter = 1;
        }
        /* Check if the ASCII character is a hex character between "A" to "F"*/
        else if(*pLocalStr >= 'A' && *pLocalStr <= 'F')
        {
            /* Each ASCII character can be max 4 bits, shift the number
              4 bits and copy the new converted number                       */
            value = (value << 4) | ((*pLocalStr - 'A') + 10);

            /* Set the flag for ASCII character                              */
            asciiCharacter = 1;
        }
        /* Check if the hextet (two octets) finished with ":" and still a
           part of the IP                                                    */
        else if((*pLocalStr == ':') && (octetIndex < 14))
        {
            /* Check if the hextet contain ASCII character                   */
            if(asciiCharacter)
            {
                /* ASCII character exists, store the converted number in tmp
                   and reset the value and ascii character parameters        */
                tmp[octetIndex++] = (value >> 8) & 0xFF;
                tmp[octetIndex++] = (value) & 0xFF;
                asciiCharacter = 0;
                value = 0;
            }
            else
            {
                /* ASCII character doesn't exists, compressed hextet found   */
                if(zeroCompressPos < 0)
                {
                    /* first compressed hextet found, sore the octet Index   */
                    zeroCompressPos = octetIndex;
                }
                else
                {
                    /* Second compressed hextet found, return error code     */
                    return SLNETERR_RET_CODE_INVALID_INPUT;
                }
            }
        }
        /* Continue to the next ASCII character                              */
        pLocalStr++;
    }

    /* if more than 15 octets found, return error code                       */
    if(octetIndex > 15)
    {
        return SLNETERR_RET_CODE_INVALID_INPUT;
    }
    /* if less than 14 octets found, and without any compress hextet,
       return error code                                                     */
    else if(asciiCharacter && (zeroCompressPos < 0) && (octetIndex < 14))
    {
        return SLNETERR_RET_CODE_INVALID_INPUT;
    }
    /* if all octets found, but still found compressed hextet,
       return error code                                                     */
    else if((zeroCompressPos >= 0) && octetIndex >= 14)
    {
        return SLNETERR_RET_CODE_INVALID_INPUT;
    }

    /* copy the last available hextet to the tmp array                       */
    if((asciiCharacter) && (octetIndex <= 14))
    {
        /* Store the converted number in tmp and reset the value and
           ascii character parameters                                        */
        tmp[octetIndex++] = (value >> 8) & 0xFF;
        tmp[octetIndex++] = (value) & 0xFF;
        asciiCharacter = 0;
        value = 0;
    }

    /* compressed position found, add zeros in the compressed sections       */
    if(zeroCompressPos >= 0)
    {
        /* compressed position found, add zeros in the compressed sections   */
        octetIndex--;
        octetTailIndex = 15;
        /* Move the converted octets from the position they are located on
           to the end of the array and add zero instead */
        while(octetIndex >= zeroCompressPos)
        {
            /* Check if the indexes are still in range                       */
            if ((octetTailIndex >= 0) && (octetIndex >= 0))
            {
                /* Move all the octets after the zero compress position to
                   the end of the array                                      */
                tmp[octetTailIndex] = tmp[octetIndex];
                tmp[octetIndex] = 0;
                octetTailIndex--;
                octetIndex--;
            }
        }
    }

    /* Copy the temporary variable to the input variable                     */
    memcpy(binaryAddr, tmp, sizeof(tmp));

    return SLNETERR_RET_CODE_OK;

}


//*****************************************************************************
//
// SlNetUtil_inetPton - converts IP address in string representation to IP
//                      address in binary representation
//
//*****************************************************************************
int32_t SlNetUtil_inetPton(int16_t addrFamily, const char *strAddr, void *binaryAddr)
{
    int32_t retVal;

    /* Switch according to the address family                                */
    switch(addrFamily)
    {
        case SLNETSOCK_AF_INET:
            /* Convert from IPv4 string to numeric/binary representation     */
            retVal = SlNetUtil_str2BinIpV4((char *)strAddr, (SlNetSock_InAddr_t *)binaryAddr);
            break;

        case SLNETSOCK_AF_INET6:
            /* Convert from IPv6 string to numeric/binary representation     */
            retVal = SlNetUtil_str2BinIpV6((char *)strAddr, (SlNetSock_In6Addr_t *)binaryAddr);
            break;

        default:
            /* wrong address family - function error, return -1 error        */
            return SLNETERR_RET_CODE_INVALID_INPUT;
    }

    /* Check if conversion was successful                                    */
    if (retVal != SLNETERR_RET_CODE_OK)
    {
        /* Conversion failed, that means the input wasn't a
           valid IP address, return 0 as error code                          */
        return 0;
    }
    /* Conversion success - return 1 for success                             */
    return 1;
}
