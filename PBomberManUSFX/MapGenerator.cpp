#include "MapGenerator.h"

MapGenerator::MapGenerator()
{
	anchoPantalla = 0;
	altoPantalla = 0;
	renderer = nullptr;
}

MapGenerator::MapGenerator(SDL_Renderer* _renderer, int _anchoPantalla, int _altoPantalla, TilesGraph* _tilesGraph):
	anchoPantalla(_anchoPantalla),
	altoPantalla(_altoPantalla),
	renderer(_renderer),
	tilesGraph(_tilesGraph)
{
	
}

bool MapGenerator::crearObjetosJuego(string _path)
{
	// Crea un flujo de archivo
	fstream file;

	// Abrir el archivo
	file.open(_path.c_str(), ios::in);

	if (file.is_open() == false) {
		std::cout << "No se pudo abrir el archivo de mapa" << std::endl;
		return false;
	}

	string line;
	/*Texture* texturaBomba;
	texturaBomba = new Texture();*/
	Texture* texturaBomberman;
	texturaBomberman = new Texture();
	Texture* texturaBomberwoman;
	texturaBomberwoman = new Texture();
	Texture* texturaMuroMetal;
	texturaMuroMetal = new Texture();
	Texture* texturaMuroCeramica;
	texturaMuroCeramica = new Texture();
	Texture* texturaSueloCesped;
	texturaSueloCesped = new Texture();
	//creamos una nueva textura para el bomber nuevo
	Texture* texturaBomberman2;
	texturaBomberman2 = new Texture();

	Texture::renderer = renderer;
	//añadimos la ubicacion desde donde va a cargar la imagen
	/*texturaBomba->loadFromImage("resources/bomba.png");*/
	texturaBomberman->loadFromImage("resources/bomberman.jpg");
	texturaBomberwoman->loadFromImage("resources/bomberman.jpg");
	texturaBomberman2->loadFromImage("resources/bomberman.jpg");
	texturaMuroCeramica->loadFromImage("resources/muro_ceramica.jpg");
	texturaMuroMetal->loadFromImage("resources/muro_metal.jpg");
	texturaSueloCesped->loadFromImage("resources/suelo_cesped.jpg");
	
	int x = 0;
	int y = 0;
	
	int bombermanPosicionX = -1;
	int bombermanPosicionY = -1;
	int bomberwomanPosicionX = -1;
	int bomberwomanPosicionY = -1;
	int bomberman2PosicionX = -1;
	int bomberman2PosicionY = -1;

	while (getline(file, line)) {
		vector<char> chars(line.begin(), line.end());
		x = 0;

		for (int i = 0; i < chars.size(); i++) {
			if (chars[i] != ' ') {
				GameObject* objetoNuevo = nullptr;
				Tile* tileNuevo = tilesGraph->getTileEn(x, y);
				switch (chars[i]) {
				case '0':
					objetoNuevo = new SueloCesped(texturaSueloCesped, tileNuevo);
					if (x > bombermanPosicionX && bombermanPosicionX == -1) {
						bombermanPosicionX = x;
						bombermanPosicionY = y;
					}

					if (x > bomberwomanPosicionX || y > bomberwomanPosicionY) {
						bomberwomanPosicionX = x;
						bomberwomanPosicionY = y;
					}

					if (x > bomberman2PosicionX || y > bomberman2PosicionY) {
						bomberman2PosicionX = x;
						bomberman2PosicionY = y;
					}
					//pilaObjetosJuegoMurosMetal.Insertar((GameActor*)objetoNuevo);

					break;
				case '1':
					objetoNuevo = new MuroMetal(texturaMuroCeramica, tileNuevo);
					break;
				case '2':
					objetoNuevo = new MuroCeramica(texturaMuroMetal, tileNuevo);
					break;
					/*case 'B':
						objetoNuevo = new Bomberman(texturaBomberman, tileNuevo);
						break;*/
				}

				if (objetoNuevo != nullptr) {
					((GameActor*)objetoNuevo)->setPosicionX(x * 34);
					((GameActor*)objetoNuevo)->setPosicionY(y * 34);
					vectorObjectosJuego.push_back(objetoNuevo);
					x++;
				}
			}
		}
		y++;
	}

	
	
	GameObject* objetoBomberman = nullptr;
	Tile* tileNuevo = tilesGraph->getTileEn(bombermanPosicionX, bombermanPosicionY);
	objetoBomberman = new Bomberman(texturaBomberman, tileNuevo);
	if (objetoBomberman != nullptr) {
		((GameActor*)objetoBomberman)->setPosicionX(bombermanPosicionX * 34);
		((GameActor*)objetoBomberman)->setPosicionY(bombermanPosicionY * 34);
		vectorObjectosJuego.push_back(objetoBomberman);
	}
	/*int bombaPosicionX = -1;
	int bombaPosicionY = -1;*/


	/*GameObject* objetoBomba = nullptr;
	Tile* tileNuevo = tilesGraph->getTileEn(bombaPosicionX, bombaPosicionY);
	objetoBomba = new Bomba (texturaBomba, tileNuevo);
	if (objetoBomba != nullptr) {
		((GameActor*)objetoBomba)->setPosicionX(bombaPosicionX * 34);
		((GameActor*)objetoBomba)->setPosicionY(bombaPosicionY * 34);
		((GamePawn*)objetoBomba)->setBotomBomba(SDLK_b);
		vectorObjectosJuego.push_back(objetoBomba);
	}*/

	GameObject* objetoBomberwoman = nullptr;
	tileNuevo = tilesGraph->getTileEn(bomberwomanPosicionX, bomberwomanPosicionY);
	objetoBomberwoman = new Bomberman(texturaBomberwoman, tileNuevo);
	if (objetoBomberwoman != nullptr) {
		((GameActor*)objetoBomberwoman)->setPosicionX(bomberwomanPosicionX * 34);
		((GameActor*)objetoBomberwoman)->setPosicionY(bomberwomanPosicionY * 34);
		((GamePawn*)objetoBomberwoman)->setBotomBomba(SDLK_o);
		((GamePawn*)objetoBomberwoman)->setBotomArriba(SDLK_w);
		((GamePawn*)objetoBomberwoman)->setBotomAbajo(SDLK_s);
		((GamePawn*)objetoBomberwoman)->setBotomIzquierda(SDLK_a);
		((GamePawn*)objetoBomberwoman)->setBotomDerecha(SDLK_d);

		vectorObjectosJuego.push_back(objetoBomberwoman);
	}

	//nuevo objeto bomber con las asignaciones de los botones
	GameObject* objetoBomberman2 = nullptr;
	tileNuevo = tilesGraph->getTileEn(bomberman2PosicionX, bomberman2PosicionY);
	objetoBomberman2 = new Bomberman(texturaBomberman2, tileNuevo);
	if (objetoBomberman2 != nullptr) {
		((GameActor*)objetoBomberman2)->setPosicionX(bomberman2PosicionX * 34);
		((GameActor*)objetoBomberman2)->setPosicionY(bomberman2PosicionY * 34);
		((GamePawn*)objetoBomberman2)->setBotomBomba(SDLK_g);
		((GamePawn*)objetoBomberman2)->setBotomArriba(SDLK_i);
		((GamePawn*)objetoBomberman2)->setBotomAbajo(SDLK_k);
		((GamePawn*)objetoBomberman2)->setBotomIzquierda(SDLK_j);
		((GamePawn*)objetoBomberman2)->setBotomDerecha(SDLK_l);

		vectorObjectosJuego.push_back(objetoBomberman2);
	}





	return false;
}

void MapGenerator::transferirObjetosJuego(vector<GameObject*>& _vectorObjetosJuegoDestino)
{
	for (int i = 0; i < vectorObjectosJuego.size(); i++) {
		_vectorObjetosJuegoDestino.push_back(vectorObjectosJuego[i]);
	}
}
