#include "myWord.h"

WordType MyWord::getWordType()
{
    if (this->m_word == this->m_input && this->m_input != "")
    {
        return WordType::CorrectInput;
    }

    if (this->m_word != this->m_input && this->m_input != "")
    {
        return WordType::ErrorInput;
    }

    return WordType::NormalInput;
}
/*
int MyWord::draw(CPaintDC& dc, int posx, int posy)
{
    CFont* font = getWordFont(this->getWordType());
    dc.SelectObject(font);

    setFontColor(dc, this->getWordType());
    dc.TextOut(posx, posy - 2, this->m_word);
    setFontColor(dc, WordType::NormalInput);
    dc.TextOut(posx, posy - 2 + TEXTBOX_HEIGHT / 2, (CString)this->m_input);

    return calContentSize(this->m_word, font).cx;
}
*/
int MyWord::draw(CDC& memDC, int posx, int posy)
{
    CFont* font = getWordFont(this->getWordType());
    CFont* oldFont = memDC.SelectObject(font); // ±£´æ¾É×ÖÌå

    setFontColor(memDC, this->getWordType());
    memDC.TextOut(posx, posy - 2, this->m_word);
    setFontColor(memDC, WordType::NormalInput);
    memDC.TextOut(posx, posy - 2 + TEXTBOX_HEIGHT / 2, (CString)this->m_input);

    memDC.SelectObject(oldFont); // »Ö¸´¾É×ÖÌå

    return calContentSize(this->m_word, font).cx;
}

void MyWord::input(CString input)
{
    this->m_input = input;

    return;
}

void MyWord::delWord()
{
    this->m_input = "";

    return;
}

void MyWord::setWord(CString word, CString input)
{
    this->m_word = word;
    this->m_input = input;

    return;
}

int MyWord::isEmpty()
{
    return this->m_word == "" ? 1 : 0;
}

bool MyWord::isCorrent()
{
    return this->m_word == this->m_input;
}

CString loadWord(MyWord* arr, CString str, int length)
{
    for (int i = 0; i < length; i++)
    {
        arr[i].setWord(str[i]);
    }

    return CString();
}
