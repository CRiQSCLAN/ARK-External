#pragma once
#include "includes.hpp"

using namespace UnrealEngine5;

void UnrealEngine5::render::text(const string& text, const ImVec2& pos, float size, uint32_t color, bool center) {
	constexpr float StrokeValue = 1.0f;
	uint32_t EdgeColor = 0xFF000000;

	float EdgeA = (EdgeColor >> 24) & 0xff;
	float EdgeR = (EdgeColor >> 16) & 0xff;
	float EdgeG = (EdgeColor >> 8) & 0xff;
	float EdgeB = (EdgeColor) & 0xff;

	stringstream StringStream(text);
	string Line;
	float Y = 0.0f;
	int I = 0;

	while (getline(StringStream, Line)) {
		ImVec2 TextSize = this->font->CalcTextSizeA(size, FLT_MAX, 0.0f, Line.c_str());

		if (center) {
			if (text_outline) {
				ImGui::GetBackgroundDrawList()->AddText(this->font, size, ImVec2((pos.x - TextSize.x / 2.0f) - StrokeValue, pos.y + TextSize.y * I), ImGui::GetColorU32(ImVec4(EdgeR / 255, EdgeG / 255, EdgeB / 255, EdgeA / 255)), Line.c_str());
				ImGui::GetBackgroundDrawList()->AddText(this->font, size, ImVec2((pos.x - TextSize.x / 2.0f) + StrokeValue, pos.y + TextSize.y * I), ImGui::GetColorU32(ImVec4(EdgeR / 255, EdgeG / 255, EdgeB / 255, EdgeA / 255)), Line.c_str());
				ImGui::GetBackgroundDrawList()->AddText(this->font, size, ImVec2((pos.x - TextSize.x / 2.0f), (pos.y + TextSize.y * I) - StrokeValue), ImGui::GetColorU32(ImVec4(EdgeR / 255, EdgeG / 255, EdgeB / 255, EdgeA / 255)), Line.c_str());
				ImGui::GetBackgroundDrawList()->AddText(this->font, size, ImVec2((pos.x - TextSize.x / 2.0f), (pos.y + TextSize.y * I) + StrokeValue), ImGui::GetColorU32(ImVec4(EdgeR / 255, EdgeG / 255, EdgeB / 255, EdgeA / 255)), Line.c_str());
			}
			ImGui::GetBackgroundDrawList()->AddText(this->font, size, ImVec2(pos.x - TextSize.x / 2.0f, pos.y + TextSize.y * I), color, Line.c_str());
		}
		else {
			if (text_outline) {
				ImGui::GetBackgroundDrawList()->AddText(this->font, size, ImVec2((pos.x) - StrokeValue, (pos.y + TextSize.y * I)), ImGui::GetColorU32(ImVec4(EdgeR / 255, EdgeG / 255, EdgeB / 255, EdgeA / 255)), Line.c_str());
				ImGui::GetBackgroundDrawList()->AddText(this->font, size, ImVec2((pos.x) + StrokeValue, (pos.y + TextSize.y * I)), ImGui::GetColorU32(ImVec4(EdgeR / 255, EdgeG / 255, EdgeB / 255, EdgeA / 255)), Line.c_str());
				ImGui::GetBackgroundDrawList()->AddText(this->font, size, ImVec2((pos.x), (pos.y + TextSize.y * I) - StrokeValue), ImGui::GetColorU32(ImVec4(EdgeR / 255, EdgeG / 255, EdgeB / 255, EdgeA / 255)), Line.c_str());
				ImGui::GetBackgroundDrawList()->AddText(this->font, size, ImVec2((pos.x), (pos.y + TextSize.y * I) + StrokeValue), ImGui::GetColorU32(ImVec4(EdgeR / 255, EdgeG / 255, EdgeB / 255, EdgeA / 255)), Line.c_str());
			}
			ImGui::GetBackgroundDrawList()->AddText(this->font, size, ImVec2(pos.x, pos.y + TextSize.y * I), color, Line.c_str());
		}

		Y = pos.y + TextSize.y * (I + 1);
		I++;
	}
}
auto RectFilled(float x0, float y0, float x1, float y1, ImColor color, float rounding, int rounding_corners_flags) -> VOID
{
	auto vList = ImGui::GetBackgroundDrawList();
	vList->AddRectFilled(ImVec2(x0, y0), ImVec2(x1, y1), color, rounding, rounding_corners_flags);
}
auto UnrealEngine5::render::HealthBar(float x, float y, float w, float h, int phealth, int currenthealth, bool Outlined, bool center) -> void
{
	auto vList = ImGui::GetBackgroundDrawList();

	int healthValue = max(0, min(phealth, 100));

	ImColor barColor = ImColor
	(
		min(510 * (100 - healthValue) / 100, 255),
		min(510 * healthValue / 100, 255),
		25,
		255
	);

	if (center)
	{
		x -= w / 2.0f;
		y -= h / 2.0f;
	}

	if (Outlined)
		vList->AddRect(ImVec2(x - 1, y - 1), ImVec2(x + w + 1, y + h + 1), ImColor(0.f, 0.f, 0.f), 0.0f, 0, 1.0f);

	float filledWidth = (w * healthValue) / 100.0f;
	RectFilled(x, y, x + filledWidth, y + h, barColor, 0.0f, 0);
	std::string actualHPText = std::to_string(currenthealth) + " HP";
	std::string healthText = std::to_string(healthValue) + "%";
	ImVec2 actualHPTextSize = ImGui::CalcTextSize(actualHPText.c_str());
	ImVec2 healthTextSize = ImGui::CalcTextSize(healthText.c_str());

	text(healthText.c_str(), ImVec2(x + w + 5, y + (h / 2) - ((healthTextSize.y / 2) - 3)), 10.f, barColor, false);
	text(actualHPText.c_str(), ImVec2(x - actualHPTextSize.x + 10, y + (h / 2) - ((actualHPTextSize.y / 2) - 3)), 10.f, barColor, false);
}
void UnrealEngine5::render::AddCenteredImage(ImTextureID texture, ImVec2 centerPosition, float imageWidth, float imageHeight)
{
	// Calculate the top-left corner of the image by centering it around the given position
	ImVec2 topLeft = ImVec2(
		centerPosition.x - imageWidth / 2.0f,
		centerPosition.y - imageHeight / 2.0f
	);

	// Calculate the bottom-right corner of the image
	ImVec2 bottomRight = ImVec2(
		centerPosition.x + imageWidth / 2.0f,
		centerPosition.y + imageHeight / 2.0f
	);

	// Draw the image centered at the given position
	ImGui::GetBackgroundDrawList()->AddImage(
		texture,      // Texture ID for the image
		topLeft,      // Top-left corner
		bottomRight,  // Bottom-right corner
		ImVec2(0, 0), // UV coordinates for the top-left of the image
		ImVec2(1, 1)  // UV coordinates for the bottom-right of the image
	);
}
auto UnrealEngine5::render::TorporBar(float x, float y, float w, float h, int ptorpor, int currenttorpor, bool Outlined, bool center) -> void
{
	auto vList = ImGui::GetBackgroundDrawList();

	// Ensure torpor value is between 0 and 100
	int torporValue = max(0, min(ptorpor, 100));

	// Calculate bar color (for torpor, we use purple color)
	ImColor barColor = ImColor(162.f / 255, 6.f / 255, 184.f / 255);

	if (center)
	{
		x -= w / 2.0f;
		y -= h / 2.0f;
	}

	if (Outlined)
		vList->AddRect(ImVec2(x - 1, y - 1), ImVec2(x + w + 1, y + h + 1), ImColor(0.f, 0.f, 0.f), 0.0f, 0, 1.0f);

	float filledWidth = (w * torporValue) / 100.0f;
	RectFilled(x, y, x + filledWidth, y + h, barColor, 0.0f, 0);
	std::string actualTorporText = std::to_string(currenttorpor);
	std::string torporText = std::to_string(torporValue) + "%";
	ImVec2 actualTorporTextSize = ImGui::CalcTextSize(actualTorporText.c_str());
	ImVec2 torporTextSize = ImGui::CalcTextSize(torporText.c_str());
	//vList->AddText(ImVec2(x - actualTorporTextSize.x - 5, y + (h / 2) - (actualTorporTextSize.y / 2)), barColor, actualTorporText.c_str());
	//vList->AddText(ImVec2(x + w + 5, y + (h / 2) - (torporTextSize.y / 2)), barColor, torporText.c_str());

	//text(actualTorporText.c_str(), ImVec2(x - actualTorporTextSize.x - 5, y + (h / 2) - (actualTorporTextSize.y / 2) + 3 ), 10.f, barColor, false);
	text(torporText.c_str(), ImVec2(x + w + 5, y + (h / 2) - (torporTextSize.y / 2) + 3), 10.f, barColor, false);

}

void UnrealEngine5::render::line(const ImVec2& from, const ImVec2& to, ImColor color, float thickness) {
	ImGui::GetBackgroundDrawList()->AddLine(from, to, color, thickness);
}
D3DXMATRIX Matrix(FVector rot, FVector origin)
{
	double radPitch = (rot.x * double(M_PI) / 180.f);
	double radYaw = (rot.y * double(M_PI) / 180.f);
	double radRoll = (rot.z * double(M_PI) / 180.f);

	double SP = sinf(radPitch);
	double CP = cosf(radPitch);
	double SY = sinf(radYaw);
	double CY = cosf(radYaw);
	double SR = sinf(radRoll);
	double CR = cosf(radRoll);

	D3DMATRIX matrix;
	matrix.m[0][0] = CP * CY;
	matrix.m[0][1] = CP * SY;
	matrix.m[0][2] = SP;
	matrix.m[0][3] = 0.f;

	matrix.m[1][0] = SR * SP * CY - CR * SY;
	matrix.m[1][1] = SR * SP * SY + CR * CY;
	matrix.m[1][2] = -SR * CP;
	matrix.m[1][3] = 0.f;

	matrix.m[2][0] = -(CR * SP * CY + SR * SY);
	matrix.m[2][1] = CY * SR - CR * SP * SY;
	matrix.m[2][2] = CR * CP;
	matrix.m[2][3] = 0.f;

	matrix.m[3][0] = origin.x;
	matrix.m[3][1] = origin.y;
	matrix.m[3][2] = origin.z;
	matrix.m[3][3] = 1.f;

	return matrix;
}
D3DMATRIX ToMatrix(FRotator Rotation, FVector origin)
{
	double Pitch = (Rotation.Pitch * double(UCONST_PI) / 180.f);
	double Yaw = (Rotation.Yaw * double(UCONST_PI) / 180.f);
	double Roll = (Rotation.Roll * double(UCONST_PI) / 180.f);

	double SP = sinf(Pitch);
	double CP = cosf(Pitch);
	double SY = sinf(Yaw);
	double CY = cosf(Yaw);
	double SR = sinf(Roll);
	double CR = cosf(Roll);

	D3DMATRIX Matrix;
	Matrix._11 = CP * CY;
	Matrix._12 = CP * SY;
	Matrix._13 = SP;
	Matrix._14 = 0.f;

	Matrix._21 = SR * SP * CY - CR * SY;
	Matrix._22 = SR * SP * SY + CR * CY;
	Matrix._23 = -SR * CP;
	Matrix._24 = 0.f;

	Matrix._31 = -(CR * SP * CY + SR * SY);
	Matrix._32 = CY * SR - CR * SP * SY;
	Matrix._33 = CR * CP;
	Matrix._34 = 0.f;

	Matrix._41 = origin.x;
	Matrix._42 = origin.y;
	Matrix._43 = origin.z;
	Matrix._44 = 1.f;

	return Matrix;


}

FVector UnrealEngine5::render::WorldToScreen(FVector world_location, FRotator Rotation, FVector Location, float FOV)
{
	FVector screen_location = FVector(0, 0, 0);
	
	D3DMATRIX tempMatrix = ToMatrix(Rotation, world_location);

	FVector vAxisX, vAxisY, vAxisZ;
	vAxisX = FVector(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	vAxisY = FVector(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	vAxisZ = FVector(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

	FVector vDelta = world_location - Location;
	FVector vTransformed = FVector(vDelta.dot(vAxisY), vDelta.dot(vAxisZ), vDelta.dot(vAxisX));

	if (vTransformed.z < 1.f)
		vTransformed.z = 1.f;

	float FovAngle = FOV;
	double ScreenCenterX = 1920 / 2.0f;
	double ScreenCenterY = 1080 / 2.0f;

	screen_location.x = ScreenCenterX + vTransformed.x * (ScreenCenterX / tanf(FovAngle * (double)M_PI / 360.f)) / vTransformed.z;
	screen_location.y = ScreenCenterY - vTransformed.y * (ScreenCenterX / tanf(FovAngle * (double)M_PI / 360.f)) / vTransformed.z;
	screen_location.z = 0;

	return screen_location;
}
D3DMATRIX MatrixMultiplication(D3DMATRIX pM1, D3DMATRIX pM2)
{
	D3DMATRIX pOut;
	pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
	pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
	pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
	pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
	pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
	pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
	pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
	pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
	pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
	pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
	pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
	pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
	pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
	pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
	pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
	pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;

	return pOut;
}

FTransform GetBoneIndex(DWORD_PTR mesh, int index)
{
	DWORD_PTR bonearray = device_t.read<DWORD_PTR>(mesh + offsets::BoneArray);
	if (!bonearray)
		bonearray = device_t.read<DWORD_PTR>(mesh + offsets::BoneArray + 0x10);
	
	return device_t.read<FTransform>(bonearray + (index * 0x30));
}
FVector UnrealEngine5::render::GetBoneWithRotation(DWORD_PTR mesh, int id)
{
	
	FTransform bone = GetBoneIndex(mesh, id);
	FTransform ComponentToWorld = device_t.read<FTransform>(mesh + offset); // offsets::ComponentToWorld

	D3DMATRIX Matrix;
	Matrix = MatrixMultiplication(bone.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());
	return FVector(Matrix._41, Matrix._42, Matrix._43);
}

void calc_range(float* x, float* y, float range) {
	float AbsX = math_utils::custom_fabsf(*x);
	float AbsY = math_utils::custom_fabsf(*y);

	if (AbsX > range || AbsY > range) {
		float ratio = AbsX > AbsY ? (range / AbsX) : (range / AbsY);

		*x *= ratio * ((*x > 0) ? 1 : -1);
		*y *= ratio * ((*y > 0) ? 1 : -1);
	}
}

std::string UnrealEngine5::render::GetNameFromFName(int key)
{
	auto chunkOffset = (UINT)((int)(key) >> 16);
	auto nameOffset = (USHORT)key;

	auto namePoolChunk = device_t.read<UINT64>(globals::memory::base_address + offsets::GNames + ((chunkOffset + 2) * 8));
	auto entryOffset = namePoolChunk + (ULONG)(2 * nameOffset);
	auto nameEntry = device_t.read<INT16>(entryOffset);

	auto nameLength = nameEntry >> 6;
	char buff[1028];
	if ((DWORD)nameLength && nameLength > 0)
	{
		device_t.read_array(entryOffset + 2, buff, nameLength);
		buff[nameLength] = '\0';
		return std::string(buff);
	}
	else return "NO_NAME";
}