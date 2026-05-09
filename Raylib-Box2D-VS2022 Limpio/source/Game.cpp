#include "Game.h"

Game::Game() 
{
    InitWindow(screenWidth, screenHeight, "MAVI II - Unidad 2");
    SetTargetFPS(60);

    // Mundo físico
    b2Vec2 gravity(0.0f, 9.8f);
    world = new b2World(gravity);

    InitPhysics();

    // Crear proyectil
    miProyectil = new Proyectil(*world, 100.0f, screenHeight - 100.0f, 15.0f);
    lanzado = false;
}

Game::~Game() 
{
    delete miProyectil;
    delete world;
    CloseWindow();
}

void Game::InitPhysics() 
{
    // -----------------------------
    // Suelo estático
    // -----------------------------
    b2BodyDef groundDef;
    groundDef.type = b2_staticBody;
    groundDef.position.Set(screenWidth / 2.0f, screenHeight - 40.0f);
    b2Body* groundBody = world->CreateBody(&groundDef);

    b2PolygonShape groundShape;
    groundShape.SetAsBox(screenWidth / 2.0f, 20.0f);
    groundBody->CreateFixture(&groundShape, 0.0f);
}

void Game::Update() 
{
    // Input para aplicar impulso al presionar ESPACIO
    if (IsKeyPressed(KEY_SPACE) && !lanzado) 
    {
        // Componente X positiva (derecha), Y negativa (hacia arriba)
        miProyectil->Lanzar(25000.0f, -50000.0f);
        lanzado = true;
    }

    // Avanzar simulación
    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 8;
    int32 positionIterations = 3;
    world->Step(timeStep, velocityIterations, positionIterations);
}

void Game::Draw() 
{
    BeginDrawing();
    ClearBackground(fondo);

    // Suelo visual
    DrawRectangle(0, screenHeight - 60, screenWidth, 40, sueloColor);

    // Dibujar proyectil
    miProyectil->Dibujar();

    // Panel superior
    DrawRectangle(90, 40, 820, 60, Fade(BLACK, 0.2f));
    DrawText("Unidad 2 - Modelos y Algoritmos para Videojuegos II", 150, 55, 25, RAYWHITE);

    if (!lanzado) 
    {
        DrawText("Presiona ESPACIO para lanzar el proyectil", 320, 300, 20, DARKGRAY);
    }

    EndDrawing();
}

void Game::Run() 
{
    while (!WindowShouldClose()) 
    {
        Update();
        Draw();
    }
}