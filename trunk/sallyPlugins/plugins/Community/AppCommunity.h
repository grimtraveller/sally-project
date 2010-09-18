////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file	Community\AppCommunity.h
///
/// \brief	Declares the application community class. 
///
/// \author	Christian Knobloch
/// \date	13.09.2010
///
/// This file is part of the Sally Project
/// 
/// Copyright(c) 2008-2010 Sally Project
/// http://www.sally-project.de/
///
/// This program is free software: you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
/// 
/// This program is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
/// GNU General Public License for more details.
/// 
/// You should have received a copy of the GNU General Public License
/// along with this program. If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <sallyAPI\sallyAPI.h>
#include <xmlParser.h>

#include "Define.h"
#include "ControlGroup.h"

#pragma comment(lib, "xmlparser.lib")

class CAppCommunity :
	public SallyAPI::GUI::CApplicationWindow
{
private:
	SallyAPI::GUI::CImageBox*				m_pApplicationImage;
	SallyAPI::GUI::CLabel*					m_pWelcome;
	SallyAPI::GUI::CLabel*					m_pNewsInfo;
	SallyAPI::GUI::CLabelBox*				m_pNewsMessage;
	std::vector<CControlGroup*>				m_vControlGroup;
	int										m_iShowCount;
	int										m_iShowRows;
	int										m_iShowCols;
	std::map<std::string, SallyAPI::GUI::CPicture*>	m_pPictures;

	void	OnCommandUpdateStatus();
	void	OnCommandGetNews();
	void	DeleteOldImages();
	void	OnCommandUpdateView();
public:
	CAppCommunity(SallyAPI::GUI::CGUIBaseObject* parent, int graphicId, const std::string& pluginPath);
	virtual ~CAppCommunity();

	virtual void SendMessageToParent(SallyAPI::GUI::CGUIBaseObject* reporter, int reporterId, int iMessageID, SallyAPI::GUI::SendMessage::CParameterBase* messageParameter = NULL);
	virtual void Visible(bool visible);
};
