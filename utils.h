#pragma once

#include <afxwin.h>

#define TEXTBOX_HEIGHT 64
#define TEXTBOX_WIDTH 920
//整行字符所占高度与整行字符所占宽度
#define TEXTBOX_WORD_WIDTH 910
#define TEXTBOX_WORD_HEIGHT 26

enum class WordType
{
	NormalInput,//无输入
	ErrorInput,//错误输入
	CorrectInput//正确输入
};

int getWindowsSizeX();

int getWindowsSizeY();

void setFontColor(CPaintDC& dc, WordType type);

void setFontColor(CDC& memDC, WordType type);

CFont* getWordFont(WordType type);

CSize calContentSize(CString text, CFont* font);

CString intDateToCStringDate(int date);

CString getFileName(CString name);