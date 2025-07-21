#include "PlayModeSwitch.h"
#include "Grid.h"

PlayModeSwitch::PlayModeSwitch(ApplicationManager* pApp) : Action(pApp)
{

}

void PlayModeSwitch::ReadActionParameters()
{

}

void PlayModeSwitch::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	pOut->ClearStatusBar();
	pOut->CreatePlayModeToolBar();
}

PlayModeSwitch::~PlayModeSwitch()
{

}
