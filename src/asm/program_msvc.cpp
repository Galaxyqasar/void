#include "program.hpp"

#include <stdexcept>

#include <cstring>
#include <windows.h>

namespace voidcore {
	size_t Program::pageSize() {
		SYSTEM_INFO system_info;
		GetSystemInfo(&system_info);
		return system_info.dwPageSize;
	}

	void Program::map(const uint8_t *data, size_t size) {
		unmap();
		size_t pages = size / pageSize() + (size % pageSize() > 0);
		m_size = pageSize() * pages;

		if(m_size > 0) {
			m_data = (uint8_t*)VirtualAlloc(nullptr, m_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			if(m_data == nullptr) {
				m_size = 0;
				throw std::runtime_error("<Program::map> can't allocate memory!");
			}
			memcpy(m_data, data, size);
    		DWORD dummy;
			if(VirtualProtect(m_data, m_size, PAGE_EXECUTE_READ, &dummy) == 0) {
				throw std::runtime_error("<Program::map> can't protect memory!");
			}
		}
	}

	void Program::unmap() {
		if(m_data) {
			VirtualFree(m_data, 0, MEM_RELEASE);
		}
		m_data = nullptr;
		m_size = 0;
	}
}