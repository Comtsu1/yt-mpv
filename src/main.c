/*
 *            yt-mpv
 * A tool that lets users download
 *    and keep track of videos
 */

/* TODO LIST
 * -----------------------------------------
 *  1. Implement video viewing when
 *  calling the program without arguments
 *  2. Download video from yt ID
 *  3. Categorise videos
 *  4. mpv integration(see from yt-mpv
 *  where you left the video)
 *  (Maybe) 5. Automatic download
 *  of new uploads from a channel
 * -----------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <dirent.h>

#include "is_match.h"
#include "is_extension.h"

#include "colors.h"

//////////////
/* Commands */
//////////////
//#include "commands/show_help.h"
#include "commands/list_videos.h"
//#include "commands/download_video.h"

#define SIZE(x) (sizeof(x) / sizeof(x[0]))
#define LENLIM 256

/////////////
/*Functions*/
/////////////
FILE* create_config_file(const char *const path)
{
// Check if file path is NULL
    if(path == NULL)
    {
        ERR();
        fprintf(stderr, "Can't create config file, path is empty...\n");
        return NULL;
    }
// Create config file
    FILE *file;
    file = fopen(path, "w");
// Check if we created the file
    if(!path)
    {
    // Couldn't create file
        ERR();
        fprintf(stderr, "Couldn't create config file \"%s\"... %s\n",path, strerror(errno));
        return NULL;
    }
// Created config file
    NOTE();
    fprintf(stdout, "Create config file \"%s\"...\n", path);

    return file;
}

// FIXME maybe not FILE const...?
bool parse_config_file(FILE *const file)
{

    // TODO 

// No problems found
    return 1;
}

bool open_config_file(const char *const config_f)
{
    // TODO
    // return pointer to file???!?!

    FILE *file;
// Opening file
    file = fopen(config_f, "r");
// Check if file doesn't exist
    if(!file)
    {
    // Warn user that the files
    // wasn't created
        WARN();
        fprintf(stderr, "Config file \"%s\" wasn't found, creating new empty file...\n", config_f);
    // Create new file
        if( !(file = create_config_file(config_f)) )
            return 0;
    }

    // TODO parse config_file
    parse_config_file(file);

// close file
// we dont need it
    fclose(file);
    
// return 1 for successfully opening
// the file
    return 1;
}

/* Variables */
static char folder_path[LENLIM] = ".";
static char config_file[LENLIM] = ".watchrc";

/////////////////////////////////////////////////////////
/*                                                     */
/*                      TODO                           */
/*                Redo main function                   */
/////////////////////////////////////////////////////////
// for the start of this project
// we won't be using argc or argv
// as they have completly an utterly
// made me want to throw myself of the
// 15th floor
int main()
{
    char open_config[LENLIM*2];
// make config file path
    snprintf(open_config, LENLIM*2, "%s/%s", folder_path, config_file);

// Try to open/create config file
    if ( !open_config_file(open_config) )
    {
    // Something very wrong happened
        fprintf(stderr, "Exiting...\n");
        exit(EXIT_FAILURE);
    }

    list_videos(folder_path);


// Exit program
// Everything is going
// OK
    exit(EXIT_SUCCESS);
}






/*

int main(int argc, char *argv[])
{
// Check if the number of arguments is less than one then show help page
    // implement video viewing function
    if(argc < 2) show_help(-1, -1, argv);

// Iterators
    int i;


// We skip over the first one as it is
// the name of the program
// Ex:
// Input: nasm -c shit.asm -o shit.bin
// argv[0] = "nasm"
    for(i = 1; i < argc; ++i)
    {
        // Check if argument is command
        if(argv[i][0] == '-')
        { // Search for a match
            int cnt;
            bool c_found = 0;
            const char *cmd = argv[i] + 1;

            // Search all the commands for a match
            for(cnt=0; cnt<SIZE(gcommands) && !c_found; ++cnt)
            {
                // Search through all the commands
                // If found, call function stored in struct
                if(is_match(cmd, gcommands[cnt].names))
                {
                    c_found = 1;
                    gcommands[cnt].func(argc, i, argv);
                }
            }
            // We have't found the command, exit
            if(!c_found)
            {
                    fprintf(stdout, "Command \"%s\" was not found, exiting...\n", argv[i]);
                    exit(EXIT_FAILURE);
            }
        }
    }

// Exit program
// Everything is going
// OK
    exit(EXIT_SUCCESS);
}
*/
