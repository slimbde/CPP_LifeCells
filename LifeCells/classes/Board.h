#pragma once
#include "AliveCell.h"
#include "DeadCell.h"


namespace LifeCells
{

	public ref class Board
	{
		int height;
		int cellSize;
		int margin;
		array<Cell^, 2>^ refinedCells;

		void updateCell(Cell^ cell);
		bool validCell(Point^ pts);


	public:
		property array<Cell^, 2>^ cells;
		property int Left;
		property int Top;

		Board(int height, int cellSize, int margin);
		Board(Board^ other);
		Cell^ swap(Cell^ cell);
		array<Cell^, 2>^ getRandomBoard();
		array<Cell^, 2>^ getDeadBoard();
		bool refineBoard();

	};



	inline void Board::updateCell(Cell^ cell)
	{
		auto checkPoint = gcnew Point((cell->Left - cellSize / 4) / cellSize,
			(cell->Top - cellSize / 4) / cellSize);

		auto pointsToCheck = gcnew array<Point^>(8)
		{
			gcnew Point(checkPoint->X - 1, checkPoint->Y - 1),
				gcnew Point(checkPoint->X, checkPoint->Y - 1),
				gcnew Point(checkPoint->X + 1, checkPoint->Y - 1),
				gcnew Point(checkPoint->X - 1, checkPoint->Y),
				gcnew Point(checkPoint->X + 1, checkPoint->Y),
				gcnew Point(checkPoint->X - 1, checkPoint->Y + 1),
				gcnew Point(checkPoint->X, checkPoint->Y + 1),
				gcnew Point(checkPoint->X + 1, checkPoint->Y + 1),
		};

		int counter = 0;    // counts alive cells
		for each (auto item in pointsToCheck)
			if (validCell(item))
				if (cells[item->Y, item->X]->GetType() == AliveCell::typeid) // if the cell is alive
					++counter;

		if (counter < 2 || counter > 3)
			refinedCells[checkPoint->Y, checkPoint->X] = gcnew DeadCell(cell->Left,
																		cell->Top,
																		cell->Side);
		else if (counter == 3)
			refinedCells[checkPoint->Y, checkPoint->X] = gcnew AliveCell(cell->Left,
																		 cell->Top,
																		 cell->Side);
		else if (cell->GetType() == AliveCell::typeid)
			refinedCells[checkPoint->Y, checkPoint->X] = gcnew AliveCell(cell->Left,
																		 cell->Top,
																		 cell->Side);
	}
	inline bool Board::validCell(Point^ pt)
	{
		if (pt->X < 0 || pt->X >= this->height * 2
			|| pt->Y < 0 || pt->Y >= this->height)
			return false;

		return true;
	}

	inline Board::Board(int height, int cellSize, int margin)
	{
		this->height = height;
		this->cellSize = cellSize;
		this->margin = margin;
		this->Left = cellSize / 4;
		this->Top = cellSize / 4;

		cells = gcnew array<Cell^, 2>(height, height * 2);
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < height * 2; ++j)
			{
				auto left = j * (cellSize + margin) + Left;
				auto top = i * (cellSize + margin) + Top;

				cells[i, j] = gcnew DeadCell(left, top, cellSize);
			}
		}
	}
	inline Board::Board(Board^ other)
	{
		this->height = other->height;
		this->cellSize = other->cellSize;
		this->margin = other->margin;
		this->Left = cellSize / 4;
		this->Top = cellSize / 4;

		cells = gcnew array<Cell^, 2>(height, height * 2);
		Array::Copy(other->cells, cells, cells->Length);
	}
	inline Cell^ Board::swap(Cell^ cell)
	{
		if (cell->GetType() == (AliveCell::typeid))
		{
			auto newCell = gcnew DeadCell(cell->Left, cell->Top, cell->Side);
			for each (Cell ^ %item in cells)
				if (item == cell)
				{
					item = newCell;
					break;
				}

			return newCell;
		}

		auto newCell = gcnew AliveCell(cell->Left, cell->Top, cell->Side);
		for each (Cell ^ %item in cells)
			if (item == cell)
			{
				item = newCell;
				break;
			}

		return newCell;
	}
	inline array<Cell^, 2>^ Board::getRandomBoard()
	{
		auto newCells = gcnew array<Cell^, 2>(height, height * 2);

		auto rnd = gcnew Random();
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < height * 2; ++j)
			{
				auto left = j * (cellSize + margin) + Left;
				auto top = i * (cellSize + margin) + Top;

				if (rnd->Next(3) == 1)
					newCells[i, j] = gcnew AliveCell(left, top, cellSize);
				else
					newCells[i, j] = gcnew DeadCell(left, top, cellSize);
			}
		}

		return newCells;
	}
	inline array<Cell^, 2>^ Board::getDeadBoard()
	{
		auto newCells = gcnew array<Cell^, 2>(height, height * 2);

		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < height * 2; ++j)
			{
				auto left = j * (cellSize + margin) + Left;
				auto top = i * (cellSize + margin) + Top;

				newCells[i, j] = gcnew DeadCell(left, top, cellSize);
			}
		}

		return newCells;
	}
	inline bool Board::refineBoard()
	{
		refinedCells = getDeadBoard();
		Array::Copy(cells, refinedCells, cells->Length);

		for each (Cell ^ %item in refinedCells)
			updateCell(item);

		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < height * 2; ++j)
			{
				if (cells[i, j] != refinedCells[i, j])
				{
					Array::Copy(refinedCells, cells, cells->Length);
					return true;
				}
			}
		}

		return false;
	}

}