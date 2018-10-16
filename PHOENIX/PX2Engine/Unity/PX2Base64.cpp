// PX2Base64.cpp

#include "PX2Base64.hpp"
using namespace PX2;

//----------------------------------------------------------------------------
static const std::string _base64_table =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";
static const char base64_pad = '=';
//----------------------------------------------------------------------------
Base64::Base64()
{
}
//----------------------------------------------------------------------------
Base64::~Base64()
{
}
//----------------------------------------------------------------------------
std::string Base64::Encode(std::string const& s)
{
	return Encode((unsigned char const*)s.c_str(), s.length());
}
//----------------------------------------------------------------------------
std::string Base64::Encode(const unsigned char * str, int bytes)
{
	int num = 0, bin = 0, i;
	std::string _encode_result;
	const unsigned char * current;
	current = str;
	while (bytes > 2) {
		_encode_result += _base64_table[current[0] >> 2];
		_encode_result += _base64_table[((current[0] & 0x03) << 4) + (current[1] >> 4)];
		_encode_result += _base64_table[((current[1] & 0x0f) << 2) + (current[2] >> 6)];
		_encode_result += _base64_table[current[2] & 0x3f];

		current += 3;
		bytes -= 3;
	}
	if (bytes > 0)
	{
		_encode_result += _base64_table[current[0] >> 2];
		if (bytes % 3 == 1) {
			_encode_result += _base64_table[(current[0] & 0x03) << 4];
			_encode_result += "==";
		}
		else if (bytes % 3 == 2) {
			_encode_result += _base64_table[((current[0] & 0x03) << 4) + (current[1] >> 4)];
			_encode_result += _base64_table[(current[1] & 0x0f) << 2];
			_encode_result += "=";
		}
	}
	return _encode_result;
}
//----------------------------------------------------------------------------
std::string Base64::Decode(const std::string &encoded_string, int &outLength)
{
	return Decode(encoded_string.c_str(), encoded_string.length(), outLength);
}
//----------------------------------------------------------------------------
std::string Base64::Decode(const char *str, int length, int &outLength)
{
	//解码表
	const char DecodeTable[] =
	{
		-2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -1, -2, -2, -1, -2, -2,
		-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
		-1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, 62, -2, -2, -2, 63,
		52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -2, -2, -2, -2, -2, -2,
		-2,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
		15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -2, -2, -2, -2, -2,
		-2, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
		41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -2, -2, -2, -2, -2,
		-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
		-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
		-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
		-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
		-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
		-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
		-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
		-2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2
	};
	int bin = 0, i = 0, pos = 0;
	std::string _decode_result;
	const char *current = str;
	char ch = *current++;
	while (length-- > 0)
	{
		if (ch == base64_pad)
		{ // 当前一个字符是“=”号
								/*
								先说明一个概念：在解码时，4个字符为一组进行一轮字符匹配。
								两个条件：
								1、如果某一轮匹配的第二个是“=”且第三个字符不是“=”，说明这个带解析字符串不合法，直接返回空
								2、如果当前“=”不是第二个字符，且后面的字符只包含空白符，则说明这个这个条件合法，可以继续。
								*/
			if (*current != '=' && (i % 4) == 1) 
			{
				return 0;
			}

			continue;
		}

		ch = DecodeTable[ch];

		//这个很重要，用来过滤所有不合法的字符
		if (ch < 0)
		{ /* a space or some other separator character, we simply skip over */
			continue;
		}

		switch (i % 4)
		{
		case 0:
			bin = ch << 2;
			break;
		case 1:
			bin |= ch >> 4;
			_decode_result += bin;
			outLength += 1;
			bin = (ch & 0x0f) << 4;
			break;
		case 2:
			bin |= ch >> 2;
			_decode_result += bin;
			outLength += 1;
			bin = (ch & 0x03) << 6;
			break;
		case 3:
			bin |= ch;
			_decode_result += bin;
			outLength += 1;
			break;
		}
		i++;
		
		ch = *current++;
	}
	return _decode_result;
}
//----------------------------------------------------------------------------