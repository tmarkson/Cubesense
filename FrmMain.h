#pragma once

#include "Ids.h"
#include "FrmFrames.h"
#include "FrmScriptSource.h"
#include "FrmScriptOutput.h"
#include "FrmNew.h"
#include "Handler.h"
#include "Threads.h"
#include "WndProc.h"
#include "Script.h"
#include "Log.h"


using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace CubeSense {

	/// <summary>
	/// Summary for FrmMain
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class FrmMain : public System::Windows::Forms::Form
	{
	public:
		FrmMain(void)
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
		~FrmMain()
		{
			if (components)
			{
				delete components;
			}
		}
	private: AxXtremeCommandBars::AxCommandBars^  axCommandBars1;
	protected: 
	private: AxXtremeDockingPane::AxDockingPane^  axDockingPane1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Panel^  panel1;
	private: AxXtremeSuiteControls::AxProgressBar^  axProgressBar1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
















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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FrmMain::typeid));
			this->axCommandBars1 = (gcnew AxXtremeCommandBars::AxCommandBars());
			this->axDockingPane1 = (gcnew AxXtremeDockingPane::AxDockingPane());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->axProgressBar1 = (gcnew AxXtremeSuiteControls::AxProgressBar());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->axCommandBars1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->axDockingPane1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->axProgressBar1))->BeginInit();
			this->SuspendLayout();
			// 
			// axCommandBars1
			// 
			this->axCommandBars1->Enabled = true;
			this->axCommandBars1->Location = System::Drawing::Point(12, 12);
			this->axCommandBars1->Name = L"axCommandBars1";
			this->axCommandBars1->OcxState = (cli::safe_cast<System::Windows::Forms::AxHost::State^  >(resources->GetObject(L"axCommandBars1.OcxState")));
			this->axCommandBars1->Size = System::Drawing::Size(24, 24);
			this->axCommandBars1->TabIndex = 0;
			this->axCommandBars1->ControlNotify += gcnew AxXtremeCommandBars::_DCommandBarsEvents_ControlNotifyEventHandler(this, &FrmMain::axCommandBars1_ControlNotify);
			this->axCommandBars1->Execute += gcnew AxXtremeCommandBars::_DCommandBarsEvents_ExecuteEventHandler(this, &FrmMain::axCommandBars1_Execute);
			this->axCommandBars1->ResizeEvent += gcnew System::EventHandler(this, &FrmMain::axCommandBars1_ResizeEvent);
			// 
			// axDockingPane1
			// 
			this->axDockingPane1->Enabled = true;
			this->axDockingPane1->Location = System::Drawing::Point(42, 12);
			this->axDockingPane1->Name = L"axDockingPane1";
			this->axDockingPane1->OcxState = (cli::safe_cast<System::Windows::Forms::AxHost::State^  >(resources->GetObject(L"axDockingPane1.OcxState")));
			this->axDockingPane1->Size = System::Drawing::Size(24, 24);
			this->axDockingPane1->TabIndex = 1;
			this->axDockingPane1->AttachPaneEvent += gcnew AxXtremeDockingPane::_DDockingPaneEvents_AttachPaneEventHandler(this, &FrmMain::axDockingPane1_AttachPaneEvent);
			this->axDockingPane1->Action += gcnew AxXtremeDockingPane::_DDockingPaneEvents_ActionEventHandler(this, &FrmMain::axDockingPane1_Action);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Black;
			this->pictureBox1->Location = System::Drawing::Point(72, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(24, 24);
			this->pictureBox1->TabIndex = 2;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->MouseLeave += gcnew System::EventHandler(this, &FrmMain::pictureBox1_MouseLeave);
			this->pictureBox1->Click += gcnew System::EventHandler(this, &FrmMain::pictureBox1_Click);
			this->pictureBox1->Resize += gcnew System::EventHandler(this, &FrmMain::pictureBox1_Resize);
			this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &FrmMain::pictureBox1_MouseDown);
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->axProgressBar1);
			this->panel1->Location = System::Drawing::Point(12, 42);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(84, 36);
			this->panel1->TabIndex = 3;
			this->panel1->Visible = false;
			// 
			// axProgressBar1
			// 
			this->axProgressBar1->Location = System::Drawing::Point(12, 12);
			this->axProgressBar1->Name = L"axProgressBar1";
			this->axProgressBar1->OcxState = (cli::safe_cast<System::Windows::Forms::AxHost::State^  >(resources->GetObject(L"axProgressBar1.OcxState")));
			this->axProgressBar1->Size = System::Drawing::Size(58, 12);
			this->axProgressBar1->TabIndex = 1;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->Filter = L"Eightcubed animation files (*.eca)|*.eca|All files(*.*)|*.*";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &FrmMain::openFileDialog1_FileOk);
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->Filter = L"Eightcubed animation files (*.eca)|*.eca|All files(*.*)|*.*";
			this->saveFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &FrmMain::saveFileDialog1_FileOk_1);
			// 
			// FrmMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(965, 532);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->axCommandBars1);
			this->Controls->Add(this->axDockingPane1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"FrmMain";
			this->Text = L"CubeSense";
			this->Load += gcnew System::EventHandler(this, &FrmMain::FrmMain_Load);
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &FrmMain::FrmMain_FormClosing);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->axCommandBars1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->axDockingPane1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->panel1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->axProgressBar1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	public: 
		virtual void WndProc(System::Windows::Forms::Message% ThisMsg) override;

	private:
		FrmScriptSource ^frmScriptSource;
		FrmScriptOutput ^frmScriptOutput;
		FrmFrames ^frmFrames;
		FrmNew ^frmNew;

		XtremeCommandBars::CommandBarComboBox ^Combo ;
		XtremeCommandBars::CommandBarComboBox ^comboLedSize ;
		XtremeCommandBars::CommandBarComboBox ^comboLedSpacing;
		XtremeCommandBars::CommandBarComboBox ^comboBlackLeds;
		XtremeCommandBars::CommandBarComboBox ^comboQuality;
		XtremeCommandBars::RibbonBar ^ribbonBar;

		System::String^ animationFileName;
		int animationFileNameSet;

		void FrmMainCreateRibbonBar()
		{
			int i;
			axCommandBars1->EnableCustomization(true);
			
			XtremeCommandBars::StatusBar ^StatusBar0;
			StatusBar0 =axCommandBars1->StatusBar;
			StatusBar0->Visible=true;

	

			XtremeCommandBars::StatusBarPane ^Pane1;
			XtremeCommandBars::StatusBarPane ^Pane0;
			XtremeCommandBars::StatusBarPane ^Pane2;
			XtremeCommandBars::StatusBarPane ^Pane3;
			XtremeCommandBars::StatusBarPane ^Pane4;
			XtremeCommandBars::StatusBarPane ^Pane5;
			XtremeCommandBars::StatusBarPane ^Pane6;

			Pane0 = StatusBar0->AddPane(IdsStatusBarItems::ITEM_DUMYY);
			Pane1 = StatusBar0->AddPane(IdsStatusBarItems::ITEM_MAIN_STATUS);
			Pane2 = StatusBar0->AddPane(IdsStatusBarItems::ITEM_FPS_OPENGL);
			Pane4 = StatusBar0->AddPane(IdsStatusBarItems::ITEM_ACTIVE_FRAME);
			Pane5 = StatusBar0->AddPane(IdsStatusBarItems::ITEM_LATTICE_SIZE);
			Pane6 = StatusBar0->AddPane(IdsStatusBarItems::ITEM_USB_STATUS);
			Pane3 = StatusBar0->AddPane(IdsStatusBarItems::ITEM_PROGRESS);

			axCommandBars1->StatusBar->Visible = true;

			Pane0->Style= XtremeCommandBars::XTPStatusPaneStyle::SBPS_NOBORDERS;
			Pane0->Width=0;
			Pane0->Visible=0;

			Pane1->Style=XtremeCommandBars::XTPStatusPaneStyle::SBPS_STRETCH | XtremeCommandBars::XTPStatusPaneStyle::SBPS_NOBORDERS;
			Pane1->Text="Ready";
			Pane1->Width=0;
	
			Pane2->Style=  XtremeCommandBars::XTPStatusPaneStyle::SBPS_NOBORDERS;
			Pane2->Text="Fps:";
			Pane2->Width=100;

			Pane3->Handle=axProgressBar1->Handle.ToInt32();
			Pane3->Width=200;

			Pane4->Style=  XtremeCommandBars::XTPStatusPaneStyle::SBPS_NOBORDERS;
			Pane4->Text="Frame:";
			Pane4->Width=100;

			Pane5->Style=  XtremeCommandBars::XTPStatusPaneStyle::SBPS_NOBORDERS;
			Pane5->Text="Lattice:";
			Pane5->Width=100;

			Pane6->Style=  XtremeCommandBars::XTPStatusPaneStyle::SBPS_NOBORDERS;
			Pane6->Text="USB: Ready";
			Pane6->Width=100;

//			Pane3->BackgroundColor=Pane1->BackgroundColor;
//			Pane3->Style=Pane1->Style;

	//		axCommandBars1->StatusBar->AddProgressPane(0);


		
			//axCommandBars1->StatusBar->AddProgressPane()

			ribbonBar = axCommandBars1->AddRibbonBar("The Ribbon");
			ribbonBar->EnableDocking(XtremeCommandBars::XTPToolBarFlags::xtpFlagStretched);

			XtremeCommandBars::CommandBarPopup ^controlFile = ribbonBar->AddSystemButton();
			controlFile->CommandBar->Controls->Add(XtremeCommandBars::XTPControlType::xtpControlButton, IdsRibbonItems::SYSTEM_EXIT, "&Exit", false, false);

			XtremeCommandBars::RibbonTab ^ribbonTabHome = ribbonBar->InsertTab(0, "&Home");
			ribbonTabHome->Id = 4;
			XtremeCommandBars::RibbonGroup ^groupFile = ribbonTabHome->Groups->AddGroup("File", 7);
			groupFile->Add(XtremeCommandBars::XTPControlType::xtpControlButton, IdsRibbonItems::HOME_FILE_NEW, "&New", false, false);
			groupFile->Add(XtremeCommandBars::XTPControlType::xtpControlButton, IdsRibbonItems::HOME_FILE_OPEN, "&Open", false, false);
			groupFile->Add(XtremeCommandBars::XTPControlType::xtpControlButton, IdsRibbonItems::HOME_FILE_SAVE, "&Save", false, false);
			groupFile->Add(XtremeCommandBars::XTPControlType::xtpControlButton, IdsRibbonItems::HOME_FILE_SAVEAS, "&Save as", false, false);


	//		XtremeCommandBars::CommandBarControl^ tempControl;

			XtremeCommandBars::RibbonGroup ^groupParameters = ribbonTabHome->Groups->AddGroup("Parameters", 7);
			groupParameters->Add(XtremeCommandBars::XTPControlType::xtpControlEdit, IdsRibbonItems::HOME_PARAMETERS_TITLE, "&Title: ", false, false);
/*			tempControl->BeginGroup=true;
			tempControl=groupParameters->Add(XtremeCommandBars::XTPControlType::xtpControlLabel, IdsRibbonItems::HOME_PARAMETERS_TITLE, "&X: ", false, false);
			tempControl=groupParameters->Add(XtremeCommandBars::XTPControlType::xtpControlLabel, IdsRibbonItems::HOME_PARAMETERS_TITLE, "&Y: ", false, false);
			tempControl=groupParameters->Add(XtremeCommandBars::XTPControlType::xtpControlLabel, IdsRibbonItems::HOME_PARAMETERS_TITLE, "&Z: ", false, false);
*/

		
			XtremeCommandBars::RibbonTab ^ribbonTabScripting = ribbonBar->InsertTab(1, "&Scripting");
			ribbonTabScripting->Id = 5;
			XtremeCommandBars::RibbonGroup ^groupScriptingFile = ribbonTabScripting->Groups->AddGroup("File", 7);
			groupScriptingFile->Add(XtremeCommandBars::XTPControlType::xtpControlButton, IdsRibbonItems::SCRIPTING_FILE_NEW, "&New", false, false);
			groupScriptingFile->Add(XtremeCommandBars::XTPControlType::xtpControlButton, IdsRibbonItems::SCRIPTING_FILE_OPEN, "&Open", false, false);
			groupScriptingFile->Add(XtremeCommandBars::XTPControlType::xtpControlButton, IdsRibbonItems::SCRIPTING_FILE_SAVE, "&Save", false, false);
			groupScriptingFile->Add(XtremeCommandBars::XTPControlType::xtpControlButton, IdsRibbonItems::SCRIPTING_FILE_SAVEAS, "&Save as", false, false);
			XtremeCommandBars::RibbonGroup ^groupScriptingExecute = ribbonTabScripting->Groups->AddGroup("Prerendered", 7);
			groupScriptingExecute->Add(XtremeCommandBars::XTPControlType::xtpControlButton, IdsRibbonItems::SCRIPTING_EXECUTE_RUN, "&Run", false, false);
			groupScriptingExecute->Add(XtremeCommandBars::XTPControlType::xtpControlButton, IdsRibbonItems::SCRIPTING_EXECUTE_STOP, "&Stop", false, false);
			XtremeCommandBars::RibbonGroup ^groupScriptingRealTime = ribbonTabScripting->Groups->AddGroup("Real time", 7);
			groupScriptingRealTime->Add(XtremeCommandBars::XTPControlType::xtpControlButton, IdsRibbonItems::SCRIPTING_REAL_TIME_PREVIEW, "&Preview", false, false);
			groupScriptingRealTime->Add(XtremeCommandBars::XTPControlType::xtpControlButton, IdsRibbonItems::SCRIPTING_REAL_TIME_EXPORT, "&Export", false, false);
			groupScriptingRealTime->Add(XtremeCommandBars::XTPControlType::xtpControlButton, IdsRibbonItems::SCRIPTING_REAL_TIME_START, "&Start", false, false);
			groupScriptingRealTime->Add(XtremeCommandBars::XTPControlType::xtpControlButton, IdsRibbonItems::SCRIPTING_REAL_TIME_STOP, "&Stop", false, false);


			XtremeCommandBars::RibbonTab ^ribbonTabPreview = ribbonBar->InsertTab(1, "&Preview");
			ribbonTabScripting->Id = 5;
			XtremeCommandBars::RibbonGroup ^groupPreviewPlayback = ribbonTabPreview->Groups->AddGroup("Playback", 7);
			groupPreviewPlayback->Add(XtremeCommandBars::XTPControlType::xtpControlButton, IdsRibbonItems::PREVIEW_PLAYBACK_PLAY, "Play", false, false);
			groupPreviewPlayback->Add(XtremeCommandBars::XTPControlType::xtpControlButton, IdsRibbonItems::PREVIEW_PLAYBACK_STOP, "Stop", false, false);
			groupPreviewPlayback->Add(XtremeCommandBars::XTPControlType::xtpControlLabel, IdsRibbonItems::DUMMY, "", false, false);
			groupPreviewPlayback->Add(XtremeCommandBars::XTPControlType::xtpControlCheckBox, IdsRibbonItems::PREVIEW_PLAYBACK_REPEAT, "Repeat", false, false);
			groupPreviewPlayback->Add(XtremeCommandBars::XTPControlType::xtpControlCheckBox, IdsRibbonItems::PREVIEW_PLAYBACK_SELECTION, "Selection only", false, false);
			XtremeCommandBars::RibbonGroup ^groupPreviewEightcubed = ribbonTabPreview->Groups->AddGroup("eightCubed", 7);
			groupPreviewEightcubed->Add(XtremeCommandBars::XTPControlType::xtpControlButton, IdsRibbonItems::PREVIEW_EIGHTCUBED_CONNECT, "Connect", false, false);
			groupPreviewEightcubed->Add(XtremeCommandBars::XTPControlType::xtpControlButton, IdsRibbonItems::PREVIEW_EIGHTCUBED_DISCONNECT, "Disconnect", false, false);
			groupPreviewEightcubed->Add(XtremeCommandBars::XTPControlType::xtpControlCheckBox, IdsRibbonItems::PREVIEW_EIGHTCUBED_STREAM, "Stream video", false, false);

			//
			XtremeCommandBars::CommandBarGallery ^GallerySize;
			XtremeCommandBars::CommandBarGalleryItems ^ItemsSize;

			ItemsSize = axCommandBars1->CreateGalleryItems(IdsRibbonItems::SCRIPTING_EXECUTE_TYPE);
			ItemsSize->ItemWidth = 0;
			ItemsSize->ItemHeight = 17;
			ItemsSize->AddItem(1, "VB script");
			ItemsSize->AddItem(2, "C# script");

			Combo = (XtremeCommandBars::CommandBarComboBox^)groupScriptingExecute->Add(XtremeCommandBars::XTPControlType::xtpControlComboBox, IdsRibbonItems::SCRIPTING_EXECUTE_TYPE, "", false, false);
			Combo->DropDownListStyle = true;
			Combo->Width = 100;
//			Combo->Text = "C# script";
			Combo->DropDownListStyle=0;

			XtremeCommandBars::CommandBar ^ComboPopup;

			ComboPopup = axCommandBars1->Add("Combo Popup", XtremeCommandBars::XTPBarPosition::xtpBarComboBoxGalleryPopup);
			GallerySize = (XtremeCommandBars::CommandBarGallery^)ComboPopup->Controls->Add(XtremeCommandBars::XTPControlType::xtpControlGallery, IdsRibbonItems::SCRIPTING_EXECUTE_TYPE, "", -1, false);
			GallerySize->Width = 90;
			GallerySize->Height = 2 * 17;

			GallerySize->Items = ItemsSize;
			Combo->CommandBar = ComboPopup;
			Combo->ListIndex=2;

			//

			XtremeCommandBars::RibbonTab ^ribbonTabView = ribbonBar->InsertTab(1, "&View");
			ribbonTabView->Id = 5;
			XtremeCommandBars::RibbonGroup ^groupViewPresets = ribbonTabView->Groups->AddGroup("Presets", 7);
			groupViewPresets->Add(XtremeCommandBars::XTPControlType::xtpControlButton, IdsRibbonItems::VIEW_PRESETS_XZ, "XZ View", false, false);
			groupViewPresets->Add(XtremeCommandBars::XTPControlType::xtpControlButton, IdsRibbonItems::VIEW_PRESETS_XY, "XY View", false, false);
			groupViewPresets->Add(XtremeCommandBars::XTPControlType::xtpControlButton, IdsRibbonItems::VIEW_PRESETS_YZ, "YZ View", false, false);
			groupViewPresets->Add(XtremeCommandBars::XTPControlType::xtpControlButton, IdsRibbonItems::VIEW_PRESETS_DEFAULT, "Default view", false, false);
			XtremeCommandBars::RibbonGroup ^groupViewItems = ribbonTabView->Groups->AddGroup("Items", 7);
			groupViewItems->Add(XtremeCommandBars::XTPControlType::xtpControlCheckBox, IdsRibbonItems::VIEW_ITEMS_LATTICE, "Lattice", false, false);
//			groupViewItems->Add(XtremeCommandBars::XTPControlType::xtpControlCheckBox, IdsRibbonItems::VIEW_ITEMS_BASE, "Base", false, false);
			groupViewItems->Add(XtremeCommandBars::XTPControlType::xtpControlCheckBox, IdsRibbonItems::VIEW_ITEMS_AXIS, "Axis", false, false);
			XtremeCommandBars::RibbonGroup ^groupViewLattice = ribbonTabView->Groups->AddGroup("Lattice", 7);
			XtremeCommandBars::RibbonGroup ^groupViewSettings = ribbonTabView->Groups->AddGroup("Settings", 7);
	
			
			XtremeCommandBars::CommandBarGallery ^galleryLedSize;
			XtremeCommandBars::CommandBarGalleryItems ^itemsLedSize;
			XtremeCommandBars::CommandBar ^popupLedSize;
			itemsLedSize = axCommandBars1->CreateGalleryItems(IdsRibbonItems::VIEW_LATTICE_SIZE);
			itemsLedSize->ItemWidth = 0;
			itemsLedSize->ItemHeight = 17;
			for(i=0;i<21;i++)
				itemsLedSize->AddItem(1, System::Convert::ToString(i)+" mm");
			comboLedSize = (XtremeCommandBars::CommandBarComboBox^)groupViewLattice->Add(XtremeCommandBars::XTPControlType::xtpControlComboBox, IdsRibbonItems::VIEW_LATTICE_SIZE, "", false, false);
			comboLedSize->Width = 150;
			comboLedSize->DropDownListStyle=0;
			popupLedSize = axCommandBars1->Add("Combo Popup", XtremeCommandBars::XTPBarPosition::xtpBarComboBoxGalleryPopup);
			galleryLedSize = (XtremeCommandBars::CommandBarGallery^)popupLedSize->Controls->Add(XtremeCommandBars::XTPControlType::xtpControlGallery, IdsRibbonItems::VIEW_LATTICE_SIZE, "", -1, false);
			galleryLedSize->Width = 146;
			galleryLedSize->Height = 21 * 17;
			galleryLedSize->Items = itemsLedSize;
			comboLedSize->CommandBar = popupLedSize;
			comboLedSize->Caption="LED size:";
			comboLedSize->ListIndex=1;
			
			XtremeCommandBars::CommandBarGallery ^galleryLedSpacing;
			XtremeCommandBars::CommandBarGalleryItems ^itemsLedSpacing;
			XtremeCommandBars::CommandBar ^popupLedSpacing;
			itemsLedSpacing = axCommandBars1->CreateGalleryItems(IdsRibbonItems::VIEW_LATTICE_SPACING);
			itemsLedSpacing->ItemWidth = 0;
			itemsLedSpacing->ItemHeight = 17;
			for(i=0;i<62;i+=2)
				itemsLedSpacing->AddItem(1, System::Convert::ToString(i)+" mm");
			comboLedSpacing = (XtremeCommandBars::CommandBarComboBox^)groupViewLattice->Add(XtremeCommandBars::XTPControlType::xtpControlComboBox, IdsRibbonItems::VIEW_LATTICE_SPACING, "", false, false);
			comboLedSpacing->Width = 150;
			comboLedSpacing->DropDownListStyle=0;
			popupLedSpacing = axCommandBars1->Add("Combo Popup", XtremeCommandBars::XTPBarPosition::xtpBarComboBoxGalleryPopup);
			galleryLedSpacing = (XtremeCommandBars::CommandBarGallery^)popupLedSpacing->Controls->Add(XtremeCommandBars::XTPControlType::xtpControlGallery, IdsRibbonItems::VIEW_LATTICE_SPACING, "", -1, false);
			galleryLedSpacing->Width = 146;
			galleryLedSpacing->Height = 31 * 17;
			galleryLedSpacing->Items = itemsLedSpacing;
			comboLedSpacing->CommandBar = popupLedSpacing;
			comboLedSpacing->Caption="LED spacing:";
			comboLedSpacing->ListIndex=1;

			XtremeCommandBars::CommandBarGallery ^galleryBlackLeds;
			XtremeCommandBars::CommandBarGalleryItems ^itemsBlackLeds;
			XtremeCommandBars::CommandBar ^popupBlackLeds;
			itemsBlackLeds = axCommandBars1->CreateGalleryItems(IdsRibbonItems::VIEW_LATTICE_BLACK_AS);
			itemsBlackLeds->ItemWidth = 0;
			itemsBlackLeds->ItemHeight = 17;
			itemsBlackLeds->AddItem(1, "Invisible");
			itemsBlackLeds->AddItem(1, "Black");
			itemsBlackLeds->AddItem(1, "Grey");
			comboBlackLeds = (XtremeCommandBars::CommandBarComboBox^)groupViewLattice->Add(XtremeCommandBars::XTPControlType::xtpControlComboBox, IdsRibbonItems::VIEW_LATTICE_BLACK_AS, "", false, false);
			comboBlackLeds->Width = 150;
			comboBlackLeds->DropDownListStyle=0;
			popupBlackLeds = axCommandBars1->Add("Combo Popup", XtremeCommandBars::XTPBarPosition::xtpBarComboBoxGalleryPopup);
			galleryBlackLeds = (XtremeCommandBars::CommandBarGallery^)popupBlackLeds->Controls->Add(XtremeCommandBars::XTPControlType::xtpControlGallery, IdsRibbonItems::VIEW_LATTICE_BLACK_AS, "", -1, false);
			galleryBlackLeds->Width = 146;
			galleryBlackLeds->Height = 3 * 17;
			galleryBlackLeds->Items = itemsBlackLeds;
			comboBlackLeds->CommandBar = popupBlackLeds;
			comboBlackLeds->Caption="Black LEDs as:";
			comboBlackLeds->ListIndex=1;

			XtremeCommandBars::CommandBarGallery ^galleryQuality;
			XtremeCommandBars::CommandBarGalleryItems ^itemsQuality;
			XtremeCommandBars::CommandBar ^popupQuality;
			itemsQuality = axCommandBars1->CreateGalleryItems(IdsRibbonItems::VIEW_SETTINGS_QUALITY);
			itemsQuality->ItemWidth = 0;
			itemsQuality->ItemHeight = 17;
			itemsQuality->AddItem(1, "High");
			itemsQuality->AddItem(1, "Medium");
			itemsQuality->AddItem(1, "Low");
			itemsQuality->AddItem(1, "Very low");
			comboQuality = (XtremeCommandBars::CommandBarComboBox^)groupViewSettings->Add(XtremeCommandBars::XTPControlType::xtpControlComboBox, IdsRibbonItems::VIEW_SETTINGS_QUALITY, "", false, false);
			comboQuality->Width = 150;
			comboQuality->DropDownListStyle=0;
			popupQuality = axCommandBars1->Add("Combo Popup", XtremeCommandBars::XTPBarPosition::xtpBarComboBoxGalleryPopup);
			galleryQuality = (XtremeCommandBars::CommandBarGallery^)popupQuality->Controls->Add(XtremeCommandBars::XTPControlType::xtpControlGallery, IdsRibbonItems::VIEW_SETTINGS_QUALITY, "", -1, false);
			galleryQuality->Width = 146;
			galleryQuality->Height = 4 * 17;
			galleryQuality->Items = itemsQuality;
			comboQuality->CommandBar = popupQuality;
			comboQuality->Caption="Quality";
			comboQuality->ListIndex=1;


			XtremeCommandBars::RibbonTab ^ribbonTabSettings = ribbonBar->InsertTab(1, "&Settings");
			ribbonTabView->Id = 5;
			XtremeCommandBars::RibbonGroup ^groupSettingsPanes = ribbonTabSettings->Groups->AddGroup("Panes", 7);
			groupSettingsPanes->Add(XtremeCommandBars::XTPControlType::xtpControlCheckBox, IdsRibbonItems::SETTINGS_PANES_FRAMES, "Frames", false, false);
			groupSettingsPanes->Add(XtremeCommandBars::XTPControlType::xtpControlCheckBox, IdsRibbonItems::SETTINGS_PANES_SCRIPT_SOURCE, "Script source", false, false);
			groupSettingsPanes->Add(XtremeCommandBars::XTPControlType::xtpControlCheckBox, IdsRibbonItems::SETTINGS_PANES_SCRIPT_OUTPUT, "Script output", false, false);

			/*   
			CResource oRes ;
			oRes.Init "C:\The path to MyResourceDLL.dll"
			ImageManager1.Icons.LoadBitmapFromResource oRes.hModule, 1000, IDS(), xtpImageNormal
			Set oRes = Nothing

			axCommandBars1->Icons->LoadBitmapFromResource("F:\\Lumisense\\eigthCubed\\Software\\CubeSense\\iconMain3.png", 777, XtremeCommandBars::XTPImageState::xtpImageNormal);

			controlFile->IconId = 777;
		*/

		}

		void FrmMainInitDockingPanes()
		{
			XtremeDockingPane::Pane ^paneA=axDockingPane1->CreatePane(IdsDockingPanel::PANEL_SCRIPT_SOURCE,500,280,XtremeDockingPane::DockingDirection::DockRightOf);
			paneA->Title="Script source";
			paneA->MinTrackSize->Width=500;
			paneA->MinTrackSize->Height=280;

			XtremeDockingPane::Pane ^paneB=axDockingPane1->CreatePane(IdsDockingPanel::PANEL_FRAMES,120,280,XtremeDockingPane::DockingDirection::DockLeftOf);
			paneB->Title="Frame list";
			paneB->MinTrackSize->Width=80;
			paneB->MinTrackSize->Height=280;
			axDockingPane1->VisualTheme=XtremeDockingPane::VisualTheme::ThemeOffice2007;

			XtremeDockingPane::Pane ^paneC=axDockingPane1->CreatePane(IdsDockingPanel::PANEL_SCRIPT_OUTPUT,120,100,XtremeDockingPane::DockingDirection::DockBottomOf);
			paneC->Title="Script output";
			paneC->MinTrackSize->Width=120;
			paneC->MinTrackSize->Height=100;
			axDockingPane1->VisualTheme=XtremeDockingPane::VisualTheme::ThemeOffice2007;

			axDockingPane1->Options->AlphaDockingContext = true;
			axDockingPane1->Options->ShowDockingContextStickers = true;
		}

	private: System::Void FrmMain_Load(System::Object^  sender, System::EventArgs^  e)
		{

			logEvent(LOG_THREAD_DEFAULT, "Main form load event handler entered");

			FrmMainCreateRibbonBar();
	
			logEvent(LOG_THREAD_DEFAULT, "Ribbon bar created");

			FrmMainInitDockingPanes();

			logEvent(LOG_THREAD_DEFAULT, "Docking panes created");


			((XtremeCommandBars::RibbonBar^)axCommandBars1->ActiveMenuBar)->EnableFrameTheme();

			axDockingPane1->SetCommandBars (axCommandBars1->GetDispatch());
			axDockingPane1->Options->ThemedFloatingFrames = true;
			axDockingPane1->VisualTheme = XtremeDockingPane::VisualTheme::ThemeOffice2003;

			frmNew=gcnew FrmNew();
			frmNew->Visible=false;
			frmNew->Initialize();

			logEvent(LOG_THREAD_DEFAULT, "Form for new animations created");

			handlerFrmMainLoad(this->Handle.ToInt32(), this->pictureBox1->Handle.ToInt32(),frmFrames->Handle.ToInt32(),frmScriptSource->Handle.ToInt32());
		
			comboQuality->ListIndex=handlerRenderQuality;
			comboLedSize->ListIndex=handlerLedSize+1;
			comboLedSpacing->ListIndex=(handlerLedSpacing/2)+1;
			comboBlackLeds->ListIndex=handlerBlackLeds;
			ribbonBar->FindControl(XTPControlType::xtpControlCheckBox,IdsRibbonItems::VIEW_ITEMS_AXIS,0,0)->Checked=handlerShowAxis;
//			ribbonBar->FindControl(XTPControlType::xtpControlCheckBox,IdsRibbonItems::VIEW_ITEMS_BASE,0,0)->Checked=handlerShowBase;
			ribbonBar->FindControl(XTPControlType::xtpControlCheckBox,IdsRibbonItems::VIEW_ITEMS_LATTICE,0,0)->Checked=handlerShowLattice;
			ribbonBar->FindControl(XTPControlType::xtpControlCheckBox,IdsRibbonItems::SETTINGS_PANES_FRAMES,0,0)->Checked=1;
			ribbonBar->FindControl(XTPControlType::xtpControlCheckBox,IdsRibbonItems::SETTINGS_PANES_SCRIPT_OUTPUT,0,0)->Checked=1;
			ribbonBar->FindControl(XTPControlType::xtpControlCheckBox,IdsRibbonItems::SETTINGS_PANES_SCRIPT_SOURCE,0,0)->Checked=1;

	
			((CommandBarEdit^)ribbonBar->FindControl(XTPControlType::xtpControlEdit,IdsRibbonItems::HOME_PARAMETERS_TITLE,0,0))->TextLimit=20;
			((CommandBarEdit^)ribbonBar->FindControl(XTPControlType::xtpControlEdit,IdsRibbonItems::HOME_PARAMETERS_TITLE,0,0))->EditHint="Enter title here";
			(ribbonBar->FindControl(XTPControlType::xtpControlEdit,IdsRibbonItems::HOME_PARAMETERS_TITLE,0,0))->Width=180;

			logEvent(LOG_THREAD_DEFAULT, "Default values for main form components set");

			animationFileName="animation.eca";
			
//		Control.EditHint = "Enter You Text Here"


			/*handlerShowBase=0;
			handlerShowAxis=1;
			handlerShowLattice=1;*/
	
		}
	private: System::Void axDockingPane1_AttachPaneEvent(System::Object^  sender, AxXtremeDockingPane::_DDockingPaneEvents_AttachPaneEvent^  e)
		{
			if (e->item->Id==IdsDockingPanel::PANEL_FRAMES)
			{
				frmFrames=gcnew FrmFrames;
				e->item->Handle=frmFrames->Handle.ToInt32();
				return;
			}
			if (e->item->Id==IdsDockingPanel::PANEL_SCRIPT_SOURCE)
			{
				frmScriptSource=gcnew FrmScriptSource;
				e->item->Handle=frmScriptSource->Handle.ToInt32();
				frmScriptSource->FrmScriptSourceInit();
				return;
			}
			if (e->item->Id==IdsDockingPanel::PANEL_SCRIPT_OUTPUT)
			{
				frmScriptOutput=gcnew FrmScriptOutput;
				e->item->Handle=frmScriptOutput->Handle.ToInt32();
				wndprocFrmScriptOutputHandle=frmScriptOutput->Handle.ToInt32();
				return;
			}
		}
private: System::Void axCommandBars1_ResizeEvent(System::Object^  sender, System::EventArgs^  e)
		{
			int left = 0;
			int top = 0;
			int right = 0;
			int bottom = 0;
			axCommandBars1->GetClientRect(left, top, right, bottom);
			pictureBox1->SetBounds(left + 2, top + 2, right - left - 2, bottom - top - 2);
		

		}
private: System::Void FrmMain_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
		{
			handlerFrmMainFormClosing();


		}
private: System::Void axCommandBars1_Execute(System::Object^  sender, AxXtremeCommandBars::_DCommandBarsEvents_ExecuteEvent^  e)
		{
			int r;
			switch (e->control->Id)
			{
				case IdsRibbonItems::SYSTEM_EXIT:
					this->Close();		
					break;
				case IdsRibbonItems::HOME_FILE_NEW:
					r=handlerAskAboutSavingAnimation();
					if (r==6)
					{
						handlerCreatingAnimation=1;
						if (animationFileNameSet==0)
							this->saveFileDialog1->ShowDialog();
						else
						{
							handlerSaveAnimationFile=1;
							Marshal::FreeHGlobal((System::IntPtr)(void*)handlerSaveAnimationFileName);
							handlerSaveAnimationFileName = (char*)(void*)Marshal::StringToHGlobalAnsi(animationFileName);
							handlerSaveAnimationFileNameLength=animationFileName->Length;
							Marshal::FreeHGlobal((System::IntPtr)(void*)handlerAnimationTitle);
							handlerAnimationTitle = (char*)(void*)Marshal::StringToHGlobalAnsi(((CommandBarEdit^)ribbonBar->FindControl(XTPControlType::xtpControlEdit,IdsRibbonItems::HOME_PARAMETERS_TITLE,0,0))->Text);
							handlerAnimationTitleLength=((CommandBarEdit^)ribbonBar->FindControl(XTPControlType::xtpControlEdit,IdsRibbonItems::HOME_PARAMETERS_TITLE,0,0))->Text->Length;
							threadCopyContentDefaultCoreIn();
							handlerDisableMainForm();
							frmNew->Visible=true;	
	
						}
					}
					if (r==7)
					{
						handlerDisableMainForm();
						frmNew->Visible=true;						
					}

					break;
				case IdsRibbonItems::SCRIPTING_EXECUTE_RUN:
					frmScriptSource->copyScriptSource();
					threadCopyContentDefaultCoreIn();
					break;
				case IdsRibbonItems::SCRIPTING_EXECUTE_STOP:
					handlerStopScript=1;
					threadCopyContentDefaultCoreIn();
					break;
				case IdsRibbonItems::SCRIPTING_REAL_TIME_PREVIEW:
					frmScriptSource->copyRealTimeScriptSource();
					threadCopyContentDefaultCoreIn();
					break;
				case IdsRibbonItems::SCRIPTING_REAL_TIME_EXPORT:
					//handlerRealTimePlaying=!handlerRealTimePlaying;
					//threadCopyContentDefaultCoreIn();
					break;
				case IdsRibbonItems::SCRIPTING_REAL_TIME_START:
					handlerRealTimeCommand=1;
					threadCopyContentDefaultCoreIn();
					break;
				case IdsRibbonItems::SCRIPTING_REAL_TIME_STOP:
					handlerRealTimeCommand=2;
					threadCopyContentDefaultCoreIn();
					break;

				case IdsRibbonItems::SCRIPTING_FILE_NEW:
					frmScriptSource->createNewScript();
					break;
				case IdsRibbonItems::SCRIPTING_FILE_SAVE:
					frmScriptSource->saveScript();
					break;
				case IdsRibbonItems::SCRIPTING_FILE_SAVEAS:
					frmScriptSource->saveScriptAs();
					break;
				case IdsRibbonItems::SCRIPTING_FILE_OPEN:
					frmScriptSource->openScript();
					break;

				case IdsRibbonItems::SCRIPTING_EXECUTE_TYPE:
					if (!System::String::Compare(Combo->Text,"VB script"))
						frmScriptSource->changeScriptType(SCRIPT_TYPE_VB);
					if (!System::String::Compare(Combo->Text,"C# script"))
						frmScriptSource->changeScriptType(SCRIPT_TYPE_CS);
/*					if (!System::String::Compare(Combo->Text,"C (real-time)"))
						frmScriptSource->changeScriptType(SCRIPT_TYPE_CRT);
*/
				case IdsRibbonItems::VIEW_LATTICE_SIZE:
					handlerLedSize=comboLedSize->ListIndex-1;
					threadCopyContentDefaultOpenglIn();
					break;
				case IdsRibbonItems::VIEW_LATTICE_SPACING:
					handlerLedSpacing=(comboLedSpacing->ListIndex-1)*2;
					threadCopyContentDefaultOpenglIn();
					break;
				case IdsRibbonItems::VIEW_LATTICE_BLACK_AS:
					handlerBlackLeds=comboBlackLeds->ListIndex;
					threadCopyContentDefaultOpenglIn();
					break;
				case IdsRibbonItems::VIEW_SETTINGS_QUALITY:
					handlerRenderQuality=comboQuality->ListIndex;
					threadCopyContentDefaultOpenglIn();
					break;
				case IdsRibbonItems::VIEW_ITEMS_AXIS:
					e->control->Checked = !e->control->Checked;
					handlerShowAxis=e->control->Checked;
					threadCopyContentDefaultOpenglIn();
					break;
				case IdsRibbonItems::VIEW_ITEMS_BASE:
					e->control->Checked = !e->control->Checked;
					handlerShowBase=e->control->Checked;
					threadCopyContentDefaultOpenglIn();
					break;
				case IdsRibbonItems::VIEW_ITEMS_LATTICE:
					e->control->Checked = !e->control->Checked;
					handlerShowLattice=e->control->Checked;
					threadCopyContentDefaultOpenglIn();
					break;
				case IdsRibbonItems::VIEW_PRESETS_XY:
					handlerPresetView=4;
					threadCopyContentDefaultCoreIn();
					break;
				case IdsRibbonItems::VIEW_PRESETS_XZ:
					handlerPresetView=2;
					threadCopyContentDefaultCoreIn();
					break;
				case IdsRibbonItems::VIEW_PRESETS_YZ:
					handlerPresetView=3;
					threadCopyContentDefaultCoreIn();
					break;
				case IdsRibbonItems::VIEW_PRESETS_DEFAULT:
					handlerPresetView=1;
					threadCopyContentDefaultCoreIn();
					break;
				case IdsRibbonItems::SETTINGS_PANES_FRAMES:
					e->control->Checked = !e->control->Checked;
					if (e->control->Checked)
						axDockingPane1->ShowPane(IdsDockingPanel::PANEL_FRAMES);
					else
						axDockingPane1->FindPane(IdsDockingPanel::PANEL_FRAMES)->Close();
					break;
				case IdsRibbonItems::SETTINGS_PANES_SCRIPT_OUTPUT:
					e->control->Checked = !e->control->Checked;
					if (e->control->Checked)
						axDockingPane1->ShowPane(IdsDockingPanel::PANEL_SCRIPT_OUTPUT);
					else
						axDockingPane1->FindPane(IdsDockingPanel::PANEL_SCRIPT_OUTPUT)->Close();
					break;
				case IdsRibbonItems::SETTINGS_PANES_SCRIPT_SOURCE:
					e->control->Checked = !e->control->Checked;
					if (e->control->Checked)
						axDockingPane1->ShowPane(IdsDockingPanel::PANEL_SCRIPT_SOURCE);
					else
						axDockingPane1->FindPane(IdsDockingPanel::PANEL_SCRIPT_SOURCE)->Close();
					break;
				case IdsRibbonItems::PREVIEW_PLAYBACK_PLAY:
					handlerPlaybackCommand=1;
					threadCopyContentDefaultCoreIn();
					break;
				case IdsRibbonItems::PREVIEW_PLAYBACK_STOP:
					handlerPlaybackCommand=2;
					threadCopyContentDefaultCoreIn();
					break;
				case IdsRibbonItems::PREVIEW_PLAYBACK_REPEAT:
					e->control->Checked = !e->control->Checked;
					if (e->control->Checked)
						handlerPlaybackCommand=3;
					else
						handlerPlaybackCommand=4;
					threadCopyContentDefaultCoreIn();
					break;
				case IdsRibbonItems::PREVIEW_PLAYBACK_SELECTION:
					e->control->Checked = !e->control->Checked;
					if (e->control->Checked)
						handlerPlaybackCommand=5;
					else
						handlerPlaybackCommand=6;
					threadCopyContentDefaultCoreIn();
					break;
				case IdsRibbonItems::PREVIEW_EIGHTCUBED_CONNECT:
					handlerUsbControl=1;
					threadCopyContentDefaultUsbIn();
					break;
				case IdsRibbonItems::PREVIEW_EIGHTCUBED_DISCONNECT:
					handlerUsbControl=2;
					threadCopyContentDefaultUsbIn();
					break;
				case IdsRibbonItems::PREVIEW_EIGHTCUBED_STREAM:
					e->control->Checked = !e->control->Checked;
					handlerUsbControl=3+e->control->Checked;
					threadCopyContentDefaultUsbIn();
				break;
				case IdsRibbonItems::HOME_FILE_OPEN:
					r=handlerAskAboutSavingAnimation();
					if (r==6)
					{
						handlerOpeningAnimation=1;
						if (animationFileNameSet==0)
							this->saveFileDialog1->ShowDialog();
						else
						{
							handlerSaveAnimationFile=1;
							Marshal::FreeHGlobal((System::IntPtr)(void*)handlerSaveAnimationFileName);
							handlerSaveAnimationFileName = (char*)(void*)Marshal::StringToHGlobalAnsi(animationFileName);
							handlerSaveAnimationFileNameLength=animationFileName->Length;
							Marshal::FreeHGlobal((System::IntPtr)(void*)handlerAnimationTitle);
							handlerAnimationTitle = (char*)(void*)Marshal::StringToHGlobalAnsi(((CommandBarEdit^)ribbonBar->FindControl(XTPControlType::xtpControlEdit,IdsRibbonItems::HOME_PARAMETERS_TITLE,0,0))->Text);
							handlerAnimationTitleLength=((CommandBarEdit^)ribbonBar->FindControl(XTPControlType::xtpControlEdit,IdsRibbonItems::HOME_PARAMETERS_TITLE,0,0))->Text->Length;
							threadCopyContentDefaultCoreIn();
							this->openFileDialog1->ShowDialog();
						}
					}
					if (r==7)
						this->openFileDialog1->ShowDialog();
					break;

				case IdsRibbonItems::HOME_FILE_SAVEAS:
						saveFileDialog1->ShowDialog();
					break;

				case IdsRibbonItems::HOME_FILE_SAVE:
						if (animationFileNameSet==0)
							this->saveFileDialog1->ShowDialog();
						else
						{
							handlerSaveAnimationFile=1;
							Marshal::FreeHGlobal((System::IntPtr)(void*)handlerSaveAnimationFileName);
							handlerSaveAnimationFileName = (char*)(void*)Marshal::StringToHGlobalAnsi(animationFileName);
							handlerSaveAnimationFileNameLength=animationFileName->Length;
							Marshal::FreeHGlobal((System::IntPtr)(void*)handlerAnimationTitle);
							handlerAnimationTitle = (char*)(void*)Marshal::StringToHGlobalAnsi(((CommandBarEdit^)ribbonBar->FindControl(XTPControlType::xtpControlEdit,IdsRibbonItems::HOME_PARAMETERS_TITLE,0,0))->Text);
							handlerAnimationTitleLength=((CommandBarEdit^)ribbonBar->FindControl(XTPControlType::xtpControlEdit,IdsRibbonItems::HOME_PARAMETERS_TITLE,0,0))->Text->Length;
							threadCopyContentDefaultCoreIn();

						}

					break;
			}

		}
private: System::Void pictureBox1_Resize(System::Object^  sender, System::EventArgs^  e) {
			 handlerPictureBox1Resize(pictureBox1->Height, pictureBox1->Width);

		 }
private: System::Void axDockingPane1_Action(System::Object^  sender, AxXtremeDockingPane::_DDockingPaneEvents_ActionEvent^  e) {
			int id;
			id=e->pane->Id;
			if (e->action==XtremeDockingPane::DockingPaneAction::PaneActionClosed)
			{
				if (id==IdsDockingPanel::PANEL_FRAMES)
					ribbonBar->FindControl(XTPControlType::xtpControlCheckBox,IdsRibbonItems::SETTINGS_PANES_FRAMES,0,0)->Checked=0;
				if (id==IdsDockingPanel::PANEL_SCRIPT_OUTPUT)
					ribbonBar->FindControl(XTPControlType::xtpControlCheckBox,IdsRibbonItems::SETTINGS_PANES_SCRIPT_OUTPUT,0,0)->Checked=0;
				if (id==IdsDockingPanel::PANEL_SCRIPT_SOURCE)
					ribbonBar->FindControl(XTPControlType::xtpControlCheckBox,IdsRibbonItems::SETTINGS_PANES_SCRIPT_SOURCE,0,0)->Checked=0;
			
			}
		 }
private: System::Void pictureBox1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				if ((e->Button==System::Windows::Forms::MouseButtons::Right)|
					(e->Button==System::Windows::Forms::MouseButtons::Left))
				{
					handlerCanvasActive=1;
					threadCopyContentDefaultCoreIn();
					pictureBox1->Focus();

					
				}

		 }
private: System::Void pictureBox1_MouseLeave(System::Object^  sender, System::EventArgs^  e) {

				handlerCanvasActive=0;
				threadCopyContentDefaultCoreIn();

		 }
private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void listBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void axCommandBars1_ControlNotify(System::Object^  sender, AxXtremeCommandBars::_DCommandBarsEvents_ControlNotifyEvent^  e) {

		 }
private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			handlerOpenAnimationFile=1;
			Marshal::FreeHGlobal((System::IntPtr)(void*)handlerOpenAnimationFileName);
			handlerOpenAnimationFileName = (char*)(void*)Marshal::StringToHGlobalAnsi(openFileDialog1->FileName);
			handlerOpenAnimationFileNameLength=openFileDialog1->FileName->Length;
			animationFileName=openFileDialog1->FileName;
			animationFileNameSet=1;
			handlerOpeningAnimation=0;
			threadCopyContentDefaultCoreIn();

		 }
private: System::Void saveFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {


		 }
private: System::Void saveFileDialog1_FileOk_1(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			handlerSaveAnimationFile=1;
			Marshal::FreeHGlobal((System::IntPtr)(void*)handlerSaveAnimationFileName);
			handlerSaveAnimationFileName = (char*)(void*)Marshal::StringToHGlobalAnsi(saveFileDialog1->FileName);
			handlerSaveAnimationFileNameLength=saveFileDialog1->FileName->Length;
			animationFileName=saveFileDialog1->FileName;
			animationFileNameSet=1;
			Marshal::FreeHGlobal((System::IntPtr)(void*)handlerAnimationTitle);
			handlerAnimationTitle = (char*)(void*)Marshal::StringToHGlobalAnsi(((CommandBarEdit^)ribbonBar->FindControl(XTPControlType::xtpControlEdit,IdsRibbonItems::HOME_PARAMETERS_TITLE,0,0))->Text);
			handlerAnimationTitleLength=((CommandBarEdit^)ribbonBar->FindControl(XTPControlType::xtpControlEdit,IdsRibbonItems::HOME_PARAMETERS_TITLE,0,0))->Text->Length;
			threadCopyContentDefaultCoreIn();
			if (handlerCreatingAnimation)
			{
				handlerDisableMainForm();
				frmNew->Visible=true;	
			}
			if (handlerOpeningAnimation)
				openFileDialog1->ShowDialog();

		 }
};
}
