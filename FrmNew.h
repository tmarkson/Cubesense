#pragma once

#include "handler.h"
#include "Threads.h"

extern int frmNewLatticeFrames;
extern int frmNewLatticeType;
extern int frmNewLatticeSizeX;
extern int frmNewLatticeSizeY;
extern int frmNewLatticeSizeZ;
extern int frmNewLatticeCustom;
extern int frmNewLatticeCreateNew;

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace CubeSense {

	/// <summary>
	/// Summary for FrmNew
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class FrmNew : public System::Windows::Forms::Form
	{
	public:
		FrmNew(void)
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
		~FrmNew()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected: 
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::ComboBox^  comboBox2;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::ComboBox^  comboBox3;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::ComboBox^  comboBox4;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::ComboBox^  comboBox5;
	private: System::Windows::Forms::ComboBox^  comboBox6;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;

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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->comboBox4 = (gcnew System::Windows::Forms::ComboBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->comboBox5 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox6 = (gcnew System::Windows::Forms::ComboBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(93, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Number of frames:";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(167, 6);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(74, 20);
			this->textBox1->TabIndex = 1;
			this->textBox1->Text = L"2048";
			this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 35);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(65, 13);
			this->label2->TabIndex = 0;
			this->label2->Text = L"Lattice type:";
			// 
			// comboBox1
			// 
			this->comboBox1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"Cubic", L"Rectangular", L"Custom"});
			this->comboBox1->Location = System::Drawing::Point(167, 32);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(74, 21);
			this->comboBox1->TabIndex = 2;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &FrmNew::comboBox1_SelectedIndexChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(13, 62);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(23, 13);
			this->label3->TabIndex = 0;
			this->label3->Text = L"X =";
			// 
			// comboBox2
			// 
			this->comboBox2->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(24) {L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8", 
				L"9", L"10", L"11", L"12", L"13", L"14", L"15", L"16", L"17", L"18", L"19", L"20", L"21", L"22", L"23", L"24"});
			this->comboBox2->Location = System::Drawing::Point(42, 59);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(43, 21);
			this->comboBox2->TabIndex = 2;
			this->comboBox2->Visible = false;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(91, 62);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(23, 13);
			this->label4->TabIndex = 0;
			this->label4->Text = L"Y =";
			// 
			// comboBox3
			// 
			this->comboBox3->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox3->FormattingEnabled = true;
			this->comboBox3->Items->AddRange(gcnew cli::array< System::Object^  >(24) {L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8", 
				L"9", L"10", L"11", L"12", L"13", L"14", L"15", L"16", L"17", L"18", L"19", L"20", L"21", L"22", L"23", L"24"});
			this->comboBox3->Location = System::Drawing::Point(120, 59);
			this->comboBox3->Name = L"comboBox3";
			this->comboBox3->Size = System::Drawing::Size(43, 21);
			this->comboBox3->TabIndex = 2;
			this->comboBox3->Visible = false;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(169, 62);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(23, 13);
			this->label5->TabIndex = 0;
			this->label5->Text = L"Z =";
			// 
			// comboBox4
			// 
			this->comboBox4->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox4->FormattingEnabled = true;
			this->comboBox4->Items->AddRange(gcnew cli::array< System::Object^  >(24) {L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8", 
				L"9", L"10", L"11", L"12", L"13", L"14", L"15", L"16", L"17", L"18", L"19", L"20", L"21", L"22", L"23", L"24"});
			this->comboBox4->Location = System::Drawing::Point(198, 59);
			this->comboBox4->Name = L"comboBox4";
			this->comboBox4->Size = System::Drawing::Size(43, 21);
			this->comboBox4->TabIndex = 2;
			this->comboBox4->Visible = false;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(12, 62);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(63, 13);
			this->label6->TabIndex = 0;
			this->label6->Text = L"Lattice size:";
			// 
			// comboBox5
			// 
			this->comboBox5->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox5->FormattingEnabled = true;
			this->comboBox5->Items->AddRange(gcnew cli::array< System::Object^  >(24) {L"1x1x1", L"2x2x2", L"3x3x3", L"4x4x4", L"5x5x5", 
				L"6x6x6", L"7x7x7", L"8x8x8", L"9x9x9", L"10x10x10", L"11x11x11", L"12x12x12", L"13x13x13", L"14x14x14", L"15x15x15", L"16x16x16", 
				L"17x17x17", L"18x18x18", L"19x19x19", L"20x20x20", L"21x21x21", L"22x22x22", L"23x23x23", L"24x24x24"});
			this->comboBox5->Location = System::Drawing::Point(167, 59);
			this->comboBox5->Name = L"comboBox5";
			this->comboBox5->Size = System::Drawing::Size(74, 21);
			this->comboBox5->TabIndex = 2;
			// 
			// comboBox6
			// 
			this->comboBox6->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox6->FormattingEnabled = true;
			this->comboBox6->Location = System::Drawing::Point(167, 59);
			this->comboBox6->Name = L"comboBox6";
			this->comboBox6->Size = System::Drawing::Size(74, 21);
			this->comboBox6->TabIndex = 2;
			this->comboBox6->Visible = false;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(38, 95);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Ok";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &FrmNew::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(139, 95);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Cancel";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &FrmNew::button2_Click);
			// 
			// FrmNew
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(253, 128);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->comboBox6);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->comboBox4);
			this->Controls->Add(this->comboBox3);
			this->Controls->Add(this->comboBox2);
			this->Controls->Add(this->comboBox5);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->comboBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"FrmNew";
			this->Text = L"Create new animation";
			this->Load += gcnew System::EventHandler(this, &FrmNew::FrmNew_Load);
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &FrmNew::FrmNew_FormClosing);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
public:
	void Initialize()
	{
		comboBox1->SelectedIndex=0;
		comboBox5->SelectedIndex=7;
		comboBox2->SelectedIndex=7;
		comboBox3->SelectedIndex=7;
		comboBox4->SelectedIndex=7;


	}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			this->Visible=false;
			handlerEnableMainForm();
			frmNewLatticeFrames=System::Int32::Parse(textBox1->Text);
			frmNewLatticeType=comboBox1->SelectedIndex;
			if (frmNewLatticeType==0)
			{
				frmNewLatticeSizeX=frmNewLatticeSizeY=frmNewLatticeSizeZ=comboBox5->SelectedIndex+1;
				frmNewLatticeCustom=0;
				frmNewLatticeCreateNew=1;
			}
			if (frmNewLatticeType==1)
			{
				frmNewLatticeSizeX=comboBox2->SelectedIndex+1;
				frmNewLatticeSizeY=comboBox3->SelectedIndex+1;
				frmNewLatticeSizeZ=comboBox4->SelectedIndex+1;
				frmNewLatticeCustom=0;
				frmNewLatticeCreateNew=1;
			}
			if (frmNewLatticeType==2)
			{
				frmNewLatticeSizeX=0;
				frmNewLatticeSizeY=0;
				frmNewLatticeSizeZ=0;
				frmNewLatticeCustom=comboBox6->SelectedIndex;
				frmNewLatticeCreateNew=1;
			}
			handlerNoAnimationTitle();
			handlerCreatingAnimation=0;
			threadCopyContentDefaultCoreIn();

		 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Visible=false;
			 handlerEnableMainForm();
		 }
private: System::Void FrmNew_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
			 this->Visible=false;
			 handlerEnableMainForm();
		 }
private: System::Void FrmNew_Load(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (comboBox1->SelectedIndex==0)
			 {
				 label3->Visible=false;
				 label4->Visible=false;
				 label5->Visible=false;
				 label6->Visible=true;
				 comboBox2->Visible=false;
				 comboBox3->Visible=false;
				 comboBox4->Visible=false;
				 comboBox5->Visible=true;
				 comboBox6->Visible=false;
			 }
			 if (comboBox1->SelectedIndex==1)
			 {
				 label3->Visible=true;
				 label4->Visible=true;
				 label5->Visible=true;
				 label6->Visible=false;
				 comboBox2->Visible=true;
				 comboBox3->Visible=true;
				 comboBox4->Visible=true;
				 comboBox5->Visible=false;
				 comboBox6->Visible=false;
			 }
			 if (comboBox1->SelectedIndex==2)
			 {
				 label3->Visible=false;
				 label4->Visible=false;
				 label5->Visible=false;
				 label6->Visible=false;
				 comboBox2->Visible=false;
				 comboBox3->Visible=false;
				 comboBox4->Visible=false;
				 comboBox5->Visible=false;
				 comboBox6->Visible=true;
			 }
		 }
};
}
