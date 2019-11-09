#pragma once

namespace LifeCells
{

	using namespace System;
	using namespace System::Drawing;
	using namespace System::Windows::Forms;

	ref class Cell abstract : public Panel
	{

	public:
		property int Side;
		property Point^ Position;

		Cell();
		bool operator==(Cell^ other);
		bool operator!=(Cell^ other);
	};


	inline Cell::Cell()
	{
		this->Margin = Windows::Forms::Padding(0);
		this->Text = "";
		this->BorderStyle = Windows::Forms::BorderStyle::FixedSingle;
		this->Cursor = Windows::Forms::Cursors::Hand;
	}
	inline bool Cell::operator==(Cell^ other)
	{
		if(this->GetType() != other->GetType())
			return false;

		return this->Left == other->Left && this->Top == other->Top;
	}
	inline bool Cell::operator!=(Cell^ other)
	{
		return !operator==(other);
	}

}