#ifndef ENTIDADES_H
#define ENTIDADES_H

#include "dominios.h"

/// \brief Classe responsável pelas informações do usuário.
class Usuario{
    private:

        CPF cpf;///> Variável que guarda o cpf do usuario, composta por um objeto da classe CPF.
        Senha senha;///> Variável que guarda a senha do usuario, composta por um objeto da classe Senha.
    public:
        /// \brief funções que recebem um objeto das respectivas classes e os guardam no objeto Usuário.
        void setCPF(CPF &cpf);
        void setSenha(Senha &senha);

        /// \brief funções que retornam os objetos previamente guardados por meio do metodo set.
        CPF getCPF();
        Senha getSenha();
};

class Evento{
    private:
        /// \brief Variáveis que guardam objetos dos tipos básicos usados pela classe Evento.
        CodigoEvento codigo;
        NomeEvento nome;
        Cidade cidade;
        Estado estado;
        ClasseEvento classe;
        FaixaEtaria faixa;

    public:
        /// \brief funções que recebem um objeto das respectivas classes e os guardam no objeto Eventos.
        void setCodigo(CodigoEvento codigo);
        void setNome(NomeEvento &nome);
        void setCidade(Cidade &cidade);
        void setEstado(Estado &estado);
        void setClasse(ClasseEvento &classe);
        void setFaixa(FaixaEtaria &faixa);

        /// \brief funções que retornam os objetos previamente guardados por meio do metodo set.
        CodigoEvento getCodigo();
        NomeEvento getNome();
        Cidade getCidade();
        Estado getEstado();
        ClasseEvento getClasse();
        FaixaEtaria getFaixa();

};

class Apresentacao{
    private:

        /// \brief Variáveis que guardam objetos dos tipos básicos usados pela classe Apresentação.
        CodigoApresentacao codigo;
        Data data;
        Horario horario;
        Preco preco;
        NumeroSala sala;
        Disponibilidade disponibilidade;

    public:

        /// \brief funções que recebem um objeto das respectivas classes e os guardam no objeto Apresentação.
        void setCodigo(CodigoApresentacao &codigo);
        void setData(Data &data);
        void setHorario(Horario &horario);
        void setPreco(Preco &preco);
        void setSala(NumeroSala &sala);
        void setDisponibilidade(Disponibilidade &disponibilidade);

        /// \brief funções que retornam os objetos previamente guardados por meio do metodo set.
        CodigoApresentacao getCodigo();
        Data getData();
        Horario getHorario();
        Preco getPreco();
        NumeroSala getSala();
        Disponibilidade getDisponibilidade();
};

class Ingresso{
    private:

        /// \brief Variável que guarda objeto do tipo básico CodigoIngresso.
        CodigoIngresso codigo;

    public:
        /// \brief funções que recebem - set - e retornam - get - o código para o Ingresso.
        void setCodigo(CodigoIngresso &codigo);
        CodigoIngresso getCodigo();
};

class CartaoCredito{
    private:
        /// \brief Variáveis que guardam objetos dos tipos básicos usados pela classe CartaoCredito.
        NumeroCartao numero;
        CodigoSeguranca codigo;
        DataValidade data;

    public:
        /// \brief funções que retornam os objetos previamente guardados por meio do metodo set.
        void setNumero(NumeroCartao &numero);
        NumeroCartao getNumero();
        void setCodigo(CodigoSeguranca &codigo);
        CodigoSeguranca getCodigo();
        void setData(DataValidade &data);
        DataValidade getData();

};
#endif // ENTIDADES
