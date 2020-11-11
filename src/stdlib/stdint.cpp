#include "stdint.hpp"

namespace voidcore {
	namespace stdint {
		void Int8TypeDecl::dump(std::ostream &out, uint32_t offset) const {
			out<<std::string(offset * 2, ' ')<<"<int8-typedecl>\n";
		}
		void Int8TypeDecl::build(Assembler *out) {}
		std::string Int8TypeDecl::name() const {
			return "int8";
		}
		std::string Int8TypeDecl::signature() const {
			return "int8";
		}
		bool Int8TypeDecl::isInline() const {
			return true;
		}
		size_t Int8TypeDecl::size() const {
			return 1;
		}

		void UInt8TypeDecl::dump(std::ostream &out, uint32_t offset) const {
			out<<std::string(offset * 2, ' ')<<"<uint8-typedecl>\n";
		}
		void UInt8TypeDecl::build(Assembler *out) {}
		std::string UInt8TypeDecl::name() const {
			return "uint8";
		}
		std::string UInt8TypeDecl::signature() const {
			return "uint8";
		}
		bool UInt8TypeDecl::isInline() const {
			return true;
		}
		size_t UInt8TypeDecl::size() const {
			return 1;
		}

		void Int16TypeDecl::dump(std::ostream &out, uint32_t offset) const {
			out<<std::string(offset * 2, ' ')<<"<int16-typedecl>\n";
		}
		void Int16TypeDecl::build(Assembler *out) {}
		std::string Int16TypeDecl::name() const {
			return "int16";
		}
		std::string Int16TypeDecl::signature() const {
			return "int16";
		}
		bool Int16TypeDecl::isInline() const {
			return true;
		}
		size_t Int16TypeDecl::size() const {
			return 2;
		}

		void UInt16TypeDecl::dump(std::ostream &out, uint32_t offset) const {
			out<<std::string(offset * 2, ' ')<<"<uint16-typedecl>\n";
		}
		void UInt16TypeDecl::build(Assembler *out) {}
		std::string UInt16TypeDecl::name() const {
			return "uint16";
		}
		std::string UInt16TypeDecl::signature() const {
			return "uint16";
		}
		bool UInt16TypeDecl::isInline() const {
			return true;
		}
		size_t UInt16TypeDecl::size() const {
			return 2;
		}

		void Int32TypeDecl::dump(std::ostream &out, uint32_t offset) const {
			out<<std::string(offset * 2, ' ')<<"<int32-typedecl>\n";
		}
		void Int32TypeDecl::build(Assembler *out) {}
		std::string Int32TypeDecl::name() const {
			return "int32";
		}
		std::string Int32TypeDecl::signature() const {
			return "int32";
		}
		bool Int32TypeDecl::isInline() const {
			return true;
		}
		size_t Int32TypeDecl::size() const {
			return 4;
		}
		void UInt32TypeDecl::dump(std::ostream &out, uint32_t offset) const {
			out<<std::string(offset * 2, ' ')<<"<uint32-typedecl>\n";
		}
		void UInt32TypeDecl::build(Assembler *out) {}
		std::string UInt32TypeDecl::name() const {
			return "uint32";
		}
		std::string UInt32TypeDecl::signature() const {
			return "uint32";
		}
		bool UInt32TypeDecl::isInline() const {
			return true;
		}
		size_t UInt32TypeDecl::size() const {
			return 4;
		}

		void Int64TypeDecl::dump(std::ostream &out, uint32_t offset) const {
			out<<std::string(offset * 2, ' ')<<"<int64-typedecl>\n";
		}
		void Int64TypeDecl::build(Assembler *out) {}
		std::string Int64TypeDecl::name() const {
			return "int64";
		}
		std::string Int64TypeDecl::signature() const {
			return "int64";
		}
		bool Int64TypeDecl::isInline() const {
			return true;
		}
		size_t Int64TypeDecl::size() const {
			return 8;
		}

		void UInt64TypeDecl::dump(std::ostream &out, uint32_t offset) const {
			out<<std::string(offset * 2, ' ')<<"<uint64-typedecl>\n";
		}
		void UInt64TypeDecl::build(Assembler *out) {}
		std::string UInt64TypeDecl::name() const {
			return "uint64";
		}
		std::string UInt64TypeDecl::signature() const {
			return "uint64";
		}
		bool UInt64TypeDecl::isInline() const {
			return true;
		}
		size_t UInt64TypeDecl::size() const {
			return 8;
		}

		Module generateModule() {
			ASTContext context;
			RootStmt *root = context.root();
			root->append(context.addNode<Int8TypeDecl>());
			root->append(context.addNode<UInt8TypeDecl>());
			root->append(context.addNode<Int16TypeDecl>());
			root->append(context.addNode<UInt16TypeDecl>());
			root->append(context.addNode<Int32TypeDecl>());
			root->append(context.addNode<UInt32TypeDecl>());
			root->append(context.addNode<Int64TypeDecl>());
			root->append(context.addNode<UInt64TypeDecl>());
			return Module(std::move(context));
		}
	}
}