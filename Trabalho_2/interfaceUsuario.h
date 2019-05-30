#ifndef INTERFACE_USUARIO_H
#define INTERFACES_USUARIO_H

#include "dominios.h"
#include "entidades.h"
#include <stdexcept>

using namespace std;

class ISUsuario;

class IAUsuario {
public:

    virtual void executar(const CPF &cpf) = 0;
    virtual void setCSUsuario(ISUsuario *CSUsuario) = 0;
    virtual ~ISUsuario(){}

};

class ISUsuario {
public:

    virtual void cadastrar(const Usuario &usuario, const CartaoCredito &cartaoCredito) throw(runtime_error) = 0;
    virtual void descadastrar(const Usuario &usuario) throw(runtime_error) = 0;
    virtual void pesquisar(const CPF &cpf) throw(runtime_error) = 0;
    virtual void editar(const Usuario &usuario) throw(runtime_error) = 0;
    virtual ~ISUsuario(){}
};

#endif
