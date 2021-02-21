///////////////////////////////////////////////////////////////////////////////
// Name               : languages.h
// Purpose            : Definition of the supported languages.
// Thread Safe        : Yes
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 11.12.2011
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


#ifndef LANGUAGES_H_
#define LANGUAGES_H_

/*!\class languages
 * \brief Definition of the languages provided in the i18n directory.
 */

#include <wx/string.h>
#include <wx/intl.h>

// language data
static const wxLanguage langIds[] =
	{wxLANGUAGE_DEFAULT, wxLANGUAGE_ENGLISH, wxLANGUAGE_GERMAN};

const wxString langNames[] =
	{_T("System default"), _T("English"), _T("German")};

// the arrays must be in sync
wxCOMPILE_TIME_ASSERT( WXSIZEOF(langNames) == WXSIZEOF(langIds),
		LangArraysMismatch );

#endif /* LANGUAGES_H_ */
