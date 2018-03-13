#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include "Trap.h"

Trap::Trap(std::string F, float X, float Y, float W, float H)
{
    x=X; y=Y;
    w=W; h=H;
    currentframe=0;
    file=F;
    trap_texture.loadFromFile(file);
    trap_sprite.setTexture(trap_texture);
    trap_sprite.setPosition(x, y);
    trap_sprite.setTextureRect(sf::IntRect(0, 0, w, h));
}

float Trap::getXtrap()
{
    return x;
}

float Trap::getYtrap()
{
    return y;
}

float Trap::getWtrap()
{
    return w;
}

float Trap::getHtrap()
{
    return h;
}

sf::Sprite &Trap::getTrapSprite()
{
    return trap_sprite;
}

void Trap::animateTrap(float time, int nof)
{
    currentframe+=0.02*time;
    if (currentframe>nof) {currentframe-=nof;}
    trap_sprite.setTextureRect(sf::IntRect(w*int(currentframe)+1, 0, w, h));
}

bool Trap::isCollision(sf::Sprite char_sprite)
{
    if (char_sprite.getPosition().x>=trap_sprite.getPosition().x &&
        char_sprite.getPosition().x<=trap_sprite.getPosition().x+trap_sprite.getTextureRect().width &&
        char_sprite.getPosition().y>=trap_sprite.getPosition().y &&
        char_sprite.getPosition().y<=trap_sprite.getPosition().y+trap_sprite.getTextureRect().height) {return true;}

    if (char_sprite.getPosition().x+char_sprite.getTextureRect().width>=trap_sprite.getPosition().x &&
        char_sprite.getPosition().x+char_sprite.getTextureRect().width<=trap_sprite.getPosition().x+trap_sprite.getTextureRect().width &&
        char_sprite.getPosition().y+char_sprite.getTextureRect().height>=trap_sprite.getPosition().y &&
        char_sprite.getPosition().y+char_sprite.getTextureRect().height<=trap_sprite.getPosition().y+trap_sprite.getTextureRect().height) {return true;}

    return false;
}

Trap::~Trap(){}


