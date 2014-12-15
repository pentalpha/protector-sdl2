//e esse aqui é o arquivo das cenas. Qualquer nova cena tem que ser adicionada aqui.
//tudo o que você precisa alterar na nova é o nome da classe e o retorno do "getStateID()"


class Scene
{
public:
	//processa toda a logica do jogo
	virtual void update(Game *pointerToGame) = 0;
	//desenha o mundo do jogo, a grande maioria da parte grafica está aqui
	virtual void render(Game *pointerToGame) = 0;
	//lida com a entrada de dados para a cena atual
	virtual void handleInput(Game *pointerToGame, SDL_Event event) = 0;
	//inicia a cena de acordo com a cena anterior referenciada em "previous"
	virtual void onEnter(Game *pointerToGame, GameStates previous) = 0;
	//passa para a proxima cena com base na cena passada em "next"
	virtual void onExit(Game *pointerToGame, GameStates next) = 0;
	//retorna o gamestate atual
	virtual GameStates getStateID() const = 0;
protected:
};

class MainScene :
	public Scene
{
public:
	void update(Game *pointerToGame);
	void render(Game *pointerToGame);
	void handleInput(Game *pointerToGame, SDL_Event event);

	void onEnter(Game *pointerToGame, GameStates previous);
	void onExit(Game *pointerToGame, GameStates next);

	GameStates getStateID() const { return GameStates::MAIN; }
};

class PauseScene :
	public Scene
{
public:
	void update(Game *pointerToGame);
	void render(Game *pointerToGame);
	void handleInput(Game *pointerToGame, SDL_Event event);

	void onEnter(Game *pointerToGame, GameStates previous);
	void onExit(Game *pointerToGame, GameStates next);

	GameStates getStateID() const { return GameStates::PAUSE; }
};

class Stage :
	public Scene
{
public:
	Map map;
	Sprite statusBox, wavesBox;
	Button skipButton;
	Sprite background;
	int health;
	int gold;
	int nTowers;
	Tower *towers;
	WaveManager waveManager;
	int nRoutes;
	List<SDL_Point> *routes;
	List<Enemy> enemys;
	List<Projectile> projectiles;
	List<Animation> animations;
	SDL_Point base;
	int maxWaves;

	Stage();
	void init(SDL_Renderer* renderer, std::string mapLocation);

	void update(Game *pointerToGame);
	void render(Game *pointerToGame);
	void handleInput(Game *pointerToGame, SDL_Event event);

	void onEnter(Game *pointerToGame, GameStates previous);
	void onExit(Game *pointerToGame, GameStates next);

	void makeCollisions();

	GameStates getStateID() const { return GameStates::STAGE; }
	void setNextMap(int newMap);
	
	int nextStage;
};

class GameOverScene :
	public Scene
{
public:
	void update(Game *pointerToGame);
	void render(Game *pointerToGame);
	void handleInput(Game *pointerToGame, SDL_Event event);

	void onEnter(Game *pointerToGame, GameStates previous);
	void onExit(Game *pointerToGame, GameStates next);

	GameStates getStateID() const { return GameStates::GAMEOVER; }
};

class VictoryScene :
	public Scene
{
public:
	void update(Game *pointerToGame);
	void render(Game *pointerToGame);
	void handleInput(Game *pointerToGame, SDL_Event event);

	void onEnter(Game *pointerToGame, GameStates previous);
	void onExit(Game *pointerToGame, GameStates next);

	GameStates getStateID() const { return GameStates::VICTORY; }
};

class OutOfTimeScene : 
	public Scene
{
public:
	void update(Game *pointerToGame);
	void render(Game *pointerToGame);
	void handleInput(Game *pointerToGame, SDL_Event event);

	void onEnter(Game *pointerToGame, GameStates previous);
	void onExit(Game *pointerToGame, GameStates next);

	GameStates getStateID() const { return GameStates::TIMEOUT; }
};