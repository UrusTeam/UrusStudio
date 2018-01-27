#ifndef _XH_LEDURUSHANDLER_H
#define _XH_LEDURUSHANDLER_H

#include <wx/xrc/xmlres.h>


class wxLedurusHandler : public wxXmlResourceHandler
{
    public:
        /** Default constructor */
        wxLedurusHandler();

        // Creates the control and returns a pointer to it.
        virtual wxObject *DoCreateResource();

        // Returns true if we know how to create a control for the given node.
        virtual bool CanHandle(wxXmlNode *node);

        // Register with wxWidgets' dynamic class subsystem.
        DECLARE_DYNAMIC_CLASS(wxLedurusHandler)
};

#endif // _XH_LEDURUSHANDLER_H
