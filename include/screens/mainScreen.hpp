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

#ifndef _UNIVERSAL_UPDATER_MAIN_SCREEN_HPP
#define _UNIVERSAL_UPDATER_MAIN_SCREEN_HPP

#include "common.hpp"
#include "store.hpp"
#include "storeEntry.hpp"
#include "storeUtils.hpp"

/*
	Modes:

	0: Entry Info.
	1: Download List.
	2: Search + Favorites.
	3: Sorting.
	4: Settings / Credits(?).
*/

class MainScreen : public Screen {
public:
	MainScreen();
	void Draw(void) const override;
	void Logic(u32 hDown, u32 hHeld, touchPosition touch) override;
private:
	std::unique_ptr<Store> store = nullptr;
	std::unique_ptr<Meta> meta = nullptr;
	std::vector<std::unique_ptr<StoreEntry>> entries;
	std::vector<std::string> dwnldList, dwnldSizes;
	bool initialized = false, fetchDown = false, showMarks = false, showSettings = false, ascending = false, updateFilter = false;
	int storeMode = 0, marks = 0, markIndex = 0, sPage = 0, lMode = 0, sSelection = 0, lastMode = 0, smallDelay = 0, sPos = 0;
	SortType sorttype = SortType::LAST_UPDATED;

	/* Title, Author, Category, Console. */
	std::vector<bool> searchIncludes = { false, false, false, false };
	std::string searchResult = "";

	C2D_Image Image = { nullptr, nullptr };
};

#endif