#pragma once
#include "Card.h"
class Card8 :
    public Card
{
public:
    Card8(const CellPosition& pos);
    ~Card8();
    virtual void Apply(Grid* pGrid, Player* pPlayer);

    virtual void Save(ofstream& OutFile);
};

