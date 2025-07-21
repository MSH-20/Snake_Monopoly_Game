#include "CellPosition.h"
#include "UI_Info.h"

CellPosition::CellPosition()
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;
}

CellPosition::CellPosition(int v, int h)
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;

	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition(int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum); // the function call with build a cell position (vCell and hCell)
	// from the passed (cellNum)
	// (*this) = ... --> this will copy the returned (vCell and hCell)
	//                   to the data members (vCell and hCell)
}

bool CellPosition::SetVCell(int v)
{
	if ((v >= 0) && (v <= 8))
	{
		vCell = v;
		return true;
	}
	///TODO: Implement this function as described in the .h file (don't forget the validation)


	return false; // this line sould be changed with your implementation
}

bool CellPosition::SetHCell(int h)
{
	if ((h >= 0) && (h <= 10))
	{
		hCell = h;
		return true;
	}
	///TODO: Implement this function as described in the .h file (don't forget the validation)


	return false; // this line sould be changed with your implementation
}

int CellPosition::VCell() const
{
	return vCell;
}

int CellPosition::HCell() const
{
	return hCell;
}

bool CellPosition::IsValidCell() const
{

	if ((hCell >= 0) && (hCell <= 10) && (vCell >= 0) && (vCell <= 8))
	{
		return true;
	}

	///TODO: Implement this function as described in the .h file


	return false; // this line sould be changed with your implementation
}

int CellPosition::GetCellNum() const
{
	return GetCellNumFromPosition(*this); // (*this) is the calling object of GetCellNum
	// which means the object of the current data members (vCell and hCell)
}

int CellPosition::GetCellNumFromPosition(const CellPosition& cellPosition)
{
	// Note:
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)
	// just define an integer that represents cell number and calculate it using the passed cellPosition then return it

	///TODO: Implement this function as described in the .h file
	int NumFromPosition = 1 + cellPosition.HCell() + ((8 - cellPosition.VCell()) * 11);
	return NumFromPosition; // this line should be changed with your implementation
}

CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)

	CellPosition position;

	/// TODO: Implement this function as described in the .h file

	int hh = ((cellNum - 1) % 11);
	position.SetHCell(hh);
	int vv = (8 - ((cellNum - 1) / 11));
	position.SetVCell(vv);
	// Note: use the passed cellNum to set the vCell and hCell of the "position" variable declared inside the function
	//       I mean: position.SetVCell(...) and position.SetHCell(...) then return it

	return position;
}

void CellPosition::AddCellNum(int addedNum)
{

	/// TODO: Implement this function as described in the .h file
	if ((GetCellNum() + addedNum) <= 99) 
		(*this) = GetCellPositionFromNum(GetCellNum() + addedNum);//idea from lines 23 to 26
	else
	{
		(*this) = GetCellPositionFromNum(99);
	}
	/*I have made it can not exceed 99 because the number of cells is from 1 to 99,
	so I am assuming that whoever reaches 99 is a winner,
	but I don't know if we get more than 99, so the user would be a winner or not
	(also as in real snake and ladder we win in the last cell so I implement the same)*/


	// Note: this function updates the data members (vCell and hCell) of the calling object

}