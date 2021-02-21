///////////////////////////////////////////////////////////////////////////////
// Name               : MainCanvas.h
// Purpose            :
// Thread Safe        : Yes
// Platform dependent : Yes
// Compiler Options   : -lopengl32 -lglu
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

#ifndef MAINCANVAS_H_
#define MAINCANVAS_H_

#include "../StdInclude.h"
#include "../Config.h"
#include <wx/glcanvas.h>

/*!\class MainCanvas
 * \brief Canvas for the Main Window
 *
 * It is basically a 2D display rendered in 3D.
 * (For the coolness factor, speed and everything.)
 */

class MainCanvas:public wxGLCanvas {
	// Constructor / Destructor
public:
	MainCanvas(wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint& pos =
			wxDefaultPosition, const wxSize& size = wxDefaultSize, long style =
			0, const wxString& name = _T("OpenGLCanvas"));
	virtual ~MainCanvas();
	// Member Variables
private:
	bool isInitialized; //! The OpenGL system is inititalized on the first paint event. It is flagged here!

public:
	::GLfloat rotx, rotz, transx, transy, transz;
	int mouse_x, mouse_y;

	// Methods
public:
	void InitGL();
	void SetupLighting();

	void RenderCoordinateSystem(void);
	void Render();

protected:
	void OnPaint(wxPaintEvent& WXUNUSED(event));
	void OnSize(wxSizeEvent& event);
	void OnEraseBackground(wxEraseEvent& WXUNUSED(event));
	void OnEnterWindow(wxMouseEvent& WXUNUSED(event));
	void OnMouseEvent(wxMouseEvent& event);
	void OnTimer(wxTimerEvent& event);
};

#endif /* MAINCANVAS_H_ */
