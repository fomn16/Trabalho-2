#include "controladoraEventos.h"
#define CLS system("cls");

/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  Serviço  ///////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void CntrSEventos::cadastrar(Evento evento){
}

Evento CntrSEventos::pesquisar(CodigoEvento codigo){
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
    if(codigo.get()!="123"){
        throw invalid_argument("Arumento invalido");
    }
}

int CntrSEventos::nApresentacoes (CodigoEvento codigo){
    if(codigo.get()!="123"){
        throw invalid_argument("Arumento invalido");
    }
    return 1;
}

Apresentacao CntrSEventos::pesquisarApresentacoes (CodigoEvento codigo, int n){
    if(codigo.get()!="123"||n>=nApresentacoes(codigo)){
        throw invalid_argument("Arumento invalido");
    }

    Apresentacao apresentacoes[nApresentacoes(codigo)];

    CodigoApresentacao codigoApresentacao;
    codigoApresentacao.set("001");
    apresentacoes[0].setCodigo(codigoApresentacao);

    Data data;
    data.set("03/04/2020");
    apresentacoes[0].setData(data);

    return apresentacoes[n];
}

void CntrSEventos::cadastrarApresentacao(Apresentacao apresentacao){
}

void CntrSEventos::excluirApresentacao(CodigoApresentacao codigo){
}

/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  APRESENTACAO  //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////


WINDOW* CntrAEventos::createWindow(int height, int width, int y, int x, int color_id){
    WINDOW* win;
    int i;

    win = newwin(height, width, y, x);
    box(win,0,0);
    wbkgd(win, A_NORMAL |COLOR_PAIR(color_id) | ' ');

    /* start of shadow */
    attron(COLOR_PAIR(3));

    for(i = (x+2); i<(x+width+1); i++){
        move((y+height), i);
        addch(' ');
    }
    for(i = (y+1); i < (y+height+1); i++){
        move(i, (x+width));
        addch(' ');
        move(i, (x+width+1));
        addch(' ');
    }
    attroff(COLOR_PAIR(3));
    /* end of shadow */

    refresh();
    return win;
}

void CntrAEventos::printMenu(WINDOW *win, int y, int x, int highlight, int color_id, int qt_opcoes,const char **opcoes){
	int i;

	wbkgd(win, A_NORMAL |COLOR_PAIR(color_id) | ' ');
	for(i = 0; i < qt_opcoes; ++i)
	{	if(highlight == i + 1) /* High light the present choice */
		{	wattron(win, A_REVERSE);
			mvwprintw(win, y, x, "%s", opcoes[i]);
			wattroff(win, A_REVERSE);
		}
		else{
			mvwprintw(win, y, x, "%s", opcoes[i]);
		}
		++y;
	}
	wrefresh(win);
}

int CntrAEventos::getKey(WINDOW* win, int &highlight, int choice, int qt_opcoes){
    switch(wgetch(win)){
		    case KEY_UP:
				if(highlight == 1)
					highlight = qt_opcoes;
				else
					highlight--;
				break;
			case KEY_DOWN:
				if(highlight == qt_opcoes)
					highlight = 1;
				else
					highlight++;
				break;
			case 10: // codigo de ENTER em ASCII
				choice = highlight;
				break;
            default:
                refresh();
                break;
		}
    return choice;
}

void CntrAEventos::index(){
    int nEventos = 1;

    WINDOW* index_win;
    int max_h, max_w;
    int highlight = 1, choice = 0;
    int index_h = 20, index_w = 60;
    const char* teclas[1] = {"VOLTAR"};

    getmaxyx(stdscr,max_h,max_w);

    index_win = createWindow(index_h, index_w, max_h/4, (max_w-index_w)/2, 2);
    echo(); // habilitando echo

    mvwprintw(index_win,index_h/8,(index_w)/8,"%s","EVENTOS CADASTRADOS:");

    for(int i = 0; i<nEventos; i++){
        CodigoEvento codigo;
        codigo.set("123");
        Evento evento = cSEventos->pesquisar(codigo);
        mvwprintw(index_win,index_h/4+i,(index_w)/4, "%d - %s, codigo: %d", i, evento.getNome().get().c_str(), stoi(evento.getCodigo().get()));
    }

    noecho();

    printMenu(index_win,index_h-5,(index_w)/4, highlight, 2, 1, teclas);

    while(1){
        choice = getKey(index_win, highlight, choice, 2);
        printMenu(index_win,index_h-5,(index_w)/4, highlight, 2, 1, teclas);
        if(choice!=0) break;
    }
}

void CntrAEventos::pesquisar(){
    char inputCodigoEvento[5];
    CodigoEvento codigo;

    WINDOW* pesquisar_win;
    int max_h, max_w;
    int highlight = 1, choice = 0;
    int pesquisar_h = 20, pesquisar_w = 60;
    const char* teclas[2] = {"PESQUISAR","VOLTAR"};
    const char* teclas2[1] = {"CONTINUAR"};

    getmaxyx(stdscr,max_h,max_w);

    pesquisar_win = createWindow(pesquisar_h, pesquisar_w, max_h/4, (max_w-pesquisar_w)/2, 2);
    mvwprintw(pesquisar_win,pesquisar_h/8,(pesquisar_w)/8,"%s","PESQUISA DE EVENTOS");

    while(true){

        printMenu(pesquisar_win,pesquisar_h-5,(pesquisar_w)/4, highlight, 2, 2, teclas);

        echo(); // habilitando echo
        mvwprintw(pesquisar_win,pesquisar_h/4,(pesquisar_w)/4, "Insira o codigo do evento a ser observado:");
        mvwscanw(pesquisar_win,pesquisar_h/4+1,(pesquisar_w)/8,"%s",inputCodigoEvento);
        noecho();


        keypad(pesquisar_win, TRUE);
        printMenu(pesquisar_win,pesquisar_h-5,(pesquisar_w)/4, highlight, 2, 2, teclas);

        while(1){
            choice = getKey(pesquisar_win, highlight, choice, 2);
            printMenu(pesquisar_win,pesquisar_h-5,(pesquisar_w)/4, highlight, 2, 2, teclas);
            if(choice!=0) break;
        }

        if(choice == 2){
            return;
        }


        try{
            codigo.set(inputCodigoEvento);
        }
        catch(invalid_argument){
            delwin(pesquisar_win);
            pesquisar_win = createWindow(pesquisar_h, pesquisar_w, max_h/4, (max_w-pesquisar_w)/2, 2);
            mvwprintw(pesquisar_win,pesquisar_h/8,(pesquisar_w)/4, "Codigo invalido, tente novamente");

            printMenu(pesquisar_win,pesquisar_h-5,(pesquisar_w)/2 - 5, highlight, 2, 1, teclas2);

            while(1){
                choice = getKey(pesquisar_win, highlight, choice, 2);
                printMenu(pesquisar_win,pesquisar_h-5,(pesquisar_w)/4, highlight, 2, 1, teclas2);
                if(choice!=0) break;
            }

            break;
        }

        try{
            Evento evento;
            evento = cSEventos->pesquisar(codigo);

            delwin(pesquisar_win);
            pesquisar_win = createWindow(pesquisar_h, pesquisar_w, max_h/4, (max_w-pesquisar_w)/2, 2);

            echo();

            mvwprintw(pesquisar_win,pesquisar_h/8,(pesquisar_w)/8,"%s","PESQUISA DE EVENTOS");

            mvwprintw(pesquisar_win,pesquisar_h/4,(pesquisar_w)/5, "Codigo do evento: %s", evento.getCodigo().get().c_str());
            mvwprintw(pesquisar_win,pesquisar_h/4+1,(pesquisar_w)/5, "Nome do evento: %s", evento.getNome().get().c_str());
            mvwprintw(pesquisar_win,pesquisar_h/4+2,(pesquisar_w)/5, "Cidade de realizacao do evento: %s", evento.getCidade().get().c_str());
            mvwprintw(pesquisar_win,pesquisar_h/4+3,(pesquisar_w)/5, "Estado de realizacao do evento: %s", evento.getEstado().get().c_str());
            mvwprintw(pesquisar_win,pesquisar_h/4+4,(pesquisar_w)/5, "Classe do evento: %d", evento.getClasse().get());
            mvwprintw(pesquisar_win,pesquisar_h/4+5,(pesquisar_w)/5, "Faixa etaria do evento: %s", evento.getFaixa().get().c_str());
            mvwprintw(pesquisar_win,pesquisar_h/4+6,(pesquisar_w)/5, "APRESENTAÇOES:");

            for(int i=0; i<cSEventos->nApresentacoes(codigo); i++)
            {
                   mvwprintw(pesquisar_win,pesquisar_h/4+7+i,(pesquisar_w)/5, "Apresentação %d, codigo %s, data %s", i, cSEventos->pesquisarApresentacoes(codigo, i).getCodigo().get().c_str(), cSEventos->pesquisarApresentacoes(codigo, i).getData().get().c_str());
            }

            noecho();

            printMenu(pesquisar_win,pesquisar_h-5,(pesquisar_w)/4, highlight, 2, 1, teclas2);

            while(1){
                choice = getKey(pesquisar_win, highlight, choice, 2);
                printMenu(pesquisar_win,pesquisar_h-5,(pesquisar_w)/4, highlight, 2, 1, teclas2);
                if(choice!=0) break;
            }

            break;
        }
        catch(invalid_argument){
            delwin(pesquisar_win);
            pesquisar_win = createWindow(pesquisar_h, pesquisar_w, max_h/4, (max_w-pesquisar_w)/2, 2);
            mvwprintw(pesquisar_win,pesquisar_h/8,(pesquisar_w)/8,"%s","O codigo fornecido nao esta cadastrado.");

            printMenu(pesquisar_win,pesquisar_h-5,(pesquisar_w)/2 - 5, highlight, 2, 1, teclas2);

            while(1){
                choice = getKey(pesquisar_win, highlight, choice, 2);
                printMenu(pesquisar_win,pesquisar_h-5,(pesquisar_w)/4, highlight, 2, 1, teclas2);
                if(choice!=0) break;
            }
            break;
        }
    }
}

void CntrAEventos::cadastrar(){
    Evento evento;
    char stringCodigo[20], stringNome[50], stringCidade[20], stringEstado[20], stringClasse[20], stringFaixa[20];

    WINDOW* cadastrar_win;
    int max_h, max_w;
    int highlight = 1, choice = 0;
    int cadastrar_h = 20, cadastrar_w = 60;
    const char* teclas[1] = {"CONTINUAR"};

    getmaxyx(stdscr,max_h,max_w);

    cadastrar_win = createWindow(cadastrar_h, cadastrar_w, max_h/4, (max_w-cadastrar_w)/2, 2);

    while(true){
        mvwprintw(cadastrar_win,cadastrar_h/8,(cadastrar_w)/8,"%s","INFORME OS SEGUINTES DADOS:");
        mvwprintw(cadastrar_win,cadastrar_h/4+1,(cadastrar_w)/8,"%s","Codigo do evento: ");
        mvwprintw(cadastrar_win,cadastrar_h/4+2,(cadastrar_w)/8,"%s","Nome do evento: ");
        mvwprintw(cadastrar_win,cadastrar_h/4+3,(cadastrar_w)/8,"%s","Cidade de realizacao do evento: ");
        mvwprintw(cadastrar_win,cadastrar_h/4+4,(cadastrar_w)/8,"%s","Estado de realizacao do evento: ");
        mvwprintw(cadastrar_win,cadastrar_h/4+5,(cadastrar_w)/8,"%s","Classe do evento: ");
        mvwprintw(cadastrar_win,cadastrar_h/4+6,(cadastrar_w)/8,"%s","Faixa etaria do evento: ");

        try {
            echo();
            mvwscanw(cadastrar_win,cadastrar_h/4+1,(cadastrar_w)/8+18,"%s",stringCodigo);
            CodigoEvento codigo2;
            codigo2.set(stringCodigo);
            evento.setCodigo(codigo2);

            mvwscanw(cadastrar_win,cadastrar_h/4+2,(cadastrar_w)/8+16,"%s",stringNome);
            NomeEvento nome;
            nome.set(stringNome);
            evento.setNome(nome);

            mvwscanw(cadastrar_win,cadastrar_h/4+3,(cadastrar_w)/8+32,"%s",stringCidade);
            Cidade cidade;
            cidade.set(stringCidade);
            evento.setCidade(cidade);

            mvwscanw(cadastrar_win,cadastrar_h/4+4,(cadastrar_w)/8+32,"%s",stringEstado);
            Estado estado;
            estado.set(stringEstado);
            evento.setEstado(estado);

            mvwscanw(cadastrar_win,cadastrar_h/4+5,(cadastrar_w)/8+18,"%s",stringClasse);
            ClasseEvento classe;
            classe.set(stringClasse);
            evento.setClasse(classe);

            mvwscanw(cadastrar_win,cadastrar_h/4+6,(cadastrar_w)/8+24,"%s",stringFaixa);
            FaixaEtaria faixa;
            faixa.set(stringFaixa);
            evento.setFaixa(faixa);
            noecho();
        }
        catch(invalid_argument){
            delwin(cadastrar_win);
            cadastrar_win = createWindow(cadastrar_h, cadastrar_w, max_h/4, (max_w-cadastrar_w)/2, 2);
            mvwprintw(cadastrar_win,cadastrar_h/8,(cadastrar_w)/8,"%s","Um dado invalido foi inserido, tente novamente.");

            printMenu(cadastrar_win,cadastrar_h-5,(cadastrar_w)/2 - 5, highlight, 2, 1, teclas);

            while(1){
                choice = getKey(cadastrar_win, highlight, choice, 2);
                printMenu(cadastrar_win,cadastrar_h-5,(cadastrar_w)/4, highlight, 2, 1, teclas);
                if(choice!=0) break;
            }
            break;
        }
        try{
            cSEventos->cadastrar(evento);

            delwin(cadastrar_win);
            cadastrar_win = createWindow(cadastrar_h, cadastrar_w, max_h/4, (max_w-cadastrar_w)/2, 2);
            mvwprintw(cadastrar_win,cadastrar_h/8,(cadastrar_w)/8,"%s","Evento cadastrado (:");

            printMenu(cadastrar_win,cadastrar_h-5,(cadastrar_w)/2 - 5, highlight, 2, 1, teclas);

            while(1){
                choice = getKey(cadastrar_win, highlight, choice, 2);
                printMenu(cadastrar_win,cadastrar_h-5,(cadastrar_w)/4, highlight, 2, 1, teclas);
                if(choice!=0) break;
            }

            break;
        }
        catch(invalid_argument){
            delwin(cadastrar_win);
            cadastrar_win = createWindow(cadastrar_h, cadastrar_w, max_h/4, (max_w-cadastrar_w)/2, 2);
            mvwprintw(cadastrar_win,cadastrar_h/8,(cadastrar_w)/8,"%s","Houve um erro de banco de dados.");

            printMenu(cadastrar_win,cadastrar_h-5,(cadastrar_w)/2 - 5, highlight, 2, 1, teclas);

            while(1){
                choice = getKey(cadastrar_win, highlight, choice, 2);
                printMenu(cadastrar_win,cadastrar_h-5,(cadastrar_w)/4, highlight, 2, 1, teclas);
                if(choice!=0) break;
            }
            break;
        }
    }
}

void CntrAEventos::excluir(){

    WINDOW* excluir_win;
    int max_h, max_w;
    int highlight = 1, choice = 0;
    int excluir_h = 20, excluir_w = 60;
    const char* teclas[1] = {"CONTINUAR"};
    const char* teclas2[2] = {"EXCLUIR", "VOLTAR"};

    getmaxyx(stdscr,max_h,max_w);

    while(true){
        char stringCodigo[20];
        CodigoEvento codigo;

        excluir_win = createWindow(excluir_h, excluir_w, max_h/4, (max_w-excluir_w)/2, 2);

        mvwprintw(excluir_win,excluir_h/8,(excluir_w)/8,"%s","digite o codigo do evento a ser excluido");
        echo();
        mvwscanw(excluir_win,excluir_h/4+1,(excluir_w)/8+18,"%s",stringCodigo);
        noecho();
        highlight = 1;
        choice = 0;
        printMenu(excluir_win,excluir_h-5,(excluir_w)/4, highlight, 2, 2, teclas2);
        keypad(excluir_win, TRUE);
        while(1){
            choice = getKey(excluir_win, highlight, choice, 2);
            printMenu(excluir_win,excluir_h-5,(excluir_w)/4, highlight, 2, 2, teclas2);
            if(choice!=0) break;
        }
        if(choice==2){
            return;
        }
        highlight = 1;
        choice = 0;
        try{
            codigo.set(stringCodigo);
            try{
                cSEventos->excluir(codigo);
                delwin(excluir_win);
                excluir_win = createWindow(excluir_h, excluir_w, max_h/4, (max_w-excluir_w)/2, 2);
                mvwprintw(excluir_win,excluir_h/8,(excluir_w)/8,"%s","O evento foi excluido.");

                printMenu(excluir_win,excluir_h-5,(excluir_w)/2 - 5, highlight, 2, 1, teclas);

                while(1){
                    choice = getKey(excluir_win, highlight, choice, 2);
                    printMenu(excluir_win,excluir_h-5,(excluir_w)/4, highlight, 2, 1, teclas);
                    if(choice!=0) break;
                }
                break;
            }
            catch(invalid_argument){
                delwin(excluir_win);
                excluir_win = createWindow(excluir_h, excluir_w, max_h/4, (max_w-excluir_w)/2, 2);
                mvwprintw(excluir_win,excluir_h/8,(excluir_w)/8,"%s","Nao ha um evento cadastrado com este codigo.");

                printMenu(excluir_win,excluir_h-5,(excluir_w)/2 - 5, highlight, 2, 1, teclas);

                while(1){
                    choice = getKey(excluir_win, highlight, choice, 2);
                    printMenu(excluir_win,excluir_h-5,(excluir_w)/4, highlight, 2, 1, teclas);
                    if(choice!=0) break;
                }
                break;
            }
        }
        catch(invalid_argument){
            delwin(excluir_win);
            excluir_win = createWindow(excluir_h, excluir_w, max_h/4, (max_w-excluir_w)/2, 2);
            mvwprintw(excluir_win,excluir_h/8,(excluir_w)/8,"%s","O codigo fornecido e invalido, tente novamente.");

            printMenu(excluir_win,excluir_h-5,(excluir_w)/2 - 5, highlight, 2, 1, teclas);

            while(1){
                choice = getKey(excluir_win, highlight, choice, 2);
                printMenu(excluir_win,excluir_h-5,(excluir_w)/4, highlight, 2, 1, teclas);
                if(choice!=0) break;
            }
        }
    }
}

void CntrAEventos::editar(){
    WINDOW* editar_win;
    int max_h, max_w;
    int highlight = 1, choice = 0;
    int editar_h = 20, editar_w = 60;
    const char* teclas[1] = {"CONTINUAR"};
    const char* teclas2[2] = {"CONTINUAR", "VOLTAR"};

    char stringCodigo[20];
    CodigoEvento codigo;

    getmaxyx(stdscr,max_h,max_w);

    editar_win = createWindow(editar_h, editar_w, max_h/4, (max_w-editar_w)/2, 2);

        editar_win = createWindow(editar_h, editar_w, max_h/4, (max_w-editar_w)/2, 2);
        mvwprintw(editar_win,editar_h/8,(editar_w)/8,"%s","digite o codigo do evento a ser editado");
        echo();
        mvwscanw(editar_win,editar_h/8+1,(editar_w)/8,"%s",stringCodigo);
        noecho();

        printMenu(editar_win,editar_h-5,(editar_w)/4, highlight, 2, 2, teclas2);
        keypad(editar_win, TRUE);
        while(1){
            choice = getKey(editar_win, highlight, choice, 2);
            printMenu(editar_win,editar_h-5,(editar_w)/4, highlight, 2, 2, teclas2);
            if(choice!=0) break;
        }
        if(choice==2){
            return;
        }

        highlight = 1;
        choice = 0;
        try{
            codigo.set(stringCodigo);
            try{
                cSEventos->excluir(codigo);
                delwin(editar_win);
                editar_win = createWindow(editar_h, editar_w, max_h/4, (max_w-editar_w)/2, 2);
                cadastrar();
            }
            catch(invalid_argument){
                delwin(editar_win);
                editar_win = createWindow(editar_h, editar_w, max_h/4, (max_w-editar_w)/2, 2);
                mvwprintw(editar_win,editar_h/8,(editar_w)/8,"%s","Nao ha um evento cadastrado com este codigo.");

                printMenu(editar_win,editar_h-5,(editar_w)/2 - 5, highlight, 2, 1, teclas);

                while(1){
                    choice = getKey(editar_win, highlight, choice, 2);
                    printMenu(editar_win,editar_h-5,(editar_w)/4, highlight, 2, 1, teclas);
                    if(choice!=0) break;
                }
            }
        }
        catch(invalid_argument){
            delwin(editar_win);
            editar_win = createWindow(editar_h, editar_w, max_h/4, (max_w-editar_w)/2, 2);
            mvwprintw(editar_win,editar_h/8,(editar_w)/8,"%s","O codigo fornecido e invalido, tente novamente.");

            printMenu(editar_win,editar_h-5,(editar_w)/2 - 5, highlight, 2, 1, teclas);

            while(1){
                choice = getKey(editar_win, highlight, choice, 2);
                printMenu(editar_win,editar_h-5,(editar_w)/4, highlight, 2, 1, teclas);
                if(choice!=0) break;
            }
        }
}

void CntrAEventos::cadastrarApresentacao(){
    Apresentacao apresentacao;
    char stringCodigo[20], stringData[20], stringHorario[20], stringPreco[20], stringSala[20], stringDisponibilidade[20];

    WINDOW* cadastrarApresentacao_win;
    int max_h, max_w;
    int highlight = 1, choice = 0;
    int cadastrar_h = 20, cadastrar_w = 60;
    const char* teclas[1] = {"CONTINUAR"};

    getmaxyx(stdscr,max_h,max_w);

    cadastrarApresentacao_win = createWindow(cadastrar_h, cadastrar_w, max_h/4, (max_w-cadastrar_w)/2, 2);

    while(true){
        mvwprintw(cadastrarApresentacao_win,cadastrar_h/8,(cadastrar_w)/8,"%s","INFORME OS SEGUINTES DADOS:");
        mvwprintw(cadastrarApresentacao_win,cadastrar_h/4+1,(cadastrar_w)/8,"%s","Codigo da apresentacao: ");
        mvwprintw(cadastrarApresentacao_win,cadastrar_h/4+2,(cadastrar_w)/8,"%s","Data da apresentacao: ");
        mvwprintw(cadastrarApresentacao_win,cadastrar_h/4+3,(cadastrar_w)/8,"%s","Horario da apresentacao: ");
        mvwprintw(cadastrarApresentacao_win,cadastrar_h/4+4,(cadastrar_w)/8,"%s","Preco da apresentacao: ");
        mvwprintw(cadastrarApresentacao_win,cadastrar_h/4+5,(cadastrar_w)/8,"%s","Sala da apresentacao: ");
        mvwprintw(cadastrarApresentacao_win,cadastrar_h/4+6,(cadastrar_w)/8,"%s","Disponibilidade da apresentacao: ");

        try {
            echo();
            mvwscanw(cadastrarApresentacao_win,cadastrar_h/4+1,(cadastrar_w)/8+33,"%s",stringCodigo);
            CodigoApresentacao codigo2;
            codigo2.set(stringCodigo);
            apresentacao.setCodigo(codigo2);

            mvwscanw(cadastrarApresentacao_win,cadastrar_h/4+2,(cadastrar_w)/8+33,"%s",stringData);
            Data data;
            data.set(stringData);
            apresentacao.setData(data);

            mvwscanw(cadastrarApresentacao_win,cadastrar_h/4+3,(cadastrar_w)/8+33,"%s",stringHorario);
            Horario horario;
            horario.set(stringHorario);
            apresentacao.setHorario(horario);

            mvwscanw(cadastrarApresentacao_win,cadastrar_h/4+4,(cadastrar_w)/8+33,"%s",stringPreco);
            Preco preco;
            preco.set(stof(stringPreco));
            apresentacao.setPreco(preco);

            mvwscanw(cadastrarApresentacao_win,cadastrar_h/4+5,(cadastrar_w)/8+33,"%s",stringSala);
            NumeroSala sala;
            sala.set(stoi(stringSala));
            apresentacao.setSala(sala);

            mvwscanw(cadastrarApresentacao_win,cadastrar_h/4+6,(cadastrar_w)/8+33,"%s",stringDisponibilidade);
            Disponibilidade disponibilidade;
            disponibilidade.set(stringDisponibilidade);
            apresentacao.setDisponibilidade(disponibilidade);
            noecho();
        }
        catch(invalid_argument){
            delwin(cadastrarApresentacao_win);
            cadastrarApresentacao_win = createWindow(cadastrar_h, cadastrar_w, max_h/4, (max_w-cadastrar_w)/2, 2);
            mvwprintw(cadastrarApresentacao_win,cadastrar_h/8,(cadastrar_w)/8,"%s","Um dado invalido foi inserido, tente novamente.");

            printMenu(cadastrarApresentacao_win,cadastrar_h-5,(cadastrar_w)/2 - 5, highlight, 2, 1, teclas);

            while(1){
                choice = getKey(cadastrarApresentacao_win, highlight, choice, 2);
                printMenu(cadastrarApresentacao_win,cadastrar_h-5,(cadastrar_w)/4, highlight, 2, 1, teclas);
                if(choice!=0) break;
            }
            break;
        }
        try{
            cSEventos->cadastrarApresentacao(apresentacao);

            delwin(cadastrarApresentacao_win);
            cadastrarApresentacao_win = createWindow(cadastrar_h, cadastrar_w, max_h/4, (max_w-cadastrar_w)/2, 2);
            mvwprintw(cadastrarApresentacao_win,cadastrar_h/8,(cadastrar_w)/8,"%s","Apresentacao cadastrada (:");

            printMenu(cadastrarApresentacao_win,cadastrar_h-5,(cadastrar_w)/2 - 5, highlight, 2, 1, teclas);

            while(1){
                choice = getKey(cadastrarApresentacao_win, highlight, choice, 2);
                printMenu(cadastrarApresentacao_win,cadastrar_h-5,(cadastrar_w)/4, highlight, 2, 1, teclas);
                if(choice!=0) break;
            }

            break;
        }
        catch(invalid_argument){
            delwin(cadastrarApresentacao_win);
            cadastrarApresentacao_win = createWindow(cadastrar_h, cadastrar_w, max_h/4, (max_w-cadastrar_w)/2, 2);
            mvwprintw(cadastrarApresentacao_win,cadastrar_h/8,(cadastrar_w)/8,"%s","Houve um erro de banco de dados.");

            printMenu(cadastrarApresentacao_win,cadastrar_h-5,(cadastrar_w)/2 - 5, highlight, 2, 1, teclas);

            while(1){
                choice = getKey(cadastrarApresentacao_win, highlight, choice, 2);
                printMenu(cadastrarApresentacao_win,cadastrar_h-5,(cadastrar_w)/4, highlight, 2, 1, teclas);
                if(choice!=0) break;
            }
            break;
        }
    }
}

void CntrAEventos::excluirApresentacao(){

    WINDOW* excluirApresentacao_win;
    int max_h, max_w;
    int highlight = 1, choice = 0;
    int excluir_h = 20, excluir_w = 60;
    const char* teclas[1] = {"CONTINUAR"};
    const char* teclas2[2] = {"EXCLUIR", "VOLTAR"};

    getmaxyx(stdscr,max_h,max_w);

    while(true){
        char stringCodigo[20];
        CodigoApresentacao codigo;

        excluirApresentacao_win = createWindow(excluir_h, excluir_w, max_h/4, (max_w-excluir_w)/2, 2);

        mvwprintw(excluirApresentacao_win,excluir_h/8,(excluir_w)/8,"%s","digite o codigo da apresentacao a ser excluida");
        echo();
        mvwscanw(excluirApresentacao_win,excluir_h/4+1,(excluir_w)/8+18,"%s",stringCodigo);
        noecho();
        highlight = 1;
        choice = 0;
        printMenu(excluirApresentacao_win,excluir_h-5,(excluir_w)/4, highlight, 2, 2, teclas2);
        keypad(excluirApresentacao_win, TRUE);
        while(1){
            choice = getKey(excluirApresentacao_win, highlight, choice, 2);
            printMenu(excluirApresentacao_win,excluir_h-5,(excluir_w)/4, highlight, 2, 2, teclas2);
            if(choice!=0) break;
        }
        if(choice==2){
            return;
        }
        highlight = 1;
        choice = 0;
        try{
            codigo.set(stringCodigo);
            try{
                cSEventos->excluirApresentacao(codigo);
                delwin(excluirApresentacao_win);
                excluirApresentacao_win = createWindow(excluir_h, excluir_w, max_h/4, (max_w-excluir_w)/2, 2);
                mvwprintw(excluirApresentacao_win,excluir_h/8,(excluir_w)/8,"%s","A apresentacao foi excluida.");

                printMenu(excluirApresentacao_win,excluir_h-5,(excluir_w)/2 - 5, highlight, 2, 1, teclas);

                while(1){
                    choice = getKey(excluirApresentacao_win, highlight, choice, 2);
                    printMenu(excluirApresentacao_win,excluir_h-5,(excluir_w)/4, highlight, 2, 1, teclas);
                    if(choice!=0) break;
                }
                break;
            }
            catch(invalid_argument){
                delwin(excluirApresentacao_win);
                excluirApresentacao_win = createWindow(excluir_h, excluir_w, max_h/4, (max_w-excluir_w)/2, 2);
                mvwprintw(excluirApresentacao_win,excluir_h/8,(excluir_w)/8,"%s","Nao ha uma apresentacao cadastrada com este codigo.");

                printMenu(excluirApresentacao_win,excluir_h-5,(excluir_w)/2 - 5, highlight, 2, 1, teclas);

                while(1){
                    choice = getKey(excluirApresentacao_win, highlight, choice, 2);
                    printMenu(excluirApresentacao_win,excluir_h-5,(excluir_w)/4, highlight, 2, 1, teclas);
                    if(choice!=0) break;
                }
                break;
            }
        }
        catch(invalid_argument){
            delwin(excluirApresentacao_win);
            excluirApresentacao_win = createWindow(excluir_h, excluir_w, max_h/4, (max_w-excluir_w)/2, 2);
            mvwprintw(excluirApresentacao_win,excluir_h/8,(excluir_w)/8,"%s","O codigo fornecido e invalido, tente novamente.");

            printMenu(excluirApresentacao_win,excluir_h-5,(excluir_w)/2 - 5, highlight, 2, 1, teclas);

            while(1){
                choice = getKey(excluirApresentacao_win, highlight, choice, 2);
                printMenu(excluirApresentacao_win,excluir_h-5,(excluir_w)/4, highlight, 2, 1, teclas);
                if(choice!=0) break;
            }
        }
    }
}

void CntrAEventos::editarApresentacao(){
    WINDOW* editarApresentacao_win;
    int max_h, max_w;
    int highlight = 1, choice = 0;
    int editar_h = 20, editar_w = 60;
    const char* teclas[1] = {"CONTINUAR"};
    const char* teclas2[2] = {"CONTINUAR", "VOLTAR"};

    char stringCodigo[20];
    CodigoApresentacao codigo;

    getmaxyx(stdscr,max_h,max_w);

    editarApresentacao_win = createWindow(editar_h, editar_w, max_h/4, (max_w-editar_w)/2, 2);

        editarApresentacao_win = createWindow(editar_h, editar_w, max_h/4, (max_w-editar_w)/2, 2);
        mvwprintw(editarApresentacao_win,editar_h/8,(editar_w)/8,"%s","digite o codigo da apresentacao a ser editada");
        echo();
        mvwscanw(editarApresentacao_win,editar_h/8+1,(editar_w)/8,"%s",stringCodigo);
        noecho();

        printMenu(editarApresentacao_win,editar_h-5,(editar_w)/4, highlight, 2, 2, teclas2);
        keypad(editarApresentacao_win, TRUE);
        while(1){
            choice = getKey(editarApresentacao_win, highlight, choice, 2);
            printMenu(editarApresentacao_win,editar_h-5,(editar_w)/4, highlight, 2, 2, teclas2);
            if(choice!=0) break;
        }
        if(choice==2){
            return;
        }

        highlight = 1;
        choice = 0;
        try{
            codigo.set(stringCodigo);
            try{
                cSEventos->excluirApresentacao(codigo);
                delwin(editarApresentacao_win);
                editarApresentacao_win = createWindow(editar_h, editar_w, max_h/4, (max_w-editar_w)/2, 2);
                cadastrarApresentacao();
            }
            catch(invalid_argument){
                delwin(editarApresentacao_win);
                editarApresentacao_win = createWindow(editar_h, editar_w, max_h/4, (max_w-editar_w)/2, 2);
                mvwprintw(editarApresentacao_win,editar_h/8,(editar_w)/8,"%s","Nao ha uma apresentacao cadastrada com este codigo.");

                printMenu(editarApresentacao_win,editar_h-5,(editar_w)/2 - 5, highlight, 2, 1, teclas);

                while(1){
                    choice = getKey(editarApresentacao_win, highlight, choice, 2);
                    printMenu(editarApresentacao_win,editar_h-5,(editar_w)/4, highlight, 2, 1, teclas);
                    if(choice!=0) break;
                }
            }
        }
        catch(invalid_argument){
            delwin(editarApresentacao_win);
            editarApresentacao_win = createWindow(editar_h, editar_w, max_h/4, (max_w-editar_w)/2, 2);
            mvwprintw(editarApresentacao_win,editar_h/8,(editar_w)/8,"%s","O codigo fornecido e invalido, tente novamente.");

            printMenu(editarApresentacao_win,editar_h-5,(editar_w)/2 - 5, highlight, 2, 1, teclas);

            while(1){
                choice = getKey(editarApresentacao_win, highlight, choice, 2);
                printMenu(editarApresentacao_win,editar_h-5,(editar_w)/4, highlight, 2, 1, teclas);
                if(choice!=0) break;
            }
        }
}

void CntrAEventos::executar(){
    WINDOW *menu_win, *title_win;
    int max_h,max_w;
    int title_w = 40, title_h = 3; // tamanho da janela de titulo
    int menu_w = 50, menu_h = 11; // variaveis para o menu
    int highlight = 1, choice = 0;
    char name[] = "EVENTOS";
    const char* opcoes[9] = {"Apresentar todos os eventos","Ver dados de um evento","Cadastrar evento", "Excluir evento", "Editar evento","Cadastrar apresentacao", "Editar apresentacao", "Excluir apresentacao", "Encerrar"};


    initscr();// iniciando biblioteca curses
    noecho(); // desabilitando echo
    curs_set(0); // nao permite que o cursor seja mostrado
    start_color(); //iniciando cores
    init_pair(1, COLOR_BLACK, COLOR_CYAN);
    init_pair(2, COLOR_YELLOW, COLOR_WHITE);
    init_pair(3, COLOR_BLACK, COLOR_BLACK);

    wbkgd(stdscr, COLOR_PAIR(1)); // mudando cores da tela principal
    refresh(); // escrevendo a tela pai

    getmaxyx(stdscr,max_h,max_w); // pegando tamanhos do terminal

    while (choice != 9){
        // reatribuindo os valores
        highlight = 1;
        choice = 0;
        // criando caixa de título
        title_win = createWindow(title_h,title_w,2,(max_w-title_w)/2,2);
        mvwprintw(title_win,title_h/2,(title_w-strlen(name))/2,"%s",name);
        wrefresh(title_win);

         // criando caixa de menu
        menu_win = createWindow(menu_h, menu_w,(max_h-menu_h+9)/2,(max_w-menu_w)/2,2);
        keypad(menu_win, TRUE); // permite o acesso a teclas especiais
        printMenu(menu_win, (menu_h)/9, (menu_w)/4, highlight, 2, 9, opcoes);
        while(1){
            choice = getKey(menu_win, highlight, choice, 9);
            printMenu(menu_win, menu_h/9, (menu_w)/4, highlight, 2, 9, opcoes);
            if(choice != 0) break;
        }

        switch(choice){
            case OPCAO_APRESENTAR_TODOS:
                    index();
                    clear();
                break;
            case OPCAO_APRESENTAR_EVENTO:
                    pesquisar();
                    clear();
                break;
            case OPCAO_CADASTRAR:
                    cadastrar();
                    clear();
                break;
            case OPCAO_EXCLUIR:
                    excluir();
                    clear();
                break;
            case OPCAO_EDITAR:
                    editar();
                    clear();
                break;
             case OPCAO_CADASTRAR_APRESENTACAO:
                    cadastrarApresentacao();
                    clear();
                break;
             case OPCAO_EDITAR_APRESENTACAO:
                    editarApresentacao();
                    clear();
                break;
             case OPCAO_EXCLUIR_APRESENTACAO:
                    excluirApresentacao();
                    clear();
                break;
        }
    }
    delwin(title_win);
    delwin(menu_win);
    endwin();
return;
}

/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  CONTROLADORA  //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////


void CntrAEventos::setCSEventos(ISEventos *cSEventos){
    this->cSEventos = cSEventos;
}
