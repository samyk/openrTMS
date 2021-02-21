///////////////////////////////////////////////////////////////////////////////
// Name               : Open-rTMS.cpp
// Purpose            : Main entry point.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 21.02.2010
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

#include "Open-rTMS.h"
#include "languages.h"
#include "Config.h"

#include <wx/config.h>

#ifndef __WIN32__
#include "icon/logo.xpm"
#endif

// The line that starts it all.
IMPLEMENT_APP(OpenrTMSApp)

OpenrTMSApp::OpenrTMSApp()
{

	// Setup the language and the i18n translations:

	unsigned int selectedLanguage = wxLocale::GetSystemLanguage();
	if(selectedLanguage == wxLANGUAGE_UNKNOWN) selectedLanguage =
			wxLANGUAGE_DEFAULT;

	// Read language from config:
	wxConfig *config = new wxConfig(_T(_OPENRTMS_NAMEOFCONFIG));
	wxString str;
	if(config->Read(_T("Language"), &str)){
		unsigned int i;
		for(i = 0; i < WXSIZEOF(langNames); i++)
			if(str.CmpNoCase(langNames[i]) == 0){
				selectedLanguage = langIds[i];
			}
	}
	// The config is closed / deleted immediately, because the MainFrame
	// opens the config as well. It is not needed in the App class anymore.
	delete config;

	// Set the language:
	//TODO: Why does wxLOCALE_CONV_ENCODING not work?
	if(!locale.Init(selectedLanguage, wxLOCALE_LOAD_DEFAULT)){
		wxLogError(_T("This language is not supported by the system!"));
		return;
	}

	locale.AddCatalogLookupPathPrefix(_T("i18n"));
	bool catalogLoaded = locale.AddCatalog(_T("Open-rTMS"));
	if(!catalogLoaded){
		wxLogError(
				_T("The translation catalog for ")
						+ locale.GetCanonicalName() + _T(" was not loaded!"));
	}
}

bool OpenrTMSApp::OnInit()
{
	frame = new MainFrame(NULL);

	//TODO: Check, why the icon is not working with Windows / Code::Blocks.
#ifndef __WIN32__
	wxIcon iconLogo(logo_xpm);
	frame->SetIcon(iconLogo);
#endif

	frame->Show(true);
	SetTopWindow(frame);

	return true;
}

/*! \mainpage Open-rTMS - Developers Documentation
 *
 * \image html  pictures/start.png
 *
 */

