///////////////////////////////////////////////////////////////////////////////
// Name               : SerialSetupDialog.cpp
// Purpose            : Setup dialog for serial port.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 25.07.2009
// Copyright          : (C) 2009 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "SerialSetupDialog.h"
#include "../hardware/ParallaxPropeller.h"
#include <wx/debug.h>

SerialSetupDialog::SerialSetupDialog(wxWindow* parent, SerialPort* serial,
		wxString portName, bool openOnStartup) :
		GUISerialSetupDialog(parent)
{
	wxASSERT(serial != NULL);

	this->serial = serial;
	this->portName = portName;
	this->openOnStartup = openOnStartup;

	if(serial->IsOpen()) m_textCtrlLog->SetValue(_("Connected!\n"));

	m_textCtrlPort->SetValue(portName);
	TransferDataToWindow();
}

SerialSetupDialog::~SerialSetupDialog()
{
}

void SerialSetupDialog::OnConnect(wxCommandEvent& event)
{
	TransferDataFromWindow();

	if(!serial->Open(portName.ToAscii(), 115200)){
		m_textCtrlLog->SetValue(_("Port could not be opened!\n"));
		return;
	}
	serial->SetDTR(true);
	m_textCtrlLog->SetValue(
			_("Connected...\nSearching for Parallax Propeller...\n"));
	TransferDataToWindow();
	Refresh();

	ParallaxPropeller propeller(serial);

	int v = propeller.GetVersion();
	m_textCtrlLog->AppendText(propeller.log);
	if(v == -1){
		m_textCtrlLog->AppendText(
				_("No Parallax Propeller found on this port!\n"));
	}else{
		m_textCtrlLog->AppendText(
				wxString::Format(_("Parallax Propeller (Version %d) found!\n"),
						v));
	}
	m_textCtrlLog->AppendText(_("Finished searching!"));
}

void SerialSetupDialog::OnDisconnect(wxCommandEvent& event)
{
	TransferDataFromWindow();
	if(!serial->Close()) return;
	TransferDataToWindow();
}

void SerialSetupDialog::OnClose(wxCommandEvent& event)
{
	TransferDataFromWindow();
	this->Close();
}

void SerialSetupDialog::OnProgramGenerator(wxCommandEvent& event)
{
	m_textCtrlLog->SetValue(_("Programming...\n"));

	ParallaxPropeller propeller(serial);

	bool worked = propeller.UploadAndStart(wxFileName(_T(_OPENRTMS_FIRMWARE)),
			m_checkBoxWriteEEprom->GetValue());

	m_textCtrlLog->AppendText(propeller.log);

	if(worked){
		m_textCtrlLog->AppendText(_("Scope loaded and started!\n"));
	}else{
		m_textCtrlLog->AppendText(_T("Programming failed!\n"));
	}
}

bool SerialSetupDialog::TransferDataToWindow(void)
{
	m_checkBoxOpenOnStartup->SetValue(openOnStartup);
	m_textCtrlPort->SetValue(portName);

	if(serial->IsOpen()){
		m_buttonConnect->Enable(false);
		m_buttonDisconnect->Enable(true);
		m_textCtrlPort->Enable(false);

		m_buttonProgramGenerator->Enable(true);
		m_checkBoxWriteEEprom->Enable(true);
	}else{
		m_buttonConnect->Enable(true);
		m_buttonDisconnect->Enable(false);
		m_textCtrlPort->Enable(true);
		m_textCtrlLog->SetValue(_("Disconnected!"));

		m_buttonProgramGenerator->Enable(false);
		m_checkBoxWriteEEprom->Enable(false);
	}

	return true;
}

bool SerialSetupDialog::TransferDataFromWindow(void)
{
	openOnStartup = m_checkBoxOpenOnStartup->GetValue();
	portName = m_textCtrlPort->GetValue();
	return true;
}
