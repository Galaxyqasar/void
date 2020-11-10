#include "program.hpp"

#include <stdexcept>

#include <cstring>
#include <unistd.h>
#include <sys/mman.h>

namespace voidcore {
	size_t Program::pageSize() {
		return sysconf(_SC_PAGE_SIZE);
	}
	void Program::map(const uint8_t *data, size_t size) {
		unmap();
		size_t pages = size / pageSize() + (size % pageSize() > 0);
		m_size = pageSize() * pages;

		if(m_size > 0) {
			m_data = (uint8_t*)mmap(nullptr, size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS ,-1, 0);
			if(m_data == MAP_FAILED) {
				m_data = nullptr;
				m_size = 0;
				throw std::runtime_error("<Program::map> can't allocate memory!");
			}
			memcpy(m_data, data, size);
			if(mprotect(m_data, m_size, PROT_READ | PROT_EXEC) == -1) {
				throw std::runtime_error("<Program::map> can't protect memory!");
			}
		}
	}

	void Program::unmap() {
		if(m_data) {
			munmap(m_data, m_size);
		}
		m_data = nullptr;
		m_size = 0;
	}
}