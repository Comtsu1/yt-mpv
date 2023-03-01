#ifndef PLAYLIST_H
#define PLAYLIST_H

typedef char* Video;

struct Playlist
{
    char p_name[NAME_MAX];             // Name of the Playlist
    char p_path[PATH_MAX];             // Path of the Playlist  
    Video p_video;                     // Names of the videos
    unsigned long videos_size,         // The current size of p_videos
        videos_cap;                    // The total cap of p_videos
};

typedef struct Playlist Playlist;

Playlist* init_playlist(const char *const path);
Playlist* get_playlist(const char *const path);
void print_playlist(Playlist* playlist);
void free_playlist(Playlist* playlist);

#endif
