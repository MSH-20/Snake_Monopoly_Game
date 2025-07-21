#pragma once
#include "Card.h"
class Card9 :
    public Card
{
private: 
    int ToCellNum;
public:
    Card9(const CellPosition& pos);
    Card9(const CellPosition& pos, int);
    virtual void ReadCardParameters(Grid* pGrid);
    virtual void Apply(Grid* pGrid, Player* pPlayer);

    virtual void Save(ofstream& OutFile);

    int GetToCellNum();//to be used in paste
    void SetToCellNum(int);
    ~Card9();
};

