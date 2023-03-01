#include <stdio.h>
#include <stdlib.h>
#include <linux/limits.h>
#include <dirent.h>
#include <string.h>

#include "playlist.h"
#include "utils.h"

Playlist* init_playlist(const char *const path)
{
// Check if path is NULL
    if(path == NULL)
    {
        ERR("Creating a playlist, path is NULL...\n");
        return NULL;
    }
    Playlist* playlist = malloc( sizeof(Playlist) );

// allocate playlist
    playlist = malloc( sizeof(Playlist) );
// init video parameters
    playlist->videos_size = 0;
    playlist->videos_cap  = 100;
    playlist->p_video     = malloc(playlist->videos_cap
                                    * sizeof(char[NAME_MAX]));
    return playlist;
}

Playlist* get_playlist(const char *const path)
{
// Check if path is NULL
    if(path == NULL)
    {
        ERR("Path to playlist is null...");
        return NULL;
    }

    Playlist* playlist = malloc( sizeof(Playlist) );
    int video_count = 0;

//    Setup 

//Set name
//TODO remove and
//make new function
//create_playlist
    strncpy(playlist->p_name, "Yee", NAME_MAX);
//Allocate memory
    playlist->p_video = malloc(100 * sizeof(char[NAME_MAX]) );
//Set path
    strncpy(playlist->p_path, path, PATH_MAX);

    DIR* dir;
    struct dirent *entry;
// Open directory from path
    if( (dir = opendir(path)) )
    {
        NOTE("Opened stuff\n");
    // Loop though every file
    // in a directory
        while( (entry = readdir(dir)) != NULL)
        {
            NOTE("Found stuff \"%s\"\n", entry->d_name);
        // See if the file is just a
        // file and not a dir or lnk
            if( entry->d_type == DT_REG)
            {
                NOTE("Found reg \"%s\"\n", entry->d_name);
                //TODO Check for video extension
                
                add_video(playlist, entry->d_name);
                /*
                strncpy(playlist->p_video[],
                    entry->d_name,
                    NAME_MAX);
                */
            }
        }
    }
    else
    {
    // Didn't directory correctly 
        ERR("Couldn't open \"%s\"", path);
        return NULL;
    }

    return playlist;
}

void print_playlist(Playlist* playlist)
{
    printf("\nPlaylist's Name: %s\n", playlist->p_name);
    printf("Playlist's Path: %s\n", playlist->p_path);
    printf("Playlist's Videos:");
    int video_count = 0;
    while ( playlist->p_video[video_count++] != NULL )
    {
        printf("\n\t%d.%s", video_count,
                &(playlist->p_video[video_count * NAME_MAX]));
    }
}
void free_playlist(Playlist *playlist)
{
// Free videos stored
    free(playlist->p_video);
}

