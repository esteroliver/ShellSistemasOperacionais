#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>

int main(){
    char dir[10];
    scanf("%s", dir);
    if(rmdir(dir) != 0){
        std::cout << "error \n";
    }
    else{
        std::cout << "diretório removido \n";
    }
}