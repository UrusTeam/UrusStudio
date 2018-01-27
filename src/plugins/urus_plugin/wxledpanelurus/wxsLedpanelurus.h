#ifndef _WXS_LEDPANELURUS_H
#define _WXS_LEDPANELURUS_H

#include "wxswidget.h"


class wxsLedpanelurus : public wxsWidget
{
    public:
        wxsLedpanelurus(wxsItemResData* Data);
        virtual ~wxsLedpanelurus();
    protected:

        void      OnBuildCreatingCode();
        wxObject* OnBuildPreview(wxWindow* Parent,long Flags);
        void      OnEnumWidgetProperties(long Flags);

        bool m_State;

    private:
};

#endif // _WXS_LEDPANELURUS_H
