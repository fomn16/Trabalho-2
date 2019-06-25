#ifndef DOMINIOS_H
#define DOMINIOS_H

#include <iostream>
#include <ctype.h>
#include <stdexcept>
#include <string>
#include <string.h>
#include <conio.h>


using namespace std;

/// \brief Classe do domínio de Estado, possibilita ao usuário fornecer uma sigla válida de estado brasileiro por meio da Método set e recuperá-la por meio da Método get.
class Estado{
    private:
        string estado; ///< O código válido do estado será guardado na variável estado.
        const static int NUMEROESTADOS = 26;///< O número de estados que tem sua sigla válida é guardado na variável NUMEROESTADOS.
        string ESTADOSVALIDOS[NUMEROESTADOS] {"AC","AL","AP","AM","BA","CE","DF","ES","GO","MA","MT","MS","MG","PA","PB","PR","PE","PI","RJ","RN","RS","RO","RR","SC","SP","SE"}; ///< Uma lista de strings das siglas válidas para os estados.
        /// \brief Método que valida o estado fornecido, se não for um estado incluso na lista de estados validos, gerará um erro.
        /// \param estado String contendo a sigla de um estado brasileiro a ser guardada.
        void validar(string estado) const throw (invalid_argument);
    public:
        /// \brief Método que salva a string fornecida na variável "estado", desde que esta seja válida.
        /// \param estado String a ser validada e guardada.
        void set(string estado) throw (invalid_argument);
        /// \brief Método que retorna a string "estado" guardada por meio de set.
        /// \return Estado guardado em "estado".
        string get() const
        {
            return this->estado;
        }
};

/// \brief Classe do domínio de Disponibilidade, possibilita ao usuário fornecer uma número válido de disponibilidade - inteiro entre 0 e 250 -  por meio da Método set e recuperá-lo por meio da Método get.
class Disponibilidade{
    private:
        int disponibilidade; ///> valor válido a ser guardado para disponibilidade.
        const static int DISPONIBILIDADEMAXIMA = 250; ///> Variável constante e estática que guarda o número máximo que pode ser fornecido para disponibilidade.
        /// \brief Método que verifica se o valor fornecido em string pode ser convertido para um inteiro e se este é positivo e menor que 251.
        /// \param disponibilidade String a ser validada.
        int validar(string disponibilidade) const throw (invalid_argument);
    public:
        /// \brief Método que guarda como um inteiro o número fornecido em string, caso este seja válido - conversível para inteiro e positivo menor que 251.
        /// \param disponibilidade string a ser validada e guardada no objeto.
        void set (string disponibilidade) throw (invalid_argument);
        /// \brief Método que retorna o valor de disponibilidade salvo em memória previamente por meio da Método set.
        /// \return retorna, em int, o valor fornecido de disponibilidade.
        int get() const
        {
            return this->disponibilidade;
        }
};

/// \brief Classe do domínio de Classe de Evento, sendo esta um inteiro entre 1 e 4. pode-se recuperar este inteiro por meio da Método get, e salvá-lo - caso este seja válido - por meio de set.
class ClasseEvento{
    private:
        int classeEvento; ///> Variável que guarda o valor de classe de evento, entre 1 e 4.
        const static int CLASSEMAXIMA = 4; ///> Variável estática e constante que guarda o número máximo que pode ser validado em classe de evento.
        /// \brief Método que verifica se o valor fornecido em string pode ser convertido para um inteiro e se este fica entre 1 e 4. Caso não seja válida lança um erro.
        /// \param disponibilidade String a ser validada.
        int validar(string classeEvento) const throw (invalid_argument);
    public:
        /// \brief Método que guarda a string fornecida como um inteiro, caso este possa ser validado por meio da Método validar, chamada internamente.
        /// \param classeEvento string a ser fornecida, representando um inteiro entre 1 e 4.
        void set(string classeEvento) throw (invalid_argument);
        /// \brief Método que retorna o valor guardado na variável "classeEvento" por meio da Método set.
        /// \return valor na variável classeEvento.
        int get(){
            return this->classeEvento;
        }
};

/// \brief Classe do dominio de Faixa Etária. Permite que se salve uma faixa etária válida - "L", "10", "12", "14", "16" ou "18" - por meio da Método set e recuperá-l por meio de get.
class FaixaEtaria{
    private:
        string faixaEtaria; ///> Variável que armazena a string válida fornecida.
        const static int NUMEROFAIXAS = 6; ///> Variável constante e estática que fornece o número de faixas etárias a serem consideradas.
        string FAIXASVALIDAS[NUMEROFAIXAS] {"L", "10", "12", "14", "16", "18"}; ///> Lista de strings válidas para faixas etárias.
        /// \brief Método responsável por verificar se a string fornecida é uma das strings válidas para faixa etária. Caso não seja válida lança uma excessão.
        /// \param faixaEtaria String fornecida para validação.
        void validar(string faixaEtaria) const throw (invalid_argument);
    public:
        /// \brief Método que guarda em memória a string fornecida caso esta seja válida. Caso não seja válida lança uma excessão.
        /// \param faixaEtária String a ser validada internamente e guardada em memória.
        void set(string faixaEtaria) throw (invalid_argument);
        /// \brief Método a partir da qual se recupera a string guardada por meio do método set.
        /// \return Retorna o valor guardado na variável faixaEtaria.
        string get(){
            return this->faixaEtaria;
        }
};

/// \brief Classe do domínio de CPF, que guarda um valor válido de CPF - utilizando o algoritmo de dígito verificador - por meio da Método set, e recuperá-lo por meio da Método get.
class CPF{
    private:
        string cpf; ///> Variável que guarda a string fornecida caso esta seja um cpf válido.
        /// \brief Método responsável pela validação do cpf fornecido.
        /// \param cpf String contendo o cpf a ser verificado.
        void validar(string cpf) const throw (invalid_argument);
        /// \brief Método que verifica se a string fornecida é composta somente de algarismos, "." e "-" - dos quais os ultimos dois devem estar nas posições corretas, caso estejam presentes. Se não estiverem no formato correto, lança um erro. Após esta verificação, retorna uma string com algarismos somente.
        /// \param cpf String a ser verificada e filtrada.
        /// \return String composta apeas de numeros.
        string filtrar(string cpf) const throw (invalid_argument);
        /// \brief Método que recebe um cpf composto apenas de algarismos e retorna uma string composta de seus dígitos verificadores corretos.
        /// \param cpf String composta somente de algarismos, a partir dos quais retorna os digitos verificadores para estes.
        /// \return String de tamano 2 com dois digitos verificadores.
        string digitoVerificador(string cpf) const throw (invalid_argument);
    public:
        /// \brief Método que recebe uma string para cpf e a guarda em memória caso esta seja válida.
        /// \param cpf CPF a ser guardado em memória.
        void set(string cpf) throw (invalid_argument);
        /// \brief Método que retorna o valor de CPF salvo em memória.
        /// \return CPF previamente salvo em memória.
        string get(){
            return this->cpf;
        }
};

/// \brief Classe do domínio de Senha, que permine ser guardado no objeto criado uma senha válida - de 6 dígitos com ao menos uma letra maiúscula, uma minúscula e um algarismo - por meio de set, e recuperar esta senha por meio de get.
class Senha{
    private:
        string senha;///>  Variável que guarda a senha salva por meio do método set.
        const static int TAMANHOSENHA = 6; ///> Variável estática e constante que guarda o tamanho que a senha deve ter.
        /// \brief Método que valida a senha, assegurando se ela possui 6 caracteres, tendo ao menos um maiúsclo, um minúsculo e um número. Caso este não seja o caso, lança um erro.
        /// \param senha Senha a ser verificada.
        void validar(string senha) const throw (invalid_argument);
    public:
        /// \brief Método que salva a string fornecida, saco esta seja válida.
        /// \param senha Senha a ser guardada.
        void set(string senha) throw (invalid_argument);
        /// \brief Método pelo qual se acessa a senha salva no objeto. retorna o valor salvo na variável senha por meio do método set.
        /// \return Retorna o valor guardado na variavel senha.
        string get(){
            return this->senha;
        }
};

/// \brief Classe do domínio de Número de Cartão de Crédito, que permite o armazenamento de um número de cartão de crédito valido por meio do algoritmo de Luhn pela Método set, e a recuperação deste por meio da Método get.
class NumeroCartao{
    private:
        const static int TAMANHOCARTAO = 16;///> variável que guarda o tamanho do numero de cartão.
        string numeroCartao;///> Variável que armazena o número de cartão fornecido por meio da função set.
        /// \brief Método que verifica se o número de cartão fornecido é composto apenas de números e se o ultimo dígito respeita o algoritmo de Luhn.
        /// \param numeroCartao Número de cartão a ser verificado.
        void validar(string numeroCartao) const throw(invalid_argument);
        /// \brief Método que calcula o dígito de verificação para o numero de cartão fornecido, e retorna este algarismo.
        /// \param numeroCartao string contendo o número do cartão a ter seu digito de verificação calculado.
        /// \return Retorna o que deve ser o último caractere do numero do cartão.
        char luhn(string numeroCartao) const;
    public:
        /// \brief Método responsável por salvar o numero de cartão fornecido, caso este seja válido. Se o número fornecido for inválido, lança um erro.
        /// \param numeroCartao String contendo o número a ser validado e salvo em memória.
        void set(string numeroCartao) throw (invalid_argument);
        /// \brief Método pelo qual se acessa o valor salvo em memória por meio do método set.
        /// \return Retorna o número do cartão.
        string get(){
            return this->numeroCartao;
        }
};

/// \brief Classe do domínio de Código de Segurança, que deve ser um inteiro de três dígitos. Este pode ser guardado por meio da Método set e recuperado por meio da Método get.
class CodigoSeguranca{
    private:
        const static int TAMANHOCODIGO = 3;///> Variável estática e constante que guarda o tamanho que o código de segurança deve ter.
        int codigoSeguranca;///> campo que guarda o código de segurança salvo por meio do método set.
        /// \brief Método responsável por verificar se o código fornecido é composto por um número de três dígitos.
        /// \param codigoSeguranca Código a ser validado.
        void validar(string codigoSeguranca) const throw (invalid_argument);
    public:
        /// \brief Método responsável por salvar o código fornecido, caso este passe pela validação.
        /// \param codioSeguranca Código a ser validado e salvo.
        void set(string codigoSeguranca) throw (invalid_argument);
        /// \brief Mátodo pelo qual se acessa o valor guardado no objeto.
        /// \return Retorna o código de segurança salvo na variável.
        int get(){
            return this->codigoSeguranca;
        }
};

/// \brief Classe do domínio de Data de Validade, que deve estar no formato XX/YY - ou similar, podendo serem ignorados zeros à esquerda. Este valor é guardado por meio de set e recuperado por meio de get.
class DataValidade{
    private:
        string dataValidade; ///> Variável que guarda a string contendo a data de validade, por meio da função set.
        /// \brief função que verifica se a data de falidade seue o padão XX/YY, e lança um erro caso isto não ocorra.
        /// \param dataValidade string contendo a data de validade a ser validada.
        void validar(string dataValidade) const throw (invalid_argument);
    public:
        /// \brief Método a partir do qual se guarda um valor para data de validade, desde que este passe pea validação.
        /// \param savaValidade String a ser fornecida dontendo uma data de validade no formato XX/YY, sendo XX entre 01 e 12 e YY entre 00 e 99.
        void set(string dataValidade) throw (invalid_argument);
        /// \brief Método que retorna a validade guardada por meio do método set.
        string get(){
            return this->dataValidade;
        }
};

/// Classe CodigoEvento que se encarrega do armazenamento,acesso e validação do código de evento.
class CodigoEvento{
    private:

        string codigoEvento; ///< codigo de evento a ser armazenado em string.
        const static int TAMANHO = 3; ///< tamanho que deve ter a string codigo de evento.
        void checaTamanho(string codigoEvento) throw(invalid_argument);
        void checaDigitos(string codigoEvento)throw(invalid_argument);
        void validar(string codigoEvento);

    public:

        void set(string codigoEvento);
        string get();
};

/// Classe CodigoApresentação que se encarrega do armazenamento,acesso e validação do código de evento.
class CodigoApresentacao{
    private:

        string codigoApresentacao; ///< codigo de apresentação a ser armazenado em string.
        const static int TAMANHO = 4; ///< tamanho que deve ter a string código de apresentação.
        void checaTamanho(string codigoApresentacao) throw(invalid_argument);
        void checaDigitos(string codigoApresentacao)throw(invalid_argument);
        void validar(string codigoApresentacao);

    public:

        void set(string codigoApresentacao);
        string get();
};

/// Classe CodigoIngresso que se encarrega do armazenamento,acesso e validação do código de evento.
class CodigoIngresso{
    private:

        string codigoIngresso; ///< código de ingresso a ser armazenado em string.
        const static int TAMANHO = 5; ///< tamanho que deve ter a string codigo de ingresso.
        void checaTamanho(string codigoIngresso) throw(invalid_argument);
        void checaDigitos(string codigoIngresso)throw(invalid_argument);
        void validar(string codigoIngresso);

    public:

        void set(string codigoIngresso);
        string get();
};


/// Classe NomeEvento que se encarrega do armazenamento,acesso e validação do nome do evento.
class NomeEvento{
    private:

        string nomeEvento; ///< Nome do evento a ser armazenado em string.
        const static int LIMITE = 20; ///< Tamanho limite
        void checaTamanho(string nomeEvento) throw(invalid_argument);
        void checaCaracteres(string nomeEvento) throw(invalid_argument);
        void checaExisteLetra(string nomeEvento) throw(invalid_argument);
        void checaEspacoSeguido(string nomeEvento) throw(invalid_argument);
        void validar(string nomeEvento);

    public:

        void set(string nomeEvento);
        string get();
};

/// Classe de armazenamento, acesso e validação da data
class Data{
    private:

        string data; ///< Data em formato DD/MM/AAAA a ser armazenado em string.
        const static int TAMANHO = 10; ///< Tamanho requerido da string data.
        string arrumaFormato(string data);
        void checaDigitos(string arg) throw(invalid_argument);
        void checaBarra(string data) throw(invalid_argument);
        void checaTamanho(string data) throw(invalid_argument);
        void checaFormato(string data);
        bool checaBissexto(string ano);
        void checaDia(string dia, string mes, string ano) throw(invalid_argument);
        void checaMes(string mes) throw(invalid_argument);
        void checaAno(string ano) throw(invalid_argument);
        void validar(string data);

    public:

        void set(string data);
        string get();
};

/// Classe de armazenamento, acesso e validação de horário.
class Horario{
    private:

        string horario; ///< Horario em formato HH:MM a ser armazenado em string.
        const static int TAMANHO = 5; ///< Tamanho requerido da string horario.
        void checaTamanho(string horario) throw(invalid_argument);
        void checaDoisPontos(string horario) throw(invalid_argument);
        void checaDigitos(string arg) throw(invalid_argument);
        void checaFormato(string horario);
        void checaHora(string hora) throw(invalid_argument);
        void checaMinuto(string minuto) throw(invalid_argument);
        void validar(string horario);

    public:

        void set(string horario);
        string get();
};

/// Classe de armazenamento, acesso e validação de preço.
class Preco{
    private:

        float preco;///< Preço a ser armazenado em float.
        const static int MAXIMO = 1000; ///< Limite superior do preço.
        const static int MINIMO = 0; ///< Limite inferior do preço.
        void  validar(float preco) throw(invalid_argument);

    public:

        void set(float preco);
        float get();
};

/// Classe de armazenamento, acesso e validação de número de sala.
class NumeroSala{
    private:

        int numeroSala;///< Número de sala a ser armazenado em int.
        const static int MAXIMO = 10; ///< Limite superior do número de sala.
        const static int MINIMO = 1; ///< Limite inferior do número de sala.
        void  validar(int numeroSala) throw(invalid_argument);

    public:

        void set(int numeroSala);
        int get();
};

/// Classe de armazenamento, acesso e validação de cidade.
class Cidade{
    private:

        string cidade; ///< Cidade a ser armazenada em string.
        const static int LIMITE = 15;///< Números de caracteres limite de cidade.
        void checaTamanho(string cidade) throw(invalid_argument);
        void checaCaracteres(string cidade) throw(invalid_argument);
        void checaExisteLetra(string cidade) throw(invalid_argument);
        void checaEspacoSeguido(string cidade) throw(invalid_argument);
        void checaPonto(string cidade) throw(invalid_argument);
        void validar(string cidade);

    public:
        void set(string cidade);
        string get();
};

#endif
