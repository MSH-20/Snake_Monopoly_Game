#include "CardM13.h"
CardM13::CardM13(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 13; // set the inherited cardNumber data member with the card number (13 here)
}

CardM13::CardM13(const CellPosition& pos, int price, int fees) : Card(pos)
{
	if (!alreadyset)
	{
		this->price = price;
		this->fees = fees;
		alreadyset = true;
	}
	cardNumber = 13;
}

bool CardM13::av = true;
bool CardM13::alreadyset = false;
int CardM13::price;
int CardM13::fees;
Player* CardM13::Owner = nullptr;
bool CardM13::isAlreadySaved = false;

int CardM13::GetPrice()
{
	return price;
}

int CardM13::GetFees()
{
	return fees;
}

void CardM13::SetPrice(int p)
{
	price = p;
}

void CardM13::SetFees(int f)
{
	fees = f;
}

void CardM13::ReadCardParameters(Grid* pGrid)
{
	if (!alreadyset)
	{
		Output* pOut = pGrid->GetOutput();
		Input* pIn = pGrid->GetInput();
		pOut->PrintMessage("New Card13: Enter the price: ");
		price = pIn->GetInteger(pOut);
		pOut->ClearStatusBar();
		pOut->PrintMessage("Enter the fees: ");
		fees = pIn->GetInteger(pOut);
		pOut->ClearStatusBar();
		alreadyset = true;
	}
}

void CardM13::Apply(Grid* pGrid, Player* pPlayer)
{
	int w;
	if (av)
	{
		Output* pOut = pGrid->GetOutput();
		Input* pIn = pGrid->GetInput();
		pOut->PrintMessage("Buy? (y/n)");
		string buy = pIn->GetSrting(pOut);
		pOut->ClearStatusBar();
		if ((buy == "y" || buy == "Y") && pPlayer->GetWallet() >= price)
		{
			av = false;
			Owner = pPlayer;
			w = Owner->GetWallet();
			Owner->SetWallet(w - price);
		}
	}
	else if (pPlayer != Owner)
	{
		w = pPlayer->GetWallet();
		if (w >= fees)
		{
			pPlayer->SetWallet(w - fees);
		}
		else
		{
			pPlayer->SetWallet(0);
		}

		w = Owner->GetWallet();
		Owner->SetWallet(w + fees);
	}
}

void CardM13::Save(ofstream& OutFile)
{
	if (!isAlreadySaved)
	{
		OutFile << cardNumber << " " << position.GetCellNum() << " " << GetPrice() << " " << GetFees() << endl;
		isAlreadySaved = true;
	}
	else
	{
		OutFile << cardNumber << " " << position.GetCellNum() << endl;
	}
}

void CardM13::ResetOwnership()
{
	av = true;
	Owner = nullptr;
	alreadyset = false;
}

CardM13::~CardM13(void)
{
}
