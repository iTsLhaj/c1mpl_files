#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <time.h>

#include "lib.h"

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
            if (strncmp(reverse_string(dp->d_name, strlen(dp->d_name)), reverse_string(".u1p", 4), 4) == 0)
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

player_ *savefile_load_stats(char *filename)
{

    player_ loadedP_t;
    FILE *sf_ = fopen(filename, "r");
    if(sf_ != NULL)
    {
        
        fread(&loadedP_t, sizeof(player_), 1, sf_);
        fclose(sf_);
        return &loadedP_t;

    }else
        return NULL;;

}

int savefile_save_stats(char *filename, player_ *player)
{

    FILE *sf_ = fopen(filename, "w");

    fwrite(player, sizeof(player_), 1, sf_);
    fclose(sf_);

    return 0;

}

/* player stats init! */
int init_player(player_ *player)
{

    // Check if save file exists!
    /*
        i'll pretend that save folder is the current dir i wanna get done with this asap! "."
    */

    char *file_name = malloc(20);
    file_name = get_last_save_file(".");

    if(file_name != NULL)
    {
        player_ *loaded_stats = savefile_load_stats(file_name);
        
        if(loaded_stats == NULL)
        {
            fprintf(stderr, "[!] Something WentWrong! [line:158] : savefile_load_stats returned NULL value [!]");
            return -1;
        }

        player->level = loaded_stats->level;
        player->hp = loaded_stats->hp;
        player->display_name = loaded_stats->display_name;
        player->title = loaded_stats->title;
        player->guild = loaded_stats->guild;

        free(loaded_stats);

        return 0;
    } else {

        player->level = default_level;
        player->hp = default_hp;
        player->display_name = fgets("display name!: ", 16, stdin);
        player->title = default_title;
        player->guild = default_guild;

        int r = savefile_save_stats(get_sfname(), player); 
    
        if(r == 0)
            return 0;
        else
            return -1;
        
    }

    return -1;

}