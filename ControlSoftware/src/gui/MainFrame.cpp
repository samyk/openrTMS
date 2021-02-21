///////////////////////////////////////////////////////////////////////////////
// Name               : MainFrame.cpp
// Purpose            : The main window.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 21.02.2010
// Copyright          : (C) 2010 Tobias Schaefer <tobiassch@users.sourceforge.net>
// Licence            : GNU General Public License version 3.0 (GPLv3)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//$LastChangedDate: 2010-05-22 01:40:18 +0200 (Sa, 22 Mai 2010) $
//$Revision: 45 $
//$LastChangedBy: tobiassch $
///////////////////////////////////////////////////////////////////////////////

#include "MainFrame.h"
#include "SerialSetupDialog.h"
#include "AboutDialog.h"
#include "../languages.h"

#include <wx/string.h>
#include <wx/stopwatch.h>
#include <wx/msgdlg.h>
#include "DialogCurrentControl.h"

MainFrame::MainFrame(wxWindow* parent) :
		GUIMainFrame(parent)
{
//	logWindow = new wxLogWindow(this, _("Open-rTMS - log window"), false, true);
//	logWindow->Show();

//	wxLogMessage(_T("Control Software started!"));

// Read configuration:
	config = new wxConfig(_T(_OPENRTMS_NAMEOFCONFIG));

	wxString temp;
	config->Read(_T("Port"), &temp, _T("/dev/ttyUSB0"));
	config->Read(_T("OpenOnStartup"), &openOnStartup, false);

	if(openOnStartup){
		serial.Open(temp.ToAscii(), 115200);
		if(serial.IsOpen()) serial.SetDTR(true);
	}
	TransferDataToWindow();
}

MainFrame::~MainFrame()
{
	delete config; // config is written back to file (automagically)
}

bool MainFrame::TransferDataToWindow(void)
{
	if(serial.IsOpen()){
		m_buttonConnect->Enable(false);
		m_buttonCurrents->Enable(true);
		m_buttonDisconnect->Enable(true);

		m_menubar->Enable(ID_CONNECT, false);
		m_menubar->Enable(ID_CONTROLCURRENTS, true);
		m_menubar->Enable(ID_DISCONNECT, true);

		m_statusBar->SetStatusText(_("Hardware: Connected"), 1);
	}else{
		m_buttonConnect->Enable(true);
		m_buttonCurrents->Enable(false);
		m_buttonDisconnect->Enable(false);

		m_menubar->Enable(ID_CONNECT, true);
		m_menubar->Enable(ID_CONTROLCURRENTS, false);
		m_menubar->Enable(ID_DISCONNECT, false);

		m_statusBar->SetStatusText(_("Hardware: Disconnected"), 1);
	}
	return true;
}

bool MainFrame::TransferDataFromWindow(void)
{
	return true;
}

void MainFrame::OnQuit(wxCommandEvent& event)
{
	this->Close();
}

void MainFrame::OnChangeLanguage(wxCommandEvent& event)
{
	long lng = wxGetSingleChoiceIndex(_T(
			"Please choose language:\nChanges will take place after restart!"),
			_T("Language"), WXSIZEOF(langNames), langNames);
	if(lng < 0) return;
	config->Write(_T("Language"), langNames[lng]);
}

void MainFrame::OnAbout(wxCommandEvent& event)
{
	AboutDialog* dialog = new AboutDialog(this);
	dialog->Show();
}

void MainFrame::OnConnect(wxCommandEvent& event)
{
	if(serial.IsOpen()) return;

	wxString temp;
	config->Read(_T("Port"), &temp, _T("/dev/ttyUSB0"));

	serial.Open(temp.ToAscii(), 115200);
	if(serial.IsOpen()){
		serial.SetDTR(true);
	}else{
		wxMessageDialog dialog(this,
				_T("Serial port (") + temp + _T(") is not found!"),
				_("Connection to hardware"),
				wxOK | wxICON_ERROR | wxSTAY_ON_TOP);
		dialog.ShowModal();
	}
	TransferDataToWindow();
}
void MainFrame::OnControlCurrents(wxCommandEvent& event)
{
	if(!serial.IsOpen()) return;
	DialogCurrentControl dialog(this, &serial);
	dialog.ShowModal();
}
void MainFrame::OnDisconnect(wxCommandEvent& event)
{
	serial.Close();
	TransferDataToWindow();
}

void MainFrame::OnSetupHardware(wxCommandEvent& event)
{
	wxString temp;
	config->Read(_T("Port"), &temp, _T("/dev/ttyUSB0"));

	SerialSetupDialog dialog(this, &serial, temp, openOnStartup);
	if(dialog.ShowModal() == wxID_OK){
		config->Write(_T("Port"), dialog.portName);
		config->Write(_T("OpenOnStartup"), dialog.openOnStartup);
		config->Flush();
	}
	TransferDataToWindow();
}

//void MainFrame::OnTimer(wxTimerEvent& event)
//{
//
//}
