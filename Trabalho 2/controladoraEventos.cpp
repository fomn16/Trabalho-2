#include "controladoraEventos.h"
#define CLS system("cls");

/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  Servicos  //////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void ControladoraServicoEventos::cadastrar(){
    Evento evento;
    string stringCodigo, stringNome, stringCidade, stringEstado, stringClasse, stringFaixa;

    while(true){
        CLS;
        cout<<"Informe os seguintes dados:"<<endl;

        try {
            cout<<"Codigo do evento: ";
            cin>>stringCodigo;
            CodigoEvento codigo2;
            codigo2.set(stringCodigo);
            evento.setCodigo(codigo2);

            cout<<"Nome do evento: ";
            cin>>stringNome;
            NomeEvento nome;
            nome.set(stringNome);
            evento.setNome(nome);

            cout<<"Cidade de realizacao do evento: ";
            cin>>stringCidade;
            Cidade cidade;
            cidade.set(stringCidade);
            evento.setCidade(cidade);

            cout<<"Estado de realizacao do evento: ";
            cin>>stringEstado;
            Estado estado;
            estado.set(stringEstado);
            evento.setEstado(estado);

            cout<<"Classe do evento: ";
            cin>>stringClasse;
            ClasseEvento classe;
            classe.set(stringClasse);
            evento.setClasse(classe);

            cout<<"Faixa etaria do evento: ";
            cin>>stringFaixa;
            FaixaEtaria faixa;
            faixa.set(stringFaixa);
            evento.setFaixa(faixa);
            break;
        }
        catch(invalid_argument){
            cout<<"Um dado invalido foi inserido, tente novamente."<<endl;
            getch();
        }
    }
    CLS;
    cout<<"*Banco de dados acessado, evento cadastrado*"<<endl<<"pressione qualquer tecla para continuar"<<endl;
    getch();
}

Evento ControladoraServicoEventos::pesquisar(CodigoEvento codigo) const{
    cout<<"*o banco de dados foi consultado*"<<endl;

    Evento evento;

    CodigoEvento codigo2;
    codigo2.set("123");
    evento.setCodigo(codigo2);

    NomeEvento nome;
    nome.set("Evento teste");
    evento.setNome(nome);

    Cidade cidade;
    cidade.set("Cidade teste");
    evento.setCidade(cidade);

    Estado estado;
    estado.set("DF");
    evento.setEstado(estado);

    ClasseEvento classe;
    classe.set("1");
    evento.setClasse(classe);

    FaixaEtaria faixa;
    faixa.set("L");
    evento.setFaixa(faixa);


    if(stoi(codigo.get())!= stoi(evento.getCodigo().get())){
        throw invalid_argument("Argumento invalido");
    }
    return evento;
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
    int nEventos = 1;
    cout<<"Eventos cadastrados:"<<endl;
    for(int i = 0; i<nEventos; i++){
        cout<<i<<" - Evento teste, codigo 123"<<endl;
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
        Evento evento;
        evento = controladoraServicoEventos.pesquisar(codigo);
        operacaoExecutada();
        CLS;
        cout<<"Dados do evento:"<<endl;
        cout<<"Codigo do evento: "<<evento.getCodigo().get()<<endl;
        cout<<"Nome do evento: "<<evento.getNome().get()<<endl;
        cout<<"Cidade de realizacao do evento: "<<evento.getCidade().get()<<endl;
        cout<<"Estado de realizacao do evento: "<<evento.getEstado().get()<<endl;
        cout<<"Classe do evento: "<<evento.getClasse().get()<<endl;
        cout<<"Faixa Etaria do evento: "<<evento.getFaixa().get()<<endl;

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
