#include<bits/stdc++.h>
#include <windows.h>
#include<conio.h>
using namespace std;

const int WIDTH = 40;
const int HEIGHT = 20;
const char BODY = '@';
const char APPLE = 'o'; // Ký tự đại diện cho trái táo
const int REFRESH_RATE = 100;

struct Point
{
    int x;
    int y;
};

vector<Point> snake = {
    Point{WIDTH / 2 + 2, HEIGHT / 2},
    Point{WIDTH / 2 + 1, HEIGHT / 2},
    Point{WIDTH / 2, HEIGHT / 2},
    Point{WIDTH / 2 - 1, HEIGHT / 2},
    Point{WIDTH / 2 - 2, HEIGHT / 2}};

Point apple; // Vị trí của trái táo

void gotoxy(int x, int y)
{
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void drawSnakePart(Point p)
{
    gotoxy(p.x, p.y);
    cout << BODY;
}

void drawSnake()
{
    for (size_t i = 0; i < snake.size(); i++)
        drawSnakePart(snake[i]);
}

void drawApple()
{
    gotoxy(apple.x, apple.y);
    cout << APPLE;
}

void generateApple()
{
    // Sinh ngẫu nhiên vị trí cho trái táo
    apple.x = rand() % (WIDTH - 2) + 1;
    apple.y = rand() % (HEIGHT - 2) + 1;
}

enum class Direction
{
    up,
    right,
    down,
    left
};

Direction direction = Direction::right;

void move()
{
    for (size_t i = snake.size() - 1; i > 0; i--)
        snake[i] = snake[i - 1];

    if (direction == Direction::up)
        snake[0].y -= 1;
    else if (direction == Direction::down)
        snake[0].y += 1;
    else if (direction == Direction::left)
        snake[0].x -= 1;
    else if (direction == Direction::right)
        snake[0].x += 1;
}

void drawBox()
{
    for (size_t i = 0; i < WIDTH; i++)
        cout << '=';

    gotoxy(0, HEIGHT);
    for (size_t i = 0; i < WIDTH; i++)
        cout << '=';

    for (size_t i = 1; i < HEIGHT; i++)
    {
        gotoxy(0, i);
        cout << '|';
    }

    for (size_t i = 1; i < HEIGHT; i++)
    {
        gotoxy(WIDTH, i);
        cout << '|';
    }
}

bool isHitWall()
{
    return snake[0].x == 0 || snake[0].y == 0 || snake[0].x == WIDTH || snake[0].y == HEIGHT;
}

bool isBiteItself()
{
    Point head = snake[0];
    for (size_t i = 1; i < snake.size(); i++)
        if (head.x == snake[i].x && head.y == snake[i].y)
            return true;
    return false;
}

int main()
{
    // Tắt hiển thị con trỏ màn hình
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);

    srand(time(NULL)); // Khởi tạo seed cho hàm sinh số ngẫu nhiên

    // Sinh trái táo ban đầu
    generateApple();

    while (true)
    {
        if (_kbhit())
        {
            char ch = _getch();
            ch = tolower(ch);
            if (ch == 'a' && direction != Direction::right)
                direction = Direction::left;
            else if (ch == 'w' && direction != Direction::down)
                direction = Direction::up;
            else if (ch == 's' && direction != Direction::up)
                direction = Direction::down;
            else if (ch == 'd' && direction != Direction::left)
                direction = Direction::right;
            else if (ch == 'q') // Quit game
                break;
        }

        move();

        // Nếu đầu của con rắn chạm vào trái táo
        if (snake[0].x == apple.x && snake[0].y == apple.y)
        {
            // Tăng chiều dài của con rắn
            snake.push_back(snake.back());
            // Sinh ra trái táo mới
            generateApple();
        }

        if (isBiteItself() || isHitWall())
            break;

        drawBox();
        drawApple();
        drawSnake();

        Sleep(REFRESH_RATE);
        system("cls");
    }

    // Hiển thị lại con trỏ màn hình khi kết thúc game
    info.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &info);

    cout << "Game over!" << endl;

    return 0;
}
