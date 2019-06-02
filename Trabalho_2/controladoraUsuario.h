#ifndef CONTROLADORA_USUARIO_H
#define CONTROLADORAS_USUARIO_H

#include "interfaceUsuario.h"
#include "dominios.h"
#include "curses.h"

#include <stdexcept>
#include <iostream>
#include <cstdlib>

using namespace std;

class CAUsuario:public IAUsuario {

private:

    const static int CADASTRAR = 1;
    const static int DESCADASTRAR = 2;
    const static int PESQUISAR = 3;
    const static int EDITAR = 4;
    const static int SAIR = 5;

    const int QT_OPCOES = 5;
    const char* opcoes[5] = {"CADASTRAR","DESCADASTRAR","PESQUISAR", "EDITAR", "SAIR"};

    ISUsuario* CSUsuario;

    WINDOW* createWindow(int height, int width, int y, int x, int color_id);
    void printMenu(WINDOW *win, int y, int x, int highlight, int color_id, int qt_opcoes, const char **opcoes);
    int getKey(WINDOW* win, int &highlight, int choice, int qt_opcoes);

    void cadastrar();
    void descadastrar();
    void pesquisar();
    void editar();

public:

    void executarOpcoes();

    void setCSUsuario(ISUsuario *CSUsuario){
        this->CSUsuario = CSUsuario;
    }
};

#endif

