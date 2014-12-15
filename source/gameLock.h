#ifndef GAMELOCK_H_INCLUDED
#define GAMELOCK_H_INCLUDED

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

//O programa funciona em tr�s passos:
//1) Quando aberto, ele verifica em que dia o jogo foi aberto da �ltima vez. Se for igual a hoje, ele verifica quantos segundos j� foram jogados. Se ainda tiver tempo sobrando (n�o atingindo o cMaxTempo), retorna 1.
//2) Durante o jogo, a cada segundo, ele vai adicionando o tempo na vari�vel cDecorrido.
//3) Quando fecha o jogo, ele pega o tempo do arquivo, e soma ao tempo do cDecorrido, e salva num arquivo "auxfile". Logo ap�s, tamb�m salva o dia atual.

class gameLock
{
    public:
        gameLock(string path); // Usa tempo padr�o de 1h, ou seja, pode jogar 1 hora por dia.
        gameLock(string path, int num); // Utiliza o segundo argumento para setar o tempo m�ximo de jogo por dia, em segundos.
        void openFile(); // Abre o txt especificado no construtor, e salva o conte�do dele na vari�vel cText, depois converte para int, e salva em cTempo;
        bool timeVerify(); // Executa o passo 1, e retorna um bool... return 1 significa que o jogo pode rodar.
        bool timeUpdate(); // Executa o passo 2.
        void timeClose(); // Executa o passo 3.
        int stringToNumber(string text); // Converte uma string para um N�mero do tipo INT.



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
        long int cMaxTempo; // Tempo m�ximo que voc� pode jogar.
        long int cInicial; // Tempo inicial em que o jogo foi aberto.
        long int cTempo; // Tempo jogado na sess�o anterior.
        long int cDecorrido; // Tempo em que o jogo est� rodando nesta sess�o.
        string cAtualDate; // Data atual.
        string cFileDate; // Data em que o jogo foi aberto da �ltima vez.
};

#endif // GAMELOCK_H_INCLUDED
