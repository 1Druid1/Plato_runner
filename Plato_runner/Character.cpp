#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include "Character.h"

static float j_y=0;
static int length_c=0;
static bool keylock=false;
static const int noid=2;
static bool under[noid];

Character::Character(std::string F, float X, float Y, float W, float H)
{
    dx=0; dy=0;
    currentframe=0;
    coinCount=0;
    distanceCount=0;
    moveSpeed=0.1;
    gravitySpeed=0.15;
    jumpSpeed=-0.13;
    life=true;
    onGround=true;
    file=F;
    w=W; h=H;
    x=X; y=Y;
    char_texture.loadFromFile(file);
    char_sprite.setTexture(char_texture);
    char_sprite.setPosition(x, y);
    char_sprite.setTextureRect(sf::IntRect(0, 0, w, h));
}


bool Character::getLife()
{
    return life;
}


void Character::setLife(bool L)
{
    life=L;
}


float Character::getXchar()
{
    return x;
}


float Character::getYchar()
{
    return y;
}

float Character::getWchar()
{
    return w;
}

float Character::getHchar()
{
    return h;
}

int Character::getCoinCount()
{
    return coinCount;
}

int Character::getDistanceCount()
{
    return distanceCount;
}

void Character::calcDistance()
{
    if (life==true)
    {
        length_c++;
        if (length_c==80)
        {
            distanceCount++;
            length_c=0;
        }
    }
}

void Character::setCoinCount(int value)
{
    coinCount=value;
}


sf::Sprite &Character::getCharSprite()
{
    return char_sprite;
}


void Character::Collision(sf::Sprite block_sprite, int id)
{
    for (int i=0; i<noid; i++)
    {
        if (char_sprite.getPosition().y+char_sprite.getTextureRect().height>block_sprite.getPosition().y+block_sprite.getTextureRect().height && id==i+1) {under[i]=true;}
        if (char_sprite.getPosition().y<block_sprite.getPosition().y-block_sprite.getTextureRect().height && id==i+1) {under[i]=false;}
    }

    if (char_sprite.getPosition().x+char_sprite.getTextureRect().width/2>block_sprite.getPosition().x-block_sprite.getTextureRect().width/2 &&
        char_sprite.getPosition().x<block_sprite.getPosition().x-block_sprite.getTextureRect().width/2+block_sprite.getTextureRect().width)
        {
            for (int i=0; i<noid; i++)
            {
                if (char_sprite.getPosition().y>block_sprite.getPosition().y-block_sprite.getTextureRect().height-5 && id==i+1 && under[i]==false)
                {
                    onGround=true; j_y=char_sprite.getPosition().y;
                }

                if (char_sprite.getPosition().y<block_sprite.getPosition().y+block_sprite.getTextureRect().height && id==i+1 && under[i]==true)
                {
                    onGround=false; keylock=false;
                }
            }
        }

    if (char_sprite.getPosition().x>block_sprite.getPosition().x+block_sprite.getTextureRect().width &&
        char_sprite.getPosition().y>block_sprite.getPosition().y-block_sprite.getTextureRect().height-5 &&
        char_sprite.getPosition().y<block_sprite.getPosition().y+block_sprite.getTextureRect().height &&
        keylock==false)
        {
            onGround=false;
        }

}


void Character::moveCharacter(float time, int nof)
{
  if (life==true)
  {
    currentframe+=0.006*time;
    if (currentframe>nof) {currentframe-=nof;}
    char_sprite.setTextureRect(sf::IntRect(w*int(currentframe), 0, w, h));
    char_sprite.move(moveSpeed*time, 0);

    if (onGround==false)
    {
        char_sprite.setTextureRect(sf::IntRect(0+nof*w, 0, w, h));
        char_sprite.move(0, gravitySpeed*time);
    }
    if (keylock==true && onGround==true)
    {
        char_sprite.setTextureRect(sf::IntRect(0+nof*w, 0, w, h));
        char_sprite.move(0, jumpSpeed*time);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && onGround==true)
    {
        keylock=true;
    }

    if (char_sprite.getPosition().y<j_y-250) {onGround=false; keylock=false;}
    if (char_sprite.getPosition().y>=600) {onGround=true; j_y=char_sprite.getPosition().y;}
  }

}

Character::~Character(){}
















