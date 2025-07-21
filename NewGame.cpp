#include "NewGame.h"
#include "Grid.h"

NewGame::NewGame(ApplicationManager* pApp) : Action(pApp)
{

}

void NewGame::ReadActionParameters()
{

}

void NewGame::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	pOut->ClearStatusBar();                  //first clear the status bar and reset all players
	pGrid->ResetPlayers();
}

NewGame::~NewGame()
{

}