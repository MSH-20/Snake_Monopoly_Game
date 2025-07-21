#pragma once

#include "Card.h"

class Card2 : public Card
{
	int walletAmount; // the wallet value to decrease from the player

public:
	Card2(const CellPosition& pos); // A Constructor takes card position
	Card2(const CellPosition& pos, int walletAmount);
	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardOne which is: walletAmount
	virtual void Apply(Grid* pGrid, Player* pPlayer);
	int GetWalletAmount();//to be used in paste
	void SetWalletAmount(int ComingWalletAmount);//to be used in paste

	virtual void Save(ofstream& OutFile);

	virtual ~Card2(); // A Virtual Destructor
};

