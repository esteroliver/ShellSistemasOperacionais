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
    //argumentos
    vector<string> args;
    size_t start = 0;
    size_t end = comando.find(' ');
    while (end != string::npos) {
        args.push_back(comando.substr(start, end - start));
        start = end + 1;
        end = comando.find(' ', start);
    }
    args.push_back(comando.substr(start));
    

    if(args[0] == "pwd"){
        cout << filesystem::current_path() << endl;
        return;
    }
    if(args[0] == "cd"){
        chdir(args[1].c_str());
        return;
    }

    string caminho_absoluto = "/mnt/d/desenvolvimento/repositorios/ShellSistemasOperacionais/chamadas";
    //executar comando
    if(access(caminho_absoluto.c_str(), F_OK) == 0){ //verificando que o diretório existe
        if(access(caminho_absoluto.c_str(), X_OK) == 0){ //verificando se o arquivo é executável
            //dividindo entre processo filho e processo pai
            pid_t pid = fork();
            if(pid < 0){
                cout << "Erro de execução." << endl;
                return;
            }
            else if(pid == 0){
                vector<char*> argv;
                argv.push_back((char *)args[0].c_str());
                if(args.size() > 1){
                    argv.push_back((char *)args[1].c_str());
                    if(args.size() == 3)
                        argv.push_back((char *)args[2].c_str());
                }
                argv.push_back(nullptr);
                execvp(argv[0], argv.data());
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
        cout << "$>";
        string comando;
        getline(cin, comando);
        if(comando == "exit") break;
        processo_comando(comando);
    }
    return 0;
}