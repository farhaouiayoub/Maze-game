#include <iostream>
#include "raylib.h"
#include "projectjeux.h"

int main() {
    InitWindow(800, 600, "Maze Game");

    DifficultyLevel level = EASY; // مستوى افتراضي
    // عرض قائمة الاختيار
    while (level == EASY) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Select Difficulty Level:", 280, 100, 20, BLACK);
        DrawText("1. Easy", 320, 150, 20, BLACK);
        DrawText("2. Medium", 320, 200, 20, BLACK);
        DrawText("3. Hard", 320, 250, 20, BLACK);
        DrawText("Press 1, 2 or 3 to select", 250, 300, 20, BLACK);
        EndDrawing();

        if (IsKeyPressed(KEY_ONE)) level = EASY;
        if (IsKeyPressed(KEY_TWO)) level = MEDIUM;
        if (IsKeyPressed(KEY_THREE)) level = HARD;
    }

    Maze maze(level);
    maze.generate();

    Player player(1, 1); // موقع اللاعب الابتدائي
    Cheese cheese(rand() % maze.getWidth(), rand() % maze.getHeight()); // وضع الجبنة في مكان عشوائي

    SetTargetFPS(60); // تحديد عدد الإطارات في الثانية

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_UP)) player.move(0, -1, maze);
        if (IsKeyPressed(KEY_DOWN)) player.move(0, 1, maze);
        if (IsKeyPressed(KEY_LEFT)) player.move(-1, 0, maze);
        if (IsKeyPressed(KEY_RIGHT)) player.move(1, 0, maze);

        // تحقق من الوصول إلى الجبنة
        if (player.x == cheese.x && player.y == cheese.y) {
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Congratulations! You collected the cheese!", 150, 300, 20, GREEN);
            DrawText("Press R to restart or Q to quit", 150, 340, 20, DARKGRAY);
            EndDrawing();

            // الانتظار حتى يقوم اللاعب بإعادة تشغيل اللعبة أو الخروج
            while (true) {
                if (IsKeyPressed(KEY_R)) {
                    level = EASY; // إعادة تعيين المستوى
                    break; // الخروج من الحلقة
                }
                if (IsKeyPressed(KEY_Q)) {
                    CloseWindow(); // إغلاق النافذة عند الخروج
                    return 0;
                }
            }

            continue;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        maze.draw();   // رسم المتاهة
        player.draw(); // رسم اللاعب
        cheese.draw(); // رسم الجبنة
        EndDrawing();
    }

    CloseWindow(); // إغلاق النافذة عند الانتهاء

    return 0;
}
