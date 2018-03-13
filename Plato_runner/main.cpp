#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <sstream>
#include "Character.h"
#include "Coin.h"
#include "Trap.h"

using namespace std;
using namespace sf;

#define numofcoin   30
#define nob3_1      15
#define nob3_2      10


bool START_GAME()
{
    srand(time(0));
    Clock clock;

    RenderWindow window(VideoMode(1500, 700), "Sprite");
    Font coin_font, distance_font;
    coin_font.loadFromFile("fonts/scorefont.ttf");
    distance_font.loadFromFile("fonts/scorefont.ttf");
    Text coin_text("", coin_font, 25);
    Text distance_text("", distance_font, 25);
    coin_text.setColor(Color::Yellow);
    coin_text.setStyle(Text::Bold);
    distance_text.setColor(Color::Cyan);
    distance_text.setStyle(Text::Bold);

    Character player("image/combat1.png", 500, 600, 50, 42);
    player.getCharSprite().setScale(1.3, 1.3);

    Trap trap("image/trap.png", -100, -100, 80, 80);
    float r_x_trap=0, r_y_trap=0;

    float r_x_coin[numofcoin], r_y_coin[numofcoin];
    Coin *coin[numofcoin];
    for (int i=0; i<numofcoin; i++)
    {
        coin[i]=new Coin("image/coin.png", 0, 0, 30, 30);
    }

    Texture blockTexure3_1[nob3_1], blockTexure3_2[nob3_2];
    for (int i=0; i<nob3_1; i++) {blockTexure3_1[i].loadFromFile("image/block3.png");}
    for (int i=0; i<nob3_2; i++) {blockTexure3_2[i].loadFromFile("image/block3.png");}

    Sprite blockSprite3_1[nob3_1], blockSprite3_2[nob3_2];
    for (int i=0; i<nob3_1; i++)
    {
        blockSprite3_1[i].setTexture(blockTexure3_1[i]);
        blockSprite3_1[i].setTextureRect(IntRect(0, 0, 72, 28));
    }
    for (int i=0; i<nob3_2; i++)
    {
        blockSprite3_2[i].setTexture(blockTexure3_2[i]);
        blockSprite3_2[i].setTextureRect(IntRect(0, 0, 72, 28));
    }

    float r_n_x3_1[nob3_1]; float r_n_x3_2[nob3_2];
    float r_n_y3_1[nob3_1]; float r_n_y3_2[nob3_2];
    float s_rand_x3_1=(player.getCharSprite().getPosition().x+1000); float s_rand_x3_2=(player.getCharSprite().getPosition().x+1500);
    float s_rand_y3_1=250+rand()%300; float s_rand_y3_2=200+rand()%350;
    int rand_pack3_1=1+rand()%nob3_1;
    int rand_pack3_2=1+rand()%nob3_2;

    Texture t1, t2;
    t1.loadFromFile("image/gamebackground1.png");
    t2.loadFromFile("image/gamebackground2.png");
    Sprite s1, s2;
    s1.setTexture(t1);
    s2.setTexture(t2);
    s1.setPosition(0, 50);
    s2.setPosition(2000, 50);

    View view;
    view.reset(FloatRect(0, 0, 1500, 700));

    while (window.isOpen())
    {
        float time=clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time=time/500;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type==Event::Closed) {window.close(); return false;}
        }
        if (Keyboard::isKeyPressed(Keyboard::R)) {return true;}
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {return false;}

        view.setCenter(player.getCharSprite().getPosition().x+300, 400);
        window.setView(view);

        ostringstream CoinsString, DistanceString;
        CoinsString <<player.getCoinCount();
        DistanceString <<player.getDistanceCount();
        coin_text.setPosition(view.getCenter().x+400, view.getCenter().y-330);
        coin_text.setString("Coins: "+CoinsString.str());
        distance_text.setPosition(view.getCenter().x-600, view.getCenter().y-330);
        distance_text.setString("Distance: "+DistanceString.str());

        player.moveCharacter(time, 11);
        player.calcDistance();
        for (int i=0; i<rand_pack3_1; i++) {player.Collision(blockSprite3_1[i], 1);}
        for (int i=0; i<rand_pack3_2; i++) {player.Collision(blockSprite3_2[i], 2);}

        for (int i=0; i<numofcoin; i++) {coin[i]->animateCoin(time, 16);}
        for (int i=0; i<numofcoin; i++) {coin[i]->collectCoin(player.getCharSprite());}

        trap.animateTrap(time, 16);

        window.clear();

        window.draw(s1);
        window.draw(s2);
        if (s1.getPosition().x<player.getCharSprite().getPosition().x-2500) {s1.setPosition(s2.getPosition().x+2000, 50);}
        if (s2.getPosition().x<player.getCharSprite().getPosition().x-2500) {s2.setPosition(s1.getPosition().x+2000, 50);}

        window.draw(player.getCharSprite());

        for (int i=0; i<numofcoin; i++) {window.draw(coin[i]->getCoinSprite());}

        window.draw(coin_text);
        window.draw(distance_text);

        if (blockSprite3_1[rand_pack3_1-1].getPosition().x<player.getCharSprite().getPosition().x-600) {rand_pack3_1=1+rand()%nob3_1;}
        if (blockSprite3_2[rand_pack3_2-1].getPosition().x<player.getCharSprite().getPosition().x-600) {rand_pack3_2=1+rand()%nob3_2;}

        if (blockSprite3_1[rand_pack3_1-1].getPosition().x<player.getCharSprite().getPosition().x-600)
        {
            for (int i=0; i<rand_pack3_1; i++) {r_n_x3_1[i]=s_rand_x3_1+i*72; r_n_y3_1[i]=s_rand_y3_1;}
        }
        if (blockSprite3_2[rand_pack3_2-1].getPosition().x<player.getCharSprite().getPosition().x-600)
        {
            for (int i=0; i<rand_pack3_2; i++) {r_n_x3_2[i]=s_rand_x3_2+i*72; r_n_y3_2[i]=s_rand_y3_2;}
        }

        for (int i=0; i<rand_pack3_1; i++)
        {
            blockSprite3_1[i].setPosition(r_n_x3_1[i], r_n_y3_1[i]);
            window.draw(blockSprite3_1[i]);
            s_rand_x3_1=(player.getCharSprite().getPosition().x+1000)+rand()%1000;
            s_rand_y3_1=250+rand()%300;
        }
        for (int i=0; i<rand_pack3_2; i++)
        {
            blockSprite3_2[i].setPosition(r_n_x3_2[i], r_n_y3_2[i]);
            window.draw(blockSprite3_2[i]);
            s_rand_x3_2=(player.getCharSprite().getPosition().x+1500)+rand()%1000;
            s_rand_y3_2=200+rand()%350;
        }

        for (int i=0; i<numofcoin; i++)
        {
            if (coin[i]->collectCoin(player.getCharSprite())==true) {player.setCoinCount(player.getCoinCount()+1);}
            if (coin[i]->getCoinSprite().getPosition().x<player.getCharSprite().getPosition().x-600 || coin[i]->collectCoin(player.getCharSprite())==true)
            {
                r_x_coin[i]=(player.getCharSprite().getPosition().x+1000)+rand()%900;
                r_y_coin[i]=200+rand()%350;
                coin[i]->getCoinSprite().setPosition(r_x_coin[i], r_y_coin[i]);
            }
        }

        window.draw(trap.getTrapSprite());
        if (trap.getTrapSprite().getPosition().x<player.getCharSprite().getPosition().x-600)
        {
            r_x_trap=(player.getCharSprite().getPosition().x+1000)+rand()%1000;
            r_y_trap=200+rand()%400;
            trap.getTrapSprite().setPosition(r_x_trap, r_y_trap);
        }

        if (trap.isCollision(player.getCharSprite())==true)
        {
            player.setLife(false);
            Font go_font;
            go_font.loadFromFile("fonts/gameoverfont.ttf");
            Text go_text("", go_font, 100);
            go_text.setColor(Color::Red);
            go_text.setStyle(Text::Bold);
            go_text.setPosition(player.getCharSprite().getPosition().x, 350);
            go_text.setString("GAME OVER");
            window.draw(go_text);
        }

        window.display();
    }

    for (int i=0; i<numofcoin; i++) {delete coin[i];}
}

void gameRunning()
{
    if (START_GAME()==true) {gameRunning();}
}

int main()
{
    gameRunning();
    return 0;
}
