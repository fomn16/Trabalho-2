#ifndef INTERFACE_MAIN_H
#define INTERFACE_MAIN_H

#include "dominios.h"
#include "entidades.h"


using namespace std;

class IAVendas{
    public:
        virtual void executar() = 0;
        virtual ~IAVendas(){}
};

#endif // INTERFACE_MAIN_H

