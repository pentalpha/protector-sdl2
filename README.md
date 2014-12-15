protector-sdl2
==============

Protector: Defenders of The Realm, a fantasy tower defense game on SDL2. This project has been succeeded by "Protector".

==============

These instructions were written on Ubuntu environment 14:04 "Trusty Tahr" but can (probably) be used in other distributions.

First of all it is necessary to have SDL2 running on your computer.
Install the following packages with "sudo apt-get install" to have all the libraries: (is advisable to make an "apt-get update" before all)

- build-essential
- libsdl2-dev
- libsdl2-gfx-dev
- libsdl2-image-dev
- libsdl2-mixer-dev
- libsdl2-net-dev
- libsdl2-ttf-dev

Now all files "*.h" from the SDL2 are in the /usr/include/SDL2. The program's classes shall go look for headers of SDL2 not in this folder, but on the top folder, the "include". Then you must move or copy all the files in /usr/include/SDL2 to /usr/include (or just to the top folder to it in the directory tree if their headers were installed elsewhere).

The next step is to compile. We will use the g ++ compiler, that on the time of this test was at version 4.8.2.
All the build command is in the "build" file in this directory, then simply run the command:

./build

This will create a executable called "towerDefense". Remember that for the game to work, the towerDefense executable must be in the same directory as the "source/" directory.

Have fun :)

==============

Estas instruções foram escritas no ambiente Ubuntu 14.04 "Trusty Tahr", mas podem (provavelmente) ser usadas em outras distribuições.


Antes de tudo é necessario ter o SDL2 em funcionamento no seu computador. 
Instale os seguintes pacotes com o "sudo apt-get install" para ter todas as bibliotecas:(é recomendavel fazer um "apt-get update" antes disso tudo)



- build-essential

- libsdl2-dev

- libsdl2-gfx-dev

- libsdl2-image-dev

- libsdl2-mixer-dev

- libsdl2-net-dev

- libsdl2-ttf-dev



Agora todos os arquivos "*.h" do SDL2 estão na pasta /usr/include/SDL2. As classes do programa iram procurar pelos headers do SDL2 não nesta pasta, mas na pasta superior, a "include". 
Então você deve mover ou copiar todos os arquivos da pasta /usr/include/SDL2 para /usr/include (ou simplesmente para a pasta superior a ela na arvore de diretorios, caso seus headers tenham sido instalados em outro lugar).



O proximo passo é a compilação. Será usado o compilador g++, que neste teste estava na versão 4.8.2. 
Todo o comando de compilação está no arquivo build neste diretorio, então basta executar o comando:

./build


Isto irá criar um executavel chamado "towerDefense". Lembre-se que para o jogo funcionar, o executavel towerDefense deve estar no mesmo diretorio que o diretorio source/

Divirta-se :)