#include "controladoraUsuario.h"
#include "interfaceUsuario.h"
#include "stubs.h"
#include "curses.h"

int main(){

    IAUsuario *cntr;
    ISUsuario  *stub;

    cntr = new CAUsuario();
    stub = new Stub();

    cntr->setCSUsuario(stub);

    cntr->executarOpcoes();

    delete cntr;
    delete stub;

    return 0;
}
