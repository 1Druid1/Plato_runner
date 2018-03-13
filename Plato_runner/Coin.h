#ifndef COIN_H_INCLUDED
#define COIN_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

class Coin
{
private:
    float x, y;
    float w, h;
    float currentframe;
    std::string file;
    sf::Texture coin_texture;
    sf::Sprite coin_sprite;
public:
    Coin(std::string F, float X, float Y, float W, float H);
    float getXcoin();
    float getYcoin();
    float getWcoin();
    float getHcoin();
    sf::Sprite &getCoinSprite();
    void animateCoin(float time, int nof);
    bool collectCoin(sf::Sprite char_sprite);
    ~Coin();
};

#endif // COIN_H_INCLUDED
