#pragma once
#include "includes.hpp"
#include <regex>

using namespace UnrealEngine5;
#define N_DEBUG
#define read device_t.read
auto UnrealEngine5::render::run_camera_loop() -> void {
	globals::threads::set_highest_priority();

	for (;; ) {
		if (!GWorld) {
			continue;
		}
		CameraCache = CameraManager->CameraCache();
		this_thread::sleep_for(chrono::milliseconds(1));
	}
}

auto UnrealEngine5::render::run_actor_loop() -> void {
	globals::threads::set_highest_priority();
	for (;;) {
		vector<PlayerInformation> TemporaryPlayerList;
		vector<DinoInformation> TemporaryDinoList;
		vector<DebugInformation> TemporaryDebugList;
		

		this->GWorld = UWorld::Get();
		if (!GWorld)
		{
			std::cout << "[-] UWorld seems invalid: " << reinterpret_cast<uintptr_t>(GWorld) << std::endl;
			continue;
		}
		const auto PersistentLevel = GWorld->PersistentLevel();
		if (!PersistentLevel) {
			continue;
		}
		const auto ActorList = PersistentLevel->ActorList();
		auto ActorCount = PersistentLevel->ActorCount();
		const auto OwningGameInstance = GWorld->OwningGameInstance();
		const auto LocalPlayer = OwningGameInstance->LocalPlayer();
		const auto LocalPlayerController = LocalPlayer->PlayerController();
		const auto LocalPawn = LocalPlayerController->AcknowledgedPawn();
		CameraManager = LocalPlayerController->CameraManager();
		const auto LocalPlayerRoot = LocalPawn->RootComponent();


		for (int i = 0; i < ActorCount; i++)
		{
			PlayerInformation CurrentPlayer{ };
			DinoInformation CurrentDino{ };
			DebugInformation Debug{ };
			uintptr_t CurrentActor = read<uintptr_t>(ActorList + ((i) * 0x8));
			if (CurrentActor == (uintptr_t) nullptr) continue;
			uint64_t RootComponent = read<uint64_t>(CurrentActor + offsets::RootComponent);
			if (RootComponent == NULL) continue;
			WorldPosition = read<FVector>(RootComponent + offsets::RelativeLocation);
			if (WorldPosition.x == 0) continue;
			auto PrimalNameAddress = read<uint64_t>(CurrentActor + 0x1110);
			std::string PrimalName = device_t.read_string<uint64_t>(PrimalNameAddress);
			auto PrimalNameLoot = read<uint64_t>(CurrentActor + offsets::TargetableDescriptiveName);
			std::string LootName = device_t.read_string<uint64_t>(PrimalNameAddress);
			auto ActorMesh = read<uintptr_t>(CurrentActor + offsets::Mesh);
			auto ActorStatus = read<uint64_t>(CurrentActor + offsets::MyCharacterStatusComponent);
			auto ActorLevel = read<uint64_t>(ActorStatus + offsets::BaseLevel);
			LocalPosition = read<FVector>(reinterpret_cast<uint64_t>(LocalPlayerRoot)+offsets::RelativeLocation);
			auto DinoDistance = LocalPosition.distance(WorldPosition);
			auto ActorID = read<int>(CurrentActor + offsets::ActorID);
			auto ActorName = GetNameFromFName(ActorID);
			auto Health = read<float>(CurrentActor + offsets::CurrentHealth);
			if (!Health) continue;
			auto MaxHealth = read<float>(CurrentActor + offsets::MaxHealth);
			if (!MaxHealth) continue;
			auto Torpor = read<float>(CurrentActor + offsets::ReplicatedCurrentTorpor);
			auto MaxTorpor = read<float>(CurrentActor + offsets::ReplicatedMaxTorpor);
			auto ProcentageTorpor = Torpor * 100 / MaxTorpor;
			auto isFemale = read<uint8_t>(CurrentActor + offsets::isFemale);
			auto isCarnivore = read<uint8_t>(CurrentActor + offsets::isCarnivore);
			auto isBaby = read<uint8_t>(CurrentActor + offsets::isBaby);
			auto isBoss = read<uint8_t>(CurrentActor + offsets::isBoss);
			auto canFly = read<uint8_t>(CurrentActor + offsets::canFly);
			auto MatingProgress = read<float>(CurrentActor + offsets::MatingProgress);
			auto CurrentWeapon = read<uintptr_t>(CurrentActor + offsets::CurrentWeapon);
			//auto MyPawn = read<uintptr_t>(CurrentWeapon + 0xA90);
			auto AmmoCount = read<int32_t>(CurrentWeapon + 0x0D18);
			//auto ArrowName = read<float>(CurrentWeapon + 0x1270);
			auto projectiledest = read<float>(CurrentWeapon + 0x11F8);
			//auto ShooterCharacter = LocalPawn
			if (ActorName.find("Player_C") != std::string::npos || ActorName.find("PlayerPawnTest") != std::string::npos)
			{
				float newAmmo = 10000;
				//printf(": %i \n", AmmoCount);

				//auto AmmoCount = read<float>(CurrentWeapon + 0x0D18);
				
				//printf("%f \n", projectiledest);
				auto Test = read<uint64_t>(CurrentActor + offsets::PlayerName);
				std::string PlayerName = device_t.read_string<uint64_t>(Test);
				CurrentPlayer.PlayerName = PlayerName;
				CurrentPlayer.PrimalName = PrimalName;
				CurrentPlayer.PlayerLevel = ActorLevel;
				CurrentPlayer.EntityPos = WorldPosition;
				CurrentPlayer.Distance = DinoDistance;
				CurrentPlayer.Mesh = ActorMesh;
				CurrentPlayer.ActorFName = ActorName;

				TemporaryPlayerList.push_back(CurrentPlayer); 
			}
			else if (ActorName.find("Character_BP") != std::string::npos || ActorName.find("Character_Br_B") != std::string::npos
				//|| ActorName.find("Scorpion_Character") != std::string::npos

				)
			{
				if (globals::debug)
				{

					device_t.write<float>(CurrentActor + 0x2270, globals::size);
					device_t.write<float>(CurrentActor + 0x2C80, globals::size);
					device_t.write<float>(CurrentActor + 0x2274, globals::size);
					device_t.write<float>(CurrentActor + 0x2020, globals::size);
				}
				CurrentDino.PrimalName = PrimalName;
				CurrentDino.PlayerLevel = ActorLevel;
				CurrentDino.EntityPos = WorldPosition;
				CurrentDino.Distance = DinoDistance;
				CurrentDino.Mesh = ActorMesh;
				CurrentDino.ActorFName = ActorName;
				CurrentDino.CurrentHealth = Health;
				CurrentDino.MaxHealth = MaxHealth;
				CurrentDino.CurrentTorpor = ProcentageTorpor;
				CurrentDino.isFemale = (isFemale & (1 << 5)) != 0;
				CurrentDino.isCarnivore = (isCarnivore & (1 << 2)) != 0;
				CurrentDino.isBaby = (isBaby & (1 << 6)) != 0;
				CurrentDino.MatingProgress = MatingProgress;
				CurrentDino.isBoss = (isBoss & (1 << 0)) != 0;
				CurrentDino.canFly = (canFly & (1 << 6)) != 0;
				TemporaryDinoList.push_back(CurrentDino);
			}
			if (globals::debug)
			{
				//Debug.FName = ActorName;
				//Debug.Position = WorldPosition;
				//TemporaryDebugList.push_back(Debug);
			}
		}

		PlayerList.clear(); DinoList.clear(); DebugList.clear();

		unique_lock<mutex> Lock(DataMutex);
		for (auto& Player : TemporaryPlayerList) {
			PlayerList.push_back(Player);
		}
		for (auto& Dino : TemporaryDinoList) {
			DinoList.push_back(Dino);
		}
		for (auto& Debug : TemporaryDebugList) {
			DebugList.push_back(Debug);
		}
		Lock.unlock();
		this_thread::sleep_for(chrono::milliseconds(1));
	}
}