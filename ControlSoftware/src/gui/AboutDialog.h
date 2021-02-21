///////////////////////////////////////////////////////////////////////////////
// Name               : AboutDialog.h
// Purpose            : The about dialog.
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
//$LastChangedDate: $
//$Revision: $
//$LastChangedBy: $
///////////////////////////////////////////////////////////////////////////////



#ifndef ABOUTDIALOG_H_
#define ABOUTDIALOG_H_

#include "../StdInclude.h"
#include "gui.h"

class AboutDialog:public GUIAboutDialog {
	// Constructor/ Destructor
public:
	AboutDialog(wxWindow* parent);
	virtual ~AboutDialog();

	// Member variables
private:


	// Methods
private:

	void OnClose(wxCommandEvent& event);
};

#endif /* ABOUTDIALOG_H_ */
