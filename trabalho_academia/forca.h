#ifndef FORCA_H
#define FORCA_H

#include "Exercicio.h"
#include <string>

class Forca : public Exercicio {
private:
    double cargaKg;
    int series;
    int repeticoes;
    int descansoSeg;
public:
    Forca(const std::string &n, double carga, int s, int r, int descanso);
    Forca(int idExistente, const std::string &n, double carga, int s, int r, int descanso, bool status);

    double calcularTempoMin() const override;
    double calcularCalorias() const override;
    void exibirDetalhes() const override;
    int getTipo() const override { return 2; }
    std::string serializar() const override;
};

#endif 