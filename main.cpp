#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <iostream>

#define GAME_TOP 0
#define GAME_LEFT 0
#define GAME_WIDTH 1024
#define GAME_HEIGHT 768
#define GAME_RIGHT GAME_LEFT+GAME_WIDTH
#define GAME_BOTTOM GAME_TOP+GAME_HEIGHT

#define BLOCK_SIZE 20

const int WORLD_WIDTH = 100;
const int WORLD_HEIGHT = 50;
const std::string grassFile = "Grass.bmp";

//class for world tiles
class Tile
{
public:
    Tile();
    void loadSprite(sf::Texture *img);
    static int loadImages(void);

    static sf::Texture grassImg;
    sf::Sprite sprite;
};

sf::Texture Tile::grassImg = sf::Texture();

// Tile function definitions
Tile::Tile(void)
{
    // construct a tile
}

void Tile::loadSprite(sf::Texture *img)
{
    this->sprite.setTexture(*img);
}

int Tile::loadImages(void)
{
    if(!Tile::grassImg.loadFromFile(grassFile))
    {
        std::cout << "Failed to load grass from file\n";
        return 1;
    }

    return 0;
}

// main game loop
int main()
{
    sf::RenderWindow window(sf::VideoMode(GAME_WIDTH, GAME_HEIGHT), "RPG");
    sf::RectangleShape background = sf::RectangleShape(sf::Vector2<float>(GAME_WIDTH, GAME_HEIGHT));

    std::srand(std::time(0));
    
    sf::RectangleShape player; 
    player.setSize(sf::Vector2f(BLOCK_SIZE,BLOCK_SIZE));
    player.setFillColor(sf::Color::Blue);



    sf::Vector2<int> moveVector;
    sf::Time dt;
    sf::Time t;
    sf::Clock clock;

    if(Tile::loadImages())
    {
        return 1;
    }

    Tile ground[WORLD_WIDTH][WORLD_HEIGHT];
    for(int i = 0; i < WORLD_WIDTH; i++)
    {
        for(int j = 0; j < WORLD_HEIGHT; j++)
        {
            ground[i][j].loadSprite(&Tile::grassImg);
            ground[i][j].sprite.move(BLOCK_SIZE*i, BLOCK_SIZE*j);
        }
    }


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // movement
        dt = clock.restart();
        t += dt;
        if(t.asMilliseconds() >= 100){
            t = sf::Time::Zero;

            // draw
            window.clear();
            for(int i = 0; i < WORLD_WIDTH; i++)
            {
                for(int j = 0; j < WORLD_HEIGHT; j++)
                {
                    window.draw(ground[i][j].sprite);
                }
            }


            window.draw(player);
            window.display();
        }




    }

    return 0;
}
