/*
 * XP compatibility for ATL's socket helper.
 *
 * ATL's atlsocket.h uses the generic GetAddrInfo names. For
 * _WIN32_WINNT < 0x0502, use the ANSI Winsock declarations available
 * on Windows XP SP2/SP3 instead of mixing GetAddrInfoW with ANSI input.
 */
#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>

#if defined(_WIN32_WINNT) && (_WIN32_WINNT < 0x0502)
#undef ADDRINFOT
#undef GetAddrInfo
#undef FreeAddrInfo

#define ADDRINFOT addrinfo
#define GetAddrInfo getaddrinfo
#define FreeAddrInfo freeaddrinfo
#endif
