#ifndef CONTROLADORA_EVENTOS_H
#define CONTROLADORA_EVENTOS_H

#include "entidades.h"
#include "dominios.h"


class ControladoraServicoEventos{
    private:
    public:
        void cadastrar ();
        void excluir ();
        void alterar ();
        void pesquisar (CodigoEvento codigo) const;
};

class ControladoraApresentacaoEventos{
    private:
        static const unsigned int NUMERO_OPCOES = 6;
        static const unsigned int OPCAO_APRESENTAR_TODOS = 1;
        static const unsigned int OPCAO_APRESENTAR_EVENTO = 2;
        static const unsigned int OPCAO_CADASTRAR = 3;
        static const unsigned int OPCAO_EXCLUIR = 4;
        static const unsigned int OPCAO_ALTERAR = 5;
        static const unsigned int OPCAO_ENCERRAR = 6;

        void apresentarOpcoes();

        void apresentarTodos  () const;
        void apresentarEvento () const;

        void operacaoExecutada() const;

        ControladoraServicoEventos controladoraServicoEventos;

    public:
        void executar();
};

#endif // CONTROLADORA_EVENTOS_H
