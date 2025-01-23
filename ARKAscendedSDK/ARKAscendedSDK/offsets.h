#pragma once

enum offsets : uint64_t
{
	UWorld = 0x9F49CF0, // IDA Dumped
	GNames = 0x9F4C100, // IDA Dumped
	Levels = 0x430, // TArray<class ULevel*> Levels; -> class UWorld final : public UPrimalWorld
	ActorID = 0x18, // Default on UE
	OwningGameInstance = 0x478, // UWorld::OwningGameInstance
	PersistentLevel = 0x02F0, // UWorld::PersistentLevel
	AActors = 0x98, // IDA Dumped
	AActorsCount = 0xA0, // Default on UE
	LocalPlayers = 0x38, // Default on UE UGameInstance->LocalPlayers
	PlayerController = 0x30, // UPlayer->PlayerController
	RelativeLocation = 0x140, // USceneComponent->RelativeLocation
	AcknowledgedPawn = 0x580, // APlayerController->AcknowledgedPawn
	PawnPrivate = 0x540,
	CameraManager = 0x598, // APlayerController->PlayerCameraManager
	CameraCachePrivate = 0x2970, // struct FCameraCacheEntry CameraCachePrivate, // 0x2970(0x08F0)(Transient, NativeAccessSpecifierPrivate)
	PlayerState = 0x4D0, // APawn->PlayerState
	RootComponent = 0x3D0, // AActor->RootComponent
	DescriptiveName = 0x1110, // DescriptiveName
	MyCharacterStatusComponent = 0x1258, // APrimalCharacter::MyCharacterStatusComponent
	ComponentToWorld = 0xF8, // Manually Dumped
	BoneArray = 0x718 + 0x8, // StaticMesh - UStaticMeshComponent
	Mesh = 0x588, // class USkeletalMeshComponent* Mesh;
	PlayerName = 0x1D78, // class AShooterCharacter : public APrimalCharacter FString PlayerName

	// Dinos Related
	CurrentHealth = 0x0C3C, // APrimalCharacter::ReplicatedCurrentHealth
	MaxHealth = 0xC40, // APrimalCharacter::ReplicatedMaxHealth;
	ReplicatedCurrentTorpor = 0xC44, // APrimalCharacter::ReplicatedCurrentTorpor;
	ReplicatedMaxTorpor = 0xC48, // APrimalCharacter::ReplicatedMaxTorpor;
	isCarnivore = 0x1FBD, // class APrimalDinoCharacter : public APrimalCharacter bIsCarnivore : 1
	isFemale = 0x1FB2, // class APrimalDinoCharacter : public APrimalCharacter bIsFemale : 1
	isBaby = 0x1FD0, // class APrimalDinoCharacter : public APrimalCharacter bIsBaby : 1
	isBoss = 0x2C0A, // class APrimalDinoCharacter : public APrimalCharacter bIsBossDino : 1
	MatingProgress = 0x29B0, // APrimalDinoCharacter::MatingProgress
	canFly = 0x1FB0,// bIsFlying
	BaseLevel = 0x700, // UPrimalCharacterStatusComponent::BaseCharacterLevel
	// Loot Related
	TargetableDescriptiveName = 0x5A0, // DescriptiveName 
	RequiredLevelToAccess = 0x19F0, // class APrimalStructureItemContainer_SupplyCrate : public APrimalStructureItemContainer
	CurrentCrateLocation = 0x1B28, // class APrimalStructureItemContainer_SupplyCrate : public APrimalStructureItemContainer
	LootHealth = 0x5FC, // class APrimalTargetableActor : public AActor
	LootMaxHealth = 0x600, // class APrimalTargetableActor : public AActor
	bFinishedCrateMovement = 0x1B88, // bit 0x00; class APrimalStructureItemContainer_SupplyCrate : public APrimalStructureItemContainer

	// Weapon Related
	ProjectileSpeed = 0x1270, // class APrimalWeaponBow : public AShooterWeapon_Projectile ProjectileSpeed
	CurrentWeapon = 0x2098, // AShooterCharacter CurrentWeapon

};