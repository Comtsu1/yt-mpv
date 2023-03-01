#ifndef UTILS_H
#define UTILS_H

#include <linux/limits.h> // for NAME_MAX PATH_MAX (file handling)
#include "colors.h"       // for warning, note and error macros

// Colored Signals
#define __WARN() fprintf(stderr, ANSI_COLOR_YELLOW "(%s) Warning [Line: %d]: "  ANSI_COLOR_RESET, __FILE__, __LINE__)
#define __ERR()  fprintf(stderr, ANSI_COLOR_RED    "(%s) Error [Line: %d]: "    ANSI_COLOR_RESET, __FILE__, __LINE__)
#define __NOTE() fprintf(stdout, ANSI_COLOR_CYAN   "Note: "              ANSI_COLOR_RESET)

// Print using colored signals
#define WARN(...) __WARN(); \
    fprintf(stderr, __VA_ARGS__);
#define ERR(...) __ERR(); \
    fprintf(stderr, __VA_ARGS__);
#define NOTE(...) __NOTE(); \
    fprintf(stdout, __VA_ARGS__);

#endif // UTILS_H
