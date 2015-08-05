/*
 * newlib.h
 *
 *  Created on: Mar 3, 2015
 *      Author: mailmindlin
 */

#ifndef NEWLIB_NEWLIB_H_
#define NEWLIB_NEWLIB_H_

#include <errno.h>
//#include "sbrk.cpp"

#ifndef __REALCOMP__
#warning "NO REALCOMP!"
static struct stat{
uint32_t st_mode;
};
extern typedef char* caddr_t;//might actually be the real definition of caddr_t
#else
//include stuff
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/types.h>
#endif
#include <stdint.h>

#undef errno
extern int errno;
#ifndef EINVAL
extern int EINVAL;
#endif
#ifndef S_IFCHR
extern int S_IFCHR;
#endif

extern unsigned int scheduler_getPID();
//make it an extern if it's using c++
#ifdef __cplusplus
extern "C" {
#endif
/**
 * No idea what this is, ,but removing it will break it at linktime.
 */
void * __dso_handle;

typedef uint32_t file_t;
/**
 * Should be declared in Kernel.cpp
 */
extern void kernel_shutdown(void);
/**
 * Abort the OS
 */
extern void abort(void);
/**
 * Called on kernel exit
 * @param code exit code
 */
extern void _exit(int code);
/**
 * Close file.
 * @param file file descriptor
 * @return success (0 for success)
 */
extern int _close(file_t file);
/**
 * Status of an open file
 * @param file file descriptor
 * @param st status
 * @return 0 for success
 */
extern int _fstat(file_t file, struct stat *st);
/**
 * Get current PID
 * @return PID
 */
extern int _getpid(void);
/**
 * Query if output stream is a terminal
 * @param file file descriptor
 * @return 1 if it is a terminal, 0 if not, negative number if error
 */
extern int _isatty(file_t file);
/**
 * Send a signal to the given process
 * @param pid PID to kill
 * @param sig signal to send
 * @return success (0 for good)
 */
extern int _kill(int pid, int sig);
/**
 * Seek position in file
 * @param file file descriptor
 * @param ptr ammount to seek
 * @param dir direction to seek
 * @return resulting offset (bytes) from beginning of file, or -1 for error.
 */
extern int _lseek(file_t file, int ptr, int dir);
/**
 * Read data from file into buffer
 * @param file file descriptor
 * @param buffer buffer to read to
 * @param len length of buffer
 * @return
 */
extern int _read(file_t file, char *buffer, int len);
/**
 * Increase program data space
 * @param incr ammount to increase by
 * @return pointer to start of new memory
 */
extern void* _sbrk(int incr);
/**
 * Write data from buffer to file
 * @param file file descriptor
 * @param buffer to read from
 * @param len length of buffer
 * @return
 */
extern int _write(file_t file, char *buffer, int len);
#ifdef __cplusplus
}
#endif
#include "sbrk.cpp"
#endif /* NEWLIB_NEWLIB_H_ */
