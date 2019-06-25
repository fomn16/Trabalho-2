#include "controladoraMain.h"
#define CLS system("cls");

/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  APRESENTACAO  //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////


WINDOW* CntrMain::createWindow(int height, int width, int y, int x, int color_id){
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

void CntrMain::printMenu(WINDOW *win, int y, int x, int highlight, int color_id, int qt_opcoes,const char **opcoes){
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

int CntrMain::getKey(WINDOW* win, int &highlight, int choice, int qt_opcoes){
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

void CntrMain::executar(){
    WINDOW *menu_win, *title_win;
    int max_h,max_w;
    int title_w = 40, title_h = 3; // tamanho da janela de titulo
    int menu_w = 50, menu_h = 11; // variaveis para o menu
    int highlight = 1, choice = 0;
    char name[] = "PAGINA INICIAL";
    const char* opcoes[5] = {"Usuarios","Autenticacao","Eventos", "Vendas", "Encerrar"};


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

    while (choice != 5){
        // reatribuindo os valores
        highlight = 1;
        choice = 0;
        // criando caixa de título
        title_win = createWindow(title_h,title_w,2,(max_w-title_w)/2,2);
        mvwprintw(title_win,title_h/2,(title_w-strlen(name))/2,"%s",name);
        wrefresh(title_win);

         // criando caixa de menu
        menu_win = createWindow(menu_h, menu_w,(max_h-menu_h+5)/2,(max_w-menu_w)/2,2);
        keypad(menu_win, TRUE); // permite o acesso a teclas especiais
        printMenu(menu_win, (menu_h)/5, (menu_w)/4, highlight, 2, 5, opcoes);
        while(1){
            choice = getKey(menu_win, highlight, choice, 5);
            printMenu(menu_win, menu_h/5, (menu_w)/4, highlight, 2, 5, opcoes);
            if(choice != 0) break;
        }

        switch(choice){
            case OPCAO_USUARIO:

                    clear();
                break;
            case OPCAO_AUTENTICACAO:

                    clear();
                break;
            case OPCAO_EVENTOS:
                    cnstE->cntrAEventos.executar();
                    clear();
                break;
            case OPCAO_VENDAS:
                    cnstV->cntrAVendas.executar();
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


void CntrMain::setCnsts(ConstrutoraEventos *cnstE, ConstrutoraVendas *cnstV){
    this->cnstE = cnstE;
    this->cnstV = cnstV;
}
