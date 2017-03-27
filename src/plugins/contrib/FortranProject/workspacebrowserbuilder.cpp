/*
 * This file is licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 *
 */

#include <sdk.h>
#include "workspacebrowserbuilder.h"
#include <globals.h>
#include <manager.h>
#include <projectmanager.h>
#include <cbproject.h>

#include <wx/settings.h>
#include <wx/utils.h>
#include <wx/string.h>
#include <string>

WorkspaceBrowserBuilder::WorkspaceBrowserBuilder(ParserF* parser, wxTreeCtrl* treeTop, wxTreeCtrl* treeBottom)
    : m_pActiveProject(0),
    m_Options()
{
    m_AtWork = false;
    m_pImlist = new wxImageList(16, 16);
    wxBitmap bmp;
    wxString prefix2;
    prefix2 = ConfigManager::GetDataFolder() + _T("/images/fortranproject/");

    bmp = cbLoadBitmap(prefix2 + _T("ctor_public.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["use"] = 0;
    bmp = cbLoadBitmap(prefix2 + _T("class_public.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["module"] = 1;
    bmp = cbLoadBitmap(prefix2 + _T("method_public.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["subroutine"] = 2;
    bmp = cbLoadBitmap(prefix2 + _T("method_protected.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["function"] = 3;
    bmp = cbLoadBitmap(prefix2 + _T("method_private.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["program"] = 4;
    bmp = cbLoadBitmap(prefix2 + _T("typedef.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["type"] = 5;
    bmp = cbLoadBitmap(prefix2 + _T("interface.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["interface"] = 6;
    bmp = cbLoadBitmap(prefix2 + _T("funcs_folder.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["function_folder"] = 7;
    bmp = cbLoadBitmap(prefix2 + _T("others_folder.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["others_folder"] = 8;
    bmp = cbLoadBitmap(prefix2 + _T("symbols_folder.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["symbols_folder"] = 9;
    bmp = cbLoadBitmap(prefix2 + _T("preproc.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["preproc"] = 10;
    bmp = cbLoadBitmap(prefix2 + _T("var_public.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["variable"] = 11;
    bmp = cbLoadBitmap(prefix2 + _T("interface_function.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["interface_function"] = 12;
    bmp = cbLoadBitmap(prefix2 + _T("interface_subroutine.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["interface_subroutine"] = 13;
    bmp = cbLoadBitmap(prefix2 + _T("procedure.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["procedure"] = 14;

    bmp = cbLoadBitmap(prefix2 + _T("subroutine_private.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["subroutine_private"] = 15;
    bmp = cbLoadBitmap(prefix2 + _T("function_private.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["function_private"] = 16;
    bmp = cbLoadBitmap(prefix2 + _T("var_private.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["variable_private"] = 17;
    bmp = cbLoadBitmap(prefix2 + _T("var_protected.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["variable_protected"] = 18;
    bmp = cbLoadBitmap(prefix2 + _T("typedef_private.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["type_private"] = 19;
    bmp = cbLoadBitmap(prefix2 + _T("interface_private.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["interface_private"] = 20;
    bmp = cbLoadBitmap(prefix2 + _T("access_list_private.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["access_list_private"] = 21;
    bmp = cbLoadBitmap(prefix2 + _T("access_list_public.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["access_list_public"] = 22;
    bmp = cbLoadBitmap(prefix2 + _T("access_list_protected.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["access_list_protected"] = 23;
    bmp = cbLoadBitmap(prefix2 + _T("procedure_private.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["procedure_private"] = 24;
    bmp = cbLoadBitmap(prefix2 + _T("interface_function_private.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["interface_function_private"] = 25;
    bmp = cbLoadBitmap(prefix2 + _T("interface_subroutine_private.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["interface_subroutine_private"] = 26;
    bmp = cbLoadBitmap(prefix2 + _T("class.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["submodule"] = 27;
    bmp = cbLoadBitmap(prefix2 + _T("interface_subroutine_gen_private.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["interface_sub_gen_private"] = 28;
    bmp = cbLoadBitmap(prefix2 + _T("interface_subroutine_gen.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["interface_sub_gen"] = 29;
    bmp = cbLoadBitmap(prefix2 + _T("interface_function_gen_private.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["interface_fun_gen_private"] = 30;
    bmp = cbLoadBitmap(prefix2 + _T("interface_function_gen.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["interface_fun_gen"] = 31;
    bmp = cbLoadBitmap(prefix2 + _T("typedef_abstract.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["type_abstract"] = 32;
    bmp = cbLoadBitmap(prefix2 + _T("typedef_abstract_private.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["type_abstract_private"] = 33;
    bmp = cbLoadBitmap(prefix2 + _T("dtor_public.png"), wxBITMAP_TYPE_PNG);
    m_pImlist->Add(bmp);
    m_ImgNr["procedure_final"] = 34;

    m_ImgNr["none"] = -1;

    m_pParser = parser;
    m_pTreeTop = treeTop;
    m_pTreeBottom = treeBottom;
    m_pTreeTop->SetImageList(m_pImlist);
    m_pTreeBottom->SetImageList(m_pImlist);
}

WorkspaceBrowserBuilder::~WorkspaceBrowserBuilder()
{
    //dtor
    delete m_pImlist;
}

void WorkspaceBrowserBuilder::Init(const wxString& active_filename,
                                    cbProject* active_project,
                                    const BrowserOptions& options)
{
    m_ActiveFilename = active_filename;
    m_pActiveProject = active_project;
    m_Options = options;

    BuildTree();
}

void WorkspaceBrowserBuilder::BuildTree()
{
    if (Manager::IsAppShuttingDown())
        return;

    m_AtWork = true;

    wxTreeItemId root = m_pTreeTop->GetRootItem();
    if (!root.IsOk())
    {
        root = m_pTreeTop->AddRoot(_("Symbols"), m_ImgNr["symbols_folder"], m_ImgNr["symbols_folder"], new TreeDataF(sfRoot));
        m_pTreeTop->SetItemHasChildren(root);
    }

    wxString oldSelText;
    wxString oldParentText;
    bool oldParent_isRoot = false;
    wxTreeItemId oldSel = m_pTreeTop->GetSelection();
    if (oldSel.IsOk())
    {
        oldSelText = m_pTreeTop->GetItemText(oldSel);
        wxTreeItemId oldParent = m_pTreeTop->GetItemParent(oldSel);
        oldParent_isRoot = (root == oldParent);
        if (oldParent.IsOk())
        {
            oldParentText = m_pTreeTop->GetItemText(oldParent);
        }
    }

    m_pTreeTop->Hide();
    m_pTreeTop->Freeze();
    wxArrayString expandedBottomNodes;
    if (m_Options.visibleBottomTree)
    {
        MakeExpandedNodesArray(expandedBottomNodes);
        m_pTreeBottom->Hide();
        m_pTreeBottom->Freeze();
    }

    m_pTreeTop->DeleteChildren(root);

    wxTreeItemId root_bot = m_pTreeBottom->GetRootItem();
    if (root_bot.IsOk())
        m_pTreeBottom->DeleteChildren(root_bot);

    if (!Manager::IsAppShuttingDown())
    {
        ExpandTop();
        m_pTreeTop->Expand(root);
        if (!m_Options.visibleBottomTree)
        {
            size_t i=0;
            while ( i < m_ExpandedNodes.GetCount() )
            {
                wxTreeItemId item = FindItemByName(m_pTreeTop, m_ExpandedNodes[i]);
                if (item.IsOk())
                {
                    m_pTreeTop->Expand(item);
                    i++;
                }
                else
                {
                    m_ExpandedNodes.RemoveAt(i);
                }
            }
        }
        else
            m_ExpandedNodes.Clear();
    }

    if (m_Options.visibleBottomTree)
    {
        m_pTreeBottom->Thaw();
        m_pTreeBottom->Show();
    }

    m_pTreeTop->Thaw();
    m_pTreeTop->Show();

    m_AtWork = false;

    if (!oldSelText.IsEmpty())
    {
        if ( !oldParent_isRoot )
        {
            wxTreeItemId item = FindItemByName(m_pTreeTop, oldParentText, oldSelText); // refresh selection
            if (item.IsOk())
                m_pTreeTop->SelectItem(item);
        }
        else
        {
            wxTreeItemId item = FindItemByName(m_pTreeTop, oldSelText); // refresh selection
            if (item.IsOk())
            {
                m_pTreeTop->SelectItem(item);
                ExpandBottomNodes(expandedBottomNodes);
            }
        }
    }
}

void WorkspaceBrowserBuilder::DeleteTopRootChildren()
{
    if (Manager::IsAppShuttingDown())
        return;

    wxTreeItemId root = m_pTreeTop->GetRootItem();
    if (root.IsOk())
    {
        m_pTreeTop->DeleteChildren(root);
    }
}

void WorkspaceBrowserBuilder::MakeExpandedNodesArray(wxArrayString &expandedBottomNodes)
{
    if (!m_Options.visibleBottomTree)
        return;

    wxTreeItemIdValue cookie;
    wxTreeItemId root = m_pTreeBottom->GetRootItem();
    if (!root.IsOk())
        return;
    wxTreeItemId item = m_pTreeBottom->GetFirstChild(root, cookie);
    while (item.IsOk())
    {
        if (m_pTreeBottom->IsExpanded(item))
        {
            wxTreeItemIdValue cookie2;
            wxTreeItemId item2 = m_pTreeBottom->GetFirstChild(item, cookie2);
            while (item2.IsOk())
            {
                if (m_pTreeBottom->IsExpanded(item2))
                {
                    expandedBottomNodes.Add(m_pTreeBottom->GetItemText(item));
                    expandedBottomNodes.Add(m_pTreeBottom->GetItemText(item2));
                }
                item2 = m_pTreeBottom->GetNextChild(item, cookie2);
            }
        }
        item = m_pTreeBottom->GetNextChild(root, cookie);
    }
}

void WorkspaceBrowserBuilder::ExpandBottomNodes(wxArrayString &expandedBottomNodes)
{
    if (!m_Options.visibleBottomTree)
        return;

    for (size_t i=1; i<expandedBottomNodes.Count(); i+=2)
    {
        wxTreeItemId item = FindItemByName(m_pTreeBottom, expandedBottomNodes.Item(i-1), expandedBottomNodes.Item(i));
        if (item.IsOk())
            m_pTreeBottom->Expand(item);
    }
}

bool WorkspaceBrowserBuilder::HasChildren(TokenF* tokenParent, int tokenKindMask)
{
    bool has = false;
    for (size_t j=0; j < tokenParent->m_Children.GetCount(); ++j)
    {
        TokenF* tok1 = tokenParent->m_Children.Item(j);
        if (tok1->m_TokenKind & tokenKindMask)
        {
            has = true;
            break;
        }
    }
    return has;
}

bool WorkspaceBrowserBuilder::HasGlobalFunctionsOthers(int tokenKindMask)
{
    bool has = false;
    if (Manager::IsAppShuttingDown())
        return has;

    switch (m_Options.displayFilter)
    {
        case bdfFile:
        {
            if (!m_ActiveFilename.IsEmpty())
                has = FileHasTokens(UnixFilename(m_ActiveFilename), tokenKindMask);
            break;
        }
        case bdfProject:
        {
            for (FilesList::iterator it = m_pActiveProject->GetFilesList().begin(); it != m_pActiveProject->GetFilesList().end(); ++it)
            {
                ProjectFile* pf = *it;
                if (FileHasTokens(UnixFilename(pf->file.GetFullPath()), tokenKindMask))
                {
                    has = true;
                    break;
                }
            }
            break;
        }
        case bdfWorkspace:
        {

            TokensArrayF* pTokens = m_pParser->GetTokens();
            for (size_t i=0; i< pTokens->GetCount(); ++i)
            {
                TokenF* token = pTokens->Item(i);
                if (token->m_TokenKind == tkFile)
                {
                    for (size_t j=0; j < token->m_Children.GetCount(); ++j)
                    {
                        TokenF* tok1 = token->m_Children.Item(j);
                        if (tok1->m_TokenKind & tokenKindMask)
                        {
                            has = true;
                            break;
                        }
                    }
                    if (has)
                        break;
                }
            }
            break;
        }
    }
    return has;
}

bool WorkspaceBrowserBuilder::FileHasTokens(const wxString& fileName, int tokenKindMask)
{
    TokensArrayF* pTokens = m_pParser->GetTokens();
    bool has = false;

    for (size_t i=0; i< pTokens->GetCount(); ++i)
    {
        TokenF* token = pTokens->Item(i);

        if (token->m_TokenKind == tkFile && token->m_Filename.IsSameAs(fileName))
        {
            for (size_t j=0; j < token->m_Children.GetCount(); ++j)
            {
                TokenF* tok1 = token->m_Children.Item(j);
                if (tok1->m_TokenKind & tokenKindMask)
                {
                    has = true;
                    break;
                }
            }
            break;
        }
    }
    return has;
}

void WorkspaceBrowserBuilder::AddTreeChildren(wxTreeCtrl* tree, wxTreeItemId parent, int tokenKindMask)
{
    if (Manager::IsAppShuttingDown())
        return;

    switch (m_Options.displayFilter)
    {
        case bdfFile:
        {
            if (!m_ActiveFilename.IsEmpty() &&
                (!m_Options.showIncludeSeparately ||
                 (m_Options.showIncludeSeparately && !m_pParser->IsIncludeFile(m_ActiveFilename))))
            {
                AddFileNodes(tree, parent, UnixFilename(m_ActiveFilename), tokenKindMask);
            }
            break;
        }
        case bdfProject:
        {
            for (FilesList::iterator it = m_pActiveProject->GetFilesList().begin(); it != m_pActiveProject->GetFilesList().end(); ++it)
            {
                ProjectFile* pf = *it;
                if (!m_Options.showIncludeSeparately ||
                    (m_Options.showIncludeSeparately && !m_pParser->IsIncludeFile(pf->file.GetFullPath())))
                    AddFileNodes(tree, parent, UnixFilename(pf->file.GetFullPath()), tokenKindMask);
            }
            break;
        }
        case bdfWorkspace:
        {
            TokensArrayF* pTokens = m_pParser->GetTokens();
            for (size_t i=0; i< pTokens->GetCount(); ++i)
            {
                TokenF* token = pTokens->Item(i);
                if (token->m_TokenKind == tkFile &&
                    (!m_Options.showIncludeSeparately ||
                     (m_Options.showIncludeSeparately && !m_pParser->IsIncludeFile(token->m_Filename))))
                {
                    AddChildrenNodes(tree, parent, token, tokenKindMask);
                }
            }
            break;
        }
    }
}

bool WorkspaceBrowserBuilder::AddFileNodes(wxTreeCtrl* tree, wxTreeItemId parent, wxString file, int tokenKindMask)
{
    TokensArrayF* pTokens = m_pParser->GetTokens();

    for (size_t i=0; i< pTokens->GetCount(); ++i)
    {
        TokenF* token = pTokens->Item(i);

        if (token->m_TokenKind == tkFile && token->m_Filename.IsSameAs(file))
        {
            return AddChildrenNodes(tree, parent, token, tokenKindMask);
        }
    }
    return false;
}

bool WorkspaceBrowserBuilder::AddChildrenNodes(wxTreeCtrl* tree, wxTreeItemId parent, TokenF* parToken, int tokenKindMask)
{
    int count = 0;
    bool sorted = m_Options.sortAlphabetically;
    TokensArrayF* pTokens = &parToken->m_Children;

    if (parToken->m_TokenKind == tkType)
    {
        count += AddTypeChildren(tree, parent, pTokens);
        return count != 0;
    }

    int childKM = tkFunction | tkProgram | tkSubroutine | tkPreprocessor | tkInterface | tkInterfaceExplicit | tkBlockData |
                    tkType | tkVariable | tkProcedure | tkAccessList;
    int interfaceMask = tkInterface | tkInterfaceExplicit;
    int funChildKM = childKM ^ tkVariable;

    if (!m_Options.showLocalVariables && (parToken->m_TokenKind == tkSubroutine || parToken->m_TokenKind == tkFunction || parToken->m_TokenKind == tkProgram))
    {
        childKM = childKM ^ tkVariable;
        if (tokenKindMask & tkVariable)
            tokenKindMask = tokenKindMask ^ tkVariable;
    }

    for (size_t i=0; i< pTokens->GetCount(); ++i)
    {
        TokenF* token = pTokens->Item(i);
        if (token->m_TokenKind & tokenKindMask)
        {
            if (token->m_TokenKind & interfaceMask)
            {
                count += AddInterfaceNode(tree, parent, token);
            }
            else
            {
                wxString nameDisp = token->m_DisplayName;
                if (token->m_TokenKind == tkVariable)
                    nameDisp << _T(" : ") << token->m_PartFirst;
                wxTreeItemId idni = AddNodeIfNotThere(tree, parent, nameDisp, GetTokenKindImageIdx(token), new TreeDataF(sfToken, token), sorted);
                count++;
                if (tree == m_pTreeTop && !m_Options.visibleBottomTree)
                {
                    if (!m_Options.showLocalVariables && (token->m_TokenKind == tkSubroutine || token->m_TokenKind == tkFunction))
                    {
                        if (HasChildren(token, funChildKM))
                            tree->SetItemHasChildren(idni);
                    }
                    else
                    {
                        if (HasChildren(token, childKM))
                            tree->SetItemHasChildren(idni);
                    }
                }
                else if(tree == m_pTreeBottom && HasChildren(token, childKM))
                {
                    AddChildrenNodes(tree, idni, token, childKM);
                }
            }
        }
    }
    return count != 0;
}

int WorkspaceBrowserBuilder::AddInterfaceNode(wxTreeCtrl* tree, wxTreeItemId parent, TokenF* parToken)
{
    int count = 0;
    bool sorted = m_Options.sortAlphabetically;

    if (!parToken->m_Name.IsEmpty())
    {
        wxString name;
        if (parToken->m_DisplayName.StartsWith(_T("%%")))
        {
            name = parToken->m_DisplayName.Mid(2);
        }
        else
        {
            name = parToken->m_DisplayName;
        }
        AddNodeIfNotThere(tree, parent, name, GetTokenKindImageIdx(parToken), new TreeDataF(sfToken, parToken), sorted);
        count++;
    }
    else
    {
        TokensArrayF* pTokens = &parToken->m_Children;
        if (pTokens)
        {
            int childKM = tkFunction | tkSubroutine;
            int imageIdx;
            for (size_t i=0; i< pTokens->GetCount(); ++i)
            {
                TokenF* token = pTokens->Item(i);
                if (token->m_TokenKind & childKM)
                {
                    if (token->m_TokenKind == tkFunction)
                    {
                        if (token->m_TokenAccess == taPublic)
                            imageIdx = m_ImgNr["interface_function"];
                        else
                            imageIdx = m_ImgNr["interface_function_private"];
                    }
                    else
                    {
                        if (token->m_TokenAccess == taPublic)
                            imageIdx = m_ImgNr["interface_subroutine"];
                        else
                            imageIdx = m_ImgNr["interface_subroutine_private"];
                    }
                    AddNodeIfNotThere(tree, parent, token->m_DisplayName, imageIdx, new TreeDataF(sfToken, token), sorted);
                    count++;
                }
            }
        }
    }
    return count;
}

int WorkspaceBrowserBuilder::AddTypeChildren(wxTreeCtrl* tree, wxTreeItemId parent, TokensArrayF* pTokens)
{
    int count = 0;
    bool sorted = m_Options.sortAlphabetically;
    TokensArrayF varTokens;
    TokensArrayF otherTokens;

    for (size_t i=0; i<pTokens->GetCount(); ++i)
    {
        TokenF* token = pTokens->Item(i);
        if (token->m_TokenKind == tkVariable)
        {
            if (sorted)
            {
                size_t j;
                for (j=0; j<varTokens.GetCount(); j++)
                {
                    if (token->m_DisplayName.CmpNoCase(varTokens.Item(j)->m_DisplayName) < 0)
                        break;
                }
                varTokens.Insert(token, j);
            }
            else
            {
                varTokens.Add(token);
            }
        }
        else
        {
            if (sorted)
            {
                wxString name;
                if (token->m_DisplayName.StartsWith(_T("%%")))
                    name = token->m_DisplayName.Mid(2);
                else
                    name = token->m_DisplayName;
                size_t j;
                for (j=0; j<otherTokens.GetCount(); j++)
                {
                    if (name.CmpNoCase(otherTokens.Item(j)->m_DisplayName) < 0)
                        break;
                }
                otherTokens.Insert(token, j);
            }
            else
            {
                otherTokens.Add(token);
            }
        }
    }

    for (size_t i=0; i<varTokens.GetCount(); ++i)
    {
        wxString nameDisp;
        nameDisp << varTokens.Item(i)->m_DisplayName << _T(" : ") << varTokens.Item(i)->m_PartFirst;
        AddNodeIfNotThere(tree, parent, nameDisp,
                          GetTokenKindImageIdx(varTokens.Item(i)), new TreeDataF(sfToken, varTokens.Item(i)), false);
        count++;
    }

    for (size_t i=0; i<otherTokens.GetCount(); ++i)
    {
        wxString name;
        if (otherTokens.Item(i)->m_DisplayName.StartsWith(_T("%%")))
            name = otherTokens.Item(i)->m_DisplayName.Mid(2);
        else
            name = otherTokens.Item(i)->m_DisplayName;
        AddNodeIfNotThere(tree, parent, name,
                          GetTokenKindImageIdx(otherTokens.Item(i)), new TreeDataF(sfToken, otherTokens.Item(i)), false);
        count++;
    }

    return count;
}

bool WorkspaceBrowserBuilder::SelectNode(wxTreeItemId node)
{
    // m_pTreeTop node was selected
    if (Manager::IsAppShuttingDown() || (!(node.IsOk())) || m_AtWork)
        return false;

    m_pTreeBottom->Freeze();
    wxTreeItemId root = m_pTreeBottom->GetRootItem();
    if (!root)
        root = m_pTreeBottom->AddRoot(_T("Members"));
    else
        m_pTreeBottom->DeleteChildren(root);
    TreeDataF* data = (TreeDataF*)m_pTreeTop->GetItemData(node);
    if (data)
    {
        switch (data->m_SpecialFolder)
        {
            case sfGFuncs:
            {
                AddTreeChildren(m_pTreeBottom, root, tkFunction | tkProgram | tkSubroutine);
                break;
            }
            case sfOthers:
            {
                AddTreeChildren(m_pTreeBottom, root, tkPreprocessor | tkInterface | tkBlockData);
                if (m_Options.showIncludeSeparately)
                    AddIncludeFiles(m_pTreeBottom, root);
                break;
            }
            case sfToken:
            {
				wxTreeItemId rootFuncs = m_pTreeBottom->AppendItem(root, _("Procedures"), m_ImgNr["function_folder"]);
				wxTreeItemId rootOthers = m_pTreeBottom->AppendItem(root, _("Others"), m_ImgNr["others_folder"]);

                TokenF* pToken = data->m_pToken;
                AddChildrenNodes(m_pTreeBottom, rootFuncs, pToken, tkFunction | tkSubroutine | tkProcedure);
                AddChildrenNodes(m_pTreeBottom, rootOthers, pToken, tkType | tkInterface | tkInterfaceExplicit | tkAccessList | tkVariable);

                m_pTreeBottom->Expand(rootFuncs);
                m_pTreeBottom->Expand(rootOthers);
                //ExpandAll();

                break;
            }
            default: break;
        }
    }
    m_pTreeBottom->Thaw();
    return true;
}

wxTreeItemId WorkspaceBrowserBuilder::AddNodeIfNotThere(wxTreeCtrl* tree, wxTreeItemId parent, const wxString& name, int imgIndex, TreeDataF* data, bool sorted)
{
    SpecialFolder new_type = data->m_SpecialFolder;

    wxTreeItemIdValue cookie = 0;

    wxTreeItemId insert_after; // node to insert after; we 'll be looping all children so we might as well sort at the same time
    wxTreeItemId existing = tree->GetFirstChild(parent, cookie);
    while (existing.IsOk())
    {
        wxString itemText = tree->GetItemText(existing);
        if (itemText.IsSameAs(name))
        {
            if (tree->GetItemImage(existing) == imgIndex)
            {
                tree->SetItemImage(existing, imgIndex, wxTreeItemIcon_Normal);
                tree->SetItemImage(existing, imgIndex, wxTreeItemIcon_Selected);
                delete tree->GetItemData(existing); // make Valgrind happy
                tree->SetItemData(existing, data);

                return existing;
            }
        }

        if (sorted)
        {
            TreeDataF* existing_data = (TreeDataF*)tree->GetItemData(existing);
            if (existing_data)
            {
                SpecialFolder existing_type = existing_data->m_SpecialFolder;

                // first go special folders
                if ((existing_type & (sfGFuncs | sfOthers)) &&
                    !(new_type & (sfGFuncs | sfOthers)))
                {
                    insert_after = existing;
                }
                // then everything else, alphabetically
                else if (name.CmpNoCase(itemText) >= 0)
                {
                    insert_after = existing;
                }
                else // name.CmpNoCase(itemText) < 0
                {
                    break;
                }
            }
        }
        existing = tree->GetNextChild(parent, cookie);
    }

    if (sorted)
        existing = tree->InsertItem(parent, insert_after, name, imgIndex, imgIndex, data);
    else
        existing = tree->AppendItem(parent, name, imgIndex, imgIndex, data);
    return existing;
}

void WorkspaceBrowserBuilder::CreateSpecialFolders()
{
    wxTreeItemId parent = m_pTreeTop->GetRootItem();
    wxTreeItemId gfuncs = AddNodeIfNotThere(m_pTreeTop, parent, _("Global procedures"), m_ImgNr["function_folder"], new TreeDataF(sfGFuncs, 0));
    wxTreeItemId others = AddNodeIfNotThere(m_pTreeTop, parent, _("Others"), m_ImgNr["others_folder"], new TreeDataF(sfOthers, 0));

    if (!m_Options.visibleBottomTree)
    {
        if (HasGlobalFunctionsOthers(tkFunction | tkProgram | tkSubroutine))
            m_pTreeTop->SetItemHasChildren(gfuncs);
        if (HasGlobalFunctionsOthers(tkPreprocessor | tkInterface | tkBlockData) ||
            (m_Options.showIncludeSeparately && m_pParser->HasIncludeFiles()))
            m_pTreeTop->SetItemHasChildren(others);
    }
}

void WorkspaceBrowserBuilder::ExpandTop()
{
    if (Manager::IsAppShuttingDown())
        return;

    CreateSpecialFolders();
    wxTreeItemId root = m_pTreeTop->GetRootItem();
    AddTreeChildren(m_pTreeTop, root, tkModule | tkSubmodule);
}

void WorkspaceBrowserBuilder::ExpandTopNode(wxTreeItemId node)
{
    if (Manager::IsAppShuttingDown() || (!(node.IsOk())) || (node == m_pTreeTop->GetRootItem()))
        return;

    m_pTreeTop->Freeze();
    TreeDataF* data = (TreeDataF*)m_pTreeTop->GetItemData(node);
    if (data)
    {
        wxString disName;
        switch (data->m_SpecialFolder)
        {
            case sfGFuncs:
            {
                AddTreeChildren(m_pTreeTop, node, tkFunction | tkProgram | tkSubroutine);
                break;
            }
            case sfOthers:
            {
                AddTreeChildren(m_pTreeTop, node, tkPreprocessor | tkInterface | tkBlockData);
                if (m_Options.showIncludeSeparately)
                    AddIncludeFiles(m_pTreeTop, node);
                break;
            }
            case sfToken:
            {
                TokenF* pToken = data->m_pToken;
                AddChildrenNodes(m_pTreeTop, node, pToken, tkFunction | tkSubroutine | tkInterface | tkType | tkVariable |
                                 tkProcedure | tkAccessList | tkInterfaceExplicit);
                break;
            }
            default: break;
        }
        disName = m_pTreeTop->GetItemText(node);
        if (m_ExpandedNodes.Index(disName) == wxNOT_FOUND)
            m_ExpandedNodes.Add(disName);
    }
    m_pTreeTop->Thaw();
}

void WorkspaceBrowserBuilder::CollapsTopNode(wxTreeItemId node)
{
    if (Manager::IsAppShuttingDown() || (!(node.IsOk())) || (node == m_pTreeTop->GetRootItem()))
        return;

    int indx = m_ExpandedNodes.Index(m_pTreeTop->GetItemText(node));
    if (indx != wxNOT_FOUND)
    {
        m_ExpandedNodes.RemoveAt(indx);
    }
}

void WorkspaceBrowserBuilder::SelectItem(TokenF* token)
{
    if (Manager::IsAppShuttingDown())
        return;

    wxTreeItemId item;
    if (token && token->m_pParent)
    {
        if (token->m_pParent->m_TokenKind == tkFile)
        {
            if (token->m_TokenKind == tkFunction)
            {
                item = FindItemByName(m_pTreeTop, _("Global procedures"));
                if (item.IsOk())
                {
                    m_pTreeTop->SelectItem(item);
                    item = FindItemByName(m_pTreeBottom, token->m_DisplayName);
                    if (item.IsOk())
                        m_pTreeBottom->SelectItem(item);
                }
            }
            else if (token->m_TokenKind == tkPreprocessor)
            {
                item = FindItemByName(m_pTreeTop, _("Preprocessor symbols"));
                if (item.IsOk())
                {
                    m_pTreeTop->SelectItem(item);
                    item = FindItemByName(m_pTreeBottom, token->m_DisplayName);
                    if (item.IsOk())
                        m_pTreeBottom->SelectItem(item);
                }
            }
            else if (token->m_TokenKind == tkModule || token->m_TokenKind == tkSubmodule)
            {
                item = FindItemByName(m_pTreeTop, token->m_DisplayName);
                if (item.IsOk())
                    m_pTreeTop->SelectItem(item);
            }
        }
        else if (token->m_pParent->m_TokenKind == tkModule || token->m_pParent->m_TokenKind == tkSubmodule)
        {
            item = FindItemByName(m_pTreeTop, token->m_pParent->m_DisplayName);
            if (item.IsOk())
            {
                m_pTreeTop->SelectItem(item);
                item = FindItemByName(m_pTreeBottom, token->m_DisplayName);
                if (item.IsOk())
                    m_pTreeBottom->SelectItem(item);
            }
        }
    }
}

wxTreeItemId WorkspaceBrowserBuilder::FindItemByName(wxTreeCtrl* tree, wxString name, wxString name2)
{
    bool foundFirst = false;
    wxTreeItemId firstItem;

    wxTreeItemIdValue cookie;
    wxTreeItemId root = tree->GetRootItem();
    if (!root.IsOk())
        return root;
    wxTreeItemId item = tree->GetFirstChild(root, cookie);
    while (item.IsOk())
    {
        if (tree->GetItemText(item).IsSameAs(name))
        {
            if (name2.IsEmpty())
                return item;
            else
            {
                firstItem = item;
                foundFirst = true;
                break;
            }
        }
        else if(name2.IsEmpty())
        {
            wxTreeItemIdValue cookie2;
            wxTreeItemId item2 = tree->GetFirstChild(item, cookie2);
            while (item2.IsOk())
            {
                if (tree->GetItemText(item2).IsSameAs(name))
                {
                    return item2;
                }
                item2 = tree->GetNextChild(item, cookie2);
            }
        }
        item = tree->GetNextChild(root, cookie);
    }
    if (!name2.IsEmpty() && foundFirst)
    {
        wxTreeItemIdValue cookie3;
        wxTreeItemId item2 = tree->GetFirstChild(firstItem, cookie3);
        while (item2.IsOk())
        {
            if (tree->GetItemText(item2).IsSameAs(name2))
            {
                return item2;
            }
            item2 = tree->GetNextChild(item, cookie3);
        }
        return firstItem;
    }
    item.Unset();
	return item;
}

int WorkspaceBrowserBuilder::GetTokenKindImageIdx(TokenF* token)
{
    if (!token)
        return m_ImgNr["none"];

    switch (token->m_TokenKind)
    {
        case tkUse: return m_ImgNr["use"];

        case tkModule: return m_ImgNr["module"];

        case tkSubroutine:
            {
                if (token->m_TokenAccess == taPrivate)
                    return m_ImgNr["subroutine_private"];
                else
                    return m_ImgNr["subroutine"];
            }
        case tkFunction:
            {
                if (token->m_TokenAccess == taPrivate)
                    return m_ImgNr["function_private"];
                else
                    return m_ImgNr["function"];
            }
        case tkProgram: return m_ImgNr["program"];

        case tkType:
            {
                if (token->m_TokenAccess == taPrivate)
                {
                    if (token->m_IsAbstract)
                        return m_ImgNr["type_abstract_private"];
                    else
                        return m_ImgNr["type_private"];
                }
                else
                {
                    if (token->m_IsAbstract)
                        return m_ImgNr["type_abstract"];
                    else
                        return m_ImgNr["type"];
                }
            }
        case tkInterface:
            {
                if (token->m_TypeDefinition.IsSameAs(_T("subroutine")))
                {
                    if (token->m_TokenAccess == taPrivate)
                        return m_ImgNr["interface_sub_gen_private"];
                    else
                        return m_ImgNr["interface_sub_gen"];
                }
                else if (token->m_TypeDefinition.IsSameAs(_T("function")))
                {
                    if (token->m_TokenAccess == taPrivate)
                        return m_ImgNr["interface_fun_gen_private"];
                    else
                        return m_ImgNr["interface_fun_gen"];
                }
                else
                {
                    if (token->m_TokenAccess == taPrivate)
                        return m_ImgNr["interface_private"];
                    else
                        return m_ImgNr["interface"];
                }
            }
        case tkInterfaceExplicit:
            {
                if (token->m_TokenAccess == taPrivate)
                    return m_ImgNr["interface_private"];
                else
                    return m_ImgNr["interface"];
            }

        case tkCommonblock: return m_ImgNr["none"];

        case tkPreprocessor: return m_ImgNr["preproc"];

        case tkFile: return m_ImgNr["none"];

        case tkVariable:
            {
                if (token->m_TokenAccess == taPrivate)
                    return m_ImgNr["variable_private"];
                else if (token->m_TokenAccess == taProtected)
                    return m_ImgNr["variable_protected"];
                else
                    return m_ImgNr["variable"];
            }

        //case tkInterfaceFunction: return m_ImgNr["interface_function"];

        //case tkInterfaceSubroutine: return m_ImgNr["interface_subroutine"];

        case tkProcedure:
            {
                if (token->m_TypeDefinition.IsSameAs(_T("subroutine")))
                {
                    if (token->m_TokenAccess == taPrivate)
                        return m_ImgNr["subroutine_private"];
                    else
                        return m_ImgNr["subroutine"];
                }
                else if (token->m_TypeDefinition.IsSameAs(_T("function")))
                {
                    if (token->m_TokenAccess == taPrivate)
                        return m_ImgNr["function_private"];
                    else
                        return m_ImgNr["function"];
                }
                else
                {
                    if (token->m_TokenAccess == taPrivate)
                        return m_ImgNr["procedure_private"];
                    else
                        return m_ImgNr["procedure"];
                }
            }

        case tkAccessList:
            {
                if (token->m_TokenAccess == taPrivate)
                    return m_ImgNr["access_list_private"];
                else if (token->m_TokenAccess == taProtected)
                    return m_ImgNr["access_list_protected"];
                else
                    return m_ImgNr["access_list_public"];
            }

        case tkSubmodule: return m_ImgNr["submodule"];

        case tkProcedureFinal: return m_ImgNr["procedure_final"];

        default: return m_ImgNr["none"];
    }
}

wxImageList* WorkspaceBrowserBuilder::GetImageList()
{
    return m_pImlist;
}

void WorkspaceBrowserBuilder::MarkSymbol(const wxString& filename, int line)
{
    if (Manager::IsAppShuttingDown() || m_AtWork)
        return;

    bool found = false;
    bool unmarked = true;
    wxTreeItemIdValue cookie;
    wxTreeItemId root = m_pTreeTop->GetRootItem();
    if(!root.IsOk())
        return;
    wxTreeItemId item = m_pTreeTop->GetFirstChild(root, cookie);
    wxTreeItemId itemGlob;
    bool haveGlob = false;
    wxTreeItemId itemOthers;
    bool haveOthers = false;
    while (item.IsOk())
    {
        TreeDataF* data = (TreeDataF*)m_pTreeTop->GetItemData(item);
        if (data)
        {
            switch (data->m_SpecialFolder)
            {
                case sfGFuncs:
                {
                    itemGlob = item;
                    haveGlob = true;
                    break;
                }
                case sfOthers:
                {
                    itemOthers = item;
                    haveOthers = true;
                    break;
                }
                case sfToken:
                {
                    if (m_pTreeTop->IsBold(item))
                    {
                        if (!data->m_pToken->m_Filename.IsSameAs(filename)
                            || ((int)data->m_pToken->m_LineStart > line)
                            || ((int)data->m_pToken->m_LineEnd < line))
                        {
                            MarkItem(m_pTreeTop, item, false);
                            if (!m_Options.visibleBottomTree && m_pTreeTop->HasChildren(item))
                            {
                                MarkChildSymbol(m_pTreeTop, item, line, false);
                            }
                            unmarked = true;
                        }
                        else
                            unmarked = false;
                    }
                    if (!found)
                    {
                        if (data->m_pToken->m_Filename.IsSameAs(filename))
                        {
                            if (((int)data->m_pToken->m_LineStart <= line) && ((int)data->m_pToken->m_LineEnd >= line))
                            {
                                if (unmarked)
                                    MarkItem(m_pTreeTop, item);
                                if ((m_pTreeTop->GetSelection() == item) && m_Options.visibleBottomTree)
                                {
                                    MarkBottomSymbol(filename, line);
                                }
                                else if (m_Options.visibleBottomTree)
                                {
                                    UnmarkBottomSymbol();
                                }
                                else if (!m_Options.visibleBottomTree && m_pTreeTop->HasChildren(item))
                                {
                                    MarkChildSymbol(m_pTreeTop, item, line);
                                }
                                found = true;
                            }
                        }
                    }
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
        item = m_pTreeTop->GetNextChild(root, cookie);
    }

    if (haveGlob && found)
    {
        if (m_Options.visibleBottomTree && (m_pTreeTop->GetSelection() == itemGlob))
        {
            UnmarkBottomSymbol();
        }
        else if (!m_Options.visibleBottomTree && m_pTreeTop->HasChildren(itemGlob) &&  m_pTreeTop->GetLastChild(itemGlob).IsOk())
        {
            MarkChildSymbol(m_pTreeTop, itemGlob, line, false);
        }
        if (m_pTreeTop->IsBold(itemGlob))
            MarkItem(m_pTreeTop, itemGlob, false);
    }
    else if (haveGlob)
    {
        bool foundGlob = false;
        if (m_Options.visibleBottomTree && (m_pTreeTop->GetSelection() == itemGlob))
        {
            foundGlob = MarkBottomSymbol(filename, line);
        }
        else if (!m_Options.visibleBottomTree && m_pTreeTop->HasChildren(itemGlob) &&  m_pTreeTop->GetLastChild(itemGlob).IsOk())
        {
            foundGlob = MarkGlobalSymbol(m_pTreeTop, itemGlob, filename, line);
        }
        else
        {
            foundGlob = IsLineInGlobals(filename, line);
            if (m_Options.visibleBottomTree && foundGlob && (m_pTreeTop->GetSelection() != itemGlob))
            {
                UnmarkBottomSymbol();
            }
        }
        if (foundGlob)
        {
            MarkItem(m_pTreeTop, itemGlob);
            found = true;
        }
        else if (m_pTreeTop->IsBold(itemGlob))
        {
            MarkItem(m_pTreeTop, itemGlob, false);
        }
    }

    if (haveOthers && found)
    {
        if (m_Options.visibleBottomTree && (m_pTreeTop->GetSelection() == itemOthers))
        {
            UnmarkBottomSymbol();
        }
        else if (!m_Options.visibleBottomTree && m_pTreeTop->HasChildren(itemOthers) &&  m_pTreeTop->GetLastChild(itemOthers).IsOk())
        {
            MarkChildSymbol(m_pTreeTop, itemOthers, line, false);
            MarkGlobalSymbol(m_pTreeTop, itemOthers, filename, line);
        }
        if (m_pTreeTop->IsBold(itemOthers))
            MarkItem(m_pTreeTop, itemOthers, false);
    }
    else if (haveOthers)
    {
        bool foundOthers = false;
        if (m_Options.visibleBottomTree && (m_pTreeTop->GetSelection() == itemOthers))
        {
            foundOthers = MarkBottomSymbol(filename, line);
        }
        else if (!m_Options.visibleBottomTree && m_pTreeTop->HasChildren(itemOthers) &&  m_pTreeTop->GetLastChild(itemOthers).IsOk())
        {
            foundOthers = MarkGlobalSymbol(m_pTreeTop, itemOthers, filename, line);
        }
        else
        {
            foundOthers = (m_Options.showIncludeSeparately && m_pParser->IsIncludeFile(filename));
            if (m_Options.visibleBottomTree && foundOthers && (m_pTreeTop->GetSelection() != itemOthers))
            {
                UnmarkBottomSymbol();
            }
        }
        if (foundOthers)
        {
            MarkItem(m_pTreeTop, itemOthers);
            found = true;
        }
        else if (m_pTreeTop->IsBold(itemOthers))
        {
            MarkItem(m_pTreeTop, itemOthers, false);
        }
    }

    if (!found && m_Options.visibleBottomTree)
    {
        UnmarkBottomSymbol();
    }
}

void WorkspaceBrowserBuilder::MarkItem(wxTreeCtrl* tree, wxTreeItemId& item, bool mark)
{
    if (item.IsOk())
    {
        tree->SetItemBold(item, mark);
#ifdef __WXGTK__
        tree->Refresh();
#endif
    }
}

bool WorkspaceBrowserBuilder::MarkBottomSymbol(const wxString& filename, int line)
{
    bool found = false;
    bool foundFile = false;
    bool unmarked = true;
    wxTreeItemIdValue cookie;
    wxTreeItemId root = m_pTreeBottom->GetRootItem();
    if (!root.IsOk())
        return false;
    wxTreeItemId item = m_pTreeBottom->GetFirstChild(root, cookie);
    while (item.IsOk())
    {
        bool goInside = false;
        TreeDataF* data = (TreeDataF*)m_pTreeBottom->GetItemData(item);
        if (data)
        {
            if (data->m_SpecialFolder == sfToken)
            {
                if (m_pTreeBottom->IsBold(item))
                {
                    if (!data->m_pToken->m_Filename.IsSameAs(filename)
                        || (int)data->m_pToken->m_LineStart > line
                        || (int)data->m_pToken->m_LineEnd < line)
                    {
                        MarkItem(m_pTreeBottom, item, false);
                        unmarked = true;
                    }
                    else
                        unmarked = false;
                }
                if (!found)
                {
                    if (data->m_pToken->m_Filename.IsSameAs(filename))
                    {
                        if (((int)data->m_pToken->m_LineStart <= line) && ((int)data->m_pToken->m_LineEnd >= line))
                        {
                            if (unmarked)
                                MarkItem(m_pTreeBottom, item);
                            found = true;
                        }
                    }
                }
            }
            else if(data->m_SpecialFolder == sfFile)
            {
                if (data->m_pToken->m_Filename.IsSameAs(filename))
                {
                    MarkItem(m_pTreeBottom, item);
                    goInside = true;
                    foundFile = true;
                }
                else
                    MarkItem(m_pTreeBottom, item, false);
            }
        }
        else
            goInside = true;

        if (goInside)
        {
            bool unmarked2 = true;
            wxTreeItemIdValue cookie2;
            wxTreeItemId item2 = m_pTreeBottom->GetFirstChild(item, cookie2);
            while (item2.IsOk())
            {
                TreeDataF* data2 = (TreeDataF*)m_pTreeBottom->GetItemData(item2);
                if (data2)
                {
                    if (data2->m_SpecialFolder == sfToken)
                    {
                        if (m_pTreeBottom->IsBold(item2))
                        {
                            if (!data2->m_pToken->m_Filename.IsSameAs(filename)
                                || (int)data2->m_pToken->m_LineStart > line
                                || (int)data2->m_pToken->m_LineEnd < line)
                            {
                                MarkItem(m_pTreeBottom, item2, false);
                                unmarked2 = true;
                            }
                            else
                                unmarked2 = false;
                        }
                        if (!found)
                        {
                            if (data2->m_pToken->m_Filename.IsSameAs(filename))
                            {
                                if (((int)data2->m_pToken->m_LineStart <= line) && ((int)data2->m_pToken->m_LineEnd >= line))
                                {
                                    if (unmarked2)
                                        MarkItem(m_pTreeBottom, item2);
                                    found = true;
                                }
                            }
                        }
                    }
                }
                item2 = m_pTreeBottom->GetNextChild(item, cookie2);
            }
        }
        item = m_pTreeBottom->GetNextChild(root, cookie);
    }
    return (found || foundFile);
}


void WorkspaceBrowserBuilder::UnmarkBottomSymbol()
{
    bool found = false;
    bool goInside = false;
    wxTreeItemIdValue cookie;
    wxTreeItemId root = m_pTreeBottom->GetRootItem();
    if (!root.IsOk())
        return;
    wxTreeItemId item = m_pTreeBottom->GetFirstChild(root, cookie);
    while (item.IsOk())
    {
        TreeDataF* data = (TreeDataF*)m_pTreeBottom->GetItemData(item);
        if (data)
        {
            if (m_pTreeBottom->IsBold(item))
            {
                MarkItem(m_pTreeBottom, item, false);
                found = true;
                goInside = true;
            }
        }
        else
            goInside = true;

        if (goInside)
        {
            wxTreeItemIdValue cookie2;
            wxTreeItemId item2 = m_pTreeBottom->GetFirstChild(item, cookie2);
            while (item2.IsOk())
            {
                TreeDataF* data2 = (TreeDataF*)m_pTreeBottom->GetItemData(item2);
                if (data2)
                {
                    if (data2->m_SpecialFolder == sfToken)
                    {
                        if (m_pTreeBottom->IsBold(item2))
                        {
                            MarkItem(m_pTreeBottom, item2, false);
                            found = true;
                            break;
                        }
                    }
                }
                item2 = m_pTreeBottom->GetNextChild(item, cookie2);
            }
        }
        if (found)
            break;
        item = m_pTreeBottom->GetNextChild(root, cookie);
    }
}


void WorkspaceBrowserBuilder::MarkChildSymbol(wxTreeCtrl* tree, wxTreeItemId& root, int line, bool mark)
{
    bool found = false;
    bool unmarked = true;
    wxTreeItemIdValue cookie;
    if (!root.IsOk())
        return;
    wxTreeItemId item = tree->GetFirstChild(root, cookie);
    while (item.IsOk())
    {
        TreeDataF* data = (TreeDataF*)tree->GetItemData(item);
        if (data)
        {
            if (data->m_SpecialFolder == sfToken)
            {
                if (tree->IsBold(item))
                {
                    if (mark)
                    {
                        if (((int)data->m_pToken->m_LineStart > line) || ((int)data->m_pToken->m_LineEnd < line))
                        {
                            MarkItem(tree, item, false);
                            unmarked = true;
                        }
                        else
                            unmarked = false;
                    }
                    else
                        MarkItem(tree, item, false);
                }
                if (!found && mark)
                {
                    if (((int)data->m_pToken->m_LineStart <= line) && ((int)data->m_pToken->m_LineEnd >= line))
                    {
                        if (unmarked)
                            MarkItem(tree, item);
                        found = true;
                    }
                }
            }
            else if (data->m_SpecialFolder == sfFile)
            {
                if ((tree->IsBold(item) && !mark) || (!tree->IsBold(item) && mark))
                    MarkItem(tree, item, mark);
                MarkChildSymbol(tree, item, line, mark);
            }
        }
        item = tree->GetNextChild(root, cookie);
    }
}

bool WorkspaceBrowserBuilder::MarkGlobalSymbol(wxTreeCtrl* tree, wxTreeItemId& root, const wxString& filename, int line)
{
    bool found = false;
    bool foundFile  = false;
    wxTreeItemIdValue cookie;
    if (!root.IsOk())
        return false;
    wxTreeItemId item = tree->GetFirstChild(root, cookie);
    while (item.IsOk())
    {
        TreeDataF* data = (TreeDataF*)tree->GetItemData(item);
        if (data)
        {
            if (data->m_SpecialFolder == sfToken)
            {
                if (tree->IsBold(item))
                {
                    MarkItem(tree, item, false);
                }
                if (!found)
                {
                    if (data->m_pToken->m_Filename.IsSameAs(filename))
                    {
                        if (((int)data->m_pToken->m_LineStart <= line) && ((int)data->m_pToken->m_LineEnd >= line))
                        {
                            MarkItem(tree, item);
                            found = true;
                        }
                    }
                }
            }
            else if (data->m_SpecialFolder == sfFile)
            {
                bool isSameFile = data->m_pToken->m_Filename.IsSameAs(filename);
                if (isSameFile)
                {
                    MarkItem(tree, item);
                    foundFile = true;
                }
                else
                    MarkItem(tree, item, false);
                wxTreeItemIdValue cookie2;
                wxTreeItemId item2 = tree->GetFirstChild(item, cookie2);

                while (item2.IsOk())
                {
                    TreeDataF* data2 = (TreeDataF*)tree->GetItemData(item2);
                    if (data2)
                    {
                        if (data2->m_SpecialFolder == sfToken)
                        {
                            if (tree->IsBold(item2))
                            {
                                MarkItem(tree, item2, false);
                            }
                            if (!found && isSameFile)
                            {
                                if (((int)data2->m_pToken->m_LineStart <= line) && ((int)data2->m_pToken->m_LineEnd >= line))
                                {
                                    MarkItem(tree, item2);
                                    found = true;
                                }
                            }
                        }
                    }
                    item2 = tree->GetNextChild(item, cookie2);
                }
            }
        }
        item = tree->GetNextChild(root, cookie);
    }
    return (found || foundFile);
}


bool WorkspaceBrowserBuilder::IsLineInGlobals(const wxString& file, int line)
{
    if (m_Options.showIncludeSeparately && m_pParser->IsIncludeFile(file))
        return false;

    int tokenKindMask = tkFunction | tkProgram | tkSubroutine;
    TokensArrayF* pTokens = m_pParser->GetTokens();
    bool found = false;
    bool foundFileToken = false;
    for (size_t i=0; i < pTokens->GetCount(); ++i)
    {
        TokenF* token = pTokens->Item(i);

        if (token->m_TokenKind == tkFile && token->m_Filename.IsSameAs(file))
        {
            switch (m_Options.displayFilter)
            {
                case bdfFile:
                {
                    foundFileToken = true;
                    break;
                }
                case bdfProject:
                {
                    for (FilesList::iterator it = m_pActiveProject->GetFilesList().begin(); it != m_pActiveProject->GetFilesList().end(); ++it)
                    {
                        ProjectFile* pf = *it;
                        foundFileToken = UnixFilename(pf->file.GetFullPath()).IsSameAs(file);
                        if(foundFileToken)
                            break;
                    }
                    break;
                }
                default: // bdfWorkspace
                {
                    foundFileToken = true;
                    break;
                }
            }
            if (foundFileToken)
            {
                TokensArrayF* children = &token->m_Children;
                for (size_t j=0; j < children->GetCount(); ++j)
                {
                    TokenF* childToken = children->Item(j);
                    if (childToken->m_TokenKind & tokenKindMask)
                    {
                        if ( ((int)childToken->m_LineStart <= line) && ((int)childToken->m_LineEnd >= line) )
                        {
                            found = true;
                            break;
                        }
                    }
                }
            }
            break;
        }
    }
    return found;
}


void WorkspaceBrowserBuilder::MakeVisibleCurrent()
{
    if (Manager::IsAppShuttingDown() || m_AtWork)
        return;

    wxTreeItemIdValue cookie;
    wxTreeItemId root = m_pTreeTop->GetRootItem();
    if (!root.IsOk())
        return;
    wxTreeItemId item = m_pTreeTop->GetFirstChild(root, cookie);
    while (item.IsOk())
    {
        if (m_pTreeTop->IsBold(item))
        {
            m_pTreeTop->SelectItem(item);
            m_pTreeTop->EnsureVisible(item);
            break;
        }
        item = m_pTreeTop->GetNextChild(root, cookie);
    }

    if (m_Options.visibleBottomTree)
    {
        root = m_pTreeBottom->GetRootItem();
        if (!root.IsOk())
            return;
        item = m_pTreeBottom->GetFirstChild(root, cookie);
        bool found = false;
        while (item.IsOk())
        {
            if (m_pTreeBottom->IsBold(item))
            {
                m_pTreeBottom->SelectItem(item);
                m_pTreeBottom->EnsureVisible(item);
                break;
            }
            else if (m_pTreeBottom->HasChildren(item))
            {
                wxTreeItemIdValue cookie2;
                wxTreeItemId item2 = m_pTreeBottom->GetFirstChild(item, cookie2);
                while (item2.IsOk())
                {
                    if (m_pTreeBottom->IsBold(item2))
                    {
                        m_pTreeBottom->SelectItem(item2);
                        m_pTreeBottom->EnsureVisible(item2);
                        found = true;
                        break;
                    }
                    item2 = m_pTreeBottom->GetNextChild(item, cookie2);
                }
                if (found)
                    break;
            }
            item = m_pTreeBottom->GetNextChild(root, cookie);
        }
    }
}

void WorkspaceBrowserBuilder::AddIncludeFiles(wxTreeCtrl* tree, wxTreeItemId parent)
{
    if (Manager::IsAppShuttingDown())
        return;

    int tokenKindMask = tkModule | tkFunction | tkProgram | tkSubroutine | tkInterface | tkInterfaceExplicit | tkBlockData |
                    tkType | tkVariable | tkProcedure | tkAccessList | tkCommonblock | tkSubmodule;

    bool sorted = m_Options.sortAlphabetically;
    switch (m_Options.displayFilter)
    {
        case bdfFile:
        {
            if (m_pParser->IsIncludeFile(m_ActiveFilename))
            {
                TokenF* fileToken= m_pParser->FindFile(m_ActiveFilename);
                if (fileToken)
                {
                    wxFileName fn(m_ActiveFilename);
                    wxString tn = _("include '");
                    tn << fn.GetFullName() << _("'");
                    wxTreeItemId idni = AddNodeIfNotThere(tree, parent, tn, m_ImgNr["symbols_folder"], new TreeDataF(sfFile, fileToken), sorted);
                    AddFileNodes(tree, idni, UnixFilename(m_ActiveFilename), tokenKindMask);
                }
            }
            break;
        }
        case bdfProject:
        {
            for (FilesList::iterator it = m_pActiveProject->GetFilesList().begin(); it != m_pActiveProject->GetFilesList().end(); ++it)
            {
                ProjectFile* pf = *it;
                if (m_pParser->IsIncludeFile(pf->file.GetFullPath()))
                {
                    TokenF* fileToken= m_pParser->FindFile(pf->file.GetFullPath());
                    if (fileToken)
                    {
                        wxString tn = _("include '");
                        tn << pf->file.GetFullName() << _("'");
                        wxTreeItemId idni = AddNodeIfNotThere(tree, parent, tn, m_ImgNr["symbols_folder"], new TreeDataF(sfFile, fileToken), sorted);
                        AddFileNodes(tree, idni, UnixFilename(pf->file.GetFullPath()), tokenKindMask);
                    }
                }
            }
            break;
        }
        case bdfWorkspace:
        {
            TokensArrayF* pTokens = m_pParser->GetTokens();
            for (size_t i=0; i< pTokens->GetCount(); ++i)
            {
                TokenF* token = pTokens->Item(i);
                if (token->m_TokenKind == tkFile &&
                    m_pParser->IsIncludeFile(token->m_Filename))
                {
                    wxString tn = _("include '");
                    tn << token->m_DisplayName << _("'");
                    wxTreeItemId idni = AddNodeIfNotThere(tree, parent, tn, m_ImgNr["symbols_folder"], new TreeDataF(sfFile, token), sorted);
                    AddChildrenNodes(tree, idni, token, tokenKindMask);
                }
            }
            break;
        }
    }
}

void WorkspaceBrowserBuilder::SetActiveProject(cbProject* prj)
{
    m_pActiveProject = prj;
}

