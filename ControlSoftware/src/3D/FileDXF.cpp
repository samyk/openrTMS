///////////////////////////////////////////////////////////////////////////////
// Name               : FileDXF.cpp
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


#include "FileDXF.h"

#include <wx/file.h>
#include <wx/textfile.h>
#include <wx/log.h>

#include <string.h>

FileDXF::FileDXF()
{
	state = idle;
}

FileDXF::~FileDXF()
{

}

void FileDXF::ProcessCode(long codeNr, wxString code)
{
	char text[20];
	strcpy(text, code.To8BitData());


	// This line converts the english '.' in numbers into the german ','. Argl!
	code.Replace(_T("."), _T(","));


	// Fill in data

	switch(codeNr){
	case 2:
		blockName = code;
		break;
	case 3:
		objectName = code;
		break;
	case 70:
		code.ToLong(&objectFlag);
		break;
	}

	if(objectType.Cmp(_T("INSERT")) == 0){
		switch(codeNr){
		case 10:
			code.ToDouble(&x);
			break;
		case 20:
			code.ToDouble(&y);
			break;
		case 30:
			code.ToDouble(&z);
			break;
		case 41:
			code.ToDouble(&sx);
			break;
		case 42:
			code.ToDouble(&sy);
			break;
		case 43:
			code.ToDouble(&sz);
			break;
		}
	}

	if(objectType.Cmp(_T("VERTEX")) == 0){
		switch(codeNr){
		case 10:
			code.ToDouble(&x);
			break;
		case 20:
			code.ToDouble(&y);
			break;
		case 30:
			code.ToDouble(&z);
			break;
		case 71:
			code.ToLong(&v0);
			break;
		case 72:
			code.ToLong(&v1);
			break;
		case 73:
			code.ToLong(&v2);
			break;
		case 74:
			code.ToLong(&v3);
			break;
		}
	}

	if(codeNr == 0){
		// Generate Objects and such

		if(objectType.Cmp(_T("BLOCK")) == 0){
			v.Empty();
			Geometry* g = new Geometry();
			g->matrix.TranslateGlobal(x, y, z);
			g->objectName = blockName;
			geometry.Add(g);
			lastGeometry = geometry.Count() - 1;
		}
		if(objectType.Cmp(_T("VERTEX")) == 0){
			if(objectFlag == 192){
				Vector3 vector(x, y, z);
				v.Add(vector);
			}
			if(objectFlag == 128){
				if(lastGeometry >= 0){
					if(v0 > 0 && v1 > 0 && v2 > 0 && v3 < 0){
						geometry[lastGeometry].AddTriangle(v[v0 - 1],
								v[v1 - 1], v[v2 - 1]);
					}
					if(v0 > 0 && v1 > 0 && v2 > 0 && v3 > 0)

					{
						geometry[lastGeometry].AddQuad(v[v0 - 1], v[v1 - 1],
								v[v2 - 1], v[v3 - 1]);
					}
				}
			}
		}

		if(objectType.Cmp(_T("INSERT")) == 0){
			size_t i;
			for(i = 0; i < geometry.GetCount(); i++){
				if(geometry[i].objectName.Cmp(blockName) == 0){
					geometry[i].matrix.ScaleGlobal(sx, sy, sz);
					geometry[i].matrix.TranslateGlobal(x, y, z);
				}
			}
		}

		objectName.Empty();
		x = y = z = 0.0;
		sx = sy = sz = 1.0;
		v0 = v1 = v2 = v3 = -1;
		objectType = code;

		switch(state){
		case idle:
			if(code.Cmp(_T("SECTION")) == 0){
				state = inSection;
				break;
			}
			break;
		case inSection:
			if(code.Cmp(_T("ENDSEC")) == 0){
				state = idle;
				break;
			}
			if(code.Cmp(_T("BLOCK")) == 0){
				state = inBlock;
				break;
			}
			if(code.Cmp(_T("ENTITIES")) == 0){
				state = inEntities;
				break;
			}
			break;
		case inBlock:
			if(code.Cmp(_T("ENDBLK")) == 0){
				state = idle;
				break;
			}
			// no break here!
		case inEntities:
			if(code.Cmp(_T("ENDSEC")) == 0){
				state = idle;
				break;
			}
			break;
		}
	}
}

bool FileDXF::ReadFile(wxString fileName)
{
	wxTextFile file;

	wxLogMessage(wxString::Format(_T("Opening File:") + fileName));

	if(!file.Open(fileName)){
		wxLogError(_T("STL: Can't open ") + fileName + _T("!"));
		return false;
	}

	wxString temp;
	long codeNumber;

	state = idle;

	temp = file.GetFirstLine();
	do{
		temp.ToLong(&codeNumber);
		temp = file.GetNextLine();
		ProcessCode(codeNumber, temp);
		temp = file.GetNextLine();
	}while(!file.Eof());
	file.Close();


	// Calculate normals to get the lighting right.
	size_t i;
	for(i = 0; i < geometry.GetCount(); i++){

	}
	return true;
}
