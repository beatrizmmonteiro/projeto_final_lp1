#ifndef CARDIO_H
#define CARDIO_H

#include "Exercicio.h"
#include <string>

class Cardio : public Exercicio {
private:
    int duracaoMin;
    double caloriasPorMin;
public:
    Cardio(const std::string &n, int duracao, double calPorMin);
    Cardio(int idExistente, const std::string &n, int duracao, double calPorMin, bool status);

    double calcularTempoMin() const override;
    double calcularCalorias() const override;
    void exibirDetalhes() const override;
    int getTipo() const override { return 1; }
    std::string serializar() const override;
};

#endif 