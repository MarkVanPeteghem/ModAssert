//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com


// DemoMFCDlg.h : header file
//

#if !defined(AFX_MOD_ASSERTDEMOMFCDLG_H__9BFE77B4_56A5_454D_B83B_E4519DB3A3D3__INCLUDED_)
#define AFX_MOD_ASSERTDEMOMFCDLG_H__9BFE77B4_56A5_454D_B83B_E4519DB3A3D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDemoMFCDlg dialog

class CDemoMFCDlg : public CDialog
{
// Construction
public:
	CDemoMFCDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDemoMFCDlg)
	enum { IDD = IDD_MOD_ASSERTDEMOMFC_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoMFCDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void OnSucceedingAssert();
	void OnFailingAssert(const CString &extra="");
	void OnFailingCheck(const CString &extra="");

	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDemoMFCDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnEqualInt();
	afx_msg void OnDiffInt();
	afx_msg void OnEqualIntWithData();
	afx_msg void OnDiffIntWithData();
	afx_msg void OnEqualString();
	afx_msg void OnDiffString();
	afx_msg void OnEqualStringWithEscape();
	afx_msg void OnDiffStringWithEscape2();
	afx_msg void OnDiffStringWithEscape();
	afx_msg void OnEqualVector();
	afx_msg void OnDiffVector();
	afx_msg void OnEqualVectorAndList();
	afx_msg void OnDiffVectorAndList();
	afx_msg void OnDiffVectorVector();
	afx_msg void OnDiffFailLessVector();
	afx_msg void OnDiffFailPred1();
	afx_msg void OnDiffFailPred2();
	afx_msg void OnDiffFailPred3();
	afx_msg void OnFailWithOptional();
	afx_msg void OnAnd();
	afx_msg void OnFailWithGroup();
	afx_msg void OnFailWithTwoGroups();
	afx_msg void OnFailWithLevelWarning();
	afx_msg void OnFailWithLevelFatal();
	afx_msg void OnFailWithGroupAndWarning();
	afx_msg void OnFailWithTwoGroupsAndWarning();
	afx_msg void OnFailInOtherThread();
	afx_msg void OnCheckAndThrow();
	afx_msg void OnSuccess();
	afx_msg void OnReportAll();
	afx_msg void OnGetlasterror();
	afx_msg void OnFailInOtherFile();
	afx_msg void OnVerifyV();
	afx_msg void OnMFCException();
	afx_msg void OnNoText();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClicked65535();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOD_ASSERTDEMOMFCDLG_H__9BFE77B4_56A5_454D_B83B_E4519DB3A3D3__INCLUDED_)
