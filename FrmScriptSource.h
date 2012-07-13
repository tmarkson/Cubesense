#ifndef FRMSCRIPTSOURCE_H
#define FRMSCRIPTSOURCE_H


#include "Script.h"
#include "handler.h"
#include "Threads.h"

int frmScriptSourceAskForSave();

extern int frmScriptSourceCreatingNew;


extern unsigned char *frmScriptSourceSourceCode;
extern unsigned int frmScriptSourceSourceCodeLength;
extern unsigned int frmScriptSourceReadyToRun;
extern unsigned int frmScriptRealTimeSourceReadyToRun;
extern unsigned int frmScriptSourceType;
extern unsigned int frmScriptSourceChanged;


using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace XtremeCommandBars;
using namespace System::Runtime::InteropServices; // for class Marshal

namespace CubeSense {

	/// <summary>
	/// Summary for FrmScriptSource
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class FrmScriptSource : public System::Windows::Forms::Form
	{
	public:
		FrmScriptSource(void)
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
		~FrmScriptSource()
		{
			if (components)
			{
				delete components;
			}
		}
	private: AxXtremeSyntaxEdit::AxSyntaxEdit^  axSyntaxEdit1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FrmScriptSource::typeid));
			this->axSyntaxEdit1 = (gcnew AxXtremeSyntaxEdit::AxSyntaxEdit());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->axSyntaxEdit1))->BeginInit();
			this->SuspendLayout();
			// 
			// axSyntaxEdit1
			// 
			this->axSyntaxEdit1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->axSyntaxEdit1->Location = System::Drawing::Point(0, 0);
			this->axSyntaxEdit1->Name = L"axSyntaxEdit1";
			this->axSyntaxEdit1->OcxState = (cli::safe_cast<System::Windows::Forms::AxHost::State^  >(resources->GetObject(L"axSyntaxEdit1.OcxState")));
			this->axSyntaxEdit1->Size = System::Drawing::Size(292, 266);
			this->axSyntaxEdit1->TabIndex = 0;
			this->axSyntaxEdit1->CurPosChanged += gcnew AxXtremeSyntaxEdit::_DSyntaxEditEvents_CurPosChangedEventHandler(this, &FrmScriptSource::axSyntaxEdit1_CurPosChanged);
			this->axSyntaxEdit1->TextChangedEvent += gcnew AxXtremeSyntaxEdit::_DSyntaxEditEvents_TextChangedEventHandler(this, &FrmScriptSource::axSyntaxEdit1_TextChangedEvent);
			this->axSyntaxEdit1->KeyDownEvent += gcnew AxXtremeSyntaxEdit::_DSyntaxEditEvents_KeyDownEventHandler(this, &FrmScriptSource::axSyntaxEdit1_KeyDownEvent);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->Filter = L"VB script files (*.vb)|*.vb|C# script files (*.cs)|*.cs|All files(*.*)|*.*";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &FrmScriptSource::openFileDialog1_FileOk);
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->Filter = L"VB script files (*.vb)|*.vb|C# script files (*.cs)|*.cs|All files(*.*)|*.*";
			this->saveFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &FrmScriptSource::saveFileDialog1_FileOk);
			// 
			// FrmScriptSource
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(292, 266);
			this->Controls->Add(this->axSyntaxEdit1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"FrmScriptSource";
			this->Text = L"FrmScriptSource";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->axSyntaxEdit1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	public: 
		virtual void WndProc(System::Windows::Forms::Message% ThisMsg) override;

		System::String^ scriptFileName;
		int scriptFileNameSet;

		CommandBarControl ^AddButton(CommandBarControls ^Controls, XTPControlType ControlType, int Id, String ^Caption)
		{
			return AddButton(Controls, ControlType, Id, Caption, false, "");
		}
		CommandBarControl ^AddButton(CommandBarControls ^Controls, XTPControlType ControlType, int Id, String ^Caption, bool BeginGroup)
		{
			return AddButton(Controls, ControlType, Id, Caption, BeginGroup, "");
		}
		CommandBarControl ^AddButton(CommandBarControls ^Controls, XTPControlType ControlType, int Id, String ^Caption, bool BeginGroup, String ^DescriptionText)
		{
			CommandBarControl ^Control = Controls->Add(ControlType, Id, Caption, -1, false);
			Control->BeginGroup = BeginGroup;
			Control->DescriptionText = DescriptionText;
			return Control;    
		}
	public:
		void FrmScriptSourceInit()
		{
			axSyntaxEdit1->ConfigFile="SyntaxEdit.ini";
			axSyntaxEdit1->DataManager->FileExt = ".cpp";
			frmScriptSourceChanged=0;
			frmScriptSourceType=SCRIPT_TYPE_CS;
			frmScriptSourceCreatingNew=0;
			scriptFileNameSet=0;
			createNewScript();
		}
		void copyScriptSource()
		{

			Marshal::FreeHGlobal((System::IntPtr)(void*)frmScriptSourceSourceCode);
			frmScriptSourceSourceCode = (unsigned char*)(void*)Marshal::StringToHGlobalAnsi(axSyntaxEdit1->Text);
			frmScriptSourceSourceCodeLength=axSyntaxEdit1->Text->Length;
			frmScriptSourceReadyToRun=1;
		}

		void copyRealTimeScriptSource()
		{
			/*
			Marshal::FreeHGlobal((System::IntPtr)(void*)frmScriptSourceSourceCode);
			frmScriptSourceSourceCode = (unsigned char*)(void*)Marshal::StringToHGlobalAnsi(axSyntaxEdit1->Text);
			frmScriptSourceSourceCodeLength=axSyntaxEdit1->Text->Length;
			*/
			axSyntaxEdit1->SaveFileAs("F:\\Lumisense\\eigthCubed\\Software\\CubeSense\\Simulations\\uscript.cpp");
			frmScriptRealTimeSourceReadyToRun=1;
		}

		System::String^ createNewVbScript()
		{
			System::String^ s;
			s="Public Sub Main() Implements scriptInterface.IScript.Main"
			+System::Environment::NewLine+
			System::Environment::NewLine+
			"End Sub";
			return s;
		}
		void changeScriptType(int t)
		{
			frmScriptSourceType=t;
			if (frmScriptSourceType==SCRIPT_TYPE_VB)
				axSyntaxEdit1->DataManager->FileExt = ".vb";
			if (frmScriptSourceType==SCRIPT_TYPE_CS)
				axSyntaxEdit1->DataManager->FileExt = ".cpp";
			axSyntaxEdit1->EnableSyntaxColorization=0;
			axSyntaxEdit1->EnableSyntaxColorization=1;

		}
		System::String^ createNewCsScript()
		{
			System::String^ s;
			s="public virtual void Main()"
			+System::Environment::NewLine+
			"{"
			+System::Environment::NewLine+
			System::Environment::NewLine+
			"}";
			return s;
		}

		void setFileDialogFilterIndex()
		{
			if (frmScriptSourceType==SCRIPT_TYPE_VB)
			{
				saveFileDialog1->FilterIndex=1;
				openFileDialog1->FilterIndex=1;
			}
			if (frmScriptSourceType==SCRIPT_TYPE_CS)
			{
				saveFileDialog1->FilterIndex=2;
				openFileDialog1->FilterIndex=2;
			}
		}

		void createNewScript()
		{
			int r;

			if (frmScriptSourceChanged!=0)
			{
	
				r=handlerAskAboutSavingScript();
				if (r==6)
				{
					frmScriptSourceCreatingNew=1;
					setFileDialogFilterIndex();
					saveFileDialog1->ShowDialog();
				}
				if (r==7)
				{
					frmScriptSourceChanged=0;
					createNewScript();
				}
			}
			else
			{
				if (frmScriptSourceType==SCRIPT_TYPE_VB)
				{
					axSyntaxEdit1->Text=createNewVbScript();
					axSyntaxEdit1->CurrPos->SetPos(2,1);
				}
				if (frmScriptSourceType==SCRIPT_TYPE_CS)
				{
					axSyntaxEdit1->Text=createNewCsScript();
					axSyntaxEdit1->CurrPos->SetPos(3,1);
				}
				scriptFileNameSet=0;
				frmScriptSourceCreatingNew=0;
			}
		}


		void saveScript()
		{
			if (scriptFileNameSet==0)
			{
				saveFileDialog1->FileName="";
				setFileDialogFilterIndex();
				saveFileDialog1->ShowDialog();	
			}
			else
			{
				frmScriptSourceChanged=0;
				axSyntaxEdit1->SaveFileAs(scriptFileName);
				axSyntaxEdit1->EnableSyntaxColorization=0;
				axSyntaxEdit1->EnableSyntaxColorization=1;
				changeScriptType(frmScriptSourceType);
			}
		}
		void saveScriptAs()
		{
			if (scriptFileNameSet)
			{
				saveFileDialog1->FileName=scriptFileName;
			}	
			else
				saveFileDialog1->FileName="";
			setFileDialogFilterIndex();
			saveFileDialog1->ShowDialog();			
		}
		void openScript()
		{
			setFileDialogFilterIndex();
			openFileDialog1->FileName="";
			openFileDialog1->ShowDialog();
		}

	

	private: System::Void axSyntaxEdit1_CurPosChanged(System::Object^  sender, AxXtremeSyntaxEdit::_DSyntaxEditEvents_CurPosChangedEvent^  e) {
			 }
	private: System::Void axSyntaxEdit1_TextChangedEvent(System::Object^  sender, AxXtremeSyntaxEdit::_DSyntaxEditEvents_TextChangedEvent^  e) {
				 frmScriptSourceChanged=1;
			 }
	private: System::Void saveFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
				frmScriptSourceChanged=0;
				scriptFileName=saveFileDialog1->FileName;
				scriptFileNameSet=1;
				axSyntaxEdit1->SaveFileAs(scriptFileName);
				axSyntaxEdit1->EnableSyntaxColorization=0;
				axSyntaxEdit1->EnableSyntaxColorization=1;
				changeScriptType(frmScriptSourceType);
				if (frmScriptSourceCreatingNew==1)
					createNewScript();
			 }
private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			axSyntaxEdit1->OpenFile(openFileDialog1->FileName);
			saveFileDialog1->FileName=openFileDialog1->FileName;
			scriptFileName=openFileDialog1->FileName;
			scriptFileNameSet=1;
			changeScriptType(frmScriptSourceType);
		 }
private: System::Void axSyntaxEdit1_KeyDownEvent(System::Object^  sender, AxXtremeSyntaxEdit::_DSyntaxEditEvents_KeyDownEvent^  e) {
			 if (e->keyCode==0x74/*VK_F5*/)
			 {
				this->copyScriptSource();
				threadCopyContentDefaultCoreIn();
			 }
		 }
};
}

#endif