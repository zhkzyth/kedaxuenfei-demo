#include "stdioFile.h"

#ifdef _MSC_VER
//win32 or win64
#include <io.h>
#ifdef _WIN64
//
#else _WIN32
//
#endif
//TODO cross platform
#elif __APPLE__
//apple os
#elif __linux
// linux
#elif __unix // all unices not caught above
// Unix
#elif __posix
// POSIX
#endif


namespace SpeechRecognizer{

	namespace stdioFile{

		FILE* stdioFile::fdup() const {
			int dupfd(dup(fileno(file_)));
			if (dupfd == -1)
				throw std::runtime_error("Cannot dup file descriptor");
			return fdopen(dupfd, mode_.c_str());
		}

		stdioFile::stdioFile(char const* name, char const* mode)
			: file_(fcheck(fopen(name, mode))), mode_(mode)
		{
		}

		//copy constructor
		stdioFile::stdioFile(stdioFile const& rhs)
			: file_(fcheck(rhs.fdup())), mode_(rhs.mode_)
		{
		}

		stdioFile::~stdioFile()
		{
			fclose(file_);
		}

		//assign constructor
		//TODO less a mode_ assign?
		stdioFile& stdioFile::operator=(stdioFile const& rhs) {
			FILE* dupstr = fcheck(rhs.fdup());
			if (fclose(file_) == EOF) {
				fclose(dupstr); // XXX ignore failed close
				throw std::runtime_error("Cannot close stream");
			}
			
			file_ = dupstr;
			mode_ = rhs.mode_;

			return *this;
		}

		int
			stdioFile::read(std::vector<char>& buffer)
		{
			int result(fread(&buffer[0], 1, buffer.size(), file_));
			if (ferror(file_))
				throw std::runtime_error(strerror(errno));
			return result;
		}

		int
			stdioFile::write(std::vector<char> const& buffer)
		{
			int result(fwrite(&buffer[0], 1, buffer.size(), file_));
			if (ferror(file_))
				throw std::runtime_error(strerror(errno));
			return result;
		}

	}
}