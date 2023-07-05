
#ifndef _SAVE_GAME_
#define _SAVE_GAME_

#include <stdio.h>

// default starting values
const unsigned int default_level = 1;
const float default_hp = 100.f;
/* display name is assigned by the player */

const char *default_title = 0;
const char *default_guild = 0;

const char *SAVE_FILE_EXTENTION = "u1p";
const unsigned int SAVE_FILE_EXTENTION_LEN = 3;


typedef struct {

    unsigned int level;
    float hp;
    char *display_name;
    char *title;
    char *guild;

} player_;


char *get_last_save_file(char *dir_);

player_ *savefile_load_stats(char *filename);
int savefile_save_stats(char *filename, player_ *player);

int init_player(player_ *player, char *player_name);

#endif
