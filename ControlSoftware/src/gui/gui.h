///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __gui__
#define __gui__

#include <wx/intl.h>

#include <wx/statusbr.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include "MainCanvas.h"
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include <wx/textctrl.h>
#include <wx/dialog.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>
#include <wx/statbox.h>
#include <wx/slider.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class GUIMainFrame
///////////////////////////////////////////////////////////////////////////////
class GUIMainFrame : public wxFrame 
{
	private:
	
	protected:
		enum
		{
			ID_CONNECT = 1000,
			ID_CONTROLCURRENTS,
			ID_DISCONNECT,
			wxID_QUIT,
			wxID_SETUPSERIALPORT,
		};
		
		wxStatusBar* m_statusBar;
		wxMenuBar* m_menubar;
		wxMenu* menuProject;
		wxMenu* menuSettings;
		wxMenu* menuHelp;
		MainCanvas* m_canvas;
		
		wxButton* m_buttonConnect;
		
		wxButton* m_buttonCurrents;
		
		wxButton* m_buttonDisconnect;
		
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnConnect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnControlCurrents( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDisconnect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnQuit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSetupHardware( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnChangeLanguage( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAbout( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIMainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Open-rTMS Control Center V0.2"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 518,350 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~GUIMainFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIAboutDialog
///////////////////////////////////////////////////////////////////////////////
class GUIAboutDialog : public wxDialog 
{
	private:
	
	protected:
		wxTextCtrl* m_textCtrl2;
		wxButton* m_button;
	
	public:
		
		GUIAboutDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Open-rTMS About"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,400 ), long style = wxDEFAULT_DIALOG_STYLE );
		~GUIAboutDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUISerialSetupDialog
///////////////////////////////////////////////////////////////////////////////
class GUISerialSetupDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		
		wxCheckBox* m_checkBoxOpenOnStartup;
		wxTextCtrl* m_textCtrlPort;
		wxButton* m_buttonConnect;
		wxButton* m_buttonDisconnect;
		wxButton* m_buttonProgramGenerator;
		wxCheckBox* m_checkBoxWriteEEprom;
		wxTextCtrl* m_textCtrlLog;
		wxButton* m_buttonOK;
		wxButton* m_buttonCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnConnect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDisconnect( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnProgramGenerator( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUISerialSetupDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Open-rTMS Setup Serial Connection"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 454,454 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxSTAY_ON_TOP );
		~GUISerialSetupDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIControlCurrentsDialog
///////////////////////////////////////////////////////////////////////////////
class GUIControlCurrentsDialog : public wxDialog 
{
	private:
	
	protected:
		enum
		{
			ID_CHANNEL0 = 1000,
			ID_CHANNEL1,
			ID_CHANNEL2,
			ID_CHANNEL3,
			ID_CHANNEL4,
			ID_CHANNEL5,
			ID_CHANNEL6,
			ID_CHANNEL7,
		};
		
		wxStaticText* m_staticText5;
		wxStaticText* m_staticText6;
		wxStaticText* m_staticText7;
		wxStaticText* m_staticText8;
		wxStaticText* m_staticText9;
		wxStaticText* m_staticText10;
		wxStaticText* m_staticText11;
		wxStaticText* m_staticText4;
		wxSlider* m_slider0;
		wxSlider* m_slider1;
		wxSlider* m_slider2;
		wxSlider* m_slider3;
		wxSlider* m_slider4;
		wxSlider* m_slider5;
		wxSlider* m_slider6;
		wxSlider* m_slider7;
		wxButton* m_buttonCancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnScroll0( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnScroll1( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnScroll2( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnScroll3( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnScroll4( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnScroll5( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnScroll6( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnScroll7( wxScrollEvent& event ) { event.Skip(); }
		virtual void OnButtonClose( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIControlCurrentsDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Current Control"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 716,455 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~GUIControlCurrentsDialog();
	
};

#endif //__gui__
