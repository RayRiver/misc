#ifndef NetDef_h__
#define NetDef_h__

#ifdef _WIN32
#include <windows.h>
#include <WinSock.h>
#include <errno.h>
#include <cerrno>
#	ifndef SD_BOTH
#		define SD_BOTH         0x02
#	endif

#define SYS_ETIMEDOUT     WSAETIMEDOUT
#define SYS_EINTR         WSAEINTR
#define SYS_EAGAIN        WSAEWOULDBLOCK
#define SYS_EWOULDBLOCK   WSAEWOULDBLOCK
#define SYS_EINPROGRESS   WSAEINPROGRESS
#define SYS_ENOTCONN       WSAENOTCONN
#else
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <sys/select.h>
#include <sys/ioctl.h>

#   ifdef _ANDROID
#   include <sys/endian.h>
#	include <fcntl.h>
#   else
#	include <sys/sockio.h>
#	include <sys/filio.h>
#	include <sys/fcntl.h>
#   endif

#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#	define ioctlsocket ioctl
#	define closesocket close
#	define TCP_NODELAY 0x6
#	define SD_BOTH SHUT_RDWR
#	define SOCKET int
#	define INVALID_SOCKET -1


#define SYS_ETIMEDOUT       ETIMEDOUT
#define SYS_EINTR           EINTR
#define SYS_EAGAIN          EAGAIN
#define SYS_EWOULDBLOCK     EWOULDBLOCK
#define SYS_EINPROGRESS     EINPROGRESS
#define SYS_ENOTCONN        ENOTCONN

#endif

#endif // NetDef_h__
