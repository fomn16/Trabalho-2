#ifndef INTERFACE_EVENTOS_H
#define INTERFACE_EVENTOS_H

#include "dominios.h"
#include "entidades.h"


using namespace std;

class ISEventos;

class IAEventos{
    public:
        virtual void executar() = 0;
        virtual void setCSEventos (ISEventos *cSEventos) = 0;
        virtual ~IAEventos(){}

        void operacaoExecutada() const{
            cout<<"pressione qualquer botao para continuar"<<endl;
            getch();
        }
};

class ISEventos{
    public:
        virtual void cadastrar() = 0;
        virtual void excluir() = 0;
        virtual void alterar () = 0;
        virtual Evento pesquisar (CodigoEvento codigo) = 0;

};

#endif // INTERFACE_EVENTOS_H
