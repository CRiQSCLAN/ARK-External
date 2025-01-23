#pragma once
#include <corecrt_math_defines.h>
#include <d3d9types.h>


struct FVector {
	FVector() : x(), y(), z() {}
	FVector(double x, double y, double z) : x(x), y(y), z(z) {}

	FVector operator+ (const FVector& other) const { return { this->x + other.x, this->y + other.y, this->z + other.z }; }
	FVector operator- (const FVector& other) const { return { this->x - other.x, this->y - other.y, this->z - other.z }; }
	FVector operator* (double offset) const { return { this->x * offset, this->y * offset, this->z * offset }; }
	FVector operator/ (double offset) const { return { this->x / offset, this->y / offset, this->z / offset }; }

	FVector& operator*= (const double other) { this->x *= other; this->y *= other; this->z *= other; return *this; }
	FVector& operator/= (const double other) { this->x /= other; this->y /= other; this->z /= other; return *this; }

	FVector& operator= (const FVector& other) { this->x = other.x; this->y = other.y; this->z = other.z; return *this; }
	FVector& operator+= (const FVector& other) { this->x += other.x; this->y += other.y; this->z += other.z; return *this; }
	FVector& operator-= (const FVector& other) { this->x -= other.x; this->y -= other.y; this->z -= other.z; return *this; }
	FVector& operator*= (const FVector& other) { this->x *= other.x; this->y *= other.y; this->z *= other.z; return *this; }
	FVector& operator/= (const FVector& other) { this->x /= other.x; this->y /= other.y; this->z /= other.z; return *this; }

	operator bool() {
		return bool(this->x || this->y || this->z);
	}
	friend bool operator== (const FVector& a, const FVector& b) { return a.x == b.x && a.y == b.y && a.z == b.z; }
	friend bool operator!= (const FVector& a, const FVector& b) { return !(a == b); }

	double dot(const FVector& vector) {
		return x * vector.x + y * vector.y + z * vector.z;
	}
	double distance(FVector v) {
		return double(sqrt(pow(v.x - x, 2.0) + pow(v.y - y, 2.0) + pow(v.z - z, 2.0)));
	}
	bool IsValidAddress() const
	{
		return !(x == 0.f && y == 0.f && z == 0.f) || (x == -1.f && y == -1.f && z == -1.f);
	}

	double x, y, z;
};

//struct FCameraCacheEntry
//{
//public:
//	float	Timestamp;                                         // 0x0000(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
//	char	Pad_4[0xC];                                        // 0x0004(0x000C)(Fixing Size After Last Property [ Dumper-7 ])
//	FMinimalViewInfo	POV;                                               // 0x0010(0x08E0)(NativeAccessSpecifierPublic)
//};
struct FVector2D {
	FVector2D() : x(0), y(0) {}
	FVector2D(float x, float y) : x(x), y(y) {}

	FVector2D operator+ (const FVector2D& other) const { return { this->x + other.x, this->y + other.y }; }
	FVector2D operator- (const FVector2D& other) const { return { this->x - other.x, this->y - other.y }; }
	FVector2D operator* (float offset) const { return { this->x * offset, this->y * offset }; }
	FVector2D operator/ (float offset) const { return { this->x / offset, this->y / offset }; }

	FVector2D& operator*= (const float other) { this->x *= other; this->y *= other; return *this; }
	FVector2D& operator/= (const float other) { this->x /= other; this->y /= other; return *this; }

	FVector2D& operator= (const FVector2D& other) { this->x = other.x; this->y = other.y; return *this; }
	FVector2D& operator+= (const FVector2D& other) { this->x += other.x; this->y += other.y; return *this; }
	FVector2D& operator-= (const FVector2D& other) { this->x -= other.x; this->y -= other.y; return *this; }
	FVector2D& operator*= (const FVector2D& other) { this->x *= other.x; this->y *= other.y; return *this; }
	FVector2D& operator/= (const FVector2D& other) { this->x /= other.x; this->y /= other.y; return *this; }

	operator bool() { return bool(this->x || this->y); }
	friend bool operator== (const FVector2D& a, const FVector2D& b) { return a.x == b.x && a.y == b.y; }
	friend bool operator!= (const FVector2D& a, const FVector2D& b) { return !(a == b); }

	float distance(FVector2D v) {
		return float(sqrt(pow(v.x - x, 2.0) + pow(v.y - y, 2.0)));
	}
	bool IsValidAddress() const
	{
		return !(x == 0.f && y == 0.f) || (x == -1.f && y == -1.f);
	}

	float x, y;
};
struct FRotator
{
public:
	double Pitch = 0.f;
	double Yaw = 0.f;
	double Roll = 0.f;

	D3DMATRIX GetAxes()
	{
		auto tempMatrix = Matrix();
		return tempMatrix;
	}

	D3DMATRIX Matrix(FVector origin = FVector(0, 0, 0))
	{
		double radPitch = (Pitch * double(UCONST_PI) / 180.f);
		double radYaw = (Yaw * double(UCONST_PI) / 180.f);
		double radRoll = (Roll * double(UCONST_PI) / 180.f);
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
};

struct FMinimalViewInfo
{
	FMinimalViewInfo() : Location(), Rotation(), FOV(0.0f) {}

	FMinimalViewInfo(FVector InLocation, FRotator InRotation, float InFOV)
		: Location(InLocation), Rotation(InRotation), FOV(InFOV) {
	}

	FVector Location;
	FRotator Rotation;
	float FOV;
};

struct FCameraCacheEntry
{
	FCameraCacheEntry() : POV() {}

	FCameraCacheEntry(FMinimalViewInfo InPOV)
		: POV(InPOV) {
	}

	char pad_0x0[0x10];
	FMinimalViewInfo POV;
};



//struct FMinimalViewInfo
//{
//	FVector Location;
//	FRotator Rotation;
//	float FOV;
//};
//#pragma pack(push, 1)
//struct FCameraCacheEntry
//{
//public:
//	char pad_0x0[0x10];
//	FMinimalViewInfo POV;
//};
//#pragma pack(pop)

INLINED double degree_to_radian(double degree) {
	return degree * (M_PI / 180);
}
INLINED FRotator GetRotation(const FVector& angles)
{
	FRotator forward;
	float sp, sy, cp, cy;

	sy = sin(degree_to_radian(angles.y));
	cy = cos(degree_to_radian(angles.y));

	sp = sin(degree_to_radian(angles.x));
	cp = cos(degree_to_radian(angles.x));

	forward.Yaw = cp * sy;
	forward.Pitch = cp * cy;
	forward.Roll = -sp;

	return forward;
}

struct TArray
{
	std::uintptr_t Array;
	std::uint32_t Count;
	std::uint32_t MaxCount;

	std::uintptr_t Get(std::uint32_t Index)
	{
		return device_t.read<std::uintptr_t>(Array + (Index * 0x8));
	}
};
template<class T>
class WArray
{
public:
	int Length() const
	{
		return m_nCount;
	}

	bool IsValid() const
	{
		if (m_nCount > m_nMax)
			return false;
		if (!m_Data)
			return false;
		return true;
	}

	uint64_t GetAddress() const
	{
		return m_Data;
	}

	T GetById(int i)
	{
		return device_t.read<T>(m_Data + i * 8);
	}

protected:
	uint64_t m_Data;
	uint32_t m_nCount;
	uint32_t m_nMax;
};

struct FString : private WArray<wchar_t>
{
	std::wstring ToWString() const
	{
		wchar_t* buffer = new wchar_t[m_nCount];
		device_t.read_array(m_Data, buffer, m_nCount);
		std::wstring ws(buffer);
		delete[] buffer;

		return ws;
	}

	std::string ToString() const
	{
		std::wstring ws = ToWString();
		std::string str(ws.begin(), ws.end());

		if (str.empty())
		{
			return "EMPTY";
		}
		return str;
	}

};
struct FPlane : public FVector
{
	double W;
};

struct FMatrix {
	FPlane XPlane, YPlane, ZPlane, WPlane;

	FMatrix MatrixMultiplication(FMatrix Other) {
		FMatrix Copy = {};

		Copy.WPlane.x = this->WPlane.x * Other.XPlane.x + this->WPlane.y * Other.YPlane.x + this->WPlane.z * Other.ZPlane.x + this->WPlane.W * Other.WPlane.x;
		Copy.WPlane.y = this->WPlane.x * Other.XPlane.y + this->WPlane.y * Other.YPlane.y + this->WPlane.z * Other.ZPlane.y + this->WPlane.W * Other.WPlane.y;
		Copy.WPlane.z = this->WPlane.x * Other.XPlane.z + this->WPlane.y * Other.YPlane.z + this->WPlane.z * Other.ZPlane.z + this->WPlane.W * Other.WPlane.z;
		Copy.WPlane.W = this->WPlane.x * Other.XPlane.W + this->WPlane.y * Other.YPlane.W + this->WPlane.z * Other.ZPlane.W + this->WPlane.W * Other.WPlane.W;

		return Copy;
	}

	static FMatrix RotatorToMatrix(FVector Rotation) {
		auto ReturnValue = FMatrix();

		auto Pitch = (Rotation.x * 3.14159265358979323846 / 180);
		auto Yaw = (Rotation.y * 3.14159265358979323846 / 180);
		auto Roll = (Rotation.z * 3.14159265358979323846 / 180);

		auto sp = sin(Pitch);
		auto cp = cos(Pitch);
		auto sy = sin(Yaw);
		auto cy = cos(Yaw);
		auto sr = sin(Roll);
		auto cr = cos(Roll);

		ReturnValue.XPlane.x = cp * cy;
		ReturnValue.XPlane.y = cp * sy;
		ReturnValue.XPlane.z = sp;

		ReturnValue.YPlane.x = sr * sp * cy - cr * sy;
		ReturnValue.YPlane.y = sr * sp * sy + cr * cy;
		ReturnValue.YPlane.z = -sr * cp;

		ReturnValue.ZPlane.x = -(cr * sp * cy + sr * sy);
		ReturnValue.ZPlane.y = cy * sr - cr * sp * sy;
		ReturnValue.ZPlane.z = cr * cp;

		ReturnValue.WPlane.W = 0x1;

		return ReturnValue;
	}
};
struct FQuat
{
	float x;
	float y;
	float z;
	float w;
};

struct FTransform
{
	FQuat rot;
	FVector translation;
	char pad[4];
	FVector scale;
	char pad1[4];

	D3DMATRIX ToMatrixWithScale()
	{
		D3DMATRIX m;
		m._41 = translation.x;
		m._42 = translation.y;
		m._43 = translation.z;

		float x2 = rot.x + rot.x;
		float y2 = rot.y + rot.y;
		float z2 = rot.z + rot.z;

		float xx2 = rot.x * x2;
		float yy2 = rot.y * y2;
		float zz2 = rot.z * z2;
		m._11 = (1.0f - (yy2 + zz2)) * scale.x;
		m._22 = (1.0f - (xx2 + zz2)) * scale.y;
		m._33 = (1.0f - (xx2 + yy2)) * scale.z;

		float yz2 = rot.y * z2;
		float wx2 = rot.w * x2;
		m._32 = (yz2 - wx2) * scale.z;
		m._23 = (yz2 + wx2) * scale.y;

		float xy2 = rot.x * y2;
		float wz2 = rot.w * z2;
		m._21 = (xy2 - wz2) * scale.y;
		m._12 = (xy2 + wz2) * scale.x;

		float xz2 = rot.x * z2;
		float wy2 = rot.w * y2;
		m._31 = (xz2 + wy2) * scale.z;
		m._13 = (xz2 - wy2) * scale.x;

		m._14 = 0.0f;
		m._24 = 0.0f;
		m._34 = 0.0f;
		m._44 = 1.0f;

		return m;
	}
};

namespace customs {
	INLINED auto in_rect(double x, double y, double radius, double coord_x, double coord_y) -> bool {
		return coord_x >= x - radius && coord_x <= x + radius &&
			coord_y >= y - radius && coord_y <= y + radius;
	}

	INLINED auto in_circle(double x, double y, double radius, double coord_x, double coord_y) -> bool {
		if (in_rect(x, coord_y, radius, x, coord_y)) {
			double dx = x - coord_x;
			double dy = y - coord_y;
			dx *= dx;
			dy *= dy;
			double distance_squared = dx + dy;
			double radius_squared = radius * radius;

			return distance_squared <= radius_squared;
		}

		return false;
	}

	INLINED float degree_to_radian(float degree) {
		return degree * (M_PI / 180);
	}

	INLINED bool is_in_screen(FVector2D head_pos_dol, int width, int height) {
		if (((head_pos_dol.x <= 0 || head_pos_dol.x > width) && (head_pos_dol.y <= 0 || head_pos_dol.y > height)) || ((head_pos_dol.x <= 0 || head_pos_dol.x > width) || (head_pos_dol.y <= 0 || head_pos_dol.y > height))) {
			return false;
		}
		else {
			return true;
		}
	}
}