#include "textBox.h"

#define TEST_INTERVAL 10
#define TEST_Y TEST_INTERVAL
/*
void Text::draw(CPaintDC& dc, int x, int y)
{
    if (y < (-2 * TEXTBOX_HEIGHT) || y > getWindowsSizeY() + (2 * TEXTBOX_HEIGHT))
    {
        return;
    }

    CBrush backbrush(this->m_background_color);
    CBrush* oldbrush = dc.SelectObject(&backbrush);
    dc.Rectangle(x, y, x + TEXTBOX_WIDTH, y + TEXTBOX_HEIGHT);
    dc.SelectObject(oldbrush);

    CPen borderpen(PS_SOLID, 1, this->m_border_color);
    CPen* oldpen = dc.SelectObject(&borderpen);
    dc.Rectangle(x, y, x + TEXTBOX_WIDTH, y + TEXTBOX_HEIGHT);
    dc.SelectObject(oldpen);

    CPen dashedPen(PS_DOT, 1, this->m_dashed_color);
    oldpen = dc.SelectObject(&dashedPen);

    dc.MoveTo(x, y + TEXTBOX_HEIGHT / 2);
    dc.LineTo(x + TEXTBOX_WIDTH, y + TEXTBOX_HEIGHT / 2);
    dc.SelectObject(oldpen);

    int putx = x + 2, puty = y + TEST_Y - 1;
    for (int i = 0; i < this->m_text_list_length; i++)
    {
        putx += this->m_word_list[i].draw(dc, putx, puty);
    }

    return;
}
*/
void Text::draw(CDC& menDC, int x, int y)
{
    if (y < (-2 * TEXTBOX_HEIGHT) || y > getWindowsSizeY() + (2 * TEXTBOX_HEIGHT))
    {
        return;
    }

    CBrush backbrush(this->m_background_color);
    CBrush* oldbrush = menDC.SelectObject(&backbrush);
    menDC.Rectangle(x, y, x + TEXTBOX_WIDTH, y + TEXTBOX_HEIGHT);
    menDC.SelectObject(oldbrush);

    CPen borderpen(PS_SOLID, 1, this->m_border_color);
    CPen* oldpen = menDC.SelectObject(&borderpen);
    menDC.Rectangle(x, y, x + TEXTBOX_WIDTH, y + TEXTBOX_HEIGHT);
    menDC.SelectObject(oldpen);
    CPen dashedPen(PS_DOT, 1, this->m_dashed_color);
    oldpen = menDC.SelectObject(&dashedPen);

    menDC.MoveTo(x, y + TEXTBOX_HEIGHT / 2);
    menDC.LineTo(x + TEXTBOX_WIDTH, y + TEXTBOX_HEIGHT / 2);
    menDC.SelectObject(oldpen);
    int putx = x + 2, puty = y + TEST_Y - 1;
    for (int i = 0; i < this->m_text_list_length; i++)
    {
        putx += this->m_word_list[i].draw(menDC, putx, puty);
    }
    return;
}

int Text::input(CString input)
{
    if (this->m_text_list_index < this->m_text_list_length)
    {
        this->m_word_list[this->m_text_list_index].input(input);
        if (this->m_word_list[this->m_text_list_index].isCorrent())
        {
            this->m_corrent_count++;
        }
        else
        {
            this->m_error_count++;
        }
        this->m_text_list_index++;
        
        return 0;
    }
    return -1;
}

int Text::delWord()
{
    if (this->m_text_list_index == 0)
    {
        return -1;
    }

    if (this->m_word_list[this->m_text_list_index - 1].isCorrent())
    {
        this->m_corrent_count--;
    }
    else
    {
        this->m_error_count--;
    }

    this->m_word_list[this->m_text_list_index - 1].delWord();
    this->m_text_list_index--;

    return 0;
}

void Text::loadText(CString text, int length)
{
    this->m_text = text;
    this->m_text_list_length = length;

    if (loadWord(this->m_word_list, this->m_text, this->m_text_list_length) == "")
    {
        //完成输入，无溢出

    }

    return;
}

int Text::getLength()
{
    return this->m_text_list_length;
}

int Text::getIndex()
{
    return this->m_text_list_index;
}

WordType Text::getFontType()
{
    return this->m_type;
}

int Text::isEmpty()
{
    return this->m_text == "" ? 1 : 0;
}

int Text::getCorrentCount()
{
    return this->m_corrent_count;
}

int Text::getErrorCount()
{
    return this->m_error_count;
}

void TextBox::textName(CString name)
{
    this->m_text_name = name;

    return;
}

void TextBox::loadText(CString contents)
{
    this->m_contents = contents;
    this->m_content_box_length = 0;

    CString str;
    int content_length;
    while (contents != "")
    {
        content_length = 0;
        str= "";
        while (contents != "" && calContentSize(str, getWordFont(WordType::NormalInput)).cx < TEXTBOX_WORD_WIDTH)
        {
            content_length++;
            str += contents[0];
            contents.Delete(0, 1);
            if (str.GetAt(content_length - 1) == L'\n')
            {
                this->m_content_box[this->m_content_box_length].loadText(str, content_length);
                this->m_content_box_length++;

                content_length = 0;
                str = "";
            }
        }

        this->m_content_box[this->m_content_box_length].loadText(str, content_length);
        this->m_content_box_length++;
    }

    return;
}

void TextBox::draw(CPaintDC& dc, int x, int y, int zoom)
{
    //备注：参数中 x 与 y 为窗口左上角位置，x 通常为 0 即可，y 记为绘制位置高度即可
    for (int i = 0; i < this->m_content_box_length; i++)
    {
        this->m_content_box[i].draw(dc, x + (getWindowsSizeX() - TEXTBOX_WIDTH) / 2, y + i * TEXTBOX_HEIGHT + i * TEST_Y);
    }

    return;
}

void TextBox::draw(CDC& memDC, int x, int y, int zoom)
{
    for (int i = 0; i < this->m_content_box_length; i++)
    {
        this->m_content_box[i].draw(memDC, x + (getWindowsSizeX() - TEXTBOX_WIDTH) / 2, y + i * TEXTBOX_HEIGHT + i * TEST_Y);
    }

    return;
}

int TextBox::input(CString input)
{
    //返回 0 表示无状况, 返回 1 表示输入结束, 异常状况返回 -1 (无)
    if (this->m_read_line >= this->m_content_box_length - 1)
    {
        if (this->m_content_box[this->m_read_line].getIndex() >= this->m_content_box[this->m_read_line].getLength())
        {
            MessageBox(NULL, L"完成已经结束，无需后续按键！", L"提示", MB_OK);
            return 1;
        }
    }

    if (this->m_content_box[this->m_read_line].input(input) == -1)
    {
        this->m_read_line++;
        if (this->m_content_box[this->m_read_line].isEmpty())
        {
            //输入结束
            this->upNumDate();
            return 0;
        }
        
        this->m_content_box[this->m_read_line].input(input);
    }
    else if (input.GetAt(0) == L'\n' && this->m_read_line < this->m_content_box_length - 1)
    {
        this->m_read_line = this->m_read_line + 1;
    }

    this->upNumDate();
    return 0;
}

int TextBox::getContentLineNum()
{
    return this->m_content_box_length;
}

int TextBox::getLength()
{
    return this->m_contents.GetLength();
}

CString TextBox::getFileName()
{
    return this->m_text_name;
}

CString TextBox::getLanguage()
{
    return this->m_text_language;
}

void TextBox::delWord()
{
    if (this->m_content_box[this->m_read_line].delWord())
    {
        this->m_read_line = (this->m_read_line == 0 ? 0 : this->m_read_line - 1);
        this->m_content_box[this->m_read_line].delWord();
    }
    this->upNumDate();
    return;
}

int TextBox::getCorrent()
{
    return this->m_corrent_count;
}

int TextBox::getError()
{
    return this->m_error_count;
}

void TextBox::upNumDate()
{
    int corrent = 0, error = 0;
    for (int i = 0; i <= this->m_read_line; i++)
    {
        corrent += this->m_content_box[i].getCorrentCount();
        error += this->m_content_box[i].getErrorCount();
    }
    this->m_corrent_count = corrent;
    this->m_error_count = error;

    return;
}
