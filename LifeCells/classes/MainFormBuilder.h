#pragma once
#include "Board.h"
#include "StartSizes.h"
#include "../TestForm.h"


using namespace System;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Collections;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;
using namespace LifeCells;

public ref class MainFormBuilder
{

public:
	MainFormBuilder(StartSizes sizes);

	MainFormBuilder^ InitializeComponent();
	MainFormBuilder^ AddTimer();
	MainFormBuilder^ AddManagePanel();
	MainFormBuilder^ AddCellsPanel();
	MainFormBuilder^ AdjustStartPoint();
	TestForm^ GetForm();

private:
	int height;
	int cellSize;
	int margin;

	TestForm^ form;
	Board^ board;
	Timer^ timer1;
	Panel^ cellsPanel;
	Button^ runButton;
	NumericUpDown^ cellSizeTB;
	NumericUpDown^ heightTB;

	void cellClick(Object^ sender, EventArgs^ e);
	void randomClick(Object^ sender, EventArgs^ e);
	void clearClick(Object^ sender, EventArgs^ e);
	void closeClick(Object^ sender, EventArgs^ e);
	void runClick(Object^ sender, EventArgs^ e);
	void timer1_Tick(System::Object^ sender, System::EventArgs^ e);
	void handleBoardDelegate(int a);
	void removeInvoke(Cell^ item);
	void addInvoke(Cell^ item);
	void resizeClick(Object^ sender, EventArgs^ e);
};



inline MainFormBuilder::MainFormBuilder(StartSizes sizes)
{
	height = sizes.height;
	cellSize = sizes.cellSize;
	margin = sizes.margin;

	form = gcnew TestForm();
	board = gcnew Board(height, cellSize, margin);
}


inline MainFormBuilder^ MainFormBuilder::InitializeComponent()
{
	form->components = (gcnew System::ComponentModel::Container());

	form->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
	form->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	form->ClientSize = System::Drawing::Size(284, 261);
	form->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
	form->MaximizeBox = false;
	form->Name = L"Main";
	form->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
	form->Text = L"Cells";
	//this->Load += gcnew System::EventHandler(this, &Main::Main_Load);
	form->Width = cellSize / 2 + 15 + height * (cellSize + margin) * 2;
	form->Height = cellSize / 2 + 40 + height * (cellSize + margin) + 50;

	return this;
}
inline MainFormBuilder^ MainFormBuilder::AddTimer()
{
	timer1 = (gcnew System::Windows::Forms::Timer(form->components));
	timer1->Interval = 1000;
	timer1->Tick += gcnew System::EventHandler(this, &MainFormBuilder::timer1_Tick);

	return this;
}
inline MainFormBuilder^ MainFormBuilder::AddManagePanel()
{
	auto randomButton = gcnew Button();
	randomButton->Text = "RANDOM";
	randomButton->Top = 10;
	randomButton->Left = 10;
	randomButton->Height = 30;
	randomButton->Click += gcnew EventHandler(this, &MainFormBuilder::randomClick);

	auto clearButton = gcnew Button();
	clearButton->Text = "CLEAR";
	clearButton->Top = 10;
	clearButton->Left = randomButton->Right + 5;
	clearButton->Height = 30;
	clearButton->Click += gcnew EventHandler(this, &MainFormBuilder::clearClick);

	runButton = gcnew Button();
	runButton->Text = "RUN";
	runButton->Top = 10;
	runButton->Left = clearButton->Right + 5;
	runButton->Height = 30;
	runButton->Click += gcnew EventHandler(this, &MainFormBuilder::runClick);

	auto cellSizeLabel = gcnew Label();
	cellSizeLabel->Text = "Cell Size:";
	cellSizeLabel->Top = 17;
	cellSizeLabel->Left = runButton->Right + 5;
	cellSizeLabel->Height = 20;
	cellSizeLabel->Width = 50;

	cellSizeTB = gcnew NumericUpDown();
	cellSizeTB->Text = Convert::ToString(cellSize);
	cellSizeTB->Minimum = 20;
	cellSizeTB->Maximum = 30;
	cellSizeTB->Top = 15;
	cellSizeTB->Left = cellSizeLabel->Right;
	cellSizeTB->Height = 20;
	cellSizeTB->Width = 40;

	auto heightLabel = gcnew Label();
	heightLabel->Text = "Height:";
	heightLabel->Top = 17;
	heightLabel->Left = cellSizeTB->Right + 5;
	heightLabel->Height = 30;
	heightLabel->Width = 43;

	heightTB = gcnew NumericUpDown();
	heightTB->Text = Convert::ToString(height);
	heightTB->Minimum = 15;
	heightTB->Maximum = 25;
	heightTB->Top = 15;
	heightTB->Left = heightLabel->Right;
	heightTB->Height = 20;
	heightTB->Width = 40;

	auto resizeButton = gcnew Button();
	resizeButton->Text = "APPLY";
	resizeButton->Top = 13;
	resizeButton->Left = heightTB->Right + 5;
	resizeButton->Height = 25;
	resizeButton->Click += gcnew EventHandler(this, &MainFormBuilder::resizeClick);

	auto closeButton = gcnew Button();
	closeButton->Text = "CLOSE";
	closeButton->Top = 10;
	closeButton->Left = randomButton->Left + form->Width - 110;
	closeButton->Height = 30;
	closeButton->Click += gcnew EventHandler(this, &MainFormBuilder::closeClick);

	auto panel = gcnew Panel();
	panel->Dock = DockStyle::Bottom;
	panel->Height = 50;
	panel->BackColor = Drawing::SystemColors::ControlLight;
	panel->Controls->Add(randomButton);
	panel->Controls->Add(clearButton);
	panel->Controls->Add(closeButton);
	panel->Controls->Add(runButton);
	panel->Controls->Add(cellSizeLabel);
	panel->Controls->Add(cellSizeTB);
	panel->Controls->Add(heightLabel);
	panel->Controls->Add(heightTB);
	panel->Controls->Add(resizeButton);
	form->Controls->Add(panel);

	return this;
}
inline MainFormBuilder^ MainFormBuilder::AddCellsPanel()
{
	cellsPanel = gcnew Panel();
	cellsPanel->Dock = DockStyle::Fill;

	for each (Cell ^ item in board->cells)
	{
		cellsPanel->Controls->Add(item);
		item->Click += gcnew EventHandler(this, &MainFormBuilder::cellClick);
	}

	form->Controls->Add(cellsPanel);

	return this;
}
inline MainFormBuilder^ MainFormBuilder::AdjustStartPoint()
{
	auto appearingPoint = Point(
		SystemInformation::VirtualScreen.Width / 2 - form->Width / 2,
		SystemInformation::VirtualScreen.Height / 2 - form->Height / 2
	);
	form->Location = appearingPoint;

	return this;
}
inline TestForm^ MainFormBuilder::GetForm()
{
	return form;
}


void MainFormBuilder::cellClick(Object^ sender, EventArgs^ e)
{
	auto cell = (Cell^)sender;

	auto item = board->swap(cell);
	item->Click += gcnew EventHandler(this, &MainFormBuilder::cellClick);

	cellsPanel->Controls->Remove(cell);
	cellsPanel->Controls->Add(item);
	//item->Focus();
}
void MainFormBuilder::randomClick(Object^ sender, EventArgs^ e)
{
	cellsPanel->Controls->Clear();

	board->cells = board->getRandomBoard();
	for each (Cell ^ item in board->cells)
	{
		cellsPanel->Controls->Add(item);
		item->Click += gcnew EventHandler(this, &MainFormBuilder::cellClick);
	}
}
void MainFormBuilder::clearClick(Object^ sender, EventArgs^ e)
{
	board->cells = board->getDeadBoard();
	cellsPanel->Controls->Clear();

	for each (Cell ^ cell in board->cells)
	{
		cell->Click += gcnew EventHandler(this, &MainFormBuilder::cellClick);
		cellsPanel->Controls->Add(cell);
	}
}
void MainFormBuilder::closeClick(Object^ sender, EventArgs^ e)
{
	form->Close();
}
void MainFormBuilder::runClick(Object^ sender, EventArgs^ e)
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
void MainFormBuilder::timer1_Tick(Object^ sender, EventArgs^ e)
{
	runButton->Text = "STOP";

	if (board->refineBoard())
	{
		auto handleBoard = gcnew Action<int>(this, &MainFormBuilder::handleBoardDelegate);
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
void MainFormBuilder::handleBoardDelegate(int a)
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
				handlingCells[i]->Click += gcnew EventHandler(this, &MainFormBuilder::cellClick);

				auto remove = gcnew Action<Cell^>(this, &MainFormBuilder::removeInvoke);
				form->Invoke(remove, item);

				auto add = gcnew Action<Cell^>(this, &MainFormBuilder::addInvoke);
				form->Invoke(add, handlingCells[i]);

				if (i == handlingCells->Count - 1)
					return;

				break;
			}
}
void MainFormBuilder::removeInvoke(Cell^ item)
{
	cellsPanel->Controls->Remove(item);
}
void MainFormBuilder::addInvoke(Cell^ item)
{
	cellsPanel->Controls->Add(item);
}
void MainFormBuilder::resizeClick(Object^ sender, EventArgs^ e)
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
