#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

class Character
{
private:
    float x, y;
    float dx, dy;
    float w, h;
    float currentframe;
    float moveSpeed;
    float gravitySpeed;
    float jumpSpeed;
    int coinCount;
    int distanceCount;
    bool life;
    bool onGround;
    std::string file;
    sf::Texture char_texture;
    sf::Sprite char_sprite;

public:
    Character(std::string F, float X, float Y, float W, float H);
    bool getLife();
    void setLife(bool L);
    float getXchar();
    float getYchar();
    float getWchar();
    float getHchar();
    int getCoinCount();
    int getDistanceCount();
    void calcDistance();
    void setCoinCount(int value);
    sf::Sprite &getCharSprite();
    void moveCharacter(float time, int nof);
    void Collision(sf::Sprite block_sprite, int id);
    ~Character();
};

#endif // CHARACTER_H_INCLUDED
