#include <stdio.h>
#include <dirent.h>

int main(){
    //abrindo diretório
    struct dirent *d;
    DIR *dr;
    //nesse buf, vamos colocar o endereço de cada arquivo do diretório (diretorio/arquivo)
    char buf[266];
    //nome do diretorio
    char nome_arq[10]; 
    scanf("%s", nome_arq);
    //abrindo o diretório no dir
    dr = opendir(nome_arq);
    //percorrendo o diretório e removendo cada arquivo
    while((d = readdir(dr)) != NULL){
      sprintf(buf, "%s/%s", nome_arq, d->d_name);
      remove(buf);
    }
}