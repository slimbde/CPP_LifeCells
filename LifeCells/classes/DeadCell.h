#pragma once
#include "Cell.h"


namespace LifeCells
{

	ref class DeadCell : public Cell
	{

	public:
		DeadCell(int left, int top, int size);
		DeadCell(Cell^ other);
	};



	inline DeadCell::DeadCell(int left, int top, int size)
	{
		this->Size = Drawing::Size(size, size);
		this->Side = size;
		this->Top = top;
		this->Left = left;
		this->Position = gcnew Point(left, top);

		BackColor = Color::AliceBlue;
	}
	inline DeadCell::DeadCell(Cell^ other)
	{
		this->Size = other->Size;
		this->Side = other->Side;
		this->Top = other->Top;
		this->Left = other->Left;
		this->Position = other->Position;

		BackColor = Color::AliceBlue;
	}
}