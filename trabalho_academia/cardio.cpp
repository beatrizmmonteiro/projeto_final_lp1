#include "Cardio.h"
#include <iostream>
#include <sstream>

Cardio::Cardio(const std::string &n, int duracao, double calPorMin)
    : Exercicio(n), duracaoMin(duracao), caloriasPorMin(calPorMin) {}

Cardio::Cardio(int idExistente, const std::string &n, int duracao, double calPorMin, bool status)
    : Exercicio(idExistente, n, status), duracaoMin(duracao), caloriasPorMin(calPorMin) {}

double Cardio::calcularTempoMin() const {
    return static_cast<double>(duracaoMin);
}

double Cardio::calcularCalorias() const {
    return duracaoMin * caloriasPorMin;
}

void Cardio::exibirDetalhes() const {
    std::cout << "Tipo: Cardio | ID: " << id << " | Nome: " << nome
              << " | Status: " << (ativo ? "Ativo" : "Inativo")
              << " | Duracao(min): " << duracaoMin
              << " | Cal/min: " << caloriasPorMin << std::endl;
}

std::string Cardio::serializar() const {
    std::ostringstream oss;
    oss << "1;" << id << ";" << nome << ";" << duracaoMin << ";" << caloriasPorMin << ";" << (ativo ? 1 : 0);
    return oss.str();
}