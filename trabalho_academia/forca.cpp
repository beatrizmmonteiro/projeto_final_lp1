#include "Forca.h"
#include <iostream>
#include <sstream>

Forca::Forca(const std::string &n, double carga, int s, int r, int descanso)
    : Exercicio(n), cargaKg(carga), series(s), repeticoes(r), descansoSeg(descanso) {}

Forca::Forca(int idExistente, const std::string &n, double carga, int s, int r, int descanso, bool status)
    : Exercicio(idExistente, n, status), cargaKg(carga), series(s), repeticoes(r), descansoSeg(descanso) {}

double Forca::calcularTempoMin() const {
    double totalSeg = static_cast<double>(series) * static_cast<double>(repeticoes) * 3.0
                      + static_cast<double>(series) * static_cast<double>(descansoSeg);
    return totalSeg / 60.0;
}

double Forca::calcularCalorias() const {
    return static_cast<double>(series) * static_cast<double>(repeticoes) * cargaKg * 0.15;
}

void Forca::exibirDetalhes() const {
    std::cout << "Tipo: Forca | ID: " << id << " | Nome: " << nome
              << " | Status: " << (ativo ? "Ativo" : "Inativo")
              << " | Carga(kg): " << cargaKg
              << " | Series: " << series
              << " | Repeticoes: " << repeticoes
              << " | Descanso(s): " << descansoSeg << std::endl;
}

std::string Forca::serializar() const {
    std::ostringstream oss;
    oss << "2;" << id << ";" << nome << ";" << cargaKg << ";" << series << ";" << repeticoes << ";" << descansoSeg << ";" << (ativo ? 1 : 0);
    return oss.str();
}