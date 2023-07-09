
#include <stdlib.h>
#include <stdio.h>

#include "lib.h"


int main(int argc, char **argv)
{

    mksd();
    while (1) /* game loop ! */
    {

        /* FIXME: infinite loop when inserting a string instead of an int! */

        short choice;
        player_ *player;

        printf("\n 0. exit\n\n 1. init new player obj\n\n 2. change player values\n\n 3. show player stats\n\n\t > ");
        scanf("%i", &choice);

        if(!(0 < choice < 3)) {
            printf("\nChoices are between 0 - 3 !\n");
            continue;
        }

        switch (choice)
        {
        case 0:
            printf("Saving ...\n");

            if(savefile_save_stats(player) != NULL)
                printf("cya ^^ !\n");
            else
                printf("Unsaved Changes Something Went Wrong!\n");
            
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