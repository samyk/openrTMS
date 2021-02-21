///////////////////////////////////////////////////////////////////////////////
// Name               : ParallaxPropeller.h
// Purpose            : 
// Thread Safe        : No
// Platform dependent : No
// Compiler Options   :
// Author             : Tobias Schaefer
// Created            : 20.02.2012
// Copyright          : (C) 2012 Tobias Schaefer <tobiassch@users.sourceforge.net>
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


#ifndef PARALLAXPROPELLER_H_
#define PARALLAXPROPELLER_H_

/*!\class ParallaxPropeller
 * \brief Programmer for a Parallax Propeller
 *
 * This class contains functions for Programming the RAM and also the I2C-EEPROM connected
 * to a Parallax Propeller CPU.
 *
 * http://propeller.wikispaces.com/Download+Protocol
 */

#include "SerialPort.h"

#include <wx/string.h>
#include <wx/filename.h>
#include <stdint.h>

class ParallaxPropeller {
public:
	ParallaxPropeller(SerialPort* serial);
	virtual ~ParallaxPropeller();

	// Member variables
public:

	wxString log;

private:
	SerialPort* serial;

	unsigned char version;

	// Member functions
public:
	int GetVersion(void);
	bool UploadAndStart(wxFileName filename, bool burnToEEPROM = false);

private:
	bool HandShake(void);
	void Transmit8(uint8_t val);
	void Transmit32(uint32_t val);

};

#endif /* PARALLAXPROPELLER_H_ */
