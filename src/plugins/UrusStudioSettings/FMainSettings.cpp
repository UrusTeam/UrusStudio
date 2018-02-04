#include "FMainSettings.h"
#include <wx/msgdlg.h>
#include <configmanager.h>
#include <manager.h>
#include <wx/wx.h>
#include "urusstudiosettings.h"

urusstudiosettings* main_urusstudio = URUS_STUDIO_SETTINGS::GetUrusStudioMain();

//(*InternalHeaders(FMainSettings)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(FMainSettings)
const long FMainSettings::ID_CHECKBOX1 = wxNewId();
const long FMainSettings::ID_BUTTON1 = wxNewId();
const long FMainSettings::ID_BUTTON2 = wxNewId();
const long FMainSettings::ID_BUTTON3 = wxNewId();
//*)

BEGIN_EVENT_TABLE(FMainSettings,wxPanel)
	//(*EventTable(FMainSettings)
	//*)
END_EVENT_TABLE()

FMainSettings::FMainSettings(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(FMainSettings)
	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer3 = new wxBoxSizer(wxVERTICAL);
	CheckBox1 = new wxCheckBox(this, ID_CHECKBOX1, _("Override Global Vars."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	CheckBox1->SetValue(false);
	BoxSizer3->Add(CheckBox1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2 = new wxBoxSizer(wxVERTICAL);
	Button1 = new wxButton(this, ID_BUTTON1, _("Close"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer2->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button2 = new wxButton(this, ID_BUTTON2, _("Test!"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer2->Add(Button2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button3 = new wxButton(this, ID_BUTTON3, _("Save"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	BoxSizer2->Add(Button3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&FMainSettings::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&FMainSettings::OnButton2Click);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&FMainSettings::OnButton3Click);
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

void FMainSettings::OnButton3Click(wxCommandEvent& event)
{
    if (CheckBox1->IsChecked()) {
        Manager::Get()->GetConfigManager(_T("app"))->Write(_T("/ur_overrsettings"), true);
    } else {
        Manager::Get()->GetConfigManager(_T("app"))->Write(_T("/ur_overrsettings"), false);
    }

    wxMessageBox(wxString::Format(_("%s"), _("UrusStudio settings saved!\n")) +
                 wxString::Format(_("%s"), _("Restart Urus Studio to take effect the changes!")));
}
