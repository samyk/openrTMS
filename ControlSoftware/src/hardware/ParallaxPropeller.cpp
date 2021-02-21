///////////////////////////////////////////////////////////////////////////////
// Name               : ParallaxPropeller.cpp
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


#include "ParallaxPropeller.h"

#include <wx/utils.h>
#include <wx/file.h>

ParallaxPropeller::ParallaxPropeller(SerialPort* serial)
{
	this->serial = serial;
	version = 0;
	log.Empty();
}

ParallaxPropeller::~ParallaxPropeller()
{

}

bool ParallaxPropeller::HandShake(void)
{
	if(!serial->IsOpen()) return false;

	serial->SetDTR(true);
	::wxMilliSleep(10);
	serial->SetDTR(false);
	::wxMilliSleep(10);
	serial->SetDTR(true);
	::wxMilliSleep(90);

	char temp[250];


	// Flush old data on serial port.
	serial->FlushData();

	temp[0] = 0xF9;
	serial->SendData(temp, 1);

	unsigned char LFSR = 0x50;
	unsigned int i;
	for(i = 0; i < 250; i++){
		if(LFSR & 1){
			temp[i] = 0xff;
		}else{
			temp[i] = 0xfe;
		}
		LFSR = (LFSR << 1) | (((LFSR >> 7) ^ (LFSR >> 5) ^ (LFSR >> 4) ^ (LFSR
				>> 1)) & 1);
	}
	serial->SendData(temp, 250);
	serial->WaitTXFinish();
	for(i = 0; i < 250; i++)
		temp[i] = 0xf9;
	serial->SendData(temp, 250);
	serial->WaitTXFinish();
	::wxMilliSleep(25);
	i = serial->ReadData(temp, 250);

	if(i == 0){
		log += _T("No data received on this port!\n");
		return false;
	}

	if(i != 250){
		log
				+= wxString::Format(
						_T("Identification sequence: Only %d of 250 bit received!\n"),
						i);
		return false;
	}
	for(i = 0; i < 250; i++){
		if((unsigned char) temp[i] != (0xfe | (LFSR & 1))){
			log
					+= wxString::Format(
							_T("Bit %u in identification sequence is false!\n(received byte is 0x%02X instead of 0x%02X)\n"),
							i, temp[i], (0xfe | (LFSR & 1)));
			return false;
		}
		LFSR = (LFSR << 1) | (((LFSR >> 7) ^ (LFSR >> 5) ^ (LFSR >> 4) ^ (LFSR
				>> 1)) & 1);
	}
	//	serial->WaitTXFinish();
	//	::wxMilliSleep(10);
	//	i = serial->ReadDataWaiting();
	//	log += wxString::Format(_T("%d RX bytes on port.\n"), i);

	temp[0] = 0xf9;
	for(i = 0; i < 8; i++){
		serial->SendData(temp, 1);
	}
	serial->WaitTXFinish();
	::wxMilliSleep(1);
	i = serial->ReadData(temp, 250);

	if(i != 8){
		log += wxString::Format(
				_T("Chip version: Only %d of 8 bit received!\n"), i);
		return false;
	}

	version = 0;
	for(i = 0; i < 8; i++){
		version >>= 1;
		version |= ((temp[i] & 1) << 7);
	}
	return true;
}

void ParallaxPropeller::Transmit8(uint8_t val)
{
	if(!serial->IsOpen()) return;
	unsigned char i;
	unsigned char temp[3];
	temp[0] = 0x92; // = 0b10010010 = Bit 2 1 0
	temp[1] = 0x92; // = 0b10010010 = Bit 5 4 3
	temp[2] = 0xf2; // = 0b11110010 = Bit   7 6
	unsigned char p = 0;
	for(i = 0; i < 8; i++){
		if((i % 3) == 0) temp[p] |= ((val & 1) << 0);
		if((i % 3) == 1) temp[p] |= ((val & 1) << 3);
		if((i % 3) == 2) temp[p++] |= ((val & 1) << 6);
		val >>= 1;
	}
	serial->SendData((char*) temp, 3);
}
void ParallaxPropeller::Transmit32(uint32_t val)
{
	if(!serial->IsOpen()) return;
	unsigned char i;
	unsigned char temp[11];
	for(i = 0; i < 10; i++)
		temp[i] = 0x92;
	temp[10] = 0xf2;
	unsigned char p = 0;
	for(i = 0; i < 32; i++){
		if((i % 3) == 0) temp[p] |= ((val & 1) << 0);
		if((i % 3) == 1) temp[p] |= ((val & 1) << 3);
		if((i % 3) == 2) temp[p++] |= ((val & 1) << 6);
		val >>= 1;
	}
	serial->SendData((char*) temp, 11);
}

int ParallaxPropeller::GetVersion(void)
{
	if(!HandShake()) return -1;
	serial->SetDTR(false);
	::wxMilliSleep(10);
	serial->SetDTR(true);
	return version;
}

bool ParallaxPropeller::UploadAndStart(wxFileName filename, bool burnToEEPROM)
{
	wxFile file;
	if(!file.Open(filename.GetFullPath(), wxFile::read)){
		log += wxString::Format(_T("File could not be read!\n"));
		return false;
	}
	unsigned char buffer[32768];
	size_t n = file.Read(buffer, 32768);
	if(n == 0){
		log += wxString::Format(_T("File is empty!\n"));
		return false;
	}
	if(n < 16){
		log += wxString::Format(_T("File has no header!\n"));
		return false;
	}
	if((n % 4) != 0){
		log += wxString::Format(_T("Filelength is not a multitude of 4!\n"));
		return false;
	}

	log += wxString::Format(_T("%d bytes read from file.\n"), n);

	if(!HandShake()) return false;

	size_t i;
	//	i = serial->ReadDataWaiting();
	//	log += wxString::Format(_T("%d RX bytes on port.\n"), i);


	if(burnToEEPROM){
		Transmit32(3); // = Load RAM, write RAM to EEPROM, launch program.
	}else{
		Transmit32(1); // = Load RAM, launch program.
	}

	//	log += wxString::Format(_T("Prozess return.\n"));
	//	return true;


	//n = 1300;

	Transmit32(n >> 2); // Number of longs in file
	serial->WaitTXFinish();


	//	size_t i;
	uint32_t val;
	for(i = 0; i < n; i += 4){
		val = (buffer[i + 3] << 24) | (buffer[i + 2] << 16) | (buffer[i + 1]
				<< 8) | (buffer[i + 0] << 0);
		//		val = (buffer[i + 0] << 24) | (buffer[i + 1] << 16) | (buffer[i + 2]
		//				<< 8) | (buffer[i + 3] << 0);
		Transmit32(val);
		serial->WaitTXFinish();
	}

	// Read back checksum result
	n = 0;
	char temp[10];
	do{
		temp[0] = 0xf9;
		serial->SendData(temp, 1);
		serial->WaitTXFinish();
		::wxMilliSleep(10);
		i = serial->ReadDataWaiting();
		n++;
	}while(i == 0 && n < 100);

	if(i > 0){
		i = serial->ReadData(temp, 10);
	}

	//	log += wxString::Format(_T("Start nach %d Impulsen! (%.3f Sekunden)\n"), n,
	//			(float) n * 9e-3);

	if(i != 1){
		log += wxString::Format(
				_T("Wrong number of bytes received (Bytecount = %d)!\n"),
				i);

		if(i > 10) i = 10;
		for(n = 0; n < i; n++){
			log += wxString::Format(_T("Byte %d = 0x%02X\n"), n,
					(unsigned char) temp[n]);
		}
		return false;
	}
	if((unsigned char) temp[0] != 0xFE){
		log += wxString::Format(
				_T("Program verification failed!\n(Result = 0x%02X)\n"),
				(unsigned char) temp[0]);
		return false;
	}

	if(!burnToEEPROM) return true;

	// Burn data to EEPROM

	log += wxString::Format(_T("Programming EEPROM...\n"));
	temp[0] = 0xf9;
	n = 0;
	do{
		serial->SendData(temp, 1);
		serial->WaitTXFinish();
		::wxMilliSleep(10);
		i = serial->ReadDataWaiting();
		n++;
	}while(i == 0 && n < 300);

	if(i > 0) i = serial->ReadData(temp, 10);
	log += wxString::Format(_T("Programming took %.3f seconds.\n"), (float) n
			* 0.01);

	if(i != 1){
		log += wxString::Format(
				_T("Wrong number of bytes received (Bytecount = %d)!\n"),
				i);

		if(i > 10) i = 10;
		for(n = 0; n < i; n++){
			log += wxString::Format(_T("Byte %d = 0x%02X\n"), n,
					(unsigned char) temp[n]);
		}
		return false;
	}
	if((unsigned char) temp[0] != 0xFE){
		log += wxString::Format(
				_T("Programming EEPROM failed!\n(Result = 0x%02X)\n"),
				(unsigned char) temp[0]);
		return false;
	}
	log += wxString::Format(_T("OK!\n"));


	// Verify EEPROM

	log += wxString::Format(_T("Verifying EEPROM...\n"));
	temp[0] = 0xf9;
	n = 0;
	do{
		serial->SendData(temp, 1);
		serial->WaitTXFinish();
		::wxMilliSleep(10);
		i = serial->ReadDataWaiting();
		n++;
	}while(i == 0 && n < 300);
	if(i > 0) i = serial->ReadData(temp, 10);

	log += wxString::Format(_T("Verification took %.3f seconds.\n"), (float) n
			* 0.01);

	if(i != 1){
		log += wxString::Format(
				_T("Wrong number of bytes received (Bytecount = %d)!\n"),
				i);

		if(i > 10) i = 10;
		for(n = 0; n < i; n++){
			log += wxString::Format(_T("Byte %d = 0x%02X\n"), n,
					(unsigned char) temp[n]);
		}
		return false;
	}
	if((unsigned char) temp[0] != 0xFE){
		log += wxString::Format(
				_T("Verification of EEPROM failed!\n(Result = 0x%02X)\n"),
				(unsigned char) temp[0]);
		return false;
	}
	log += wxString::Format(_T("OK!\n"));

	return true;
}

