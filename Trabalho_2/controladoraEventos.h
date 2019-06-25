#ifndef CONTROLADORA_EVENTOS_H
#define CONTROLADORA_EVENTOS_H

#include "entidades.h"
#include "dominios.h"
#include "interfaceEventos.h"
#include "curses.h"

class CntrSEventos:public ISEventos{
    public:
        void cadastrar (Evento evento);
        void excluir (CodigoEvento codigo);

        void cadastrarApresentacao (Apresentacao apresentacao);
        void excluirApresentacao (CodigoApresentacao codigo);

        Evento pesquisar (CodigoEvento codigo);

        int nApresentacoes (CodigoEvento codigo);
        Apresentacao pesquisarApresentacoes (CodigoEvento codigo, int n);
};

class CntrAEventos:public IAEventos{
    private:
        static const unsigned int NUMERO_OPCOES = 9;
        static const unsigned int OPCAO_APRESENTAR_TODOS = 1;
        static const unsigned int OPCAO_APRESENTAR_EVENTO = 2;
        static const unsigned int OPCAO_CADASTRAR = 3;
        static const unsigned int OPCAO_EXCLUIR = 4;
        static const unsigned int OPCAO_EDITAR = 5;
        static const unsigned int OPCAO_CADASTRAR_APRESENTACAO = 6;
        static const unsigned int OPCAO_EXCLUIR_APRESENTACAO = 8;
        static const unsigned int OPCAO_EDITAR_APRESENTACAO = 7;
        static const unsigned int OPCAO_ENCERRAR = 9;

        void index ();
        void pesquisar ();
        void cadastrar ();
        void excluir ();
        void editar();
        void cadastrarApresentacao ();
        void excluirApresentacao ();
        void editarApresentacao();

        ISEventos *cSEventos;

        WINDOW* createWindow(int height, int width, int y, int x, int color_id);
        void printMenu(WINDOW *win, int y, int x, int highlight, int color_id, int qt_opcoes,const char **opcoes);

    public:
        void executar();
        void setCSEventos(ISEventos *cSEventos);
        int getKey(WINDOW* win, int &highlight, int choice, int qt_opcoes);
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
