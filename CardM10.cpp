#include "CardM10.h"
CardM10::CardM10(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 10; // set the inherited cardNumber data member with the card number (10 here)
}

CardM10::CardM10(const CellPosition& pos, int price, int fees) : Card(pos)
{
	if (!alreadyset)
	{
		this->price = price;
		this->fees = fees;
		alreadyset = true;
	}
	cardNumber = 10;
}

bool CardM10::av = true;
bool CardM10::alreadyset = false;
int CardM10::price;
int CardM10::fees;
Player* CardM10::Owner = nullptr;
bool CardM10::isAlreadySaved = false;

int CardM10::GetPrice()
{
	return price;
}

int CardM10::GetFees()
{
	return fees;
}

void CardM10::SetPrice(int p)
{
	price = p;
}

void CardM10::SetFees(int f)
{
	fees = f;
}

void CardM10::Save(ofstream& OutFile)
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

void CardM10::ReadCardParameters(Grid* pGrid)
{
	if (!alreadyset)
	{
		Output* pOut = pGrid->GetOutput();
		Input* pIn = pGrid->GetInput();
		pOut->PrintMessage("New Card10: Enter the price: ");
		price = pIn->GetInteger(pOut);
		pOut->ClearStatusBar();
		pOut->PrintMessage("Enter the fees: ");
		fees = pIn->GetInteger(pOut);
		pOut->ClearStatusBar();
		alreadyset = true;
	}
}

void CardM10::Apply(Grid* pGrid, Player* pPlayer)
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
	else if(pPlayer != Owner)
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

void CardM10::ResetOwnership()
{
	av = true;
	Owner = nullptr;
	alreadyset = false;
}

CardM10::~CardM10(void)
{
	
}
