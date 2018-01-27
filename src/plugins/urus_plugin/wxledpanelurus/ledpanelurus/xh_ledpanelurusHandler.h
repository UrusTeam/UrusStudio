#ifndef _XH_LEDUPANELRUSHANDLER_H
#define _XH_LEDUPANELRUSHANDLER_H

#include <wx/xrc/xmlres.h>


class wxLedpanelurusHandler : public wxXmlResourceHandler
{
    public:
        /** Default constructor */
        wxLedpanelurusHandler();

        // Creates the control and returns a pointer to it.
        virtual wxObject *DoCreateResource();

        // Returns true if we know how to create a control for the given node.
        virtual bool CanHandle(wxXmlNode *node);

        // Register with wxWidgets' dynamic class subsystem.
        DECLARE_DYNAMIC_CLASS(wxLedpanelurusHandler)
};

#endif // _XH_LEDPANELURUSHANDLER_H
