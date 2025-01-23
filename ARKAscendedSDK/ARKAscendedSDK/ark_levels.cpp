#pragma once
#include "includes.hpp"

using namespace UnrealEngine5;

auto UnrealEngine5::render::run_levels_loop() -> void {

	for (;;) {
		vector<LootInformation> TemporaryLootList;
		uintptr_t World = reinterpret_cast<uintptr_t>(GWorld);
		uintptr_t ItemLevels = device_t.read<uintptr_t>(World + offsets::Levels);
		DWORD ItemSize = device_t.read<DWORD>(World + (offsets::Levels + sizeof(PVOID)));
		for (DWORD i = 0; i < ItemSize; ++i) {
			uintptr_t ItemLevel = device_t.read<uintptr_t>(ItemLevels + (i * sizeof(uintptr_t)));
			if (!device_t.is_valid(ItemLevel)) {
				continue;
			}
			DWORD itemCount = device_t.read<DWORD>(ItemLevel + (offsets::AActors + sizeof(PVOID)));
			if (itemCount == NULL) {
				continue;
			}
			uintptr_t ItemsPawns = device_t.read<uintptr_t>(ItemLevel + AActors);
			if (!device_t.is_valid(ItemsPawns)) {
				continue;
			}
			for (DWORD j = 0; j < itemCount; ++j) {
				LootInformation Loot{ };
				uintptr_t CurrentItemPawn = device_t.read<uintptr_t>(ItemsPawns + (j * sizeof(uintptr_t)));
				int ItemIndex = device_t.read<int>(CurrentItemPawn + offsets::ActorID);
				auto CurrentItemPawnName = GetNameFromFName(ItemIndex);
				auto RequiredLevel = device_t.read<int32_t>(CurrentItemPawn + offsets::RequiredLevelToAccess);
				auto CurrentLocation = device_t.read<FVector>(CurrentItemPawn + offsets::CurrentCrateLocation);
				auto PrimalNameAddress = device_t.read<uint64_t>(CurrentItemPawn + offsets::TargetableDescriptiveName);
				std::string PrimalName = device_t.read_string<uint64_t>(PrimalNameAddress);
				auto Health = device_t.read<float>(CurrentItemPawn + offsets::LootHealth);
				auto MaxHealth = device_t.read<float>(CurrentItemPawn + offsets::LootMaxHealth);
				//auto test  = device_t.read<float>(CurrentItemPawn + 0x19B8);

				auto FinishedCrateMovement = device_t.read<uint8_t>(CurrentItemPawn + offsets::bFinishedCrateMovement);

				if (CurrentItemPawnName.find("SupplyCrate_") != std::string::npos || CurrentItemPawnName.find("SupplyCreate_") != std::string::npos) {

					Loot.PrimalName = PrimalName;
					Loot.RequiredLevel = RequiredLevel;
					Loot.ActorFName = CurrentItemPawnName;
					Loot.EntityPos = get_location(CurrentItemPawn);
					Loot.CurrentCrateLocation = CurrentLocation;
					Loot.Distance = LocalPosition.distance(Loot.EntityPos);
					Loot.FinishedMovement = (FinishedCrateMovement & (1 << 0)) != 0;
					Loot.Health = Health;
					Loot.MaxHealth = MaxHealth;
					TemporaryLootList.push_back(Loot);
				}
				
			}

		}
		unique_lock<mutex> Lock(DataMutex);
		LootList.clear();
		for (auto& Loot : TemporaryLootList) {
			LootList.push_back(Loot);
		}
		Lock.unlock();
		this_thread::sleep_for(chrono::milliseconds(1));
	}

}