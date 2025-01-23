#pragma once
#include "includes.hpp"

void Dark_Light_Theme() {
    c::color_bg1 = ImLerp(c::color_bg1, dark ? ImColor(2, 2, 2) : ImColor(121, 114, 114), ImGui::GetIO().DeltaTime * 12.f);
    c::color_bg2 = ImLerp(c::color_bg2, dark ? ImColor(42, 42, 42) : ImColor(251, 251, 251), ImGui::GetIO().DeltaTime * 12.f);

    c::bg::background = ImLerp(c::bg::background, dark ? ImColor(23, 24, 31) : ImColor(255, 255, 255), ImGui::GetIO().DeltaTime * 12.f);
    c::widget::bg_inactive = ImLerp(c::widget::bg_inactive, dark ? ImColor(38, 39, 48) : ImColor(222, 228, 244), ImGui::GetIO().DeltaTime * 12.f);

    c::accent = ImLerp(c::accent, dark ? globals::menu_color_dark : globals::menu_color_light, ImGui::GetIO().DeltaTime * 12.f);

    c::widget::mark = ImLerp(c::widget::mark, dark ? ImColor(0, 0, 0) : ImColor(255, 255, 255), ImGui::GetIO().DeltaTime * 12.f);

    c::child::background = ImLerp(c::child::background, dark ? ImColor(28, 29, 37) : ImColor(241, 243, 249), ImGui::GetIO().DeltaTime * 12.f);
    c::child::cap = ImLerp(c::child::cap, dark ? ImColor(31, 32, 41) : ImColor(228, 235, 248), ImGui::GetIO().DeltaTime * 12.f);

    c::tab::tab_active = ImLerp(c::tab::tab_active, dark ? ImColor(38, 39, 48) : ImColor(196, 205, 228), ImGui::GetIO().DeltaTime * 25.f);
    c::bg::tab_border = ImLerp(c::bg::tab_border, dark ? ImColor(31, 34, 43) : ImColor(227, 234, 246), ImGui::GetIO().DeltaTime * 25.f);
    c::bg::sub_border = ImLerp(c::bg::sub_border, dark ? ImColor(31, 32, 41) : ImColor(227, 234, 246), ImGui::GetIO().DeltaTime * 25.f);
    c::bg::weapon_border = ImLerp(c::bg::weapon_border, dark ? ImColor(28, 29, 37) : ImColor(241, 244, 249), ImGui::GetIO().DeltaTime * 25.f);

    c::text::text_active = ImLerp(c::text::text_active, dark ? ImColor(255, 255, 255) : ImColor(0, 0, 0), ImGui::GetIO().DeltaTime * 12.f);
    c::text::text_hov = ImLerp(c::text::text_hov, dark ? ImColor(137, 151, 199) : ImColor(136, 145, 176), ImGui::GetIO().DeltaTime * 12.f);
    c::text::text = ImLerp(c::text::text, dark ? ImColor(85, 92, 115) : ImColor(136, 145, 176), ImGui::GetIO().DeltaTime * 12.f);

} // LIGHT / DARK THEME CONVERTER

bool UnrealEngine5::render::render_menu() {
    ImGuiStyle* style = &ImGui::GetStyle();

    style->WindowPadding = ImVec2(0, 0);
    style->ItemSpacing = ImVec2(20, 20 * dpi);
    style->WindowBorderSize = 0;
    style->ScrollbarSize = 8.f * dpi;


    ImGui::SetNextWindowSize(ImVec2(c::bg::size) * dpi);
    ImGui::Begin(_("ARK ASCENDED 5.2.0-0+UE5-ShooterGame"), nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoResize);
    {
        const ImVec2& pos = ImGui::GetWindowPos();
        const ImVec2& region = ImGui::GetContentRegionMax();
        const ImVec2& spacing = style->ItemSpacing;

        //Dark_Light_Theme();

        ImGui::GetBackgroundDrawList()->AddRectFilled(pos, pos + ImVec2(c::bg::size * dpi), ImGui::GetColorU32(c::bg::background), c::bg::rounding * dpi);

        ImGui::GetBackgroundDrawList()->AddRectFilled(pos, pos + ImVec2(85, c::bg::size.y) * dpi, ImGui::GetColorU32(c::bg::tab_border), c::bg::rounding * dpi, ImDrawFlags_RoundCornersLeft);
        ImGui::GetBackgroundDrawList()->AddRectFilled(pos + ImVec2(85 * dpi, 0), pos + ImVec2(c::bg::size.x, 85) * dpi, ImGui::GetColorU32(c::bg::sub_border), c::bg::rounding * dpi, ImDrawFlags_RoundCornersTopRight);
        //ImGui::GetBackgroundDrawList( )->AddRectFilled( pos + ImVec2( 85, 85 ) * dpi, pos + ImVec2( c::bg::size.x, 165 ) * dpi, ImGui::GetColorU32( c::bg::weapon_border ), 0.f);

        ImGui::GetBackgroundDrawList()->AddImage(image::logo, pos + (ImVec2(85 - 37, 85 - 37) / 2) * dpi, pos + (ImVec2(85 + 37, 85 + 37) / 2) * dpi, ImVec2(0, 0), ImVec2(1, 1));

        ImVec2 text_size = ImGui::CalcTextSize(global_tooltip.c_str());

        float adjusted_width = text_size.x + 10; // Adding padding on both sides of the text

        ImVec2 rect_pos = pos + ImVec2((920 * dpi - adjusted_width) / 2, 705 * dpi);
        ImVec2 rect_end = rect_pos + ImVec2(adjusted_width, 25 * dpi);

        //ImGui::GetBackgroundDrawList()->AddRectFilled(rect_pos, rect_end, ImGui::GetColorU32(c::bg::background), c::bg::rounding * dpi);

        ImVec2 text_pos = rect_pos + ImVec2(10, 5) * dpi; // Adjust the text position within the rectangle
        //text(global_tooltip, text_pos, 14.0f, ImColor(c::accent), false);

        ImGui::SetCursorPos(ImVec2((85 - 45) / 2 * dpi, 85 * dpi));
        ImGui::BeginGroup();
        {

            if (edited::Tab(0 == tabs_state, _("a"), ImVec2(45, 45))) tabs_state = 0;

            if (edited::Tab(1 == tabs_state, _("b"), ImVec2(45, 45))) tabs_state = 1;

            if (edited::Tab(2 == tabs_state, _("d"), ImVec2(45, 45))) tabs_state = 2;

            if (edited::Tab(3 == tabs_state, _("e"), ImVec2(45, 45))) tabs_state = 3;

        }
        ImGui::EndGroup();



        static float tab_alpha = 0.f; /* */ static float tab_add; /* */ static int active_tab = 0;

        tab_alpha = ImClamp(tab_alpha + (4.f * ImGui::GetIO().DeltaTime * (tabs_state == active_tab ? 1.f : -1.f)), 0.f, 1.f);

        if (tab_alpha == 0.f && tab_add == 0.f) active_tab = tabs_state;

        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab_alpha * style->Alpha);

        if (active_tab == 0) {
            ImGui::SetCursorPos(ImVec2((85 + spacing.x) * dpi, (85 - 45) / 2 * dpi));
            ImGui::BeginGroup();
            {
                if (edited::SubTab(0 == subtab_state, _("Dinos"), ImVec2(90, 45))) subtab_state = 0;

                //ImGui::SameLine(0, spacing.x * dpi);

                //if (edited::SubTab(1 == subtab_state, _("Triggerbot"), ImVec2(90, 45))) subtab_state = 1;

                //ImGui::SameLine(0, spacing.x * dpi);

                //if (edited::SubTab(2 == subtab_state, _("Weapons"), ImVec2(90, 45))) subtab_state = 2;
            }
            ImGui::EndGroup();
        }
        else if (active_tab == 1) {
            ImGui::SetCursorPos(ImVec2((85 + spacing.x) * dpi, (85 - 45) / 2 * dpi));
            ImGui::BeginGroup();
            {
                if (edited::SubTab(0 == subtab_state, _("Players"), ImVec2(90, 45))) subtab_state = 0;

//                ImGui::SameLine(0, spacing.x * dpi);
//
//                if (edited::SubTab(1 == subtab_state, _("Radar"), ImVec2(80, 45))) subtab_state = 1;
//#
//                ImGui::SameLine(0, spacing.x * dpi);
//
//                if (edited::SubTab(2 == subtab_state, _("World"), ImVec2(80, 45))) subtab_state = 2;
            }
            ImGui::EndGroup();
        }
        else if (active_tab == 2) {
            ImGui::SetCursorPos(ImVec2((85 + spacing.x) * dpi, (85 - 45) / 2 * dpi));
            ImGui::BeginGroup();
            {
                if (edited::SubTab(0 == subtab_state, _("Loot"), ImVec2(90, 45))) subtab_state = 0;
            }
            ImGui::EndGroup();
        }
        else if (active_tab == 3) {
            ImGui::SetCursorPos(ImVec2((85 + spacing.x) * dpi, (85 - 45) / 2 * dpi));
            ImGui::BeginGroup();
            {
                if (edited::SubTab(0 == subtab_state, _("Settings"), ImVec2(90, 45))) subtab_state = 0;

                //ImGui::SameLine(0, spacing.x * dpi);

                //if (edited::SubTab(1 == subtab_state, _("Miscellaneous"), ImVec2(80, 45))) subtab_state = 1;
            }
            ImGui::EndGroup();
        }

        ImGui::SetCursorPos(ImVec2((85 + spacing.x) * dpi, (90 + spacing.x) * dpi));
        ImGui::BeginChild(_("General child"), ImVec2(c::bg::size) * dpi - ImVec2(85 + spacing.x, 90 + spacing.x) * dpi);
        {
            if (active_tab == 0 && subtab_state == 0) {
                ImGui::BeginGroup();
                {
                    edited::BeginChild(_("DINOS"), ImVec2((c::bg::size.x - (85 + spacing.x * 3)) / 2, 0), NULL);
                    {
                        edited::Checkbox(_("Enable Dino"), &dinos::enable);
                        edited::Checkbox(_("Enable Name"), &dinos::name);
                        edited::Checkbox(_("Enable Distance"), &dinos::distance);
                        edited::Checkbox(_("Enable Line"), &dinos::line);
                        edited::Checkbox(_("Enable Level"), &dinos::level);
                        edited::Checkbox(_("Enable Growth"), &dinos::isbaby);
                        edited::Checkbox(_("Enable Aggressivity"), &dinos::aggressivity);
                        edited::Checkbox(_("Enable Gender"), &dinos::gender);
                        edited::Checkbox(_("Enable Health Bar"), &dinos::health);
                        edited::Checkbox(_("Enable Torpor Bar"), &dinos::torpor);

                    }
                    edited::EndChild();
                }
                ImGui::EndGroup();

                ImGui::SameLine(0, spacing.x * dpi);

                ImGui::BeginGroup();
                {
                    edited::BeginChild(_("SETTINGS"), ImVec2((c::bg::size.x - (85 + spacing.x * 3)) / 2, 0), NULL);
                    {
                        edited::SliderFloat(_("Render Range"), &dinos::render_range, 1.f, 300.f, _("%.fM"));
                    }
                    edited::EndChild();
                }
                ImGui::EndGroup();

            }
            else if (active_tab == 1 && subtab_state == 0) {
                ImGui::BeginGroup();
                {
                    edited::BeginChild(_("VISUALS"), ImVec2((c::bg::size.x - (85 + spacing.x * 3)) / 2, 0), NULL);
                    {

                    }
                    edited::EndChild();
                }
                ImGui::EndGroup();

                ImGui::SameLine(0, spacing.x * dpi);

                ImGui::BeginGroup();
                {
                    edited::BeginChild(_("SETTINGS"), ImVec2((c::bg::size.x - (85 + spacing.x * 3)) / 2, 0), NULL);
                    {

                    }
                    edited::EndChild();
                }
                ImGui::EndGroup();

            }
            else if (active_tab == 2 && subtab_state == 0) {
                ImGui::BeginGroup();
                {
                    edited::BeginChild(_("LOOT"), ImVec2((c::bg::size.x - (85 + spacing.x * 3)) / 2, 0), NULL);
                    {

                    }
                    edited::EndChild();
                }
                ImGui::EndGroup();

                ImGui::SameLine(0, spacing.x* dpi);

                ImGui::BeginGroup();
                {
                    edited::BeginChild(_("SETTINGS"), ImVec2((c::bg::size.x - (85 + spacing.x * 3)) / 2, 0), NULL);
                    {

                    }
                    edited::EndChild();
                }
                ImGui::EndGroup();

            }
            else if (active_tab == 3 && subtab_state == 0) {
                ImGui::BeginGroup();
                {
                    edited::BeginChild(_("MISC"), ImVec2((c::bg::size.x - (85 + spacing.x * 3)) / 2, 0), NULL);
                    {
                        edited::Checkbox(_("DEBUG WORLD"), &globals::debug);
                        edited::SliderFloat(_("SizeOf"), &globals::size, 1.f, 300.f, _("%.3fF"));
                    }
                    edited::EndChild();
                }
                ImGui::EndGroup();

                ImGui::SameLine(0, spacing.x * dpi);

                ImGui::BeginGroup();
                {
                    edited::BeginChild(_("SETTINGS"), ImVec2((c::bg::size.x - (85 + spacing.x * 3)) / 2, 0), NULL);
                    {
                        //static char buffer[128] = "";
                        edited::Checkbox(_("Enable Crosshair"), &show_crosshair);
                        edited::Checkbox(_("Enable RGB"), &misc_rgb);
                        edited::Checkbox(_("Enable FOV Circle"), &show_fov_circle);
                        edited::SliderFloat(_("FOV Value"), &fov_value, 1.f, 300.f, _("%.3fF"));
                        //ImGui::InputText("Enter text", buffer, IM_ARRAYSIZE(buffer));
                    }
                    edited::EndChild();
                }
                ImGui::EndGroup();
            }
        }
        ImGui::EndChild();
        ImGui::PopStyleVar();

    }

    ImGui::End();

    return true;
}