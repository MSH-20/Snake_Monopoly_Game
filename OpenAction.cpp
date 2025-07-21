#include "OpenAction.h"


OpenAction::OpenAction(ApplicationManager* pApp) : Action(pApp)
{
	F = "";
}

void OpenAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Enter the file name");
	F = pIn->GetSrting(pOut);
	pOut->ClearStatusBar();

	F = "saves/" + F + ".txt";
}

void OpenAction::Execute()
{
	ReadActionParameters();

	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	ifstream inF(F, ios::in);

	if (!inF.is_open())
	{
		pOut->PrintMessage("Couldn't Open Input File");
		pOut->ClearStatusBar();
	}
	else
	{
		Action* pAct;
		pGrid->DeleteAll();
		pAct = new AddLadderAction(pManager);
		pAct->Open(inF);
		delete pAct;
		pAct = new AddSnakeAction(pManager);
		pAct->Open(inF);
		delete pAct;
		pAct = new AddCardAction(pManager);
		pAct->Open(inF);
		delete pAct;
		pAct = nullptr;
		inF.close();
	}


}

OpenAction::~OpenAction()
{
}
