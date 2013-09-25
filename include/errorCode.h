#pragma once

#include <string>

namespace SpeechRecognizer{

	namespace errorCode{

		using namespace std;

		class errorCode
		{
		public:
			errorCode(void);
			void formatErrorString(int nRet,int line , string &str);
			bool exist;
		protected:
			bool getErrorString(int errorCode , string &strEn , string &strCn );
		public:
			~errorCode(void);
		};
	}
}