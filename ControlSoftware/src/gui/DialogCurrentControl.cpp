///////////////////////////////////////////////////////////////////////////////
// Name               : DialogCurrentControl.cpp
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

#include "DialogCurrentControl.h"

DialogCurrentControl::DialogCurrentControl(wxWindow* parent,
		SerialPort * serial) :
		GUIControlCurrentsDialog(parent)
{
	wxASSERT(serial!=NULL);
	this->serial = serial;
}

DialogCurrentControl::~DialogCurrentControl()
{

}

void DialogCurrentControl::OnButtonClose(wxCommandEvent& event)
{
	this->Close();
}

bool DialogCurrentControl::TransferDataToWindow(void)
{
	return true;
}
bool DialogCurrentControl::TransferDataFromWindow(void)
{
	return true;
}

void DialogCurrentControl::SetCurrent(unsigned char channel, int current_mA)
{
	int i = ((current_mA + 250) * 4095) / 501;

	if(i < 0 || i > 9999) return;
	if(channel < 0 || channel > 7) return;

	char command[16];
	sprintf(command, "C %u %4u\n", channel, i);
	serial->SendData(command, strlen(command));
}

// There must be a better way of doing this.
// event.GetId() did not return the ID_CHANNELx of the slider...

void DialogCurrentControl::OnScroll0(wxScrollEvent& event)
{
	int current = event.GetPosition();
	SetCurrent(0, current);
}
void DialogCurrentControl::OnScroll1(wxScrollEvent& event)
{
	int current = event.GetPosition();
	SetCurrent(1, current);
}
void DialogCurrentControl::OnScroll2(wxScrollEvent& event)
{
	int current = event.GetPosition();
	SetCurrent(2, current);
}
void DialogCurrentControl::OnScroll3(wxScrollEvent& event)
{
	int current = event.GetPosition();
	SetCurrent(3, current);
}
void DialogCurrentControl::OnScroll4(wxScrollEvent& event)
{
	int current = event.GetPosition();
	SetCurrent(4, current);
}
void DialogCurrentControl::OnScroll5(wxScrollEvent& event)
{
	int current = event.GetPosition();
	SetCurrent(5, current);
}
void DialogCurrentControl::OnScroll6(wxScrollEvent& event)
{
	int current = event.GetPosition();
	SetCurrent(6, current);
}
void DialogCurrentControl::OnScroll7(wxScrollEvent& event)
{
	int current = event.GetPosition();
	SetCurrent(7, current);
}
