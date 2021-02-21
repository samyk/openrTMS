///////////////////////////////////////////////////////////////////////////////
// Name               : MainCanvas.cpp
// Purpose            :
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

#include "MainCanvas.h"

#include <wx/wx.h>

#ifdef __WXMAC__
#include "OpenGL/glu.h"
#else
#include <GL/glu.h>
#endif

static int wx_gl_attribs[] =
	{WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 24, 0};

MainCanvas::MainCanvas(wxWindow *parent, wxWindowID id, const wxPoint& pos,
		const wxSize& size, long style, const wxString& name) :
		wxGLCanvas(parent, (wxGLCanvas*) NULL, id, pos, size,
				style | wxFULL_REPAINT_ON_RESIZE, name, wx_gl_attribs)
{
	Connect(wxEVT_ENTER_WINDOW, wxMouseEventHandler(MainCanvas::OnEnterWindow),
			NULL, this);
	Connect(wxEVT_ERASE_BACKGROUND,
			wxEraseEventHandler(MainCanvas::OnEraseBackground), NULL, this);
	Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(MainCanvas::OnMouseEvent),
			NULL, this);
	Connect(wxEVT_LEFT_UP, wxMouseEventHandler(MainCanvas::OnMouseEvent), NULL,
			this);
	Connect(wxEVT_MIDDLE_DOWN, wxMouseEventHandler(MainCanvas::OnMouseEvent),
			NULL, this);
	Connect(wxEVT_MIDDLE_UP, wxMouseEventHandler(MainCanvas::OnMouseEvent),
			NULL, this);
	Connect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(MainCanvas::OnMouseEvent),
			NULL, this);
	Connect(wxEVT_RIGHT_UP, wxMouseEventHandler(MainCanvas::OnMouseEvent), NULL,
			this);
	Connect(wxEVT_MOTION, wxMouseEventHandler(MainCanvas::OnMouseEvent), NULL,
			this);
	Connect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(MainCanvas::OnMouseEvent),
			NULL, this);
	Connect(wxEVT_MIDDLE_DCLICK, wxMouseEventHandler(MainCanvas::OnMouseEvent),
			NULL, this);
	Connect(wxEVT_RIGHT_DCLICK, wxMouseEventHandler(MainCanvas::OnMouseEvent),
			NULL, this);
	Connect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(MainCanvas::OnMouseEvent),
			NULL, this);
	Connect(wxEVT_ENTER_WINDOW, wxMouseEventHandler(MainCanvas::OnMouseEvent),
			NULL, this);
	Connect(wxEVT_MOUSEWHEEL, wxMouseEventHandler(MainCanvas::OnMouseEvent),
			NULL, this);
	Connect(wxEVT_PAINT, wxPaintEventHandler(MainCanvas::OnPaint), NULL, this);

	//TODO: MAXIMIZE does not throw a EVT_SIZE. Workaround would be a timer to do a regular repaint.
	Connect(wxEVT_SIZE, wxSizeEventHandler(MainCanvas::OnSize), NULL, this);

	mouse_x = mouse_y = 0;
	rotx = rotz = 0.0;
	transx = transy = transz = 0.0;
}

MainCanvas::~MainCanvas()
{
	// Disconnect Events
	Disconnect(wxEVT_ENTER_WINDOW,
			wxMouseEventHandler(MainCanvas::OnEnterWindow), NULL, this);
	Disconnect(wxEVT_ERASE_BACKGROUND,
			wxEraseEventHandler(MainCanvas::OnEraseBackground), NULL, this);
	Disconnect(wxEVT_LEFT_DOWN, wxMouseEventHandler(MainCanvas::OnMouseEvent),
			NULL, this);
	Disconnect(wxEVT_LEFT_UP, wxMouseEventHandler(MainCanvas::OnMouseEvent),
			NULL, this);
	Disconnect(wxEVT_MIDDLE_DOWN, wxMouseEventHandler(MainCanvas::OnMouseEvent),
			NULL, this);
	Disconnect(wxEVT_MIDDLE_UP, wxMouseEventHandler(MainCanvas::OnMouseEvent),
			NULL, this);
	Disconnect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(MainCanvas::OnMouseEvent),
			NULL, this);
	Disconnect(wxEVT_RIGHT_UP, wxMouseEventHandler(MainCanvas::OnMouseEvent),
			NULL, this);
	Disconnect(wxEVT_MOTION, wxMouseEventHandler(MainCanvas::OnMouseEvent),
			NULL, this);
	Disconnect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(MainCanvas::OnMouseEvent),
			NULL, this);
	Disconnect(wxEVT_MIDDLE_DCLICK,
			wxMouseEventHandler(MainCanvas::OnMouseEvent), NULL, this);
	Disconnect(wxEVT_RIGHT_DCLICK,
			wxMouseEventHandler(MainCanvas::OnMouseEvent), NULL, this);
	Disconnect(wxEVT_LEAVE_WINDOW,
			wxMouseEventHandler(MainCanvas::OnMouseEvent), NULL, this);
	Disconnect(wxEVT_ENTER_WINDOW,
			wxMouseEventHandler(MainCanvas::OnMouseEvent), NULL, this);
	Disconnect(wxEVT_MOUSEWHEEL, wxMouseEventHandler(MainCanvas::OnMouseEvent),
			NULL, this);
	Disconnect(wxEVT_PAINT, wxPaintEventHandler(MainCanvas::OnPaint), NULL,
			this);
	Disconnect(wxEVT_SIZE, wxSizeEventHandler(MainCanvas::OnSize), NULL, this);

}

void MainCanvas::OnEnterWindow(wxMouseEvent& WXUNUSED(event))
{
	SetFocus();
}

void MainCanvas::OnSize(wxSizeEvent& event)
{
	// this is also necessary to update the context on some platforms
	wxGLCanvas::OnSize(event);
	this->Refresh();
}

void MainCanvas::OnEraseBackground(wxEraseEvent& WXUNUSED(event))
{
	// Do nothing, to avoid flashing.
}

void MainCanvas::OnMouseEvent(wxMouseEvent& event)
{

	if(event.ButtonDown(wxMOUSE_BTN_ANY)){
		mouse_x = event.m_x;
		mouse_y = event.m_y;
	}

	if(event.Dragging() && event.ButtonIsDown(wxMOUSE_BTN_LEFT)){
		transx += (float) (event.m_x - mouse_x) / 1000;
		transz -= (float) (event.m_y - mouse_y) / 1000;
	}
	if(event.GetWheelRotation() != 0){
		transy += (float) event.GetWheelRotation() / 1000;
	}

	if(event.Dragging() && event.ButtonIsDown(wxMOUSE_BTN_RIGHT)){
		rotz -= (float) (event.m_x - mouse_x) / 5;
		rotx -= (float) (event.m_y - mouse_y) / 5;
	}

	if(event.Dragging() || event.GetWheelRotation() != 0){
		mouse_x = event.m_x;
		mouse_y = event.m_y;
		this->Refresh();
	}

}

void MainCanvas::InitGL()
{
	SetCurrent();

	/* set viewing projection */
	//	glMatrixMode(GL_PROJECTION);
	//	glFrustum( -0.5f, 0.5f, -0.5f, 0.5f, 1.0f, 3.0f);
	// Is done in OnSize(...)
	//	GLfloat attenuation[] =
	//		{1.0f, -0.01f, -.000001f};
	//::glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, attenuation, 0);
	::glEnable(GL_COLOR_MATERIAL);
	::glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//::glBlendFunc(GL_ONE, GL_ONE); // for Stereo Mode

	::glEnable(GL_BLEND);
	::glEnable(GL_POINT_SMOOTH);
	::glEnable(GL_DEPTH_TEST);
	SetupLighting();
	this->Refresh();

}

void MainCanvas::SetupLighting()
{
	GLfloat ambient0[] =
		{0.2f, 0.2f, 0.2f};
	GLfloat diffuse0[] =
		{0.5f, 0.5f, 0.5f};
	GLfloat specular0[] =
		{0.9f, 0.9f, 0.9f};
	GLfloat position0[] =
		{-100, 200, 500, 0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
	glLightfv(GL_LIGHT0, GL_POSITION, position0);
	glEnable(GL_LIGHT0); // ... and activate

	::glEnable(GL_LIGHTING);
}

void MainCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	if(!IsShown()) return;

#ifndef __WXMOTIF__
	if(!GetContext()) return;
#endif

	wxGLCanvas::SetCurrent();
	wxPaintDC(this);

	// Init OpenGL once, but after SetCurrent
	if(!isInitialized){
		InitGL();
		isInitialized = true;
	}

	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();

	// Switch to a coronal coordinate system (i.e. You look the patient directly into the face)
	// Z is upwards, X is to the right, and Y is toward the viewer
	::glScalef(1.0, 1.0, -1.0); // Change right hande to left handed by inverting Z
	::glRotatef(-90, 1.0, 0.0, 0.0); // Rotate Z upwards

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDrawBuffer(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set GL viewport (not called by wxGLCanvas::OnSize on all platforms...)
	int w, h;
	GetClientSize(&w, &h);
#ifndef __WXMOTIF__
	if(GetContext())
#endif
	{
		SetCurrent();
		::glViewport(0, 0, (GLint) w, (GLint) h);
		GLdouble ar = (GLdouble) w / (GLdouble) h; // setup perspective
		::glMatrixMode(GL_PROJECTION);
		::glLoadIdentity();
		::gluPerspective(45, ar, 0.01, 10);
		::glMatrixMode(GL_MODELVIEW);
	}

	::glTranslatef(0, -1.0, 0.0); // Move the origin back by 1 meter.
	::glTranslatef(transx, transy, transz); // Move the origin
	::glRotatef(rotx, 1, 0, 0); // Rotate around X, ...
	::glRotatef(rotz, 0, 0, 1); // ... then rotate around Z (turntable style)

	//	::glMultMatrixd(transmat.a);
	//	::glMultMatrixd(rotmat.a);

	Render();

	glFlush();
	SwapBuffers();
}

void MainCanvas::RenderCoordinateSystem(void)
{
	glBegin(GL_LINES);

	glColor3b(32, 32, 32);
	glNormal3f(-1, 0, 0);
	glVertex3f(-1, 0, 0);
	glColor3b(127, 0, 0);
	glNormal3f(1, 0, 0);
	glVertex3f(1, 0, 0);

	glColor3b(32, 32, 32);
	glNormal3f(0, -1, 0);
	glVertex3f(0, -1, 0);
	glColor3b(0, 127, 0);
	glNormal3f(0, 1, 0);
	glVertex3f(0, 1, 0);

	glColor3b(32, 32, 32);
	glNormal3f(0, 0, -1);
	glVertex3f(0, 0, -1);
	glColor3b(0, 0, 127);
	glNormal3f(0, 0, 1);
	glVertex3f(0, 0, 1);

	glEnd();
}

void MainCanvas::Render()
{
	::glEnable(GL_RESCALE_NORMAL);
	RenderCoordinateSystem();

	::glDisable(GL_RESCALE_NORMAL);

	//Headform:
	//plot(-(u+1)*(1-t).^3+u*(1-t).^2+1,-(u+1)*t.^3+u*t.^2+1,'-x')

}
