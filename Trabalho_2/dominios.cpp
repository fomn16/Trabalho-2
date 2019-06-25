#include "dominios.h"

/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  ESTADO  ////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void Estado::set(string estado) throw (invalid_argument){
    validar(estado);
    this->estado = estado;
}

void Estado::validar(string estado) const throw (invalid_argument){
    bool valido = 0;
    for(int i = 0; i < this->NUMEROESTADOS; i++){
        if(estado == this->ESTADOSVALIDOS[i]){
            valido++;
        }
    }
    if(valido == 0){//caso nenhum estato valido seja igual à entrada fornecida, ocorre um erro.
        throw invalid_argument("Argumento invalido.");
    }
}

/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  DISPONIBILIDADE  ///////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void Disponibilidade::set(string disponibilidade) throw(invalid_argument){
    this->disponibilidade = validar(disponibilidade);
}

//o proprio validar chama a função de conversor de string para int, e caso esta ocorra sem erros, verifica se a disponibilidade se encontra dentro do limite fornecido
int Disponibilidade::validar(string disponibilidade) const throw(invalid_argument){


    for (int i = 0; i<disponibilidade.length(); i++){
        if(disponibilidade[i]<'0'||disponibilidade[i]>'9')
        {
            throw invalid_argument("Argumento invalido.");
        }
    }
    int disponibilidadeInt = stoi(disponibilidade);

    if(disponibilidadeInt>this->DISPONIBILIDADEMAXIMA){
        throw invalid_argument("Argumento invalido.");
    }
    return disponibilidadeInt;
}

/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  CLASSE DE EVENTO  //////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void ClasseEvento::set(string classeEvento) throw (invalid_argument){
    this->classeEvento = validar(classeEvento);
}

int ClasseEvento::validar(string classeEvento) const throw (invalid_argument){

    for (int i = 0; i<classeEvento.length(); i++){
        if(classeEvento[i]<'0'||classeEvento[i]>'9')
        {
            throw invalid_argument("Argumento invalido.");
        }
    }
    int classeEventoInt = stoi(classeEvento);
    if(classeEventoInt<1||classeEventoInt>CLASSEMAXIMA){
        throw invalid_argument("Argumento Invalido.");
    }
    return classeEventoInt;
}

/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  FAIXA ETARIA  //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void FaixaEtaria::set(string faixaEtaria) throw (invalid_argument){
    validar(faixaEtaria);
    this->faixaEtaria = faixaEtaria;
}

void FaixaEtaria::validar(string faixaEtaria) const throw (invalid_argument){


    bool achado = 0;
    for (int i=0; i<this->NUMEROFAIXAS; i++){
        if(faixaEtaria==this->FAIXASVALIDAS[i]){
            achado = 1;
        }
    }
    if(!achado){
        throw invalid_argument("Argumento invalido.");
    }
}

/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  CPF  ///////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void CPF::set(string cpf) throw (invalid_argument){
    validar(cpf);
    this->cpf = cpf;
}

string CPF::filtrar(string cpf) const throw (invalid_argument){
    int posCPFLimpo = 0;
    int posCPFSujo = 0;

    string cpfLimpo = "00000000000";
    for(posCPFSujo=0; posCPFSujo<cpf.length(); posCPFSujo++){
        if(cpf[posCPFSujo]>=48&&cpf[posCPFSujo]<=57){
            cpfLimpo[posCPFLimpo] = cpf[posCPFSujo];
            posCPFLimpo++;
        }
    }
    if (posCPFLimpo==11){
        return cpfLimpo;
    }
    throw invalid_argument("Argumento Inválido");
}

string CPF::digitoVerificador(string cpf) const throw (invalid_argument){
    string digito = "00";
    int soma1 = 0;
    int soma2 = 0;
    for(int i=0; i<9; i++){
        soma1+=(cpf[i]-'0')*(10-i);
        soma2+=(cpf[i]-'0')*(11-i);
    }
    if(soma1%11<2){
        digito[0] = '0';
    }
    else{
        digito[0] = '0' + (11 - soma1%11);
        soma2+= (11 - soma1%11)*2;
    }
    if(soma2%11<2){
        digito[1] = '0';
    }
    else{
        digito[1] = '0' + (11 - soma2%11);
    }
    return digito;
}

void CPF::validar(string cpf) const throw (invalid_argument){

    if (cpf.length()==14){
        if(!(cpf[3]=='.' && cpf[7]=='.' && cpf[11]=='-')){
            throw invalid_argument("Argumento invalido.");
        }
    }
    else if(cpf.length()!=11){
        throw invalid_argument("Argumento invalido.");
    }
    string cpfLimpo = filtrar(cpf);
    string digito = digitoVerificador(cpfLimpo);
    if(!(cpfLimpo[9]==digito[0]&&cpfLimpo[10]==digito[1])){
        throw invalid_argument("Argumento invalido.");
    }
}

/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  SENHA  /////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void Senha::set(string senha) throw (invalid_argument){
    validar(senha);
    this->senha = senha;
}

void Senha::validar(string senha) const throw (invalid_argument){

    bool maiuscula = 0;
    bool minuscula = 0;
    bool digito = 0;
    if(senha.length()!=TAMANHOSENHA)
    {
        throw invalid_argument("Argumento invalido.");
    }
    for (int i=0; i<this->TAMANHOSENHA; i++){
        if(senha[i]>='A'&&senha[i]<='Z'){
                maiuscula = 1;
        }
        else if(senha[i]>='a'&&senha[i]<='z'){
                minuscula = 1;
        }
        else if(senha[i]>='0'&&senha[i]<='9'){
                digito = 1;
        }
        else{
            throw invalid_argument("Argumento invalido.");
        }
        for(int j=i+1;j<TAMANHOSENHA;j++){
            if(senha[i]==senha[j]){
                throw invalid_argument("Argumento invalido.");
            }
        }
    }
    if(maiuscula+minuscula+digito != 3){
        throw invalid_argument("Argumento invalido.");
    }
}

/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  NUMERO CARTAO  /////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

char NumeroCartao::luhn(string numeroCartao)const{
    int soma = 0;
    for(int i=1; i<this->TAMANHOCARTAO;i++){
        if((i)%2!=0){
            int parteSoma = 2*(numeroCartao[this->TAMANHOCARTAO-1-i]-'0');
            if(parteSoma<10){
                soma += parteSoma;
            }
            else{
                soma += parteSoma%10 + (parteSoma-parteSoma%10)/10;
            }
        }
        else{
            soma += numeroCartao[i]-'0';
        }
    }
    return ((soma*9)%10)+'0';
}

void NumeroCartao::validar(string numeroCartao) const throw (invalid_argument){
    if (numeroCartao.length()!=this->TAMANHOCARTAO){
        throw invalid_argument("Argumento inválido.");
    }
    if (numeroCartao[this->TAMANHOCARTAO-1]!=luhn(numeroCartao))
    {
       throw invalid_argument("Argumento inválido");
    }
}

void NumeroCartao::set(string numeroCartao) throw (invalid_argument){


    validar(numeroCartao);
    this->numeroCartao=numeroCartao;
}

/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  CODIGO DE SEGURANCA  //////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void CodigoSeguranca::validar(string codigoSeguranca) const throw (invalid_argument){
    if(codigoSeguranca.length()!=TAMANHOCODIGO){
        throw invalid_argument("Argumento invalido.");
    }
    for (int i = 0; i<codigoSeguranca.length(); i++){
        if(codigoSeguranca[i]<'0'||codigoSeguranca[i]>'9')
        {
            throw invalid_argument("Argumento invalido.");
        }
    }
}

void CodigoSeguranca::set(string codigoSeguranca) throw (invalid_argument){
    validar(codigoSeguranca);
    this->codigoSeguranca = stoi(codigoSeguranca);
}

/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  DATA DE VALIDADE  //////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void DataValidade::validar(string dataValidade) const throw (invalid_argument){
    int barra = 0;
    int mes=0;
    int ano=0;
    for (int i =0; i<dataValidade.length();i++){
        if(dataValidade[i]=='-')
        {
            barra++;
        }
        else{
            if(dataValidade[i]<'0'||dataValidade[i]>'9'){
                throw invalid_argument("Argumento invalido");
            }
            if(!barra){
                mes*=10;
                mes+=dataValidade[i] - '0';
            }
            else{
                ano*=10;
                ano+=dataValidade[i] - '0';
            }
        }
    }
    if(!barra||barra>1){
        throw invalid_argument("Argumento invalido.");
    }
    else{
        if (mes==0||mes>12){
            throw invalid_argument("Argumento invalido.");
        }
        if(ano>99){
            throw invalid_argument("Argumento invalido.");
        }
    }
}

void DataValidade::set(string dataValidade) throw (invalid_argument){
    validar(dataValidade);
    this->dataValidade = dataValidade;
}

/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  CODIGO DE EVENTO  //////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

/// \brief Função que verifica se o tamanho do código de evento está de acordo com o determinado tamanho.
/// \param string codigoEvento
void CodigoEvento::checaTamanho(string codigoEvento) throw(invalid_argument){
    if( codigoEvento.length() > TAMANHO ){
        throw invalid_argument("Tamanho de codigo errado.");
    }
}

/// \brief Função checa se todos os caracteres da string correspondem a dígitos.
/// \param string codigoEvento
void CodigoEvento::checaDigitos(string codigoEvento) throw(invalid_argument){
    int i;
    for(i=0; i<codigoEvento.length(); i++){
        if(isdigit(codigoEvento[i]));
        else throw invalid_argument("Codigo possui caracteres nao numericos.");
    }
}

/// \brief Função que verifica todas as condições de formato de uma vez só.
/// \param string codigoEvento
void CodigoEvento::validar(string codigoEvento){
    checaTamanho(codigoEvento);
    checaDigitos(codigoEvento);
}

/// \brief Funçao de atribui valor do código de evento após validação.
/// \param string codigoEvento
void CodigoEvento::set(string codigoEvento){
    validar(codigoEvento);
    this->codigoEvento = codigoEvento;
}

/// \brief Função que retorna o valor código de evento armazenado na classe.
/// \return string codigoEvento
string CodigoEvento::get(){
    return codigoEvento;
}


/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  CODIGO DE APRESENTAÇÃO  ////////////////////////
/////////////////////////////////////////////////////////////////////////////////

/// \brief Função que verifica se o tamanho do código de apresentação está de acordo com o determinado tamanho.
/// \param string codigoApresentacao
void CodigoApresentacao::checaTamanho(string codigoApresentacao) throw(invalid_argument){
    if( codigoApresentacao.length() > TAMANHO ){
        throw invalid_argument("Tamanho de codigo errado.");
    }
}

/// \brief Função checa se todos os caracteres da string correspondem a dígitos.
/// \param string codigoApresentacao
void CodigoApresentacao::checaDigitos(string codigoApresentacao) throw(invalid_argument){
    int i;
    for(i=0; i<codigoApresentacao.length(); i++){
        if(isdigit(codigoApresentacao[i]));
        else throw invalid_argument("Codigo possui caracteres nao numericos.");
    }
}

/// \brief Função que verifica todas as condições de formato de uma vez só.
/// \param string codigoApresentacao
void CodigoApresentacao::validar(string codigoApresentacao){
    checaTamanho(codigoApresentacao);
    checaDigitos(codigoApresentacao);
}

/// \brief Funçao de atribui valor do código de apresentação após validação.
/// \param string codigoApresentacao
void CodigoApresentacao::set(string codigoApresentacao){
    validar(codigoApresentacao);
    this->codigoApresentacao = codigoApresentacao;
}

/// \brief Função que retorna o valor código de apresentação armazenado na classe.
/// \return string codigoApresentacao
string CodigoApresentacao::get(){
    return codigoApresentacao;
}


/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  CODIGO DE INGRESSO  ////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

/// \brief Função que verifica se o tamanho do código de ingresso está de acordo com o determinado tamanho.
/// \param string codigoIngresso
void CodigoIngresso::checaTamanho(string codigoIngresso) throw(invalid_argument){
    if( codigoIngresso.length() > TAMANHO ){
        throw invalid_argument("Tamanho de codigo errado.");
    }
}

/// \brief Função checa se todos os caracteres da string correspondem a dígitos.
/// \param string codigoIngresso
void CodigoIngresso::checaDigitos(string codigoIngresso) throw(invalid_argument){
    int i;
    for(i=0; i<codigoIngresso.length(); i++){
        if(isdigit(codigoIngresso[i]));
        else throw invalid_argument("Codigo possui caracteres nao numericos.");
    }
}

/// \brief Função que verifica todas as condições de formato de uma vez só.
/// \param string codigoIngresso
void CodigoIngresso::validar(string codigoIngresso){
    checaTamanho(codigoIngresso);
    checaDigitos(codigoIngresso);
}

/// \brief Funçao de atribui valor do código de ingresso após validação.
/// \param string codigoIngresso
void CodigoIngresso::set(string codigoIngresso){
    validar(codigoIngresso);
    this->codigoIngresso = codigoIngresso;
}

/// \brief Função que retorna o valor código de ingresso armazenado na classe.
/// \return string codigoIngresso
string CodigoIngresso::get(){
    return codigoIngresso;
}

///////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////  NOME DE EVENTO  /////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

/// \brief Função verifica se o nome de evento extrapola o tamanho limite.
/// \param string nomeEvento
void NomeEvento::checaTamanho(string nomeEvento) throw(invalid_argument){
    if(nomeEvento.length() > LIMITE){
        throw invalid_argument("Nome de Evento excedendo tamanho limite");
    }
}

/// \brief Função verifica se caractere são ou letras ou dígitos ou espaços.
/// \param string nomeEvento
void NomeEvento::checaCaracteres(string nomeEvento) throw(invalid_argument){
    int i;
    for(i=0; i<nomeEvento.length(); i++){
        if(isdigit(nomeEvento[i]) || isalpha(nomeEvento[i]) || isspace(nomeEvento[i]));
        else throw invalid_argument("Nome de Evento possui caracteres nao validos.");
    }
}
/// \brief Função verifica se o nome do evento possui pelo menos uma letra.
/// \param string nomeEvento
void NomeEvento::checaExisteLetra(string nomeEvento) throw(invalid_argument){
    int i, flagLetra = 1;
    for(i=0; i<nomeEvento.length(); i++){
        if(isalpha(nomeEvento[i])){
            flagLetra = 0;
            break;
        }
    }

    if(flagLetra) throw invalid_argument("Nome de evento nao possui nenhuma letra.");
}

/// \brief Função checa se o nome do evento possui espaços seguidos.
/// \param string nomeEvento
void NomeEvento::checaEspacoSeguido(string nomeEvento) throw(invalid_argument){
    int i;
    for(i=0; i<nomeEvento.length(); i++){
        if(isspace(nomeEvento[i]) && isspace(nomeEvento[i+1])) throw invalid_argument("Nome de evento tem espacos repetidos.");
    }
}

/// \brief Função validar verifica todas as requisições de formato para nome de evento de uma vez.
/// \param string nomeEvento
void NomeEvento::validar(string nomeEvento){
    checaTamanho(nomeEvento);
    checaCaracteres(nomeEvento);
    checaExisteLetra(nomeEvento);
    checaEspacoSeguido(nomeEvento);
}

/// \brief Função que atribui um valor para nomeEvento após validação.
/// \param string nomeEvento
void NomeEvento::set(string nomeEvento){
    validar(nomeEvento);
    this->nomeEvento = nomeEvento;
}

/// \brief Função acessa o valor
/// \return string nomeEvento
string NomeEvento::get(){
    return nomeEvento;
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////  DATA  ////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

/// \brief Função que permite o usuário passar datas em formato D/M/AAAA, corrigindo para o formato DD/MM/AAAA.
/// \param string data
/// \return dataArrumada
string Data::arrumaFormato(string data){
    int i, counter = 0;
    for(i=0; i<data.length(); i++){
        counter += 1;

        if(data[i] == '/'){
            if(counter == 2){
                data.insert((i-1),"0");
                counter = 0;
                i+=1;
            }
            else counter = 0;
        }
    }
    return data;
}

/// \brief Função checa se o tamanho da string data está correta de acordo com o formato.
/// \param string data
void Data::checaTamanho(string data) throw(invalid_argument){
    if(data.length() != TAMANHO) throw invalid_argument("Data com formato errado.");
}

/// \brief Função checa se a substring qualquer arg possuem todos os caracteres iguais a dígitos.
/// \param string arg
void Data::checaDigitos(string arg) throw(invalid_argument){
    int i;
    for(i=0; i<arg.length(); i++){
        if(isdigit(arg[i]));
        else throw invalid_argument("Data com o formato errado.");
    }
}

/// \brief Função verifica se existe barras nos locais certos de acordo com o formato.
/// \param string data
void Data::checaBarra(string data) throw(invalid_argument){
    if(data[2] != '/' || data[5] != '/') throw invalid_argument("Data com o formato errado.");
}

/// \brief Função que confere se a string data está no formato DD/MM/AAAA.
/// \param string data
void Data::checaFormato(string data){
    checaTamanho(data);
    checaBarra(data);
    // Após a verificação do tamanho sabe-se se essas partições de strings são possíveis.
    string dia = data.substr(0,2);
    string mes = data.substr(3,2);
    string ano = data.substr(6,4);

    checaDigitos(dia);
    checaDigitos(mes);
    checaDigitos(ano);
}

/// \brief Função checa se o ano da data é bissexto.
/// \param string ano/// \return bool retorna true caso seja bissexto e false caso contrário.
bool Data::checaBissexto(string ano){
    int anoInt;
    anoInt = stoi(ano);

    if((anoInt%4 == 0 && anoInt%100 != 0) || anoInt % 400 == 0) return true;
    else return false;
}

/// \brief Função checa se o dia repassado é válido de acordo com o mês e o ano.
/// \param string dia
/// \param string mes
/// \param string ano
void Data::checaDia(string dia, string mes, string ano) throw(invalid_argument){
    int diaInt, mesInt,anoInt;
    diaInt = stoi(dia);
    mesInt = stoi(mes);
    anoInt = stoi(ano);
    int agosto = 8;
    int fevereiro = 2;

    // Checa os meses até agosto
    if(mesInt < agosto){
        // Checa os meses impares até agosto
        if(mesInt%2 != 0){
            if(diaInt<1 || diaInt>31) throw invalid_argument("Dia invalido.");
        }
        // Checa os meses pares até agosto
        else{
            if(mesInt == fevereiro){
                if(checaBissexto(ano)){
                    if(diaInt<1 || diaInt>29) throw invalid_argument("Dia invalido.");
                }
                else{
                    if(diaInt<1 || diaInt>28) throw invalid_argument("Dia invalido.");
                }
            }
            // Checa outros meses pares que não sejam Fevereiro
            else{
                if(diaInt<1 || diaInt>30) throw invalid_argument("Dia invalido.");
            }
        }
    }
    // Checa os meses iguai ou depois de Agosto
    else{
        // Checa os meses ímpares depois de Agosto
        if(mesInt%2 != 0){
            if(diaInt<1 || diaInt>30) throw invalid_argument("Dia invalido.");
        }
        // Checa os meses pares iguais ou depois de Agosto
        else{
            if(diaInt<1 || diaInt>31) throw invalid_argument("Dia invalido.");
        }
    }
}

/// \brief Função checa se o mês passado é válido,isto é, está entre 1 e 12.
/// \param string mes
void Data::checaMes(string mes) throw(invalid_argument){
    int mesInt;
    mesInt = stoi(mes);

    if(mesInt<1 || mesInt>12) throw invalid_argument("Mes invalido.");
}

/// \brief Função checa se o ano é válido, isto é, se é positivo.
/// \param string ano
void Data::checaAno(string ano) throw(invalid_argument){
    int anoInt;
    anoInt = stoi(ano);

    if(anoInt<0) throw invalid_argument("Ano invalido.");
}

/// \brief Função confere se data está válida de acordo com todos os requerimentos.
/// \param string data
void Data::validar(string data){
    //Dando espaço para a passagem de data um pouco diferente
    data = arrumaFormato(data);
    checaFormato(data);
    //Após checaFormato sabe-se se essas substrings são possíveis.
    string dia = data.substr(0,2);
    string mes = data.substr(3,2);
    string ano = data.substr(6,4);
    // Checa mes e ano antes para não realizar checagens que dependem deles sem os terem verificados individualmente.
    checaMes(mes);
    checaAno(ano);
    checaDia(dia, mes, ano);
}

/// \brief Função atribui valor para a variável de data.
/// \param string data
void Data::set(string data){
    validar(data);
    this->data = data;
}

/// \brief Função acessa o que está armazenado em data.
/// \return string data
string Data::get(){
    return data;
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// HORÁRIO /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

/// \brief Função que verifica se a string tem o tamanho requerido pelo formato.
/// \param string horario
void Horario::checaTamanho(string horario) throw(invalid_argument){
    if(horario.length() != TAMANHO) throw invalid_argument("Horario com formato invalido.");
}

/// \brief Função checa se há um dois pontos de acordo com o formato.
/// \param string horario
void Horario::checaDoisPontos(string horario) throw(invalid_argument){
    if(horario[2] != ':') throw invalid_argument("Horario com formato invalido.");
}

/// \brief Função checa se uma substrings qualquer é composta de dígitos.
/// \param string arg
void Horario::checaDigitos(string arg) throw(invalid_argument){
    int i;
    for(i=0; i<arg.length(); i++){
        if(isdigit(arg[i]));
        else throw invalid_argument("Horario com formato invalido.");
    }
}

/// \brief Função que verifica se a string horario está de acordo com o formato HH:MM
/// \param string horario
void Horario::checaFormato(string horario){
    checaTamanho(horario);
    checaDoisPontos(horario);

    string hora = horario.substr(0,2);
    string minuto = horario.substr(3,2);

    checaDigitos(hora);
    checaDigitos(minuto);
}

/// \brief Função verifica se a hora está no intervalo permitido.
/// \param string hora
void Horario::checaHora(string hora) throw(invalid_argument){
    int horaInt;
    horaInt = stoi(hora);

    if(horaInt<7 || horaInt>22) throw invalid_argument("Hora invalida.");
}

/// \brief Função checa se os minutos estão entre as opções(00, 15, 30, 45).
/// \param string minuto
void Horario::checaMinuto(string minuto) throw(invalid_argument){
    int minutoInt = stoi(minuto);

    switch(minutoInt){
        case 0:
        break;

        case 15:
        break;

        case 30:
        break;

        case 45:
        break;

        default:
            throw invalid_argument("Minutos invalidos.");
    }
}

/// \brief Função confere se horário está válido de acordo com todos os requerimentos.
/// \param string horario
void Horario::validar(string horario){
    checaFormato(horario);

    string hora = horario.substr(0,2);
    string minuto = horario.substr(3,2);

    checaHora(hora);
    checaMinuto(minuto);

}

/// \brief Função atribui valor para a variável de horário.
/// \param string horario
void Horario::set(string horario){
    validar(horario);
    this->horario = horario;
}

/// \brief Função acessa valor armazenado se horário.
/// \return string horario
string Horario::get(){
    return horario;
}

/////////////////////////////////////////////////////////////////////////////
////////////////////////////// PREÇO ////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/// \brief Função que valida preço em relação ao intervalo permitido [0,1000].
/// \param float preco
void Preco::validar(float preco) throw(invalid_argument){
    if(preco<MINIMO || preco>MAXIMO) throw invalid_argument("Preco invalido.");
}

/// \brief Função quer armazena valor na variável de preço.
/// \param float preco
void Preco::set(float preco){
    validar(preco);
    this->preco = preco;
}

/// \brief Função que acessa valor armazenado na variável de preço.
/// \return float preco
float Preco::get(){
    return preco;
}

/////////////////////////////////////////////////////////////////////////////
//////////////////////////// NÚMERO DE SALA /////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/// \brief Função verifica se número de sala está no intervalo permitido [0,10].
/// \param int numeroSala
void NumeroSala::validar(int numeroSala) throw(invalid_argument){
    if(numeroSala<MINIMO || numeroSala>MAXIMO) throw invalid_argument("Numero de Sala invalido.");
}

/// \brief Função armazena valor na variável de número de sala.
/// \param int numeroSala
void NumeroSala::set(int numeroSala){
    validar(numeroSala);
    this->numeroSala = numeroSala;
}

/// \brief Função acessa valor armazenado na variável de número de sala.
/// \return int numeroSala
int NumeroSala::get(){
    return numeroSala;
}

/////////////////////////////////////////////////////////////////////////////
//////////////////////////// CIDADE /////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/// \brief Função que verifica se a string passa do tamanho limite de 15 caracteres.
/// \param string cidade
void Cidade::checaTamanho(string cidade) throw(invalid_argument){
    if(cidade.length() > LIMITE) throw invalid_argument("Cidade com tamanho invalido.");
}

/// \brief Função verifica se todos os caracteres da string são ou letras, ou espaços, ou pontos.
/// \param string cidade
void Cidade::checaCaracteres(string cidade) throw(invalid_argument){
    int i;
    for(i=0; i<cidade.length(); i++){
        if(isalpha(cidade[i]) || isspace(cidade[i]) || cidade[i]=='.');
        else throw invalid_argument("Cidade com caracteres invalidos.");
    }
}

/// \brief Função verifica se o nome da cidade possui pelo menos uma letra.
/// \param string cidade
void Cidade::checaExisteLetra(string cidade) throw(invalid_argument){
    int i, flagLetra = 1;
    for(i=0; i<cidade.length(); i++){
        if(isalpha(cidade[i])){
            flagLetra = 0;
            break;
        }
    }

    if(flagLetra) throw invalid_argument("Cidade nao possui nenhuma letra.");
}

/// \brief Função checa se o nome da cidade possui espaços seguidos.
/// \param string cidade
void Cidade::checaEspacoSeguido(string cidade) throw(invalid_argument){
    int i;
    for(i=0; i<cidade.length(); i++){
        if(isspace(cidade[i]) && isspace(cidade[i+1])) throw invalid_argument("Cidade tem espacos repetidos.");
    }
}

/// \brief Função verifica se todo ponto da string é precidido por letra.
/// \param string cidade
void Cidade::checaPonto(string cidade) throw(invalid_argument){
    int i;
    for(i=0; i<cidade.length(); i++){
        if(cidade[i]=='.' && !isalpha(cidade[i-1])) throw invalid_argument("Cidade tem ponto nao precedido por letra.");
    }
}

/// \brief Função que verifica todos os requerimentos para cidade de uma vez.
/// \param string cidade
void Cidade::validar(string cidade){
    checaTamanho(cidade);
    checaCaracteres(cidade);
    checaEspacoSeguido(cidade);
    checaExisteLetra(cidade);
    checaPonto(cidade);
}

/// \brief Função armazena conteúdo na variável de cidade.
/// \param string cidade
void Cidade::set(string cidade){
    validar(cidade);
    this->cidade = cidade;
}

/// \brief Função que acessa conteúdo armazenado na variável de cidade.
/// \return string cidade
string Cidade::get(){
    return cidade;
}
