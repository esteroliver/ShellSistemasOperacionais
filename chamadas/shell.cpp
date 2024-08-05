#include <iostream>
#include <unistd.h>
#include <filesystem>
#include <sys/wait.h>
#include <stdio.h>
#include <vector>
#include <string>
#include "diretorio.hpp"

using namespace std;
vector<vector<string>> history;
diretorio dir;

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
    
    int x = 1;
    if(args[0] == "history" || args[0] == "pwd" || args[0] == "cd") 
        x = 0;

    while(x == 0){
        if(args[0] != "history" && args[0] == "pwd" || args[0] == "cd")
            history.push_back(args);
        if(args[0] == "pwd"){
            cout << filesystem::current_path() << endl;
            return;
        }
        if(args[0] == "cd"){
            chdir(args[1].c_str());
            return;
        }
        if(args[0] == "history"){
            if(args.size() == 1){
                for(int i = 0; i < history.size(); i++){
                    if(history[i].size() != 1){
                        cout << ((i-history.size()) * -1 ) - 1 << " " << history[i][0] << "/" << history[i][1] << endl;
                    }
                    else{
                        cout << ((i-history.size()) * -1 ) - 1 << " " << history[i][0] << endl;
                    }
                } 
                return;
            }
            else{
                if(args[1] == "-c"){
                    history.clear();
                    return;
                }
                else{
                    int comando = stoi(args[1]);
                    comando = (comando*-1)+history.size()-1;
                    args[0] = history[comando][0];
                    if(history[comando].size() > 1)
                        args[1] = history[comando][1];
                    if(history[comando].size() > 2){
                        args[2] = history[comando][2];
                    }
                    if(args[0] != "cd" && args[0] != "pwd"){
                        x = 1;
                    }
                }
            } 
        }
    }

    char *caminho = dir.getDiretorio();
    string caminho_absoluto = (string) caminho;
    string caminho_vec = caminho_absoluto + '/' + args[0];

    //executar comando
    if(access(caminho_absoluto.c_str(), F_OK) == 0){ //verificando que o diretório existe
        if(access(caminho_vec.c_str(), X_OK) == 0){ //verificando se o arquivo é executável
            //dividindo entre processo filho e processo pai
            pid_t pid = fork();
            history.push_back(args);
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
                waitpid(pid, nullptr, 0);
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