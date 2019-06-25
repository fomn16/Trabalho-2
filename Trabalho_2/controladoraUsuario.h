#ifndef CONTROLADORA_USUARIO_H
#define CONTROLADORAS_USUARIO_H

#include "interfaceUsuario.h"
#include "dominios.h"
#include "curses.h"
#include "sqlite3.h"

#include <exception>
#include <iostream>

using namespace std;

class CAUsuario: public IAUsuario {

private:
    // constant variables for functionality codes
    const static int CADASTRAR = 1;
    const static int DESCADASTRAR = 2;
    const static int PESQUISAR = 3;
    const static int EDITAR = 4;
    const static int SAIR = 5;
    // string variables for functionalities
    const int QT_OPCOES = 5;
    const char* opcoes[5] = {"CADASTRAR","DESCADASTRAR","PESQUISAR", "EDITAR", "SAIR"};
    //Service user Controller
    ISUsuario* CSUsuario;
    //Functions for window creation in curses
    WINDOW* createWindow(int height, int width, int y, int x, int color_id);
    void printMenu(WINDOW *win, int y, int x, int highlight, int color_id, int qt_opcoes, const char **opcoes);
    int getKey(WINDOW* win, int &highlight, int choice, int qt_opcoes);
    //Functions that show functionalities windows
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

class CSUsuario: public ISUsuario {

private:
    //DB variables
    const char *nomeBD = "banco.db";
    sqlite3* bd;
    char *mensagem;
    int rc;

    //int inutil();
    static int callback(void *NotUsed, int argc, char **valorColuna, char **nomeColuna);
    void conectar() throw(runtime_error);
    void desconectar() throw(runtime_error);
    void executar(const char* comando) throw(runtime_error);

public:
    static Usuario usuario;
    static CartaoCredito cartao;

    void cadastrar(Usuario usuario, CartaoCredito cartaoCredito) throw(runtime_error);
    void descadastrar(CPF cpf) throw(runtime_error);
    void pesquisar(CPF cpf) throw(runtime_error);
    void editar( Usuario usuario, CartaoCredito cartao) throw(runtime_error);
};


#endif

