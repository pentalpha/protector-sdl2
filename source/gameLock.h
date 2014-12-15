#ifndef GAMELOCK_H_INCLUDED
#define GAMELOCK_H_INCLUDED

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

//O programa funciona em três passos:
//1) Quando aberto, ele verifica em que dia o jogo foi aberto da última vez. Se for igual a hoje, ele verifica quantos segundos já foram jogados. Se ainda tiver tempo sobrando (não atingindo o cMaxTempo), retorna 1.
//2) Durante o jogo, a cada segundo, ele vai adicionando o tempo na variável cDecorrido.
//3) Quando fecha o jogo, ele pega o tempo do arquivo, e soma ao tempo do cDecorrido, e salva num arquivo "auxfile". Logo após, também salva o dia atual.

class gameLock
{
    public:
        gameLock(string path); // Usa tempo padrão de 1h, ou seja, pode jogar 1 hora por dia.
        gameLock(string path, int num); // Utiliza o segundo argumento para setar o tempo máximo de jogo por dia, em segundos.
        void openFile(); // Abre o txt especificado no construtor, e salva o conteúdo dele na variável cText, depois converte para int, e salva em cTempo;
        bool timeVerify(); // Executa o passo 1, e retorna um bool... return 1 significa que o jogo pode rodar.
        bool timeUpdate(); // Executa o passo 2.
        void timeClose(); // Executa o passo 3.
        int stringToNumber(string text); // Converte uma string para um Número do tipo INT.



        //sets e gets.
        void setTempo(int num);
        void setDecorrido(int num);
        void setDate();

        long int getMaxTempo();
        long int getDecorrido();
        long int getInicial();
        long int getTempo();

    private:
        string cText; // Texto do arquivo aberto em string.
        string cPath; // Caminho do arquivo especificado no construtor.
        long int cMaxTempo; // Tempo máximo que você pode jogar.
        long int cInicial; // Tempo inicial em que o jogo foi aberto.
        long int cTempo; // Tempo jogado na sessão anterior.
        long int cDecorrido; // Tempo em que o jogo está rodando nesta sessão.
        string cAtualDate; // Data atual.
        string cFileDate; // Data em que o jogo foi aberto da última vez.
};

#endif // GAMELOCK_H_INCLUDED
