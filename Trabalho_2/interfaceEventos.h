#ifndef INTERFACE_EVENTOS_H
#define INTERFACE_EVENTOS_H

#include "dominios.h"
#include "entidades.h"


using namespace std;

class ISEventos{
    public:
        virtual void cadastrar(Evento evento) = 0;
        virtual void excluir(CodigoEvento codigo) = 0;
        virtual Evento pesquisar (CodigoEvento codigo) = 0;
        virtual void editar() = 0;
        virtual ~ISEventos(){}
};

class IAEventos{
    public:
        virtual void executar() = 0;
        virtual void setCSEventos (ISEventos *cSEventos) = 0;
        virtual ~IAEventos(){}

        void operacaoExecutada() const{
            cout<<"pressione qualquer tecla para continuar"<<endl;
            getch();
        }
};

#endif // INTERFACE_EVENTOS_H
