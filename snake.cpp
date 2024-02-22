#include <iostream>
#include <cstdlib>
#include <vector>

#include "raylib.h"
#include "raymath.h"

using namespace std;

#define SPEED 40

const int screenWidth = 1400;
const int screenHeight = 1400;

struct SnakePart {
    Vector2 position;
    Vector2 velocity;
};

vector<SnakePart> snake;

struct Food {
    Vector2 position;
} food;

bool collisions = false;

void updateTheSnake();

int main(void) {
    srand(time(NULL));

    SnakePart head;
    head.position = {0, 0};
    head.velocity = {SPEED, 0}; 
    snake.push_back(head);

    int x = (rand() % (screenWidth / SPEED)) * SPEED;
    int y = (rand() % (screenHeight / SPEED)) * SPEED;

    food.position = {static_cast<float>(x), static_cast<float>(y)};

    InitWindow(screenWidth, screenHeight, "snake");

    SetTargetFPS(15);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        for (size_t i = 0; i < snake.size(); ++i) {
                Rectangle bodyPart = {snake[i].position.x, snake[i].position.y, SPEED, SPEED};
                DrawRectangleRec(bodyPart, GREEN);
            }

        Rectangle theFood = {food.position.x, food.position.y, SPEED, SPEED};
        DrawRectangleRec(theFood, BLUE);

        updateTheSnake();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void updateTheSnake() {

    for (int i = snake.size() - 1; i > 0; --i) {
        snake[i] = snake[i - 1];
    }

    snake[0].position.x += snake[0].velocity.x;
    snake[0].position.y += snake[0].velocity.y;

    if (snake[0].position.x >= screenWidth) {
        snake[0].position.x = 0;
    } else if (snake[0].position.x < 0) {
        snake[0].position.x = screenWidth - SPEED;
    }

    if (snake[0].position.y >= screenHeight) {
        snake[0].position.y = 0;
    } else if (snake[0].position.y < 0) {
        snake[0].position.y = screenHeight - SPEED;
    }
   
    if (CheckCollisionRecs({snake[0].position.x, snake[0].position.y, SPEED, SPEED},
                            {food.position.x, food.position.y, SPEED, SPEED})) {

        snake.push_back({food.position, {0, 0}});

        int x = (rand() % (screenWidth / SPEED)) * SPEED;
        int y = (rand() % (screenHeight / SPEED)) * SPEED;
        food.position = {(float)x, (float)y};
    }

    if (IsKeyPressed(KEY_LEFT) && snake[0].velocity.x == 0) {
        snake[0].velocity = {-SPEED, 0};
    } else if (IsKeyPressed(KEY_RIGHT) && snake[0].velocity.x == 0) {
        snake[0].velocity = {SPEED, 0};
    } else if (IsKeyPressed(KEY_UP) && snake[0].velocity.y == 0) {
        snake[0].velocity = {0, -SPEED};
    } else if (IsKeyPressed(KEY_DOWN) && snake[0].velocity.y == 0) {
        snake[0].velocity = {0, SPEED};
    }
}