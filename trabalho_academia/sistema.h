#ifndef SISTEMA_H
#define SISTEMA_H

#include <vector>
#include <string>
#include "Exercicio.h"
#include "Ficha.h"
#include "Historico.h"

class Sistema {
private:
    std::vector<Exercicio*> bancoExercicios;
    std::vector<Ficha> fichas;
    std::vector<Registro> historico;

    std::string arquivoExercicios;
    std::string arquivoFichas;
    std::string arquivoHistorico;

    Exercicio* buscarExercicioPorId(int id);
    std::string agoraFormatado() const;

    void carregarExercicios();
    void salvarExercicios() const;
    void carregarFichas();
    void salvarFichas() const;
    void carregarHistorico();
    void salvarHistorico() const;

public:
    Sistema(const std::string &ex, const std::string &fi, const std::string &hi);
    ~Sistema();

    void iniciar();

    void cadastrarCardio(const std::string &nome, int duracao, double calpm);
    void cadastrarForca(const std::string &nome, double carga, int s, int r, int descanso);
};

#endif