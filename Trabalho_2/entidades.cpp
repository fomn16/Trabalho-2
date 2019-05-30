#include "entidades.h"

/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  USUARIO  ///////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void Usuario::setCPF(CPF &cpf){
    this->cpf = cpf;
}

CPF Usuario::getCPF(){
    return this->cpf;
}

void Usuario::setSenha(Senha &senha){
    this->senha = senha;
}

Senha Usuario::getSenha(){
    return this->senha;
}

/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  EVENTO  ////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void Evento::setCodigo(CodigoEvento codigo){
    this->codigo = codigo;
}

CodigoEvento Evento::getCodigo(){
    return this->codigo;
}

void Evento::setNome(NomeEvento &nome){
    this->nome = nome;
}

NomeEvento Evento::getNome(){
    return this->nome;
}

void Evento::setCidade(Cidade &cidade){
    this->cidade = cidade;
}

Cidade Evento::getCidade(){
    return this->cidade;
}

void Evento::setEstado(Estado &estado){
    this->estado = estado;
}

Estado Evento::getEstado(){
    return this->estado;
}

void Evento::setClasse(ClasseEvento &classe){
    this->classe = classe;
}

ClasseEvento Evento::getClasse(){
    return this->classe;
}

void Evento::setFaixa(FaixaEtaria &faixa){
    this->faixa = faixa;
}

FaixaEtaria Evento::getFaixa(){
    return this->faixa;
}

/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  APRESENTACAO  //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void Apresentacao::setCodigo(CodigoApresentacao &codigo){
    this->codigo = codigo;
}

CodigoApresentacao Apresentacao::getCodigo(){
    return this->codigo;
}

void Apresentacao::setData(Data &data){
    this->data = data;
}

Data Apresentacao::getData(){
    return this->data;
}

void Apresentacao::setHorario(Horario &horario){
    this->horario = horario;
}

Horario Apresentacao::getHorario(){
    return this->horario;
}

void Apresentacao::setPreco(Preco &preco){
    this->preco = preco;
}

Preco Apresentacao::getPreco(){
    return this->preco;
}

void Apresentacao::setSala(NumeroSala &sala){
    this->sala = sala;
}

NumeroSala Apresentacao::getSala(){
    return this->sala;
}

void Apresentacao::setDisponibilidade(Disponibilidade &disponibilidade){
    this->disponibilidade = disponibilidade;
}

Disponibilidade Apresentacao::getDisponibilidade(){
    return this->disponibilidade;
}

/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  INGRESSO  //////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void Ingresso::setCodigo(CodigoIngresso &codigo){
    this->codigo = codigo;
}

CodigoIngresso Ingresso::getCodigo(){
    return this->codigo;
}

/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////  CARTAO DE CREDITO  /////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

void CartaoCredito::setNumero(NumeroCartao &numero){
    this->numero = numero;
}

NumeroCartao CartaoCredito::getNumero(){
    return this->numero;
}

void CartaoCredito::setCodigo(CodigoSeguranca &codigo){
    this->codigo = codigo;
}

CodigoSeguranca CartaoCredito::getCodigo(){
    return this->codigo;
}

void CartaoCredito::setData(DataValidade &data){
    this->data = data;
}

DataValidade CartaoCredito::getData(){
    return this->data;
}
