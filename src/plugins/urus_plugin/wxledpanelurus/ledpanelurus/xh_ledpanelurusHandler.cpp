#include "xh_ledpanelurusHandler.h"

#include "ledpanelurus/NewPanel.h"

// Register with wxWidgets' dynamic class subsystem.
IMPLEMENT_DYNAMIC_CLASS(wxLedpanelurusHandler, wxXmlResourceHandler)

wxLedpanelurusHandler::wxLedpanelurusHandler()
{
    // this call adds support for all wxWindows class styles
    // (e.g. wxBORDER_SIMPLE, wxBORDER_SUNKEN, wxWS_EX_* etc etc)
    AddWindowStyles();
}

wxObject *wxLedpanelurusHandler::DoCreateResource()
{
    // the following macro will init a pointer named "control"
    // with a new instance of the MyControl class, but will NOT
    // Create() it!
    XRC_MAKE_INSTANCE(control, NewPanel)

    control->Create(m_parentAsWindow, GetID());

    if( GetBool(wxT("enabled"),true))
        control->Enable();
    else
        control->Disable();

    //control->SetOnOrOff(GetBool(wxT("on_or_off")));
    //control->SetCustomOnOrOff(GetBool(wxT("custom_on_or_off")));

    SetupWindow(control);

    return control;
}

bool wxLedpanelurusHandler::CanHandle(wxXmlNode *node)
{
    // this function tells XRC system that this handler can parse
    // the <object class="MyControl"> tags
    return IsOfClass(node, wxT("NewPanel"));
}
