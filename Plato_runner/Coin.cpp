#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include "Coin.h"

Coin::Coin(std::string F, float X, float Y, float W, float H)
{
    x=X; y=Y;
    w=W; h=H;
    currentframe=0;
    file=F;
    coin_texture.loadFromFile(file);
    coin_sprite.setTexture(coin_texture);
    coin_sprite.setPosition(x, y);
    coin_sprite.setTextureRect(sf::IntRect(0, 0, w, h));
}

float Coin::getXcoin()
{
    return x;
}

float Coin::getYcoin()
{
    return y;
}

float Coin::getWcoin()
{
    return w;
}

float Coin::getHcoin()
{
    return h;
}

sf::Sprite &Coin::getCoinSprite()
{
    return coin_sprite;
}

void Coin::animateCoin(float time, int nof)
{
    currentframe+=0.02*time;
    if (currentframe>nof) {currentframe-=nof;}
    coin_sprite.setTextureRect(sf::IntRect(w*int(currentframe), 0, w, h));
}

bool Coin::collectCoin(sf::Sprite char_sprite)
{
    if (char_sprite.getPosition().x+char_sprite.getTextureRect().width/2>=coin_sprite.getPosition().x-coin_sprite.getTextureRect().width/2 &&
        char_sprite.getPosition().x<=coin_sprite.getPosition().x+coin_sprite.getTextureRect().width-coin_sprite.getTextureRect().width/2 &&
        char_sprite.getPosition().y+char_sprite.getTextureRect().height/2>=coin_sprite.getPosition().y-coin_sprite.getTextureRect().height/2 &&
        char_sprite.getPosition().y<=coin_sprite.getPosition().y+coin_sprite.getTextureRect().height-coin_sprite.getTextureRect().height/2) {return true;}
    return false;
}

Coin::~Coin(){}



