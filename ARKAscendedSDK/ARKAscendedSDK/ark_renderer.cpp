#pragma once
#include "includes.hpp"

using namespace UnrealEngine5;

auto UnrealEngine5::render::render_actors() -> void {
	unique_lock<mutex> Lock(DataMutex);
	if (!show_render) {
		return;
	}
	globals::misc_color = ImColor({ misc_color[0], misc_color[1], misc_color[2], misc_color[3] });
	globals::menu_color_dark = ImColor({ menu_color_dark[0], menu_color_dark[1], menu_color_dark[2], menu_color_dark[3] });
	globals::menu_color_light = ImColor({ menu_color_light[0], menu_color_light[1], menu_color_light[2], menu_color_light[3] });
	render_elements();
	for (auto& Player : PlayerList) {

		auto PrimalName = Player.PrimalName;
		auto PlayerLevel = Player.PlayerLevel;
		auto RequiredLevel = Player.RequiredLevel;
		auto EntityPos = Player.EntityPos;
		auto PlayerDistance = Player.Distance;
		auto Mesh = Player.Mesh;
		auto FName = Player.ActorFName;
		auto PlayerName = Player.PlayerName;
		auto PlayerPosition = WorldToScreen(EntityPos, CameraCache.POV.Rotation, CameraCache.POV.Location, CameraCache.POV.FOV); // 0xf8 
		if (PlayerPosition)
		{
			char dist[64];
			float distanceInMeters = PlayerDistance / 100.0f;
			sprintf_s(dist, "[%.fm]", distanceInMeters);
			if (!PrimalName.empty())
			{
				text(PrimalName + "[Lv " + to_string(PlayerLevel) + "]", ImVec2(PlayerPosition.x, PlayerPosition.y), 12.f, colors::player_distance, true);
			}
			text(dist, ImVec2(PlayerPosition.x, PlayerPosition.y + 12), 12.f, colors::player_distance, true);
			text(PlayerName, ImVec2(PlayerPosition.x, PlayerPosition.y + 24), 12.f, colors::player_distance, true);
			//line(ImVec2(1920 / 2, 1080 / 2), ImVec2(test.x, test.y), ImColor(0, 255, 0, 255), 1.0f);
		}
	}

	for (auto& Dino : DinoList) {

		auto PrimalName = Dino.PrimalName;
		auto PlayerLevel = Dino.PlayerLevel;
		auto RequiredLevel = Dino.RequiredLevel;
		auto EntityPos = Dino.EntityPos;
		auto PlayerDistance = Dino.Distance;
		auto Mesh = Dino.Mesh;
		auto FName = Dino.ActorFName;
		auto PlayerName = Dino.PlayerName;
		auto DinoHealth = Dino.CurrentHealth;
		auto DinoMaxHealth = Dino.MaxHealth;
		auto PlayerPosition = WorldToScreen(EntityPos, CameraCache.POV.Rotation, CameraCache.POV.Location, CameraCache.POV.FOV); // 0xf8 
		auto DinoTorpor = Dino.CurrentTorpor;
		auto isFemale = Dino.isFemale;
		auto isAggresive = Dino.isCarnivore;
		auto isBaby = Dino.isBaby;
		auto MatingProgress = Dino.MatingProgress;
		auto isBoss = Dino.isBoss;
		auto canFly = Dino.canFly;
		if (dinos::enable)
		{
			if (PlayerPosition)
			{
				char dist[64];
				char matingprog[64];
				sprintf_s(matingprog, "%f", MatingProgress);
				float matingprogressconverted = MatingProgress * 100.0f;
				
				float distanceInMeters = PlayerDistance / 100.0f;
				int HealthConverted = DinoHealth;
				int TorporConverted = DinoTorpor;
				sprintf_s(dist, "[%.fm]", distanceInMeters);
				std::string level = "[Lv " + to_string(PlayerLevel) + "]";
				std::string matingprogress = to_string(matingprogressconverted);
				
				if (dinos::render_range > distanceInMeters)
				{
					if (!PrimalName.empty())
					{
						if (dinos::name)
						{
							text(PrimalName, ImVec2(PlayerPosition.x, PlayerPosition.y), 12.f, ImColor(0, 255, 0, 255), true);
						}
						if (dinos::level)
						{
							if (PlayerLevel > 100)
							{
								text("[Lv " + to_string(PlayerLevel) + "]", ImVec2(PlayerPosition.x, PlayerPosition.y + 12), 15.f, ImColor(255, 0, 0, 255), true);

							}
							else
								text("[Lv " + to_string(PlayerLevel) + "]", ImVec2(PlayerPosition.x, PlayerPosition.y + 12), 10.f, ImColor(0, 255, 0, 255), true);
						}
						if (dinos::distance)
						{
							text(dist, ImVec2(PlayerPosition.x, PlayerPosition.y + 22), 10.f, ImColor(0, 255, 0, 255), true);
						}
						if (dinos::health)
						{
							auto procentage = DinoHealth * 100 / DinoMaxHealth;
							HealthBar(PlayerPosition.x, PlayerPosition.y + 36, 50, 8, procentage, HealthConverted, true, true);
						}
						if (dinos::torpor)
						{
							TorporBar(PlayerPosition.x, PlayerPosition.y + 46, 50, 8, DinoTorpor, TorporConverted, true, true);
						}
						if (dinos::line)
						{
							if (PlayerLevel > 140)
							{
								line(ImVec2(globals::n_half_width, globals::n_half_height), ImVec2(PlayerPosition.x, PlayerPosition.y + 50), ImColor(255, 0, 0, 255), 1.0f);

							}
							else
								line(ImVec2(globals::n_half_width, globals::n_half_height), ImVec2(PlayerPosition.x, PlayerPosition.y + 50), ImColor(0, 255, 0, 255), 1.0f);
						}
						if (dinos::gender)
						{
							if (isFemale)
							{
								AddCenteredImage(image::female, ImVec2(PlayerPosition.x, PlayerPosition.y - 10), 20, 20);
							}
							else
							{
								AddCenteredImage(image::male, ImVec2(PlayerPosition.x, PlayerPosition.y - 10), 20, 20);
							}
						}
						if (dinos::aggressivity)
						{
							if (isAggresive)
							{
								text("[Aggresive]", ImVec2(PlayerPosition.x, PlayerPosition.y + 53), 10.f, ImColor(255, 0, 0, 255), true);
							}
							else
							{
								text("[Friendly]", ImVec2(PlayerPosition.x, PlayerPosition.y + 53), 10.f, ImColor(0, 255, 0, 255), true);
							}
						}
						if (dinos::isbaby)
						{
							if (isBaby)
							{
								text("[BABY]", ImVec2(PlayerPosition.x, PlayerPosition.y + 63), 10.f, ImColor(255, 255, 0, 255), true);
							}
							else
							{
								text("[ADULT]", ImVec2(PlayerPosition.x, PlayerPosition.y + 63), 10.f, ImColor(0, 255, 0, 255), true);
							}
						}
						if (dinos::matingprogress)
						{
							if (isFemale)
								text("Mating Progress " + matingprogress, ImVec2(PlayerPosition.x, PlayerPosition.y + 73), 10.f, ImColor(0, 255, 0, 255), true);
						}
						if (dinos::isboss)
						{
							if (isBoss)
							{
								text("BOSS", ImVec2(PlayerPosition.x, PlayerPosition.y + 73), 10.f, ImColor(0, 0, 255, 255), true);

							}
						}
						if (canFly)
						{
							text("CAN FLY", ImVec2(PlayerPosition.x, PlayerPosition.y + 73), 10.f, ImColor(0, 255, 255, 255), true);
						}
					}
				}
			}

		}

	}

	for (auto& Debug : DebugList) {

		auto Name = Debug.FName;
		auto Position = Debug.Position;
		auto DebugPosition = WorldToScreen(Position, CameraCache.POV.Rotation, CameraCache.POV.Location, CameraCache.POV.FOV); // 0xf8 
		text(Name, ImVec2(DebugPosition.x, DebugPosition.y), 12.f, ImColor(0, 255, 0, 255), true);
	}

	for (auto& Loot : LootList) {

		//auto FName = Loot.ActorFName;
		//auto PrimalName = Loot.PrimalName;
		//auto Position = Loot.EntityPos;
		//auto RequiredLevel = Loot.RequiredLevel;
		//auto LootPosition = WorldToScreen(Position, CameraCache.POV.Rotation, CameraCache.POV.Location, CameraCache.POV.FOV); // 0xf8 
		//auto Location = Loot.CurrentCrateLocation;
		//auto Distance = Loot.Distance;
		//auto FinishedMovement = Loot.FinishedMovement;
		//auto Health = Loot.Health;
		//auto MaxHealth = Loot.MaxHealth;
		//char dist[64];
		//float distanceInMeters = Distance / 100.0f;
		//sprintf_s(dist, "[%.fm]", distanceInMeters);
		//text(FName, ImVec2(LootPosition.x, LootPosition.y), 10.f, ImColor(0, 255, 0, 255), true);
		//text(PrimalName, ImVec2(LootPosition.x, LootPosition.y), 10.f, ImColor(0, 255, 0, 255), true);
		//text("[Required Level: " + to_string(RequiredLevel) +"]", ImVec2(LootPosition.x, LootPosition.y + 10), 10.f, ImColor(0, 255, 0, 255), true);
		//text(dist, ImVec2(LootPosition.x, LootPosition.y + 20), 10.f, ImColor(0, 255, 0, 255), true);
		//if (FinishedMovement)
		//{
		//	text("ACCESIBLE", ImVec2(LootPosition.x, LootPosition.y + 30), 10.f, ImColor(0, 255, 0, 255), true);
		//	auto procentage = Health * 100 / MaxHealth;
		//	HealthBar(LootPosition.x, LootPosition.y + 50, 50, 8, procentage, int(Health), true, true);
		//}
		//else
		//{
		//	text("CRATE MOVING", ImVec2(LootPosition.x, LootPosition.y + 30), 10.f, ImColor(255, 0, 0, 255), true);
		//}
	}
	Lock.unlock();
}