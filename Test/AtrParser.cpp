// AtrParser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "..\source\ISO7816Atr.hpp"

bool IsValidATR(unsigned char* buff, int len);

int main()
{
	unsigned char _valid_atr_1[] = { 0x3B, 0x9E, 0x96, 0x80, 0x1F, 0xC7, 0x80, 0x31, 0xE0, 0x73, 0xFE, 0x21, 0x1B, 0x66, 0xD0, 0x01, 0x6C, 0xCF, 0x0D, 0x00, 0xAF };
	bool valid = IsValidATR(_valid_atr_1, sizeof(_valid_atr_1) / sizeof(_valid_atr_1[0]));
	std::cout << "Valid ATR1: " << valid << std::endl;

	// NO TCK
	unsigned char _invalid_atr_1[] = { 0x3B, 0x9E, 0x96, 0x80, 0x1F, 0xC7, 0x80, 0x31, 0xE0, 0x73, 0xFE, 0x21, 0x1B, 0x66, 0xD0, 0x01, 0x6C, 0xCF, 0x0D, 0x00 };
	valid = IsValidATR(_invalid_atr_1, sizeof(_invalid_atr_1) / sizeof(_invalid_atr_1[0]));
	std::cout << "Invalid ATR1: " << valid << std::endl;

	// T0 only, expected no TCK
	unsigned char _valid_atr_2[] = { 0x3B, 0xE2, 0x00, 0x00, 0x40, 0x20, 0x49, 0x05 };
	valid = IsValidATR(_valid_atr_2, sizeof(_valid_atr_2) / sizeof(_valid_atr_2[0]));
	std::cout << "Valid ATR2: " << valid << std::endl;

	unsigned char _valid_atr_3[] = { 0x3B, 0x90, 0x95, 0x91, 0x81, 0xB1, 0xFE, 0x55, 0x1F, 0xC7, 0xD7 };
	valid = IsValidATR(_valid_atr_3, sizeof(_valid_atr_3) / sizeof(_valid_atr_3[0]));
	std::cout << "Valid ATR3: " << valid << std::endl;
	

	return 0;
}

bool IsValidATR(unsigned char* buff, int len)
{
	try
	{
		ISO7816Atr::ptr _parser = ISO7816Atr::factory();
		for (int i = 0; i < len; i++)
		{
			_parser->PushData(buff[i]);
		}
		bool _valid = _parser->Valid();
		if (_valid)
		{
			std::string tmp = _parser->ToString();
		}
		return _valid;
	}
	catch (std::exception&)
	{
		return false;
	}
}

