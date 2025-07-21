#pragma once
#include "Card.h"
class Card4 : public Card
{
public:
    Card4(const CellPosition& pos);
    virtual void Apply(Grid* pGrid, Player* pPlayer);

    virtual void Save(ofstream& OutFile);

    ~Card4();
};

