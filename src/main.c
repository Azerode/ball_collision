#include <stdio.h>
#include <time.h>
#include <math.h>
#include "../include/ball.h"

#define WIDTH 800
#define HEIGHT 450


void generate_balls(){

    SetRandomSeed(time(NULL));

    float r;
    int red, blue, green;
    for (int i = 0; i < MAX_OBJECT; i++){
        r = GetRandomValue(5, 8);
        red = GetRandomValue(0,255);
        blue = GetRandomValue(0,255);
        green = GetRandomValue(0,255);

        objects[i].position.x = GetRandomValue(0, WIDTH - r);
        objects[i].position.y = GetRandomValue(0, HEIGHT - r);
        objects[i].velocity.x = GetRandomValue(-2, 2);
        objects[i].velocity.y = GetRandomValue(-2, 2);
        objects[i].mass = GetRandomValue(1, 10);
        objects[i].r = r;
        objects[i].color = (Color) {red,green,blue,255};
    }
}

void DrawObject(){
    for(size_t i = 0; i < MAX_OBJECT; i++){
        ball *obj = &objects[i];
        DrawCircle(obj->position.x, obj->position.y, obj->r, obj->color);
    }
}

void apply_movement(){
    for(size_t i = 0; i < MAX_OBJECT; i++){
        ball *obj = &objects[i];
        applyVelocity(obj);
    } 
}

void check_edge(ball *obj){
    if (obj->position.x < obj->r || obj->position.x > WIDTH - obj->r) {
        obj->velocity.x *= -1;
    }

    if (obj->position.y < obj->r || obj->position.y > HEIGHT - obj->r){
        obj->velocity.y *= -1;
    }
}

void ApplyCollision(){
    for (int i = 0 ; i < MAX_OBJECT; i++){
        ball *obj_a = &objects[i];
        check_edge(obj_a);
        for(int j = i + 1; j < MAX_OBJECT; j++){
            ball *obj_b = &objects[j];

            if (CheckCollisionCircles(obj_a->position, obj_a->r,obj_b->position,obj_b->r))
            {
                calcElacticCollision(obj_a,obj_b);
            }
        }
    }
}

int main(){

    generate_balls();

    InitWindow(WIDTH, HEIGHT, "Collision Simulator Application");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        ApplyCollision();
        apply_movement();
        BeginDrawing();
            DrawFPS(10,10);
            ClearBackground(BLACK);
            DrawObject();
        EndDrawing();        
    }

    CloseWindow();

    return 0;
}
