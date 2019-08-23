#include <sdk.h> // Code::Blocks SDK
#include <configurationpanel.h>
#include "urus_plug.h"

// Register the plugin with Code::Blocks.
// We are using an anonymous namespace so we don't litter the global one.
namespace
{
    PluginRegistrant<urus_plug> reg(_T("urus_plug"));
}

int idUrusPlugMain = wxNewId();

// events handling
BEGIN_EVENT_TABLE(urus_plug, cbPlugin)
    EVT_MENU(idUrusPlugMain,urus_plug::Execute)
    EVT_UPDATE_UI(idUrusPlugMain, urus_plug::OnUpdateUI)
    // add any events you want to handle here
END_EVENT_TABLE()

// constructor
urus_plug::urus_plug()
{
    // Make sure our resources are available.
    // In the generated boilerplate code we have no resources but when
    // we add some, it will be nice that this code is in place already ;)

    if(!Manager::LoadResource(_T("urus_plug.zip")))
    {
        NotifyMissingFile(_T("urus_plug.zip"));
    }

}

// destructor
urus_plug::~urus_plug()
{
}

void urus_plug::OnAttach()
{
    // do whatever initialization you need for your plugin
    // NOTE: after this function, the inherited member variable
    // m_IsAttached will be TRUE...
    // You should check for it in other functions, because if it
    // is FALSE, it means that the application did *not* "load"
    // (see: does not need) this plugin...
}

void urus_plug::OnRelease(bool appShutDown)
{
    // do de-initialization for your plugin
    // if appShutDown is true, the plugin is unloaded because Code::Blocks is being shut down,
    // which means you must not use any of the SDK Managers
    // NOTE: after this function, the inherited member variable
    // m_IsAttached will be FALSE...
}

void urus_plug::BuildMenu(wxMenuBar* menuBar)
{
    //The application is offering its menubar for your plugin,
    //to add any menu items you want...
    //Append any items you need in the menu...
    //NOTE: Be careful in here... The application's menubar is at your disposal.
    //NotImplemented(_T("urusstudiosettings::BuildMenu()"));
}

void urus_plug::BuildModuleMenu(const ModuleType type, wxMenu* menu, const FileTreeData* data)
{
    //Some library module is ready to display a pop-up menu.
    //Check the parameter \"type\" and see which module it is
    //and append any items you need in the menu...
    //TIP: for consistency, add a separator as the first item...
    //NotImplemented(_T("urusstudiosettings::BuildModuleMenu()"));
}

bool urus_plug::BuildToolBar(wxToolBar* toolBar)
{
    //The application is offering its toolbar for your plugin,
    //to add any toolbar items you want...
    //Append any items you need on the toolbar...
    //NotImplemented(_T("urusstudiosettings::BuildToolBar()"));

    return false;
}

void urus_plug::Execute(wxCommandEvent& event)
{
    int eventId = event.GetId();
    if (eventId == idUrusPlugMain)
    {
    }
}

void urus_plug::OnUpdateUI(wxUpdateUIEvent& event)
{
    // allow other UpdateUI handlers to process this event
    // *very* important! don't forget it...
    event.Skip();
}
