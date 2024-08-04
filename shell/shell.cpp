#include <iostream>
#include <unistd.h>
#include <filesystem>
#include <sys/wait.h>
#include <stdio.h>
#include <vector>

// comandos internos:
//     - exit
//     - pwd 
//     - cd dir 
//     - history (mostrar os últimos comandos executados)

using namespace std;

void processo_comando(string comando){
    if(comando == "pwd"){
        cout << filesystem::current_path() << endl;
    }
    if(comando.find("cd") == 0){
        char diretorio[comando.length()-3];
        for(int i = 3; i < comando.length(); i++){
            diretorio[i-3] = comando[i];
        }
        chdir(diretorio);
        return;
    }
    else{
        //comando
        int caracteres_comando = 0;
        for(int i = 0; i < comando.length(); i++){
            if(comando[i] == ' ') break;
            caracteres_comando++;
        }
        char comando_n[caracteres_comando-2];
        for(int i = 0; i < caracteres_comando; i++){
            comando_n[i] = comando[i];
        }
        string comando_nome = comando_n;
        string caminho_absoluto = "chamadas/";
        if(access(caminho_absoluto.c_str(), F_OK) == 0){ //verificando que o diretório existe
            if(access(caminho_absoluto.c_str(), X_OK) == 0){ //verificando se o arquivo é executável
                //dividindo entre processo filho e processo pai
                pid_t pid = fork();
                if(pid < 0){
                    cout << "Erro de execução." << endl;
                    return;
                }
                else if(pid == 0){
                    char * argv[2] = {(char *)comando.c_str(), nullptr};
                    execve(caminho_absoluto.c_str(), argv, NULL);
                }
                else{
                    //to do
                }
            }
            else{
                cout << "Permissão negada: " << comando << endl;
            }
        }
        else{
            cout << "Comando não encontrado." << endl;
        }
    }
}

int main() {
    while (true) {
        cout << "$ ";
        string comando;
        getline(cin, comando);
        if(comando == "exit") break;
        processo_comando(comando);
    }
    return 0;
}