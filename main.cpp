#include "include/raylib.h"
#include "include/raymath.h"
#include <cmath>

#define RAYGUI_IMPLEMENTATION
#include "include/raygui.h"

#define WIDTH 800
#define HIGHT 600

#define G 0.1


typedef struct {
    Vector2 start;
    float L;        
    float theta;   // in radians
    float theta_dot;
    float theta_dotdot;
    float m;        
} Point;

void update(Point* p1,Point* p2){

    p1->theta_dotdot = (-G*(2*p1->m + p2->m)*sinf(p1->theta) - p2->m * G * sinf(p1->theta - 2* p2->theta) -2 *sinf(p1->theta - p2->theta)*p2->m *(p2->theta_dot * p2->theta_dot * p2->L + p1->theta_dot * p1->theta_dot * p1->L * cosf(p1->theta - p2->theta) ));
    p1->theta_dotdot = p1->theta_dotdot / (p1->L * (2 * p1->m + p2->m - p2->m * cosf(2*p1->theta - 2*p2->theta)));

    p2->theta_dotdot = (2*sinf(p1->theta - p2->theta) * (p1->theta_dot * p1->theta_dot * p1->L * (p1->m + p2->m) + (G *(p1->m + p2->m) * cosf(p1->theta)) + (p2->theta_dot * p2->theta_dot * p2->L * p2->m * cosf(p1->theta - p2->theta))));
    p2->theta_dotdot = p2->theta_dotdot / (p2->L * (2 * p1->m + p2->m - (p2->m * cosf(2 * p1->theta - 2 * p2->theta))));
    
    p1->theta_dot += p1->theta_dotdot;
    p1->theta += p1->theta_dot;

    p2->theta_dot += p2->theta_dotdot;
    p2->theta += p2->theta_dot;
}

int main(void) {
    InitWindow(WIDTH, HIGHT, "pendulum");
    SetTargetFPS(120);

    
    Vector2 pivot = { (float)WIDTH / 2.0f, 200 };

    Point p1 = {pivot,150.0f, -PI/2,0,0, 20.0f}; 
    Point p2 = {(Vector2){pivot.x + (p1.L * sinf(p1.theta)),pivot.y + (p1.L * cosf(p1.theta))},100.0f, PI,0,0, 20.0f};;
    
    while(!WindowShouldClose()){
        
        update(&p1, &p2);
        float bobX = pivot.x + (p1.L * sinf(p1.theta));
        float bobY = pivot.y + (p1.L * cosf(p1.theta));

        
        
        float patX = bobX +(p2.L * sinf(p2.theta));
        float patY = bobY + (p2.L * cosf(p2.theta));
        
        BeginDrawing();
            ClearBackground(BLACK);
            
            DrawLineV(pivot, (Vector2){bobX, bobY}, WHITE);
            DrawLineV((Vector2){bobX, bobY}, (Vector2){patX, patY}, WHITE);
            
            DrawCircle(bobX, bobY, p1.m, RED);
            DrawCircle(patX, patY, p2.m, RED);
            
        EndDrawing();
    }

    CloseWindow();
    return 0;
}