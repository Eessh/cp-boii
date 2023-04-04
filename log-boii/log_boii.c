#include "log_boii.h"
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

#ifdef LOG_BOII__COLORED_LOGS
#define COLOR_TRACE "\x1b[37m"
#define COLOR_DEBUG "\x1b[36m"
#define COLOR_INFO "\x1b[32m"
#define COLOR_WARN "\x1b[35m"
#define COLOR_ERROR "\x1b[33m"
#define COLOR_FATAL "\x1b[31m"
#define COLOR_RESET "\x1b[0m"
#endif

/*
 * Returns string format of `log_level`.
 *
 */
const char*
log_level_string(log_level level)
{
  switch (level) {
    case LOG_TRACE:
      return "TRACE";
    case LOG_DEBUG:
      return "DEBUG";
    case LOG_INFO:
      return "INFO ";
    case LOG_WARN:
      return "WARN ";
    case LOG_ERROR:
      return "ERROR";
    default:
      break;
  }
  return "FATAL";
}

/*
 * Returns time struct for current time.
 *
 */
struct tm*
time_info()
{
  time_t rawtime;
  struct tm* time_info;

  time(&rawtime);
  time_info = localtime(&rawtime);

  return time_info;
}

/*
 * Base function for all logging functions.
 *
 * Use `log_level` properly :)
 *
 * References how to use log levels properly:
 * https://stackoverflow.com/questions/2031163/when-to-use-the-different-log-levels
 * https://betterstack.com/community/guides/logging/log-levels-explained/
 *
 */
void
log_boii(log_level level,
         const char* function,
         const char* file,
         int line,
         const char* format_string,
         ...)
{
  struct tm* timeinfo = time_info();

#ifdef LOG_BOII__COLORED_LOGS
  switch (level) {
    case LOG_TRACE: {
      fprintf(stderr,
              "[%d:%d:%d] " COLOR_TRACE "%s" COLOR_RESET " %s:%s:%d: ",
              timeinfo->tm_hour,
              timeinfo->tm_min,
              timeinfo->tm_sec,
              log_level_string(level),
              function,
              file,
              line);
      break;
    }
    case LOG_DEBUG: {
      fprintf(stderr,
              "[%d:%d:%d] " COLOR_DEBUG "%s" COLOR_RESET " %s:%s:%d: ",
              timeinfo->tm_hour,
              timeinfo->tm_min,
              timeinfo->tm_sec,
              log_level_string(level),
              function,
              file,
              line);
      break;
    }
    case LOG_INFO: {
      fprintf(stderr,
              "[%d:%d:%d] " COLOR_INFO "%s" COLOR_RESET " %s:%s:%d: ",
              timeinfo->tm_hour,
              timeinfo->tm_min,
              timeinfo->tm_sec,
              log_level_string(level),
              function,
              file,
              line);
      break;
    }
    case LOG_WARN: {
#ifdef LOG_BOII__HIGHLIGHT_WARN_ERROR_FATAL_STRINGS
      fprintf(stderr,
              "[%d:%d:%d] " COLOR_WARN "%s %s:%s:%d: " COLOR_RESET,
              timeinfo->tm_hour,
              timeinfo->tm_min,
              timeinfo->tm_sec,
              log_level_string(level),
              function,
              file,
              line);
#else
      fprintf(stderr,
              "[%d:%d:%d] " COLOR_WARN "%s" COLOR_RESET " %s:%s:%d: ",
              timeinfo->tm_hour,
              timeinfo->tm_min,
              timeinfo->tm_sec,
              log_level_string(level),
              function,
              file,
              line);
#endif
      break;
    }
    case LOG_ERROR: {
#ifdef LOG_BOII__HIGHLIGHT_WARN_ERROR_FATAL_STRINGS
      fprintf(stderr,
              "[%d:%d:%d] " COLOR_ERROR "%s %s:%s:%d: " COLOR_RESET,
              timeinfo->tm_hour,
              timeinfo->tm_min,
              timeinfo->tm_sec,
              log_level_string(level),
              function,
              file,
              line);
#else
      fprintf(stderr,
              "[%d:%d:%d] " COLOR_ERROR "%s" COLOR_RESET " %s:%s:%d: ",
              timeinfo->tm_hour,
              timeinfo->tm_min,
              timeinfo->tm_sec,
              log_level_string(level),
              function,
              file,
              line);
#endif
      break;
    }
    case LOG_FATAL: {
#ifdef LOG_BOII__HIGHLIGHT_WARN_ERROR_FATAL_STRINGS
      fprintf(stderr,
              "[%d:%d:%d] " COLOR_FATAL "%s %s:%s:%d: " COLOR_RESET,
              timeinfo->tm_hour,
              timeinfo->tm_min,
              timeinfo->tm_sec,
              log_level_string(level),
              function,
              file,
              line);
#else
      fprintf(stderr,
              "[%d:%d:%d] " COLOR_FATAL "%s" COLOR_RESET " %s:%s:%d: ",
              timeinfo->tm_hour,
              timeinfo->tm_min,
              timeinfo->tm_sec,
              log_level_string(level),
              function,
              file,
              line);
#endif
      break;
    }
    default:
      break;
  }
#else
  // printing usual stuff: time, log level, function, file, line
  fprintf(stderr,
          "[%d:%d:%d] %s %s:%s:%d: ",
          timeinfo->tm_hour,
          timeinfo->tm_min,
          timeinfo->tm_sec,
          log_level_string(level),
          function,
          file,
          line);
#endif

  // handling variable arguments
  va_list format_args;
  va_start(format_args, format_string);
#ifdef LOG_BOII__HIGHLIGHT_WARN_ERROR_FATAL_STRINGS
  if (level == LOG_WARN) {
    fprintf(stderr, COLOR_WARN);
  } else if (level == LOG_ERROR) {
    fprintf(stderr, COLOR_ERROR);
  } else if (level == LOG_FATAL) {
    fprintf(stderr, COLOR_FATAL);
  }
#endif
  vfprintf(stderr, format_string, format_args);
#ifdef LOG_BOII__HIGHLIGHT_WARN_ERROR_FATAL_STRINGS
  fprintf(stderr, COLOR_RESET);
#endif
  va_end(format_args);

  fprintf(stderr, "\n");
}
