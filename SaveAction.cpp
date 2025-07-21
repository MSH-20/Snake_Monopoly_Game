#include "SaveAction.h"

SaveAction::SaveAction(ApplicationManager* pApp) : Action(pApp)
{
	F = "";
}

void SaveAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("Enter the file name");
	F = pIn->GetSrting(pOut);
	pOut->ClearStatusBar();

	F = "saves/" + F + ".txt";
}
void SaveAction::Execute()
{
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	ofstream inF(F, ios::out);
	pGrid->SaveAll(inF);

	inF.close();

	//inF << Ladder::GetNumberOfLadders() << endl;
	//inF << Snake::GetNumberOfSnakes() << endl;
	//inF << Card::GetNumberOfCards() << endl;
	//int num = pGrid->GetLaddersNum();
	//inF << num << "\n";
	//int** Ladders = pGrid->GetLadders(num);
	//for (int i = 0; i < num; ++i)
	//{
	//	inF << Ladders[i][0] << " " << Ladders[i][1] << "\n";
	//}

	//for (int i = 0; i < num; ++i)
	//{
	//	delete[] Ladders[i];
	//}
	//if (num != 0)
	//delete[] Ladders;

	//num = pGrid->GetSnakesNum();
	//inF << num << "\n";
	//int** Snakes = pGrid->GetSnakes(num);
	//for (int i = 0; i < num; ++i)
	//{
	//	inF << Snakes[i][0] << " " << Snakes[i][1] << "\n";
	//}

	//for (int i = 0; i < num; ++i)
	//{
	//	delete[] Snakes[i];
	//}
	//if(num !=0)
	//delete[] Snakes;
}

SaveAction::~SaveAction()
{
}
