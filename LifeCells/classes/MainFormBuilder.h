#pragma once
#include "CellStrategy.h"
#include "StartSizes.h"
#include "../TestForm.h"


namespace LifeCells
{

	public ref class MainFormBuilder
	{

	public:
		MainFormBuilder(StartSizes sizes);

		MainFormBuilder^ InitializeComponent();
		MainFormBuilder^ AddTimer();
		MainFormBuilder^ AddManagePanel();
		MainFormBuilder^ AddCellsPanel();
		MainFormBuilder^ AdjustStartPoint();
		MainFormBuilder^ BindStrategyFields();
		TestForm^ GetForm();

	private:
		int height;
		int cellSize;
		int margin;

		CellStrategy^ strategy;
		TestForm^ form;
		Timer^ timer1;
		Panel^ cellsPanel;
		Button^ runButton;
		NumericUpDown^ cellSizeTB;
		NumericUpDown^ heightTB;
	};


	inline MainFormBuilder::MainFormBuilder(StartSizes sizes)
	{
		height = sizes.height;
		cellSize = sizes.cellSize;
		margin = sizes.margin;

		form = gcnew TestForm();
		strategy = gcnew CellStrategy(sizes, form);
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
		form->Width = cellSize / 2 + 15 + height * (cellSize + margin) * 2;
		form->Height = cellSize / 2 + 40 + height * (cellSize + margin) + 50;

		return this;
	}
	inline MainFormBuilder^ MainFormBuilder::AddTimer()
	{
		timer1 = (gcnew System::Windows::Forms::Timer(form->components));
		timer1->Interval = 1000;
		timer1->Tick += gcnew System::EventHandler(strategy, &CellStrategy::timer1_Tick);

		return this;
	}
	inline MainFormBuilder^ MainFormBuilder::AddManagePanel()
	{
		auto randomButton = gcnew Button();
		randomButton->Text = "RANDOM";
		randomButton->Top = 10;
		randomButton->Left = 10;
		randomButton->Height = 30;
		randomButton->Click += gcnew EventHandler(strategy, &CellStrategy::randomClick);

		auto clearButton = gcnew Button();
		clearButton->Text = "CLEAR";
		clearButton->Top = 10;
		clearButton->Left = randomButton->Right + 5;
		clearButton->Height = 30;
		clearButton->Click += gcnew EventHandler(strategy, &CellStrategy::clearClick);

		runButton = gcnew Button();
		runButton->Text = "RUN";
		runButton->Top = 10;
		runButton->Left = clearButton->Right + 5;
		runButton->Height = 30;
		runButton->Click += gcnew EventHandler(strategy, &CellStrategy::runClick);

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
		resizeButton->Click += gcnew EventHandler(strategy, &CellStrategy::resizeClick);

		auto closeButton = gcnew Button();
		closeButton->Text = "CLOSE";
		closeButton->Top = 10;
		closeButton->Left = randomButton->Left + form->Width - 110;
		closeButton->Height = 30;
		closeButton->Click += gcnew EventHandler(strategy, &CellStrategy::closeClick);

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

		for each (Cell ^ item in strategy->board->cells)
		{
			cellsPanel->Controls->Add(item);
			item->Click += gcnew EventHandler(strategy, &CellStrategy::cellClick);
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
	inline MainFormBuilder^ MainFormBuilder::BindStrategyFields()
	{
		strategy->cellsPanel = cellsPanel;
		strategy->timer1 = timer1;
		strategy->runButton = runButton;
		strategy->cellSizeTB = cellSizeTB;
		strategy->heightTB = heightTB;

		return this;
	}
	inline TestForm^ MainFormBuilder::GetForm()
	{
		return form;
	}

}