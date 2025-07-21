#pragma once
#include "Card.h"
// [ CardOne ] Summary:
// Its Apply() Function: Decrements the value of the passing player’s wallet by a value
// Its Parameters: The Wallet Value to decrease --> put it as a "data member" and read it in ReadCardParameters()

class Card5 :
    public Card
{
public:
    Card5(const CellPosition& pos);
    ~Card5();
    virtual void Apply(Grid* pGrid, Player* pPlayer);

    virtual void Save(ofstream& OutFile);
};
