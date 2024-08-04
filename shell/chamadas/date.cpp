#include <time.h>
#include <iostream>

int main(){
    time_t t = time(NULL);
    std::cout << ctime(&t);
    //object t = date [-u|--utc|--universal] [MMDDhhmm[[CC]YY][.ss]]
    return 0;
}