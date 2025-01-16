#pragma once

#include "utils.h"

class MyWord
{
public:

	WordType getWordType();

	//int draw(CPaintDC& dc, int posx, int posy);

	int draw(CDC& menDC, int posx, int posy);

	void input(CString input);

	void delWord();

	void setWord(CString word, CString input = "");

	int isEmpty();

	bool isCorrent();

private:

	CString m_word = "";

	CString m_input = "";

};

CString loadWord(MyWord* arr, CString str, int length);