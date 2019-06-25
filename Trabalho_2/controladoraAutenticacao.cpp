#include "controladoraAutenticacao.h"
/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  APRESENTACAO  //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
WINDOW* CAAutenticacao::createWindow(int height, int width, int y, int x, int color_id){
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

void CAAutenticacao::printMenu(WINDOW *win, int y, int x, int highlight, int color_id, int qt_opcoes,const char **opcoes){
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

int CAAutenticacao::getKey(WINDOW* win, int &highlight, int choice, int qt_opcoes){
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

 Usuario CAAutenticacao::usuario_atual;

void CAAutenticacao::executarOpcoes(){
    WINDOW *menu_win, *title_win;
    int max_h,max_w;
    int title_w = 40, title_h = 3; // tamanho da janela de titulo
    int menu_w = 50, menu_h = 10; // variaveis para o menu
    int highlight = 1, choice = 0;
    char name[] = "AUTENTICACAO";

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

        // criando caixa de título
        title_win = createWindow(title_h,title_w,2,(max_w-title_w)/2,2);
        mvwprintw(title_win,title_h/2,(title_w-strlen(name))/2,"%s",name);
        wrefresh(title_win);

        CPF cpf; Senha senha;
        char dado1[20], dado2[20];

        // criando caixa de menu
        menu_win = createWindow(menu_h, menu_w,(max_h-menu_h+5)/2,(max_w-menu_w)/2,2);

        echo();
        mvwprintw(menu_win,menu_h/8,(menu_w)/8,"%s","AUTENTICACAO");
        mvwprintw(menu_win,menu_h/4,(menu_w)/4,"%s","CPF: ");
        wscanw(menu_win,"%s",dado1);
        mvwprintw(menu_win,menu_h/4+1,(menu_w)/4,"%s","Senha: ");
        wscanw(menu_win,"%s",dado2);
        noecho();

        printMenu(menu_win, menu_h/5+4, (menu_w)/4, highlight, 2, QT_OPCOES, opcoes);
        while(1){
            // reatribuindo os valores
            highlight = 1;
            choice = 0;

            keypad(menu_win, TRUE); // permite o acesso a teclas especiais
            while(1){
                choice = getKey(menu_win, highlight, choice, QT_OPCOES);
                printMenu(menu_win, menu_h/5+4, (menu_w)/4, highlight, 2, QT_OPCOES, opcoes);
                if(choice != 0) break;
            }
            // chamando a funcionalidade escolhida
            switch(choice){
                case AUTENTICAR:
                    try{
                        cpf.set(dado1);
                        senha.set(dado2);

                        CSAutenticacao->autenticar(cpf);

                        if(senha.get() == CSAutenticacao::usuario.getSenha().get()){
                           CAAutenticacao::usuario_atual.setCPF(cpf);
                           CAAutenticacao::usuario_atual.setSenha(senha);

                           mvwprintw(menu_win,menu_h/4+3,(menu_w)/4,"%s","Autenticado com sucesso.");
                        }
                        else{
                           mvwprintw(menu_win,menu_h/4+3,(menu_w)/4,"%s","Senha Errada.");
                        }
                    }
                    catch(exception &e){
                        mvwprintw(menu_win,menu_h/4+3,(menu_w)/4,"%s",e.what());
                    }
                    break;

                case SAIR:
                    delwin(title_win);
                    delwin(menu_win);
                    endwin();
                    return;
                }
        }
}


void CSAutenticacao::conectar() throw (runtime_error) {
      rc = sqlite3_open(nomeBD, &bd);
      if( rc != SQLITE_OK )
        throw runtime_error("Erro na conexao ao banco de dados");
}

void CSAutenticacao::desconectar() throw (runtime_error) {
      rc =  sqlite3_close(bd);
      if( rc != SQLITE_OK )
        throw runtime_error("Erro na desconexao ao banco de dados");
}

Usuario CSAutenticacao::usuario;

int CSAutenticacao::callback(void *NotUsed, int argc, char **valorColuna, char **nomeColuna){
      NotUsed=0;
      CPF cpf; Senha senha;

        cpf.set(valorColuna[0]);
        CSAutenticacao::usuario.setCPF(cpf);
        senha.set(valorColuna[1]);
        CSAutenticacao::usuario.setSenha(senha);

      return 0;
}

void CSAutenticacao::executar(const char* comando) throw (runtime_error) {
        conectar();
        rc = sqlite3_exec(bd, comando, callback, 0, &mensagem);
        if(rc != SQLITE_OK){
                if (mensagem)
                        free(mensagem);
                throw runtime_error("Erro na execucao do comando SQL");
        }
        desconectar();
}

void CSAutenticacao::autenticar(CPF cpf) throw(runtime_error){
     string comando;

     comando = "SELECT * FROM usuario WHERE cpf = ";
     comando += "'" + cpf.get() + "'";
     executar(comando.c_str());
}
