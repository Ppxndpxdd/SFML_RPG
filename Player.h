#ifndef PLAYER_H
#define PLAYER_H


#include "Entity.h"
class Player :
    public Entity
{
private:
    //Variables

    //Initializer functions
    void initVariable();
    void initComponents();
public:
    Player(float x, float y, sf::Texture& texture);
    virtual ~Player();

    //Funtions
};

#endif // !PLAYER_H