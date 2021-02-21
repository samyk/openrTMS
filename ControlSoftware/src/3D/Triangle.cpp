///////////////////////////////////////////////////////////////////////////////
// Name               : Triangle.cpp
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 11.06.2011
// Copyright          : (C) 2011 Tobias Schaefer <tobiassch@users.sourceforge.net>
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

#include "Triangle.h"
#include <GL/gl.h>
#include <wx/tokenzr.h>
#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfTriangle)

Triangle::Triangle()
{
}
Triangle::Triangle(wxString string)
{
	this->FromString(string);
}

Triangle::~Triangle()
{
}

wxString Triangle::ToString(void) const
{
	wxString temp;
	temp = p[0].ToString() + _T(";");
	temp += p[1].ToString() + _T(";");
	temp += p[2].ToString() + _T(";");
	temp += n[0].ToString() + _T(";");
	temp += n[1].ToString() + _T(";");
	temp += n[2].ToString() + _T(";");
	temp += c[0].ToString() + _T(";");
	temp += c[1].ToString() + _T(";");
	temp += c[2].ToString();
	return temp;
}

void Triangle::FromString(wxString const &string)
{
	wxStringTokenizer tkz(string, wxT(";"));
	while(tkz.HasMoreTokens()){
		wxString token = tkz.GetNextToken();
		switch(tkz.CountTokens()){
		case 8:
			p[0].FromString(token);
			break;
		case 7:
			p[1].FromString(token);
			break;
		case 6:
			p[2].FromString(token);
			break;
		case 5:
			n[0].FromString(token);
			break;
		case 4:
			n[1].FromString(token);
			break;
		case 3:
			n[2].FromString(token);
			break;
		case 2:
			c[0].FromString(token);
			break;
		case 1:
			c[1].FromString(token);
			break;
		case 0:
			c[2].FromString(token);
			break;
		}
	}
}

/*!\brief Puts a triangle in the OpenGL queue.
 *
 * This function does not call glBegin(GL_TRIANGLES); and
 * glEnd();. This has to be done by the calling function.
 * (Allows to save on OpenGL calls.)
 */
void Triangle::Paint(bool useNormals, bool useColors) const
{
	unsigned char i;
	for(i = 0; i < 3; i++){
		if(useNormals) ::glNormal3f(n[i].x, n[i].y, n[i].z);
		if(useColors) ::glColor3f(c[i].x, c[i].y, c[i].z);
		::glVertex3f(p[i].x, p[i].y, p[i].z);
	}
}
/*!\brief Calculates normals for the corners of a triangle.
 *
 *  If no normals can be provided from elsewhere, this function
 *  can generate a set. The normal vectors n[0] to n[2] are all
 *  set normal to the plane of the triangle. Orientation is
 *  right handed.
 */
void Triangle::CalculateNormal()
{
	n[0] = (p[1] - p[0]) * (p[2] - p[1]);
	n[0].Normalize();
	n[1] = n[0];
	n[2] = n[0];
}

void Triangle::ApplyTransformation(const AffineTransformMatrix &matrix)
{
	p[0] = matrix.Transform(p[0]);
	p[1] = matrix.Transform(p[1]);
	p[2] = matrix.Transform(p[2]);
	n[0] = matrix.TransformNoShift(n[0]);
	n[1] = matrix.TransformNoShift(n[1]);
	n[2] = matrix.TransformNoShift(n[2]);
}

