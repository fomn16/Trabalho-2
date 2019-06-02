#ifndef STUBS_H_INCLUDED
#define STUBS_H_INCLUDED

#include "interfaceUsuario.h"
#include <stdexcept>
#include <iostream>

using namespace std;

class Stub:public ISUsuario{  // classe implementa a interface.

public:
    void cadastrar(const Usuario &usuario, const CartaoCredito &cartaoCredito) throw(runtime_error);
    void descadastrar(const Usuario &usuario) throw(runtime_error);
    void pesquisar(const CPF &cpf) throw(runtime_error);
    void editar(const Usuario &usuario) throw(runtime_error);
};

#endif // STUBS_H_INCLUDED

