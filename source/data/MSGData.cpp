// SPDX-License-Identifier: GPL-3.0-or-later
//
// Copyright (c) 2019-2024 Universal-Team

#include "MSGData.hpp"

#include "gui.hpp"
#include "Platform.hpp"
#include "UniversalUpdater.hpp"


void MSGData::DisplayWaitMsg(const std::string &MSG) {
	/* Hide the Sprites on a message display. */
	UU::App->GData->HideUniStoreSprites();

	UU::App->GData->StartFrame();
	UU::App->GData->DrawTop();
	Gui::DrawStringCentered(0, 80, TEXT_MEDIUM, TEXT_COLOR, MSG);
	UU::App->GData->DrawBottom();
	UU::App->GData->EndFrame();
};


bool MSGData::PromptMsg(const std::string &MSG) {
	/* Hide the Sprites on a message display. */
	UU::App->GData->HideUniStoreSprites();

	bool Result = false;

	while(Platform::MainLoop()) {
		UU::App->GData->StartFrame();
		UU::App->GData->DrawTop();
		Gui::DrawStringCentered(0, 80, TEXT_MEDIUM, TEXT_COLOR, MSG);
		Gui::DrawStringCentered(0, 210, TEXT_MEDIUM, TEXT_COLOR, "Press A to continue, B to cancel.");
		UU::App->GData->DrawBottom();
		UU::App->GData->EndFrame();

		Platform::waitForVBlank();
		UU::App->ScanInput();

		if (UU::App->Down & KEY_A) {
			Result = true;
			break;
		}

		if (UU::App->Down & KEY_B) {
			Result = false;
			break;
		}
	}

	UU::App->ScanInput();
	return Result;
};