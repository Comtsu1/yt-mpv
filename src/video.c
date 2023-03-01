#include <stdio.h>
#include <stdlib.h>
#include <linux/limits.h>

#include "playlist.h"

// TODO check returning type
void add_video(Playlist* playlist, Video video)
{
    //TODO check if we need
    //pointer
    if(playlist->videos_size == playlist->videos_cap)
    {
    //Increment videos size/cap
        playlist->videos_cap *= 2;
    //Reallocate p_video
        playlist->p_video = realloc(playlist->p_video,
                playlist->videos_cap * sizeof(char[NAME_MAX]));
    }

    snprintf(&(playlist->p_video[playlist->videos_size++ * NAME_MAX]),
            NAME_MAX, "%s", video);
}
