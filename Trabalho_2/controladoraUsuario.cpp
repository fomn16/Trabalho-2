#include "controladoraUsuario.h"
#include <string.h>
/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  APRESENTACAO  //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
WINDOW* CAUsuario::createWindow(int height, int width, int y, int x, int color_id){
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

void CAUsuario::printMenu(WINDOW *win, int y, int x, int highlight, int color_id, int qt_opcoes,const char **opcoes){
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

int CAUsuario::getKey(WINDOW* win, int &highlight, int choice, int qt_opcoes){
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

void CAUsuario::executarOpcoes(){
    WINDOW *menu_win, *title_win;
    int max_h,max_w;
    int title_w = 40, title_h = 3; // tamanho da janela de titulo
    int menu_w = 50, menu_h = 10; // variaveis para o menu
    int highlight = 1, choice = 0;
    char name[] = "USUARIO";

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

    while(1){
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
        printMenu(menu_win, menu_h/5, (menu_w)/4, highlight, 2, 5, opcoes);
        while(1){
            choice = getKey(menu_win, highlight, choice, 5);
            printMenu(menu_win, menu_h/5, (menu_w)/4, highlight, 2, 5, opcoes);
            if(choice != 0) break;
        }

        // chamando a funcionalidade escolhida
        switch(choice){
                case CADASTRAR:
                    cadastrar();
                    clear();
                    break;
                case DESCADASTRAR:
                    descadastrar();
                    clear();
                    break;
                case PESQUISAR:
                    pesquisar();
                    clear();
                    break;
                case EDITAR:
                    editar();
                    clear();
                    break;
                case SAIR:
                    delwin(title_win);
                    delwin(menu_win);
                    endwin();
                    return;
            }
        }
}

void CAUsuario::cadastrar(){
    WINDOW* cadastro_win;
    int max_h, max_w;
    int highlight = 1, choice = 0;
    int cadastro_h = 20, cadastro_w = 60;
    const char* teclas[2] = {"CADASTRAR", "VOLTAR"};

    // variaveis a serem armazenadas sobre o usuario
    CPF cpf; Senha senha; NumeroCartao numero; CodigoSeguranca codigo; DataValidade data;
    Usuario usuario; CartaoCredito cartao;
    char dado1[20], dado2[20], dado3[20], dado4[20], dado5[20];

    getmaxyx(stdscr,max_h,max_w);

    cadastro_win = createWindow(cadastro_h, cadastro_w, max_h/4, (max_w-cadastro_w)/2, 2);
    keypad(cadastro_win,TRUE);
    wrefresh(cadastro_win);
    echo(); // habilitando echo

    mvwprintw(cadastro_win,cadastro_h/8,(cadastro_w)/8,"%s","CADASTRAMENTO");
    mvwprintw(cadastro_win,cadastro_h/4,(cadastro_w)/4,"%s","CPF: ");
    wscanw(cadastro_win,"%s",dado1);
    mvwprintw(cadastro_win,cadastro_h/4+1,(cadastro_w)/4,"%s","Senha: ");
    wscanw(cadastro_win,"%s",dado2);
    mvwprintw(cadastro_win,cadastro_h/4+3,(cadastro_w)/4,"%s","Numero do Cartao: ");
    wscanw(cadastro_win,"%s",dado3);
    mvwprintw(cadastro_win,cadastro_h/4+4,(cadastro_w)/4,"%s","Codigo de Seguranca: ");
    wscanw(cadastro_win,"%s",dado4);
    mvwprintw(cadastro_win,cadastro_h/4+5,(cadastro_w)/4,"%s","Data de Validade: ");
    wscanw(cadastro_win,"%s",dado5);
    noecho();

    printMenu(cadastro_win,cadastro_h-5,(cadastro_w)/4, highlight, 2, 2, teclas);
    while(1){
        // reatribuindo os valores
        highlight = 1;
        choice = 0;
        while(1){
            choice = getKey(cadastro_win, highlight, choice, 2);
            printMenu(cadastro_win,cadastro_h-5,(cadastro_w)/4, highlight, 2, 2, teclas);
            if(choice!=0) break;
        }

        //testando dados caso seja confirmado
        if(choice == 1){
            // parte a ser implementada
            try{
                cpf.set(dado1);
                senha.set(dado2);
                numero.set(dado3);
                codigo.set(dado4);
                data.set(dado5);

                usuario.setCPF(cpf);
                usuario.setSenha(senha);
                cartao.setNumero(numero);
                cartao.setCodigo(codigo);
                cartao.setData(data);

                CSUsuario->cadastrar(usuario, cartao);
                mvwprintw(cadastro_win,cadastro_h/4+7,(cadastro_w)/4,"%s","Cadastrado com sucesso.");
            }
            catch(exception &e){
                mvwprintw(cadastro_win,cadastro_h/4+7,(cadastro_w)/4,"%s",e.what());
            }
        }
        else{
            return;
        }
    }
};

void CAUsuario::descadastrar(){
    WINDOW* descadastro_win;
    int max_h, max_w;
    int highlight = 1, choice = 0;
    int descadastro_h = 20, descadastro_w = 60;
    const char* teclas[2] = {"DESCADASTRAR", "VOLTAR"};

    CPF cpf;
    char dado1[20];

    getmaxyx(stdscr,max_h,max_w);

    descadastro_win = createWindow(descadastro_h, descadastro_w, max_h/4, (max_w-descadastro_w)/2, 2);
    keypad(descadastro_win,TRUE);
    wrefresh(descadastro_win);
    echo(); // habilitando echo

    mvwprintw(descadastro_win,descadastro_h/8,(descadastro_w)/8,"%s","DESCADASTRAMENTO");
    mvwprintw(descadastro_win,descadastro_h/4,(descadastro_w)/8,"%s","Insira CPF do usuario a ser descadastrado: ");
    mvwscanw(descadastro_win,descadastro_h/4+1,(descadastro_w)/8,"%s",dado1);
    noecho();

    while(1){
        // reatribuindo os valores
        highlight = 1;
        choice = 0;
        printMenu(descadastro_win,descadastro_h-5,(descadastro_w)/4, highlight, 2, 2, teclas);
        while(1){
            choice = getKey(descadastro_win, highlight, choice, 2);
            printMenu(descadastro_win,descadastro_h-5,(descadastro_w)/4, highlight, 2, 2, teclas);
            if(choice!=0) break;
        }

        //testando dados caso seja confirmado
       if(choice == 1){
            // parte a ser implementada
            try{
                cpf.set(string(dado1));

                CSUsuario->descadastrar(cpf);
                mvwprintw(descadastro_win,descadastro_h/4+7,(descadastro_w)/4,"%s","Descadastrado com sucesso.");
            }
            catch(exception &e){
                mvwprintw(descadastro_win,descadastro_h/4+7,(descadastro_w)/4,"%s",e.what());
            }
        }
        else{
            return;
        }
    }
};

void CAUsuario::pesquisar(){
    WINDOW* pesquisa_win;
    int max_h, max_w;
    int highlight = 1, choice = 0;
    int pesquisa_h = 20, pesquisa_w = 60;
    const char* teclas[2] = {"PESQUISAR", "VOLTAR"};

    CPF cpf;
    char dado1[20];

    getmaxyx(stdscr,max_h,max_w);

    pesquisa_win = createWindow(pesquisa_h, pesquisa_w, max_h/4, (max_w-pesquisa_w)/2, 2);
    keypad(pesquisa_win,TRUE);
    wrefresh(pesquisa_win);
    echo(); // habilitando echo

    mvwprintw(pesquisa_win,pesquisa_h/8,(pesquisa_w)/8,"%s","PESQUISA DE USUARIO");
    mvwprintw(pesquisa_win,pesquisa_h/4,(pesquisa_w)/8,"%s","Insira CPF do usuario a ser procurado: ");
    mvwscanw(pesquisa_win,pesquisa_h/4+1,(pesquisa_w)/8,"%s",dado1);
    noecho();

    while(1){
        // reatribuindo os valores
        highlight = 1;
        choice = 0;
        printMenu(pesquisa_win,pesquisa_h-5,(pesquisa_w)/4, highlight, 2, 2, teclas);
        while(1){
            choice = getKey(pesquisa_win, highlight, choice, 2);
            printMenu(pesquisa_win,pesquisa_h-5,(pesquisa_w)/4, highlight, 2, 2, teclas);
            if(choice!=0) break;
        }

        //testando dados caso seja confirmado
        if(choice == 1){
            // parte a ser implementada
            try{
                cpf.set(string(dado1));
                CSUsuario->pesquisar(cpf);

                mvwprintw(pesquisa_win,pesquisa_h/4+2,(pesquisa_w)/4,"%s %s","CPF:",CSUsuario::usuario.getCPF().get().c_str());
                mvwprintw(pesquisa_win,pesquisa_h/4+3,(pesquisa_w)/4,"%s %s","Senha:",CSUsuario::usuario.getSenha().get().c_str());
                mvwprintw(pesquisa_win,pesquisa_h/4+5,(pesquisa_w)/4,"%s %s","Numero do Cartao:",CSUsuario::cartao.getNumero().get().c_str());
                mvwprintw(pesquisa_win,pesquisa_h/4+6,(pesquisa_w)/4,"%s %s","Codigo de Seguranca:",to_string(CSUsuario::cartao.getCodigo().get()).c_str());
                mvwprintw(pesquisa_win,pesquisa_h/4+7,(pesquisa_w)/4,"%s %s","Data de Validade:",CSUsuario::cartao.getData().get().c_str());
                mvwprintw(pesquisa_win,pesquisa_h/4+8,(pesquisa_w)/4,"%s","Pesquisa realizada com sucesso.");
            }
            catch(exception &e){
                mvwprintw(pesquisa_win,pesquisa_h/4+7,(pesquisa_w)/4,"%s",e.what());
            }
        }
        else{
            return;
        }
    }
};

void CAUsuario::editar(){

    WINDOW* edita_win;
    int max_h, max_w;
    int highlight = 1, choice = 0;
    int edita_h = 20, edita_w = 60;
    const char* teclas[2] = {"EDITAR", "VOLTAR"};

    // variaveis a serem armazenadas sobre o usuario
    CPF cpf; Senha senha; NumeroCartao numero; CodigoSeguranca codigo; DataValidade data;
    Usuario usuario; CartaoCredito cartao;
    char dado1[20], dado2[20], dado3[20], dado4[20], dado5[20];

    getmaxyx(stdscr,max_h,max_w);

    edita_win = createWindow(edita_h, edita_w, max_h/4, (max_w-edita_w)/2, 2);
    keypad(edita_win,TRUE);
    wrefresh(edita_win);
    echo(); // habilitando echo

    mvwprintw(edita_win,edita_h/8,(edita_w)/8,"%s","ALTERACAO DE DADOS");

    mvwprintw(edita_win,edita_h/4+1,(edita_w)/4,"%s","CPF: ");
    wscanw(edita_win,"%s",dado1);
    mvwprintw(edita_win,edita_h/4+2,(edita_w)/4,"%s","Senha: ");
    wscanw(edita_win,"%s",dado2);
    mvwprintw(edita_win,edita_h/4+5,(edita_w)/4,"%s","Numero do Cartao: ");
    wscanw(edita_win,"%s",dado3);
    mvwprintw(edita_win,edita_h/4+6,(edita_w)/4,"%s","Codigo de Seguranca: ");
    wscanw(edita_win,"%s",dado4);
    mvwprintw(edita_win, edita_h/4+7,(edita_w)/4,"%s","Data de Validade: ");
    wscanw(edita_win,"%s",dado5);
    noecho();
    while(1){
        // reatribuindo os valores
        highlight = 1;
        choice = 0;
        printMenu(edita_win,edita_h-5,(edita_w)/4, highlight, 2, 2, teclas);
        while(1){
            choice = getKey(edita_win, highlight, choice, 2);
            printMenu(edita_win,edita_h-5,(edita_w)/4, highlight, 2, 2, teclas);
            if(choice!=0) break;
        }

        //testando dados caso seja confirmado
        if(choice == 1){
         // parte a ser implementada
            try{
                cpf.set(dado1);
                senha.set(dado2);
                numero.set(dado3);
                codigo.set(dado4);
                data.set(dado5);

                usuario.setCPF(cpf);
                usuario.setSenha(senha);
                cartao.setNumero(numero);
                cartao.setCodigo(codigo);
                cartao.setData(data);

                CSUsuario->editar(usuario, cartao);
                mvwprintw(edita_win,edita_h/4+9,(edita_w)/4,"%s","Editado com sucesso.");
            }
            catch(exception &e){
                mvwprintw(edita_win,edita_h/4+9,(edita_w)/4,"%s",e.what());
            }
        }
        else{
            return;
        }
    }
};

/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  SERVICOS  //////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////


void CSUsuario::conectar() throw (runtime_error) {
      rc = sqlite3_open(nomeBD, &bd);
      if( rc != SQLITE_OK )
        throw runtime_error("Erro na conexao ao banco de dados");
}

void CSUsuario::desconectar() throw (runtime_error) {
      rc =  sqlite3_close(bd);
      if( rc != SQLITE_OK )
        throw runtime_error("Erro na desconexao ao banco de dados");
}

Usuario CSUsuario::usuario;
CartaoCredito CSUsuario::cartao;

int CSUsuario::callback(void *NotUsed, int argc, char **valorColuna, char **nomeColuna){
      NotUsed=0;
      CPF cpf; Senha senha; NumeroCartao numero; CodigoSeguranca codigo; DataValidade data;

      if(argc == 2){
        cpf.set(valorColuna[0]);
        CSUsuario::usuario.setCPF(cpf);
        senha.set(valorColuna[1]);
        CSUsuario::usuario.setSenha(senha);
      }
      else{
        numero.set(valorColuna[0]);
        CSUsuario::cartao.setNumero(numero);
        codigo.set(valorColuna[1]);
        CSUsuario::cartao.setCodigo(codigo);
        data.set(valorColuna[2]);
        CSUsuario::cartao.setData(data);
      }

      return 0;
}

void CSUsuario::executar(const char* comando) throw (runtime_error) {
        conectar();
        rc = sqlite3_exec(bd, comando, callback, 0, &mensagem);
        if(rc != SQLITE_OK){
                if (mensagem)
                        free(mensagem);
                throw runtime_error("Erro na execucao do comando SQL");
        }
        desconectar();
}

void CSUsuario::cadastrar(Usuario usuario, CartaoCredito cartao) throw(runtime_error){
        string comando;
        comando = "INSERT INTO usuario VALUES (";
        comando += "'" + usuario.getCPF().get() + "', ";
        comando += "'" + usuario.getSenha().get() + "');";

        comando += "INSERT INTO cartao VALUES (";
        comando += "'" + cartao.getNumero().get() + "', ";
        comando += "'" + to_string(cartao.getCodigo().get()) + "', ";
        comando += "'" + cartao.getData().get() + "', ";
        comando += "'" + usuario.getCPF().get() + "')";

        //cout << comando << endl;
        executar(comando.c_str());
}

 void CSUsuario::descadastrar(CPF cpf) throw(runtime_error){
        string comando;
        comando = "PRAGMA foreign_keys = ON;";
        comando += "DELETE FROM usuario WHERE cpf = ";
        comando += "'" + cpf.get() + "'";

        //cout << comando << endl;
        executar(comando.c_str());
}

void CSUsuario::pesquisar(CPF cpf) throw(runtime_error){
     string comando1, comando2;

     comando1 = "SELECT * FROM usuario WHERE cpf = ";
     comando1 += "'" + cpf.get() + "'";
     executar(comando1.c_str());

     comando2 = "SELECT * FROM cartao WHERE usuario_cpf = ";
     comando2 += "'"+ cpf.get() + "'";
     executar(comando2.c_str());

}

void CSUsuario::editar(Usuario usuario, CartaoCredito cartao) throw(runtime_error){
        string comando;
        comando = "PRAGMA foreign_keys = ON;";
        comando += "UPDATE usuario ";
        comando += "SET";
        comando += " senha = '" + usuario.getSenha().get();
        comando += "' WHERE cpf = '" + usuario.getCPF().get()+"';";
        comando += "UPDATE cartao ";
        comando += "SET numero = '" + cartao.getNumero().get();
        comando += "', codigo = '" + to_string(cartao.getCodigo().get());
        comando += "',  data = '" + cartao.getData().get();
        comando += "' WHERE numero = '" + cartao.getNumero().get()+"'";

        //cout << comando << endl;
        executar(comando.c_str());
}
