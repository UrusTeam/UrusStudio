#include "wxsLedpanelurus.h"
#include "ledpanelurus/NewPanel.h"

namespace
{

    #include "images/wxled16.xpm"
    #include "images/wxled32.xpm"

    wxsRegisterItem<wxsLedpanelurus> Reg(
        _T("NewPanel"),
        wxsTWidget,
        _T("wxWindows"),
        _T("Hiroshi Takey"),
        _T("htakey@gmail.com"),
        _T(""),
        _T("URUS_Ardupilot"),
        80,
        _T("Ledpanelurus"),
        wxsCPP,
        1, 0,
        wxBitmap(wxled32),
        wxBitmap(wxled16),
        true);

}

wxsLedpanelurus::wxsLedpanelurus(wxsItemResData* Data):
    wxsWidget(
        Data,
        &Reg.Info,
        NULL,
        NULL,
        flVariable | flId|flEnabled),
        m_State(true)
{
    //ctor
}

wxsLedpanelurus::~wxsLedpanelurus()
{
    //dtor
}

void wxsLedpanelurus::OnBuildCreatingCode()
{

    switch ( GetLanguage())
    {
        case wxsCPP:
            AddHeader(_T("<ledpanelurus/NewPanel.h>"),GetInfo().ClassName);
            Codef(_T("%C(%W,%I);\n"));

            if(m_State)
                Codef(_T("%ASetBackgroundColour(wxColour(0,255,0));\n"));
            else
                Codef(_T("%ASetBackgroundColour(wxColour(255,0,0));\n"));

            break;

        case wxsUnknownLanguage: // fall-though
        default:
            wxsCodeMarks::Unknown(_T("wxsLedpanelurus::OnBuildCreatingCode"),GetLanguage());
    }
}

wxObject* wxsLedpanelurus::OnBuildPreview(wxWindow* Parent,cb_unused long Flags)
{
    NewPanel *Panel = new NewPanel(Parent,GetId());

    if( m_State)
        Panel->SwitchON();
    else
        Panel->SwitchOFF();

    return Panel;
}

void wxsLedpanelurus::OnEnumWidgetProperties(cb_unused long Flags)
{

    WXS_BOOL(
        wxsLedpanelurus,
        m_State,
        _("On"),
        _T("on_or_off"),
        true
    );

}

