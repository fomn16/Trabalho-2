#ifndef CONTROLADORAS_H_INCLUDED
#define CONTROLADORAS_H_INCLUDED

#include "interfaces.h"
#include "dominios.h"

#include <stdexcept>
#include <iostream>
#include <cstdlib>

using namespace std;

// Exemplifica controladora com m�ltiplos servi�os providos.

class CntrIUGerente:public IUGerente {

private:

    const static int INCLUIR   = 1;
    const static int REMOVER   = 2;
    const static int PESQUISAR = 3;
    const static int EDITAR    = 4;
    const static int RETORNAR  = 5;

    // Refer�ncia para servidor.

    ILNGerente *cntrLNGerente;

    // M�todos respons�veis por prover os servi�os.

    void incluir();
    void remover();
    void pesquisar();
    void editar();

public:

    // M�todo previsto na interface por meio do qual � solicitada execu��o da controladora.

    void executar(const Matricula&);

    // M�todo por meio do qual � estabelecido relacionamento com o servidor.

    void setCntrLNGerente(ILNGerente *cntrLNGerente){
        this->cntrLNGerente = cntrLNGerente;
    }
};


#endif // CONTROLADORAS_H_INCLUDED

