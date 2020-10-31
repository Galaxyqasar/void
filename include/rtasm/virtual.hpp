#pragma once

#include "emitter.hpp"
#include "ins/base.hpp"
#include "ins/mov.hpp"
#include "ins/stack.hpp"

namespace rtasm {
	struct VirtualAssembler : Base, Mov, Stack {
		inline void bind(Label &label) {
			Base::bind(label);
		}
	};
}