<!-- by Pitagoras, NOTA: Neste repositorio fica APENAS O CODIGO. Não inicie um repositorio git direto no diretorio base do seu projeto, pois isso irá incluir arquivos de projeto aqui. Crie uma pasta chamada source/ dentro dele e inicie o repositorio lá dentro. Dessa forma, por exemplo, o main.cpp vai ficar em <pasta do projeto>/source/main.cpp. Mesmo assim, para imagens por exemplo, você terá que usar o endereço do arquivo a partir do diretorio raiz do projeto, por exemplo. Para carregar o arquivo "/source/img/mapa.png" dentro do "/source/game.cpp" não basta dizer "/img/mapa.png", mas sim o caminho completo "/source/img/mapa.png" -->

PARA-FAZER:

Alguns balanceamentos e melhoramentos devem ainda ser implementados nos mapas;
Interface precisa ser melhorada, exibindo mais informações em tempo real;
O "Game Lock" ainda não foi ativado;

----------------------------------------------------------------

SOBRE AS CLASSES:

main.cpp:
	Apenas inicializa o SDL2, cria uma instancia de Game e roda esta instancia.

GAME:
	Classe main, gerencia todos os recursos do jogo.

Scene:
	Cena do jogo. Possui o proprio render(), update() e etc...

Button:
	Botão sem função propria, apenas retorna se pode estar sendo clicado ou não.

Sprite:
	É o game object padrão. Outras classes podem herdar dela e dar override nos metodos virtuais update e draw não implementados.

Animation:

Enemy:

List:

Map:

WaveManager:

Wave:


----------------------------------------------------------------

INSTRUÇÕES DE INSTALAÇÃO:

Instalem o SDL2 juntamente com a extensão SDL_Image em seus computadores, não importa muito a plataforma que desejarem...

Download:

http://www.libsdl.org/download-2.0.php

A instalação não tem segredo:

- Extraia o arquivo baixado para algum lugar.

- Inclua o diretorio include do SDL2 nos diretorios include do seu projeto (varia de IDE para IDE).
(para compatibilidade dos codigos é essencial que os .h estejam DIRETAMENTE dentro do include, não em subdiretorios).

- Inclua o diretorio lib do SDL2 nos diretorios lib do seu projeto (varia de IDE para IDE).

- Em bibliotecas adicionais, inclua
<libmingw32.lib, pode ser necessario, se for no MinGW>
SDL2.lib
SDL2main.lib
(nessa ordem)

- Como é uma biblioteca dinamica, você deve colocar o arquivo "SDL2.dll" na mesma pasta onde ficará o seu futuro executavel.


-----------------------------------------------------------------------------


Para baixar o SDL_Image: 

http://sdl.beuc.net/sdl.wiki/SDL_image

- Copie os arquivos no diretorio include do SDL_Image para o diretorio include do SDL2

- Copie os arquivos do diretorio lib do SDL_Image para o diretorio lib do SDL2

- Inclua o SDL2_image.lib nas bibliotecas adicionais, agora a sequencia deve ficar assim:

SDL2.lib
SDL2_image.lib
SDL2main.lib

- Dentro da pasta lib do SDL_Image tem um monte de dlls, você também precisa copiar todas para o diretorio do executavel, se quiser que ele funcione.

Isso dá mais trabalho, mas é necessario para que o SDL2 seja capaz de suportar arquivos diferentes do velho .BMP...

-------------------------------------------------------------------

Tenham certeza de ter o git instalado, ele já vem com o "GIT BASH", então não se preocupem de ter que usar o cmd do Windows.