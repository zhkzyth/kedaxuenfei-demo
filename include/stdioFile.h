#pragma once

#include <iostream> 
#include <vector>

namespace SpeechRecognizer{

	namespace stdioFile{

		using namespace std;

		class stdioFile {
			FILE* file_;
			std::string mode_;

			static FILE* fcheck(FILE* stream){
				if (!stream)
					throw std::runtime_error("Cannot open file");
				return stream;
			}

			FILE* fdup() const;

		public:
			stdioFile(char const* name, char const* mode);

			stdioFile(stdioFile const& rhs);

			~stdioFile();

			stdioFile& operator=(stdioFile const& rhs);

			int read(std::vector<char>& buffer);

			int write(std::vector<char> const& buffer);

		};

	}
}