#include <sdk.h> // Code::Blocks SDK
#include <configurationpanel.h>
#include <configmanager.h>
#include <manager.h>
#include <wx/msgdlg.h>
#include <wx/wx.h>
#include <wx/xrc/xmlres.h>

#include "urusstudiosettings.h"

static urusstudiosettings* main_urusstudio;
// Register the plugin with Code::Blocks.
// We are using an anonymous namespace so we don't litter the global one.
namespace
{
    PluginRegistrant<urusstudiosettings> reg(_T("urusstudiosettings"));
}

int idMenuUrusSetMain = wxNewId();
int idToolUrusSetMain = XRCID("idMenuUrusSettingsMain");

// events handling
BEGIN_EVENT_TABLE(urusstudiosettings, cbPlugin)
    EVT_MENU(idMenuUrusSetMain,urusstudiosettings::Execute)
    EVT_MENU(idToolUrusSetMain,urusstudiosettings::Execute)
    EVT_UPDATE_UI(idMenuUrusSetMain, urusstudiosettings::OnUpdateUI)
    // add any events you want to handle here
END_EVENT_TABLE()

// constructor
urusstudiosettings::urusstudiosettings()
{
    // Make sure our resources are available.
    // In the generated boilerplate code we have no resources but when
    // we add some, it will be nice that this code is in place already ;)
    if(!Manager::LoadResource(_T("urusstudiosettings.zip")))
    {
        NotifyMissingFile(_T("urusstudiosettings.zip"));
    }


}

// destructor
urusstudiosettings::~urusstudiosettings()
{
}

void urusstudiosettings::OnAttach()
{
    // do whatever initialization you need for your plugin
    // NOTE: after this function, the inherited member variable
    // m_IsAttached will be TRUE...
    // You should check for it in other functions, because if it
    // is FALSE, it means that the application did *not* "load"
    // (see: does not need) this plugin...
    ConfigManager *cfgman_gcv = Manager::Get()->GetConfigManager(_T("gcv"));
    cfgman_gcv->Write(_T("/sets/default/uruspath/base"),"$(URUSSPATH)");
    cfgman_gcv->Write(_T("/sets/default/uruspath/include"),"$(URUSSPATH)/include");
    cfgman_gcv->Write(_T("/sets/default/uruspath/lib"),"$(URUSSPATH)/devel");

    wxString plattoolurus;
    #if   defined(__WXMSW__)
        plattoolurus = _T("mingw32");
    #elif defined(__WXGTK__)
        plattoolurus = _T("gtk");
    #elif defined(__WXMAC__)
        plattoolurus = _T("mac");
    #else
        plattoolurus = _T("");
    #endif
    wxString vermajor, verminor;
    wxString verwxurus;
    vermajor = _T(wxSTRINGIZE(wxMAJOR_VERSION));
    verminor = _T(wxSTRINGIZE(wxMINOR_VERSION));
    verwxurus = vermajor + _T(".") + verminor;

    cfgman_gcv->Write(_T("/sets/default/urustool/base"),(_T("$(URUSTOOL)/") + plattoolurus));
    cfgman_gcv->Write(_T("/sets/default/urustool/include"),(_T("$(URUSTOOL)/") + plattoolurus + _T("/include/wx-") + verwxurus) + _T("-urus"));
    cfgman_gcv->Write(_T("/sets/default/urustool/setup"),(_T("$(URUSTOOL)/") + plattoolurus + _T("/lib/wx/include/msw-unicode-release-") + verwxurus + _T("-urus")));
    cfgman_gcv->Write(_T("/sets/default/urustool/lib"),(_T("$(URUSTOOL)/") + plattoolurus) + _T("/lib"));

    main_settings = new FMainSettings(Manager::Get()->GetAppWindow());
    CodeBlocksDockEvent evt(cbEVT_ADD_DOCK_WINDOW);
    evt.name = _T("Urus");
    evt.title = _("Urus Settings");
    evt.pWindow = main_settings;
    evt.dockSide = CodeBlocksDockEvent::dsFloating;
    evt.desiredSize.Set(400, 300);
    evt.floatingSize.Set(400, 300);
    evt.minimumSize.Set(200, 150);
    Manager::Get()->ProcessEvent(evt);

}

void urusstudiosettings::OnRelease(bool appShutDown)
{
    // do de-initialization for your plugin
    // if appShutDown is true, the plugin is unloaded because Code::Blocks is being shut down,
    // which means you must not use any of the SDK Managers
    // NOTE: after this function, the inherited member variable
    // m_IsAttached will be FALSE...
}

void urusstudiosettings::BuildMenu(wxMenuBar* menuBar)
{
    //The application is offering its menubar for your plugin,
    //to add any menu items you want...
    //Append any items you need in the menu...
    //NOTE: Be careful in here... The application's menubar is at your disposal.
    //NotImplemented(_T("urusstudiosettings::BuildMenu()"));
    int pos = menuBar->FindMenu(_("&Help"));
    wxMenu *EditMenu = menuBar->GetMenu(pos);
    menuBar->Remove(pos);

    menuBar->Insert(pos, idmenu1, _("&Urus"));
    idmenu1->Append(idMenuUrusSetMain, _("Settings"),_T(""),wxITEM_CHECK);
    menuBar->Insert(pos, EditMenu, _("&Help"));
}

void urusstudiosettings::BuildModuleMenu(const ModuleType type, wxMenu* menu, const FileTreeData* data)
{
    //Some library module is ready to display a pop-up menu.
    //Check the parameter \"type\" and see which module it is
    //and append any items you need in the menu...
    //TIP: for consistency, add a separator as the first item...
    //NotImplemented(_T("urusstudiosettings::BuildModuleMenu()"));

}

bool urusstudiosettings::BuildToolBar(wxToolBar* toolBar)
{
    //The application is offering its toolbar for your plugin,
    //to add any toolbar items you want...
    //Append any items you need on the toolbar...
    //NotImplemented(_T("urusstudiosettings::BuildToolBar()"));

    if (!IsAttached() || !toolBar)
        return false;

    wxString my_16x16 = Manager::isToolBar16x16(toolBar) ? _T("_16x16") : _T("");
    Manager::Get()->AddonToolBar(toolBar,_T("urussettings_toolbar")+my_16x16);
    toolBar->Realize();
    toolBar->SetInitialSize();

    // return true if you add toolbar items
    return true;
}

void urusstudiosettings::Execute(wxCommandEvent& event)
{
    int eventId = event.GetId();
    if (eventId == idMenuUrusSetMain)
    {
        CodeBlocksDockEvent evt(event.IsChecked() ? cbEVT_SHOW_DOCK_WINDOW : cbEVT_HIDE_DOCK_WINDOW);
        evt.pWindow = main_settings;
        Manager::Get()->ProcessEvent(evt);
    }
    if (eventId == idToolUrusSetMain)
    {
        TestCommand();
    }
}

void urusstudiosettings::OnUpdateUI(wxUpdateUIEvent& event)
{

    idmenu1->Check(idMenuUrusSetMain,IsWindowReallyShown(main_settings));
    // allow other UpdateUI handlers to process this event
    // *very* important! don't forget it...
    event.Skip();

}

void urusstudiosettings::TestCommand()
{
    wxMessageBox(_("UrusStudio Test OK!"));
}

urusstudiosettings* URUS_STUDIO_SETTINGS::GetUrusStudioMain()
{
    return main_urusstudio;
}
