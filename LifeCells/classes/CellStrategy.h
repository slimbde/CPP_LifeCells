#pragma once
#include "Board.h"
#include "StartSizes.h"
using namespace System;
using namespace System::Windows::Forms;
using namespace LifeCells;


public ref class CellStrategy
{

public:
	Board^ board;
	Panel^ cellsPanel;
	Timer^ timer1;
	Button^ runButton;
	NumericUpDown^ cellSizeTB;
	NumericUpDown^ heightTB;

	TestForm^ form;

	CellStrategy(StartSizes sizes)
	{
		height = sizes.height;
		cellSize = sizes.cellSize;
		margin = sizes.margin;

		board = gcnew Board(height, cellSize, margin);
	}

	


private:
	int height;
	int cellSize;
	int margin;
};