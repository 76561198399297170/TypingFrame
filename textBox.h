#pragma once

#include <afxwin.h>
#include "utils.h"
#include "MyWord.h"

class Text
{
public:

	//void draw(CPaintDC& dc, int x, int y);
	
	void draw(CDC& menDC, int x, int y);

	int input(CString input);

	int delWord();

	void loadText(CString text, int length);

	int getLength();

	int getIndex();

	WordType getFontType();

	int isEmpty();

	int getCorrentCount();

	int getErrorCount();

private:

	int m_is_empty = 0;

	int m_corrent_count = 0;
	int m_error_count = 0;

	CString m_text = "There is no input text, this text is the default test text.";

	int m_text_list_index = 0;
	int m_text_list_length = 59;

	MyWord m_word_list[1010];

	WordType m_type = WordType::NormalInput;

	COLORREF m_background_color = RGB(255, 255, 255);
	COLORREF m_border_color = RGB(25, 145, 255);
	COLORREF m_dashed_color = RGB(200, 200, 200);

};

class TextBox
{
public:

	void textName(CString name);

	void loadText(CString contents);

	void draw(CPaintDC& dc, int x, int y, int zoom);

	void draw(CDC& memDC, int x, int y, int zoom);

	int input(CString input);

	int getContentLineNum();

	int getLength();

	CString getFileName();

	CString getLanguage();

	void delWord();

	void upNumDate();

	int getCorrent();

	int getError();

public:

	int m_corrent_count = 0;
	int m_error_count = 0;

	CString m_contents = "o(TmT)o";
	
	CString m_text_name = "¿ÕÎÄ¼þ";
	CString m_text_language = "Ó¢Óï";

	int m_read_line = 0;

private:

	int m_content_box_length = 1;

	Text m_content_box[10010];

};