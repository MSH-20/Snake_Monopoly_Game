#include "Snake.h"

Snake::Snake(const CellPosition& startCellPos, const CellPosition& endCellPos) : GameObject(startCellPos)
{

	this->endCellPos = endCellPos;
	++num;

	///TODO: Do the needed validation
}

int Snake::num = 0; // Definition and initialization

void Snake::Draw(Output* pOut) const
{
	pOut->DrawSnake(position, endCellPos);

}

void Snake::Apply(Grid* pGrid, Player* pPlayer)
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


		// == Here are some guideline steps (numbered below) to implement this function ==

		// 1- Print a message "You have reached a Snake. Click to continue ..." and wait mouse click

	pGrid->PrintErrorMessage("You have reached a Snake. Click to continue ...");

	// 2- Apply the Snake's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that
	pGrid->UpdatePlayerCell(pPlayer, endCellPos);

}

CellPosition Snake::GetEndPosition() const
{
	return endCellPos;
}





int Snake::GetNumberOfSnakes()
{
	return num;
}

void Snake::DecNum()
{
	--num;
}

void Snake::Save(ofstream& OutFile)
{
	OutFile << position.GetCellNum() << " " << endCellPos.GetCellNum() << endl;
}

bool Snake::IsOverLapping(GameObject* newObj) const
{
	bool is = false;
	if (!dynamic_cast<Card*>(newObj))
	{
		int s = endCellPos.GetCellNum();
		int e = position.GetCellNum();

		int s2, e2;

		bool done = true;

		if (dynamic_cast<Snake*>(newObj))
		{
			e2 = (static_cast<Snake*>(newObj)->GetPosition()).GetCellNum();
			s2 = (static_cast<Snake*>(newObj)->GetEndPosition()).GetCellNum();
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
		else if (dynamic_cast<Ladder*>(newObj) && done)
		{
			e2 = (static_cast<Ladder*>(newObj)->GetPosition()).GetCellNum();
			s2 = (static_cast<Ladder*>(newObj)->GetEndPosition()).GetCellNum();
			if (s == e2 || e == s2)
			{
				is = true;
			}
		}
		/*if (s2 != e2)
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
		}*/
	}
	return is;
}

Snake::~Snake()
{
}
