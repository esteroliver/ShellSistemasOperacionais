#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
    char dir[10];
    scanf("%s", dir);
    mkdir(dir, 0777);
}