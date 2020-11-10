#pragma once

#include <vector>

#include "emitter.hpp"
#include "program.hpp"

#include "ins/add.hpp"
#include "ins/base.hpp"
#include "ins/branch.hpp"
#include "ins/func.hpp"
#include "ins/mov.hpp"
#include "ins/stack.hpp"
#include "ins/sub.hpp"

namespace voidcore {
	struct Assembler : Add, Base, Branch, Func, Mov, Stack, Sub {
		inline void bind(Label &label) {
			Base::bind(label);
		}

		inline Program build() {
			return Program(buffer);
		}

	protected:
		intptr_t nextAddr();
		void emit(uint8_t byte);
		void patch(intptr_t loc, uint8_t byte);

	private:
		std::vector<uint8_t> buffer;
	};
}