#pragma once
#include "includes.hpp"

#define current_address reinterpret_cast<uint64_t>(this)
#define read_address(type, name, offset) type name() { return device_t.read<type>(current_address + offset); } 
#define read_address1(type, name, offset) type name() { return device_t.Read1<type>(current_address + offset); } 
#define write_to_address(type, name, offset) type name( type val ) { return request->write<type>(current_address + offset, val); }

namespace UnrealEngine5
{
	struct UObject {

	};

	struct UPrimalWorld : UObject {

	};

	struct UPrimalActor : UObject {

	};

	struct UActorComponent : UObject {

	};

	struct USceneComponent : UActorComponent {

	};

	struct AActor : UPrimalActor {

		read_address(USceneComponent*, RootComponent, offsets::RootComponent);

	};

	struct APrimalTargetableActor : AActor {

		read_address(std::string, DescriptiveName, 0x5A0);
	};

	struct APrimalStructure : APrimalTargetableActor {

	};

	struct APrimalStructureItemContainer : APrimalStructure {

	};

	struct APlayerCameraManager : AActor {
		read_address1(FCameraCacheEntry, CameraCache, offsets::CameraCachePrivate)
	};

	struct AInfo : AActor {

	};

	struct AController : AActor {

	};
	
	struct APawn : AActor {

	};

	struct APrimalPawn : APawn {

	};

	struct ACharacter : public APrimalPawn {

	};
	struct APrimalCharacter : ACharacter {

	};

	struct AShooterCharacter : APrimalCharacter {

	};

	struct AShooterWeapon : AActor {

		read_address(AShooterCharacter*, MyPawn, 0xA90);

	};

	struct AShooterWeapon_Projectile : AShooterWeapon {

	};

	struct APrimalWeaponBow : AShooterWeapon_Projectile {

	};
	struct APlayerController : AController {
		read_address(ACharacter*, AcknowledgedPawn, offsets::AcknowledgedPawn);
		read_address(APlayerCameraManager*, CameraManager, offsets::CameraManager);
	};

	struct APrimitive_PlayerController : APlayerController {

	};

	struct UPlayer : UObject {

		read_address(APrimitive_PlayerController*, PlayerController, offsets::PlayerController);

	};

	struct ULocalPlayer : UPlayer {

	};

	struct UPrimitiveLocalPlayer : ULocalPlayer {

	};

	struct UGameInstance : UObject {
		UPrimitiveLocalPlayer* LocalPlayer() {
			uintptr_t LocalPlayers = device_t.read<uintptr_t>(current_address + offsets::LocalPlayers);
			if (LocalPlayers) {
				return device_t.read<UPrimitiveLocalPlayer*>(LocalPlayers);
			}
			return nullptr;
		}
	};

	struct ULevel : UObject {
		read_address(uint64_t, ActorList, offsets::AActors);
		read_address(int, ActorCount, offsets::AActorsCount);
	};

	struct UWorld : UPrimalWorld
	{
		static UWorld* Get()
		{
			return device_t.read<UWorld*>(globals::memory::base_address + offsets::UWorld);
		}
		read_address(ULevel*, PersistentLevel, offsets::PersistentLevel);
		read_address(UGameInstance*, OwningGameInstance, offsets::OwningGameInstance);
	};
}