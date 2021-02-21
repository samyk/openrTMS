///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui.h"

///////////////////////////////////////////////////////////////////////////

GUIMainFrame::GUIMainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_statusBar = this->CreateStatusBar( 2, wxST_SIZEGRIP, wxID_ANY );
	m_menubar = new wxMenuBar( 0 );
	menuProject = new wxMenu();
	wxMenuItem* m_menuItemConnect;
	m_menuItemConnect = new wxMenuItem( menuProject, ID_CONNECT, wxString( _("&Connect") ) , wxEmptyString, wxITEM_NORMAL );
	menuProject->Append( m_menuItemConnect );
	
	wxMenuItem* m_menuItemControlCurrents;
	m_menuItemControlCurrents = new wxMenuItem( menuProject, ID_CONTROLCURRENTS, wxString( _("&Control currents") ) , wxEmptyString, wxITEM_NORMAL );
	menuProject->Append( m_menuItemControlCurrents );
	m_menuItemControlCurrents->Enable( false );
	
	wxMenuItem* m_menuItemDisconnect;
	m_menuItemDisconnect = new wxMenuItem( menuProject, ID_DISCONNECT, wxString( _("&Disconnect") ) , _("Disconnect from hardware"), wxITEM_NORMAL );
	menuProject->Append( m_menuItemDisconnect );
	m_menuItemDisconnect->Enable( false );
	
	wxMenuItem* m_separator1;
	m_separator1 = menuProject->AppendSeparator();
	
	wxMenuItem* m_menuItemQuit;
	m_menuItemQuit = new wxMenuItem( menuProject, wxID_QUIT, wxString( _("&Quit") ) + wxT('\t') + wxT("Ctrl+Q"), _("Quit the program."), wxITEM_NORMAL );
	menuProject->Append( m_menuItemQuit );
	
	m_menubar->Append( menuProject, _("&Project") );
	
	menuSettings = new wxMenu();
	wxMenuItem* m_menuItemSetupPort;
	m_menuItemSetupPort = new wxMenuItem( menuSettings, wxID_SETUPSERIALPORT, wxString( _("&Setup and program hardware") ) , _("Setup the serial port and program the hardware."), wxITEM_NORMAL );
	menuSettings->Append( m_menuItemSetupPort );
	
	wxMenuItem* m_menuItemLanguage;
	m_menuItemLanguage = new wxMenuItem( menuSettings, wxID_ANY, wxString( _("&Change language") ) , wxEmptyString, wxITEM_NORMAL );
	menuSettings->Append( m_menuItemLanguage );
	
	m_menubar->Append( menuSettings, _("&Settings") );
	
	menuHelp = new wxMenu();
	wxMenuItem* m_menuItem9;
	m_menuItem9 = new wxMenuItem( menuHelp, wxID_ABOUT, wxString( _("&About") ) , wxEmptyString, wxITEM_NORMAL );
	menuHelp->Append( m_menuItem9 );
	
	m_menubar->Append( menuHelp, _("&Help") );
	
	this->SetMenuBar( m_menubar );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_canvas = new MainCanvas(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	bSizer1->Add( m_canvas, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer13->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonConnect = new wxButton( this, wxID_ANY, _("Connect"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_buttonConnect, 0, wxALL, 5 );
	
	
	bSizer13->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonCurrents = new wxButton( this, wxID_ANY, _("Control currents"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonCurrents->Enable( false );
	
	bSizer13->Add( m_buttonCurrents, 0, wxALL, 5 );
	
	
	bSizer13->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_buttonDisconnect = new wxButton( this, wxID_ANY, _("Disconnect"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonDisconnect->Enable( false );
	
	bSizer13->Add( m_buttonDisconnect, 0, wxALL, 5 );
	
	
	bSizer13->Add( 0, 0, 1, wxEXPAND, 5 );
	
	bSizer1->Add( bSizer13, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	// Connect Events
	this->Connect( m_menuItemConnect->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnConnect ) );
	this->Connect( m_menuItemControlCurrents->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnControlCurrents ) );
	this->Connect( m_menuItemDisconnect->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnDisconnect ) );
	this->Connect( m_menuItemQuit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnQuit ) );
	this->Connect( m_menuItemSetupPort->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnSetupHardware ) );
	this->Connect( m_menuItemLanguage->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnChangeLanguage ) );
	this->Connect( m_menuItem9->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnAbout ) );
	m_buttonConnect->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIMainFrame::OnConnect ), NULL, this );
	m_buttonCurrents->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIMainFrame::OnControlCurrents ), NULL, this );
	m_buttonDisconnect->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIMainFrame::OnDisconnect ), NULL, this );
}

GUIMainFrame::~GUIMainFrame()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnConnect ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnControlCurrents ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnDisconnect ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnQuit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnSetupHardware ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnChangeLanguage ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIMainFrame::OnAbout ) );
	m_buttonConnect->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIMainFrame::OnConnect ), NULL, this );
	m_buttonCurrents->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIMainFrame::OnControlCurrents ), NULL, this );
	m_buttonDisconnect->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIMainFrame::OnDisconnect ), NULL, this );
}

GUIAboutDialog::GUIAboutDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	m_textCtrl2 = new wxTextCtrl( this, wxID_ANY, _("Open rTMS Control Center\n\n(C) Tobias Schäfer 2011\n\nGNU General Public License version 3.0 (GPLv3)\n\nThis program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.\nThis program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.\n\nYou should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>."), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	bSizer4->Add( m_textCtrl2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_button = new wxButton( this, wxID_CANCEL, _("Ok"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_button, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	this->SetSizer( bSizer4 );
	this->Layout();
}

GUIAboutDialog::~GUIAboutDialog()
{
}

GUISerialSetupDialog::GUISerialSetupDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Serial Port:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer14->Add( m_staticText1, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxALIGN_BOTTOM, 5 );
	
	
	bSizer14->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_checkBoxOpenOnStartup = new wxCheckBox( this, wxID_ANY, _("Open port on Startup"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( m_checkBoxOpenOnStartup, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	bSizer2->Add( bSizer14, 0, wxEXPAND, 5 );
	
	m_textCtrlPort = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_textCtrlPort, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonConnect = new wxButton( this, wxID_OK, _("Connect"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_buttonConnect, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonDisconnect = new wxButton( this, wxID_ANY, _("Disconnect"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonDisconnect->Enable( false );
	
	bSizer3->Add( m_buttonDisconnect, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer2->Add( bSizer3, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Programm hardware with...") ), wxVERTICAL );
	
	m_buttonProgramGenerator = new wxButton( this, wxID_ANY, _("rTMS - signal generator"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonProgramGenerator->Enable( false );
	
	sbSizer1->Add( m_buttonProgramGenerator, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_checkBoxWriteEEprom = new wxCheckBox( this, wxID_ANY, _("write the program to the EEPROM as well"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkBoxWriteEEprom->SetValue(true); 
	m_checkBoxWriteEEprom->Enable( false );
	
	sbSizer1->Add( m_checkBoxWriteEEprom, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer2->Add( sbSizer1, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_textCtrlLog = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	bSizer2->Add( m_textCtrlLog, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonOK = new wxButton( this, wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( m_buttonOK, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer8->Add( m_buttonCancel, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer2->Add( bSizer8, 0, wxALIGN_RIGHT, 5 );
	
	this->SetSizer( bSizer2 );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUISerialSetupDialog::OnClose ) );
	m_buttonConnect->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISerialSetupDialog::OnConnect ), NULL, this );
	m_buttonDisconnect->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISerialSetupDialog::OnDisconnect ), NULL, this );
	m_buttonProgramGenerator->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISerialSetupDialog::OnProgramGenerator ), NULL, this );
}

GUISerialSetupDialog::~GUISerialSetupDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUISerialSetupDialog::OnClose ) );
	m_buttonConnect->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISerialSetupDialog::OnConnect ), NULL, this );
	m_buttonDisconnect->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISerialSetupDialog::OnDisconnect ), NULL, this );
	m_buttonProgramGenerator->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUISerialSetupDialog::OnProgramGenerator ), NULL, this );
}

GUIControlCurrentsDialog::GUIControlCurrentsDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 2, 8, 0, 0 );
	fgSizer1->AddGrowableCol( 0 );
	fgSizer1->AddGrowableCol( 1 );
	fgSizer1->AddGrowableCol( 2 );
	fgSizer1->AddGrowableCol( 3 );
	fgSizer1->AddGrowableCol( 4 );
	fgSizer1->AddGrowableCol( 5 );
	fgSizer1->AddGrowableCol( 6 );
	fgSizer1->AddGrowableCol( 7 );
	fgSizer1->AddGrowableRow( 1 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, _("Channel 0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	fgSizer1->Add( m_staticText5, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText6 = new wxStaticText( this, wxID_ANY, _("Channel 1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	fgSizer1->Add( m_staticText6, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText7 = new wxStaticText( this, wxID_ANY, _("Channel 2"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	fgSizer1->Add( m_staticText7, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText8 = new wxStaticText( this, wxID_ANY, _("Channel 3"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	fgSizer1->Add( m_staticText8, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText9 = new wxStaticText( this, wxID_ANY, _("Channel 4"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	fgSizer1->Add( m_staticText9, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText10 = new wxStaticText( this, wxID_ANY, _("Channel 5"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	fgSizer1->Add( m_staticText10, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText11 = new wxStaticText( this, wxID_ANY, _("Channel 6"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	fgSizer1->Add( m_staticText11, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, _("Channel 7"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	fgSizer1->Add( m_staticText4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_slider0 = new wxSlider( this, ID_CHANNEL0, 0, -250, 250, wxDefaultPosition, wxDefaultSize, wxSL_AUTOTICKS|wxSL_INVERSE|wxSL_LABELS|wxSL_VERTICAL );
	fgSizer1->Add( m_slider0, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	m_slider1 = new wxSlider( this, ID_CHANNEL1, 0, -250, 250, wxDefaultPosition, wxDefaultSize, wxSL_AUTOTICKS|wxSL_INVERSE|wxSL_LABELS|wxSL_VERTICAL );
	fgSizer1->Add( m_slider1, 1, wxALL|wxEXPAND, 5 );
	
	m_slider2 = new wxSlider( this, ID_CHANNEL2, 0, -250, 250, wxDefaultPosition, wxDefaultSize, wxSL_AUTOTICKS|wxSL_INVERSE|wxSL_LABELS|wxSL_VERTICAL );
	fgSizer1->Add( m_slider2, 1, wxALL|wxEXPAND, 5 );
	
	m_slider3 = new wxSlider( this, ID_CHANNEL3, 0, -250, 250, wxDefaultPosition, wxDefaultSize, wxSL_AUTOTICKS|wxSL_INVERSE|wxSL_LABELS|wxSL_VERTICAL );
	fgSizer1->Add( m_slider3, 1, wxALL|wxEXPAND, 5 );
	
	m_slider4 = new wxSlider( this, ID_CHANNEL4, 0, -250, 250, wxDefaultPosition, wxDefaultSize, wxSL_AUTOTICKS|wxSL_INVERSE|wxSL_LABELS|wxSL_VERTICAL );
	fgSizer1->Add( m_slider4, 1, wxALL|wxEXPAND, 5 );
	
	m_slider5 = new wxSlider( this, ID_CHANNEL5, 0, -250, 250, wxDefaultPosition, wxDefaultSize, wxSL_AUTOTICKS|wxSL_INVERSE|wxSL_LABELS|wxSL_VERTICAL );
	fgSizer1->Add( m_slider5, 1, wxALL|wxEXPAND, 5 );
	
	m_slider6 = new wxSlider( this, ID_CHANNEL6, 0, -250, 250, wxDefaultPosition, wxDefaultSize, wxSL_AUTOTICKS|wxSL_INVERSE|wxSL_LABELS|wxSL_VERTICAL );
	fgSizer1->Add( m_slider6, 1, wxALL|wxEXPAND, 5 );
	
	m_slider7 = new wxSlider( this, ID_CHANNEL7, 0, -250, 250, wxDefaultPosition, wxDefaultSize, wxSL_AUTOTICKS|wxSL_INVERSE|wxSL_LABELS|wxSL_VERTICAL );
	fgSizer1->Add( m_slider7, 1, wxALL|wxEXPAND, 5 );
	
	bSizer12->Add( fgSizer1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_buttonCancel = new wxButton( this, wxID_ANY, _("Close Dialog"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( m_buttonCancel, 0, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( bSizer12 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_slider0->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIControlCurrentsDialog::OnScroll0 ), NULL, this );
	m_slider1->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIControlCurrentsDialog::OnScroll1 ), NULL, this );
	m_slider2->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIControlCurrentsDialog::OnScroll2 ), NULL, this );
	m_slider3->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIControlCurrentsDialog::OnScroll3 ), NULL, this );
	m_slider4->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIControlCurrentsDialog::OnScroll4 ), NULL, this );
	m_slider5->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIControlCurrentsDialog::OnScroll5 ), NULL, this );
	m_slider6->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIControlCurrentsDialog::OnScroll6 ), NULL, this );
	m_slider7->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIControlCurrentsDialog::OnScroll7 ), NULL, this );
	m_buttonCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIControlCurrentsDialog::OnButtonClose ), NULL, this );
}

GUIControlCurrentsDialog::~GUIControlCurrentsDialog()
{
	// Disconnect Events
	m_slider0->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIControlCurrentsDialog::OnScroll0 ), NULL, this );
	m_slider1->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIControlCurrentsDialog::OnScroll1 ), NULL, this );
	m_slider2->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIControlCurrentsDialog::OnScroll2 ), NULL, this );
	m_slider3->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIControlCurrentsDialog::OnScroll3 ), NULL, this );
	m_slider4->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIControlCurrentsDialog::OnScroll4 ), NULL, this );
	m_slider5->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIControlCurrentsDialog::OnScroll5 ), NULL, this );
	m_slider6->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIControlCurrentsDialog::OnScroll6 ), NULL, this );
	m_slider7->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIControlCurrentsDialog::OnScroll7 ), NULL, this );
	m_buttonCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIControlCurrentsDialog::OnButtonClose ), NULL, this );
}
