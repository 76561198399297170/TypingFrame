#pragma once

#include <afxwin.h>

#define TEXTBOX_HEIGHT 64
#define TEXTBOX_WIDTH 920
//�����ַ���ռ�߶��������ַ���ռ���
#define TEXTBOX_WORD_WIDTH 910
#define TEXTBOX_WORD_HEIGHT 26

enum class WordType
{
	NormalInput,//������
	ErrorInput,//��������
	CorrectInput//��ȷ����
};

int getWindowsSizeX();

int getWindowsSizeY();

void setFontColor(CPaintDC& dc, WordType type);

void setFontColor(CDC& memDC, WordType type);

CFont* getWordFont(WordType type);

CSize calContentSize(CString text, CFont* font);

CString intDateToCStringDate(int date);

CString getFileName(CString name);