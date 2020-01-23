#pragma once
#include "classes/Board.h"
#include "classes/MainFormBuilder.h"


namespace LifeCells
{
	delegate void voidVoidDelegate();

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;



	public ref class Main : public System::Windows::Forms::Form
	{

	protected: ~Main()
	{
		if (components)
		{
			delete components;
		}
	}
	public:	Main(void)
	{
		InitializeComponent();
	}


	private: System::ComponentModel::IContainer^ components;
	private: System::Windows::Forms::Timer^ timer1;
	private:
		Board^ board;
		int height = 15;
		int cellSize = 20;
		int margin = 0;
		System::Windows::Forms::Panel^ cellsPanel;
		System::Windows::Forms::Button^ runButton;
		System::Windows::Forms::NumericUpDown^ cellSizeTB;
		System::Windows::Forms::NumericUpDown^ heightTB;


#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Interval = 1000;
			this->timer1->Tick += gcnew System::EventHandler(this, &Main::timer1_Tick);
			// 
			// Main
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"Main";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"Main";
			this->Load += gcnew System::EventHandler(this, &Main::Main_Load);
			this->ResumeLayout(false);

		}
#pragma endregion

	private: void Main_Load(System::Object^ sender, System::EventArgs^ e)
	{
		this->SuspendLayout();
		this->Text = "Cells";
		board = gcnew Board(height, cellSize, margin);

		// 15 and 40 - additions for windows header and borders
		// 50 - height of the buttons bar
		this->Width = cellSize / 2 + 15 + height * (cellSize + margin) * 2;
		this->Height = cellSize / 2 + 40 + height * (cellSize + margin) + 50;

		auto appearingPoint = Point(
			SystemInformation::VirtualScreen.Width / 2 - this->Width / 2,
			SystemInformation::VirtualScreen.Height / 2 - this->Height / 2
		);
		this->Location = appearingPoint;

		auto randomButton = gcnew Button();
		randomButton->Text = "RANDOM";
		randomButton->Top = 10;
		randomButton->Left = 10;
		randomButton->Height = 30;
		randomButton->Click += gcnew EventHandler(this, &Main::randomClick);

		auto clearButton = gcnew Button();
		clearButton->Text = "CLEAR";
		clearButton->Top = 10;
		clearButton->Left = randomButton->Right + 5;
		clearButton->Height = 30;
		clearButton->Click += gcnew EventHandler(this, &Main::clearClick);

		runButton = gcnew Button();
		runButton->Text = "RUN";
		runButton->Top = 10;
		runButton->Left = clearButton->Right + 5;
		runButton->Height = 30;
		runButton->Click += gcnew EventHandler(this, &Main::runClick);

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
		resizeButton->Click += gcnew EventHandler(this, &Main::resizeClick);

		auto closeButton = gcnew Button();
		closeButton->Text = "CLOSE";
		closeButton->Top = 10;
		closeButton->Left = randomButton->Left + this->Width - 110;
		closeButton->Height = 30;
		closeButton->Click += gcnew EventHandler(this, &Main::closeClick);

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
		this->Controls->Add(panel);

		cellsPanel = gcnew Panel();
		cellsPanel->Dock = DockStyle::Fill;

		for each (Cell ^ item in board->cells)
		{
			cellsPanel->Controls->Add(item);
			item->Click += gcnew EventHandler(this, &Main::cellClick);
		}

		this->Controls->Add(cellsPanel);
		this->ResumeLayout();
	}
	private: void cellClick(Object^ sender, EventArgs^ e)
	{
		auto cell = (Cell^)sender;

		auto item = board->swap(cell);
		item->Click += gcnew EventHandler(this, &Main::cellClick);

		cellsPanel->Controls->Remove(cell);
		cellsPanel->Controls->Add(item);
		//item->Focus();
	}
	private: void randomClick(Object^ sender, EventArgs^ e)
	{
		cellsPanel->Controls->Clear();

		board->cells = board->getRandomBoard();
		for each (Cell ^ item in board->cells)
		{
			cellsPanel->Controls->Add(item);
			item->Click += gcnew EventHandler(this, &Main::cellClick);
		}
	}
	private: void clearClick(Object^ sender, EventArgs^ e)
	{
		board->cells = board->getDeadBoard();
		cellsPanel->Controls->Clear();

		for each (Cell ^ cell in board->cells)
		{
			cell->Click += gcnew EventHandler(this, &Main::cellClick);
			cellsPanel->Controls->Add(cell);
		}
	}
	private: void closeClick(Object^ sender, EventArgs^ e)
	{
		this->Close();
	}
	private: void runClick(Object^ sender, EventArgs^ e)
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
	private: void timer1_Tick(System::Object^ sender, System::EventArgs^ e)
	{
		runButton->Text = "STOP";

		if (board->refineBoard())
		{
			auto handleBoard = gcnew Action<int>(this, &Main::handleBoardDelegate);
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
	private: void handleBoardDelegate(int a)
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
					handlingCells[i]->Click += gcnew EventHandler(this, &Main::cellClick);

					auto remove = gcnew Action<Cell^>(this, &Main::removeInvoke);
					Invoke(remove, item);

					auto add = gcnew Action<Cell^>(this, &Main::addInvoke);
					Invoke(add, handlingCells[i]);

					if (i == handlingCells->Count - 1)
						return;

					break;
				}
	}
	private: void removeInvoke(Cell^ item)
	{
		cellsPanel->Controls->Remove(item);
	}
	private: void addInvoke(Cell^ item)
	{
		cellsPanel->Controls->Add(item);
	}
	private: void resizeClick(Object^ sender, EventArgs^ e)
	{
		if (cellSize == Convert::ToInt32(cellSizeTB->Text) &&
			height == Convert::ToInt32(heightTB->Text))
			return;

		cellSize = Convert::ToInt32(cellSizeTB->Text);
		height = Convert::ToInt32(heightTB->Text);
		this->Controls->Clear();
		Main_Load(this, EventArgs::Empty);
	}
	};

}