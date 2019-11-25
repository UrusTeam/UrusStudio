
#include "RadialGL_Dialog.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(RadialGL_Dialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(RadialGL_Dialog)
const long RadialGL_Dialog::ID_GLCANVAS1 = wxNewId();
const long RadialGL_Dialog::ID_BUTTON11 = wxNewId();
const long RadialGL_Dialog::ID_TIMER1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(RadialGL_Dialog,wxDialog)
    //(*EventTable(RadialGL_Dialog)
    //*)
END_EVENT_TABLE()


RadialGL_Dialog::RadialGL_Dialog(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(RadialGL_Dialog)
    Create(parent, id, _("Urus GUI app"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxTAB_TRAVERSAL, _T("id"));
    SetClientSize(wxSize(574,480));
    int GLCanvasAttributes_1[] = {
    	WX_GL_RGBA,
    	WX_GL_DOUBLEBUFFER,
    	WX_GL_DEPTH_SIZE,      16,
    	WX_GL_STENCIL_SIZE,    0,
    	0, 0 };
    GLCanvas1 = new wxGLCanvas(this, ID_GLCANVAS1, wxPoint(88,64), wxSize(300,300), wxTRANSPARENT_WINDOW, _T("ID_GLCANVAS1"), GLCanvasAttributes_1);
    Button111 = new wxButton(this, ID_BUTTON11, _("Label"), wxPoint(32,16), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON11"));
    Timer1.SetOwner(this, ID_TIMER1);

    Connect(ID_BUTTON11,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&RadialGL_Dialog::OnButton111Click);
    Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&RadialGL_Dialog::OnTimer1Trigger);
    Connect(wxEVT_PAINT,(wxObjectEventFunction)&RadialGL_Dialog::OnPaint);
    Connect(wxEVT_SIZE,(wxObjectEventFunction)&RadialGL_Dialog::OnResize);
    //*)
    Timer1.Stop();
    glPane = new BasicGLPane((wxFrame*)GLCanvas1, GLCanvasAttributes_1);
    glPane->SetSize(256, 256);
    GLCanvas1->SetSize(glPane->getWidth(), glPane->getHeight());
}

RadialGL_Dialog::~RadialGL_Dialog()
{
    //(*Destroy(RadialGL_Dialog)
    //*)
}

void RadialGL_Dialog::OnButton111Click(wxCommandEvent& event)
{
    static bool on = false;

    on = !on;

    if (on) {
        Timer1.Start(18);
    } else {
        Timer1.Stop();
    }
}

void RadialGL_Dialog::OnTimer1Trigger(wxTimerEvent& event)
{
    static bool in_proc = false;

    if (in_proc == true) {
        return;
    }

    in_proc = true;

    static float cnt1 = 0.2;
    static float cnt = 0;
    cnt = cnt + cnt1;

    if (cnt > 360) {
        //cnt = 0;
        cnt1 = -0.2;
    }

    if (cnt < 0) {
        cnt = 0;
        cnt1 = 0.2;
    }

    //glPane1->rotate(-cnt);
    glPane->rotate(cnt);

    in_proc = false;
}

void RadialGL_Dialog::OnResize(wxSizeEvent& event)
{
    glPane->SetSize(256, 256);
    GLCanvas1->SetSize(glPane->getWidth(), glPane->getHeight());
}

void RadialGL_Dialog::OnPaint(wxPaintEvent& event)
{
    wxPaintDC wx(this);
}
