///////////////////////////////////////////////////////////////////////////////
// Name               : DialogCurrentControl.h
// Purpose            : 
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 19.11.2013
// Copyright          : (C) 2013 Tobias Schaefer <tobiassch@users.sourceforge.net>
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
///////////////////////////////////////////////////////////////////////////////

#ifndef DIALOGCURRENTCONTROL_H_
#define DIALOGCURRENTCONTROL_H_

/*!\class DialogCurrentControl
 * \brief Dialog that allows the direct control of the currents in the coils.
 */

#include "../StdInclude.h"
#include "../hardware/SerialPort.h"

#include "gui.h"

class DialogCurrentControl:public GUIControlCurrentsDialog {
	// Constructor / Destructor
public:
	DialogCurrentControl(wxWindow* parent, SerialPort * serial);
	virtual ~DialogCurrentControl();

	// Member variables
private:
	SerialPort * serial;
	// Methods

public:
	bool TransferDataToWindow(void);
	bool TransferDataFromWindow(void);

private:
	void SetCurrent(unsigned char channel, int current_mA);

	virtual void OnButtonClose(wxCommandEvent& event);
	virtual void OnScroll0(wxScrollEvent& event);
	virtual void OnScroll1(wxScrollEvent& event);
	virtual void OnScroll2(wxScrollEvent& event);
	virtual void OnScroll3(wxScrollEvent& event);
	virtual void OnScroll4(wxScrollEvent& event);
	virtual void OnScroll5(wxScrollEvent& event);
	virtual void OnScroll6(wxScrollEvent& event);
	virtual void OnScroll7(wxScrollEvent& event);

};

#endif /* DIALOGCURRENTCONTROL_H_ */
