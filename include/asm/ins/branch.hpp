#pragma once

#include "../emitter.hpp"
#include "../label.hpp"
#include "../x86-64.hpp"

namespace voidcore {
	struct Branch : Emitter {
		void jmp(imm32 offset);
		void jmp(Label *label);
	};
}