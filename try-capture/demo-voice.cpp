#define _CRT_SECURE_NO_WARNINGS
#define  _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

//test for our api
#include "../include/SpeechRecognizer.h"

//
using namespace std;
namespace SpeRec = SpeechRecognizer;

int 
_tmain(int argc, _TCHAR* argv[])
{
	const char * appid = "appid=5201a7cd";
	SpeRec::SpeechRecognizer* speech;
	char result[1000] = {"\0"};
	int32 BUFFER_LENGTH = 1000;
	int32 status;
	int32 byte_copy=-1;
	int32 max_try=0;
	bool clear_buffer = false;
	const char* isr_params = "rst=plain,sub=iat,ssm=1,aue=speex-wb;7,auf=audio/L16;rate=16000,ent=sms16k";//设置会话参数
	const char* recog_params = "rst=plain,sub=asr,ssm=1,aue=speex-wb;7,auf=audio/L16;rate=16000,grt=abnf";//注意sub=asr,grt=abnf
	const char * grammar = "abnf/alishanlongdan.abnf";
	//const char * grammar = "abnf/noexit.abnf";
	//const char * grammar = "abnf\kedaxunfei-long.abnf";
	//const char * grammar = "abnf\gm_continuous_digit.abnf";
	bool fun_status = false;

	//TODO 
	try{
		//
		//speech = new SpeRec::SpeechRecognizer(); 

		//
		std::auto_ptr<SpeRec::SpeechRecognizer> speech( SpeRec::createSpeechRecognizer());

		try{
			speech->set_logger_params("abc.log",SpeRec::logger::INFO);//path and level
		}
		catch(const std::runtime_error& e)
		{
			//file not exit thrown!
			//e.what();
		}

		fun_status = speech->init();
		if( fun_status != true )
		{
			//check log
			return -1;
		}

		////when user click or some evt happens,start listening
		//fun_status = speech->startIsrListening(appid,isr_params);
		fun_status = speech->startRecogListening(appid,grammar,recog_params);
		if( fun_status != true )
		{
			//start listening error
			//may need to check log to find out reasons
			return -1;
		}

		Sleep(1000);//record 1 second

		//when user click stop or the time was too long,we stop listening
		fun_status = speech->stopListening();
		if( fun_status != true )
		{
			//stop listening error
			//may use getError to find out reasons
			return -1;
		}

		//get result
		do{

			Sleep(1000); //sleeptime can be changed

			byte_copy = speech->getResult(result,BUFFER_LENGTH,status,clear_buffer);
			cout<<"API:: "<<"byte buffer.byte_copy: "<<byte_copy<<". status is: "<<status<<endl;

			if( status == SpeRec::SPEECHRECOGNIZER_SUCCESS ){
				cout<<"API:: "<<"data length in byte(s): "<<byte_copy<<" || result is: "<<result<<endl;
				break;
			}else{
				if(status == SpeRec::SPEECHRECOGNIZER_FAIL)
				{
					byte_copy = speech->getError(result,BUFFER_LENGTH);
					cout<<"API:: "<<"Error! Length: "<<byte_copy<<" Result:"<<result<<endl;
					break;
				}
				else if( status == SpeRec::SPEECHRECOGNIZER_FAIL_OTHER )
				{
					//
				}
			}
		}while( max_try++ < 5);
	}
	catch(...){
		printf("exception in main loop");
	}

	//delete speech;

	cout<<"API:: "<<"API call done."<<endl;

	char key = _getch();
	return 0;
}