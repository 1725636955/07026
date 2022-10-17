// ts.h : main header file for the TS application
//

#if !defined(AFX_TS_H__FF52AAE4_FDC6_11D9_BC43_000795DF7F99__INCLUDED_)
#define AFX_TS_H__FF52AAE4_FDC6_11D9_BC43_000795DF7F99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTsApp:
// See ts.cpp for the implementation of this class
//

class CTsApp : public CWinApp
{
public:
	CTsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TS_H__FF52AAE4_FDC6_11D9_BC43_000795DF7F99__INCLUDED_)
