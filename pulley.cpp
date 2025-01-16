#include "pulley.h"

void Pulley::setPulley(int pos)
{
    this->m_camera_posy = pos;

    if (this->m_camera_posy < 0)
    {
        this->m_camera_posy = 0;
    }

    if (this->m_camera_posy > this->m_content_height - getWindowsSizeY())
    {
        this->m_camera_posy = this->m_content_height - getWindowsSizeY();
    }

    return;
}

void Pulley::movePulley(int pos)
{
    this->m_camera_posy += pos * this->m_move_speed;

    if (this->m_camera_posy < 0)
    {
        this->m_camera_posy = 0;
    }

    if (this->m_camera_posy > this->m_content_height - getWindowsSizeY())
    {
        this->m_camera_posy = this->m_content_height - getWindowsSizeY();
    }

    return;
}

void Pulley::setPulley(int content_height, int setSpeed)
{
    //setSpeed为负数则自动计算速度，若为 0 则使用默认速度，大于 0 为设定速度
    this->m_camera_posy = 0;
    this->m_zoom = 0;
    this->m_move_speed = (setSpeed > 0 ? setSpeed : 5);

    this->m_content_height = content_height;
    this->m_pulley_height = getWindowsSizeY() * getWindowsSizeY() / content_height;

    if (setSpeed < 0)
    {
        this->m_move_speed = (TEXTBOX_HEIGHT + 10) * 5 * getWindowsSizeY() / content_height;
    }

    return;
}
/*
void Pulley::draw(CPaintDC& dc)
{
    if (this->m_content_height == -1 || this->m_content_height == this->m_pulley_height)
    {
        return;
    }

    CBrush backbrush(this->m_backgroundColor);
    dc.SelectObject(&backbrush);
    dc.Rectangle(getWindowsSizeX() - PULLEY_WIDTH, 0, getWindowsSizeX(), getWindowsSizeY());

    CPen borderpen(PS_SOLID, 1, this->m_pulleyColor);
    dc.SelectObject(&borderpen);
    dc.Rectangle(getWindowsSizeX() - PULLEY_WIDTH + 2, this->getCameraY() * getWindowsSizeY() / this->m_content_height, getWindowsSizeX() - 2, this->getCameraY() * getWindowsSizeY() / this->m_content_height + this->m_pulley_height);

    return;
}
*/
void Pulley::draw(CDC& memDC)
{
    if (this->m_content_height == -1 || this->m_content_height == this->m_pulley_height)
    {
        return;
    }

    CBrush backbrush(this->m_backgroundColor);
    memDC.SelectObject(&backbrush);
    memDC.Rectangle(getWindowsSizeX() - PULLEY_WIDTH, 0, getWindowsSizeX(), getWindowsSizeY());

    CPen borderpen(PS_SOLID, 1, this->m_pulleyColor);
    memDC.SelectObject(&borderpen);
    memDC.Rectangle(getWindowsSizeX() - PULLEY_WIDTH + 2, this->getCameraY() * getWindowsSizeY() / this->m_content_height, getWindowsSizeX() - 2, this->getCameraY() * getWindowsSizeY() / this->m_content_height + this->m_pulley_height);

    return;
}

int Pulley::getCameraY()
{
    return this->m_camera_posy;
}

int Pulley::getZoom()
{
    return this->m_zoom;
}
