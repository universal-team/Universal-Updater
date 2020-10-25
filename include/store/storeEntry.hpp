/*
*   This file is part of Universal-Updater
*   Copyright (C) 2019-2020 Universal-Team
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
*       * Requiring preservation of specified reasonable legal notices or
*         author attributions in that material or in the Appropriate Legal
*         Notices displayed by works containing it.
*       * Prohibiting misrepresentation of the origin of that material,
*         or requiring that modified versions of such material be marked in
*         reasonable ways as different from the original version.
*/

#ifndef _UNIVERSAL_UPDATER_STORE_ENTRY_HPP
#define _UNIVERSAL_UPDATER_STORE_ENTRY_HPP

#include "meta.hpp"
#include "store.hpp"
#include "stringUtils.hpp"

class StoreEntry {
public:
	StoreEntry(std::unique_ptr<Store> &store, std::unique_ptr<Meta> &meta, int index);

	std::string GetTitle() const { return this->Title; };
	std::string GetAuthor() const { return this->Author; };
	std::string GetDescription() const { return this->Description; };
	std::string GetCategory() const { return this->Category; };
	std::string GetVersion() const { return this->Version; };
	std::string GetConsole() const { return this->Console; };
	std::string GetLastUpdated() const { return this->LastUpdated; };
	std::string GetLicense() const { return this->License; };
	std::string GetSize() const { return this->Size; };
	int GetMarks() const { return this->Marks; };

	C2D_Image GetIcon() const { return this->Icon; };

	int GetSheetIndex() const { return this->SheetIndex; };
	int GetEntryIndex() const { return this->EntryIndex; };

	std::vector<std::string> GetCategoryFull() const { return this->FullCategory; };
	std::vector<std::string> GetConsoleFull() const { return this->FullConsole; };

	bool GetUpdateAvl() const { return this->UpdateAvailable; };
	void SetUpdateAvl(bool v) { this->UpdateAvailable = v; };

	void SetMark(int marks) {
		this->Marks = marks;
		this->MarkString = StringUtils::GetMarkString(this->Marks);
	};

private:
	std::string Title, Author, Description, Category, Version, Console, LastUpdated, License, Size, MarkString;
	C2D_Image Icon;
	int SheetIndex, EntryIndex, Marks;
	std::vector<std::string> FullCategory, FullConsole;
	bool UpdateAvailable;
};

#endif