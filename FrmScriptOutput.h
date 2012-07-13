#pragma once

#include "handler.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace CubeSense {

	/// <summary>
	/// Summary for FrmScriptOutput
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class FrmScriptOutput : public System::Windows::Forms::Form
	{
	public:
		FrmScriptOutput(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FrmScriptOutput()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListBox^  listBox1;
	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->SuspendLayout();
			// 
			// listBox1
			// 
			this->listBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->listBox1->Font = (gcnew System::Drawing::Font(L"Courier New", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(186)));
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 16;
			this->listBox1->Location = System::Drawing::Point(0, 0);
			this->listBox1->Name = L"listBox1";
			this->listBox1->ScrollAlwaysVisible = true;
			this->listBox1->Size = System::Drawing::Size(292, 260);
			this->listBox1->TabIndex = 0;
			this->listBox1->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &FrmScriptOutput::listBox1_MouseDoubleClick);
			this->listBox1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &FrmScriptOutput::listBox1_MouseClick);
			this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &FrmScriptOutput::listBox1_SelectedIndexChanged);
			// 
			// FrmScriptOutput
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(292, 266);
			this->Controls->Add(this->listBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"FrmScriptOutput";
			this->Text = L"FrmScriptOutput";
			this->Load += gcnew System::EventHandler(this, &FrmScriptOutput::FrmScriptOutput_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	public: 
		virtual void WndProc(System::Windows::Forms::Message% ThisMsg) override;

	private: System::Void FrmScriptOutput_Load(System::Object^  sender, System::EventArgs^  e) {
				 int a;
				 a=4;

			 }
	private: System::Void listBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
	private: System::Void listBox1_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			handlerFrmScriptOutputListBox1SelectedIndexChanged(listBox1->SelectedIndex);
			 }
	private: System::Void listBox1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				handlerFrmScriptOutputListBox1SelectedIndexChanged(listBox1->SelectedIndex);
			 }
	};
}
