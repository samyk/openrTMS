///////////////////////////////////////////////////////////////////////////////
// Name               : SerialSetupDialog.h
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

#ifndef SERIALSETUPDIALOG_H_
#define SERIALSETUPDIALOG_H_

#include "../StdInclude.h"
#include "../Config.h"
#include "../hardware/SerialPort.h"
#include "gui.h"

class SerialSetupDialog:public GUISerialSetupDialog {
	// Constructor / Destructor
public:
	SerialSetupDialog(wxWindow* parent, SerialPort* serial, wxString portName,
			bool openOnStartup);
	virtual ~SerialSetupDialog();

	// Member Variables
public:
	wxString portName;
	bool openOnStartup;

private:
	SerialPort* serial;

	// Member Functions
public:

private:
	void OnConnect(wxCommandEvent& event);
	void OnDisconnect(wxCommandEvent& event);
	void OnClose(wxCommandEvent& event);
	void OnProgramGenerator(wxCommandEvent& event);

	bool TransferDataToWindow(void);
	bool TransferDataFromWindow(void);
};

#endif /* SERIALSETUPDIALOG_H_ */
