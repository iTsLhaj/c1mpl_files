
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "lib.h"


const char *save_dir = "./savedir/";

/* default starting values */
unsigned int default_level = 1;
float default_hp = 100.0f;

/* display name is assigned by the player! */

char *default_title = 0;
char *default_guild = 0;

char *SAVE_FILE_EXTENTION = ".u1p";
unsigned int SAVE_FILE_EXTENTION_LEN = 4;

/* check if save dir exists otherwise make one */
void mksd() {
    /* make save dir */

    DIR *dirp = opendir(".");
    while (dirp) {
        struct dirent *dp = readdir(dirp);
        if(dp != NULL)
        {
            if (strncmp(dp->d_name, "savedir", 7) == 0)
            {
                closedir(dirp);
                return ;
            } else 
                continue;
        } else 
            break ;
    }

    char *cmd_ = malloc(16);

    strcat(cmd_, "mkdir ");
    strcat(cmd_, save_dir);

    system(cmd_);
    free(cmd_);

}

char* make_path(char *fn)
{

    unsigned int size = strlen(save_dir) + strlen(fn);
    char *path = malloc(size);
    memset(path, 0, size);

    strcat(path, save_dir);
    strcat(path, fn);

    return path;

}

char *reverse_string(char *str, int len)
{

    char *rstr = malloc(len);
    int i = len - 1;
    int k = 0;

    while (i > -1)
    {
        
        rstr[k] = str[i];
        i--;
        k++;

    }
    
    return rstr;

}

char *itoa(int n)
{
    char *a = malloc(10);
    int i = 0;
    while (n > 0)
    {
        if(n % 10 > 0)
        {
            a[i] = (n % 10) + 48;
            n -= n % 10;
            i++;
        } else {
            n /= 10;
        }
    }
    
    char *rv = malloc(10);

    rv[i] = '\0';
    for (int j = i-1, k = 0; j > -1 && k < i; j-- && k++)
        rv[k] = a[j];
    
    free(a);
    return rv;
}

char *get_last_save_file(const char *dir_) /* FIXME: not sorted! it just check's if file end's with .u1p */
{
    DIR *dirp = opendir(dir_);
    while (dirp) {
        struct dirent *dp = readdir(dirp);
        if(dp != NULL)
        {
            if (strncmp(reverse_string(dp->d_name, strlen(dp->d_name)), reverse_string(SAVE_FILE_EXTENTION, SAVE_FILE_EXTENTION_LEN), SAVE_FILE_EXTENTION_LEN) == 0)
            {
                closedir(dirp);
                return dp->d_name;
            } else 
                continue;
        } else
            return NULL;
    }

    return NULL;
}

char *get_sfname(void)
{

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    char **fnsc = (char**)malloc(sizeof(char*)*6);
    for (int i = 0; i < 6; i++)
        fnsc[i] = (char*)malloc(16);

    fnsc[0] = "savefile_";
    fnsc[1] = itoa(tm.tm_mday);
    fnsc[2] = itoa(tm.tm_hour);
    fnsc[3] = itoa(tm.tm_min);
    fnsc[4] = itoa(tm.tm_sec);
    fnsc[5] = ".u1p";


    char *fname = malloc(25);
    memset(fname, 0, 25);

    int i = 0, j = 0;
    while (i < 6)
    {
        char *string_ = fnsc[i];
        while (*string_)
        {
            fname[j] = *string_;
            j++;
            string_++;
        }
        i++;
    }

    return fname;

}

char *savefile_save_stats(player_ *player)
{

    char *filename = get_sfname();
    FILE *sf_ = fopen(make_path(filename), "wb");

    if (sf_ != NULL)
    {

        fwrite(player, sizeof(player_), 1, sf_);
        fclose(sf_);
        
    }else{

        fprintf(stderr, "\n There was an error while opening a file!");
        return NULL;
    
    }

    return filename;

}

player_ *savefile_load_stats(char *filename)
{

    player_ *loadedPlayer = (player_*)malloc(sizeof(player_));
    FILE *sf_ = fopen(make_path(filename), "rb");

    if(sf_ != NULL)
    {
        
        fread(loadedPlayer, sizeof(player_), 1, sf_);
        fclose(sf_);

        return loadedPlayer;

    }else{
        fprintf(stderr, "couldn't open file or file has no content");
        return NULL;
    }

}

/* player stats init! */
player_ *init_player()
{

    // Check if save file exists!
    /*
        i'll pretend that save folder is the current dir i wanna get done with this asap! "."
    */

    char *file_name = get_last_save_file(save_dir);
    if(file_name != NULL)
        printf("%s\n", make_path(file_name));

    // READ
    if(file_name != NULL)
    {
        
        printf("SaveFile Found! ... Loading Game data!\n");
        return savefile_load_stats(file_name);

    } else {

        // WRITE

        player_ *player = (player_*)malloc(sizeof(player_));
        printf("SaveFile doesen't exist :c !\n");
        
        player->level = default_level;
        player->hp = default_hp;

        printf("type a display name: ");
        getchar();
        
        /* getchar();
        
            i wanna let u know that i've been struggling with fgets
            then i found out why XD 
            thanks to @MacGyver from cprogramming forume !

            source: https://cboard.cprogramming.com/c-programming/105615-user-input-gets-skipped.html
        
        */

        fgets(player->display_name, 48, stdin);

        printf("\nSaving Game data ...\n");
        char* r = savefile_save_stats(player); 
    
        if(r == NULL)
            return NULL;
        else
            printf("Saved to: %s\n", make_path(r));
        
        return player;
        
    }

    return NULL;

}

void change_pdata(player_ *player)
{

    memcpy(player->guild, "indonesia patch notes guild", 28);
    memcpy(player->title, "son of Raftel", 14);
    player->hp = 21915.0f;
    player->level = 159;

}

void show_pdata(player_ *player)
{

    printf("\n----- ꜱᴛᴀᴛꜱ -----\n\n");

    /*
        ➤ ᴅɪꜱᴘʟᴀʏ ɴᴀᴍᴇ  : %s\n
        ➤ ᴛɪᴛʟᴇ         : %s\n
        ➤ ɢᴜɪʟᴅ         : %s\n
        ➤ ʟᴇᴠᴇʟ         : %s\n
        ➤ ʜᴘ            : %s\n
    */

    printf("➤ ᴅɪꜱᴘʟᴀʏ ɴᴀᴍᴇ  : %s\n", player->display_name);
    printf("➤ ᴛɪᴛʟᴇ         : %s\n", player->title);
    printf("➤ ɢᴜɪʟᴅ         : %s\n", player->guild);
    printf("➤ ʟᴇᴠᴇʟ         : %i\n", player->level);
    printf("➤ ʜᴘ            : %f\n", player->hp);

    printf("\n----- ᴇɴᴅ ------\n");

}