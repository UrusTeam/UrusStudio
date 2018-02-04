#include <sdk.h> // Code::Blocks SDK
#include <configurationpanel.h>
#include <configmanager.h>
#include <manager.h>
#include <wx/msgdlg.h>
#include <wx/wx.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>

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

    idmenu1 = new wxMenu;
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

    main_settings = new FMainSettings(Manager::Get()->GetAppWindow());

    bool showAtStartup = Manager::Get()->GetConfigManager(_T("app"))->ReadBool(_T("/show_tips"), true);
    if (showAtStartup) {
        Manager::Get()->GetConfigManager(_T("app"))->Write(_T("/show_tips"), true);
    }

    bool override_settings = Manager::Get()->GetConfigManager(_T("app"))->ReadBool(_T("/ur_overrsettings"), true);
    main_settings->CheckBox1->SetValue(override_settings);

    if (override_settings) {
        wxString plattoolurus;
        wxString wxplaturus;
        wxString dummy;
        dummy = _T("");
        #if   defined(__WXMSW__)
            plattoolurus = _T("/..");
            wxplaturus =  _T("msw");
        #elif defined(__WXGTK__)
            plattoolurus = _T("/..");
            #if GTK_VERSION == 2
                wxplaturus =  _T("gtk2");
            #else
                wxplaturus =  _T("gtk");
            #endif // defined
        #elif defined(__WXMAC__)
            plattoolurus = _T("mac");
        #else
            plattoolurus = _T("");
            wxplaturus =  _T("default");
        #endif

        ConfigManager *cfgman_gcv = Manager::Get()->GetConfigManager(_T("gcv"));
        cfgman_gcv->Write(_T("/sets/default/uruspath/base"),_T("$(URUSSPATH)"  + plattoolurus  + _T("/")));
        cfgman_gcv->Write(_T("/sets/default/uruspath/include"),_T("$(URUSSPATH)") + plattoolurus + _T("/include"));
        cfgman_gcv->Write(_T("/sets/default/uruspath/lib"),_T("$(URUSSPATH)") + plattoolurus + _T("/lib"));

        wxString vermajor, verminor;
        wxString verwxurus;
        vermajor = _T(wxSTRINGIZE(wxMAJOR_VERSION));
        verminor = _T(wxSTRINGIZE(wxMINOR_VERSION));
        verwxurus = vermajor + _T(".") + verminor;

        cfgman_gcv->Write(_T("/sets/default/urusstool/base"),(_T("$(URUSTOOL)") + plattoolurus + _T("/")));
        cfgman_gcv->Write(_T("/sets/default/urusstool/include"),(_T("$(URUSTOOL)") + plattoolurus + _T("/include/wx-") + verwxurus) + _T("-urus"));
        cfgman_gcv->Write(_T("/sets/default/urusstool/setup"),(_T("$(URUSTOOL)") + plattoolurus + _T("/lib/wx/include/") + wxplaturus + _T("-unicode-release-") + verwxurus + _T("-urus")));
        cfgman_gcv->Write(_T("/sets/default/urusstool/lib"),(_T("$(URUSTOOL)") + plattoolurus) + _T("/lib"));

        cfgman_gcv->Write(_T("/sets/default/cb/base"),(_T("$(WORKSPACEDIR)") + dummy));
        cfgman_gcv->Write(_T("/sets/default/cb/include"),(_T("$(WORKSPACEDIR)") + dummy + _T("/include/urusstudio")));
        cfgman_gcv->Write(_T("/sets/default/cb/lib"),(_T("$(WORKSPACEDIR)") + dummy + _T("/lib")));

        cfgman_gcv->Write(_T("/sets/default/wx/base"),(_T("$(#URUSSTOOL.base)") + dummy));
        cfgman_gcv->Write(_T("/sets/default/wx/include"),(_T("$(#URUSSTOOL.include)") + dummy));
        cfgman_gcv->Write(_T("/sets/default/wx/lib"),(_T("$(#URUSSTOOL.lib)") + dummy));
        cfgman_gcv->Write(_T("/sets/default/wx/wxlibs"),(_T("wx_") + wxplaturus + _T("u_urus-") + verwxurus));

        cfgman_gcv->Write(_T("/sets/default/wxsetup/base"),(_T("$(#URUSSTOOL.base)") + dummy));
        cfgman_gcv->Write(_T("/sets/default/wxsetup/include"),(_T("$(#URUSSTOOL.setup)") + dummy));
        cfgman_gcv->Write(_T("/sets/default/wxsetup/lib"),(_T("$(#URUSSTOOL.lib)") + dummy));

        cfgman_gcv->Write(_T("/sets/default/boost/base"),(_T("$(#cb.base)/../modules/boost") + dummy));
        cfgman_gcv->Write(_T("/sets/default/boost/include"),(_T("$(#cb.base)/../modules/boost") + dummy));

        ConfigManager *config = Manager::Get()->GetConfigManager(wxT("debugger_common"));
        wxString path = wxT("/sets/gdb_debugger");
        wxArrayString configs = config->EnumerateSubPaths(path);
        configs.Sort();

        /* TODO: This is not optimal and not elegant, we need to make it better. */
        if (configs.empty())
        {
            config->Write(path + wxT("/conf1/name"), wxString(wxT("Default")));
            if (platform::windows) {
                config->Write(path + wxT("/conf1/values/executable_path"), wxString(wxT("$(#URUSSTOOL.base)/mingw32/i686-w64-mingw32/debug-root/usr/bin/gdb.exe")));
            } else if (platform::Linux) {
                config->Write(path + wxT("/conf1/values/executable_path"), wxString(wxT("$(#URUSSTOOL.base)/mingw32/i686-pc-linux-gnu/debug-root/usr/bin/gdb")));
            }

        }

        config->Write(path + wxT("/conf2/name"), wxString(wxT("mingw")));

        if (platform::windows) {
            config->Write(path + wxT("/conf2/values/executable_path"), wxString(wxT("$(#URUSSTOOL.base)/mingw32/i686-w64-mingw32/debug-root/usr/bin/gdb.exe")));
        } else if (platform::Linux) {
            config->Write(path + wxT("/conf2/values/executable_path"), wxString(wxT("$(#URUSSTOOL.base)/mingw32/i686-pc-linux-gnu/debug-root/usr/bin/gdb")));
        }

        configs = config->EnumerateSubPaths(path);
        configs.Sort();
    }

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
    int pos = menuBar->GetMenuCount();
    //wxMenu *EditMenu = menuBar->GetMenu(pos);
    //menuBar->Remove(pos);

    menuBar->Insert(pos, idmenu1, _("&Urus"));
    idmenu1->Append(idMenuUrusSetMain, _("Settings"),_T(""),wxITEM_CHECK);
    //menuBar->Insert(pos + 1, EditMenu, _("&Help"));
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
