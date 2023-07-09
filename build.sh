
EXE_NAME=$1

gcc -c lib.c lib.h
gcc main.c lib.o -o $EXE_NAME
rm *.o *.gch
