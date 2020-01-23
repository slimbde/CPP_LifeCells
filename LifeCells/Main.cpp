#include "Main.h"
#include "TestForm.h"
#include "classes/StartSizes.h"
#include "classes/MainFormBuilder.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

[STAThreadAttribute]
Int32 main(array<System::String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	auto sizes = StartSizes();
	auto builder = gcnew MainFormBuilder(sizes);

	builder = builder->InitializeComponent()
		->AddTimer()
		->AddManagePanel()
		->AddCellsPanel()
		->AdjustStartPoint();

	auto form = builder->GetForm();
	Application::Run(form);

	return 0;
}