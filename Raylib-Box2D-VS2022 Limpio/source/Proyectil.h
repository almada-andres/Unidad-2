#pragma once
#include <box2d.h>
#include "raylib.h"

class Proyectil 
{
    private:
            b2Body* body;
            float radius;
            Color color;

    public:
            Proyectil(b2World& world, float x, float y, float r);
            void Lanzar(float fuerzaX, float fuerzaY);
            void Dibujar();
            b2Vec2 GetPosicion() const { return body->GetPosition(); }
};