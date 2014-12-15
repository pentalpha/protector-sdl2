#include <iostream>
#include <ctime>
#include <sstream>
#include <time.h>
using namespace std;
#include "gameLock.h"

gameLock::gameLock(string path)
{
    cPath = path;
    cMaxTempo = 1*60*60;
    setDate();
    cInicial = time(0);
    openFile();
}

gameLock::gameLock(string path, int num)
{
    cPath = path;
    cMaxTempo = num;
    setDate();
    cInicial = time(0);
    openFile();
}

void gameLock::openFile()
{
    string aux;
    ifstream file;
    file.open(cPath.c_str(), ifstream::in);
    if(file.fail())
    {
        cout << "Arquivo \"" << cPath << "\" nao encontrado." << endl;
    }

    char c = file.get();

    while (file.good()) {
        cText = cText + c;
        c = file.get();
    }

    file.close();

    int i;
    for(i = 0; i < cText.size(); i++)
    {
        if(cText[i] == ' ')
        {
			i++;
            break;
        }
        aux = aux + cText[i];
    }

    int j = 0;
    for( ; i < cText.size(); j++, i++)
    {
        cFileDate = cFileDate + cText[i];
    }

    if(cFileDate == cAtualDate)
    {
        cTempo = stringToNumber(aux);
    }
    else
    {
        cTempo = 0;
    }
}

bool gameLock::timeVerify()
{
    if(cTempo >= cMaxTempo && cAtualDate == cFileDate)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int gameLock::stringToNumber(string text)
{
    int Result;

    istringstream convert(text);
void timeUpdate();
    if ( !(convert >> Result) )
        Result = 0;
    return Result;
}

void gameLock::setTempo(int num)
{
    cMaxTempo = num;
}

void gameLock::setDecorrido(int num)
{
    cDecorrido = num;
}

bool gameLock::timeUpdate()
{
    long int tempo;
    tempo = time(0);
    cDecorrido = tempo - cInicial;

    if(cDecorrido + cTempo > cMaxTempo)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

long int gameLock::getMaxTempo()
{
    return cMaxTempo;
}

long int gameLock::getDecorrido()
{
    return cDecorrido;
}

long int gameLock::getInicial()
{
    return cInicial;
}

void gameLock::timeClose()
{
    ofstream ofs;
    ofs.open("source/auxfile");
	if (ofs.fail())
	{
		cout << "Falha ao criar o arquivo \"auxfile\"" << endl;
	}
    ofs << cDecorrido + cTempo << " " << cAtualDate;
    remove("source/file");
}

long int gameLock::getTempo()
{
    return cTempo;
}

void gameLock::setDate()
{
    /*time_t rawtime;
    struct tm timeinfo;

    char t1[9];

    time (&rawtime);
    localtime_s (&timeinfo, &rawtime);

    strftime (t1,9,"%d/%m/%y",&timeinfo);

    cAtualDate = t1;*/
    time_t rawtime;
    struct tm * timeinfo;

    char t1[9];

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    strftime (t1,9,"%d/%m/%y",timeinfo);

    cAtualDate = t1;
}
