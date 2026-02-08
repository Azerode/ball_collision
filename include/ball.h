#ifndef OBJECT_H
#define OBJECT_H
#include "raylib.h"

#define MAX_OBJECT 100

typedef struct vector {
    float x;
    float y;
} vector;

typedef struct object {
    Vector2 position;
    Vector2 velocity;
    float mass;
    float r;
    Color color; 
} ball;

extern ball objects[MAX_OBJECT];

float distance(Vector2 *v_a, Vector2 *v_b);

void applyVelocity(ball *obj);

void calcElacticCollision(ball *obj1, ball *obj2);

#endif