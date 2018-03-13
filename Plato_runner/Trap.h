#ifndef TRAP_H_INCLUDED
#define TRAP_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

class Trap
{
private:
    float x, y;
    float w, h;
    float currentframe;
    std::string file;
    sf::Texture trap_texture;
    sf::Sprite trap_sprite;
public:
    Trap(std::string F, float X, float Y, float W, float H);
    float getXtrap();
    float getYtrap();
    float getWtrap();
    float getHtrap();
    sf::Sprite &getTrapSprite();
    void animateTrap(float time, int nof);
    bool isCollision(sf::Sprite char_sprite);
    ~Trap();
};

#endif // TRAP_H_INCLUDED
