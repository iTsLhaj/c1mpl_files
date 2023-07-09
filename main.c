// #include "lib.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <dirent.h>
#include <time.h>

typedef struct {

    unsigned int level;
    float hp;
    char display_name[48];
    char title[48];
    char guild[48];

} player_;

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



void init_(player_ *player)
{
    
    fgets(player->display_name, 48, stdin);
    memcpy(player->guild, "mamak", 5);
    memcpy(player->title, "khrztk", 6);

    player->level = 1;
    player->hp = 300;

}

int main(int argc, char **argv)
{
    
    player_ *player = (player_*)malloc(sizeof(player_));
    init_(player);

    printf("%s\n", player->display_name);

    return 0;

}