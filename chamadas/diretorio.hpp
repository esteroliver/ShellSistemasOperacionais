#ifndef __DIRETORIO__
#define __DIRETORIO__

#include <unistd.h>

class diretorio{
    private:
        char *dir;
    public:
        diretorio(){
            dir = get_current_dir_name();
        }
        ~diretorio(){
            delete dir;
        }
        char *getDiretorio(){
            return dir;
        }
};

#endif // __DIRETORIO__