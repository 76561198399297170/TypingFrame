#include "utils.h"

CFont* normal_font = NULL;
CFont* error_font = NULL;
CFont* correct_font = NULL;

int getWindowsSizeX()
{
	return GetSystemMetrics(SM_CXSCREEN);
}

int getWindowsSizeY()
{
	return GetSystemMetrics(SM_CYSCREEN);
}

void setFontColor(CPaintDC& dc, WordType type)
{
	switch (type)
	{
	case WordType::NormalInput:
	{
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(RGB(0, 0, 0));
	}
		break;
	case WordType::ErrorInput:
	{
		dc.SetBkMode(OPAQUE);
		dc.SetBkColor(RGB(220, 220, 220));
		dc.SetTextColor(RGB(240, 35, 50));
	}
		break;
	case WordType::CorrectInput:
	{
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(RGB(50, 200, 50));
	}
		break;
	default:
		break;
	}

	return;
}

void setFontColor(CDC& memDC, WordType type)
{
	switch (type)
	{
	case WordType::NormalInput:
	{
		memDC.SetBkMode(TRANSPARENT);
		memDC.SetTextColor(RGB(0, 0, 0));
	}
	break;
	case WordType::ErrorInput:
	{
		memDC.SetBkMode(OPAQUE);
		memDC.SetBkColor(RGB(220, 220, 220));
		memDC.SetTextColor(RGB(240, 35, 50));
	}
	break;
	case WordType::CorrectInput:
	{
		memDC.SetBkMode(TRANSPARENT);
		memDC.SetTextColor(RGB(50, 200, 50));
	}
	break;
	default:
		break;
	}
	return;
}

CFont* getWordFont(WordType type)
{
	if (normal_font == NULL)
	{
		normal_font = new CFont();
		normal_font->CreateFont(TEXTBOX_WORD_HEIGHT, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"ËÎÌו");
	}

	if (error_font == NULL)
	{
		error_font = new CFont();
		error_font->CreateFont(TEXTBOX_WORD_HEIGHT, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"ËÎÌו");
	}

	if (correct_font == NULL)
	{
		correct_font = new CFont();
		correct_font->CreateFont(TEXTBOX_WORD_HEIGHT, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"ËÎÌו");
	}

	switch (type)
	{
	case WordType::ErrorInput:
		return error_font;
	case WordType::CorrectInput:
		return correct_font;
	default:
		return normal_font;
	}

	return NULL;
}

CSize calContentSize(CString text, CFont* font)
{
	CSize size;

	CWnd* pWnd = AfxGetMainWnd();
	if (pWnd)
	{
		CDC* pDC = pWnd->GetDC();

		pDC->SelectObject(font);
		size = pDC->GetTextExtent(text);

		pWnd->ReleaseDC(pDC);
	}

	return size;
}

CString intDateToCStringDate(int date)
{
	CString h, m, s;
	h.Format(_T("%02d"), date / 3600);
	m.Format(_T("%02d"), (date % 3600) / 60);
	s.Format(_T("%02d"), date % 60);
	
	CString t = h + ":" + m + ":" + s;

	return t;
}

CString getFileName(CString name)
{
	CString res = PathFindFileName(name);
	int pos = res.ReverseFind('.');

	res = (pos == -1 ? res : res.Left(pos));
	
	return res;
}
