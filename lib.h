
#ifndef _SAVE_GAME_
#define _SAVE_GAME_

typedef struct {

    unsigned int level;
    float hp;
    char display_name[48];
    char title[48];
    char guild[48];

} player_;


char *get_last_save_file(char *dir_);

player_ *savefile_load_stats(char *filename);
char *savefile_save_stats(player_ *player);

player_ *init_player();

void change_pdata(player_ *player);
void show_pdata(player_ *player);

#endif
