#pragma once

#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "Card.h"
#include <fstream>
#include "Card1.h"
#include "Card2.h"
#include "Card3.h"
#include "Card4.h"
#include "Card5.h"
#include "Card6.h"
#include "Card7.h"
#include "Card8.h"
#include "Card9.h"
#include "CardM10.h"
#include "CardM11.h"
#include "CardM12.h"
#include "CardM13.h"


class AddCardAction : public Action
{
	// [Action Parameters]
	int cardNumber;            // 1- the card number
	CellPosition cardPosition; // 2- cell position of the card

	// Note: These parameters should be read in ReadActionParameters()
	
public:
	AddCardAction(ApplicationManager *pApp); // A Constructor
		
	virtual void ReadActionParameters(); // Reads AddCardAction action parameters (cardNumber, cardPosition)
	
	virtual void Execute(); // Creates a new Card Object of the specific Card Number
	void Execute(int t, const CellPosition& p, int par1, int par2);
	void Open(ifstream& Infile);
	                        // and Reads the Parameters of This Card Number (if any)
	                        // then Sets this Card Object to GameObject Pointer of its Cell
	
	virtual ~AddCardAction(); // A Virtual Destructor
};

