#ifndef FICHA_H
#define FICHA_H

#include <vector>
#include <string>
#include "Exercicio.h"

class Ficha {
private:
    int id;
    std::string nome;
    std::vector<Exercicio*> exercicios; 
    static int proximoIdFicha;
public:
    Ficha(const std::string &n);
    Ficha(int idExistente, const std::string &n);

    int getId() const { return id; }
    std::string getNome() const { return nome; }

    void adicionarExercicio(Exercicio* e);
    const std::vector<Exercicio*>& getExercicios() const { return exercicios; }

    double calcularTempoTotalMin() const;
    double calcularCaloriasTotal() const;

    std::string serializar() const;
    void exibirDetalhes() const;
};

#endif