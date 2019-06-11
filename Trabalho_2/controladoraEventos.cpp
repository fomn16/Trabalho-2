#include "controladoraEventos.h"
#define CLS system("cls");

/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  Serviço  ///////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void CntrSEventos::cadastrar(Evento evento){
}

Evento CntrSEventos::pesquisar(CodigoEvento codigo){
    cout<<"*o banco de dados foi consultado*"<<endl;

    if(codigo.get()!= "123"){
        throw invalid_argument("Argumento invalido");
    }

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

    return evento;
}
void CntrSEventos::excluir(CodigoEvento codigo){
    if(codigo.get()!="123")
    {
        throw invalid_argument("Arumento invalido");
    }
}
void CntrSEventos::editar(){
}
/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  APRESENTACAO  //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void CntrAEventos::index(){
    int nEventos = 1;
    cout<<"Eventos cadastrados:"<<endl;
    for(int i = 0; i<nEventos; i++){
        CodigoEvento codigo;
        codigo.set("123");
        Evento evento = cSEventos->pesquisar(codigo);
        cout<<i<<" - Evento teste, codigo "<<evento.getCodigo().get()<<endl;
    }
    operacaoExecutada();
}

void CntrAEventos::pesquisar(){
    string inputCodigoEvento;
    CodigoEvento codigo;
    while(true){
        CLS;
        cout<<"Insira o codigo do evento a ser observado:"<<endl;
        cin>>inputCodigoEvento;
        try{
            codigo.set(inputCodigoEvento);
        }
        catch(invalid_argument){
            CLS;
            cout<<"Codigo invalido, tente novamente."<<endl;
            operacaoExecutada();
            break;
        }

        try{
            CLS;
            Evento evento;
            evento = cSEventos->pesquisar(codigo);
            operacaoExecutada();
            CLS;
            cout<<"Dados do evento:"<<endl;
            cout<<"Codigo do evento: "<<evento.getCodigo().get()<<endl;
            cout<<"Nome do evento: "<<evento.getNome().get()<<endl;
            cout<<"Cidade de realizacao do evento: "<<evento.getCidade().get()<<endl;
            cout<<"Estado de realizacao do evento: "<<evento.getEstado().get()<<endl;
            cout<<"Classe do evento: "<<evento.getClasse().get()<<endl;
            cout<<"Faixa etaria do evento: "<<evento.getFaixa().get()<<endl;

            operacaoExecutada();
            break;
        }
        catch(invalid_argument){
            cout<<"O codigo fornecido nao esta cadastrado"<<endl;
            operacaoExecutada();
            break;
        }
    }
}

void CntrAEventos::cadastrar(){
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
        }
        catch(invalid_argument){
            cout<<"Um dado invalido foi inserido, tente novamente."<<endl;
            operacaoExecutada();
            break;
        }
        CLS;
        try{
            cSEventos->cadastrar(evento);
            cout<<"*Banco de dados acessado, evento cadastrado*"<<endl<<"pressione qualquer tecla para continuar"<<endl;
            getch();
            break;
        }
        catch(invalid_argument){
            cout<<"Houve um erro de banco de dados, tente novamente"<<endl;
            getch();
            break;
        }
    }
}

void CntrAEventos::excluir(){
    while(true){
        CLS;
        string stringCodigo;
        CodigoEvento codigo;

        cout<<"digite o codigo do evento a ser excluido"<<endl;
        cin>>stringCodigo;
        try{
            codigo.set(stringCodigo);
            try{
                cSEventos->excluir(codigo);
                cout<<"Evento excluido"<<endl;
                operacaoExecutada();
                break;
            }
            catch(invalid_argument){
                cout<<"Nao ha um evento cadastrado com este codigo"<<endl;
                operacaoExecutada();
                break;
            }
        }
        catch(invalid_argument){
            cout<<"O codigo fornecido e invalido, tente novamente"<<endl;
            operacaoExecutada();
        }
    }
}

void CntrAEventos::editar(){
}

void CntrAEventos::apresentarOpcoes(){
    cout<<"Selecione uma opcao:"<<endl;
    cout<<"1 - Apresentar todos os eventos"<<endl;
    cout<<"2 - Ver dados de um evento"<<endl;
    cout<<"3 - Cadastrar evento"<<endl;
    cout<<"4 - Excluir evento"<<endl;
    cout<<"5 - Alterar evento"<<endl;
    cout<<"6 - Encerrar"<<endl;
}

void CntrAEventos::executar(){
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
                    index();
                break;
            case OPCAO_APRESENTAR_EVENTO:
                    pesquisar();
                break;
            case OPCAO_CADASTRAR:
                    cadastrar();
                break;
            case OPCAO_EXCLUIR:
                    excluir();
                break;
            case OPCAO_EDITAR:
                    editar();
                break;
        }
    }
}


/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  CONTROLADORA  //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////


void CntrAEventos::setCSEventos(ISEventos *cSEventos){
    this->cSEventos = cSEventos;
}
