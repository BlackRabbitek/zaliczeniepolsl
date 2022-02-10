#include "header.h"
using namespace std;


int main() {
    SetConsoleOutputCP(CP_UTF8);
    int err = 0;
    string acc[] = {"Guest","0"};
    ROM rooms{};
    SVC services{}, types{};
    load(&rooms,&services,&types);
    home();
    while(comm(acc,&err,&rooms,&services,&types)){
        if(err==1){
            errf();
            err=0;
        }
    }
    save(&rooms,&services,&types);
    return 0;
}
