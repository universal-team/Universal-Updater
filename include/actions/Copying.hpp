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

#ifndef _UNIVERSAL_UPDATER_COPYING_HPP
#define _UNIVERSAL_UPDATER_COPYING_HPP

#include "Action.hpp"
#include "BrowseData.hpp"
#include <memory>
#include <string>


/*
	Handles Copying of Files.
*/
class Copying : public Action {
public:
	enum class Error : uint8_t { Good = 0, SourceNotExist, DestNotExist, WrittenNotRead, Unknown, OutOfSpace };

	Copying(const std::string &Source, const std::string &Dest)
		: Source(Source), Dest(Dest) { };

	void Handler() override;
	void Draw() const override;

	/* Some returns. */
	uint8_t State() const override { return (uint8_t)this->CurState; };
	Action::ActionType Type() const override { return Action::ActionType::Copying; };
	
private:
	uint32_t CopyOffs = 0, CopySize = 0;
	Error CurState = Error::Good; // The current state of the operation.
	std::string Source = "", Dest = "";

	/* Some Helpers. */
	static constexpr int CopyBufSize = 0x8000;
	uint32_t CopyBuf[CopyBufSize];
	
	void FileCopy(const std::string &Source, const std::string &Dest);
	void DirCopy(const BrowseData::DirEntry &Entry, const std::string &Source, const std::string &Dest);
};

#endif