#pragma once
#include "Card.h"
class Card3 : public Card
{
public:
    Card3(const CellPosition& pos);
    virtual void Apply(Grid* pGrid, Player* pPlayer);

    virtual void Save(ofstream& OutFile);

    ~Card3();
};

