#ifndef FMAINSETTINGS_H
#define FMAINSETTINGS_H

//(*Headers(FMainSettings)
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/sizer.h>
//*)

class FMainSettings: public wxPanel
{
	public:

		FMainSettings(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~FMainSettings();

		//(*Declarations(FMainSettings)
		wxBoxSizer* BoxSizer1;
		wxBoxSizer* BoxSizer2;
		wxBoxSizer* BoxSizer3;
		wxButton* Button1;
		wxButton* Button2;
		wxButton* Button3;
		wxCheckBox* CheckBox1;
		//*)

	protected:

		//(*Identifiers(FMainSettings)
		static const long ID_CHECKBOX1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_BUTTON3;
		//*)

	private:

		//(*Handlers(FMainSettings)
		void OnButton1Click(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		void OnButton3Click(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
