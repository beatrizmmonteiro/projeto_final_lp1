#include "Sistema.h"
#include "Cardio.h"
#include "Forca.h"
#include "Utils.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>

Sistema::Sistema(const std::string &ex, const std::string &fi, const std::string &hi)
    : arquivoExercicios(ex), arquivoFichas(fi), arquivoHistorico(hi) {
    carregarExercicios();
    carregarFichas();
    carregarHistorico();
}

Sistema::~Sistema() {
    // liberar ponteiros
    for (auto p : bancoExercicios) delete p;
    salvarExercicios();
    salvarFichas();
    salvarHistorico();
}

Exercicio* Sistema::buscarExercicioPorId(int id) {
    for (auto e : bancoExercicios) if (e && e->getId() == id) return e;
    return nullptr;
}

std::string Sistema::agoraFormatado() const {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << tm.tm_mday << "/"
        << std::setw(2) << (tm.tm_mon + 1) << "/"
        << (tm.tm_year + 1900) << " "
        << std::setw(2) << tm.tm_hour << ":"
        << std::setw(2) << tm.tm_min << ":"
        << std::setw(2) << tm.tm_sec;
    return oss.str();
}

void Sistema::carregarExercicios() {
    std::ifstream ifs(arquivoExercicios.c_str());
    if (!ifs.is_open()) return;
    std::string linha;
    while (std::getline(ifs, linha)) {
        if (linha.empty()) continue;
        auto campos = Utils::split(linha, ';');
        if (campos.size() < 1) continue;
        int tipo = std::stoi(campos[0]);
        if (tipo == 1 && campos.size() >= 6) {
            int id = std::stoi(campos[1]);
            std::string nome = campos[2];
            int dur = std::stoi(campos[3]);
            double calpm = std::stod(campos[4]);
            bool status = (std::stoi(campos[5]) != 0);
            bancoExercicios.push_back(new Cardio(id, nome, dur, calpm, status));
        } else if (tipo == 2 && campos.size() >= 8) {
            int id = std::stoi(campos[1]);
            std::string nome = campos[2];
            double carga = std::stod(campos[3]);
            int series = std::stoi(campos[4]);
            int rep = std::stoi(campos[5]);
            int descanso = std::stoi(campos[6]);
            bool status = (std::stoi(campos[7]) != 0);
            bancoExercicios.push_back(new Forca(id, nome, carga, series, rep, descanso, status));
        }
    }
    ifs.close();
}

void Sistema::salvarExercicios() const {
    std::ofstream ofs(arquivoExercicios.c_str());
    for (auto e : bancoExercicios) {
        if (e) ofs << e->serializar() << "\n";
    }
    ofs.close();
}

void Sistema::carregarFichas() {
    std::ifstream ifs(arquivoFichas.c_str());
    if (!ifs.is_open()) return;
    std::string linha;
    while (std::getline(ifs, linha)) {
        if (linha.empty()) continue;
        auto campos = Utils::split(linha, ';');
        if (campos.size() >= 3) {
            int idFicha = std::stoi(campos[0]);
            std::string nome = campos[1];
            int total = std::stoi(campos[2]);
            Ficha f(idFicha, nome);
            for (int i = 0; i < total; ++i) {
                if (3 + i < (int)campos.size()) {
                    int idEx = std::stoi(campos[3 + i]);
                    Exercicio* e = buscarExercicioPorId(idEx);
                    if (e) f.adicionarExercicio(e);
                }
            }
            fichas.push_back(f);
        }
    }
    ifs.close();
}

void Sistema::salvarFichas() const {
    std::ofstream ofs(arquivoFichas.c_str());
    for (const auto &f : fichas) ofs << f.serializar() << "\n";
    ofs.close();
}

void Sistema::carregarHistorico() {
    std::ifstream ifs(arquivoHistorico.c_str());
    if (!ifs.is_open()) return;
    std::string linha;
    while (std::getline(ifs, linha)) {
        if (linha.empty()) continue;
        auto campos = Utils::split(linha, ';');
        if (campos.size() >= 5) {
            Registro r;
            r.dataHora = campos[0];
            r.idFicha = std::stoi(campos[1]);
            r.nomeFicha = campos[2];
            r.tempoTotal = std::stod(campos[3]);
            r.caloriasTotal = std::stod(campos[4]);
            historico.push_back(r);
        }
    }
    ifs.close();
}

void Sistema::salvarHistorico() const {
    std::ofstream ofs(arquivoHistorico.c_str());
    for (const auto &r : historico) ofs << r.serializar() << "\n";
    ofs.close();
}

void Sistema::cadastrarCardio(const std::string &nome, int duracao, double calpm) {
    bancoExercicios.push_back(new Cardio(nome, duracao, calpm));
}

void Sistema::cadastrarForca(const std::string &nome, double carga, int s, int r, int descanso) {
    bancoExercicios.push_back(new Forca(nome, carga, s, r, descanso));
}

void Sistema::iniciar() {
    while (true) {
        std::cout << "\n=== Menu Principal ===\n";
        std::cout << "1 Gerenciar Banco de Exercicios\n2 Gerenciar Fichas de Treino\n3 Registrar Execucao\n4 Consultar Historico\n0 Sair\nEscolha: ";
        int op; std::cin >> op;
        if (op == 1) {
            while (true) {
                std::cout << "\n--- Gerenciar Banco de Exercicios ---\n";
                std::cout << "1 Cadastrar\n2 Listar Ativos\n3 Listar Todos\n4 Excluir (logico)\n0 Voltar\nEscolha: ";
                int op2; std::cin >> op2;
                if (op2 == 1) {
                    std::cout << "Tipo (1 = Cardio, 2 = Forca): ";
                    int t; std::cin >> t; std::cin.ignore();
                    if (t == 1) {
                        std::string nome; int dur; double calpm;
                        std::cout << "Nome: "; std::getline(std::cin, nome);
                        std::cout << "Duracao (min): "; std::cin >> dur;
                        std::cout << "Calorias por minuto: "; std::cin >> calpm;
                        bancoExercicios.push_back(new Cardio(nome, dur, calpm));
                        std::cout << "Cardio cadastrado.\n";
                    } else if (t == 2) {
                        std::string nome; double carga; int s, r, desc;
                        std::cout << "Nome: "; std::getline(std::cin, nome);
                        std::cout << "Carga (kg): "; std::cin >> carga;
                        std::cout << "Series: "; std::cin >> s;
                        std::cout << "Repeticoes: "; std::cin >> r;
                        std::cout << "Descanso (s): "; std::cin >> desc;
                        bancoExercicios.push_back(new Forca(nome, carga, s, r, desc));
                        std::cout << "Forca cadastrado.\n";
                    } else {
                        std::cout << "Tipo invalido.\n";
                    }
                } else if (op2 == 2) {
                    std::cout << "=== Lista de Exercicios Ativos ===\n";
                    for (auto e : bancoExercicios) if (e && e->isAtivo()) e->exibirDetalhes();
                } else if (op2 == 3) {
                    std::cout << "=== Lista de Todos os Exercicios ===\n";
                    for (auto e : bancoExercicios) if (e) e->exibirDetalhes();
                } else if (op2 == 4) {
                    std::cout << "ID do exercicio para marcar Inativo: ";
                    int id; std::cin >> id;
                    Exercicio* e = buscarExercicioPorId(id);
                    if (!e) { std::cout << "Nao encontrado.\n"; }
                    else { e->setAtivo(false); std::cout << "Exercicio marcado como Inativo.\n"; }
                } else if (op2 == 0) break;
                else std::cout << "Opcao invalida.\n";
            }
        } else if (op == 2) {
            while (true) {
                std::cout << "\n--- Gerenciar Fichas de Treino ---\n";
                std::cout << "1 Criar Ficha\n2 Adicionar Exercicio\n3 Visualizar Fichas\n0 Voltar\nEscolha: ";
                int op2; std::cin >> op2;
                if (op2 == 1) {
                    std::cin.ignore();
                    std::string nome;
                    std::cout << "Nome da ficha: ";
                    std::getline(std::cin, nome);
                    fichas.push_back(Ficha(nome));
                    std::cout << "Ficha criada.\n";
                } else if (op2 == 2) {
                    if (fichas.empty()) { std::cout << "Nao ha fichas.\n"; continue; }
                    std::cout << "Fichas disponiveis:\n";
                    for (const auto &f : fichas) std::cout << f.getId() << " - " << f.getNome() << "\n";
                    std::cout << "Escolha ID da ficha: ";
                    int idFicha; std::cin >> idFicha;
                    Ficha* ptrFicha = nullptr;
                    for (auto &f : fichas) if (f.getId() == idFicha) { ptrFicha = &f; break; }
                    if (!ptrFicha) { std::cout << "Ficha nao encontrada.\n"; continue; }

                    std::cout << "Exercicios ativos:\n";
                    for (auto e : bancoExercicios) if (e && e->isAtivo()) e->exibirDetalhes();
                    std::cout << "Digite ID do exercicio para adicionar: ";
                    int idEx; std::cin >> idEx;
                    Exercicio* ex = buscarExercicioPorId(idEx);
                    if (!ex) { std::cout << "Exercicio nao encontrado.\n"; continue; }
                    ptrFicha->adicionarExercicio(ex);
                    std::cout << "Exercicio adicionado.\n";
                } else if (op2 == 3) {
                    if (fichas.empty()) { std::cout << "Nenhuma ficha.\n"; continue; }
                    for (const auto &f : fichas) f.exibirDetalhes();
                } else if (op2 == 0) break;
                else std::cout << "Opcao invalida.\n";
            }
        } else if (op == 3) {
            if (fichas.empty()) { std::cout << "Nao ha fichas.\n"; continue; }
            std::cout << "Fichas disponiveis:\n";
            for (const auto &f : fichas) std::cout << f.getId() << " - " << f.getNome() << "\n";
            std::cout << "Escolha ID da ficha realizada: ";
            int idFicha; std::cin >> idFicha;
            Ficha* ptrFicha = nullptr;
            for (auto &f : fichas) if (f.getId() == idFicha) { ptrFicha = &f; break; }
            if (!ptrFicha) { std::cout << "Ficha nao encontrada.\n"; continue; }
            Registro r;
            r.dataHora = agoraFormatado();
            r.idFicha = ptrFicha->getId();
            r.nomeFicha = ptrFicha->getNome();
            r.tempoTotal = ptrFicha->calcularTempoTotalMin();
            r.caloriasTotal = ptrFicha->calcularCaloriasTotal();
            historico.push_back(r);
            std::cout << "Treino registrado: Tempo=" << r.tempoTotal << " min, Calorias=" << r.caloriasTotal << "\n";
        } else if (op == 4) {
            if (historico.empty()) { std::cout << "Historico vazio.\n"; continue; }
            for (const auto &r : historico) {
                std::cout << r.dataHora << " | Ficha ID: " << r.idFicha << " | " << r.nomeFicha
                          << " | Tempo: " << r.tempoTotal << " | Cal: " << r.caloriasTotal << "\n";
            }
        } else if (op == 0) {
            std::cout << "Salvando e saindo...\n";
            break;
        } else {
            std::cout << "Opcao invalida.\n";
        }
    }
}