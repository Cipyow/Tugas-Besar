#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <time.h>

#define MAX_PLAYERS 11
#define MAX_NAME_LEN 15
#define FILE_NAME "hhhighscores.txt"

// Struktur pemain
typedef struct {
    char name[MAX_NAME_LEN];
    int score;
    time_t completion_time;
} Player;

extern Player players[MAX_PLAYERS];
extern int player_count;

void highscore();
void load_scores();
void save_scores();
void sort_scores();
void update_or_add_player(char *name, int score, time_t completion_time);
void reset_scores();

#endif
