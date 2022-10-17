// Base64.cpp: implementation of the CBase64 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "smtp.h"
#include "Base64.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static char Base64Digits[] = 
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
BOOL CBase64::m_Init = FALSE;
char CBase64::m_DecodeTable[256];

#ifndef PAGESIZE
#define PAGESIZE    4096
#endif

#ifndef ROUNDTOPAGE
#define ROUNDTOPAGE(a)  (((a/4096)+1)*4096)
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBase64::CBase64() : m_pDBuffer(NULL), m_pEBuffer(NULL),
                           m_nDBufLen(0),	m_nEBufLen(0)
{
}

CBase64::~CBase64()
{
	if (m_pDBuffer != NULL)
	{
		delete [] m_pDBuffer;
		m_pDBuffer = NULL;
	}

	if (m_pEBuffer != NULL)
	{
		delete [] m_pEBuffer;
		m_pEBuffer = NULL;
	}
}

LPSTR CBase64::DecodedMessage() const 
{ 
	return (LPSTR) m_pDBuffer;
}

LPSTR CBase64::EncodedMessage() const
{ 
	return (LPSTR) m_pEBuffer;
}

LONG CBase64::DecodedMessageSize() const 
{ 
	return m_nDDataLen;
}

LONG CBase64::EncodedMessageSize() const
{ 
	return m_nEDataLen;
}

void CBase64::AllocEncode(DWORD nSize)
{
	if (m_nEBufLen < nSize)
	{
		if (m_pEBuffer != NULL)  delete [] m_pEBuffer;
		m_nEBufLen = ROUNDTOPAGE(nSize);
		m_pEBuffer = new BYTE[m_nEBufLen];
	}
	::ZeroMemory(m_pEBuffer, m_nEBufLen);
	m_nEDataLen = 0;
}

void CBase64::AllocDecode(DWORD nSize)
{
	if (m_nDBufLen < nSize)
	{
		if (m_pDBuffer != NULL)  delete [] m_pDBuffer;
		m_nDBufLen = ROUNDTOPAGE(nSize);
		m_pDBuffer = new BYTE[m_nDBufLen];
	}
	::ZeroMemory(m_pDBuffer, m_nDBufLen);
	m_nDDataLen = 0;
}

void CBase64::SetEncodeBuffer(const PBYTE pBuffer, DWORD nBufLen)
{
	DWORD  i = 0;
	AllocEncode(nBufLen);
	while(i < nBufLen)
	{
		if (!_IsBadMimeChar(pBuffer[i]))
		{
			m_pEBuffer[m_nEDataLen] = pBuffer[i];
			m_nEDataLen++;
		}
		i++;
	}
}

void CBase64::SetDecodeBuffer(const PBYTE pBuffer, DWORD nBufLen)
{
	AllocDecode(nBufLen);
	::CopyMemory(m_pDBuffer, pBuffer, nBufLen);
	m_nDDataLen = nBufLen;
}

void CBase64::Encode(const PBYTE pBuffer, DWORD nBufLen)
{
	SetDecodeBuffer(pBuffer, nBufLen);
	AllocEncode(nBufLen * 2);
	TempBucket  Raw;
	DWORD  nIndex  = 0;
	while ((nIndex + 3) <= nBufLen)
	{
		Raw.Clear();
		::CopyMemory(&Raw, m_pDBuffer + nIndex, 3);
		Raw.nSize = 3;
		_EncodeToBuffer(Raw, m_pEBuffer + m_nEDataLen);
		nIndex += 3;
		m_nEDataLen  += 4;
	}

	if (nBufLen > nIndex)
	{
		Raw.Clear();
		Raw.nSize = (BYTE) (nBufLen - nIndex);
		::CopyMemory(&Raw, m_pDBuffer + nIndex, nBufLen - nIndex);
		_EncodeToBuffer(Raw, m_pEBuffer + m_nEDataLen);
		m_nEDataLen += 4;
	}
}

void CBase64::Encode(LPCSTR szMessage)
{
	if (szMessage != NULL)
		Encode((const PBYTE)szMessage, strlen(szMessage));
}

void CBase64::Decode(const PBYTE pBuffer, DWORD dwBufLen)
{
	if (!CBase64::m_Init)  _Init();

	SetEncodeBuffer(pBuffer, dwBufLen);
	AllocDecode(dwBufLen);

	TempBucket Raw;
	DWORD   nIndex = 0;
	while((nIndex + 4) <= m_nEDataLen)
	{
		Raw.Clear();
		Raw.nData[0] = 
			CBase64::m_DecodeTable[m_pEBuffer[nIndex]];
	Raw.nData[1] = CBase64::m_DecodeTable[m_pEBuffer[nIndex + 1]];
	Raw.nData[2] = CBase64::m_DecodeTable[m_pEBuffer[nIndex + 2]];
	Raw.nData[3] = CBase64::m_DecodeTable[m_pEBuffer[nIndex + 3]];

		if (Raw.nData[2] == 255)  Raw.nData[2] = 0;
		if (Raw.nData[3] == 255)  Raw.nData[3] = 0;
 
		Raw.nSize = 4;
		_DecodeToBuffer(Raw, m_pDBuffer + m_nDDataLen);
		nIndex += 4;
		m_nDDataLen += 3;
	}
 
	if (nIndex < m_nEDataLen)
	{
		Raw.Clear();
		for (DWORD i=nIndex; i<m_nEDataLen; i++)
		{
			Raw.nData[i - nIndex] = 
			CBase64::m_DecodeTable[m_pEBuffer[i]];
			Raw.nSize++;
			if(Raw.nData[i - nIndex] == 255)
			Raw.nData[i - nIndex] = 0;
		}

		_DecodeToBuffer(Raw, m_pDBuffer + m_nDDataLen);
		m_nDDataLen += (m_nEDataLen - nIndex);
	}
}

void CBase64::Decode(LPCSTR szMessage)
{
	if (szMessage != NULL)
	Decode((const PBYTE)szMessage, strlen(szMessage));
}

DWORD CBase64::_DecodeToBuffer(const TempBucket &Decode, PBYTE pBuffer)
{
	TempBucket  Data;
	DWORD  nCount = 0;
	_DecodeRaw(Data, Decode);
	for (int i=0; i<3; i++)
	{
		pBuffer[i] = Data.nData[i];
		if(pBuffer[i] != 255) 	nCount++;
	}
	return nCount;
}


void CBase64::_EncodeToBuffer(const TempBucket &Decode, PBYTE pBuffer)
{
	TempBucket Data;
	_EncodeRaw(Data, Decode);
	for (int i=0; i<4; i++)
		pBuffer[i] = Base64Digits[Data.nData[i]];
	switch (Decode.nSize)
	{
	case 1:
		pBuffer[2] = '=';
	case 2:
		pBuffer[3] = '=';
	}
}

void CBase64::_DecodeRaw(TempBucket &Data, const TempBucket &Decode)
{
	BYTE nTemp;

	Data.nData[0] = Decode.nData[0];
	Data.nData[0] <<= 2;

	nTemp = Decode.nData[1];
	nTemp >>= 4;
	nTemp &= 0x03;
	Data.nData[0] |= nTemp;

	Data.nData[1] = Decode.nData[1];
	Data.nData[1] <<= 4;

	nTemp = Decode.nData[2];
	nTemp >>= 2;
	nTemp &= 0x0F;
	Data.nData[1] |= nTemp;

	Data.nData[2] = Decode.nData[2];
	Data.nData[2] <<= 6;
	nTemp = Decode.nData[3];
	nTemp &= 0x3F;
	Data.nData[2] |= nTemp;
}

void CBase64::_EncodeRaw(TempBucket &Data, const TempBucket &Decode)
{
	BYTE nTemp;

	Data.nData[0] = Decode.nData[0];
	Data.nData[0] >>= 2;
 
	Data.nData[1] = Decode.nData[0];
	Data.nData[1] <<= 4;
	nTemp = Decode.nData[1];
	nTemp >>= 4;
	Data.nData[1] |= nTemp;
	Data.nData[1] &= 0x3F;

	Data.nData[2] = Decode.nData[1];
	Data.nData[2] <<= 2;

	nTemp = Decode.nData[2];
	nTemp >>= 6;

	Data.nData[2] |= nTemp;
	Data.nData[2] &= 0x3F;

	Data.nData[3] = Decode.nData[2];
	Data.nData[3] &= 0x3F;
}

BOOL CBase64::_IsBadMimeChar(BYTE nData)
{
	switch(nData)
	{
	case '\r': case '\n': case '\t': case ' ' :
	case '\b': case '\a': case '\f': case '\v':
		return TRUE;
	default:
		return FALSE;
	}
}

void CBase64::_Init()
{  
	// Initialize Decoding table.
	int	i;
	for (i=0; i<256; i++)
	CBase64::m_DecodeTable[i] = -2;

	for (i=0; i<64; i++)
	{
		CBase64::m_DecodeTable[Base64Digits[i]]	= (char) i;
		CBase64::m_DecodeTable[Base64Digits[i]|0x80] = (char) i;
	}

	CBase64::m_DecodeTable['=']	= -1;
	CBase64::m_DecodeTable['='|0x80] = -1;
	CBase64::m_Init = TRUE;
}

