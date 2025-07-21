#include "ApplicationManager.h"

#include "Grid.h"
#include "AddLadderAction.h"
#include "AddCardAction.h"
#include "RollDiceAction.h"
#include "CopyAction.h"
#include "PasteAction.h"
#include "CutAction.h"
#include "DeleteAction.h"
///TODO: Add #include for all action types
#include "AddSnakeAction.h"
#include "EditAction.h"
#include "PlayModeSwitch.h"
#include "DesignModeSwitch.h"
#include "DiceValueAction.h"
#include "NewGame.h"
#include "OpenAction.h"
#include "SaveAction.h"


ApplicationManager::ApplicationManager()
{
	// Create Input, output and Grid
	pOut = new Output();
	pIn = pOut->CreateInput();
	pGrid = new Grid(pIn, pOut);
}

////////////////////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	delete pGrid;
}

//==================================================================================//
//								Interface Management Functions						//
//==================================================================================//

Grid* ApplicationManager::GetGrid() const
{
	return pGrid;
}

void ApplicationManager::UpdateInterface() const
{
	pGrid->UpdateInterface();
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//

ActionType ApplicationManager::GetUserAction() const
{
	// Ask the input to get the action from the user.
	return pIn->GetUserAction();
}

////////////////////////////////////////////////////////////////////////////////////

// Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;

	// According to Action Type, create the corresponding action object
	switch (ActType)
	{
	case ADD_LADDER:
		pAct = new AddLadderAction(this);
		break;
	case ADD_SNAKE:
		pAct = new AddSnakeAction(this);
		break;

	case ADD_CARD:
		// create an object of AddCardAction here
		pAct = new AddCardAction(this);
		break;

	case COPY:
		// create an object of CopyAction here
		pAct = new CopyAction(this);
		break;
	case PASTE:
		pAct = new PasteAction(this);
		break;
	case CUT:
		pAct = new CutAction(this);
		break;
	case EDIT:
		pAct = new EditAction(this);
		break;
	case SAVE:
		pAct = new SaveAction(this);
		break;
	case OPEN:
		pAct = new OpenAction(this);
		break;
	case DEL:
		pAct = new DeleteAction(this);
		break;
	case EXIT:
		break;

	case TO_PLAY_MODE:
		pAct = new PlayModeSwitch(this);
		break;

	case ROLL_DICE:
		// create an object of RollDiceAction here
		pAct = new RollDiceAction(this);
		break;

	case DICE_VALUE:
		pAct = new DiceValueAction(this);
		break;

	case NEW_GAME:
		pAct = new NewGame(this);
		break;

	case EXIT2:
		 break;

	case TO_DESIGN_MODE:
		pAct = new DesignModeSwitch(this);
		break;




		///TODO: Add a case for EACH Action type in the Design mode or Play mode



	case STATUS:	// a click on the status bar ==> no action
		return;
	}

	// Execute the created action
	if (pAct != NULL)
	{
		pAct->Execute(); // Execute
		delete pAct;	 // Action is not needed any more after executing ==> delete it
		pAct = NULL;
	}
}
