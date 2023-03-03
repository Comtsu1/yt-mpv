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
#include <linux/limits.h>

#include "playlist.h"
#include "is_match.h"
#include "is_extension.h"
#include "utils.h"

//////////////
/* Commands */
//////////////
//#include "commands/show_help.h"
//#include "commands/download_video.h"

#define SIZE(x) (sizeof(x) / sizeof(x[0]))

/////////////
/*Functions*/
/////////////
FILE* create_config_file(const char *const path)
{
// Check if file path is NULL
    if(path == NULL)
    {
        ERR("Can't create config file, path is empty...\n");
        return NULL;
    }
// Create config file
    FILE *file;
    file = fopen(path, "w");
// Check if we created the file
    if(!path)
    {
    // Couldn't create file
        ERR("Couldn't create config file \"%s\"... %s\n",path, strerror(errno));
        return NULL;
    }
// Created config file
    NOTE("Create config file \"%s\"...\n", path);

    return file;
}

// FIXME maybe not FILE const...?
bool parse_config_file(FILE *const file)
{

    // TODO 

// No problems found
    return 1;
}

// change to return FILE*
// TODO 
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
        WARN("Config file \"%s\" wasn't found, creating new empty file...\n", config_f);
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
static char folder_path[NAME_MAX+1] = ".";
static char config_file[NAME_MAX+1] = ".watchrc";

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
    char open_config[PATH_MAX];
// make config file path
    snprintf(open_config, PATH_MAX, "%s/%s", folder_path, config_file);

// Try to open/create config file
    if ( !open_config_file(open_config) )
    {
    // Something very wrong happened
        fprintf(stderr, "Exiting...\n");
        exit(EXIT_FAILURE);
    }

    Playlist* p;
    p = create_playlist(10);
    if(p != NULL)
    {
        char *a = "Hello",
             *b = "No";
        p->videos[0] = a;
        p->videos[1] = b;

        printf("%s, %s", p->videos[0] = a, 
                p->videos[1] = b);
    }

    free_playlist(p);

// Exit program
// Everything is going
// OK
    exit(EXIT_SUCCESS);
}
