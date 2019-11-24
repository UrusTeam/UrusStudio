
#pragma once

#include "glpane.h"

//(*Headers(RadialGL_Dialog)
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/glcanvas.h>
#include <wx/timer.h>
//*)

class RadialGL_Dialog: public wxDialog
{
    public:

        RadialGL_Dialog(wxWindow* parent,wxWindowID id = -1);
        virtual ~RadialGL_Dialog();

    private:

        //wxFrame *frame;
        BasicGLPane * glPane;
        //BasicGLPane * glPane1;

        //(*Handlers(RadialGL_Dialog)
        void OnButton111Click(wxCommandEvent& event);
        void OnTimer1Trigger(wxTimerEvent& event);
        void OnResize(wxSizeEvent& event);
        void OnPaint(wxPaintEvent& event);
        //*)

        //(*Identifiers(RadialGL_Dialog)
        static const long ID_GLCANVAS1;
        static const long ID_BUTTON11;
        static const long ID_TIMER1;
        //*)

        //(*Declarations(RadialGL_Dialog)
        wxButton* Button111;
        wxGLCanvas* GLCanvas1;
        wxTimer Timer1;
        //*)

        DECLARE_EVENT_TABLE()
};

