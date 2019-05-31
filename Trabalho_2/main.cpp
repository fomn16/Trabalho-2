#include "controladoraEventos.h"
#include "curses.h"

int main(){
    ConstrutoraEventos construtora;
    construtora.build();
    construtora.cntrAEventos.executar();
}
