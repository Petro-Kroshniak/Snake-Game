#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace sf;

int N = 30, M = 20;
int size = 32;
int w = size * N;
int h = size * M;

int dir, num = 4;
int score,highscore=0;

struct Snake
{
    int x, y;
}  s[100];

struct Fruit
{
    int x, y;
} f;

void Tick()
{
    
    for (int i = num; i > 0; --i)
    {
        s[i].x = s[i - 1].x; s[i].y = s[i - 1].y;
    }

    if (dir == 0) s[0].y += 1;
    if (dir == 1) s[0].x -= 1;
    if (dir == 2) s[0].x += 1;
    if (dir == 3) s[0].y -= 1;

    if ((s[0].x == f.x) && (s[0].y == f.y))
    {
        num++; f.x = (rand() % (N - 1)) + 1;
        f.y = (rand() % (M - 1)) + 1;
        
    }

    if (s[0].x > N) s[0].x = 0;  if (s[0].x < 0) s[0].x = N;
    if (s[0].y > M) s[0].y = 1;  if (s[0].y < 1) s[0].y = M;

    for (int i = 1; i < num; i++)
        if (s[0].x == s[i].x && s[0].y == s[i].y)  num = 2;
}

int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(w, h), "Snake Game!");

    Font font;
    font.loadFromFile("9041.ttf");
    Text text("", font, 20);
    text.setFillColor(Color::Red);
    Text text1("", font, 20);
    text1.setFillColor(Color::Red);

    Texture t1, t2, t3, t4;
    t1.loadFromFile("fon.png");
    t2.loadFromFile("snake.png");
    t3.loadFromFile("apple.png");
    t4.loadFromFile("white.png");

    Sprite sprite1(t1);
    Sprite sprite2(t2);
    Sprite sprite3(t3);
    Sprite sprite4(t4);

    Clock clock;
    float timer = 0, delay = 0.2;

    f.x = 10;
    f.y = 10;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) dir = 1;
        if (Keyboard::isKeyPressed(Keyboard::Right)) dir = 2;
        if (Keyboard::isKeyPressed(Keyboard::Up)) dir = 3;
        if (Keyboard::isKeyPressed(Keyboard::Down)) dir = 0;

        if (timer > delay) { timer = 0; Tick(); }

        ////// draw  ///////
        window.clear();

        for (int i = 0; i < N; i++)
        {
            sprite4.setPosition(i * size, 0); window.draw(sprite4);
        }
            

        for (int i = 0; i < N; i++)
            for (int j = 1; j < M; j++)
            {
                sprite1.setPosition(i * size, j * size);  window.draw(sprite1);
            }

        
        for (int i = 0; i < num; i++)
        {
            std::ifstream readfile;
            readfile.open("highscore.txt");
            if (readfile.is_open())
            {
                while (!readfile.eof())
                {
                    readfile >> highscore;
                }
            }
            readfile.close();
            std::ofstream writefile("highscore.txt");
            if (writefile.is_open())
            {
                if (score > highscore)
                {
                    highscore = score;
                }
                writefile << highscore;
            }
            writefile.close();

            score = num * 10;
            std::ostringstream playerscorestring;
            playerscorestring<<score;
            text.setString("Score:"+playerscorestring.str());
            text.setPosition(0, 0);
            window.draw(text);
            std::ostringstream playerhighscore;
            playerhighscore << highscore;
            text1.setString("Highscore:" + playerhighscore.str());
            text1.setPosition(800, 0);
            window.draw(text1);

            sprite2.setPosition(s[i].x * size, s[i].y * size);  window.draw(sprite2);
        }

        sprite3.setPosition(f.x * size, f.y * size);  window.draw(sprite3);

        window.display();
    }

    return 0;
}