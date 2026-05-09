#include "Proyectil.h"

Proyectil::Proyectil(b2World& world, float x, float y, float r) : radius(r) 
{
    // Color para el proyectil
    color = RED; 

    // Definicion del cuerpo
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);
    body = world.CreateBody(&bodyDef);

    // Forma circular
    b2CircleShape shape;
    shape.m_radius = r;

    // Propiedades fisicas
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.5f;  // Para que rebote un poco al caer

    body->CreateFixture(&fixtureDef);
}

void Proyectil::Lanzar(float fuerzaX, float fuerzaY) 
{
    // Aplica impulso lineal al centro del cuerpo
    body->ApplyLinearImpulseToCenter(b2Vec2(fuerzaX, fuerzaY), true);
}

void Proyectil::Dibujar() 
{
    b2Vec2 pos = body->GetPosition();
    DrawCircleV({ pos.x, pos.y }, radius, color);
    DrawCircleLines((int)pos.x, (int)pos.y, radius, MAROON);
}