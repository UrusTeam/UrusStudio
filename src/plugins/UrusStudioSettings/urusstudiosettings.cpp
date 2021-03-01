#include <sdk.h> // Code::Blocks SDK
#include <configurationpanel.h>
#include <configmanager.h>
#include <manager.h>
#include <wx/msgdlg.h>
#include <wx/wx.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <debuggermanager.h>
#include <tinyxml.h>
#include <wx/wxscintilla.h>

#ifndef CB_PRECOMP
    #include <wx/string.h>
    #include <wx/utils.h>
    #include "cbproject.h"
    #include "configmanager.h"
    #include "globals.h"
    #include "logmanager.h"
    #include "manager.h"
    #include "projectmanager.h"
    #include <wx/stream.h>
    #include <wx/strconv.h>
    #include <wx/msgdlg.h>
    #include <stdio.h>
    #include <wx/print.h>
#endif

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

    main_settings = new FMainSettings(Manager::Get()->GetAppWindow());

    bool showAtStartup = Manager::Get()->GetConfigManager(_T("app"))->ReadBool(_T("/show_tips"), true);
    if (showAtStartup) {
        Manager::Get()->GetConfigManager(_T("app"))->Write(_T("/show_tips"), true);
    }

    bool override_settings = Manager::Get()->GetConfigManager(_T("app"))->ReadBool(_T("/urus_settings/ur_overrsettings"), true);
    bool enable_comp_opt = Manager::Get()->GetConfigManager(_T("app"))->ReadBool(_T("/urus_settings/gl_linker_options"), true);
    main_settings->CheckBox1->SetValue(override_settings);
    main_settings->GLitemLinker->SetValue(enable_comp_opt);

    if (override_settings) {
        wxString plattoolurus;
        wxString wxplaturus;
        wxString dummy;
        dummy = _T("");
        #if   defined(__WXMSW__)
            plattoolurus = _T("/..");
            wxplaturus =  _T("msw");
        #elif defined(__WXGTK3__)
            plattoolurus = _T("/..");
            wxplaturus =  _T("gtk3");
        #elif defined(__WXGTK20__)
            plattoolurus = _T("/..");
            wxplaturus =  _T("gtk2");
        #elif defined(__WXGTK__)
            plattoolurus = _T("/..");
            wxplaturus =  _T("gtk");
        #elif defined(__WXMAC__)
            plattoolurus = _T("mac");
        #else
            plattoolurus = _T("");
            wxplaturus =  _T("default");
        #endif

        ConfigManager *cfgman_gcv = Manager::Get()->GetConfigManager(_T("gcv"));
        cfgman_gcv->Write(_T("/sets/default/urusspath/base"),_T("$(URUSPATH)"  + plattoolurus  + _T("/")));
        cfgman_gcv->Write(_T("/sets/default/urusspath/include"),_T("$(URUSPATH)") + plattoolurus + _T("/include"));
        cfgman_gcv->Write(_T("/sets/default/urusspath/lib"),_T("$(URUSPATH)") + plattoolurus + _T("/lib"));

        wxString vermajor, verminor;
        wxString verwxurus;
        vermajor = _T(wxSTRINGIZE(wxMAJOR_VERSION));
        verminor = _T(wxSTRINGIZE(wxMINOR_VERSION));
        verwxurus = vermajor + _T(".") + verminor;

        cfgman_gcv->Write(_T("/sets/default/urusstool/base"),(_T("$(URUSTOOL)") + plattoolurus + _T("/")));
        cfgman_gcv->Write(_T("/sets/default/urusstool/include"),(_T("$(URUSTOOL)") + plattoolurus + _T("/include/wx-") + verwxurus) + _T("-urus"));

        if (verwxurus == _T("3.0") || verwxurus == _T("3.1")) {
            cfgman_gcv->Write(_T("/sets/default/urusstool/setup"),(_T("$(URUSTOOL)") + plattoolurus + _T("/lib/wx/include/") + wxplaturus + _T("-unicode-") + verwxurus + _T("-urus")));
        } else {
            cfgman_gcv->Write(_T("/sets/default/urusstool/setup"),(_T("$(URUSTOOL)") + plattoolurus + _T("/lib/wx/include/") + wxplaturus + _T("-unicode-release-") + verwxurus + _T("-urus")));
        }

        cfgman_gcv->Write(_T("/sets/default/urusstool/lib"),(_T("$(URUSTOOL)") + plattoolurus) + _T("/lib"));

        cfgman_gcv->Write(_T("/sets/default/cb/base"),(_T("$(WORKSPACEDIR)") + dummy));
        cfgman_gcv->Write(_T("/sets/default/cb/include"),(_T("$(WORKSPACEDIR)") + dummy + _T("/include/urusstudio")));
        cfgman_gcv->Write(_T("/sets/default/cb/lib"),(_T("$(WORKSPACEDIR)") + dummy + _T("/lib")));

        cfgman_gcv->Write(_T("/sets/default/wx/base"),(_T("$(#URUSSTOOL.base)") + dummy));
        cfgman_gcv->Write(_T("/sets/default/wx/include"),(_T("$(#URUSSTOOL.include)") + dummy));
        cfgman_gcv->Write(_T("/sets/default/wx/lib"),(_T("$(#URUSSTOOL.lib)") + dummy));
        cfgman_gcv->Write(_T("/sets/default/wx/wxlibs"),(_T("wx_") + wxplaturus + _T("u_urus-") + verwxurus));
        cfgman_gcv->Write(_T("/sets/default/wx/wxgl_libs"),(_T("wx_") + wxplaturus + _T("u_urus_gl-") + verwxurus));

        cfgman_gcv->Write(_T("/sets/default/wxsetup/base"),(_T("$(#URUSSTOOL.base)") + dummy));
        cfgman_gcv->Write(_T("/sets/default/wxsetup/include"),(_T("$(#URUSSTOOL.setup)") + dummy));
        cfgman_gcv->Write(_T("/sets/default/wxsetup/lib"),(_T("$(#URUSSTOOL.lib)") + dummy));

        cfgman_gcv->Write(_T("/sets/default/boost/base"),(_T("$(#cb.base)/../modules/boost") + dummy));
        cfgman_gcv->Write(_T("/sets/default/boost/include"),(_T("$(#cb.base)/../modules/boost") + dummy));

        cfgman_gcv->Write(_T("/sets/default/cb_release_type/base"),(_T("-O2") + dummy));

        ConfigManager *config = Manager::Get()->GetConfigManager(wxT("debugger_common"));
        wxString path = wxT("/sets/gdb_debugger");
        wxArrayString configs = config->EnumerateSubPaths(path);
        configs.Sort();

        /* TODO: This is not optimal and not elegant, we need to make it better. */
        config->Write(path + wxT("/conf1/name"), wxString(wxT("Default")));
        if (platform::windows) {
                config->Write(path + wxT("/conf1/values/executable_path"), wxString(wxT("$(#URUSSTOOL.base)/mingw32/i686-w64-mingw32/debug-root/usr/bin/gdb.exe")));
        } else if (platform::Linux) {
            config->Write(path + wxT("/conf1/values/executable_path"), wxString(wxT("$(#URUSSTOOL.base)/i686-pc-linux-gnu/debug-root/usr/bin/gdb")));
        }

        config->Write(path + wxT("/conf2/name"), wxString(wxT("mingw")));

        if (platform::windows) {
            config->Write(path + wxT("/conf2/values/executable_path"), wxString(wxT("$(#URUSSTOOL.base)/mingw32/i686-w64-mingw32/debug-root/usr/bin/gdb.exe")));
        } else if (platform::Linux) {
            config->Write(path + wxT("/conf2/values/executable_path"), wxString(wxT("$(#URUSSTOOL.base)/bin/i686-w64-mingw32-gdb")));
        }

        configs = config->EnumerateSubPaths(path);
        configs.Sort();

        ConfigManager *cfg = Manager::Get()->GetConfigManager(_T("editor"));
        cfg->Write(_T("/default_encoding"), _("UTF-8") + dummy);
        cfg->Write(_T("/default_encoding/use_option"), 1);
        cfg->Write(_T("/default_encoding/find_latin2"), false);
        cfg->Write(_T("/default_encoding/use_system"), true);
        cfg->Write(_T("/eol/eolmode"), wxSCI_EOL_LF);

        DebuggerManager *dbgManager = Manager::Get()->GetDebuggerManager();
        dbgManager->RebuildAllConfigs();
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

	int idx = menuBar->FindMenu(_("&Urus"));

	if (idx == wxNOT_FOUND) {
        int pos = menuBar->GetMenuCount();
        wxMenu *EditMenu = menuBar->GetMenu(pos);
        menuBar->Remove(pos);

        idmenu1 = new wxMenu;
        menuBar->Insert(pos, idmenu1, _("&Urus"));
        idmenu1->Append(idMenuUrusSetMain, _("Settings"),_T(""),wxITEM_CHECK);
        //menuBar->Insert(pos + 1, EditMenu, _("&Help"));
	}
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

    Manager::Get()->AddonToolBar(toolBar,_T("urussettings_toolbar"));
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
    event.Skip();
}

void urusstudiosettings::OnUpdateUI(wxUpdateUIEvent& event)
{
    if (idmenu1) {
        idmenu1->Check(idMenuUrusSetMain,IsWindowReallyShown(main_settings));
    }
    // allow other UpdateUI handlers to process this event
    // *very* important! don't forget it...
    event.Skip();

}

void urusstudiosettings::TestCommand()
{
    bool enable_comp_opt = Manager::Get()->GetConfigManager(_T("app"))->ReadBool(_T("/urus_settings/gl_linker_options"), true);
    if (enable_comp_opt) {
        ProjectManager *pm = Manager::Get()->GetProjectManager();
        cbProject* prjActive = pm->GetActiveProject();
        ProjectBuildTarget* buildTargetActive;

        if (pm->GetProjects()->GetCount() <= 0) {
            wxMessageBox(_("No active projects!"));
            return;
        }

        //prjActive->AddLinkLib(_("$(#wx.wxgl_libs)"));

        uint16_t cnt = prjActive->GetBuildTargetsCount();
        wxString scnt1;
        scnt1 << cnt;
        wxMessageBox(_("ACTIVE MAIN\n\nPrj: ") + prjActive->GetTitle() + _("\nBldTgt cnt:\t") + scnt1);

        for (uint16_t i1 = 0; i1 < cnt; i1++) {
            buildTargetActive = prjActive->GetBuildTarget(i1);
            //buildTargetActive->AddLinkLib(_("$(#wx.wxgl_libs)"));
        }

        wxArrayString arraylnk = prjActive->GetLinkerOptions();
        cnt = arraylnk.GetCount();
        wxString scnt;
        scnt.Printf(_("%d"), cnt);
        wxMessageBox(_("ACTIVE MAIN\n\nPrj: ") + prjActive->GetTitle() + _("\nLnkOpt cnt:\t") + scnt);

        for (uint16_t i1 = 0; i1 < cnt; i1++) {
            scnt = arraylnk.Item(i1);
            wxMessageBox(_("ACTIVE MAIN\n\nPrj:\t") + prjActive->GetTitle() + _("\nLnk Opt:\t") + scnt);
        }

        ProjectBuildTarget* buildTargets;
        ProjectsArray *prjarrays = pm->GetProjects();
        cbProject* prj;

        for (uint16_t i1 = 0; i1 < prjarrays->GetCount(); i1++) {
            prj = prjarrays->Item(i1);
            wxArrayString prjarraylnks = prj->GetLinkLibs();

            for (uint16_t p1 = 0; p1 < prjarraylnks.GetCount(); p1++) {
                wxMessageBox(_("MAIN\n\nPrj:\t") + prj->GetTitle() + _("\nLnk Lib:\t") + prjarraylnks.Item(p1));
                if (prjarraylnks.Item(p1).Contains(_("wxgl_libs"))) {
                    wxMessageBox(_("Contains wxgl_libs on MAIN PRJ ") + prj->GetTitle() + _("!"));
                    //prj->RemoveLinkLib(prjarraylnks.Item(p1));
                }
            }

            for (uint16_t i2 = 0; i2 < prj->GetBuildTargetsCount(); i2++) {
                buildTargets = prj->GetBuildTarget(i2);
                wxArrayString strlinks = buildTargets->GetLinkLibs();
                for (uint16_t i3 = 0; i3 < strlinks.GetCount(); i3++) {
                    wxMessageBox(_("TARGETS\n\nPrj:\t") + prj->GetTitle() + _("\nTgt:\t") + buildTargets->GetTitle() + _("\nLnk Lib:\t") + strlinks.Item(i3));
                    if (strlinks.Item(i3).Contains(_("wxgl_libs"))) {
                        wxMessageBox(_("Contains wxgl_libs on TARGET ") + buildTargets->GetTitle() + _("!"));
                        //buildTargets->RemoveLinkLib(strlinks.Item(i3));
                    }
                }
            }
        }
    }

    wxMessageBox(_("UrusStudio Test OK!"));
}

urusstudiosettings* URUS_STUDIO_SETTINGS::GetUrusStudioMain()
{
    return main_urusstudio;
}
