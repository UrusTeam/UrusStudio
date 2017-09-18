#include "FMainSettings.h"
#include <wx/msgdlg.h>
#include <manager.h>
#include <wx/wx.h>
#include "urusstudiosettings.h"

urusstudiosettings* main_urusstudio = URUS_STUDIO_SETTINGS::GetUrusStudioMain();

//(*InternalHeaders(FMainSettings)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(FMainSettings)
const long FMainSettings::ID_BUTTON1 = wxNewId();
const long FMainSettings::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(FMainSettings,wxPanel)
	//(*EventTable(FMainSettings)
	//*)
END_EVENT_TABLE()

FMainSettings::FMainSettings(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(FMainSettings)
	wxBoxSizer* BoxSizer1;

	Create(parent, id, wxDefaultPosition, wxSize(315,202), wxTAB_TRAVERSAL, _T("id"));
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	Button1 = new wxButton(this, ID_BUTTON1, _("Close"), wxDefaultPosition, wxSize(88,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer1->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button2 = new wxButton(this, ID_BUTTON2, _("Test!"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer1->Add(Button2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	SetSizer(BoxSizer1);
	Layout();

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&FMainSettings::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&FMainSettings::OnButton2Click);
	//*)
}

FMainSettings::~FMainSettings()
{
	//(*Destroy(FMainSettings)
	//*)
}

void FMainSettings::OnButton1Click(wxCommandEvent& event)
{
    CodeBlocksDockEvent evt(cbEVT_HIDE_DOCK_WINDOW);
    evt.pWindow = this;
    Manager::Get()->ProcessEvent(evt);
}

void FMainSettings::OnButton2Click(wxCommandEvent& event)
{
    main_urusstudio->TestCommand();
}
