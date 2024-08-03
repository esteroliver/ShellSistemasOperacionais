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
    //comando
    int caracteres_comando = 0;
    for(int i = 0; i < comando.length(); i++){
        caracteres_comando++;
        if(comando[i] == " ") break;
    }
    char comando_nome[caracteres_comando];
    for(int i = 0; i < caracteres_comando; i++){
        comando_nome[i] = comando[i];
    }

    //parâmetros
    if(caracteres_comando < comando.length()){
        vector<string> parametros;
        int param1 = 0;
        int param2 = 0;
        int indice = 0;
        for(int i = caracteres_comando+2; i < comando.length(); i++){
            if(comando[i] == " ") indice++;
            if(indice == 0) param1++;
            else param2++;
        }
        char param1_c[param1];
        if(param2 > 0) char param2_c[param2];
        for(int i = caracteres_comando+2; i < param1; i++){
            param1_c[i] = comando[i];
        }
        if(param2 > 0){
            for(int i = param1+2; i < comando.length(); i++){
                param2_c[i] = comando[i];
            }
        }
        parametros.push_back(param1_c);
        if(param2 > 0) parametros.push_back(param2_c);
    }
    string caminho_absoluto = "../chamadas/" + comando;
    if(access(caminho_absoluto.c_str(), F_OK) == 0){ //verificando que o diretório existe
        if(access(caminho_absoluto.c_str(), X_OK) == 0){ //verificando se o arquivo é executável
            //dividindo entre processo filho e processo pai
            pid_t pid = fork();
            if(pid < 0){
                cout << "Erro de execução." << endl;
                return;
            }
            else if(pid == 0){

                // char *parametros[100];
                // int index = 0;
                // fgets(comando, BUFF_SIZE+1, stdin);
                // token = strtok(comando, " \t\n");
                // parametros[index] = token;
                // index++;

                // while(token != NULL){
                //     token = strtok(NULL, " \t\n");
                //     parametros[index] = token; 
                //     index++;
                // }
                // parametros[index] = NULL;
                // //to do
                // execve(parametros[0], parametros);
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