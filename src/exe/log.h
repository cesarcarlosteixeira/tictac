#ifndef LOG_H
#define LOG_H
#include <stdio.h>
#include <stdlib.h>


/*
 * Displays a message to stderr; prints
 * addtional information on debug mode.
*/
static inline void log_error(
  const char *message, 
  [[maybe_unused]] int line, 
  [[maybe_unused]] const char *func
) {

#ifdef DEBUG
   fprintf(
     stderr,
     "error: %d:%s: %s",
     line,
     func,
     message
   );

#else
  fprintf(stderr, "error: %s", message);
#endif
}
#endif
