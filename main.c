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

#define SIZE(x) (sizeof(x) / sizeof(x[0]))
#define LENLIM 256

/* Function declarations */
bool is_match(const char *const needle, const char *const *const stack);

void show_help(int all, int index, char ** buf, ...);
void list_videos(int all, int index, char ** dir, ...);
void download_video(int all, int index, char ** buf, ...);

///////////////
/* Functions */
///////////////
bool is_match(const char *const needle, const char *const *const stack)
{ // sees if a word is contained in an array or words
    int cnt = 0;    
    bool found_match = 1;
    const char *p1, *p2;

    while(stack[cnt] != NULL)
    {   found_match = 1;


        // copy of needle
        p1 = needle;
        p2 = stack[cnt];

        printf("n:%s, s:%s\n", p1, p2);
        printf("\t%d\n", *p1 && *p2);
        
        // Check if strings are empty (prob something went wrong) FIXME later
        if(!(*p1 && *p2)) return 0;

        // See if we are the end of
        // our strings
        while(*p1 && *p2)
        {
            printf("\t%d(%c),%d(%c)\n", *p1, *p1, *p2, *p2);
            if(*p1 != *p2) found_match = 0;
            p1++;
            p2++;
        } 

        // Check for tralling characters
        // Ex: neddle: he, stack: h
        // h == h
        // stack is now \0 so the while stops
        // but we still didnt compare 'e' from the needle
        if(*p1 || *p2) found_match = 0;

        //printf("c:%d, %d\n", *p1, *p2);

        // See if we found
        // our match
        if(found_match) return 1;
        
        // next word
        cnt++;
    }

    // No matches found
    return 0;
}

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
            // We dont want to include 
            if(!is_match(dir->d_name, ".") != 0 && !is_match(dir->d_name, ".."))
                printf("%s\n", dir->d_name);
        }
        // Close the directory when we are done
        closedir(d);
    }
    else
    { // Something went wrong
        printf("Errno code: %d", errno);
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
            int cnt, cmd_cnt, r1, r2;
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
