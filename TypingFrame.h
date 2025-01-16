#pragma once

#include <afxwin.h>
#include <fstream>
#include <string>
#include "TextBox.h"
#include "pulley.h"
#include "utils.h"

#define TIMER 1

class TypingFrame : public CFrameWnd
{
public:

	TypingFrame();

	TypingFrame(CString content);

	TypingFrame(LPCTSTR path);

	~TypingFrame();

	void initFrame();

	void setting(int is_can_back);

	void OnTimer();

	int getCorrentCount();

	int getErrorCount();

	DECLARE_MESSAGE_MAP();

	afx_msg void OnLButtonDown(UINT, CPoint);

	afx_msg void OnChar(UINT, UINT, UINT);

	afx_msg void OnPaint();

	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint point);

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

public:
	CRect m_timeRect;

private:

	int m_count_num = 19;

	int m_is_errorInit = 1;
	int m_is_canBack = 1;

	CString m_contents = "there is nothing :(";

	bool m_is_start = false;

	Pulley m_pulley;
	TextBox m_content_box;

	COLORREF m_backgroundColor = RGB(215, 230, 245);

	COLORREF m_currentColor = RGB(150, 150, 150);

};