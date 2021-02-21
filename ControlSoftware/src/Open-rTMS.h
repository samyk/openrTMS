///////////////////////////////////////////////////////////////////////////////
// Name               : Open-rTMS.h
// Purpose            : Main entry point.
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

#ifndef OPENRTMS_H_
#define OPENRTMS_H_

#include "StdInclude.h"
#include "Config.h"
#include "gui/MainFrame.h"
#include <wx/intl.h>

/*!\class OpenrTMSApp
 * \brief Main application class for the project
 *
 * the purpose of this class is only to provide a vehicle upon which the rest of the
 * program runs.
 *
 * This classes tasks are:
 *
 *  - Setup the language (in the Constructor).
 *  - Open the main window (in OnInit).
 *
 * Everything else is done in the MainFrame.
 *
 */

class OpenrTMSApp:public wxApp {
	// Constructor
public:
	OpenrTMSApp(void);

	// Member variables
public:
	MainFrame* frame;

protected:
	wxLocale locale;

	// Methods
public:
	bool OnInit();

};

DECLARE_APP(OpenrTMSApp)
#endif /* OPENRTMS_H_ */
