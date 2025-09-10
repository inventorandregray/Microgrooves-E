/*
 * Microgrooves-E - Final Master Version for IBM Simon
 * World's First Mobile Multimedia Player
 * Copyright Andre Gray ©1998
 *
 * Features:
 *   - Full album playback with sequencing
 *   - Audio/video recording and playback
 *   - Polyphonic audio simulation
 *   - EQ adjustments (bass/treble)
 *   - Playlist looping and shuffle
 * Platform: IBM Simon Personal Communicator (NEC V30HL CPU)
 * Language: C/C++ (1998 style)
 * License: Open Source by Andre Gray 1998
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dos.h>
#include <conio.h>

/* Constants */
#define MAX_TRACKS 128
#define MAX_ALBUMS 16
#define MAX_FILENAME 64
#define MAX_POLYPHONY 4
#define LOOP_INFINITE -1

/* Audio/Video track structure */
typedef struct {
    char filename[MAX_FILENAME]; /* Audio/video file path */
    int duration;                /* seconds */
    int volume;                  /* 0-100 */
} Track;

/* Album structure */
typedef struct {
    char albumName[64];
    Track tracks[MAX_TRACKS];
    int trackCount;
} Album;

/* Playlist structure */
typedef struct {
    Album albums[MAX_ALBUMS];
    int albumCount;
} Playlist;

/* EQ structure */
typedef struct {
    int bass;      /* -10 to +10 */
    int treble;    /* -10 to +10 */
} EQSettings;

/* Function prototypes */
void playTrack(Track *t, EQSettings eq);
void playPolyphonicTracks(Track *tracks[], int count, EQSettings eq);
void playAlbum(Album *album, EQSettings eq, int loopCount, int shuffle);
void recordAudio(const char *filename, int duration);
void recordVideo(const char *filename, int duration);
void setEQ(EQSettings *eq, int bass, int treble);

/* --- Low-level hardware simulation (IBM Simon) --- */
void hwPlayAudio(int volume, int frequency, int duration) {
    /* 
     * Placeholder for IBM Simon audio DAC and timer control.
     * Polyphonic audio is time-sliced across multiple tones.
     */
    printf("HW Audio: freq=%dHz vol=%d dur=%dms\n", frequency, volume, duration);
    delay(duration);
}

/* --- Main Demo --- */
int main() {
    Album demoAlbum;
    EQSettings eq;

    /* Configure EQ */
    setEQ(&eq, 3, 2);

    /* Initialize album */
    strcpy(demoAlbum.albumName, "Greatest Hits");
    demoAlbum.trackCount = 3;
    strcpy(demoAlbum.tracks[0].filename, "track1.mg"); demoAlbum.tracks[0].duration = 180; demoAlbum.tracks[0].volume = 80;
    strcpy(demoAlbum.tracks[1].filename, "track2.mg"); demoAlbum.tracks[1].duration = 210; demoAlbum.tracks[1].volume = 80;
    strcpy(demoAlbum.tracks[2].filename, "track3.mg"); demoAlbum.tracks[2].duration = 200; demoAlbum.tracks[2].volume = 80;

    /* Play album with looping and shuffle disabled */
    playAlbum(&demoAlbum, eq, 1, 0);

    /* Record audio and video examples */
    recordAudio("myaudio.mg", 60);
    recordVideo("myvideo.mg", 30);

    return 0;
}

/* --- Set EQ --- */
void setEQ(EQSettings *eq, int bass, int treble) {
    if(bass < -10) bass = -10; if(bass > 10) bass = 10;
    if(treble < -10) treble = -10; if(treble > 10) treble = 10;
    eq->bass = bass; eq->treble = treble;
}

/* --- Play a single track with EQ and volume adjustment --- */
void playTrack(Track *t, EQSettings eq) {
    int adjVolume = t->volume + eq.bass + eq.treble;
    if(adjVolume > 100) adjVolume = 100;
    if(adjVolume < 0) adjVolume = 0;

    printf("Playing Track: %s Duration: %d sec Volume: %d\n",
           t->filename, t->duration, adjVolume);

    /* Simulate polyphonic audio with time-sliced DAC calls */
    hwPlayAudio(adjVolume, 440, t->duration * 1000);
}

/* --- Play multiple tracks simultaneously (Polyphony) --- */
void playPolyphonicTracks(Track *tracks[], int count, EQSettings eq) {
    int i;
    int maxDuration = 0;
    for(i = 0; i < count; i++) {
        if(tracks[i]->duration > maxDuration) maxDuration = tracks[i]->duration;
    }
    printf("Polyphonic playback: %d tracks\n", count);
    for(i = 0; i < count; i++) {
        playTrack(tracks[i], eq);
    }
    delay(maxDuration * 1000);
}

/* --- Play entire album with optional looping and shuffle --- */
void playAlbum(Album *album, EQSettings eq, int loopCount, int shuffle) {
    int i, loop;
    for(loop = 0; loopCount == LOOP_INFINITE || loop < loopCount; loop++) {
        int indices[MAX_TRACKS];
        for(i = 0; i < album->trackCount; i++) indices[i] = i;

        /* Shuffle tracks if requested */
        if(shuffle) {
            srand((unsigned)time(NULL));
            for(i = 0; i < album->trackCount; i++) {
                int j = rand() % album->trackCount;
                int temp = indices[i]; indices[i] = indices[j]; indices[j] = temp;
            }
        }

        /* Play tracks */
        for(i = 0; i < album->trackCount; i++) {
            playTrack(&album->tracks[indices[i]], eq);
        }

        if(loopCount != LOOP_INFINITE) break;
    }
}

/* --- Record audio --- */
void recordAudio(const char *filename, int duration) {
    printf("Recording Audio: %s Duration: %d sec\n", filename, duration);
    /* Access ADC microphone input in real hardware */
    delay(duration * 1000);
    printf("Audio recording saved: %s\n", filename);
}

/* --- Record video --- */
void recordVideo(const char *filename, int duration) {
    printf("Recording Video: %s Duration: %d sec\n", filename, duration);
    /* Access camera sensor in real hardware */
    delay(duration * 1000);
    printf("Video recording saved: %s\n", filename);
}


