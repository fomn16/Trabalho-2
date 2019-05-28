#include "controladoraEventos.h"
#define CLS system("cls");

/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  Servicos  //////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void ControladoraServicoEventos::cadastrar(){
}

void ControladoraServicoEventos::pesquisar(CodigoEvento codigo) const{
    cout<<"*o banco de dados foi consultado*"<<endl;
    if(stoi(codigo.get())!=123){
        throw invalid_argument("Argumento invalido");
    }
}

void ControladoraServicoEventos::excluir(){
}

void ControladoraServicoEventos::alterar(){
}


/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  APRESENTACAO  //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////


void ControladoraApresentacaoEventos::operacaoExecutada() const{
    cout<<"pressione qualquer botao para continuar"<<endl;
    getch();
}

void ControladoraApresentacaoEventos::apresentarOpcoes(){
    cout<<"Selecione uma opcao:"<<endl;
    cout<<"1 - Apresentar todos os eventos"<<endl;
    cout<<"2 - Ver dados de um evento"<<endl;
    cout<<"3 - Cadastrar evento"<<endl;
    cout<<"4 - Excluir evento"<<endl;
    cout<<"5 - Alterar evento"<<endl;
    cout<<"6 - Encerrar"<<endl;
}

void ControladoraApresentacaoEventos::apresentarTodos() const{
    int nEventos = 5;
    cout<<"Eventos cadastrados:"<<endl;
    for(int i = 0; i<nEventos; i++){
        cout<<"evento "<< i <<endl;
    }
    operacaoExecutada();
}

void ControladoraApresentacaoEventos::apresentarEvento() const{
    string inputCodigoEvento;
    CodigoEvento codigo;
    while(true){
        CLS;
        cout<<"Insira o codigo do evento a ser observado:"<<endl;
        cin>>inputCodigoEvento;
        try{
            codigo.set(inputCodigoEvento);
            break;
        }
        catch(invalid_argument){
            CLS;
            cout<<"Codigo invalido."<<endl;
            operacaoExecutada();
        }
    }

    CLS;
    try{
        CLS;
        controladoraServicoEventos.pesquisar(codigo);
        operacaoExecutada();
        CLS;
        cout<<"Dados do evento:"<<endl;
        operacaoExecutada();
    }
    catch(invalid_argument){
        cout<<"O codigo fornecido nao esta cadastrado"<<endl;
        operacaoExecutada();
    }
}

void ControladoraApresentacaoEventos::executar(){
    unsigned int escolha = 0;
    while (escolha != 6){
        CLS;
        do {
            apresentarOpcoes();
            cout<<"Sua opcao:"<<endl;
            cin>>escolha;
        } while(escolha == 0 || escolha > NUMERO_OPCOES);
        CLS;
        switch(escolha){
            case OPCAO_APRESENTAR_TODOS:
                    apresentarTodos();
                break;
            case OPCAO_APRESENTAR_EVENTO:
                    apresentarEvento();
                break;
            case OPCAO_CADASTRAR:
                    controladoraServicoEventos.cadastrar();
                break;
            case OPCAO_EXCLUIR:
                    controladoraServicoEventos.excluir();
                break;
            case OPCAO_ALTERAR:
                    controladoraServicoEventos.alterar();
                break;
        }
    }
}
