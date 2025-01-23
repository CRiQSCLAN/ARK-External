
namespace UnrealEngine5
{
	class render
	{
	public:
// GAME VARS
		//uint64_t GWorld;
		//uintptr_t LocalController;
		//uintptr_t CameraManager;
		UWorld* GWorld;
		APawn* LocalPlayer;
		APlayerController* LocalPlayerController;
		FCameraCacheEntry CameraCache;
		APlayerCameraManager* CameraManager;
		APrimalTargetableActor* TargetableActor;
		FVector WorldPosition;
		FVector LocalPosition;
		std::string CrateName;
		uint64_t offset = 0x0;
		FVector WorldToScreen(FVector world_location, FRotator Rotation, FVector Location, float FOV);
		FVector GetBoneWithRotation(DWORD_PTR mesh, int id);
		render(HMODULE hModule);
		
		void run_render_loop();
		void run_levels_loop();
		void process_messages();
		void handle_inputs();
		void start_scene();
		void end_scene();
		void clean_up();
		bool render_menu();
		bool initialize_overlay();
		bool hijack_overlay();
		bool create_swapchain();
		bool create_render_target();
		bool init_imgui();
		void run_actor_loop();
		void render_actors();
		std::string GetNameFromFName(int key);
		std::mutex DataMutex; // Mutex for Lock-Unlock
		std::string global_tooltip = _("N/A");
		// Data members for rendering
		void render_elements();
		void line(const ImVec2& from, const ImVec2& to, ImColor color, float thickness);
		float calculate_text_size(float distance);
		MARGINS margin{ -1 };
		ID3D11Device* device;
		ID3D11DeviceContext* device_context;
		IDXGISwapChain* swapchain;
		ID3D11RenderTargetView* render_target;
		DWORD picker_flags = ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview;
		RECT rect{ };
		HWND hwnd{ };
		MSG msg = { nullptr };
		ImFont* font{ };
		void AddCenteredImage(ImTextureID texture, ImVec2 centerPosition, float imageWidth, float imageHeight);
		void text(const std::string& text, const ImVec2& pos, float size, uint32_t color, bool center);
		void HealthBar(float x, float y, float w, float h, int phealth, int currenthealth, bool Outlined, bool center);
		void TorporBar(float x, float y, float w, float h, int ptorpor, int currenttorpor, bool Outlined, bool center);
		void filled_box(const ImVec2& position, const float width, const float height, const uint32_t color) {
			ImGui::GetBackgroundDrawList()->AddRectFilled(position, ImVec2(position.x + width, position.y + height), color, settings::visuals::box_rounding, 0);
		}

		void normal_box(const ImVec2& position, const float width, const float height, const uint32_t color, float thickness) {
			ImGui::GetBackgroundDrawList()->AddRect(position, ImVec2(position.x + width, position.y + height), color, settings::visuals::box_rounding, 0, thickness);
		}

		void outlined_box(const ImVec2& position, const float width, const float height, const uint32_t color, float thickness, float outline_thickness) {
			const ImVec2 top_left = position;
			const ImVec2 bottom_right = ImVec2(position.x + width, position.y + height);

			// Outline
			ImGui::GetBackgroundDrawList()->AddRect(top_left, bottom_right, ImColor(0, 0, 0), settings::visuals::box_rounding, 0, thickness + outline_thickness);

			// Inline
			ImGui::GetBackgroundDrawList()->AddRect(top_left, bottom_right, color, settings::visuals::box_rounding, 0, thickness);
		}

		void draw_cornered_box(int x, int y, int w, int h, ImColor color, float thickness) {
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x, y), ImVec2(x, y + (h / 3)), color, thickness);
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x, y), ImVec2(x + (w / 3), y), color, thickness);
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x + w - (w / 3), y), ImVec2(x + w, y), color, thickness);
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x + w, y), ImVec2(x + w, y + (h / 3)), color, thickness);
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x, y + h - (h / 3)), ImVec2(x, y + h), color, thickness);
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x, y + h), ImVec2(x + (w / 3), y + h), color, thickness);
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x + w - (w / 3), y + h), ImVec2(x + w, y + h), color, thickness);
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x + w, y + h - (h / 3)), ImVec2(x + w, y + h), color, thickness);
		}

		void circle(const FVector2D& pos, int radius, uint32_t color, int segments, float thickness) {
			ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(pos.x, pos.y), radius, color, segments, thickness);
		}
		uintptr_t rootcomp(uintptr_t actor) {

			return device_t.read<uintptr_t>(actor + offsets::RootComponent);
		}
		FVector get_location(uintptr_t actor) {

			return device_t.read<FVector>(rootcomp(actor) + offsets::RelativeLocation);
		}
		ImU32 gradient_color(float hue) {
			float saturation = 1.0f;
			float value = 1.0f;

			ImVec4 color;
			ImGui::ColorConvertHSVtoRGB(hue, saturation, value, color.x, color.y, color.z);
			color.w = 1.0f;

			// Convert ImVec4 color to ImU32
			return IM_COL32(int(color.x * 255), int(color.y * 255), int(color.z * 255), 255);
		}
		void draw_spinning_gradient_circle(float x, float y, float radius, int segments, float thickness, float rotation_speed) {
			if (settings::visuals::misc_outline) {
				this->circle(FVector2D(x, y), radius, ImColor(0, 0, 0), 99, 3.0f);
			}

			ImDrawList* draw_list = ImGui::GetBackgroundDrawList();

			// Calculate rotation angle based on time
			float rotation = ImGui::GetTime() * rotation_speed;

			ImVec2 wheel_center(x, y);

			// Render spinning gradient circle
			const float aeps = 0.5f / radius; // Half a pixel arc length in radians (2pi cancels out).
			const int segment_per_arc = ImMax(4, static_cast<int>(radius) / 12);

			for (int n = 0; n < 6; n++) {
				const float a0 = (n) / 6.0f * 2.0f * IM_PI - aeps + rotation;
				const float a1 = (n + 1.0f) / 6.0f * 2.0f * IM_PI + aeps + rotation;

				const int vert_start_idx = draw_list->VtxBuffer.Size;
				draw_list->PathArcTo(wheel_center, radius, a0, a1, segment_per_arc);
				draw_list->PathStroke(gradient_color(n / 6.0f), false, thickness);
				const int vert_end_idx = draw_list->VtxBuffer.Size;

				// Paint colors over existing vertices
				ImVec2 gradient_p0(wheel_center.x + ImCos(a0) * radius, wheel_center.y + ImSin(a0) * radius);
				ImVec2 gradient_p1(wheel_center.x + ImCos(a1) * radius, wheel_center.y + ImSin(a1) * radius);
				ImGui::ShadeVertsLinearColorGradientKeepAlpha(draw_list, vert_start_idx, vert_end_idx, gradient_p0, gradient_p1, gradient_color(n / 6.0f), gradient_color((n + 1.0f) / 6.0f));
			}
		}
		void draw_fov_circle(float x, float y, float radius, ImColor color, int segments, float thickness) {
			if (settings::visuals::misc_outline) {
				this->circle(FVector2D(x, y), radius, ImColor(0, 0, 0), 99, 3.0f);
			}

			this->circle(FVector2D(x, y), radius, color, 99, thickness);
		}
		void run_camera_loop();

	};


}