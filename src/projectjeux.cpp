#include <vector>
#include <stack>
#include <cstdlib>
#include "raylib.h"
#include "projectjeux.h"

// تعريف المتاهة بناءً على المستوى
Maze::Maze(DifficultyLevel level) {
    switch (level) {
        case EASY:
            grid = std::vector<std::vector<int>>(HEIGHT_EASY, std::vector<int>(WIDTH_EASY, 1));
            break;
        case MEDIUM:
            grid = std::vector<std::vector<int>>(HEIGHT_MEDIUM, std::vector<int>(WIDTH_MEDIUM, 1));
            break;
        case HARD:
            grid = std::vector<std::vector<int>>(HEIGHT_HARD, std::vector<int>(WIDTH_HARD, 1));
            break;
    }
}

bool Maze::isInside(int x, int y) const {
    return (x >= 0 && x < grid[0].size() && y >= 0 && y < grid.size());
}

std::vector<std::pair<int, int>> Maze::getNeighbors(int x, int y) {
    std::vector<std::pair<int, int>> neighbors;
    for (int i = 0; i < 4; i++) {
        int nx = x + 2 * dx[i];
        int ny = y + 2 * dy[i];
        if (isInside(nx, ny) && grid[ny][nx] == 1) {
            neighbors.push_back({nx, ny});
        }
    }
    return neighbors;
}

void Maze::generate() {
    int startX = rand() % (grid[0].size() / 2) * 2;
    int startY = rand() % (grid.size() / 2) * 2;
    grid[startY][startX] = 0; // ابدأ في نقطة عشوائية
    backtrackStack.push({startX, startY});

    while (!backtrackStack.empty()) {
        auto cell = backtrackStack.top();
        backtrackStack.pop();
        int x = cell.first;
        int y = cell.second;

        auto neighbors = getNeighbors(x, y);
        if (!neighbors.empty()) {
            backtrackStack.push(cell);

            auto neighbor = neighbors[rand() % neighbors.size()];
            int nx = neighbor.first;
            int ny = neighbor.second;

            grid[(y + ny) / 2][(x + nx) / 2] = 0; // إزالة الجدار
            grid[ny][nx] = 0; // فتح الجار

            backtrackStack.push(neighbor);
        }
    }
}

void Maze::draw() {
    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid[0].size(); x++) {
            if (grid[y][x] == 1) {
                DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, BLACK); // رسم الجدران
            } else {
                DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, WHITE); // رسم المسارات
            }
        }
    }
}

bool Maze::isPath(int x, int y) const {
    return isInside(x, y) && grid[y][x] == 0; // تحقق مما إذا كانت الخلية مفتوحة
}

int Maze::getWidth() const {
    return grid[0].size();
}

int Maze::getHeight() const {
    return grid.size();
}

Player::Player(int startX, int startY) : x(startX), y(startY) {}

void Player::move(int dx, int dy, const Maze &maze) {
    int newX = x + dx;
    int newY = y + dy;
    if (maze.isPath(newX, newY)) {
        x = newX;
        y = newY;
    }
}

void Player::draw() {
    DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, RED); // اللاعب باللون الأحمر
}

Cheese::Cheese(int startX, int startY) : x(startX), y(startY) {}

void Cheese::draw() {
    DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, YELLOW); // رسم الجبنة باللون الأصفر
}
