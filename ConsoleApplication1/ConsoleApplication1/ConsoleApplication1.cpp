#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

int dir = 2, num = 1;

bool game = true;

struct Snake {
    int x, y;
} s[600];

struct Apple {
    int x, y;
} f;

void Tick() {
    for (int i = num; i > 0; i--) {
        s[i].x = s[i - 1].x;
        s[i].y = s[i - 1].y;
    }

    if (dir == 0)
        s[0].y += 1;
    if (dir == 1)
        s[0].x -= 1;
    if (dir == 2)
        s[0].x += 1;
    if (dir == 3)
        s[0].y -= 1;


    if ((s[0].x == f.x) && (s[0].y == f.y)) {
        num++;

        f.x = rand();
        f.y = rand();
    }

    for (int i = 1; i < num; i++)
        if ((s[0].x == s[i].x) && (s[0].y == s[i].y))
            game = false;
}

int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(100, 100), "Snake!");

    Texture sn;
    sn.loadFromFile("C:/Users/User/Desktop/dot.png");
    Sprite snake(sn);

    Texture ap;
    ap.loadFromFile("C:/Users/User/Desktop/apple.png");
    Sprite apple(ap);

    Texture go;
    go.loadFromFile("C:/Users/User/Desktop/game-over-801800.png");
    Sprite gameover(go);
    gameover.setPosition(0, 175);

    f.x = 10;
    f.y = 10;

    Clock clock;
    float timer = 0, delay = 0.1;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left))
            dir = 1;
        if (Keyboard::isKeyPressed(Keyboard::Right))
            dir = 2;
        if (Keyboard::isKeyPressed(Keyboard::Up))
            dir = 3;
        if (Keyboard::isKeyPressed(Keyboard::Down))
            dir = 0;

        if (timer > delay && game) {
            timer = 0;
            Tick();
        }

        window.clear();


        for (int i = 0; i < num; i++) {
            if (i != 0)
                snake.setTextureRect(IntRect(0, 0, 16, 16));
            else
                snake.setTextureRect(IntRect(dir * 16, 16, 16, 16));

            if (!game && i == 1)
                snake.setTextureRect(IntRect(dir * 16, 16 * 2, 16, 16));

            snake.setPosition(s[i].x * 16, s[i].y * 16);
            window.draw(snake);
        }

        apple.setPosition(f.x * 16, f.y * 16);
        window.draw(apple);

        if (!game)
            window.draw(gameover);

        window.display();
    }

    return 0;
}