#pragma once
#include "Sprite.hpp"
#include "Suelo.cpp"
#include "mapa.cpp"
#include <iostream>

class Enemigo : public Sprite {
public:
    int tipo = -1; // 1->Robot 2-> Agua NO USAR 3->Fantasma 4-> Monsta 5-> Rosa
    bool borrame = false; //Eliminarlo de la lista
    bool muerto = false; //Iniciar animacion de muerte
    bool muertePorAgua = false;
    
    bool saltando = false;
    bool finSaltando = false;
    bool enElAire = false;
    bool cayendo = false;
    bool golpeado = false;
    bool enfadado = true;
    float velocidadLateral = 0;
    float velocidadSalto = 0;
    float saltoRecorrido = 0;
    float distanciaSaltoMax = 0;

    Enemigo() = default; //Debe llamarsse a Inicializador

    Enemigo(std::string rutaTextura, float tamano, float saltoMax, float velSalto, float velLateral) {
        Inicializador(rutaTextura, tamano, saltoMax, velSalto, velLateral);
    };

    void virtual Actualizar(Rectangle playerPosition) = 0;
    void virtual Dibujar() = 0;

    void Inicializador(std::string rutaTextura, float tamano, float saltoMax, float velSalto, float velLateral)
    {
        sprite = LoadTexture(rutaTextura.c_str());// Texture loading
        velocidadLateral = velLateral;
        velocidadSalto = velSalto;
        distanciaSaltoMax = saltoMax;

        //frameWidth = sprite.width;
        //frameHeight = sprite.height;

        frameWidth = 16;
        frameHeight = 16;


        // Source rectangle (part of the texture to use for drawing)
        srcRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };
        this->tamano = tamano;

        // Destination rectangle (screen rectangle where drawing part of texture)
        destRec = { GetScreenWidth() / 2.0f - 50, GetScreenHeight() / 2.0f - 20, (float)frameWidth * tamano, (float)frameHeight * tamano }; //Dos primeros, ubicacion. Dos ultimos, dimensiones
        //destRec = { 0,0, (float)frameWidth * tamano, (float)frameHeight * tamano }; //Dos primeros, ubicacion. Dos ultimos, dimensiones

        // Origin of the texture (rotation/scale point), it's relative to destination rectangle size
        origin = { (float)frameWidth * tamano / 2, (float)frameHeight * tamano / 2 }; //En principio no lo necesitamos
    }

    ~Enemigo() {
        UnloadTexture(sprite);
    };

    void Unload() {
        UnloadTexture(sprite);
    };

    void virtual compruebaSuelo() = 0;

    void virtual compruebaColision(Plataforma& s, int enemyNum) = 0;

    void virtual compruebaPared(const Columnas& s) = 0;

    //void Dibujar() {
    //    DrawTexturePro(sprite, srcRec, destRec, origin, 0.0f, WHITE);
    //}
};

typedef std::shared_ptr<Enemigo> sh_Enemigo;