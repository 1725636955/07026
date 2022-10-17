// Base64.h: interface for the CBase64 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BASE64_H__2C7B9EA0_0F6A_11DA_BB87_8CF83F6321B3__INCLUDED_)
#define AFX_BASE64_H__2C7B9EA0_0F6A_11DA_BB87_8CF83F6321B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBase64  
{
public:
	CBase64();
	virtual ~CBase64();

//����
	virtual void  Encode(const PBYTE, DWORD);
	virtual void  Decode(const PBYTE, DWORD);
	virtual void  Encode(LPCSTR sMessage);
	virtual void  Decode(LPCSTR sMessage);
	virtual LPSTR  DecodedMessage() const;
	virtual LPSTR  EncodedMessage() const;
	virtual LONG  DecodedMessageSize() const;
	virtual LONG  EncodedMessageSize() const;

protected:
	// Internal bucket class.
	class TempBucket
	{
	public:
		BYTE  nData[4];
		BYTE  nSize;
		void  Clear() { ::ZeroMemory(nData, 4); nSize = 0; };
	};

//����
	PBYTE  m_pDBuffer;
	PBYTE  m_pEBuffer;
	DWORD  m_nDBufLen;
	DWORD  m_nEBufLen;
	DWORD  m_nDDataLen;
	DWORD  m_nEDataLen;
	static char m_DecodeTable[256];
	static BOOL m_Init;

//����
	virtual void   AllocEncode(DWORD);
	virtual void   AllocDecode(DWORD);
	virtual void   SetEncodeBuffer(const PBYTE pBuffer, DWORD nBufLen);
	virtual void   SetDecodeBuffer(const PBYTE pBuffer, DWORD nBufLen);
	virtual void  _EncodeToBuffer(const TempBucket &Decode, PBYTE pBuffer);
	virtual ULONG _DecodeToBuffer(const TempBucket &Decode, PBYTE pBuffer);
	virtual void  _EncodeRaw(TempBucket &, const TempBucket &);
	virtual void  _DecodeRaw(TempBucket &, const TempBucket &);
	virtual BOOL _IsBadMimeChar(BYTE);
	void  _Init();
};

#endif // !defined(AFX_BASE64_H__2C7B9EA0_0F6A_11DA_BB87_8CF83F6321B3__INCLUDED_)
