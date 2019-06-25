#ifndef CONTROLADORA_AUTENTICACAO_H
#define CONTROLADORA_AUTENTICACAO_H

#include "interfaceAutenticacao.h"
#include "dominios.h"
#include "curses.h"
#include "sqlite3.h"

#include <exception>
#include <iostream>

using namespace std;

class CAAutenticacao: public IAAutenticacao {

private:

    static Usuario usuario_atual;
    // constant variables for functionality codes
    const static int AUTENTICAR = 1;
    const static int SAIR = 2;// string variables for functionalities

    const int QT_OPCOES = 2;
    const char* opcoes[2] = {"AUTENTICAR","SAIR"};
    //Service user Controller
    ISAutenticacao* CSAutenticacao;
    //Functions for window creation in curses
    WINDOW* createWindow(int height, int width, int y, int x, int color_id);
    void printMenu(WINDOW *win, int y, int x, int highlight, int color_id, int qt_opcoes, const char **opcoes);
    int getKey(WINDOW* win, int &highlight, int choice, int qt_opcoes);

public:

    void executarOpcoes();
    void setCSAutenticacao(ISAutenticacao *CSAutenticacao){
        this->CSAutenticacao = CSAutenticacao;
    }
};

class CSAutenticacao: public ISAutenticacao {

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

    void autenticar(CPF cpf) throw(runtime_error);
};

#endif
