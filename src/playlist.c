#include <stdio.h>
#include <stdlib.h>

#include "playlist.h"
#include "utils.h"

Playlist* create_playlist(size_t sz)
{
// make playlist 
    Playlist *p;
    p = malloc( sizeof(Playlist) );
    if(p == NULL)
    {
        ERR("Couldn't create a playlist...");
        return NULL;
    }
    p->video_size = 0;
    p->video_count = sz;
    p->videos = malloc( sz*sizeof(Video) );
    
// Return created playlist
    return p;
}

void free_playlist(Playlist* p)
{
    if(p != NULL)
    {
        free(p->videos);
        free(p);
    }
}
