#pragma once

#include <afxwin.h>
#include "utils.h"

#define PULLEY_WIDTH 20

class Pulley
{
public:

	void setPulley(int pos);

	void movePulley(int pos);

	void setPulley(int content_height, int setSpeed = 5);

	//void draw(CPaintDC& dc);

	void draw(CDC& memDC);

	int getCameraY();

	int getZoom();

private:

	int m_move_speed = 15;

	int m_camera_posy = 0;

	int m_content_height = -1;
	int m_pulley_height = 0;

	int m_zoom = 1;

	COLORREF m_backgroundColor = RGB(250, 250, 250);
	COLORREF m_pulleyColor = RGB(140, 140, 140);

};