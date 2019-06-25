#ifndef INTERFACE_USUARIO_H
#define INTERFACE_USUARIO_H

#include "dominios.h"
#include "entidades.h"
#include <stdexcept>

using namespace std;

class ISUsuario;

class IAUsuario {
public:

    virtual void executarOpcoes() = 0;
    virtual void setCSUsuario(ISUsuario *CSUsuario) = 0;
    virtual ~IAUsuario(){}

};

class ISUsuario {
public:

    virtual void cadastrar( Usuario usuario, CartaoCredito cartaoCredito) throw(runtime_error) = 0;
    virtual void descadastrar(CPF cpf) throw(runtime_error) = 0;
    virtual void pesquisar(CPF cpf) throw(runtime_error) = 0;
    virtual void editar(Usuario usuario, CartaoCredito cartao) throw(runtime_error) = 0;
    virtual ~ISUsuario(){}
};

#endif
