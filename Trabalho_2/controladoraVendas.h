#ifndef CONTROLADORA_VENDAS_H
#define CONTROLADORA_VENDAS_H

#include "entidades.h"
#include "dominios.h"
#include "interfaceVendas.h"
#include "curses.h"

class CntrSVendas:public ISVendas{
    public:
        void processarVenda(CPF cpf, CodigoEvento codigoEvento, CodigoApresentacao codigoApresentacao);
        Ingresso pesquisarIngresso(CPF cpf, int n);
        int nIngressos(CPF cpf);
};

class CntrAVendas:public IAVendas{
    private:
        static const unsigned int NUMERO_OPCOES = 3;
        static const unsigned int OPCAO_COMPRAR = 1;
        static const unsigned int OPCAO_PESQUISAR_INGRESSO = 2;
        static const unsigned int OPCAO_ENCERRAR = 3;

        void comprar();
        void pesquisarIngresso();

        ISVendas *cSVendas;

        WINDOW* createWindow(int height, int width, int y, int x, int color_id);
        void printMenu(WINDOW *win, int y, int x, int highlight, int color_id, int qt_opcoes,const char **opcoes);

    public:
        void executar();
        void setCSVendas(ISVendas *cSVendas);
        int getKey(WINDOW* win, int &highlight, int choice, int qt_opcoes);
};

class ConstrutoraVendas{
    public:
        CntrAVendas cntrAVendas;
        CntrSVendas cntrSVendas;

        void build(){
            cntrAVendas.setCSVendas(&cntrSVendas);
        }
};

#endif // CONTROLADORA_VENDAS_H
