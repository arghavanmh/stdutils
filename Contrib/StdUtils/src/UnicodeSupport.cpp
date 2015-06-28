///////////////////////////////////////////////////////////////////////////////
// StdUtils plug-in for NSIS
// Copyright (C) 2004-2015 LoRd_MuldeR <MuldeR2@GMX.de>
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//
// http://www.gnu.org/licenses/lgpl-2.1.txt
///////////////////////////////////////////////////////////////////////////////

#include <Windows.h>

wchar_t *ansi_to_utf16(const char *const input)
{
	wchar_t *Buffer;
	int BuffSize, Result;
	BuffSize = MultiByteToWideChar(CP_ACP, 0, input, -1, NULL, 0);
	if(BuffSize > 0)
	{
		Buffer = new wchar_t[BuffSize];
		Result = MultiByteToWideChar(CP_UTF8, 0, input, -1, Buffer, BuffSize);
		return ((Result > 0) && (Result <= BuffSize)) ? Buffer : NULL;
	}
	return NULL;
}

wchar_t *utf8_to_utf16(const char *const input)
{
	wchar_t *Buffer;
	int BuffSize, Result;
	BuffSize = MultiByteToWideChar(CP_UTF8, 0, input, -1, NULL, 0);
	if(BuffSize > 0)
	{
		Buffer = new wchar_t[BuffSize];
		Result = MultiByteToWideChar(CP_UTF8, 0, input, -1, Buffer, BuffSize);
		return ((Result > 0) && (Result <= BuffSize)) ? Buffer : NULL;
	}
	return NULL;
}

char *utf16_to_utf8(const wchar_t *const input)
{
	char *Buffer;
	int BuffSize, Result;
	BuffSize = WideCharToMultiByte(CP_UTF8, 0, input, -1, NULL, 0, NULL, NULL);
	if(BuffSize > 0)
	{
		Buffer = new char[BuffSize];
		Result = WideCharToMultiByte(CP_UTF8, 0, input, -1, Buffer, BuffSize, NULL, NULL);
		return ((Result > 0) && (Result <= BuffSize)) ? Buffer : NULL;
	}
	return NULL;
}

inline static bool str_whitespace(const char c)
{
	return iscntrl(c) || isspace(c);	//return (c == ' ') || (c == '\t') || (c == '\n') || (c == '\r');
}

inline static bool wcs_whitespace(const wchar_t c)
{
	return iswcntrl(c) || iswspace(c);	//return (c == L' ') || (c == L'\t') || (c == L'\n') || (c == L'\r');
}

char *strtrim(char* input, bool trim_left, bool trim_right)
{
	if(trim_right && (input[0] != '\0'))
	{
		size_t right = strlen(input);
		while(right > 0)
		{
			if(!str_whitespace(input[--right])) break;
			input[right] = '\0';
		}
	}

	size_t left = 0;
	if(trim_left && (input[0] != '\0'))
	{
		while(str_whitespace(input[left])) left++;
	}

	return &input[left];
}

wchar_t *wcstrim(wchar_t* input, bool trim_left, bool trim_right)
{
	if(trim_right && (input[0] != L'\0'))
	{
		size_t right = wcslen(input);
		while(right > 0)
		{
			if(!wcs_whitespace(input[--right])) break;
			input[right] = L'\0';
		}
	}

	size_t left = 0;
	if(trim_left && (input[0] != L'\0'))
	{
		while(wcs_whitespace(input[left])) left++;
	}

	return &input[left];
}
