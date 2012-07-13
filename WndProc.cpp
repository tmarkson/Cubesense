#include "stdafx.h"
#include "includeall.h"

#include "windows.h"
#include <cstdio>

#include "FrmMain.h"

using namespace CubeSense;
int wndprocFrmMainHandle;
int wndprocFrmScriptOutputHandle;
int wndprocFrmScriptSourceHandle;
int wndprocMouseWheel;

int wndprocMessages[10];

void FrmMain::WndProc(System::Windows::Forms::Message %ThisMsg)
{
	char tc[1024];
	if (ThisMsg.Msg == WM_MOUSEWHEEL)
	{
		wndprocMouseWheel=HIWORD((int)ThisMsg.WParam);
		threadCopyContentDefaultCoreIn();
	}
	if (ThisMsg.Msg == wndprocMessages[0])
	{	
		if (((int)ThisMsg.WParam)==WNDPROC_MESSAGE0_SHOW_DEBUG_PARAM_1)
		{

			sprintf_s(&tc[0], 20,"%i", (int)ThisMsg.LParam);
	//		toolStripStatusLabel1->Text=gcnew String(tc);

		}
	}
/*	if (ThisMsg.Msg == wndprocMessages[0])
	{	
		if (((int)ThisMsg.WParam)==WNDPROC_MESSAGE0_SHOW_DEBUG_PARAM_2)
		{

			sprintf_s(&tc[0], 20,"%i", (int)ThisMsg.LParam);
			toolStripStatusLabel2->Text=gcnew String(tc);

		}
	}*/
	if (ThisMsg.Msg == wndprocMessages[0])
	{	
		if (((int)ThisMsg.WParam)==WNDPROC_MESSAGE0_SHOW_OPENGL_FPS)
		{

			sprintf_s(&tc[0], 20,"FPS: %i", (int)ThisMsg.LParam);
			axCommandBars1->StatusBar->FindPane(IdsStatusBarItems::ITEM_FPS_OPENGL)->Text=gcnew String(tc);
		

		}
	}	
	if (ThisMsg.Msg == wndprocMessages[0])
	{	
		if (((int)ThisMsg.WParam)==WNDPROC_MESSAGE0_SHOW_ANIMATION_TITLE)
		{
			((CommandBarEdit^)ribbonBar->FindControl(XTPControlType::xtpControlEdit,IdsRibbonItems::HOME_PARAMETERS_TITLE,0,0))->Text=gcnew String(latticeAnimationTitle);
		}
	}
	if (ThisMsg.Msg == wndprocMessages[0])
	{	
		if (((int)ThisMsg.WParam)==WNDPROC_MESSAGE0_NO_ANIMATION_FILE_NAME)
		{
			animationFileName="";
			animationFileNameSet=0;
		}
	}
	if (ThisMsg.Msg == wndprocMessages[0])
	{	
		if (((int)ThisMsg.WParam)==WNDPROC_MESSAGE0_SHOW_LATTICE_SIZE)
		{

			sprintf_s(&tc[0], 1024,"Lattice: %ix%ix%i", ((int)ThisMsg.LParam/LATTICE_MAX_Y/LATTICE_MAX_Z),(((int)ThisMsg.LParam/LATTICE_MAX_Z))%LATTICE_MAX_Y,(((int)ThisMsg.LParam))%LATTICE_MAX_Z);
			axCommandBars1->StatusBar->FindPane(IdsStatusBarItems::ITEM_LATTICE_SIZE)->Text=gcnew String(tc);
		

		}
	}
	if (ThisMsg.Msg == wndprocMessages[0])
	{	
		if (((int)ThisMsg.WParam)==WNDPROC_MESSAGE0_SHOW_USB_STATUS)
		{
			if ((int)ThisMsg.LParam==1)
				axCommandBars1->StatusBar->FindPane(IdsStatusBarItems::ITEM_USB_STATUS)->Text="USB: Connected";
			if ((int)ThisMsg.LParam==2)
				axCommandBars1->StatusBar->FindPane(IdsStatusBarItems::ITEM_USB_STATUS)->Text="USB: Failed";
			if ((int)ThisMsg.LParam==3)
				axCommandBars1->StatusBar->FindPane(IdsStatusBarItems::ITEM_USB_STATUS)->Text="USB: Ready";


		

		}
	}
	if (ThisMsg.Msg == wndprocMessages[0])
	{	
		if (((int)ThisMsg.WParam)==WNDPROC_MESSAGE0_SHOW_ACTIVE_FRAME)
		{

			sprintf_s(&tc[0], 20,"Frame: %i", (int)ThisMsg.LParam);
			axCommandBars1->StatusBar->FindPane(IdsStatusBarItems::ITEM_ACTIVE_FRAME)->Text=gcnew String(tc);
		

		}
	}
	if (ThisMsg.Msg == wndprocMessages[0])
	{	
		if (((int)ThisMsg.WParam)==WNDPROC_MESSAGE0_SHOW_MAIN_STATUS)
		{

			if ((int)ThisMsg.LParam==0)
				axCommandBars1->StatusBar->FindPane(IdsStatusBarItems::ITEM_MAIN_STATUS)->Text="Ready";
			if ((int)ThisMsg.LParam==1)
				axCommandBars1->StatusBar->FindPane(IdsStatusBarItems::ITEM_MAIN_STATUS)->Text="Playing...";
			if ((int)ThisMsg.LParam==2)
				axCommandBars1->StatusBar->FindPane(IdsStatusBarItems::ITEM_MAIN_STATUS)->Text="Compiling script...";
			if ((int)ThisMsg.LParam==3)
				axCommandBars1->StatusBar->FindPane(IdsStatusBarItems::ITEM_MAIN_STATUS)->Text="Running script...";

		}
	}
	if (ThisMsg.Msg == wndprocMessages[0])
	{	
		if (((int)ThisMsg.WParam)==WNDPROC_MESSAGE0_SHOW_CORE_FPS)
		{

			sprintf_s(&tc[0], 20,"FPS: %i", (int)ThisMsg.LParam);
	//		toolStripStatusLabel4->Text=gcnew String(tc);

		}
	}
	if (ThisMsg.Msg == wndprocMessages[0])
	{	
		if (((int)ThisMsg.WParam)==WNDPROC_MESSAGE0_SET_PROGRES_BAR_VALUE)
		{
			axProgressBar1->Value=(int)ThisMsg.LParam;
			//FindPane(ID.ID_INDICATOR_PROGRESS).Visible = chkShowProgress.Checked;
	//		toolStripProgressBar1->Value =(int)ThisMsg.LParam;
		}
	}
	if (ThisMsg.Msg == wndprocMessages[0])
	{	
		if (((int)ThisMsg.WParam)==WNDPROC_MESSAGE0_ENABLE_MAIN_FORM)
		{
			if ((int)ThisMsg.LParam==1)
			{
				EnableWindow((HWND)wndprocFrmMainHandle,1);
				BringToFront();
				this->Focus();
			}
			if ((int)ThisMsg.LParam==0)
				EnableWindow((HWND)wndprocFrmMainHandle,0);

		}
	}

	if (ThisMsg.Msg == wndprocMessages[0])
	{	
		if (((int)ThisMsg.WParam)==WNDPROC_MESSAGE0_ACTIVATE_SCRIPT_SOURCE)
		{
			//axDockingPane1->FindPane(IdsDockingPanel::PANEL_SCRIPT_SOURCE)->Select();
			axDockingPane1->ShowPane(IdsDockingPanel::PANEL_SCRIPT_SOURCE);
		}

	}

	System::Windows::Forms::Form::WndProc(ThisMsg);
}


void FrmScriptOutput::WndProc(System::Windows::Forms::Message %ThisMsg)
{
	int i,j,k;
	char singleError[SCRIPT_SINGLE_ERROR_LENGTH];
	char tc[1024];
	if (ThisMsg.Msg == wndprocMessages[0])
		{	
			if (ThisMsg.Msg == wndprocMessages[0])
			{	
				if (((int)ThisMsg.WParam)==WNDPROC_MESSAGE0_SHOW_COMPILETIME)
				{

					sprintf_s(&tc[0], 1024,"Script compiled succesfully in %i.%i s", (int)ThisMsg.LParam/1000,(int)ThisMsg.LParam%1000);
					listBox1->Items->Add(gcnew String(tc));
				

				}
			}	
			if (ThisMsg.Msg == wndprocMessages[0])
			{	
				if (((int)ThisMsg.WParam)==WNDPROC_MESSAGE0_SHOW_RUNTIME)
				{

					sprintf_s(&tc[0], 1024,"Script finished in %i.%i s", (int)ThisMsg.LParam/1000,(int)ThisMsg.LParam%1000);
					listBox1->Items->Add(gcnew String(tc));
				

				}
			}
			if (ThisMsg.Msg == wndprocMessages[0])
			{	
				if (((int)ThisMsg.WParam)==WNDPROC_MESSAGE0_DEBUG_SHOW_NUMBER)
				{

					sprintf_s(&tc[0], 1024,"%i", (int)ThisMsg.LParam);
					listBox1->Items->Add(gcnew String(tc));


				}
			}	
			if (((int)ThisMsg.WParam)==WNDPROC_MESSAGE0_SHOW_SCRIPT_ERRORS)
			{
				listBox1->Items->Clear();
				listBox1->BeginUpdate();
				k=0;
				for(i=0;i<(int)scriptErrorCount;i++)
				{
					for(j=0;j<SCRIPT_SINGLE_ERROR_LENGTH;j++)
						singleError[j]=0;
					j=0;
					while (scriptErrors[k]!=0)
					{
						singleError[j]=scriptErrors[k];
						k++;
						j++;
					}
					k++;
					listBox1->Items->Add(gcnew String(singleError));
				}
				listBox1->EndUpdate();
			}
	}

	System::Windows::Forms::Form::WndProc(ThisMsg);
}


void FrmFrames::WndProc(System::Windows::Forms::Message %ThisMsg)
{
	int i;
	char tc[1024];

	if (ThisMsg.Msg == wndprocMessages[0])
		{	
			if (((int)ThisMsg.WParam)==WNDPROC_MESSAGE0_SHOW_FRAME_LIST)
			{
				listBox1->Items->Clear();
				for(i=0;i<(int)ThisMsg.LParam;i++)
				{
					sprintf_s(&tc[0], 20,"%i", i);
					listBox1->Items->Add(gcnew String(tc));
				}
				listBox1->EndUpdate();
			}
	}

	System::Windows::Forms::Form::WndProc(ThisMsg);
}

void FrmScriptSource::WndProc(System::Windows::Forms::Message %ThisMsg)
{
	int i;
	char tc[1024];

	if (ThisMsg.Msg == wndprocMessages[0])
	{	
		axSyntaxEdit1->Selection->Start->Row=(int)ThisMsg.LParam;
		axSyntaxEdit1->Selection->Start->Col=1;

		axSyntaxEdit1->Selection->End->Row=(int)ThisMsg.LParam+1;
		axSyntaxEdit1->Selection->End->Col=1;

		axSyntaxEdit1->CurrPos->Row=(int)ThisMsg.LParam;
		axSyntaxEdit1->CurrPos->Col=1;
		axSyntaxEdit1->BringToFront();
		axSyntaxEdit1->Focus();
	

		SendMessageW((HWND)wndprocFrmMainHandle,wndprocMessages[0],WNDPROC_MESSAGE0_ACTIVATE_SCRIPT_SOURCE,0);


		BringToFront();
	}

	System::Windows::Forms::Form::WndProc(ThisMsg);
}