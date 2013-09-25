#pragma once

#include <stdarg.h>
#include  <iostream> 
#include  <string>

namespace SpeechRecognizer{

	namespace utils{

		using namespace std;

		string string_format(const std::string fmt,...);

		class Uncopyable
		{
		protected:
			Uncopyable(){}
			~Uncopyable(){}

		private:
			Uncopyable(const Uncopyable&);
			Uncopyable& operator= (const Uncopyable&);
		};
	}
}