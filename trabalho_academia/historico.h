#ifndef HISTORICO_H
#define HISTORICO_H

#include <string>
#include <sstream>

struct Registro {
    std::string dataHora;
    int idFicha;
    std::string nomeFicha;
    double tempoTotal;
    double caloriasTotal;

    std::string serializar() const {
        std::ostringstream oss;
        oss << dataHora << ";" << idFicha << ";" << nomeFicha << ";" << tempoTotal << ";" << caloriasTotal;
        return oss.str();
    }
};

#endif 