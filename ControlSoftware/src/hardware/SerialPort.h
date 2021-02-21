///////////////////////////////////////////////////////////////////////////////
// Name               : SerialPort.h
// Purpose            : A serial port class for Linux, Windows, and macOS.
// Thread Safe        : No
// Platform dependent : Yes
// Compiler Options   :
// Authors            : Tobias Schaefer, Samy Kamkar
// Created            : 08.09.2002
// Copyright          : (C) 2002 Tobias Schaefer <tobiassch@users.sourceforge.net>
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
//$LastChangedDate: 2010-05-04 01:09:07 +0200 (Di, 04. Mai 2010) $
//$Revision: 43 $
//$LastChangedBy: tobiassch $
///////////////////////////////////////////////////////////////////////////////

#ifndef __SERIALPORT_H__
#define __SERIALPORT_H__

/*!\class SerialPort
 * \brief Serial port class for Linux, Windows, and macOS
 *
 *
 */

#define FC_DTRDSR       0x01
#define FC_RTSCTS       0x02
#define FC_XONXOFF      0x04
#define ASCII_BEL       0x07
#define ASCII_BS        0x08
#define ASCII_LF        0x0A
#define ASCII_CR        0x0D
#define ASCII_XON       0x11
#define ASCII_XOFF      0x13

#define BUFFER_LEN	2100

#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__)
#define __WIN
#elif defined(linux) || defined(__linux)
#define __LINUX
#define __UNIX
#elif defined(__APPLE__)
#define __APPLE
#define __UNIX
#else
#error "Requires Linux, Windows, or macOS (Weder Linux noch Windows gefunden)!"
#endif

#ifdef __WIN
#include <windows.h>
#endif

#ifdef __LINUX
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#define _POSIX_SOURCE 1
#endif

#ifdef __APPLE
#include <stddef.h>
#include <wchar.h>
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#define _POSIX_SOURCE 1
#endif

class SerialPort {

public:
	SerialPort();
	virtual ~SerialPort();

	bool Open(int nPort = 2, int nBaud = 19200);
	bool Open(const char *Port = NULL, int nBaud = 19200);
	bool Close(void);

	int ReadData(char *, unsigned int);
	int SendData(char *, unsigned int);
	int ReadDataWaiting(void);
	void FlushData(void);
	bool IsOpen(void)
	{
		return (Opened);
	}
	char* GetName()
	{
		return (szPort);
	}
	void SetDTR(bool activate);
	void WaitTXFinish(void);

protected:
	bool Opened;

	char szPort[15]; ///> Name of the open port.

#ifdef __WIN
	bool WriteCommByte( unsigned char );
	HANDLE m_hIDComDev;
	OVERLAPPED m_OverlappedRead, m_OverlappedWrite;
#endif


#if defined(__LINUX) || defined(__APPLE)
	int fd, c, res;
	unsigned int buffer_RD, buffer_WR;
	char m_buffer[BUFFER_LEN];
	struct termios oldtio, newtio;

#endif

public:
	char Error[200];

};

#endif // __SERIALPORT_H__
