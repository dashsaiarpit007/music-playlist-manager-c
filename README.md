# Music Playlist Manager (C)

A simple command-line music playlist manager built using a **singly linked list** in C.

## Features
- Add songs (title and artist)
- Display the playlist
- Delete a song by ID
- Reverse the playlist
- Simulate playing the next song (removes it from the queue)

## Run

```bash
gcc -std=c11 -Wall -Wextra main.c -o playlist
./playlist
```

On Windows, run `playlist.exe` after compiling.

## Data structure
Each node stores a song ID, title, artist, and pointer to the next song. The list is dynamically allocated and freed on exit.

## Future improvements
- Shuffle mode
- Tree-based traversal experiments
- Save and load playlists

**Note:** This program simulates playback by printing the next song; it does not play audio files.
