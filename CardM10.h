#pragma once

#include "Card.h"
#include <string>

class CardM10 : public Card
{
private:
    static bool alreadyset;
    static bool av;
    static int price;
    static int fees;
    static Player* Owner;
    static bool isAlreadySaved;
public:
    CardM10(const CellPosition& pos);
    CardM10(const CellPosition& pos, int, int);

    int GetPrice();
    int GetFees();

    void SetPrice(int);
    void SetFees(int);

    virtual void Save(ofstream& OutFile);

    virtual void ReadCardParameters(Grid* pGrid);
    virtual void Apply(Grid* pGrid, Player* pPlayer);

    static void ResetOwnership();            //to remove ownership of a card from the player

    ~CardM10();
};

