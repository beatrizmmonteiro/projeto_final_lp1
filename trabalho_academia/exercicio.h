#ifndef EXERCICIO_H
#define EXERCICIO_H

#include <string>

class Exercicio {
protected:
    int id;
    std::string nome;
    bool ativo;
    static int proximoId;

public:
    Exercicio(const std::string &n);

    Exercicio(int idExistente, const std::string &n, bool status);

    virtual ~Exercicio() {}

    int getId() const { return id; }
    std::string getNome() const { return nome; }
    bool isAtivo() const { return ativo; }
    void setAtivo(bool a) { ativo = a; }

    virtual double calcularTempoMin() const = 0;
    virtual double calcularCalorias() const = 0;
    virtual void exibirDetalhes() const = 0;
    virtual int getTipo() const = 0; 
    virtual std::string serializar() const = 0;

    static void setProximoIdIfGreater(int idLido);
};

#endif 