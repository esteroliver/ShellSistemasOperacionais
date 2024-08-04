#include <iostream>
#include <dirent.h>

int main(){
    char argc[10];
    DIR *p; //irá percorrer o diretório
    struct dirent *d; //estrutura de diretório
    scanf("%s", argc); //aqui vamos ler o nome do diretório
    p = opendir(argc); // iremos abrir um diretório que possua o nome digitado e armazenar no P
    if(p == NULL){
        printf("DIRETÓRIO NÃO ENCONTRADO");
    }
    while(NULL != (d = readdir(p))){  //percorrendo o diretório
        std::cout << std::endl << d->d_name;
    }
    std::cout << std::endl;
}