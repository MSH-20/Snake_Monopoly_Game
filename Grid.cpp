#include "Grid.h"

#include "Cell.h"
#include "GameObject.h"
#include "Ladder.h"
#include "Card.h"
#include "Player.h"
#include "Snake.h"

Grid::Grid(Input * pIn, Output * pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}

	// Allocate thePlayer Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells-1][0], i); // first cell
		PlayerList[i]->Draw(pOut); // initially draw players in the first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;
}


// ========= Adding or Removing GameObjects to Cells =========


bool Grid::AddObjectToCell(GameObject * pNewObject)  // think if any validation is needed
{
	// Get the cell position of pNewObject
	CellPosition pos = pNewObject->GetPosition();
	if (pos.IsValidCell()) // Check if valid position
	{
		// Get the previous GameObject of the Cell
		GameObject * pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if( pPrevObject)  // the cell already contains a game object
			return false; // do NOT add and return false

		// Set the game object of the Cell with the new game object
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);
		return true; // indicating that addition is done
	}
	return false; // if not a valid position
}

void Grid::RemoveObjectFromCell(const CellPosition & pos)
{
	if (pos.IsValidCell()) // Check if valid position
	{
		// Note: you can deallocate the object here before setting the pointer to null if it is needed

		if (CellList[pos.VCell()][pos.HCell()]->HasSnake())
			Snake::DecNum();
		else if (CellList[pos.VCell()][pos.HCell()]->HasLadder())
			Ladder::DecNum();
		else if (CellList[pos.VCell()][pos.HCell()]->HasCard())
			Card::DecNum();

		CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL);


	}
}

void Grid::UpdatePlayerCell(Player * player, const CellPosition & newPosition)
{
	// Clear the player's circle from the old cell position
	player->ClearDrawing(pOut);

	// Set the player's CELL with the new position
	Cell * newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);	

	// Draw the player's circle on the new cell position
	player->Draw(pOut);
}

bool Grid::IsOverLapping(GameObject* newObj) const
{
	bool is = false;
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->GetGameObject() != nullptr)
			{
				if ((CellList[i][j]->GetGameObject())->IsOverLapping(newObj))
				{
					is = true;
					break;
				}
			}
		}
	}
	if (is)
	{
		pOut->PrintMessage("The 2 objects are over lapping");
	}
	return is;
}


// ========= Setters and Getters Functions =========


Input * Grid::GetInput() const
{
	return pIn;
}

Output * Grid::GetOutput() const
{
	return pOut;
}

void Grid::SetClipboard(Card * pCard) // to be used in copy/cut
{
	// you may update slightly in implementation if you want (but without breaking responsibilities)
	Clipboard = pCard;
}

Card * Grid::GetClipboard() const // to be used in paste
{
	return Clipboard;
}

void Grid::SetEndGame(bool endGame)
{
	this->endGame = endGame;
}

bool Grid::GetEndGame() const
{
	return endGame;
}

void Grid::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount; // this generates value from 0 to MaxPlayerCount - 1
}

void Grid::SaveAll(ofstream& inF) // if we saved without checking we will save all in random order
{
	int f = 0;
	bool has = false;
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if(CellList[i][j]->HasLadder())
			{
				GameObject* g = CellList[i][j]->GetGameObject();
				has = true;

				if (f == 0)
				{
					inF << static_cast<Ladder*>(g)->GetNumberOfLadders() << endl;
					f++;
				}
				
				g->Save(inF);
			}
		}
	}
	f = 0;
	if (!has)
		inF << 0 << endl;
	has = false;
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->HasSnake())
			{
				GameObject* g = CellList[i][j]->GetGameObject();
				has = true;
				if (f == 0)
				{
					inF << static_cast<Snake*>(g)->GetNumberOfSnakes() << endl;
					f++;
				}

				g->Save(inF);
			}
		}
	}
	f = 0;
	if (!has)
		inF << 0 << endl;
	has = false;
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->HasCard())
			{
				GameObject* g = CellList[i][j]->GetGameObject();
				has = true;
				if (f == 0)
				{
					inF << static_cast<Card*>(g)->GetNumberOfCards() << endl;
					f++;
				}

				g->Save(inF);
			}
		}
	}
	if (!has)
		inF << 0 << endl;
}

void Grid::DeleteAll() // use it when load
{
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			RemoveObjectFromCell(CellList[i][j]->GetCellPosition());
		}
	}
}

// ========= Other Getters =========


Player * Grid::GetCurrentPlayer() const     //you were adding that one
{
	return PlayerList[currPlayerNumber];
}


Ladder * Grid::GetNextLadder(const CellPosition & position)
{
	
	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
			GameObject* go = CellList[i][j]->GetGameObject();
			Ladder* ladder = dynamic_cast<Ladder*>(go);
			if (ladder)
			{
				return ladder; // If it's a ladder, return it
			}
			///TODO: Check if CellList[i][j] has a ladder, if yes return it
			

		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}

Snake* Grid::GetNextSnake(const CellPosition& position)
{

	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
			GameObject* go = CellList[i][j]->GetGameObject();
			Snake* sn = dynamic_cast<Snake*>(go);
			if (sn)
			{
				return sn; // If it's a ladder, return it
			}

			///TODO: Check if CellList[i][j] has a ladder, if yes return it


		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}

GameObject* Grid::GetGameObject(const CellPosition& position)
{
	CellList[position.VCell()][position.HCell()];
	return CellList[position.VCell()][position.HCell()]->GetGameObject();
}

// ========= User Interface Functions =========

void Grid::ResetPlayers()      //added this function to reset the players
{
	currPlayerNumber = 0;
	endGame = 0;
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		PlayerList[i]->reset(pOut);
	}
}

void Grid::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw cells with or without cards 
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCellOrCard(pOut);
			}
		}

		// 2- Draw other cell objects (ladders, snakes)
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawLadderOrSnake(pOut);
			}
		}

		// 3- Draw players
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->Draw(pOut);
		}
	}
	else // In PLAY Mode
	{
		// 1- Print Player's Info
		string playersInfo = "";
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->AppendPlayerInfo(playersInfo); // passed by reference
			if (i < MaxPlayerCount-1) // except the last player
				playersInfo += ", ";
		}
		playersInfo += " | Curr = " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(playersInfo);

		// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
		//       so we do NOT need draw all players again in UpdateInterface() of the Play mode
		// In addition, cards/snakes/ladders do NOT change positions in Play Mode, so need to draw them here too
	}
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}


//int** Grid::GetLadders(int n)
//{
//	int** Ladders = new int*[n];
//	for (int i = 0; i < n; ++i)
//	{
//		Ladders[i] = new int[2];
//	}
//	n = 0;
//	for (int i = NumVerticalCells - 1; i >= 0; i--)
//	{
//		for (int j = 0; j < NumHorizontalCells; j++)
//		{
//			if (CellList[i][j]->HasLadder())
//			{
//				Ladders[n][0] = (CellList[i][j]->GetCellPosition()).GetCellNum();
//				Ladders[n][1] = static_cast<Ladder*>(CellList[i][j]->GetGameObject())->GetEndPosition().GetCellNum();
//				++n;
//			}
//		}
//	}
//	return Ladders;
//}
//
//int** Grid::GetSnakes(int n)
//{
//	int** Snakes = new int* [n];
//	for (int i = 0; i < n; ++i)
//	{
//		Snakes[i] = new int[2];
//	}
//	n = 0;
//	for (int i = NumVerticalCells - 1; i >= 0; i--)
//	{
//		for (int j = 0; j < NumHorizontalCells; j++)
//		{
//			if (CellList[i][j]->HasSnake())
//			{
//				Snakes[n][0] = (CellList[i][j]->GetCellPosition()).GetCellNum();
//				Snakes[n][1] = static_cast<Snake*>(CellList[i][j]->GetGameObject())->GetEndPosition().GetCellNum();
//				++n;
//			}
//		}
//	}
//	return Snakes;
//}
//
 
// ========= Bonus Functions =========

void Grid::Icedpower(int n)
{
	PlayerList[n]->setIced();
}

void Grid::Firedpower(int i)
{
	PlayerList[i]->setFired(currPlayerNumber);
}
void Grid::Poisonedpower(int i)
{
	PlayerList[i]->setPoisoned(currPlayerNumber);
}
void Grid::Lightening()
{
	for (int i = 0; i < 4; i++)
	{
		if (i != currPlayerNumber)
			PlayerList[i]->DecWalletForSuperPowers();
	}
}


// ========= Destructor=========
Grid::~Grid()
{
	delete pIn;
	delete pOut;

	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			delete CellList[i][j];
		}
	}

	// Deallocate the Player Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		delete PlayerList[i];
	}
}