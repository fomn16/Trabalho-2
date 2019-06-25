#include "controladoraUsuario.h"
#include "interfaceUsuario.h"
#include "controladoraAutenticacao.h"
#include "interfaceAutenticacao.h"
#include "stubs.h"
#include "curses.h"

int main(){
    //IAAutenticacao *cntrA;
    //ISAutenticacao *cntrS;

    //cntrA = new CAAutenticacao();
    //cntrS = new CSAutenticacao();
    //cntrA->setCSAutenticacao(cntrS);

    //cntrA->executarOpcoes();

    IAUsuario *cntrA;
    ISUsuario  *cntrS;

    cntrA = new CAUsuario();
    cntrS = new CSUsuario();
    cntrA->setCSUsuario(cntrS);

    cntrA->executarOpcoes();

    delete cntrA;
    delete cntrS;

    return 0;
}
