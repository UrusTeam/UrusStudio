#ifndef _WXS_LEDURUS_H
#define _WXS_LEDURUS_H

#include "wxswidget.h"


class wxsLedurus : public wxsWidget
{
    public:
        wxsLedurus(wxsItemResData* Data);
        virtual ~wxsLedurus();
    protected:

        void      OnBuildCreatingCode();
        wxObject* OnBuildPreview(wxWindow* Parent,long Flags);
        void      OnEnumWidgetProperties(long Flags);

        wxsColourData	m_Disable;
        wxsColourData	m_EnableOn;
        wxsColourData	m_EnableOff;
        bool m_State;
        bool m_StateCustom;

    private:
};

#endif // _WXS_LEDURUS_H
