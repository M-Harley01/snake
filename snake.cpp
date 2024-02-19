#include <iostream>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "raylib.h"
#include "raymath.h"

using namespace std;

#define SPEED 40

const int screenWidth = 1000;
const int screenHeight = 1000;

struct snakeHead {
    Vector2 position;
    Vector2 velocity;
} snakeHead;

struct snakeBody {
    Vector2 position;
};

vector<snakeBody> snBody;

struct food {
    Vector2 position;
} food;

bool collisions = false;

void updateTheSnake();

int main(void) {
    srand(time(NULL));

    snakeHead.position = (Vector2){0, 0};
    snakeHead.velocity = (Vector2){0, 0};

    int x = (rand() % 25) * 40;
    int y = (rand() % 25) * 40;

    food.position = (Vector2){static_cast<float>(x), static_cast<float>(y)};

    InitWindow(screenWidth, screenHeight, "snake");

    SetTargetFPS(15);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        for (size_t i = 0; i < snBody.size(); ++i) {
        Rectangle bodyPart = {snBody[i + 1].position.x, snBody[i +1].position.y, 40, 40};
        DrawRectangleRec(bodyPart, GREEN);
}

        Rectangle theSnake = {snakeHead.position.x, snakeHead.position.y, 40, 40};
        DrawRectangleRec(theSnake, RED);

        Rectangle theFood = {food.position.x, food.position.y, 40, 40};
        DrawRectangleRec(theFood, BLUE);

        updateTheSnake();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void updateTheSnake() {
    snakeHead.position.x += snakeHead.velocity.x;
    snakeHead.position.y += snakeHead.velocity.y;

    if (snakeHead.position.x >= screenWidth) {
        snakeHead.position.x = 0;
    } else if (snakeHead.position.x < 0) {
        snakeHead.position.x = screenWidth - 40;
    }

    if (snakeHead.position.y >= screenHeight) {
        snakeHead.position.y = 0;
    } else if (snakeHead.position.y < 0) {
        snakeHead.position.y = screenHeight - 40;
    }

    for (int i = snBody.size() - 1; i > 0; --i) {
        snBody[i] = snBody[i - 1];
    }

    if (!snBody.empty()) {
        snBody[0] = {snakeHead.position.x, snakeHead.position.y};
    }

    if (CheckCollisionRecs({snakeHead.position.x, snakeHead.position.y, 40, 40},{food.position.x, food.position.y, 40, 40})){

        DrawText("collision", 0,0,40,BLACK);
        snBody.push_back({snakeHead.position.x, snakeHead.position.y});

        int x = (rand() % 25) * 40;
        int y = (rand() % 25) * 40;
        food.position = {(float)x, (float)y};
    }

    if (IsKeyPressed(KEY_LEFT) && snakeHead.velocity.x == 0) {
        snakeHead.velocity = {-SPEED, 0};
    } else if (IsKeyPressed(KEY_RIGHT) && snakeHead.velocity.x == 0) {
        snakeHead.velocity = {SPEED, 0};
    } else if (IsKeyPressed(KEY_UP) && snakeHead.velocity.y == 0) {
        snakeHead.velocity = {0, -SPEED};
    } else if (IsKeyPressed(KEY_DOWN) && snakeHead.velocity.y == 0) {
        snakeHead.velocity = {0, SPEED};
    }
}
