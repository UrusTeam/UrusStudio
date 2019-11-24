
#include "RadialGL_App.h"

//(*AppHeaders
#include "RadialGL_Dialog.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(RadialGL_App);

bool RadialGL_App::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	RadialGL_Dialog Dlg(0);
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }
    //*)
    return wxsOK;

}
