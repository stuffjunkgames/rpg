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
const std::string playerFile = "Player.bmp";

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

// class for players
class Player
{
  sf::Texture playerImg;
  sf::Sprite sprite;

public:
  Player();
  void loadSprite(sf::Texture *img);
  int loadImage(std::string file);
  void move(float x, float y);
  void draw(sf::RenderWindow *window);
};

Player::Player()
{
  // construct a player object
  if(loadImage(playerFile))
    {
      exit(1);
    }
  loadSprite(&playerImg);
}

int Player::loadImage(std::string file)
{
  if(!playerImg.loadFromFile(file))
    {
      std::cout << "Failed to load player texture from file\n";
      return 1;
    }
  
  return 0;
}

void Player::loadSprite(sf::Texture *img)
{
  sprite.setTexture(*img);
}

void Player::move(float x, float y)
{
  sprite.move(x, y);
}

void Player::draw(sf::RenderWindow *window)
{
  window->draw(sprite);
}

// main game loop
int main()
{
  sf::RenderWindow window(sf::VideoMode(GAME_WIDTH, GAME_HEIGHT), "RPG");
  sf::RectangleShape background = sf::RectangleShape(sf::Vector2<float>(GAME_WIDTH, GAME_HEIGHT));

  std::srand(std::time(0));
    
  Player player;
  float playerSpeed = 100;

  const int upKey = sf::Keyboard::W;
  const int leftKey = sf::Keyboard::A;
  const int downKey = sf::Keyboard::S;
  const int rightKey = sf::Keyboard::D;
  

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
      bool upPressed, downPressed, leftPressed, rightPressed;
      sf::Event event;
      while (window.pollEvent(event))
	{
	  if (event.type == sf::Event::Closed)
	    window.close();
	  if(event.type == sf::Event::KeyPressed)
	    {
	      if(event.key.code == upKey)
		upPressed = 1;
	      if(event.key.code == leftKey)
		leftPressed = 1;
	      if(event.key.code == rightKey)
		rightPressed = 1;
	      if(event.key.code == downKey)
		downPressed = 1;
	      if(event.key.code == sf::Keyboard::Escape)
		window.close();
	    }
	  if(event.type == sf::Event::KeyReleased)
	    {
	      if(event.key.code == upKey)
		upPressed = 0;
	      if(event.key.code == leftKey)
		leftPressed = 0;
	      if(event.key.code == rightKey)
		rightPressed = 0;
	      if(event.key.code == downKey)
		downPressed = 0;
	    }
	  
	}
      
      // movement      
      dt = clock.restart();
      t += dt;

      if(leftPressed)
	{
	  player.move(-dt.asSeconds()*playerSpeed, 0);
	}
      if(rightPressed)
	{
	  player.move(dt.asSeconds()*playerSpeed, 0);
	}
      if(upPressed)
	{
	  player.move(0, -dt.asSeconds()*playerSpeed);
	}
      if(downPressed)
	{
	  player.move(0, dt.asSeconds()*playerSpeed);
	}

      if(t.asMilliseconds() >= 100)
	{
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


	  player.draw(&window);
	  window.display();
	}




    }

  return 0;
}
