#ifndef FMAINSETTINGS_H
#define FMAINSETTINGS_H

//(*Headers(FMainSettings)
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/sizer.h>
//*)

class FMainSettings: public wxPanel
{
	public:

		FMainSettings(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~FMainSettings();

		//(*Declarations(FMainSettings)
		wxButton* Button1;
		wxButton* Button2;
		//*)

	protected:

		//(*Identifiers(FMainSettings)
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(FMainSettings)
		void OnButton1Click(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
