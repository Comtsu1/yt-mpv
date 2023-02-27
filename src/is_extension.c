#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "is_match.h"

// redef
#define LENLIM 256

#define __IS_EXTENSION_PRINT 0

bool is_extension(const char *const fname, const char *const extension)
{
    if(__IS_EXTENSION_PRINT) printf("File: %s\n", fname);

    // we get the extension pointer
    const char *const find = strrchr(fname, '.');
    // See if the file has our wanted extension
    if(find == NULL)
    {
        if(__IS_EXTENSION_PRINT) printf("Couldn't process \"%s\" ...\n", fname);
        return 0;
    }

    if(__IS_EXTENSION_PRINT) printf("Processed file \"%s\","
            "with extension \"%s\"\n", fname, find+1);

    int result = strncmp(find+1, extension, strnlen(extension, LENLIM));
    
    //printf("\n\tV:%d\n", result == 0);
    // return the result
    return (result == 0);
}
