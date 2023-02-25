/*
 *            yt-mpv
 * A tool that lets users download
 *    and keep track of videos
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <dirent.h>

#include "is_match.h"
#include "is_extension.h"

#define SIZE(x) (sizeof(x) / sizeof(x[0]))
#define LENLIM 256

void show_help(int all, int index, char ** buf, ...);
void list_videos(int all, int index, char ** dir, ...);
void download_video(int all, int index, char ** buf, ...);

///////////////
/* Functions */
///////////////


void show_help(int all, int index, char ** buf, ...)
{ // Show help when no arguments are presented
    fprintf(stdout, "This is the help page:"
		    "\n\t-h(elp)\t\t\tHelp"
            "\n\t-d(ownload)\t\tDownloads Youtube link ID" // TODO
            "\n\t-l(ist)\t\t\tLists all videos in a directory(Default \".\")");
// Exit our program
// as the user didn't put enough info
// or
// wanted to see help page
    exit(EXIT_SUCCESS);
}

void list_videos(int all, int index, char ** buf, ...)
{ // List videos from a directory
  // TODO currently prints everything
  // fix!
    char path[LENLIM];
    
    const char * dirsub[] = {".", "..", NULL};

    // Check if we are at the end of the array and default to .
    if (index+1 == all) strncpy(path, ".", LENLIM);
    // Check if the user didnt provide a path
    // and if yes then we pressume its directory "."
    else if(buf[index+1][0] == '-') strncpy(path, ".", LENLIM);
    // if none of the above just copy the next argv
    else strncpy(path, buf[index + 1], LENLIM);


    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    // If we have such a directory then open it
    if(d)
    { // Opened the directory
        // Read files from selected dir
        while((dir = readdir(d)) != NULL)
        {
            // Check if we have dir "." or ".."
            if(!is_match(dir->d_name, dirsub))
            { 
                // See if file has the extension webm ig
                if(is_extension(dir->d_name, "mkv"))
                    printf("%s\n", dir->d_name);
            }
        }
        // Close the directory when we are done
        closedir(d);
    }
    else
    { // Something went wrong
        printf("Errno code: %d\n"
                "Please visit %s"
                "\nto see the error code", errno, "https://www.cisco.com/c/en/us/td/docs/ios/sw_upgrades/interlink/r2_0/unpremsg/mucsock.html");
    }

}

void download_videos(int all, int index, char **buf, ...)
{ // Downloads selected videos (through ID link)
  // TODO
}

/////////////
/* Structs */
/////////////

struct Video
{ // TODO
    char *name;
};
struct Command
{
    int ab;
    const char *const names[16];
    void (*func)(int, int, char **, ...);
};


typedef struct Video video;
typedef struct Command command;


/* Variables */
static char file_path[LENLIM] = "~/Videos";

static const command gcommands[] =
{
    {2, .names={"h", "help"}, &show_help},
    {2, .names={"l", "list"}, &list_videos},
};

int main(int argc, char *argv[])
{
/* Check if the number of arguments is less than one then show help page*/
    if(argc < 2) show_help(-1, -1, argv);

// Iterators
    int i, j;


// We skip over the first one as it is
// the name of the program
// Ex:
// Input: nasm -c shit.asm -o shit.bin
// argv[1] = "nasm"
    for(i = 1; i < argc; ++i)
    {
        // Check if argument is command
        if(argv[i][0] == '-')
        { // Search for a match
        // Search all the commands for a match
            int cnt;
            bool c_found = 0;
            const char *cmd = argv[i] + 1;

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
            if(!c_found)
            {
                    printf("Command \"%s\" was not found, exiting...", argv[i]);
                    exit(EXIT_FAILURE);
            }
        }
    }

// Exit program
// Everything is going
// OK
    exit(EXIT_SUCCESS);
}
