#pragma once
#include "Card.h"
class Card7 :
    public Card
{
public:
    Card7(const CellPosition& pos);
    ~Card7();
    virtual void Apply(Grid* pGrid, Player* pPlayer);

    virtual void Save(ofstream& OutFile);
};