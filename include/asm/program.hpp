#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>

template <typename T> class funcptr_t;
template<typename R, typename... Args>
class funcptr_t<R(Args...)> {
public:
	funcptr_t(void *fptr) {
		f = reinterpret_cast<R(*)(Args...)>(fptr);
	}
	R operator()(Args... args) {
		return f(args...);
	}
	operator bool() {
		return f != nullptr;
	}

private:
	R (*f)(Args...);
};

namespace voidcore {
	class Program {
	public:
		inline Program(const std::vector<uint8_t> &code = {}) {
			map(code.data(), code.size());
		}

		inline Program(const Program &other) {
			map(other.m_data, other.m_size);
		}

		inline ~Program() {
			unmap();
		}

		inline Program& operator=(const Program &other) {
			map(other.m_data, other.m_size);
			return *this;
		}

		inline Program& operator=(const std::vector<uint8_t> &code) {
			map(code.data(), code.size());
			return *this;
		}

		inline const uint8_t* data() {
			return m_data;
		}

		inline size_t size() {
			return m_size;
		}

		template<typename F>
		funcptr_t<F> get(intptr_t offset = 0) {
			return m_data + offset;
		}

		inline std::vector<uint8_t> copy() {
			return std::vector<uint8_t>(m_data, m_data + m_size);
		}

		static size_t pageSize();

	private:
		uint8_t *m_data = nullptr;
		size_t m_size = 0;

		void map(const uint8_t *data, size_t size);
		void unmap();
	};
}