///////////////////////////////////////////////////////////////////////////////
// Name               : FileDXF.h
// Purpose            : Reads a DXF File.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 07.08.2010
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

#ifndef FILEDXF_H_
#define FILEDXF_H_

/*!\class FileDXF
 * \brief Reads a DXF file
 *
 * ...
 */

#include "GeometryFileAbstract.h"
#include <wx/string.h>

class FileDXF:public GeometryFileAbstract {
	// Constructor/ Destructor
public:
	FileDXF();
	virtual ~FileDXF();

	// Member variables
public:

private:
	enum StateType {
		idle = 0, inSection, inBlock, inEntities
	};
	StateType state;

	wxString blockName;
	wxString objectName;
	wxString objectType;
	long objectFlag;
	double x, y, z;
	double sx, sy, sz;
	long v0, v1, v2, v3;
	long lastGeometry;
	ArrayOfVector3 v;

	//Methods:
public:
	bool ReadFile(wxString fileName);
private:
	void ProcessCode(long codeNr, wxString code);
};

#endif /* FILEDXF_H_ */
