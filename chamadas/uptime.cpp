#include <sys/sysinfo.h>
#include <stdio.h>
#include <iostream>

int main (){
    struct sysinfo info;
    sysinfo(&info); //construtor
    int minutos = info.uptime/60;
    std::cout << minutos << " minutos";
    std::cout << std::endl;
    return 0;
}