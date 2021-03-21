#include "glpane.h"

BEGIN_EVENT_TABLE(BasicGLPane, wxGLCanvas)
EVT_MOTION(BasicGLPane::mouseMoved)
EVT_LEFT_DOWN(BasicGLPane::mouseDown)
EVT_LEFT_UP(BasicGLPane::mouseReleased)
EVT_RIGHT_DOWN(BasicGLPane::rightClick)
EVT_LEAVE_WINDOW(BasicGLPane::mouseLeftWindow)
EVT_SIZE(BasicGLPane::resized)
EVT_KEY_DOWN(BasicGLPane::keyPressed)
EVT_KEY_UP(BasicGLPane::keyReleased)
EVT_MOUSEWHEEL(BasicGLPane::mouseWheelMoved)
EVT_PAINT(BasicGLPane::render)
END_EVENT_TABLE()

// some useful events to use
void BasicGLPane::mouseMoved(wxMouseEvent& event) {}
void BasicGLPane::mouseDown(wxMouseEvent& event) {}
void BasicGLPane::mouseWheelMoved(wxMouseEvent& event) {}
void BasicGLPane::mouseReleased(wxMouseEvent& event) {}
void BasicGLPane::rightClick(wxMouseEvent& event) {}
void BasicGLPane::mouseLeftWindow(wxMouseEvent& event) {}
void BasicGLPane::keyPressed(wxKeyEvent& event) {}
void BasicGLPane::keyReleased(wxKeyEvent& event) {}

static void CheckGLError()
{
    GLenum errLast = GL_NO_ERROR;

    for ( ;; )
    {
        GLenum err = glGetError();
        if ( err == GL_NO_ERROR )
            return;

        // normally the error is reset by the call to glGetError() but if
        // glGetError() itself returns an error, we risk looping forever here
        // so check that we get a different error than the last time
        if ( err == errLast )
        {
            wxLogError(_("OpenGL error state couldn't be reset."));
            return;
        }

        errLast = err;

        wxLogError(_("OpenGL error %d"), err);
    }
}

TestGLContext::TestGLContext(wxGLCanvas *canvas)
             : wxGLContext(canvas)
{
    SetCurrent(*canvas);
    CheckGLError();
}

BasicGLPane::BasicGLPane(wxFrame* parent, int* args) :
    wxGLCanvas(parent, wxID_ANY, args,  wxDefaultPosition, wxDefaultSize, 0, wxT("GLCanvas"))
{
    glContext = new TestGLContext(this);
}

void BasicGLPane::resized(wxSizeEvent& evt)
{
    //wxGLCanvas::OnSize(evt);
    Refresh();
}

void BasicGLPane::prepare3DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y)
{
    /*
     *  Inits the OpenGL viewport for drawing in 3D.
     */

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black Background
    glClearDepth(1.0f);	// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST); // Enables Depth Testing
    glDepthFunc(GL_LEQUAL); // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glEnable(GL_COLOR_MATERIAL);

    glViewport(topleft_x, topleft_y, bottomrigth_x-topleft_x, bottomrigth_y-topleft_y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float ratio_w_h = (float)(bottomrigth_x-topleft_x)/(float)(bottomrigth_y-topleft_y);
    gluPerspective(45 /*view angle*/, ratio_w_h, 0.1 /*clip close*/, 200 /*clip far*/);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void BasicGLPane::prepare2DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y)
{
    /*
     *  Inits the OpenGL viewport for drawing in 2D
     */

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black Background
    glEnable(GL_TEXTURE_2D);   // textures
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glViewport(topleft_x, topleft_y, bottomrigth_x-topleft_x, bottomrigth_y-topleft_y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(topleft_x, bottomrigth_x, bottomrigth_y, topleft_y);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int BasicGLPane::getWidth()
{
    return GetSize().x;
}

int BasicGLPane::getHeight()
{
    return GetSize().y;
}

int BasicGLPane::getTextWidth()
{
    return image->textureWidth;
}

int BasicGLPane::getTextHeight()
{
    return image->textureHeight;
}

void BasicGLPane::render( wxPaintEvent& evt )
{
    if(!IsShown()) return;

    wxPaintDC dc(this); // only to be used in paint events. use wxClientDC to paint outside the paint event
    glContext->SetCurrent(*this);

    if(image == NULL) {
        image = new Image(wxT("alt_face_1.png"));
        sprite[0] = new glDrawable(image);
        image = new Image(wxT("alt_face_2.png"));
        sprite[1] = new glDrawable(image);
        image = new Image(wxT("alt_face_3.png"));
        sprite[2] = new glDrawable(image);
        image = new Image(wxT("alt_hand_1.png"));
        sprite[3] = new glDrawable(image);
        image = new Image(wxT("alt_hand_2.png"));
        sprite[4] = new glDrawable(image);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // render loaded image
    prepare2DViewport(0, 0, image->textureWidth, image->textureHeight);

    for (uint8_t i = 0; i < LAYER_COUNT; i++) {
        sprite[i]->render();
    }

    glFlush();
    SwapBuffers();
}

void BasicGLPane::rotate(float angle)
{
    static float cnt1 = 1.7;
    static float cnt = 0;

    if (image == NULL) {
        return;
    }

    cnt = cnt + cnt1;

    if (cnt > 360) {
        cnt1 = -1.7;
    }

    if (cnt < 0) {
        cnt = 0;
        cnt1 = 1.7;
    }

    wxClientDC dc(this);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    prepare2DViewport(0, 0, image->textureWidth, image->textureHeight);
    sprite[0]->rotate(angle);
    sprite[0]->render();
    sprite[1]->render();
    sprite[2]->rotate(-angle - 1.2);
    sprite[2]->render();
    sprite[3]->rotate(angle + 5.2);
    sprite[3]->render();
    sprite[4]->rotate(cnt);
    sprite[4]->render();
    glFlush();
    SwapBuffers();
}
