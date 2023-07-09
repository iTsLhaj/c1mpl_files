#include <stdio.h>
#include <stdlib.h>

typedef struct artifact
{

    char *a_name;
    int lvl;
    int critdmg;
    int critrate;
    int exp;
    int max_exp;
    int max_level;
    char a_type;

} artifact_t;


void display(artifact_t *_artifact)
{

    printf("\n LVL: %i\n CRIT[DMG|RATE]: %i, %i\n EXP: %i\n MAX EXP: %i\n MAX LEVEL: %i\n Artifact (Type/Class): %c\n", _artifact->lvl, _artifact->critdmg, _artifact->critrate, _artifact->exp, _artifact->max_exp, _artifact->max_level, _artifact->a_type);

}

artifact_t *init()
{

    artifact_t *a = (artifact_t*)malloc(sizeof(artifact_t));

    a->a_name = malloc(6);
    a->a_name = "mok\0";
    
    a->lvl = 1;
    a->critdmg = 21;
    a->critrate = 37;
    a->exp = 1000;
    a->max_exp = 2000;
    a->max_level = 20;
    a->a_type = 'C';

    return a;

}

char *save(artifact_t *_artifact)
{

    char *fn = get_sfname();
    FILE *fs = fopen(fn, "w");

    if (fs != NULL)
    {
        fwrite(_artifact, sizeof(artifact_t), 1, fs);
        fclose(fs);
    }else{
        return NULL;
    }
    
    return fn;

}

artifact_t *load(char *fn)
{

    artifact_t *a = (artifact_t*)malloc(sizeof(artifact_t));
    FILE *fs = fopen(fn, "r");

    if (fs != NULL)
    {
        fread(a, sizeof(artifact_t), 1, fs);
        fclose(fs);
    }else{
        return NULL;
    }
    
    return a;

}

int main(int argc, char **argv)
{
    
    // SAVE !
    artifact_t *my_afct = init();
    char *fn = save(my_afct);

    printf("Saved To: %s", fn);

    // LOAD !
    artifact_t *my_lafct;
    my_lafct = load(fn);
    /* display(my_afct); */

    printf("%s\n", my_lafct->a_name);

    return 0;

}