///////////////////////////////////////////////////////////////////////////////
// Name               : AffineTransformMatrix.h
// Purpose            : A class to store a 3D affine transform matrix and provide operations upon.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   : -lm
// Author             : Tobias Schaefer
// Created            : 22.07.2009
// Copyright          : (C) 2009 Tobias Schaefer <tobiassch@users.sourceforge.net>
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
//$LastChangedDate: 2010-05-04 01:09:07 +0200 (Di, 04 Mai 2010) $
//$Revision: 43 $
//$LastChangedBy: tobiassch $
///////////////////////////////////////////////////////////////////////////////

#ifndef AFFINETRANSFORMMATRIX_H_
#define AFFINETRANSFORMMATRIX_H_

/** \class AffineTransformMatrix
 * 	\code #include "AffineTransformMatrix.h"\endcode
 *  \brief A class to store a 3D affine transform matrix and provide operations upon.
 *
 * This class stores and manages a 4x4 matrix. This matrix is organized the same way,
 * the transformation matrices of OpenGL are:
 *
 *  R11 R12 R13 Tx\n
 *  R21 R22 R23 Ty\n
 *  R31 R32 R33 Tz\n
 *   0   0   0   1\n
 *
 * Where R is responsible for rotation and scaling
 * and T for translation.
 * The vector \c a is organized as follows:
 *
 *   0   4   8  12\n
 *   1   5   9  13\n
 *   2   6  10  14\n
 *   3   7  11  15\n
 *
 * Right handed coordinate system:\n
 * X to the right of the screen\n
 * Y to the top of the screen\n
 * Z towards the viewer\n
 *
 */

// http://www.parashift.com/c++-faq-lite/operator-overloading.html


#include <wx/string.h>
#include <wx/dynarray.h>
#include "Vector3.h"

class AffineTransformMatrix {
	// Constructor / Destructor
public:
	AffineTransformMatrix();
	virtual ~AffineTransformMatrix();

	// Member variables
public:
	double a[16]; //!< The transformation matrix.

	double rx, ry, rz; //!< Rotation after taking the matrix apart.
	double tx, ty, tz; //!< Translation after taking the matrix apart.
	double sx, sy, sz; //!< Scaling after taking the matrix apart.

	bool linkScaling; //!< Force uniform scaling.

	// Methods
public:

	void TakeMatrixApart(void);
	void PutMatrixTogether(void);

	wxString ToString();
	void FromString(wxString const& string);

	AffineTransformMatrix& operator=(const AffineTransformMatrix &b);
	void Set(AffineTransformMatrix const& b);

	AffineTransformMatrix & operator*=(const AffineTransformMatrix &b);
	const AffineTransformMatrix operator*(const AffineTransformMatrix &b) const;

	AffineTransformMatrix & operator/=(const AffineTransformMatrix &b);
	const AffineTransformMatrix operator/(const AffineTransformMatrix &b) const;

	Vector3 GetCenter(void) const;

	void SetIdentity();
	static AffineTransformMatrix Identity();

	const AffineTransformMatrix Inverse() const;

	static AffineTransformMatrix RotateAroundVector(Vector3 const& vector,
			double const& phi);
	static AffineTransformMatrix RotateInterwoven(double const& x,
			double const& y, double const& z);
	static AffineTransformMatrix RotateXY(int const& x, int const& y,
			double const& scale);
	static AffineTransformMatrix RotateXYZ(double const& x, double const& y,
			double const& z);

	void TranslateGlobal(double const& x, double const& y, double const& z);
	void TranslateLocal(double const& x, double const& y, double const& z);

	void ScaleGlobal(double const& x, double const& y, double const& z);

	Vector3 Transform(Vector3 const& v) const;
	Vector3 TransformNoShift(Vector3 const& v) const;

};

WX_DECLARE_OBJARRAY(AffineTransformMatrix, ArrayOfAffineTransformMatrix)
;

#endif /* AFFINETRANSFORMMATRIX_H_ */
