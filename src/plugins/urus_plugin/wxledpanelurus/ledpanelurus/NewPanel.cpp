#include "NewPanel.h"

//(*InternalHeaders(NewPanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(NewPanel)
//*)

BEGIN_EVENT_TABLE(NewPanel,wxPanel)
	//(*EventTable(NewPanel)
	//*)
END_EVENT_TABLE()

NewPanel::NewPanel(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(NewPanel)
	Create(parent, wxID_ANY, wxDefaultPosition, wxSize(40,33), wxTAB_TRAVERSAL, _T("wxID_ANY"));
	SetBackgroundColour(wxColour(0,255,0));
	//*)

}

NewPanel::~NewPanel()
{
	//(*Destroy(NewPanel)
	//*)
}

void NewPanel::SwitchON()
{
    m_onoff = true;
    SetBackgroundColour(wxColour(0,255,0));
}

void NewPanel::SwitchOFF()
{
    m_onoff = false;
    SetBackgroundColour(wxColour(255,0,0));
}

void NewPanel::Switch()
{
    if (m_onoff) {
        SwitchOFF();
    } else {
        SwitchON();
    }
}
