#ifndef FORMATINDENT_H
#define FORMATINDENT_H

//(*Headers(FormatIndentDlg)
#include <wx/spinctrl.h>
#include <wx/checkbox.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/notebook.h>
#include <wx/radiobut.h>
#include <wx/panel.h>
#include <wx/stattext.h>
//*)

class FormatIndentDlg: public wxDialog
{
	public:

	    enum FormatIndentScope{ fisProject, fisSelection, fisCurrentFile };

		FormatIndentDlg(wxWindow* parent);
		virtual ~FormatIndentDlg();

		//(*Declarations(FormatIndentDlg)
		wxSpinCtrl* spc_Spaces;
		wxCheckBox* cb_UseTabs;
		wxCheckBox* cb_TrimLines;
		wxRadioButton* rb_ActiveProject;
		wxPanel* Panel1;
		wxCheckBox* cb_CONTTypeAfter;
		wxCheckBox* cb_CONTMod;
		wxCheckBox* cb_PROGafter;
		wxCheckBox* cb_MODafter;
		wxStaticText* stxt_TabSpaces;
		wxCheckBox* cb_CONTProc;
		wxStaticText* StaticText1;
		wxPanel* Panel2;
		wxStaticText* StaticText3;
		wxCheckBox* cb_SELECTTYPEafter;
		wxPanel* Panel3;
		wxStaticText* StaticText2;
		wxNotebook* Notebook1;
		wxRadioButton* rb_Selection;
		wxCheckBox* cb_CONTProcAfter;
		wxCheckBox* cb_TabAsEditor;
		wxCheckBox* cb_CONTModAfter;
		wxCheckBox* cb_CONTType;
		wxRadioButton* rb_CurrentFile;
		wxCheckBox* cb_SELECTCASEafter;
		//*)

        FormatIndentScope GetFormatScope();

	protected:

		//(*Identifiers(FormatIndentDlg)
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT3;
		static const long ID_RADIOBUTTON1;
		static const long ID_RADIOBUTTON2;
		static const long ID_RADIOBUTTON3;
		static const long ID_PANEL1;
		static const long ID_STATICTEXT2;
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX3;
		static const long ID_CHECKBOX4;
		static const long ID_CHECKBOX5;
		static const long ID_CHECKBOX6;
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX7;
		static const long ID_CHECKBOX8;
		static const long ID_CHECKBOX9;
		static const long ID_CHECKBOX10;
		static const long ID_PANEL3;
		static const long ID_CHECKBOX11;
		static const long ID_CHECKBOX12;
		static const long ID_CHECKBOX13;
		static const long ID_STATICTEXT4;
		static const long ID_SPINCTRL1;
		static const long ID_PANEL2;
		static const long ID_NOTEBOOK1;
		//*)

	private:

		//(*Handlers(FormatIndentDlg)
		void OnCbTabAsEditorClick(wxCommandEvent& event);
		//*)

		void OnOK(wxCommandEvent& event);


		DECLARE_EVENT_TABLE()
};

#endif
