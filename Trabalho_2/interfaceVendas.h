#ifndef INTERFACE_VENDAS_H
#define INTERFACE_VENDAS_H

#include "dominios.h"
#include "entidades.h"


using namespace std;

class ISVendas{
    public:
        virtual void processarVenda(CPF cpf, CodigoEvento codigoEvento, CodigoApresentacao codigoApresentacao) = 0;
        virtual Ingresso pesquisarIngresso(CPF cpf, int n) = 0;
        virtual int nIngressos(CPF cpf) = 0;
        virtual ~ISVendas(){}
};

class IAVendas{
    public:
        virtual void executar() = 0;
        virtual void setCSVendas (ISVendas *cSVendas) = 0;
        virtual ~IAVendas(){}
};

#endif // INTERFACE_VENDAS_H

