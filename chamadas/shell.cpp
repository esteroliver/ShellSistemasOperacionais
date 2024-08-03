#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

void processo_comando(string comando){
    string caminho_absoluto = "/chamadas/" + comando + comando;
    if(acess(caminho_absoluto.c_str(), F_OK) == 0){ //verificando que o diretório existe
        if(acess(caminho_absoluto.c_str(), X_OK) == 0){ //verificando se o arquivo é executável
            //dividindo entre processo filho e processo pai
            pid_t pid = fork();
            if(pid < 0){
                cout << "Erro de execução." << endl;
                return;
            }
            else if(pid == 0){
                //to do
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
        cout << "$> ";
        string comando;
        getline(cin, comando);
        if(comando == "exit") break;
        processo_comando(comando);
    }
    return 0;
}