////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file	SallyConfig\LanguagesHelper.h
///
/// \brief	Declares the languages helper functions. 
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

void LoadLanguage(const std::string& languagePath)
{
	static int id = 0;
	// check version
	std::string fileInfo = languagePath;
	fileInfo.append("manifest.ini");

	std::string name = SallyAPI::System::COption::GetPropertyStringStatic("info", "name", "", fileInfo);
	std::string author = SallyAPI::System::COption::GetPropertyStringStatic("info", "author", "", fileInfo);
	std::string version = SallyAPI::System::COption::GetPropertyStringStatic("info", "version", "", fileInfo);
	std::string uid = SallyAPI::System::COption::GetPropertyStringStatic("info", "uid", "", fileInfo);

	int index = hLanguageView.AddItem(id, 0, name.c_str(), id, 0);
	hLanguageView.AddItem(index, 1, author.c_str(), id, 0);
	hLanguageView.AddItem(index, 2, version.c_str(), id, 0);
	hLanguageView.AddItem(index, 3, uid.c_str(), id, 0);

	// put to list
	languageMap[id] = languagePath;

	++id;
}

void LoadLanguages()
{
	// Add Plugins
	std::string installDir = SallyAPI::System::SystemHelper::GetModulePath();
	std::string searchPlugins = installDir;
	searchPlugins.append("languages\\*");

	HANDLE				hFolder, hDll;
	WIN32_FIND_DATA		pluginFolderInformation, pluginDllInformation;

	hFolder = FindFirstFile(searchPlugins.c_str(), &pluginFolderInformation);

	if(hFolder != INVALID_HANDLE_VALUE)
	{
		do
		{
			if ((pluginFolderInformation.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				&& (strcmp(pluginFolderInformation.cFileName, "..") != 0)
				&& (strcmp(pluginFolderInformation.cFileName, ".") != 0))
			{
				std::string pluginFolderSearch = installDir;
				pluginFolderSearch.append("languages\\");

				pluginFolderSearch.append(pluginFolderInformation.cFileName);
				pluginFolderSearch.append("\\");
				pluginFolderSearch.append("manifest.ini");
				hDll = FindFirstFile(pluginFolderSearch.c_str(), &pluginDllInformation);

				if(hDll != INVALID_HANDLE_VALUE)
				{
					do
					{
						std::string pluginFolder = installDir;
						pluginFolder.append("languages\\");
						pluginFolder.append(pluginFolderInformation.cFileName);
						pluginFolder.append("\\");

						LoadLanguage(pluginFolder);
					} while(FindNextFile(hDll, &pluginDllInformation) == TRUE);
				}
				FindClose(hDll);
			}
		} while(FindNextFile(hFolder, &pluginFolderInformation) == TRUE);
	}
	FindClose(hFolder);	
}