#pragma once


using namespace System;
using namespace System::ComponentModel;




public ref class TestForm : public System::Windows::Forms::Form
{

public:
	System::ComponentModel::Container^ components;

	TestForm(void)
	{ }

protected:
	~TestForm()
	{
		if (components)
		{
			delete components;
		}
	}
};

