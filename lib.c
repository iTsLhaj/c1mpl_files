
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "lib.h"


/* default starting values */
unsigned int default_level = 1;
float default_hp = 100.0f;

/* display name is assigned by the player! */

char *default_title = 0;
char *default_guild = 0;

char *SAVE_FILE_EXTENTION = ".u1p";
unsigned int SAVE_FILE_EXTENTION_LEN = 4;


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

char *get_last_save_file(char *dir_)
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
    FILE *sf_ = fopen(filename, "wb");

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
    FILE *sf_ = fopen(filename, "rb");

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

    char *file_name = get_last_save_file(".");

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
            printf("Saved to: %s\n", r);
        
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

int main(int argc, char **argv)
{

    // TODO: examine the code & remove bugs
    while (1) /* game loop ! */
    {

        int choice;
        player_ *player;

        printf("\n 0. exit\n\n 1. init new player obj\n\n 2. change player values\n\n 3. show player stats (comming soon)\n\n\t > ");
        scanf("%i", &choice);

        if(!(0 < choice < 3)) {
            printf("\nChoices are between 0 - 3 !\n");
            continue;
        }

        switch (choice)
        {
        case 0:
            printf("cya ^^ !\n");
            exit(0);

        case 1:
            printf("Initializing New Player Obj!\n");
            player = init_player();
            break;

        case 2:
            printf("Changing Player Values!\n");
            change_pdata(player);
            break;

        case 3:
            printf("SettingUp Player data to display!\n");
            show_pdata(player);
            break;

        default:
            break;
        }
        

    }

    return 0;

}