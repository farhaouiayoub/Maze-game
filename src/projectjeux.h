#ifndef PROJECTJEUX_H
#define PROJECTJEUX_H

#include <vector>
#include <stack>
#include <utility> // for std::pair

// تعريفات المتغيرات العامة
const int WIDTH_EASY = 10;         // عرض المتاهة السهلة
const int HEIGHT_EASY = 10;        // ارتفاع المتاهة السهلة
const int WIDTH_MEDIUM = 15;       // عرض المتاهة المتوسطة
const int HEIGHT_MEDIUM = 15;      // ارتفاع المتاهة المتوسطة
const int WIDTH_HARD = 20;          // عرض المتاهة الصعبة
const int HEIGHT_HARD = 20;         // ارتفاع المتاهة الصعبة
const int CELL_SIZE = 25;           // حجم كل خلية

enum DifficultyLevel { EASY, MEDIUM, HARD };

class Maze {
private:
    std::vector<std::vector<int>> grid;
    std::stack<std::pair<int, int>> backtrackStack;

    // اتجاهات الحركة: (up, down, left, right)
    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {-1, 1, 0, 0};

    bool isInside(int x, int y) const;
    std::vector<std::pair<int, int>> getNeighbors(int x, int y);

public:
    Maze(DifficultyLevel level);
    void generate();
    void draw();
    bool isPath(int x, int y) const;
    int getWidth() const;  // دالة للحصول على عرض المتاهة
    int getHeight() const; // دالة للحصول على ارتفاع المتاهة
};

class Player {
public:
    int x, y;
    Player(int startX, int startY);
    void move(int dx, int dy, const Maze &maze);
    void draw();
};

class Cheese {
public:
    int x, y;
    Cheese(int startX, int startY);
    void draw();
};

#endif // PROJECTJEUX_H
