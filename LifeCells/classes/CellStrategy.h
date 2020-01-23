#pragma once
#include "Board.h"
#include "../TestForm.h"
#include "StartSizes.h"
using namespace System::Collections;


namespace LifeCells
{

	public ref class CellStrategy
	{

	public:
		Board^ board;
		Panel^ cellsPanel;
		Timer^ timer1;
		Button^ runButton;
		NumericUpDown^ cellSizeTB;
		NumericUpDown^ heightTB;


		CellStrategy(StartSizes sizes, TestForm^ form);


		void cellClick(Object^ sender, EventArgs^ e);
		void randomClick(Object^ sender, EventArgs^ e);
		void clearClick(Object^ sender, EventArgs^ e);
		void closeClick(Object^ sender, EventArgs^ e);
		void runClick(Object^ sender, EventArgs^ e);
		void timer1_Tick(Object^ sender, EventArgs^ e);
		void handleBoardDelegate(int a);
		void removeInvoke(Cell^ item);
		void addInvoke(Cell^ item);
		void resizeClick(Object^ sender, EventArgs^ e);

	private:
		TestForm^ form;
		int height;
		int cellSize;
		int margin;
	};


	inline CellStrategy::CellStrategy(StartSizes sizes, TestForm^ form)
	{
		height = sizes.height;
		cellSize = sizes.cellSize;
		margin = sizes.margin;

		board = gcnew Board(height, cellSize, margin);
		this->form = form;
	}


	void CellStrategy::cellClick(Object^ sender, EventArgs^ e)
	{
		auto cell = (Cell^)sender;

		auto item = board->swap(cell);
		item->Click += gcnew EventHandler(this, &CellStrategy::cellClick);

		cellsPanel->Controls->Remove(cell);
		cellsPanel->Controls->Add(item);
		//item->Focus();
	}
	void CellStrategy::randomClick(Object^ sender, EventArgs^ e)
	{
		cellsPanel->Controls->Clear();

		board->cells = board->getRandomBoard();
		for each (Cell ^ item in board->cells)
		{
			cellsPanel->Controls->Add(item);
			item->Click += gcnew EventHandler(this, &CellStrategy::cellClick);
		}
	}
	void CellStrategy::clearClick(Object^ sender, EventArgs^ e)
	{
		board->cells = board->getDeadBoard();
		cellsPanel->Controls->Clear();

		for each (Cell ^ cell in board->cells)
		{
			cell->Click += gcnew EventHandler(this, &CellStrategy::cellClick);
			cellsPanel->Controls->Add(cell);
		}
	}
	void CellStrategy::closeClick(Object^ sender, EventArgs^ e)
	{
		form->Close();
	}
	void CellStrategy::runClick(Object^ sender, EventArgs^ e)
	{
		if (timer1->Enabled)
		{
			timer1->Enabled = false;
			runButton->Text = "RUN";
			return;
		}

		timer1->Enabled = true;
		runButton->Text = "STOP";
	}
	void CellStrategy::timer1_Tick(Object^ sender, EventArgs^ e)
	{
		runButton->Text = "STOP";

		if (board->refineBoard())
		{
			auto handleBoard = gcnew Action<int>(this, &CellStrategy::handleBoardDelegate);
			handleBoard->BeginInvoke(5, nullptr, nullptr);
			return;
		}

		timer1->Enabled = false;
		runButton->Text = "RUN";

		for each (Cell ^ cell in cellsPanel->Controls)
			if (cell->GetType() == AliveCell::typeid)
			{
				MessageBox::Show("The cells are in their harmony");
				return;
			}

		MessageBox::Show("All the cells have been exterminated");
	}
	void CellStrategy::handleBoardDelegate(int a)
	{
		// get cells to clear
		auto handlingCells = gcnew Generic::List<Cell^>();
		for each (Cell ^ item in cellsPanel->Controls)
			if (item->GetType() == AliveCell::typeid)
				handlingCells->Add(gcnew DeadCell(item));

		for each (Cell ^ item in board->cells)
			if (item->GetType() == AliveCell::typeid)
				handlingCells->Add(gcnew AliveCell(item));


		// substitute cells
		for (int i = 0; i < handlingCells->Count; ++i)
			for each (Cell ^ item in cellsPanel->Controls)
				if (handlingCells[i]->Position->Equals(item->Position))
				{
					handlingCells[i]->Click += gcnew EventHandler(this, &CellStrategy::cellClick);

					auto remove = gcnew Action<Cell^>(this, &CellStrategy::removeInvoke);
					form->Invoke(remove, item);

					auto add = gcnew Action<Cell^>(this, &CellStrategy::addInvoke);
					form->Invoke(add, handlingCells[i]);

					if (i == handlingCells->Count - 1)
						return;

					break;
				}
	}
	void CellStrategy::removeInvoke(Cell^ item)
	{
		cellsPanel->Controls->Remove(item);
	}
	void CellStrategy::addInvoke(Cell^ item)
	{
		cellsPanel->Controls->Add(item);
	}
	void CellStrategy::resizeClick(Object^ sender, EventArgs^ e)
	{
		if (timer1->Enabled)
		{
			timer1->Enabled = false;
			runButton->Text = "RUN";
		}

		if (cellSize == Convert::ToInt32(cellSizeTB->Text) &&
			height == Convert::ToInt32(heightTB->Text))
			return;

		cellSize = Convert::ToInt32(cellSizeTB->Text);
		height = Convert::ToInt32(heightTB->Text);

		board = gcnew Board(height, cellSize, margin);

		form->Width = cellSize / 2 + 15 + height * (cellSize + margin) * 2;
		form->Height = cellSize / 2 + 40 + height * (cellSize + margin) + 50;

		clearClick(this, EventArgs::Empty);
	}

}