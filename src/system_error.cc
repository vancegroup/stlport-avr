// -*- C++ -*- Time-stamp: <2012-02-27 21:47:16 ptr>

/*
 * Copyright (c) 2007-2012
 * Petr Ovtchenkov
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

#include "stlport_prefix.h"

#include <cerrno>
#include "callstack.h"
#include <string>
#include <cstdlib>
#include <cstring>

#include <vector>

#include <system_error>
// #include <typeinfo>

namespace detail {

struct _SysErrInit
{
    typedef _STLP_STD::vector<const char *> container_type;

    _SysErrInit();

    container_type _sys_err;
    container_type::size_type _last_value;
};

_SysErrInit::_SysErrInit() :
    _sys_err( 255 ),
    _last_value( 0 )
{
  _sys_err[0] = "Success";
  /* Operation not permitted; only the owner of the file (or other resource)
     or processes with special privileges can perform the operation. */
#ifdef EPERM
  _sys_err[EPERM] = "Operation not permitted";
#endif
#ifdef ENOENT
  /* No such file or directory. This is a ``file doesn't exist'' error
     for ordinary files that are referenced in contexts where they are
     expected to already exist. */
  _sys_err[ENOENT] = "No such file or directory";
#endif
#ifdef ESRCH
  /* No process matches the specified process ID. */
  _sys_err[ESRCH] = "No such process";
#endif
#ifdef EINTR
  /* Interrupted function call; an asynchronous signal occurred and prevented
     completion of the call.  When this happens, you should try the call
     again.
 
     You can choose to have functions resume after a signal that is handled,
     rather than failing with EINTR. */
  _sys_err[EINTR] = "Interrupted system call";
#endif
#ifdef EIO
  /* Input/output error; usually used for physical read or write errors. */
  _sys_err[EIO] = "Input/output error";
#endif
#ifdef ENXIO
  /* No such device or address. The system tried to use the device
     represented by a file you specified, and it couldn't find the device.
     This can mean that the device file was installed incorrectly, or that
     the physical device is missing or not correctly attached to the
     computer. */
  _sys_err[ENXIO] = "No such device or address";
#endif
#ifdef E2BIG
  /* Argument list too long; used when the arguments passed to a new program
     being executed with one of the exec functions occupy too much memory
     space. This condition never arises in the GNU system. */
  _sys_err[E2BIG] = "Argument list too long";
#endif
#ifdef ENOEXEC
  /* Invalid executable file format. This condition is detected by the
     exec functions. */
  _sys_err[ENOEXEC] = "Exec format error";
#endif
#ifdef EBADF
  /* Bad file descriptor; for example, I/O on a descriptor that has been
     closed or reading from a descriptor open only for writing (or vice
     versa). */
  _sys_err[EBADF] = "Bad file descriptor";
#endif
#ifdef ECHILD
  /* There are no child processes.  This error happens on operations that are
     supposed to manipulate child processes, when there aren't any processes
     to manipulate. */
  _sys_err[ECHILD] = "No child processes";
#endif
#ifdef EDEADLK
  /* Deadlock avoided; allocating a system resource would have resulted in a
     deadlock situation. The system does not guarantee that it will notice
     all such situations. This error means you got lucky and the system
     noticed; it might just hang. */
  _sys_err[EDEADLK] = "Resource deadlock avoided";
#endif
#ifdef ENOMEM
  /* No memory available. The system cannot allocate more virtual memory
     because its capacity is full. */
  _sys_err[ENOMEM] = "Cannot allocate memory";
#endif
#ifdef EACCES
  /* Permission denied; the file permissions do not allow the attempted operation. */
  _sys_err[EACCES] = "Permission denied";
#endif
#ifdef EFAULT
  /* Bad address; an invalid pointer was detected.
     In the GNU system, this error never happens; you get a signal instead. */
  _sys_err[EFAULT] = "Bad address";
#endif
#ifdef ENOTBLK
  /* A file that isn't a block special file was given in a situation that
     requires one.  For example, trying to mount an ordinary file as a file
     system in Unix gives this error. */
  _sys_err[ENOTBLK] = "Block device required";
#endif
#ifdef EBUSY
  /* Resource busy; a system resource that can't be shared is already in use.
     For example, if you try to delete a file that is the root of a currently
     mounted filesystem, you get this error. */
  _sys_err[EBUSY] = "Device or resource busy";
#endif
#ifdef EEXIST
  /* File exists; an existing file was specified in a context where it only
     makes sense to specify a new file. */
  _sys_err[EEXIST] = "File exists";
#endif
#ifdef EXDEV
  /* An attempt to make an improper link across file systems was detected.
     This happens not only when you use link but also when you rename a file
     with rename. */
  _sys_err[EXDEV] = "Invalid cross-device link";
#endif
#ifdef ENODEV
  /* The wrong type of device was given to a function that expects a
     particular sort of device. */
  _sys_err[ENODEV] = "No such device";
#endif
#ifdef ENOTDIR
  /* A file that isn't a directory was specified when a directory is required. */
  _sys_err[ENOTDIR] = "Not a directory";
#endif
#ifdef EISDIR
  /* File is a directory; you cannot open a directory for writing,
     or create or remove hard links to it. */
  _sys_err[EISDIR] = "Is a directory";
#endif
#ifdef EINVAL
  /* Invalid argument. This is used to indicate various kinds of problems
     with passing the wrong argument to a library function. */
  _sys_err[EINVAL] = "Invalid argument";
#endif
#ifdef EMFILE
  /* The current process has too many files open and can't open any more.
     Duplicate descriptors do count toward this limit.
 
     In BSD and GNU, the number of open files is controlled by a resource
     limit that can usually be increased.  If you get this error, you might
     want to increase the RLIMIT_NOFILE limit or make it unlimited. */
  _sys_err[EMFILE] = "Too many open files";
#endif
#ifdef ENFILE
  /* There are too many distinct file openings in the entire system. Note
     that any number of linked channels count as just one file opening;
     This error never occurs in the GNU system. */
  _sys_err[ENFILE] = "Too many open files in system";
#endif
#ifdef ENOTTY
  /* Inappropriate I/O control operation, such as trying to set terminal
     modes on an ordinary file. */
  _sys_err[ENOTTY] = "Inappropriate ioctl for device";
#endif
#ifdef ETXTBSY
  /* An attempt to execute a file that is currently open for writing, or
     write to a file that is currently being executed.  Often using a
     debugger to run a program is considered having it open for writing and
     will cause this error.  (The name stands for ``text file busy''.)  This
     is not an error in the GNU system; the text is copied as necessary. */
  _sys_err[ETXTBSY] = "Text file busy";
#endif
#ifdef EFBIG
  /* File too big; the size of a file would be larger than allowed by the system. */
  _sys_err[EFBIG] = "File too large";
#endif
#ifdef ENOSPC
  /* No space left on device; write operation on a file failed because the
     disk is full. */
  _sys_err[ENOSPC] = "No space left on device";
#endif
#ifdef ESPIPE
  /* Invalid seek operation (such as on a pipe). */
  _sys_err[ESPIPE] = "Illegal seek";
#endif
#ifdef EROFS
  /* An attempt was made to modify something on a read-only file system. */
  _sys_err[EROFS] = "Read-only file system";
#endif
#ifdef EMLINK
  /* Too many links; the link count of a single file would become too large.
     rename can cause this error if the file being renamed already has
     as many links as it can take. */
  _sys_err[EMLINK] = "Too many links";
#endif
#ifdef EPIPE
  /* Broken pipe; there is no process reading from the other end of a pipe.
     Every library function that returns this error code also generates a
     SIGPIPE signal; this signal terminates the program if not handled
     or blocked. Thus, your program will never actually see EPIPE
     unless it has handled or blocked SIGPIPE. */
  _sys_err[EPIPE] = "Broken pipe";
#endif
#ifdef EDOM
  /* Domain error; used by mathematical functions when an argument value does
     not fall into the domain over which the function is defined. */
  _sys_err[EDOM] = "Numerical argument out of domain";
#endif
#ifdef ERANGE
  /* Range error; used by mathematical functions when the result value is
     not representable because of overflow or underflow. */
  _sys_err[ERANGE] = "Numerical result out of range";
#endif
#ifdef EAGAIN
  /* Resource temporarily unavailable; the call might work if you try again
     later.  The macro EWOULDBLOCK is another name for EAGAIN;
     they are always the same in the GNU C library.
 
     This error can happen in a few different situations:
 
   * An operation that would block was attempted on an object that has
     non-blocking mode selected.  Trying the same operation again will block
     until some external condition makes it possible to read, write, or
     connect (whatever the operation).  You can use select to find out
     when the operation will be possible.
 
     Portability Note: In many older Unix systems, this condition
     was indicated by EWOULDBLOCK, which was a distinct error code
     different from EAGAIN. To make your program portable, you should
     check for both codes and treat them the same.
 
   * A temporary resource shortage made an operation impossible. fork
     can return this error.  It indicates that the shortage is expected to
     pass, so your program can try the call again later and it may succeed.
     It is probably a good idea to delay for a few seconds before trying it
     again, to allow time for other processes to release scarce resources.
     Such shortages are usually fairly serious and affect the whole system,
     so usually an interactive program should report the error to the user
     and return to its command loop. */
  _sys_err[EAGAIN] = "Resource temporarily unavailable";
#endif
#if defined (EWOULDBLOCK) && (EWOULDBLOCK != EAGAIN)
  /* In the GNU C library, this is another name for EAGAIN (above).
     The values are always the same, on every operating system.
 
     C libraries in many older Unix systems have EWOULDBLOCK as a
     separate error code. */
  _sys_err[EWOULDBLOCK] = "Operation would block";
#endif
#ifdef EINPROGRESS
  /* An operation that cannot complete immediately was initiated on an object
     that has non-blocking mode selected. Some functions that must always
     block (such as connect) never return EAGAIN. Instead, they return
     EINPROGRESS to indicate that the operation has begun and will take
     some time. Attempts to manipulate the object before the call completes
     return EALREADY. You can use the select function to find out when
     the pending operation has completed. */
  _sys_err[EINPROGRESS] = "Operation now in progress";
#endif
#ifdef EALREADY
  /* An operation is already in progress on an object that has non-blocking
     mode selected. */
  _sys_err[EALREADY] = "Operation already in progress";
#endif
#ifdef ENOTSOCK
  /* A file that isn't a socket was specified when a socket is required. */
  _sys_err[ENOTSOCK] = "Socket operation on non-socket";
#endif
#ifdef EMSGSIZE
  /* The size of a message sent on a socket was larger than the supported
     maximum size. */
  _sys_err[EMSGSIZE] = "Message too long";
#endif
#ifdef EPROTOTYPE
  /* The socket type does not support the requested communications protocol. */
  _sys_err[EPROTOTYPE] = "Protocol wrong type for socket";
#endif
#ifdef ENOPROTOOPT
  /* You specified a socket option that doesn't make sense for the
     particular protocol being used by the socket. */
  _sys_err[ENOPROTOOPT] = "Protocol not available";
#endif
#ifdef EPROTONOSUPPORT
  /* The socket domain does not support the requested communications protocol
     (perhaps because the requested protocol is completely invalid). */
  _sys_err[EPROTONOSUPPORT] = "Protocol not supported";
#endif
#ifdef ESOCKTNOSUPPORT
  /* The socket type is not supported. */
  _sys_err[ESOCKTNOSUPPORT] = "Socket type not supported";
#endif
#ifdef EOPNOTSUPP
  /* The operation you requested is not supported.  Some socket functions
     don't make sense for all types of sockets, and others may not be
     implemented for all communications protocols.  In the GNU system, this
     error can happen for many calls when the object does not support the
     particular operation; it is a generic indication that the server knows
     nothing to do for that call. */
  _sys_err[EOPNOTSUPP] = "Operation not supported";
#endif
#ifdef EPFNOSUPPORT
  /* The socket communications protocol family you requested is not supported. */
  _sys_err[EPFNOSUPPORT] = "Protocol family not supported";
#endif
#ifdef EAFNOSUPPORT
  /* The address family specified for a socket is not supported; it is
     inconsistent with the protocol being used on the socket. */
  _sys_err[EAFNOSUPPORT] = "Address family not supported by protocol";
#endif
#ifdef EADDRINUSE
  /* The requested socket address is already in use. */
  _sys_err[EADDRINUSE] = "Address already in use";
#endif
#ifdef EADDRNOTAVAIL
  /* The requested socket address is not available; for example, you tried
     to give a socket a name that doesn't match the local host name. */
  _sys_err[EADDRNOTAVAIL] = "Cannot assign requested address";
#endif
#ifdef ENETDOWN
  /* A socket operation failed because the network was down. */
  _sys_err[ENETDOWN] = "Network is down";
#endif
#ifdef ENETUNREACH
  /* A socket operation failed because the subnet containing the remote host
     was unreachable. */
  _sys_err[ENETUNREACH] = "Network is unreachable";
#endif
#ifdef ENETRESET
  /* A network connection was reset because the remote host crashed. */
  _sys_err[ENETRESET] = "Network dropped connection on reset";
#endif
#ifdef ECONNABORTED
  /* A network connection was aborted locally. */
  _sys_err[ECONNABORTED] = "Software caused connection abort";
#endif
#ifdef ECONNRESET
  /* A network connection was closed for reasons outside the control of the
     local host, such as by the remote machine rebooting or an unrecoverable
     protocol violation. */
  _sys_err[ECONNRESET] = "Connection reset by peer";
#endif
#ifdef ENOBUFS
  /* The kernel's buffers for I/O operations are all in use. In GNU, this
     error is always synonymous with ENOMEM; you may get one or the
     other from network operations. */
  _sys_err[ENOBUFS] = "No buffer space available";
#endif
#ifdef EISCONN
  /* You tried to connect a socket that is already connected. */
  _sys_err[EISCONN] = "Transport endpoint is already connected";
#endif
#ifdef ENOTCONN
  /* The socket is not connected to anything.  You get this error when you
     try to transmit data over a socket, without first specifying a
     destination for the data.  For a connectionless socket (for datagram
     protocols, such as UDP; you get EDESTADDRREQ instead. */
  _sys_err[ENOTCONN] = "Transport endpoint is not connected";
#endif
#ifdef EDESTADDRREQ
  /* No default destination address was set for the socket.  You get this
     error when you try to transmit data over a connectionless socket,
     without first specifying a destination for the data with connect. */
  _sys_err[EDESTADDRREQ] = "Destination address required";
#endif
#ifdef ESHUTDOWN
  /* The socket has already been shut down. */
  _sys_err[ESHUTDOWN] = "Cannot send after transport endpoint shutdown";
#endif
#ifdef ETOOMANYREFS
  /* ??? */
  _sys_err[ETOOMANYREFS] = "Too many references: cannot splice";
#endif
#ifdef ETIMEDOUT
  /* A socket operation with a specified timeout received no response during
     the timeout period. */
  _sys_err[ETIMEDOUT] = "Connection timed out";
#endif
#ifdef ECONNREFUSED
  /* A remote host refused to allow the network connection (typically because
     it is not running the requested service). */
  _sys_err[ECONNREFUSED] = "Connection refused";
#endif
#ifdef ELOOP
  /* Too many levels of symbolic links were encountered in looking up a file name.
     This often indicates a cycle of symbolic links. */
  _sys_err[ELOOP] = "Too many levels of symbolic links";
#endif
#ifdef ENAMETOOLONG
  /* Filename too long (longer than PATH_MAX) or host name too long
     (in gethostname or sethostname). */
  _sys_err[ENAMETOOLONG] = "File name too long";
#endif
#ifdef EHOSTDOWN
  /* The remote host for a requested network connection is down. */
  _sys_err[EHOSTDOWN] = "Host is down";
#endif
#ifdef EHOSTUNREACH
  /* The remote host for a requested network connection is not reachable. */
  _sys_err[EHOSTUNREACH] = "No route to host";
#endif
#ifdef ENOTEMPTY
  /* Directory not empty, where an empty directory was expected. Typically,
     this error occurs when you are trying to delete a directory. */
  _sys_err[ENOTEMPTY] = "Directory not empty";
#endif
#ifdef EPROCLIM
  /* This means that the per-user limit on new process would be exceeded by
     an attempted fork. */
  _sys_err[EPROCLIM] = "Too many processes";
#endif
#ifdef EUSERS
  /* The file quota system is confused because there are too many users.
     This can probably happen in a GNU system when using NFS. */
  _sys_err[EUSERS] = "Too many users";
#endif
#ifdef EDQUOT
  /* The user's disk quota was exceeded. */
  _sys_err[EDQUOT] = "Disk quota exceeded";
#endif
#ifdef ESTALE
  /* Stale NFS file handle.  This indicates an internal confusion in the NFS
     system which is due to file system rearrangements on the server host.
     Repairing this condition usually requires unmounting and remounting
     the NFS file system on the local host. */
  _sys_err[ESTALE] = "Stale NFS file handle";
#endif
#ifdef EREMOTE
  /* An attempt was made to NFS-mount a remote file system with a file name that
     already specifies an NFS-mounted file.
     (This is an error on some operating systems, but we expect it to work
     properly on the GNU system, making this error code impossible.) */
  _sys_err[EREMOTE] = "Object is remote";
#endif
#ifdef EBADRPC
  /* ??? */
  _sys_err[EBADRPC] = "RPC struct is bad";
#endif
#ifdef ERPCMISMATCH
  /* ??? */
  _sys_err[ERPCMISMATCH] = "RPC version wrong";
#endif
#ifdef EPROGUNAVAIL
  /* ??? */
  _sys_err[EPROGUNAVAIL] = "RPC program not available";
#endif
#ifdef EPROGMISMATCH
  /* ??? */
  _sys_err[EPROGMISMATCH] = "RPC program version wrong";
#endif
#ifdef EPROCUNAVAIL
  /* ??? */
  _sys_err[EPROCUNAVAIL] = "RPC bad procedure for program";
#endif
#ifdef ENOLCK
  /* No locks available.  This is used by the file locking facilities.
     This error is never generated by the GNU system, but
     it can result from an operation to an NFS server running another
     operating system. */
  _sys_err[ENOLCK] = "No locks available";
#endif
#ifdef EFTYPE
  /* Inappropriate file type or format. The file was the wrong type for the
     operation, or a data file had the wrong format.
 
     On some systems chmod returns this error if you try to set the
     sticky bit on a non-directory file. */
  _sys_err[EFTYPE] = "Inappropriate file type or format";
#endif
#ifdef EAUTH
  /* ??? */
  _sys_err[EAUTH] = "Authentication error";
#endif
#ifdef ENEEDAUTH
  /* ??? */
  _sys_err[ENEEDAUTH] = "Need authenticator";
#endif
#ifdef ENOSYS
  /* Function not implemented.  This indicates that the function called is
     not implemented at all, either in the C library itself or in the
     operating system.  When you get this error, you can be sure that this
     particular function will always fail with ENOSYS unless you
     install a new version of the C library or the operating system. */
  _sys_err[ENOSYS] = "Function not implemented";
#endif
#if defined (ENOTSUP) && ENOTSUP != EOPNOTSUPP
  /* Not supported.  A function returns this error when certain parameter
     values are valid, but the functionality they request is not available.
     This can mean that the function does not implement a particular command
     or option value or flag bit at all.  For functions that operate on some
     object given in a parameter, such as a file descriptor or a port, it
     might instead mean that only that specific object (file
     descriptor, port, etc.) is unable to support the other parameters given;
     different file descriptors might support different ranges of parameter
     values.
 
     If the entire function is not available at all in the implementation,
     it returns ENOSYS instead. */
  _sys_err[ENOTSUP] = "Not supported";
#endif
#ifdef EILSEQ
  /* While decoding a multibyte character the function came along an invalid
     or an incomplete sequence of bytes or the given wide character is invalid. */
  _sys_err[EILSEQ] = "Invalid or incomplete multibyte or wide character";
#endif
#ifdef EBACKGROUND
  /* In the GNU system, servers supporting the term protocol return
     this error for certain operations when the caller is not in the
     foreground process group of the terminal.  Users do not usually see this
     error because functions such as read and write translate
     it into a SIGTTIN or SIGTTOU signal. */
  _sys_err[EBACKGROUND] = "Inappropriate operation for background process";
#endif
#ifdef EDIED
  /* In the GNU system, opening a file returns this error when the file is
     translated by a program and the translator program dies while starting
     up, before it has connected to the file. */
  _sys_err[EDIED] = "Translator died";
#endif
#ifdef ED
  /* The experienced user will know what is wrong.
     This error code is a joke. Its perror text is part of the joke.
     Don't change it. */
  _sys_err[ED] = "?";
#endif
#ifdef EGREGIOUS
  /* You did what? */
  _sys_err[EGREGIOUS] = "You really blew it this time";
#endif
#ifdef EIEIO
  /* Go home and have a glass of warm, dairy-fresh milk. */
  _sys_err[EIEIO] = "Computer bought the farm";
#endif
#ifdef EGRATUITOUS
  /* This error code has no purpose. */
  _sys_err[EGRATUITOUS] = "Gratuitous error";
#endif
#ifdef EBADMSG
  /* */
  _sys_err[EBADMSG] = "Bad message";
#endif
#ifdef EIDRM
  /* */
  _sys_err[EIDRM] = "Identifier removed";
#endif
#ifdef EMULTIHOP
  /* */
  _sys_err[EMULTIHOP] = "Multihop attempted";
#endif
#ifdef ENODATA
  /* */
  _sys_err[ENODATA] = "No data available";
#endif
#ifdef ENOLINK
  /* */
  _sys_err[ENOLINK] = "Link has been severed";
#endif
#ifdef ENOMSG
  /* */
  _sys_err[ENOMSG] = "No message of desired type";
#endif
#ifdef ENOSR
  /* */
  _sys_err[ENOSR] = "Out of streams resources";
#endif
#ifdef ENOSTR
  /* */
  _sys_err[ENOSTR] = "Device not a stream";
#endif
#ifdef EOVERFLOW
  /* */
  _sys_err[EOVERFLOW] = "Value too large for defined data type";
#endif
#ifdef EPROTO
  /* */
  _sys_err[EPROTO] = "Protocol error";
#endif
#ifdef ETIME
  /* */
  _sys_err[ETIME] = "Timer expired";
#endif
#ifdef ECANCELED
  /* Operation canceled; an asynchronous operation was canceled before it
     completed. When you call aio_cancel, the normal result is for
     the operations affected to complete with this error. */
  _sys_err[ECANCELED] = "Operation canceled";
#endif
#ifdef ERESTART
  /* */
  _sys_err[ERESTART] = "Interrupted system call should be restarted";
#endif
#ifdef ECHRNG
  /* */
  _sys_err[ECHRNG] = "Channel number out of range";
#endif
#ifdef EL2NSYNC
  /* */
  _sys_err[EL2NSYNC] = "Level 2 not synchronized";
#endif
#ifdef EL3HLT
  /* */
  _sys_err[EL3HLT] = "Level 3 halted";
#endif
#ifdef EL3RST
  /* */
  _sys_err[EL3RST] = "Level 3 reset";
#endif
#ifdef ELNRNG
  /* */
  _sys_err[ELNRNG] = "Link number out of range";
#endif
#ifdef EUNATCH
  /* */
  _sys_err[EUNATCH] = "Protocol driver not attached";
#endif
#ifdef ENOCSI
  /* */
  _sys_err[ENOCSI] = "No CSI structure available";
#endif
#ifdef EL2HLT
  /* */
  _sys_err[EL2HLT] = "Level 2 halted";
#endif
#ifdef EBADE
  /* */
  _sys_err[EBADE] = "Invalid exchange";
#endif
#ifdef EBADR
  /* */
  _sys_err[EBADR] = "Invalid request descriptor";
#endif
#ifdef EXFULL
  /* */
  _sys_err[EXFULL] = "Exchange full";
#endif
#ifdef ENOANO
  /* */
  _sys_err[ENOANO] = "No anode";
#endif
#ifdef EBADRQC
  /* */
  _sys_err[EBADRQC] = "Invalid request code";
#endif
#ifdef EBADSLT
  /* */
  _sys_err[EBADSLT] = "Invalid slot";
#endif
#if defined (EDEADLOCK) && EDEADLOCK != EDEADLK
  /* */
  _sys_err[EDEADLOCK] = "File locking deadlock error";
#endif
#ifdef EBFONT
  /* */
  _sys_err[EBFONT] = "Bad font file format";
#endif
#ifdef ENONET
  /* */
  _sys_err[ENONET] = "Machine is not on the network";
#endif
#ifdef ENOPKG
  /* */
  _sys_err[ENOPKG] = "Package not installed";
#endif
#ifdef EADV
  /* */
  _sys_err[EADV] = "Advertise error";
#endif
#ifdef ESRMNT
  /* */
  _sys_err[ESRMNT] = "Srmount error";
#endif
#ifdef ECOMM
  /* */
  _sys_err[ECOMM] = "Communication error on send";
#endif
#ifdef EDOTDOT
  /* */
  _sys_err[EDOTDOT] = "RFS specific error";
#endif
#ifdef ENOTUNIQ
  /* */
  _sys_err[ENOTUNIQ] = "Name not unique on network";
#endif
#ifdef EBADFD
  /* */
  _sys_err[EBADFD] = "File descriptor in bad state";
#endif
#ifdef EREMCHG
  /* */
  _sys_err[EREMCHG] = "Remote address changed";
#endif
#ifdef ELIBACC
  /* */
  _sys_err[ELIBACC] = "Can not access a needed shared library";
#endif
#ifdef ELIBBAD
  /* */
  _sys_err[ELIBBAD] = "Accessing a corrupted shared library";
#endif
#ifdef ELIBSCN
  /* */
  _sys_err[ELIBSCN] = ".lib section in a.out corrupted";
#endif
#ifdef ELIBMAX
  /* */
  _sys_err[ELIBMAX] = "Attempting to link in too many shared libraries";
#endif
#ifdef ELIBEXEC
  /* */
  _sys_err[ELIBEXEC] = "Cannot exec a shared library directly";
#endif
#ifdef ESTRPIPE
  /* */
  _sys_err[ESTRPIPE] = "Streams pipe error";
#endif
#ifdef EUCLEAN
  /* */
  _sys_err[EUCLEAN] = "Structure needs cleaning";
#endif
#ifdef ENOTNAM
  /* */
  _sys_err[ENOTNAM] = "Not a XENIX named type file";
#endif
#ifdef ENAVAIL
  /* */
  _sys_err[ENAVAIL] = "No XENIX semaphores available";
#endif
#ifdef EISNAM
  /* */
  _sys_err[EISNAM] = "Is a named type file";
#endif
#ifdef EREMOTEIO
  /* */
  _sys_err[EREMOTEIO] = "Remote I/O error";
#endif
#ifdef ENOMEDIUM
  /* */
  _sys_err[ENOMEDIUM] = "No medium found";
#endif
#ifdef EMEDIUMTYPE
  /* */
  _sys_err[EMEDIUMTYPE] = "Wrong medium type";
#endif
#ifdef ENOKEY
  /* */
  _sys_err[ENOKEY] = "Required key not available";
#endif
#ifdef EKEYEXPIRED
  /* */
  _sys_err[EKEYEXPIRED] = "Key has expired";
#endif
#ifdef EKEYREVOKED
  /* */
  _sys_err[EKEYREVOKED] = "Key has been revoked";
#endif
#ifdef EKEYREJECTED
  /* */
  _sys_err[EKEYREJECTED] = "Key was rejected by service";
#endif
#ifdef EOWNERDEAD
  /* */
  _sys_err[EOWNERDEAD] = "Owner died";
#endif
#ifdef ENOTRECOVERABLE
  /* */
  _sys_err[ENOTRECOVERABLE] = "State not recoverable";
#endif

  for ( container_type::reverse_iterator i = _sys_err.rbegin(); i != _sys_err.rend(); ++i ) {
    if ( *i != 0 ) {
      _last_value = _sys_err.rend() - i;
      --_last_value;
      break;
    }
  }
}

static _SysErrInit _syserr;

static const _STLP_STD::string _unknown( "Code not specified in this category" );

class posix_error_category :
    public _STLP_STD::error_category
{
  public:
    virtual const char* name() const;
    virtual _STLP_STD::string message( int err ) const;
};

const char* posix_error_category::name() const
{
  return "POSIX";
}

_STLP_STD::string posix_error_category::message( int err ) const
{
  // bad: allocation present, so no memory may happens...
  return (err >= 0) && (err <= _syserr._last_value) && (_syserr._sys_err[err] != 0) ? _STLP_STD::string( _syserr._sys_err[err] ) : _unknown;
}

class system_error_category :
    public _STLP_STD::error_category
{
  public:
    virtual const char* name() const;
    virtual _STLP_STD::string message( int err ) const;

};

const char* system_error_category::name() const
{
  return "system";
}

_STLP_STD::string system_error_category::message( int err ) const
{
  // bad: allocation present, so no memory may happens...
  return (err >= 0) && (err <= _syserr._last_value) && (_syserr._sys_err[err] != 0) ? _STLP_STD::string( _syserr._sys_err[err] ) : _unknown;
}

static posix_error_category _posix_error_category;
static system_error_category _system_error_category;

} // namespace detail

_STLP_BEGIN_NAMESPACE

using namespace detail;

error_category::~error_category()
{ }

error_condition error_category::default_error_condition( int err ) const
{
  return error_condition( err, *this );
}

bool error_category::equivalent( int code, const error_condition& cnd ) const
{
  return default_error_condition( code ) == cnd;
}

bool error_category::equivalent( const error_code& code, int cnd ) const
{
  return (*this == code.category()) && (code.value() == cnd);
}

bool error_category::operator ==( const error_category& cat ) const
{
  return this == &cat;
}

bool error_category::operator !=( const error_category& cat ) const
{
  return this != &cat;
}

bool error_category::operator <( const error_category& cat ) const
{
  return this < &cat;
}

_STLP_DECLSPEC const error_category& get_posix_category()
{
  return ::detail::_posix_error_category;
}

_STLP_DECLSPEC const error_category& get_system_category()
{
  return ::detail::_system_error_category;
}

_STLP_DECLSPEC error_code::error_code() :
    v( 0 ),
    c( &::detail::_system_error_category )
{ }

_STLP_DECLSPEC error_code::error_code( int val, const error_category& cat ) :
    v( val ),
    c( &cat )
{ }

_STLP_DECLSPEC void error_code::assign( int val, const error_category& cat )
{
  v = val;
  c = &cat;
}

_STLP_DECLSPEC void error_code::clear()
{
  v = 0;
  c = &::detail::_system_error_category;
}

namespace posix_error {

_STLP_DECLSPEC error_code make_error_code( posix_errno err )
{ return error_code( err, ::detail::_posix_error_category ); }

_STLP_DECLSPEC error_condition make_error_condition( posix_errno err )
{ return error_condition( err, ::detail::_posix_error_category ); }

} // namespace posix_error

_STLP_DECLSPEC bool operator <( const error_code& l, const error_code& r )
{
  return l.category() == r.category() ? l.value() < r.value() : l.category() < r.category();
}

_STLP_DECLSPEC error_condition::error_condition() :
    v( 0 ),
    c( &::detail::_posix_error_category )
{ }

_STLP_DECLSPEC error_condition::error_condition( int val, const error_category& cat ) :
    v( val ),
    c( &cat )
{ }

_STLP_DECLSPEC void error_condition::assign( int val, const error_category& cat )
{
  v = val;
  c = &cat;
}

_STLP_DECLSPEC void error_condition::clear()
{
  v = 0;
  c = &::detail::_posix_error_category;
}

_STLP_DECLSPEC bool operator <( const error_condition& l, const error_condition& r )
{
  return l.category() == r.category() ? l.value() < r.value() : l.category() < r.category();
}

_STLP_DECLSPEC bool operator ==( const error_code& l, const error_code& r )
{ return l.category() == r.category() && l.value() == r.value(); }

_STLP_DECLSPEC bool operator ==( const error_code& l, const error_condition& r )
{ return l.category().equivalent( l.value(), r ) || r.category().equivalent( l, r.value() ); }

_STLP_DECLSPEC bool operator ==( const error_condition& l, const error_code& r )
{ return r.category().equivalent( r.value(), l ) || l.category().equivalent( r, l.value() ); }

_STLP_DECLSPEC bool operator ==( const error_condition& l, const error_condition& r )
{ return l.category() == r.category() && l.value() == r.value(); }

_STLP_DECLSPEC bool operator !=( const error_code& l, const error_code& r )
{ return !(l == r); }

_STLP_DECLSPEC bool operator !=( const error_code& l, const error_condition& r )
{ return !(l == r); }

_STLP_DECLSPEC bool operator !=( const error_condition& l, const error_code& r )
{ return !(l == r); }

_STLP_DECLSPEC bool operator !=( const error_condition& l, const error_condition& r )
{ return !(l == r); }

// char _stack_buf[4096];

system_error::system_error( error_code code, const string& what ) :
    runtime_error( what ),
    ecode_( code.value(), code.category() ),
    _dbuf( 0 )
{
  // stringstream s;
  // xmt::callstack( cerr );
  // strcpy( _stack_buf, s.str().c_str() );
}

system_error::system_error( error_code code ) :
    runtime_error( "" ),
    ecode_( code.value(), code.category() ),
    _dbuf( 0 )
{
  // stringstream s;
  // xmt::callstack( cerr );
  // strcpy( _stack_buf, s.str().c_str() );
}

system_error::system_error( int code, const error_category& category,
                            const string& what ) :
    runtime_error( what ),
    ecode_( code, category ),
    _dbuf( 0 )
{
  // stringstream s;
  // xmt::callstack( cerr );
  // strcpy( _stack_buf, s.str().c_str() );
}

system_error::system_error( int code, const error_category& category ) :
    runtime_error( "" ),
    ecode_( code, category ),
    _dbuf( 0 )
{
  // stringstream s;
  // xmt::callstack( cerr );
  // strcpy( _stack_buf, s.str().c_str() );
}

system_error::~system_error() throw()
{
  if ( _dbuf ) {
    free( _dbuf );
  }
}

const char* system_error::what() const throw()
{
  size_t sz = strlen( runtime_error::what() );
  size_t sz_add = sz + ecode_.message().length() + (sz > 0 ? 3 : 1); // + ": ", not \0

  // sz_add += strlen( _stack_buf );

  if ( sz_add < _bufsize ) {
    if ( sz > 0 ) {
      memcpy( _buf, runtime_error::what(), sz );
      _buf[sz++] = ':';
      _buf[sz++] = ' ';
    }
    memcpy( _buf + sz, ecode_.message().data(), ecode_.message().length() );
    // memcpy( _buf + sz + ecode_.message().length() + (sz > 0 ? 3 : 1), _stack_buf, strlen( _stack_buf ) );
    _buf[sz_add - 1] = 0;
  } else {
    _dbuf = static_cast<char *>(malloc( sz_add ));
    if ( _dbuf != 0 ) {
      if ( sz > 0 ) {
        memcpy( _dbuf, runtime_error::what(), sz );
        _dbuf[sz++] = ':';
        _dbuf[sz++] = ' ';
      }
      memcpy( _dbuf + sz, ecode_.message().data(), ecode_.message().length() );
      // memcpy( _dbuf + sz + ecode_.message().length() + (sz > 0 ? 3 : 1), _stack_buf, strlen( _stack_buf ) );
      _dbuf[sz_add - 1] = 0;
      return _dbuf;
    }
    if ( sz > 0 ) {
      strncpy( _buf, runtime_error::what(), _bufsize - 1 );
    }
    if ( sz < (_bufsize - 1) ) {
      if ( sz > 0 ) {
        _buf[sz++] = ':';
      }
      if ( sz < (_bufsize - 1) ) {
        if ( sz > 0 ) {
          _buf[sz++] = ' ';
        }
        if ( sz < (_bufsize - 1) ) {
          strncpy( _buf + sz, ecode_.message().data(), _bufsize - sz - 1 );
        }
      }
    }
    _buf[_bufsize - 1] = 0;
  }

  return _buf;
}

_STLP_END_NAMESPACE
