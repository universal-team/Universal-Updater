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

#include "storeUtils.hpp"



/*
	Compare Title.

	const std::unique_ptr<StoreEntry> &a: Const Reference to Entry A.
	const std::unique_ptr<StoreEntry> &b: Const Reference to Entry B.
*/
bool StoreUtils::compareTitleDescending(const std::unique_ptr<StoreEntry> &a, const std::unique_ptr<StoreEntry> &b) {
	if (a && b) return strcasecmp(StringUtils::lower_case(a->GetTitle()).c_str(), StringUtils::lower_case(b->GetTitle()).c_str()) > 0;

	return true;
}
bool StoreUtils::compareTitleAscending(const std::unique_ptr<StoreEntry> &a, const std::unique_ptr<StoreEntry> &b) {
	if (a && b) return strcasecmp(StringUtils::lower_case(b->GetTitle()).c_str(), StringUtils::lower_case(a->GetTitle()).c_str()) > 0;

	return true;
}

/*
	Compare Author.

	const std::unique_ptr<StoreEntry> &a: Const Reference to Entry A.
	const std::unique_ptr<StoreEntry> &b: Const Reference to Entry B.
*/
bool StoreUtils::compareAuthorDescending(const std::unique_ptr<StoreEntry> &a, const std::unique_ptr<StoreEntry> &b) {
	if (a && b) return strcasecmp(StringUtils::lower_case(a->GetAuthor()).c_str(), StringUtils::lower_case(b->GetAuthor()).c_str()) > 0;

	return true;
}
bool StoreUtils::compareAuthorAscending(const std::unique_ptr<StoreEntry> &a, const std::unique_ptr<StoreEntry> &b) {
	if (a && b) return strcasecmp(StringUtils::lower_case(b->GetAuthor()).c_str(), StringUtils::lower_case(a->GetAuthor()).c_str()) > 0;

	return true;
}

/*
	Compare Last Updated.

	const std::unique_ptr<StoreEntry> &a: Const Reference to Entry A.
	const std::unique_ptr<StoreEntry> &b: Const Reference to Entry B.
*/
bool StoreUtils::compareUpdateDescending(const std::unique_ptr<StoreEntry> &a, const std::unique_ptr<StoreEntry> &b) {
	if (a && b) return strcasecmp(StringUtils::lower_case(a->GetLastUpdated()).c_str(), StringUtils::lower_case(b->GetLastUpdated()).c_str()) > 0;

	return true;
}
bool StoreUtils::compareUpdateAscending(const std::unique_ptr<StoreEntry> &a, const std::unique_ptr<StoreEntry> &b) {
	if (a && b) return strcasecmp(StringUtils::lower_case(b->GetLastUpdated()).c_str(), StringUtils::lower_case(a->GetLastUpdated()).c_str()) > 0;

	return true;
}

/*
	Sort the entries.

	const bool &Ascending: Const Reference to Ascending.
	const SortType &sorttype: Const Reference to the sort type.
	std::vector<std::unique_ptr<StoreEntry>> &entries: Reference to the Entries, which should be sorted.
*/
void StoreUtils::SortEntries(const bool &Ascending, const SortType &sorttype, std::vector<std::unique_ptr<StoreEntry>> &entries) {
	switch(sorttype) {
		case SortType::TITLE:
			Ascending ? std::sort(entries.begin(), entries.end(), StoreUtils::compareTitleAscending) : std::sort(entries.begin(), entries.end(), StoreUtils::compareTitleDescending);
			break;

		case SortType::AUTHOR:
			Ascending ? std::sort(entries.begin(), entries.end(), StoreUtils::compareAuthorAscending) : std::sort(entries.begin(), entries.end(), StoreUtils::compareAuthorDescending);
			break;

		case SortType::LAST_UPDATED:
			Ascending ? std::sort(entries.begin(), entries.end(), StoreUtils::compareUpdateAscending) : std::sort(entries.begin(), entries.end(), StoreUtils::compareUpdateDescending);
			break;
	}
}

/*
	Find a query from a vector.

	const std::vector<std::string> &items: Const Reference to the vector strings / items.
	const std::string &query: Const Reference to the query.
*/
static bool findInVector(const std::vector<std::string> &items, const std::string &query) {
	for(const std::string &item : items) {
		if (StringUtils::lower_case(item).find(query) != std::string::npos) return true;
	}

	return false;
}

/*
	Search for stuff of the store.

	std::vector<std::unique_ptr<StoreEntry>> &entries: Reference to the entries.
	const std::string &query: Const Reference to the query.
	const bool &title: Const Reference, to if titles should be included.
	const bool &author: Const Reference, to if authors should be included.
	const bool &category: Const Reference, to if categories should be included.
	const bool &console: Const Reference, to if consoles should be included.
	const int &selectedMarks: Const Reference, to the selected mark flags.
*/
void StoreUtils::search(std::vector<std::unique_ptr<StoreEntry>> &entries, const std::string &query, const bool &title, const bool &author, const bool &category, const bool &console, const int &selectedMarks) {
	bool hasDone = false;

	/* Check for no title, author, category & console. */
	if (!title && !author && !category && !console) {
		if (selectedMarks != 0) {
			for (auto it = entries.begin(); it != entries.end(); ++it) {

				if (!((*it)->GetMarks() & selectedMarks)) {
					entries.erase(it);
					--it;
				}
			}
		}

		hasDone = true;
	}

	if (hasDone) return;

	for (auto it = entries.begin(); it != entries.end(); ++it) {
		if (selectedMarks != 0) { // if not 0, do filter.
			if ((*it)->GetMarks() & selectedMarks) {
				if (!((title && StringUtils::lower_case((*it)->GetTitle()).find(StringUtils::lower_case(query)) != std::string::npos)
				|| (author && StringUtils::lower_case((*it)->GetAuthor()).find(StringUtils::lower_case(query)) != std::string::npos)
				|| (category && findInVector((*it)->GetCategoryFull(), StringUtils::lower_case(query)))
				|| (console && findInVector((*it)->GetConsoleFull(), StringUtils::lower_case(query))))) {
					entries.erase(it);
					--it;
				}

			} else {
				entries.erase(it);
				--it;
			}

		} else { // Else without filter.
			if (!((title && StringUtils::lower_case((*it)->GetTitle()).find(StringUtils::lower_case(query)) != std::string::npos)
			|| (author && StringUtils::lower_case((*it)->GetAuthor()).find(StringUtils::lower_case(query)) != std::string::npos)
			|| (category && findInVector((*it)->GetCategoryFull(), StringUtils::lower_case(query)))
			|| (console && findInVector((*it)->GetConsoleFull(), StringUtils::lower_case(query))))) {
				entries.erase(it);
				--it;
			}
		}
	}
}

/*
	Reset everything of the store and clear + fetch the Entries again.

	const std::unique_ptr<Store> &store: Const Reference to the Store class.
	const std::unique_ptr<Meta> &meta: Const Reference to the Meta class.
	std::vector<std::unique_ptr<StoreEntry>> &entries: Reference to the entries.
*/
void StoreUtils::ResetAll(const std::unique_ptr<Store> &store, const std::unique_ptr<Meta> &meta, std::vector<std::unique_ptr<StoreEntry>> &entries) {
	if (store) {
		entries.clear();

		if (store->GetValid()) {
			for (int i = 0; i < store->GetStoreSize(); i++) {
				entries.push_back( std::make_unique<StoreEntry>(store, meta, i) );
			}

			store->SetBox(0);
			store->SetEntry(0);
			store->SetScreenIndx(0);
		}
	}
}