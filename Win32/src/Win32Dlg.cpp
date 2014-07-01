//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif

#include "modassert/logger.hpp"
#include "modassert/info.hpp"
#include "modassert/infostore.hpp"
#include "modassert/properties.hpp"
#include "modassert/result.hpp"
#include "modassert/handler.hpp"
#include "modassert/Win32Dlg.hpp"
#include "modassert/Win32Displayer.hpp"
#include "modassert/resource.h"

#include "commctrl.h"

// There is a windows header file that defines the macro GetMessage
// to GetMessageA or GetMessageW. Since we use the method GetMessage
// in our own ParameterList class, we need to undefine this macro:
#undef GetMessage

namespace ModAssert
{
    int idOptionalAction = 0, idGlobalOptionalAction = 0;

	const Data *s_data = 0;

	BOOL CALLBACK ModAssertDlg(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_INITDIALOG:
			{
				s_data = (const Data*)lParam;
				const Properties *properties = s_data->properties;
				const Result *result = s_data->result;
				const InfoProviders::InfoUser *infoUser = s_data->infoUser;

				SetDlgItemText(hDlg, IDC_MOD_ASSERT_CONTEXT,
					RichBool::ToString(properties->GetContext()).c_str());

				if (result->GetAnalysis())
				{
					// set font for analysis
					HFONT hFont = CreateFont(
						0, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
						DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
						DEFAULT_QUALITY, FIXED_PITCH|FF_MODERN, "courier");
					SendDlgItemMessage(hDlg, IDC_MOD_ASSERT_ANALYSIS,
						WM_SETFONT, (WPARAM)hFont, 0);

					// show the analysis
					std::string str = RichBool::ToString(*result->GetAnalysis());
					SetDlgItemText(hDlg, IDC_MOD_ASSERT_ANALYSIS,
						str.c_str());
				}

				const char *category = properties->GetCategory()->GetName();

				std::string str = "Stop displaying ";
				str += category;
				SetDlgItemText(hDlg, IDC_MOD_ASSERT_STOP_DISPLAYING, str.c_str());

				if (properties->CanStopDisplayingThis())
				{
					str = "This ";
					str += category;
					SetDlgItemText(hDlg, IDC_MOD_ASSERT_KEEP_IGNORING_THIS, str.c_str());
				}
				else
				{
					HWND hWnd = GetDlgItem(hDlg, IDC_MOD_ASSERT_KEEP_IGNORING_THIS);
					ShowWindow(hWnd, FALSE);
				}

				str = "All ";
				str += category;
				str += "s";
				SetDlgItemText(hDlg, IDC_MOD_ASSERT_KEEP_IGNORING_ALL, str.c_str());

				// show the condition
				if (!properties->IsUnconditional())
				{
					std::string cond = category;
					if (properties->GetCondition())
					{
						cond += " ";
						cond += properties->GetCondition();
					}
					cond += result->Succeeded() ? " succeeded" : " failed";
					if (!properties->GetCondition())
						cond += " (no condition text available)";
					SetDlgItemText(hDlg, IDC_MOD_ASSERT_DESCRIPTION, cond.c_str());
				}
				else
				{
					std::string cond = "unconditional ";
					cond += category;
					cond += " failed";
					SetDlgItemText(hDlg, IDC_MOD_ASSERT_DESCRIPTION, cond.c_str());
				}

				// create the listview
				HWND hListView = GetDlgItem(hDlg, IDC_MOD_ASSERT_EXPRESSIONS_AND_MESSAGES);
				LVCOLUMN column;

				column.mask = LVCF_TEXT|LVCF_WIDTH;
				column.cx = 200;
				column.pszText = "Expression";
				ListView_InsertColumn(hListView, 0, (LPARAM)&column);

				column.mask = LVCF_TEXT|LVCF_WIDTH;
				column.cx = 285;
				column.pszText = "Value";
				ListView_InsertColumn(hListView, 1, (LPARAM)&column);

				if (result->GetParameterList())
				{
					int idx = 0;
					for (const ParameterList::Message *message=result->GetParameterList()->GetFirst();
						message; message = message->GetNext(), ++idx)
					{
						LVITEM itemExpr;
						itemExpr.mask = LVIF_TEXT;
						itemExpr.iItem = idx;
						itemExpr.iSubItem = 0;
						std::string strMessage = message->GetMessage();
						if (message->GetType()==ParameterList::eMessage)
						{
							itemExpr.pszText = "message";
							ListView_InsertItem(hListView, &itemExpr);
							ListView_SetItemText(hListView, idx, 1, &strMessage[0]);
						}
						else if (message->GetType()==ParameterList::eValue)
						{
							const ParameterList::Value *value =
								(const ParameterList::Value*)message;

							itemExpr.pszText = &strMessage[0];
							ListView_InsertItem(hListView, &itemExpr);
							std::string strValue = value->GetValue();
							ListView_SetItemText(hListView, idx, 1, &strValue[0]);
						}
					}
				}

				// show the extra information
				std::string allInfo = ModAssert::GetAllInfo(
					*properties, *result, *infoUser,
					"\r\n");
				SetDlgItemText(hDlg, IDC_MOD_ASSERT_INFO,
					allInfo.c_str());

				// set text for some checkboxes
				for (unsigned int group=0; (group<properties->GetGroupList()->GetSize()) && (group<4u); ++group)
				{
					SetDlgItemText(hDlg, IDC_MOD_ASSERT_KEEP_IGNORING_CUSTOM_1+group,
						properties->GetGroupList()->GetName(group).c_str());
				}

				//disable unnecessary checkboxes
				for (size_t disable=properties->GetGroupList()->GetSize(); disable<4u; ++disable)
				{
					HWND hWnd = GetDlgItem(hDlg,
						IDC_MOD_ASSERT_KEEP_IGNORING_CUSTOM_1+disable);

					EnableWindow(hWnd, FALSE);
				}

				// set the text for the optional action,
				// if there is one and we're allowed to do it
				if (properties->GetOptional() && GetAllowOptional())
				{
					idOptionalAction = IDC_MOD_ASSERT_OPTIONAL_ACTION1;
					SetDlgItemText(hDlg, IDC_MOD_ASSERT_OPTIONAL_ACTION1,
						properties->GetOptional());
				}
				else
				{
					idOptionalAction = 0;
				}

				// set the text for the global optional action,
				// if there is one and we're allowed to do it
				if (GetGlobalOptionalAction() && GetAllowGlobalOptional())
				{
					idGlobalOptionalAction = (idOptionalAction==0) ?
						IDC_MOD_ASSERT_OPTIONAL_ACTION1 : IDC_MOD_ASSERT_OPTIONAL_ACTION2;
					SetDlgItemText(hDlg, idGlobalOptionalAction,
						GetGlobalOptionalActionDescription());
				}
				else
				{
					idGlobalOptionalAction = 0;
				}

				if ( (idOptionalAction==0) && (idGlobalOptionalAction==0) )
				{
					HWND hWnd = GetDlgItem(hDlg, IDC_MOD_ASSERT_OPTIONAL_ACTION1);
					ShowWindow(hWnd, FALSE);
				}

				if ( (idOptionalAction==0) || (idGlobalOptionalAction==0) )
				{
					HWND hWnd = GetDlgItem(hDlg, IDC_MOD_ASSERT_OPTIONAL_ACTION2);
					ShowWindow(hWnd, FALSE);
				}

				BOOL AllowDebug = IsDebugPossible() && GetAllowBreakIntoDebugger();
				if (!AllowDebug)
				{
					HWND hWndDebug = GetDlgItem(hDlg, IDC_MOD_ASSERT_DEBUG);
					EnableWindow(hWndDebug, FALSE);
				}

				if (!GetAllowExit())
				{
					HWND hWndExit = GetDlgItem(hDlg, IDC_MOD_ASSERT_EXIT);
					EnableWindow(hWndExit, FALSE);
				}

				// enable the optional logger if there is one
				if (GetOptionalLogger())
				{
					SetDlgItemText(hDlg, IDC_MOD_ASSERT_OPTIONAL_LOGGER,
						GetOptionalLoggerText() ? GetOptionalLoggerText() : "Optional logger");
				}
				else
				{
					HWND hWndOptionalLogger =
						GetDlgItem(hDlg, IDC_MOD_ASSERT_OPTIONAL_LOGGER);
					ShowWindow(hWndOptionalLogger, FALSE);
				}

				// set title
				str = category;
				str += result->Succeeded() ? " succeeded" : " failed";
				str[0] = (char)toupper(str[0]);
				SetWindowText(hDlg, str.c_str());

				// set icon
				LPCSTR szIcon = result->Succeeded() ?
					MAKEINTRESOURCE(IDC_MOD_ASSERT_ICON_SUCCESS) :
					MAKEINTRESOURCE(IDC_MOD_ASSERT_ICON_FAILURE);

				HICON hIcon = LoadIcon(Win32Displayer::GetInstance(),
					szIcon);
				SendMessage(hDlg, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
			}
			break;
		case WM_COMMAND:
			switch (wParam)
			{
			case IDC_MOD_ASSERT_OPTIONAL_LOGGER:
				{
					if (GetOptionalLogger())
						GetOptionalLogger()->OnAssert(*s_data->properties,
							*s_data->result);
					break;
				}
			case IDC_MOD_ASSERT_OK:
				{
					s_data = 0;

					int response = 0;

					if ((IsDlgButtonChecked(hDlg, IDC_MOD_ASSERT_DEBUG)==BST_CHECKED) && IsDebugPossible())
						response |= BreakIntoDebugger;
					if (IsDlgButtonChecked(hDlg, IDC_MOD_ASSERT_EXIT)==BST_CHECKED)
						response |= Exit;
					if (IsDlgButtonChecked(hDlg, IDC_MOD_ASSERT_KEEP_IGNORING_THIS)==BST_CHECKED)
						response |= StopDisplayingThis;
					if (IsDlgButtonChecked(hDlg, IDC_MOD_ASSERT_KEEP_IGNORING_IN_FILE)==BST_CHECKED)
						response |= StopDisplayingFile;
					if (IsDlgButtonChecked(hDlg, IDC_MOD_ASSERT_KEEP_IGNORING_ALL)==BST_CHECKED)
						response |= StopDisplayingAll;
					if (IsDlgButtonChecked(hDlg, IDC_MOD_ASSERT_KEEP_IGNORING_CUSTOM_1)==BST_CHECKED)
						response |= StopDisplayingCustom1;
					if (IsDlgButtonChecked(hDlg, IDC_MOD_ASSERT_KEEP_IGNORING_CUSTOM_2)==BST_CHECKED)
						response |= StopDisplayingCustom2;
					if (IsDlgButtonChecked(hDlg, IDC_MOD_ASSERT_KEEP_IGNORING_CUSTOM_3)==BST_CHECKED)
						response |= StopDisplayingCustom3;
					if (IsDlgButtonChecked(hDlg, IDC_MOD_ASSERT_KEEP_IGNORING_CUSTOM_4)==BST_CHECKED)
						response |= StopDisplayingCustom4;
					if ( (idOptionalAction!=0) && (IsDlgButtonChecked(hDlg, idOptionalAction)==BST_CHECKED) )
						response |= Optional;
					if ( (idGlobalOptionalAction!=0) && (IsDlgButtonChecked(hDlg, idGlobalOptionalAction)==BST_CHECKED) )
						response |= GlobalOptional;
					EndDialog(hDlg, response);

					HFONT hFont = (HFONT)SendDlgItemMessage(hDlg, IDC_MOD_ASSERT_ANALYSIS,
						WM_GETFONT, 0, 0);
					DeleteObject(hFont);
				}
				break;
			}
			break;
		case WM_QUIT:
		case WM_CLOSE:
			{
				s_data = 0;
				HFONT hFont = (HFONT)SendDlgItemMessage(hDlg, IDC_MOD_ASSERT_ANALYSIS,
					WM_GETFONT, 0, 0);
				DeleteObject(hFont);

				EndDialog(hDlg, 0); // 0 means no action
			}
			break;
		default:
			return FALSE;
		}
		return TRUE;
	}
}
