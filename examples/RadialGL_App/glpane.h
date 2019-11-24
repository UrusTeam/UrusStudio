#pragma once

#include "wx/wx.h"
#include "wx/glcanvas.h"
#include "gl_image.h"
#include "gl_drawable.h"

#define LAYER_COUNT 5

class BasicGLPane : public wxGLCanvas
{

public:
	BasicGLPane(wxFrame* parent, int* args);

	void resized(wxSizeEvent& evt);

	int getWidth();
	int getHeight();

	int getTextWidth();
	int getTextHeight();

	void render(wxPaintEvent& evt);
	void prepare3DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y);
	void prepare2DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y);
	void rotate(float angle);

	// events
	void mouseMoved(wxMouseEvent& event);
	void mouseDown(wxMouseEvent& event);
	void mouseWheelMoved(wxMouseEvent& event);
	void mouseReleased(wxMouseEvent& event);
	void rightClick(wxMouseEvent& event);
	void mouseLeftWindow(wxMouseEvent& event);
	void keyPressed(wxKeyEvent& event);
	void keyReleased(wxKeyEvent& event);

private:

    Image* image = NULL;
    glDrawable* sprite[LAYER_COUNT];

	DECLARE_EVENT_TABLE()
};
