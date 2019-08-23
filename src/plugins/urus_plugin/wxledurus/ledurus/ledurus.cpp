/////////////////////////////////////////////////////////////////////////////
// Name:        led.cpp
// Purpose:     wxLedurus implementation
// Author:      Thomas Monjalon
// Created:     09/06/2005
// Revision:    09/06/2005
// Licence:     wxWidgets
// mod   by:    Jonas Zinn
// mod date:    24/03/2012
// mod   by:    Hiroshi Takey
// mon date:    26/01/2018
/////////////////////////////////////////////////////////////////////////////

#include "ledurus.h"
#include <string.h>

BEGIN_EVENT_TABLE (wxLedurus, wxWindow)
    EVT_PAINT (wxLedurus::OnPaint)
END_EVENT_TABLE ()

wxLedurus::wxLedurus(wxWindow * parent, wxWindowID id, wxColour disableColour, wxColour onColour, wxColour offColour, const wxPoint & pos, const wxSize & size)
{
    Create(parent, id, disableColour, onColour, offColour);
}

wxLedurus::wxLedurus ()
{

}

wxLedurus::~wxLedurus ()
{
    delete m_bitmap ;
}

bool wxLedurus::Create(wxWindow * parent, wxWindowID id, wxColour disableColour, wxColour onColour, wxColour offColour)
{
    if(!wxWindow::Create(parent, id, wxDefaultPosition, wxDefaultSize))
        return false;

    m_bitmap    = NULL;
    m_isEnabled = true ;
    m_isOn      = false;
    m_Disable   = disableColour;
    m_On        = onColour;
    m_Off       = offColour;
    Enable();

    return true;
}

void wxLedurus::Enable (void)
{
    m_isEnable = true;
    if( m_isOn)
        SetBitmap (m_On.GetAsString( wxC2S_HTML_SYNTAX)) ;
    else
        SetBitmap (m_Off.GetAsString( wxC2S_HTML_SYNTAX)) ;
}

void wxLedurus::Disable( void)
{
    m_isEnable= false;
    SetBitmap( m_Disable.GetAsString( wxC2S_HTML_SYNTAX));
}

void wxLedurus::Switch(void)
{
    if( m_isEnable)
    {
        m_isOn = !m_isOn;
        if(m_isOn)
            SetBitmap (m_On.GetAsString( wxC2S_HTML_SYNTAX)) ;
        else
            SetBitmap (m_Off.GetAsString( wxC2S_HTML_SYNTAX)) ;
    }
}

void wxLedurus::SwitchOn(void)
{
    if( m_isEnable)
    {
        m_isOn = true;
        SetBitmap (m_On.GetAsString( wxC2S_HTML_SYNTAX)) ;
    }
}

void wxLedurus::SwitchOff( void)
{
    if( m_isEnable)
    {
        m_isOn = false;
        SetBitmap (m_Off.GetAsString( wxC2S_HTML_SYNTAX)) ;
    }
}

void wxLedurus::SwitchCustomOff( void)
{
    SwitchOff();
}

void wxLedurus::SwitchCustomOn(void)
{
    SwitchOn();
}

void wxLedurus::SetOnColour (wxColour rgb)
{
    m_On = rgb;
    if (m_isEnabled && m_isOn)
        SetBitmap (m_On.GetAsString( wxC2S_HTML_SYNTAX)) ;

}

void wxLedurus::SetOffColour(wxColour rgb)
{
    m_Off = rgb;
    if (m_isEnabled && !m_isOn)
        SetBitmap (m_Off.GetAsString( wxC2S_HTML_SYNTAX)) ;
}

void wxLedurus::SetDisableColour(wxColour rgb)
{
    m_Disable = rgb;
    if (!m_isEnabled)
        SetBitmap (m_Disable.GetAsString( wxC2S_HTML_SYNTAX)) ;
}

void wxLedurus::SetOnOrOff( bool on)
{

    m_isOn = on;
    if (m_isEnable)
    {
        if( m_isOn)
            SetBitmap (m_On.GetAsString( wxC2S_HTML_SYNTAX)) ;
        else
            SetBitmap (m_Off.GetAsString( wxC2S_HTML_SYNTAX)) ;
    }
}

void wxLedurus::SetCustomOnOrOff( bool on)
{
    SetOnOrOff(on);
}

bool wxLedurus::IsEnabled( void)
{
    return m_isEnabled;
}

bool wxLedurus::IsOn(void)
{
    return m_isOn;
}

void wxLedurus::OnPaint (wxPaintEvent & WXUNUSED (event))
{
    wxPaintDC dc (this) ;
    m_mutex.Lock () ;
    dc.DrawBitmap (* m_bitmap, 0, 0, true) ;
    m_mutex.Unlock () ;
}

#define WX_LED_WIDTH    17
#define WX_LED_HEIGHT   17
#define WX_LED_COLORS    5
#define WX_LED_XPM_COLS    (WX_LED_WIDTH + 1)
#define WX_LED_XPM_LINES   (1 + WX_LED_COLORS + WX_LED_HEIGHT)

void wxLedurus::SetBitmap (wxString color)
{
    char ** xpm = NULL ;
    char * xpmData = NULL ;
    xpm = new char * [WX_LED_XPM_LINES] ;
    if (xpm == NULL)
        goto end ;
    xpmData = new char [WX_LED_XPM_LINES * WX_LED_XPM_COLS] ;
    if (xpmData == NULL)
        goto end ;
    for (int i = 0 ; i < WX_LED_XPM_LINES ; i ++)
        xpm [i] = xpmData + i * WX_LED_XPM_COLS ;
    // width height num_colors chars_per_pixel
    sprintf (xpm [0], "%d %d %d 1", WX_LED_WIDTH, WX_LED_HEIGHT, WX_LED_COLORS) ;
    // colors
    strncpy (xpm [1], "  c None", WX_LED_XPM_COLS) ;
    strncpy (xpm [2], "- c #C0C0C0", WX_LED_XPM_COLS) ;
    strncpy (xpm [3], "_ c #F8F8F8", WX_LED_XPM_COLS) ;
    strncpy (xpm [4], "* c #FFFFFF", WX_LED_XPM_COLS) ;
    strncpy (xpm [WX_LED_COLORS], "X c ", WX_LED_XPM_COLS) ;
    strncpy ((xpm [WX_LED_COLORS]) + 4, color.char_str(), 8) ;
    // pixels
    strncpy (xpm [WX_LED_COLORS +  1], "      -----      ", WX_LED_XPM_COLS) ;
    strncpy (xpm [WX_LED_COLORS +  2], "    ---------    ", WX_LED_XPM_COLS) ;
    strncpy (xpm [WX_LED_COLORS +  3], "   -----------   ", WX_LED_XPM_COLS) ;
    strncpy (xpm [WX_LED_COLORS +  4], "  -----XXX----_  ", WX_LED_XPM_COLS) ;
    strncpy (xpm [WX_LED_COLORS +  5], " ----XX**XXX-___ ", WX_LED_XPM_COLS) ;
    strncpy (xpm [WX_LED_COLORS +  6], " ---X***XXXXX___ ", WX_LED_XPM_COLS) ;
    strncpy (xpm [WX_LED_COLORS +  7], "----X**XXXXXX____", WX_LED_XPM_COLS) ;
    strncpy (xpm [WX_LED_COLORS +  8], "---X**XXXXXXXX___", WX_LED_XPM_COLS) ;
    strncpy (xpm [WX_LED_COLORS +  9], "---XXXXXXXXXXX___", WX_LED_XPM_COLS) ;
    strncpy (xpm [WX_LED_COLORS + 10], "---XXXXXXXXXXX___", WX_LED_XPM_COLS) ;
    strncpy (xpm [WX_LED_COLORS + 11], "----XXXXXXXXX____", WX_LED_XPM_COLS) ;
    strncpy (xpm [WX_LED_COLORS + 12], " ---XXXXXXXXX___ ", WX_LED_XPM_COLS) ;
    strncpy (xpm [WX_LED_COLORS + 13], " ---_XXXXXXX____ ", WX_LED_XPM_COLS) ;
    strncpy (xpm [WX_LED_COLORS + 14], "  _____XXX_____  ", WX_LED_XPM_COLS) ;
    strncpy (xpm [WX_LED_COLORS + 15], "   ___________   ", WX_LED_XPM_COLS) ;
    strncpy (xpm [WX_LED_COLORS + 16], "    _________    ", WX_LED_XPM_COLS) ;
    strncpy (xpm [WX_LED_COLORS + 17], "      _____      ", WX_LED_XPM_COLS) ;
    m_mutex.Lock () ;
    delete m_bitmap ;
    m_bitmap = new wxBitmap (xpm) ;
    if (m_bitmap == NULL)
    {
        m_mutex.Unlock () ;
        goto end ;
    }
    SetSize (wxSize (m_bitmap->GetWidth (), m_bitmap->GetHeight ())) ;
    m_mutex.Unlock () ;
    Refresh () ;
end :
    delete [] xpm ;
    delete [] xpmData ;
}
