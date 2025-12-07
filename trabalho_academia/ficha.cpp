#include "Ficha.h"
#include <sstream>
#include <iostream>

int Ficha::proximoIdFicha = 1;

Ficha::Ficha(const std::string &n) {
    nome = n;
    id = proximoIdFicha++;
}

Ficha::Ficha(int idExistente, const std::string &n) {
    id = idExistente;
    nome = n;
    if (idExistente >= proximoIdFicha) proximoIdFicha = idExistente + 1;
}

void Ficha::adicionarExercicio(Exercicio* e) {
    if (e) exercicios.push_back(e);
}

double Ficha::calcularTempoTotalMin() const {
    double soma = 0.0;
    for (auto e : exercicios) {
        if (e && e->isAtivo()) soma += e->calcularTempoMin();
    }
    return soma;
}

double Ficha::calcularCaloriasTotal() const {
    double soma = 0.0;
    for (auto e : exercicios) {
        if (e && e->isAtivo()) soma += e->calcularCalorias();
    }
    return soma;
}

std::string Ficha::serializar() const {
    std::ostringstream oss;
    oss << id << ";" << nome << ";" << exercicios.size();
    for (auto e : exercicios) {
        oss << ";" << (e ? e->getId() : -1);
    }
    return oss.str();
}

void Ficha::exibirDetalhes() const {
    std::cout << "Ficha ID: " << id << " | Nome: " << nome << std::endl;
    std::cout << "Exercicios:" << std::endl;
    for (auto e : exercicios) {
        if (e) e->exibirDetalhes();
    }
    std::cout << "TOTAL - Tempo (min): " << calcularTempoTotalMin()
              << " | Calorias: " << calcularCaloriasTotal() << std::endl;
}