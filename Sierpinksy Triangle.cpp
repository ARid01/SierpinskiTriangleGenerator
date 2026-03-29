#include "SFML/Graphics.hpp"
#include <vector>

using namespace std;

const int winWid = 800, winHig = 800;
const int pointDiff = 35;

int main()
{
    sf::RenderWindow window(sf::VideoMode(winWid, winHig), "Chaos Sierpinski Triangle");
    window.setFramerateLimit(60);

    vector<sf::Vector2f> points = {
        sf::Vector2f(winWid / 4, 3 * winHig / 4),
        sf::Vector2f(3 * winWid / 4, 3 * winHig / 4),
        sf::Vector2f(winWid / 2, winHig / 4)
    };

    //Get first random point within triangle
    float triWid = winWid / 2;
    sf::Vector2f C = { points[2].x - points[0].x, points[2].y - points[0].y };
    float r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    
    // if over the diagonal, then flip r1 & r2
    if (r1 + r2 > 1) {
        r1 = (1 - r1);
        r2 = (1 - r2);
    }
    //Create transformed coordinate
    float x = triWid * r2 + C.x * r1 + points[0].x;
    float y = C.y * r1 + points[0].y;

    points.push_back(sf::Vector2f( x, y ));
    int totalPoints = 4;

    sf::CircleShape dot(1);
    
    sf::Text text;
    sf::Font font;
    font.loadFromFile("Minecraft.ttf");
    text.setFont(font);
    text.setCharacterSize(25);
    text.setPosition(sf::Vector2f(25, 25));
    string stat;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    for (int i = 0; i < pointDiff; i++) {
                        sf::Vector2f randVert = points[rand() % 3];
                        sf::Vector2f lastPoint = points[points.size() - 1];
                        sf::Vector2f midPoint = { (randVert.x + lastPoint.x) / 2, (randVert.y + lastPoint.y) / 2 };
                        points.push_back(midPoint);
                    }
                    totalPoints += pointDiff;
                }
            }
        }

        window.clear();
        for (sf::Vector2f& p : points) {
            dot.setPosition(p);
            window.draw(dot);
        }
        stat = "Sierpinski Triangle using Rand Points\nTotal Points: " + to_string(totalPoints);
        text.setString(stat);
        window.draw(text);
        window.display();
    }

    return 0;
}