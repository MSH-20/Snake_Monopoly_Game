#include "CardM11.h"
CardM11::CardM11(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 11; // set the inherited cardNumber data member with the card number (11 here)
}

CardM11::CardM11(const CellPosition& pos, int price, int fees) : Card(pos)
{
	if (!alreadyset)
	{
		this->price = price;
		this->fees = fees;
		alreadyset = true;
	}
	cardNumber = 11;
}

bool CardM11::av = true;
bool CardM11::alreadyset = false;
int CardM11::price;
int CardM11::fees;
Player* CardM11::Owner = nullptr;
bool CardM11::isAlreadySaved = false;


int CardM11::GetPrice()
{
	return price;
}

int CardM11::GetFees()
{
	return fees;
}

void CardM11::SetPrice(int p)
{
	price = p;
}

void CardM11::SetFees(int f)
{
	fees = f;
}

void CardM11::ReadCardParameters(Grid* pGrid)
{
	if (!alreadyset)
	{
		Output* pOut = pGrid->GetOutput();
		Input* pIn = pGrid->GetInput();
		pOut->PrintMessage("New Card11: Enter the price: ");
		price = pIn->GetInteger(pOut);
		pOut->ClearStatusBar();
		pOut->PrintMessage("Enter the fees: ");
		fees = pIn->GetInteger(pOut);
		pOut->ClearStatusBar();
		alreadyset = true;
	}
}

void CardM11::Apply(Grid* pGrid, Player* pPlayer)
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

void CardM11::Save(ofstream& OutFile)
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

void CardM11::ResetOwnership()
{
	av = true;
	Owner = nullptr;
	alreadyset = false;
}

CardM11::~CardM11(void)
{
}
