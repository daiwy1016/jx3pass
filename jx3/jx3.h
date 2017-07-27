// jx3.h : main header file for the JX3 application
//

#if !defined(AFX_JX3_H__B7959830_BC53_440F_B096_0FE8A5D3EB8C__INCLUDED_)
#define AFX_JX3_H__B7959830_BC53_440F_B096_0FE8A5D3EB8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CJx3App:
// See jx3.cpp for the implementation of this class
//

class CJx3App : public CWinApp
{
public:
	CJx3App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJx3App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CJx3App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JX3_H__B7959830_BC53_440F_B096_0FE8A5D3EB8C__INCLUDED_)
