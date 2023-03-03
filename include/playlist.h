#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <stdio.h>
#include "video.h"

typedef struct Playlist
{
    size_t video_size,     // How many videos there are in playlist
        video_count;       // capacity in playlist
    Video* videos;         // video names
} Playlist;

Playlist* create_playlist(size_t sz);
void free_playlist(Playlist *p);

#endif
