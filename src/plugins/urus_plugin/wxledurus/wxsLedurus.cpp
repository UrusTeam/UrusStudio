#include "wxsLedurus.h"
#include "ledurus/ledurus.h"

namespace
{

    #include "images/wxled16.xpm"
    #include "images/wxled32.xpm"

    wxsRegisterItem<wxsLedurus> Reg(
        _T("wxLedurus"),
        wxsTWidget,
        _T("wxWindows"),
        _T("Hiroshi Takey"),
        _T("htakey@gmail.com"),
        _T(""),
        _T("URUS_Ardupilot"),
        80,
        _T("Ledurus"),
        wxsCPP,
        1, 0,
        wxBitmap(wxled32),
        wxBitmap(wxled16),
        true);

}

wxsLedurus::wxsLedurus(wxsItemResData* Data):
    wxsWidget(
        Data,
        &Reg.Info,
        NULL,
        NULL,
        flVariable | flId|flEnabled),
        m_State(true),
        m_StateCustom(true)
{
    //ctor
    m_Disable = wxColour(128,128,128);
    m_EnableOn  = *wxGREEN;
    m_EnableOff  = *wxRED;
    GetBaseProps()->m_Enabled = false;
}

wxsLedurus::~wxsLedurus()
{
    //dtor
}

void wxsLedurus::OnBuildCreatingCode()
{

    wxString ss  = m_Disable.BuildCode(GetCoderContext());
    wxString ss2 = m_EnableOn.BuildCode(GetCoderContext());
    wxString ss3 = m_EnableOff.BuildCode(GetCoderContext());

    switch ( GetLanguage())
    {
        case wxsCPP:
            AddHeader(_T("<ledurus/ledurus.h>"),GetInfo().ClassName);
            Codef(_T("%C(%W,%I,%s,%s,%s,%P,%S);\n"), ss.wx_str(), ss2.wx_str(), ss3.wx_str());
            if ( !GetBaseProps()->m_Enabled)
                Codef(_T("%ADisable();\n"));
            if(m_State)
                Codef(_T("%ASwitchOn();\n"));
            else
                Codef(_T("%ASwitchOff();\n"));

            if(m_StateCustom)
                Codef(_T("%ASwitchCustomOn();\n"));
            else
                Codef(_T("%ASwitchCustomOff();\n"));

            break;

        case wxsUnknownLanguage: // fall-though
        default:
            wxsCodeMarks::Unknown(_T("wxsLedurus::OnBuildCreatingCode"),GetLanguage());
    }
}

wxObject* wxsLedurus::OnBuildPreview(wxWindow* Parent,cb_unused long Flags)
{
    wxLedurus *Led = new wxLedurus(Parent,GetId(),m_Disable.GetColour(), m_EnableOn.GetColour(), m_EnableOff.GetColour(),Pos(Parent),Size(Parent));

    if( !GetBaseProps()->m_Enabled)
        Led->Disable();
    if( m_State)
        Led->SwitchOn();
    else
        Led->SwitchOff();

    if( m_StateCustom)
        Led->SwitchCustomOn();
    else
        Led->SwitchCustomOff();

    return Led;
}

void wxsLedurus::OnEnumWidgetProperties(cb_unused long Flags)
{

    WXS_COLOUR(
    wxsLedurus,
    m_Disable,
    _("Disable Colour"),
    _T("disable_colour"));

    WXS_COLOUR(
    wxsLedurus,
    m_EnableOn,
    _("On Colour"),
    _T("on_colour"));

    WXS_COLOUR(
    wxsLedurus,
    m_EnableOff,
    _("Off Colour"),
    _T("off_colour"));

    WXS_BOOL(
        wxsLedurus,
        m_State,
        _("On"),
        _T("on_or_off"),
        true
    );

    WXS_BOOL(
        wxsLedurus,
        m_StateCustom,
        _("Custom On"),
        _T("custom_on_or_off"),
        true
    );
}

/*bool wxsLedurus::OnXmlWrite(TiXmlElement* Element, bool IsXRC, bool IsExtra)
{

    TiXmlElement* ColourElem = Element->InsertEndChild(TiXmlElement("colour"))->ToElement();
    ColourElem->SetAttribute("enableon_colour",cbU2C(m_EnableOn.GetColour().GetAsString()));
    ColourElem->SetAttribute("enableoff_colour",cbU2C(m_EnableOff.GetColour().GetAsString()));
    ColourElem->SetAttribute("disable_color",cbU2C(m_Disable.GetColour().GetAsString()));
    ColourElem->SetAttribute("on_or_off_state",m_State);

    return wxsWidget::OnXmlWrite(Element, IsXRC, IsExtra);
}

bool wxsLedurus::OnXmlRead(TiXmlElement* Element, bool IsXRC, bool IsExtra)
{

    TiXmlElement* ColourElem = Element->FirstChildElement("disable_colour");
    if(ColourElem != NULL)
    {
        m_Disable.GetColour().Set(cbC2U(Element->Value()));
    }
    ColourElem = Element->FirstChildElement("on_colour");
    if(ColourElem != NULL)
    {
        m_EnableOn.GetColour().Set(cbC2U(Element->Value()));
    }
    ColourElem = Element->FirstChildElement("off_colour");
    if(ColourElem != NULL)
    {
        m_EnableOff.GetColour().Set(cbC2U(Element->Value()));
    }
    ColourElem = Element->FirstChildElement("on_or_off");
    if(ColourElem != NULL)
    {
        m_State = static_cast<bool>(wxAtoi(cbC2U(Element->Value())));
    }

    return wxsWidget::OnXmlRead(Element, IsXRC, IsExtra);
}*/
