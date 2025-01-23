#pragma once
#include "includes.hpp"

using namespace UnrealEngine5;

void UnrealEngine5::render::render_elements() {
	if (show_fps) {
		char FPS[256];
		sprintf_s(FPS, _("ARK ASCENDED 5.2.0-0+UE5-ShooterGame | Total Players: %d | Total Dinosaurs: %d | Total Crates: %d | FPS: %.0f"), PlayerList.size(), DinoList.size(), LootList.size(), ImGui::GetIO().Framerate);

		text(FPS, ImVec2(15, 15), 12.0f, ImColor(255, 0, 0, 255), false);
	}
	else {
		text(_("ARK ASCENDED 5.2.0-0+UE5-ShooterGame"), ImVec2(15, 15), 15.0f, ImColor(255, 255, 255, 245), false);
	}

	if (show_fov_circle) {
		float AimRadius = (fov_value * globals::n_half_width / CameraCache.POV.FOV) / 2;
		if (misc_rgb) {
			draw_spinning_gradient_circle(globals::n_half_width, globals::n_half_height, AimRadius, 250, 1.0f, 1.0f);
		}
		else {
			draw_fov_circle(globals::n_half_width, globals::n_half_height, AimRadius, globals::misc_color, 250, 1.0f);
		}
	}

	if (show_crosshair) {
		constexpr long CrosshairSize = 10.0f;
		ImVec2 Center = ImVec2(globals::n_half_width, globals::n_half_height);

		line(ImVec2(Center.x, Center.y - CrosshairSize), ImVec2(Center.x, Center.y + CrosshairSize), globals::misc_color, 1.0f);
		line(ImVec2(Center.x - CrosshairSize, Center.y), ImVec2(Center.x + CrosshairSize, Center.y), globals::misc_color, 1.0f);
	}
}
float UnrealEngine5::render::calculate_text_size(float Distance) {
	float BaseTextSize = text_font_size;
	float MaxDistance = 270.0f;
	float MinTextSize = text_font_size - 2.0f;
	float TextSize = BaseTextSize - ((Distance / MaxDistance) * (BaseTextSize - MinTextSize));
	TextSize = TextSize < MinTextSize ? MinTextSize : TextSize;

	return TextSize;
}
