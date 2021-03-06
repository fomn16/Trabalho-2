#ifndef CONTROLADORA_MAIN_H
#define CONTROLADORA_MAIN_H

#include "entidades.h"
#include "dominios.h"
#include "controladoraEventos.h"
#include "controladoraVendas.h"
#include "curses.h"

class CntrMain{
    private:
        static const unsigned int NUMERO_OPCOES = 5;
        static const unsigned int OPCAO_USUARIO = 1;
        static const unsigned int OPCAO_AUTENTICACAO = 2;
        static const unsigned int OPCAO_EVENTOS = 3;
        static const unsigned int OPCAO_VENDAS = 4;
        static const unsigned int OPCAO_ENCERRAR = 5;

        ConstrutoraEventos *cnstE;
        ConstrutoraVendas *cnstV;

        WINDOW* createWindow(int height, int width, int y, int x, int color_id);
        void printMenu(WINDOW *win, int y, int x, int highlight, int color_id, int qt_opcoes,const char **opcoes);

    public:
        void executar();
        int getKey(WINDOW* win, int &highlight, int choice, int qt_opcoes);
        void setCnsts(ConstrutoraEventos *cnstE, ConstrutoraVendas *cnstV);
};

class ConstrutoraMain{
    public:
        CntrMain cntrMain;
        ConstrutoraEventos cnstE;
        ConstrutoraVendas cnstV;

        void build(){
            cnstE.build();
            cnstV.build();
            cntrMain.setCnsts(&cnstE, &cnstV);
        }
};

#endif // CONTROLADORA_MAIN_H
