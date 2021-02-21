///////////////////////////////////////////////////////////////////////////////
// Name               : Vector3.cpp
// Purpose            : A 3D vector class with support functions.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   : -lm
// Author             : Tobias Schaefer
// Created            : 28.01.2010
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


#include "Vector3.h"

#include <wx/tokenzr.h>
#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfVector3)

wxString Vector3::ToString(void) const
{
	return wxString::Format(_T("%f#%f#%f"), x, y, z);
}

void Vector3::FromString(wxString const& string)
{
	wxStringTokenizer tkz(string, wxT("#"));
	double temp;
	while(tkz.HasMoreTokens()){
		wxString token = tkz.GetNextToken();
		token.ToDouble(&temp);
		switch(tkz.CountTokens()){
		case 2:
			x = temp;
			break;
		case 1:
			y = temp;
			break;
		case 0:
			z = temp;
			break;
		}
	}
}

float Vector3::Abs(void)
{
	return sqrt(x * x + y * y + z * z);
}

void Vector3::Zero(void)
{
	x = y = z = 0.0;
}

void Vector3::Swap(Vector3& b)
{
	//TODO: Rewrite to simpler version.
	float temp;
	temp = b.x;
	b.x = this->x;
	this->x = temp;

	temp = b.y;
	b.y = this->y;
	this->y = temp;

	temp = b.z;
	b.z = this->z;
	this->z = temp;
}

Vector3 Vector3::Normalize(void)
{
	float d = Abs();
	if(d > 0){
		x /= d;
		y /= d;
		z /= d;
	}
	return Vector3(x, y, z);
}
