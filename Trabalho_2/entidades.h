#ifndef ENTIDADES_H
#define ENTIDADES_H

#include "dominios.h"

/// \brief Classe respons�vel pelas informa��es do usu�rio.
class Usuario{
    private:

        CPF cpf;///> Vari�vel que guarda o cpf do usuario, composta por um objeto da classe CPF.
        Senha senha;///> Vari�vel que guarda a senha do usuario, composta por um objeto da classe Senha.
    public:
        /// \brief fun��es que recebem um objeto das respectivas classes e os guardam no objeto Usu�rio.
        void setCPF(CPF &cpf);
        void setSenha(Senha &senha);

        /// \brief fun��es que retornam os objetos previamente guardados por meio do metodo set.
        CPF getCPF();
        Senha getSenha();
};

class Evento{
    private:
        /// \brief Vari�veis que guardam objetos dos tipos b�sicos usados pela classe Evento.
        CodigoEvento codigo;
        NomeEvento nome;
        Cidade cidade;
        Estado estado;
        ClasseEvento classe;
        FaixaEtaria faixa;

    public:
        /// \brief fun��es que recebem um objeto das respectivas classes e os guardam no objeto Eventos.
        void setCodigo(CodigoEvento codigo);
        void setNome(NomeEvento &nome);
        void setCidade(Cidade &cidade);
        void setEstado(Estado &estado);
        void setClasse(ClasseEvento &classe);
        void setFaixa(FaixaEtaria &faixa);

        /// \brief fun��es que retornam os objetos previamente guardados por meio do metodo set.
        CodigoEvento getCodigo();
        NomeEvento getNome();
        Cidade getCidade();
        Estado getEstado();
        ClasseEvento getClasse();
        FaixaEtaria getFaixa();

};

class Apresentacao{
    private:

        /// \brief Vari�veis que guardam objetos dos tipos b�sicos usados pela classe Apresenta��o.
        CodigoApresentacao codigo;
        Data data;
        Horario horario;
        Preco preco;
        NumeroSala sala;
        Disponibilidade disponibilidade;

    public:

        /// \brief fun��es que recebem um objeto das respectivas classes e os guardam no objeto Apresenta��o.
        void setCodigo(CodigoApresentacao &codigo);
        void setData(Data &data);
        void setHorario(Horario &horario);
        void setPreco(Preco &preco);
        void setSala(NumeroSala &sala);
        void setDisponibilidade(Disponibilidade &disponibilidade);

        /// \brief fun��es que retornam os objetos previamente guardados por meio do metodo set.
        CodigoApresentacao getCodigo();
        Data getData();
        Horario getHorario();
        Preco getPreco();
        NumeroSala getSala();
        Disponibilidade getDisponibilidade();
};

class Ingresso{
    private:

        /// \brief Vari�vel que guarda objeto do tipo b�sico CodigoIngresso.
        CodigoIngresso codigo;

    public:
        /// \brief fun��es que recebem - set - e retornam - get - o c�digo para o Ingresso.
        void setCodigo(CodigoIngresso &codigo);
        CodigoIngresso getCodigo();
};

class CartaoCredito{
    private:
        /// \brief Vari�veis que guardam objetos dos tipos b�sicos usados pela classe CartaoCredito.
        NumeroCartao numero;
        CodigoSeguranca codigo;
        DataValidade data;

    public:
        /// \brief fun��es que retornam os objetos previamente guardados por meio do metodo set.
        void setNumero(NumeroCartao &numero);
        NumeroCartao getNumero();
        void setCodigo(CodigoSeguranca &codigo);
        CodigoSeguranca getCodigo();
        void setData(DataValidade &data);
        DataValidade getData();

};
#endif // ENTIDADES
