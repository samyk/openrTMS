///////////////////////////////////////////////////////////////////////////////
// Name               : Geometry.cpp
// Purpose            : Class for managing 3D geometry data.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer, Samy Kamkar
// Updated            : 2020/02/20
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


#include "Geometry.h"

#if defined(__APPLE__)
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include <wx/log.h>

#include <wx/arrimpl.cpp> // this is a magic incantation which must be done!
WX_DEFINE_OBJARRAY(ArrayOfGeometry)

Geometry::Geometry()
{
	visible = true;
	color.Set(0.8, 0.8, 0.8);
}
Geometry::~Geometry()
{
}

void Geometry::Clear(void)
{
	triangles.Clear();
}

void Geometry::CopyFrom(const Geometry &geometry)
{
	Clear();
	CopyTrianglesFrom(geometry);
	this->matrix = geometry.matrix;
	this->objectName = geometry.objectName;
	this->visible = geometry.visible;
	this->color = geometry.color;
}

void Geometry::CopyTrianglesFrom(const Geometry &geometry)
{
	size_t i;
	Triangle temp;
	for(i = 0; i < geometry.triangles.GetCount(); i++){
		temp = geometry.triangles[i];
		this->triangles.Add(temp);
	}
}

void Geometry::ApplyTransformation(const AffineTransformMatrix &matrix)
{
	size_t i;
	for(i = 0; i < triangles.Count(); i++){
		triangles[i].ApplyTransformation(matrix);
		//		triangles[i].p[0] = matrix.Transform(triangles[i].p[0]);
		//		triangles[i].p[1] = matrix.Transform(triangles[i].p[1]);
		//		triangles[i].p[2] = matrix.Transform(triangles[i].p[2]);
		//		triangles[i].n[0] = matrix.TransformNoShift(triangles[i].n[0]);
		//		triangles[i].n[1] = matrix.TransformNoShift(triangles[i].n[1]);
		//		triangles[i].n[2] = matrix.TransformNoShift(triangles[i].n[2]);
	}
}

void Geometry::ApplyTransformation(void)
{
	size_t i;
	for(i = 0; i < triangles.Count(); i++)
		triangles[i].ApplyTransformation(this->matrix);
}

void Geometry::Paint(void) const
{
	if(!visible) return;
	size_t i;


	// GL_RESCALE_NORMAL is faster, but doesn't work on non-uniform scaled models
	// GL_NORMALIZE is slower, but works always
	// ... and there seems to be a problem under Windows with OpenGL 1.1...

#if defined __WIN32__
	::glEnable(GL_NORMALIZE);
#else
	::glEnable(GL_RESCALE_NORMAL);
#endif

	::glPushMatrix();
	::glMultMatrixd(matrix.a);

	::glBegin(GL_TRIANGLES);
	::glColor3f(color.x, color.y, color.z);
	for(i = 0; i < triangles.Count(); i++){
		triangles[i].Paint();
	}
	::glEnd();
	::glPopMatrix();
#if defined (__WIN32__)
	::glDisable(GL_NORMALIZE);
#else
	::glDisable(GL_RESCALE_NORMAL);
#endif
}

void Geometry::AddTriangle(const Vector3 &a, const Vector3 &b, const Vector3 &c)
{
	Triangle* tri = new Triangle;
	tri->p[0] = a;
	tri->p[1] = b;
	tri->p[2] = c;
	tri->CalculateNormal();
	triangles.Add(tri);
}

void Geometry::AddTriangleWithNormals(const Vector3 &a, const Vector3 &b,
		const Vector3 &c, const Vector3 &na, const Vector3 &nb,
		const Vector3 &nc)
{
	Triangle* tri = new Triangle;
	tri->p[0] = a;
	tri->p[1] = b;
	tri->p[2] = c;
	tri->n[0] = na;
	tri->n[1] = nb;
	tri->n[2] = nc;
	triangles.Add(tri);
}

void Geometry::AddTriangleTransform(const Vector3 &a, const Vector3 &b,
		const Vector3 &c, const AffineTransformMatrix &transformMatrix)
{
	Triangle* tri = new Triangle;
	tri->p[0] = transformMatrix.Transform(a);
	tri->p[1] = transformMatrix.Transform(b);
	tri->p[2] = transformMatrix.Transform(c);
	tri->CalculateNormal();
	triangles.Add(tri);
}

void Geometry::AddQuad(const Vector3 &a, const Vector3 &b, const Vector3 &c,
		const Vector3 &d)
{
	Triangle* tri0 = new Triangle;
	Triangle* tri1 = new Triangle;
	tri0->p[0] = a;
	tri0->p[1] = b;
	tri0->p[2] = c;
	tri1->p[0] = tri0->p[2];
	tri1->p[1] = d;
	tri1->p[2] = tri0->p[0];
	tri0->CalculateNormal();
	tri1->n[0] = tri0->n[0];
	tri1->n[1] = tri0->n[1];
	tri1->n[2] = tri0->n[2];
	triangles.Add(tri0);
	triangles.Add(tri1);
}

void Geometry::AddQuadTransform(const Vector3 &a, const Vector3 &b,
		const Vector3 &c, const Vector3 &d,
		const AffineTransformMatrix &transformMatrix)
{
	Triangle* tri0 = new Triangle;
	Triangle* tri1 = new Triangle;
	tri0->p[0] = transformMatrix.Transform(a);
	tri0->p[1] = transformMatrix.Transform(b);
	tri0->p[2] = transformMatrix.Transform(c);
	tri1->p[0] = tri0->p[2];
	tri1->p[1] = transformMatrix.Transform(d);
	tri1->p[2] = tri0->p[0];
	tri0->CalculateNormal();
	tri1->n[0] = tri0->n[0];
	tri1->n[1] = tri0->n[1];
	tri1->n[2] = tri0->n[2];
	triangles.Add(tri0);
	triangles.Add(tri1);
}

void Geometry::CalculateNormals(void)
{
	size_t i;
	for(i = 0; i < triangles.GetCount(); i++){
		triangles[i].CalculateNormal();
	}
}

void Geometry::FlipNormals(void)
{
	size_t i;
	for(i = 0; i < triangles.GetCount(); i++){
		triangles[i].n[0] *= -1;
		triangles[i].n[1] *= -1;
		triangles[i].n[2] *= -1;
	}
}

void Geometry::ToXml(wxXmlNode* parentNode)
{
	wxXmlNode *temp, *temp2;
	wxXmlNode *nodeObject = NULL;


	// Find out, if object already exists in XML tree.
	temp = parentNode->GetChildren();
	while(temp != NULL && nodeObject == NULL){
		if(temp->GetName() == _T("geometry") && temp->GetPropVal(_T("name"),
				_T("")) == objectName) nodeObject = temp;
		temp = temp->GetNext();
	}
	if(nodeObject == NULL){
		nodeObject = new wxXmlNode(wxXML_ELEMENT_NODE, _T("geometry"));
		nodeObject->AddProperty(_T("name"), objectName);
		parentNode->InsertChild(nodeObject, NULL);
	}

	// Remove the subelements, that will be updated
	temp = nodeObject->GetChildren();
	while(temp != NULL){
		temp2 = NULL;
		if(temp->GetName() == _T("matrix")) temp2 = temp;
		if(temp->GetName() == _T("tri")) temp2 = temp;
		temp = temp->GetNext();
		if(temp2 != NULL){
			nodeObject->RemoveChild(temp2);
			delete (temp2);
		}
	}

	// Insert new matrix
	temp = new wxXmlNode(wxXML_ELEMENT_NODE, _T("matrix"));
	nodeObject->InsertChild(temp, NULL);
	temp2 = new wxXmlNode(wxXML_CDATA_SECTION_NODE, wxEmptyString,
			matrix.ToString());
	temp->InsertChild(temp2, NULL);


	// Insert new triangles
	size_t i;
	for(i = 0; i < triangles.GetCount(); i++){
		temp = new wxXmlNode(wxXML_ELEMENT_NODE, _T("tri"));
		nodeObject->InsertChild(temp, NULL);
		temp2 = new wxXmlNode(wxXML_CDATA_SECTION_NODE, wxEmptyString,
				triangles[i].ToString());
		temp->InsertChild(temp2, NULL);
	}
}

bool Geometry::FromXml(wxXmlNode* node)
{
	if(node->GetName() != _T("geometry")) return false;
	objectName = node->GetPropVal(_T("name"), _T(""));
	wxXmlNode *temp = node->GetChildren();

	triangles.Empty();
	Triangle* tri;

	while(temp != NULL){
		if(temp->GetName() == _T("tri")){
			tri = new Triangle(temp->GetNodeContent());
			//			if(triangles.GetCount() < 20) wxLogMessage(
			//					_T("Geometry::FromXml: Tri from >")
			//							+ temp->GetNodeContent() + _T("<."));

			triangles.Add(tri);
		}
		if(temp->GetName() == _T("matrix")){
			matrix.FromString(temp->GetNodeContent());
			//			wxLogMessage(_T("Geometry::FromXml: Matrix from >")
			//					+ temp->GetNodeContent() + _T("<."));
		}
		temp = temp->GetNext();
	}
	return true;
}

