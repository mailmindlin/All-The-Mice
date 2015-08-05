/*
 * newlib.c
 *
 *  Created on: Feb 26, 2015
 *      Author: mailmindlin
 */

#ifndef NEWLIB_NEWLIB_H_
#include "newlib.h"
#endif
/**
 * Abort the OS
 */
extern void abort(void) {
	while(1);
}
/**
 * Called on kernel exit
 * @param code exit code
 */
extern void _exit(int code) {
	kernel_shutdown();
	abort();
}
/**
 * Close file.
 * @param file file descriptor
 * @return success (0 for success)
 */
extern int _close(file_t file) {
	return -1;
}
/**
 * Status of an open file
 * @param file file descriptor
 * @param st status
 * @return 0 for success
 */
extern int _fstat(file_t file, struct stat *st) {
	st->st_mode = S_IFCHR;
	return 0;
}
/**
 * Get current PID
 * @return PID
 */
extern int _getpid(void) {
	return 1;//scheduler_getPID();
}
/**
 * Query if output stream is a terminal
 * @param file file descriptor
 * @return 1 if it is a terminal, 0 if not, negative number if error
 */
extern int _isatty(file_t file) {
	return 1;
}
/**
 * Send a signal to the given process
 * @param pid PID to kill
 * @param sig signal to send
 * @return success (0 for good)
 */
extern int _kill(int pid, int sig) {
	errno = EINVAL;
	return -1;
}
/**
 * Seek position in file
 * @param file file descriptor
 * @param ptr ammount to seek
 * @param dir direction to seek
 * @return resulting offset (bytes) from beginning of file, or -1 for error.
 */
extern int _lseek(file_t file, int ptr, int dir) {
	return 0;
}
/**
 * Read data from file into buffer
 * @param file file descriptor
 * @param buffer buffer to read to
 * @param len length of buffer
 * @return
 */
extern int _read(file_t file, char *buffer, int len) {
	return 0;
}
/**
 * Increase program data space
 * @param incr amount to increase by
 * @return pointer to start of new memory
 */
/*
extern caddr_t _sbrk(int incr) {
	unsigned int* stack_ptr = ({ register unsigned int* arg0 __asm("sp"); arg0; });
	extern char _end; // Defined by the linker
	static char *heap_end;
	char *prev_heap_end;

	if (heap_end == 0) {
		heap_end = &_end;
	}
	prev_heap_end = heap_end;
	if (((unsigned int)heap_end + incr) > *stack_ptr) {
		_write(1, "Heap and stack collision\n", 25);
		abort();
	}

	heap_end += incr;
	return (caddr_t) prev_heap_end;
}*/
/**
 * Write data from buffer to file
 * @param file file descriptor
 * @param buffer to read from
 * @param len length of buffer
 * @return
 */
extern int _write(file_t file, char *buffer, int len) {
	int todo;

	for (todo = 0; todo < len; todo++) {
//		outbyte(*ptr++);
	}
	return len;
}
