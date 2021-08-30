/*
*   This file is part of Universal-Updater
*   Copyright (C) 2019-2021 Universal-Team
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

#ifndef _UNIVERSAL_UPDATER_SEARCH_MENU_HPP
#define _UNIVERSAL_UPDATER_SEARCH_MENU_HPP

#include "structs.hpp"
#include <vector>


class SearchMenu {
public:
	enum class FavoriteMarks : int {
		Star = 1 << 0,
		Heart = 1 << 1,
		Diamond = 1 << 2,
		Clubs = 1 << 3,
		Spade = 1 << 4
	};

	void Draw();
	void Handler();
private:
	int Marks = 0x0;
	bool UpdateFilter = false, IsAnd = true, Includes[4] = { false };
	std::string SearchText = "";

	bool FindInVector(const std::vector<std::string> &Items, const std::string &Query);
	void DoSearch();

	static constexpr Structs::ButtonPos SearchPos[14] = {
		{ 51, 41, 262, 30 }, // Search bar.

		/* Includes. */
		{ 85, 101, 50, 10 },
		{ 85, 117, 50, 10 },
		{ 167, 101, 50, 10 },
		{ 167, 117, 50, 10 },

		/* Filters. */
		{ 82, 159, 30, 30 },
		{ 117, 159, 30, 30 },
		{ 152, 159, 30, 30 },
		{ 187, 159, 30, 30 },
		{ 222, 159, 30, 30 },
		{ 257, 159, 30, 30 },

		/* Send to Queue. */
		{ 82, 200, 205, 25 },

		/* AND / OR. */
		{ 222, 139, 30, 13 },
		{ 257, 139, 30, 13 }
	};
};

#endif