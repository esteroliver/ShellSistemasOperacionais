#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv){
    int file;
    char buf[50];
    int ler_tamanho;

    if(argc < 2){
        printf("error");
    }
    else{
        file = open(argv[1], O_RDONLY); //abrindo o arquivo para ler
        if (file == -1){
            printf("erro na leitura");
        }
        else{
            // o read vai ler os bytes do arquivo
            while((ler_tamanho = read(file, buf, 50)) > 0){
                write(1, &buf, ler_tamanho); //irá escrever o conteúdo do arquivo
            } 
        }
        close(file); //fechando o arquivo
    }
}