#include "controladoraUsuario.h"
#include "interfaceUsuario.h"
#include "stubs.h"
#include "curses.h"

int main(){

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
