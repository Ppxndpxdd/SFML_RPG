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
    Player(float x, float y, sf::Texture& texture_sheet);
    virtual ~Player();

    //Funtions
    virtual void update(const float& dt);
};

#endif // !PLAYER_H