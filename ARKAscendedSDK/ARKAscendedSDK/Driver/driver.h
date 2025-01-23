#pragma once 
#include <Windows.h>
#include <iostream>
#include <queue>

#include "interface.h"
namespace Memory
{
	inline uint64_t ModuleBaseAddress = 0;
	inline DWORD ProcessID = 0;
	inline HANDLE ProcessHandle = 0;
}

namespace m_ue
{
	class interface_t
	{
		HANDLE m_handle;

	public:
		int m_pid;

		uintptr_t m_base;

		uintptr_t m_peb;

	public:

		bool start_service();

		std::uintptr_t get_module_base(const char* module_name);
		static interface_t& get_instance()
		{
			static interface_t instance;
			return instance;
		}
		bool send_cmd(void* data, requests code);
		bool is_mapped(int proc);
		bool resolve_dtb();

		bool write(const std::uintptr_t address, void* buffer, const std::size_t size);

		// write template
		template <typename t>
		bool write(const std::uintptr_t address, t value)
		{
			return this->write(address, &value, sizeof(t));
		}

		bool is_valid( const uint64_t adress )
		{
			if ( adress <= 0x400000 || adress == 0xCCCCCCCCCCCCCCCC || reinterpret_cast< void* >( adress ) == nullptr || adress >
				0x7FFFFFFFFFFFFFFF ) {
				return false;
			}

			return true;
		}

		template<typename T>
		bool read_large_array( uint64_t address, T out[], size_t len )
		{
			size_t real_size = sizeof( T ) * len;
			size_t read_size = 0;
			T* temp = out;  // Temporary pointer to keep track of the current position in the out array

			while ( read_size < real_size ) {
				BYTE* buffer = new BYTE[512];

				size_t diff = real_size - read_size;
				if ( diff > 512 )
					diff = 512;

				this->read( address + read_size, buffer, diff );

				memcpy( temp, buffer, diff );

				read_size += diff;
				temp += ( diff / sizeof( T ) );

				delete[] buffer;
			}

			return true;
		}

		bool read(const std::uintptr_t address, void* buffer, const std::size_t size); 
		// read template
		template <typename t>
		t read(const std::uintptr_t address)
		{
			t response{ };
			this->read(address, &response, sizeof(t));
			return response;
		}
		template <typename T>
		T read_value(const uintptr_t address) {
			T value = T();
			if (this->read(address, &value, sizeof(T)))
				return value;
		}
		template <typename R> R Read1(uint64_t address)
		{
			R value = R();
			if (ReadProcessMemory(Memory::ProcessHandle, (LPCVOID)address, &value, sizeof(R), NULL))
				return value;
		}
		template<typename T>
		std::string read_string(uintptr_t address)
		{
			char buffer[70];
			this->read(address, &buffer, sizeof(buffer));
			int a_size = sizeof(buffer) / sizeof(char);
			std::string nameString;
			for (int i = 0; i < 70; i += 2) {
				if (buffer[i] == 0)
					break;
				else
					nameString += buffer[i];
			};
			return nameString;
		}

		std::string read_ascii(uint64_t adr)
		{
			char buf[64] = { 0 };
			this->read(adr, &buf, 64);
			return buf;
		}
		std::string read_ascii_2(uint64_t adr)
		{
			char buffer[64] = { 0 };  // Adjust buffer size if needed

			// Read the memory content into the buffer
			this->read(adr, &buffer, sizeof(buffer));

			// Convert buffer to a null-terminated string
			std::string result;
			for (int i = 0; i < sizeof(buffer); i++) {
				if (buffer[i] == 0) {
					break;  // Stop if a null character is found
				}
				result += buffer[i];  // Append each character to the result string
			}

			return result;
		}

		// read array template
		template<typename T>
		bool read_array(uint64_t address, T out[], size_t len)
		{
			return this->read(address, (uint8_t*)out, sizeof(T) * len) == 0;
		}
	};
}
#define INLINED inline
inline m_ue::interface_t device_t;