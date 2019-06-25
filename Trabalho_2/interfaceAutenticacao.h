#ifndef INTERFACE_AUTENTICACAO_H
#define INTERFACE_AUTENTICACAO_H

#include "dominios.h"
#include "entidades.h"
#include <stdexcept>

using namespace std;

class ISAutenticacao;

class IAAutenticacao {
public:

    virtual void executarOpcoes() = 0;
    virtual void setCSAutenticacao(ISAutenticacao *CSAutenticacao) = 0;
    virtual ~IAAutenticacao(){}

};

class ISAutenticacao {
public:

    virtual void autenticar(CPF cpf) throw(runtime_error) = 0;
    virtual ~ISAutenticacao(){}
};

#endif

