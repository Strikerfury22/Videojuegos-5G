#include "raylib.h"
#include "clasesConSprite/Bub.cpp"

const int TARGET_FPS = 60;

//cambiar nombre de "not_main" a "main" para que el depurador entre aqu?.
//Se mueve con A y S, y se salta con el espacio
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    const int numEspadas = 50;

    InitWindow(screenWidth, screenHeight, "Practica 1.2 - espada giratoria");
    SetWindowMinSize(200, 200);
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    InitAudioDevice();

    Sound select = LoadSound("resources/select2cut.wav");
    SetSoundVolume(select, 0.5f);
    Music fun = LoadMusicStream("resources/feFun.ogg");
    //SetMusicVolume(fun, 0.2f);
    //PlayMusicStream(fun);
    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

    Bub bub = Bub(2.0f, 30.0f, 1.0f, 1.0f,TARGET_FPS);
    Suelo suelo = Suelo("resources/Suelo.png");

    SetTargetFPS(TARGET_FPS);
    // Main game loop
    std::cout << "Inicia bucle" << std::endl;
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        bub.Actualizar();
        bub.compruebaColision(suelo);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);//RAYWHITE);

        suelo.Dibujar();
        bub.Dibujar();

        //DrawText("(c) Scarfy sprite by Eiden Marsal", screenWidth - 200, screenHeight - 20, 10, GRAY);
        std::string x_extremo = "Suelo sup y " + std::to_string(suelo.destRec.y - suelo.destRec.height / 2);
        std::string valores = "Megaman inf y= " + std::to_string(bub.destRec.y + bub.destRec.height / 2) + " Valor H = " + std::to_string(bub.frameHeight);
        DrawText(valores.c_str(), screenWidth - 600, screenHeight - 30, 20, GRAY);
        DrawText(x_extremo.c_str(), screenWidth - 600, screenHeight - 50, 20, GRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    bub.Unload();
    suelo.UnloadAsteroide();
    UnloadMusicStream(fun);

    CloseAudioDevice();
    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}