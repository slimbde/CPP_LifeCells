#pragma once
#include "Cell.h"


namespace LifeCells
{

	ref class AliveCell : public Cell
	{

	public:
		AliveCell(int left, int top, int size);
		AliveCell(Cell^ other);
	};



	inline AliveCell::AliveCell(int left, int top, int size)
	{
		this->Size = Drawing::Size(size, size);
		this->Side = size;
		this->Top = top;
		this->Left = left;
		this->Position = gcnew Point(left, top);

		BackColor = Color::LightCoral;
	}
	inline AliveCell::AliveCell(Cell^ other)
	{
		this->Size = other->Size;
		this->Side = other->Side;
		this->Top = other->Top;
		this->Left = other->Left;
		this->Position = other->Position;

		BackColor = Color::LightCoral;
	}

}