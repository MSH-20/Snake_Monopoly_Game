#include "Ladder.h"

Ladder::Ladder(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{

	this->endCellPos = endCellPos;
	++num;

	///TODO: Do the needed validation
}

int Ladder::num = 0; // Definition and initialization

void Ladder::Draw(Output* pOut) const
{
	pOut->DrawLadder(position, endCellPos);

}

void Ladder::Apply(Grid* pGrid, Player* pPlayer) 
{
	

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


		// == Here are some guideline steps (numbered below) to implement this function ==

		// 1- Print a message "You have reached a ladder. Click to continue ..." and wait mouse click

	pGrid->PrintErrorMessage("You have reached a ladder. Click to continue ...");

	// 2- Apply the ladder's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that
	pGrid->UpdatePlayerCell(pPlayer, endCellPos);
	
}

CellPosition Ladder::GetEndPosition() const
{
	return endCellPos;
}





int Ladder::GetNumberOfLadders()
{
	return num;
}

void Ladder::DecNum()
{
	--num;
}

void Ladder::Save(ofstream& OutFile)
{
	OutFile << position.GetCellNum() << " " << endCellPos.GetCellNum() << endl;
}

bool Ladder::IsOverLapping(GameObject* newObj) const
{
	bool is = false;
	if (!dynamic_cast<Card*>(newObj))
	{
		int e = endCellPos.GetCellNum();
		int s = position.GetCellNum();

		int s2, e2;

		bool done = true;

		if (dynamic_cast<Ladder*>(newObj))
		{
			s2 = (static_cast<Ladder*>(newObj)->GetPosition()).GetCellNum();
			e2 = (static_cast<Ladder*>(newObj)->GetEndPosition()).GetCellNum();
			done = false;
			if (s2 != e2)
			{
				for (int i = s; i <= e; i += 11)
				{
					for (int j = s2; j <= e2; j += 11)
						if (i == j)
						{
							is = true;
							break;
						}
				}
			}
		}
		else if (dynamic_cast<Snake*>(newObj) && done)
		{
			s2 = (static_cast<Snake*>(newObj)->GetPosition()).GetCellNum();
			e2 = (static_cast<Snake*>(newObj)->GetEndPosition()).GetCellNum();
			if (e2 == s || s2 == e)
			{
				is = true;
			}
		}
		
	}
	return is;
}

Ladder::~Ladder()
{
}
