#ifndef CONTROLADORA_EVENTOS_H
#define CONTROLADORA_EVENTOS_H

#include "entidades.h"
#include "dominios.h"
#include "interfaceEventos.h"

class CntrSEventos:public ISEventos{
    public:
        void cadastrar (Evento evento);
        void excluir (CodigoEvento codigo);
        void alterar ();
        void editar();
        Evento pesquisar (CodigoEvento codigo);
};

class CntrAEventos:public IAEventos{
    private:
        static const unsigned int NUMERO_OPCOES = 6;
        static const unsigned int OPCAO_APRESENTAR_TODOS = 1;
        static const unsigned int OPCAO_APRESENTAR_EVENTO = 2;
        static const unsigned int OPCAO_CADASTRAR = 3;
        static const unsigned int OPCAO_EXCLUIR = 4;
        static const unsigned int OPCAO_EDITAR = 5;
        static const unsigned int OPCAO_ENCERRAR = 6;

        void apresentarOpcoes();

        void index ();
        void pesquisar ();
        void cadastrar ();
        void excluir ();
        void editar();

        ISEventos *cSEventos;

    public:
        void executar();
        void setCSEventos(ISEventos *cSEventos);
};

class ConstrutoraEventos{
    public:
        CntrAEventos cntrAEventos;
        CntrSEventos cntrSEventos;

        void build(){
            cntrAEventos.setCSEventos(&cntrSEventos);
        }
};

#endif // CONTROLADORA_EVENTOS_H
