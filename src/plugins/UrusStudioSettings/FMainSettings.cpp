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
const long FMainSettings::ID_GLitemLinker = wxNewId();
const long FMainSettings::ID_BUTTON3 = wxNewId();
const long FMainSettings::ID_BUTTON1 = wxNewId();
const long FMainSettings::ID_BUTTON2 = wxNewId();
const long FMainSettings::ID_PANEL1 = wxNewId();
const long FMainSettings::ID_NOTEBOOK1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(FMainSettings,wxPanel)
	//(*EventTable(FMainSettings)
	//*)
END_EVENT_TABLE()

FMainSettings::FMainSettings(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(FMainSettings)
	wxNotebook* Notebook1;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_NOTEBOOK1"));
	Panel1 = new wxPanel(Notebook1, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	GridBagSizer1 = new wxGridBagSizer(0, 0);
	GridBagSizer1->AddGrowableCol(1);
	GridBagSizer1->AddGrowableRow(2);
	BoxSizer2 = new wxBoxSizer(wxVERTICAL);
	CheckBox1 = new wxCheckBox(Panel1, ID_CHECKBOX1, _("Override Global Vars."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	CheckBox1->SetValue(false);
	BoxSizer2->Add(CheckBox1, 1, wxALL, 5);
	GLitemLinker = new wxCheckBox(Panel1, ID_GLitemLinker, _("GL Item Linker"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GLitemLinker"));
	GLitemLinker->SetValue(false);
	BoxSizer2->Add(GLitemLinker, 1, wxALL, 5);
	GridBagSizer1->Add(BoxSizer2, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	Button3 = new wxButton(Panel1, ID_BUTTON3, _("Save"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	BoxSizer3->Add(Button3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button1 = new wxButton(Panel1, ID_BUTTON1, _("Close"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer3->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	GridBagSizer1->Add(BoxSizer3, wxGBPosition(2, 1), wxDefaultSpan, wxALL|wxALIGN_RIGHT|wxALIGN_BOTTOM, 5);
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	Button2 = new wxButton(Panel1, ID_BUTTON2, _("Test!"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer4->Add(Button2, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
	GridBagSizer1->Add(BoxSizer4, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
	Panel1->SetSizer(GridBagSizer1);
	GridBagSizer1->Fit(Panel1);
	GridBagSizer1->SetSizeHints(Panel1);
	Notebook1->AddPage(Panel1, _("Main"), true);
	BoxSizer1->Add(Notebook1, 1, wxALL|wxEXPAND, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&FMainSettings::OnButton3Click);
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

void FMainSettings::OnButton3Click(wxCommandEvent& event)
{
    if (CheckBox1->IsChecked()) {
        Manager::Get()->GetConfigManager(_T("app"))->Write(_T("/urus_settings/ur_overrsettings"), true);
    } else {
        Manager::Get()->GetConfigManager(_T("app"))->Write(_T("/urus_settings/ur_overrsettings"), false);
    }

    if (GLitemLinker->IsChecked()) {
        Manager::Get()->GetConfigManager(_T("app"))->Write(_T("/urus_settings/gl_linker_options"), true);
    } else {
        Manager::Get()->GetConfigManager(_T("app"))->Write(_T("/urus_settings/gl_linker_options"), false);
    }

    wxMessageBox(wxString::Format(_("%s"), _("UrusStudio settings saved!\n")) +
                 wxString::Format(_("%s"), _("Restart Urus Studio to take effect the changes!")));

    event.Skip();
}
