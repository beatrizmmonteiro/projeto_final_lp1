#include "Exercicio.h"

int Exercicio::proximoId = 1;

Exercicio::Exercicio(const std::string &n) {
    nome = n;
    ativo = true;
    id = proximoId++;
}

Exercicio::Exercicio(int idExistente, const std::string &n, bool status) {
    id = idExistente;
    nome = n;
    ativo = status;
    setProximoIdIfGreater(idExistente);
}

void Exercicio::setProximoIdIfGreater(int idLido) {
    if (idLido >= proximoId) proximoId = idLido + 1;
}