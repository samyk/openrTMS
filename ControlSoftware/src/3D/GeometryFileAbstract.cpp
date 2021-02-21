///////////////////////////////////////////////////////////////////////////////
// Name               : GeometryFileAbstract.cpp
// Purpose            : Abstract class for geometry loaded from a file.
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


#include "GeometryFileAbstract.h"

#include <GL/gl.h>

GeometryFileAbstract::GeometryFileAbstract()
{
}

GeometryFileAbstract::~GeometryFileAbstract()
{
}


void GeometryFileAbstract::Paint(void) const
{
	size_t i;
	::glPushMatrix();
	::glMultMatrixd(matrix.a);
	for(i = 0; i < geometry.Count(); i++){
		geometry[i].Paint();
	}
	::glPopMatrix();
}
