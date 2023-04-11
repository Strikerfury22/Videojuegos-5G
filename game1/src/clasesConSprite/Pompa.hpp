#pragma once
#include "Sprite.hpp"
#include <string>
#include <cmath>
#include "Robot.cpp"
#include <iostream> //DEBUG

// Aquí debajo se pondrán las constantes para especificar 
// las animaciones de enemigos atrapados en pompas
const int ROBOT = 5;
const int FANTASMA = 8;

/* Tipo de dato que representa las burbujas que disparan Bub y Bob.
 * A continuación, la lista de animaciones que se contienen en su variable
 * <sprite> junto al número de fotogramas que tiene:
 * 0 -> Disparo -> 7
 * 1 -> Verde	-> 3
 * 2 -> Naranja -> 3
 * 3 -> Rojo	-> 3
 * 4 -> Explota -> 10
 * 5,6,7 -> Pompas verde-naranja-rojo (3-3-3) de un enemigo (así con todos)
 */
class Pompa : public Sprite {
	
	int contadorFrames = -1;
	const int maxFrames = 10;

	//Índices de color
	const int VERDE = 0;
	const int NARANJA = 1;
	const int ROJO = 2;

	const int NUM_FOTOGRAMAS = 3;

	const int widthAnimation = 16;
	const int heightAnimation = 16;

	const int fDisparo = 7;
	const int fExplota = 10;
	const int fAtrapado = 3;

	//Razón a la que se va restando la vida a la pompa
	const int VELOCIDAD_MUERTE = 1;
	
	//Modo oscilacion
	bool oscilando = false;
	bool abajo = true;
	uint8_t contador = 0;

	//Abstracción de generación de enemigo al explotar
	sh_Enemigo extraeEnemigo(bool matalo);

public:
	//Indice de animación básicos
	static const int DISPARO = 0;
	static const int VACIA = 1;
	static const int EXPLOTA = 4;

	static uint32_t ID_GLOBAL;
	int ID = -1;
	static void init();

	//Vida de la pompa (asociado a naranja-rojo)
	int vidaMaxima = 0;
	int tVida = 0;
	bool matame = false;

	//Indica si inicia cadena de explosiones
	bool cadena = false;


	//Enemigo contenido
	sh_Enemigo enemigoContenido = NULL;
	int modulo = 0;

	//Desplazamiento
	float velocidadDesplazamiento = 0;
	int sentidoLateral = 1; //1-> Sin sentido, 2 -> hacia la izquierda, 3->hacia la derecha
	//Relacionado con el modo disparo
	float distanciaRecorrida = 0;
	float distanciaDisparo = 0;
	int disparada = 2;

	//Control de animaciones
	int animacionActiva;
	int indiceAnimacion = 0;
	int indiceExtra = 0;
	int cuentaFrames = 0;
	int velocidadFrames = 0;


	Pompa() = default;
	Pompa(Texture2D spriteSheet, const Rectangle origen, float velDisparo, float distanciaDisparo, bool esDisparada, int tiempoVida);
	
	bool operator==(const Pompa& p);

	void Inicializador(Texture2D spriteSheet, const Rectangle origen, float velDisparo, float distanciaDisparo, bool esDisparada, int tiempoVida);

	sh_Enemigo Actualizar(Rectangle pJ1, bool cayendoJ1, int sentidoJ1, bool muriendoJ1, int& j1DebeRebotar, float j1VelLateral);

	void Dibujar();
};