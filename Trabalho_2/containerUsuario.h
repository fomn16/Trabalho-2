#ifndef CONTAINERS_H_INCLUDED
#define CONTAINERS_H_INCLUDED

#include "dominios.h"
#include "entidades.h"

#include <list>

using namespace std;


class ContainerUsuario{
public:
    Usuario usuario;
    NumeroCartao numero;
    CodigoEvento evento

    void setCartao(NumeroCartao numero){
        this->numero = numero
    }
    void setEvento(CodigoEvento evento){
        this->evento = evento
    }
};

#endif // CONTROLADORAS_H_INCLUDED

