#include "controladoraVendas.h"
#define CLS system("cls");

/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  Serviço  ///////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void CntrSVendas::processarVenda(CPF cpf, CodigoEvento codigoEvento, CodigoApresentacao codigoApresentacao){


}
Ingresso CntrSVendas::pesquisarIngresso(CPF cpf, int n){
    Ingresso a;
    return a;

}
int CntrSVendas::nIngressos(CPF cpf){

    return 0;
}


/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  APRESENTACAO  //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////


WINDOW* CntrAVendas::createWindow(int height, int width, int y, int x, int color_id){
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

void CntrAVendas::printMenu(WINDOW *win, int y, int x, int highlight, int color_id, int qt_opcoes,const char **opcoes){
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

int CntrAVendas::getKey(WINDOW* win, int &highlight, int choice, int qt_opcoes){
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

void CntrAVendas::comprar(){
    char stringCPF[20], stringCodigoEvento[20], stringCodigoApresentacao[20];

    WINDOW* comprar_win;
    int max_h, max_w;
    int highlight = 1, choice = 0;
    int comprar_h = 20, comprar_w = 60;
    const char* teclas[1] = {"CONTINUAR"};

    getmaxyx(stdscr,max_h,max_w);

    comprar_win = createWindow(comprar_h, comprar_w, max_h/4, (max_w-comprar_w)/2, 2);

    while(true){
        CPF cpf;
        CodigoEvento codigoEvento;
        CodigoApresentacao codigoApresentacao;

        mvwprintw(comprar_win,comprar_h/8,(comprar_w)/8,"%s","INFORME OS SEGUINTES DADOS:");
        mvwprintw(comprar_win,comprar_h/4+1,(comprar_w)/8,"%s","Seu CPF: ");
        mvwprintw(comprar_win,comprar_h/4+2,(comprar_w)/8,"%s","Codigo do evento: ");
        mvwprintw(comprar_win,comprar_h/4+3,(comprar_w)/8,"%s","Codigo da apresentacao: ");

        try {
            echo();
            mvwscanw(comprar_win,comprar_h/4+1,(comprar_w)/8+24,"%s",stringCPF);
            cpf.set(stringCPF);

            mvwscanw(comprar_win,comprar_h/4+2,(comprar_w)/8+24,"%s",stringCodigoEvento);
            codigoEvento.set(stringCodigoEvento);

            mvwscanw(comprar_win,comprar_h/4+3,(comprar_w)/8+24,"%s",stringCodigoApresentacao);
            codigoApresentacao.set(stringCodigoApresentacao);

            noecho();
        }
        catch(invalid_argument){
            delwin(comprar_win);
            comprar_win = createWindow(comprar_h, comprar_w, max_h/4, (max_w-comprar_w)/2, 2);
            mvwprintw(comprar_win,comprar_h/8,(comprar_w)/8,"%s","Um dado invalido foi inserido, tente novamente.");

            printMenu(comprar_win,comprar_h-5,(comprar_w)/2 - 5, highlight, 2, 1, teclas);

            while(1){
                choice = getKey(comprar_win, highlight, choice, 2);
                printMenu(comprar_win,comprar_h-5,(comprar_w)/4, highlight, 2, 1, teclas);
                if(choice!=0) break;
            }
            break;
        }
        try{
            cSVendas->processarVenda(cpf, codigoEvento, codigoApresentacao);

            delwin(comprar_win);
            comprar_win = createWindow(comprar_h, comprar_w, max_h/4, (max_w-comprar_w)/2, 2);
            mvwprintw(comprar_win,comprar_h/8,(comprar_w)/8,"%s","Compra realizada com sucesso.");

            printMenu(comprar_win,comprar_h-5,(comprar_w)/2 - 5, highlight, 2, 1, teclas);

            while(1){
                choice = getKey(comprar_win, highlight, choice, 2);
                printMenu(comprar_win,comprar_h-5,(comprar_w)/4, highlight, 2, 1, teclas);
                if(choice!=0) break;
            }

            break;
        }
        catch(invalid_argument){
            delwin(comprar_win);
            comprar_win = createWindow(comprar_h, comprar_w, max_h/4, (max_w-comprar_w)/2, 2);
            mvwprintw(comprar_win,comprar_h/8,(comprar_w)/8,"%s","Houve um erro de banco de dados.");

            printMenu(comprar_win,comprar_h-5,(comprar_w)/2 - 5, highlight, 2, 1, teclas);

            while(1){
                choice = getKey(comprar_win, highlight, choice, 2);
                printMenu(comprar_win,comprar_h-5,(comprar_w)/4, highlight, 2, 1, teclas);
                if(choice!=0) break;
            }
            break;
        }
    }
}

void CntrAVendas::pesquisarIngresso(){
    char stringCPF[20];

    WINDOW* pesquisarIngresso_win;
    int max_h, max_w;
    int highlight = 1, choice = 0;
    int pesquisar_h = 20, pesquisar_w = 60;
    const char* teclas[1] = {"CONTINUAR"};

    getmaxyx(stdscr,max_h,max_w);

    pesquisarIngresso_win = createWindow(pesquisar_h, pesquisar_w, max_h/4, (max_w-pesquisar_w)/2, 2);

    while(true){
        CPF cpf;
        CodigoEvento codigoEvento;
        CodigoApresentacao codigoApresentacao;

        mvwprintw(pesquisarIngresso_win,pesquisar_h/8,(pesquisar_w)/8,"%s","INFORME OS SEGUINTES DADOS:");
        mvwprintw(pesquisarIngresso_win,pesquisar_h/4+1,(pesquisar_w)/8,"%s","Seu CPF: ");

        try {
            echo();
            mvwscanw(pesquisarIngresso_win,pesquisar_h/4+1,(pesquisar_w)/8+24,"%s",stringCPF);
            cpf.set(stringCPF);
            noecho();
        }
        catch(invalid_argument){
            delwin(pesquisarIngresso_win);
            pesquisarIngresso_win = createWindow(pesquisar_h, pesquisar_w, max_h/4, (max_w-pesquisar_w)/2, 2);
            mvwprintw(pesquisarIngresso_win,pesquisar_h/8,(pesquisar_w)/8,"%s","Um dado invalido foi inserido, tente novamente.");

            printMenu(pesquisarIngresso_win,pesquisar_h-5,(pesquisar_w)/2 - 5, highlight, 2, 1, teclas);

            while(1){
                choice = getKey(pesquisarIngresso_win, highlight, choice, 2);
                printMenu(pesquisarIngresso_win,pesquisar_h-5,(pesquisar_w)/4, highlight, 2, 1, teclas);
                if(choice!=0) break;
            }
            break;
        }
        try{
            cSVendas->processarVenda(cpf, codigoEvento, codigoApresentacao);

            delwin(pesquisarIngresso_win);
            pesquisarIngresso_win = createWindow(pesquisar_h, pesquisar_w, max_h/4, (max_w-pesquisar_w)/2, 2);
            mvwprintw(pesquisarIngresso_win,pesquisar_h/8,(pesquisar_w)/8,"%s","Ingressos nesta conta:");

            printMenu(pesquisarIngresso_win,pesquisar_h-5,(pesquisar_w)/2 - 5, highlight, 2, 1, teclas);

            while(1){
                choice = getKey(pesquisarIngresso_win, highlight, choice, 2);
                printMenu(pesquisarIngresso_win,pesquisar_h-5,(pesquisar_w)/4, highlight, 2, 1, teclas);
                if(choice!=0) break;
            }

            break;
        }
        catch(invalid_argument){
            delwin(pesquisarIngresso_win);
            pesquisarIngresso_win = createWindow(pesquisar_h, pesquisar_w, max_h/4, (max_w-pesquisar_w)/2, 2);
            mvwprintw(pesquisarIngresso_win,pesquisar_h/8,(pesquisar_w)/8,"%s","Houve um erro de banco de dados.");

            printMenu(pesquisarIngresso_win,pesquisar_h-5,(pesquisar_w)/2 - 5, highlight, 2, 1, teclas);

            while(1){
                choice = getKey(pesquisarIngresso_win, highlight, choice, 2);
                printMenu(pesquisarIngresso_win,pesquisar_h-5,(pesquisar_w)/4, highlight, 2, 1, teclas);
                if(choice!=0) break;
            }
            break;
        }
    }
}

void CntrAVendas::executar(){
    WINDOW *menu_win, *title_win;
    int max_h,max_w;
    int title_w = 40, title_h = 3; // tamanho da janela de titulo
    int menu_w = 50, menu_h = 11; // variaveis para o menu
    int highlight = 1, choice = 0;
    char name[] = "Vendas";
    const char* opcoes[3] = {"Comprar ingresso","Pesquisar ingresso", "Encerrar"};


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

    while (choice != 3){
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
        printMenu(menu_win, (menu_h)/9, (menu_w)/4, highlight, 2, 3, opcoes);
        while(1){
            choice = getKey(menu_win, highlight, choice, 3);
            printMenu(menu_win, menu_h/9, (menu_w)/4, highlight, 2, 3, opcoes);
            if(choice != 0) break;
        }

        switch(choice){
            case OPCAO_COMPRAR:
                    comprar();
                    clear();
                break;
            case OPCAO_PESQUISAR_INGRESSO:
                    pesquisarIngresso();
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


void CntrAVendas::setCSVendas(ISVendas *cSVendas){
    this->cSVendas = cSVendas;
}
