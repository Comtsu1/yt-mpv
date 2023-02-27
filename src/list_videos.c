#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>

#include "is_extension.h"

#include "colors.h"

#define LENLIM 256

void list_videos(const char *const path, const char *const ext)
{ // List videos from a directory
  // TODO currently prints everything
  // fix!

    char current_path[LENLIM];

// Check if the path is null
    if(!path)
    {
        WARN();
        fprintf(stderr, "Path is NULL, defaulting to \"~/Videos\"\n");
    // Copy default string
    // ~/Videos
        snprintf(current_path, LENLIM,"%s", ".");
    }
    else
    {
        snprintf(current_path, LENLIM, "%s", path);
    }
// Check if extension if NULL
    if(!ext)
    {
        ERR();
        fprintf(stderr, "Extension for searching in directory is empty!...\n");
    }

    bool file_found = 0;

    DIR *d;
    struct dirent *dir;
    
// open dir
    d = opendir(current_path);

// If we have such a directory then open it
    if(d)
    {
    // Opened the directory
    // Read files from selected dir
        while((dir = readdir(d)) != NULL)
        {
        // check if the file is just a
        // file and not a dir
            if( dir->d_type == DT_REG )
            { 
            // See if file has the extension webm ig
                if(is_extension(dir->d_name, "mkv"))
                {
                // Mark that we found a file
                    file_found = 1;
                    fprintf(stdout, "Found file: %s\n", dir->d_name);
                }
            }
        }
    // Close the directory when we are done
        closedir(d);
    }
    else
    { 
    // Something went wrong
        ERR();
        fprintf(stderr, "Couldn't open \"%s\"\n", current_path);
        fprintf(stderr, "Errno code: %d => "
                "%s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

// No errors
// but no files found
    if(!file_found)
    {
        NOTE();
        fprintf(stdout, "No files found with extension \"%s\"\n", "mkv"); 
    }
}
