#pragma once

#include "../emitter.hpp"
#include "../label.hpp"
#include "../x86-64.hpp"

namespace rtasm {
	struct Func : Emitter {
		void call(Label &pos);
		void call(reg64 addr);
		void ret(imm16 ds = 0);
	};
}