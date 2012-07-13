#pragma once

#include "Threads.h"

extern int frmFramesSelectedFrameFirst;
extern int frmFramesSelectedFrameLast;
extern int frmFramesSelectedFrameCurrent;
extern int frmFramesSelectionMade;


using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace CubeSense {

	/// <summary>
	/// Summary for FrmFrames
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class FrmFrames : public System::Windows::Forms::Form
	{
	public:
		FrmFrames(void)
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
		~FrmFrames()
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
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(0, 0);
			this->listBox1->Name = L"listBox1";
			this->listBox1->ScrollAlwaysVisible = true;
			this->listBox1->SelectionMode = System::Windows::Forms::SelectionMode::MultiExtended;
			this->listBox1->Size = System::Drawing::Size(292, 264);
			this->listBox1->TabIndex = 0;
			this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &FrmFrames::listBox1_SelectedIndexChanged);
			this->listBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &FrmFrames::listBox1_MouseDown);
			// 
			// FrmFrames
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(292, 266);
			this->Controls->Add(this->listBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"FrmFrames";
			this->Text = L"FrmFrames";
			this->ResumeLayout(false);

		}
#pragma endregion
	public: 
		virtual void WndProc(System::Windows::Forms::Message% ThisMsg) override;


	private: System::Void listBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
				int min;
				int max;
				int i;
				if (listBox1->SelectedIndices->Count>0)
				{
					min=max=listBox1->SelectedIndices[0];
					for(i=0;i<listBox1->SelectedIndices->Count;i++)
					{
						if (listBox1->SelectedIndices[i]>max)
							max=listBox1->SelectedIndices[i];
						if (listBox1->SelectedIndices[i]<min)
							min=listBox1->SelectedIndices[i];
					}
					frmFramesSelectedFrameFirst=min;
					frmFramesSelectedFrameLast=max;
					frmFramesSelectedFrameCurrent=listBox1->SelectedIndex;
					frmFramesSelectionMade=1;
					threadCopyContentDefaultCoreIn();
				}
			 }
	private: System::Void listBox1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				int t;
				t=listBox1->SelectedIndex;
				listBox1->SelectedIndices->Clear();
				listBox1->SelectedIndices->Add(t);
			 }
	};
}
