#include "DesignModeSwitch.h"
#include "Grid.h"

DesignModeSwitch::DesignModeSwitch(ApplicationManager* pApp) : Action(pApp)
{

}

void DesignModeSwitch::ReadActionParameters()
{

}

void DesignModeSwitch::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	
	pOut->ClearStatusBar();
	pOut->CreateDesignModeToolBar();
	pGrid->ResetPlayers();	
}

DesignModeSwitch::~DesignModeSwitch()
{

}
