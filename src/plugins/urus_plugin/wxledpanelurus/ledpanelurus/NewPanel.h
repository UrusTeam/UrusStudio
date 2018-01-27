#ifndef NEWPANEL_H
#define NEWPANEL_H

//(*Headers(NewPanel)
#include <wx/panel.h>
//*)

class NewPanel: public wxPanel
{
	public:

		NewPanel(wxWindow* parent,wxWindowID id=wxID_ANY);
		NewPanel(){}
		virtual ~NewPanel();

		void Switch();
		void SwitchON();
		void SwitchOFF();
		//(*Declarations(NewPanel)
		//*)

	protected:

        bool m_onoff;

        //(*Identifiers(NewPanel)
        //*)

	private:

		DECLARE_EVENT_TABLE()
};

#endif
