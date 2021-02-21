///////////////////////////////////////////////////////////////////////////////
// Name               : Geometry.h
// Purpose            : Class for managing 3D geometry data.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 28.02.2010
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
//$LastChangedDate: 2010-06-12 17:59:21 +0200 (Sa, 12 Jun 2010) $
//$Revision: 49 $
//$LastChangedBy: tobiassch $
///////////////////////////////////////////////////////////////////////////////


#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include "Vector3.h"
#include "Triangle.h"
#include "AffineTransformMatrix.h"

#include <wx/string.h>
#include <wx/dynarray.h>
#include <wx/xml/xml.h>

/*!\class Geometry
 * \brief Contains geometric data.
 *
 * Geometric data is stored in this class.
 */
class Geometry {
	// Constructor/ Destructor
public:
	Geometry();
	virtual ~Geometry();

	// Member variables
public:
	wxString objectName;
	Vector3 color;
	bool visible;

	AffineTransformMatrix matrix; //!< Transformation of the data.
	ArrayOfTriangle triangles; //!< The storage of the geometric data.

	// Methods
public:
	void ToXml(wxXmlNode* parentNode);
	bool FromXml(wxXmlNode* node);

	void Paint(void) const;

	void Clear(void);
	void CopyFrom(const Geometry &geometry);
	void CopyTrianglesFrom(const Geometry &geometry);

	void CalculateNormals(void);
	void FlipNormals(void);

	void ApplyTransformation(const AffineTransformMatrix &matrix);
	void ApplyTransformation(void);


	void AddTriangle(const Vector3 &a, const Vector3 &b, const Vector3 &c);
	void AddTriangleTransform(const Vector3 &a, const Vector3 &b,
			const Vector3 &c, const AffineTransformMatrix &transformMatrix);
	void AddTriangleWithNormals(const Vector3 &a, const Vector3 &b,
			const Vector3 &c, const Vector3 &na, const Vector3 &nb,
			const Vector3 &nc);

	void AddQuad(const Vector3 &a, const Vector3 &b, const Vector3 &c,
			const Vector3 &d);
	void AddQuadTransform(const Vector3 &a, const Vector3 &b, const Vector3 &c,
			const Vector3 &d, const AffineTransformMatrix &transformMatrix);
};
WX_DECLARE_OBJARRAY(Geometry, ArrayOfGeometry)
;

#endif /* GEOMETRY_H_ */
