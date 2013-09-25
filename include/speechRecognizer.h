//sound record specified
#pragma once

//std
#include <string>
#include <queue>

//boost
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

//
#include "errorCode.h"
//
#include "logger.h"
//
#include "stdioFile.h"
//
#include "utils.h"

//type specified
#ifdef _MSC_VER

typedef	__int8				int8;
typedef	__int16				int16;
typedef	__int32				int32;
typedef	__int64				int64;

typedef	unsigned __int8		uint8;
typedef	unsigned __int16	uint16;
typedef	unsigned __int32	uint32;
typedef	unsigned __int64	uint64;

#else

#include <stdint.h>

#endif

#ifdef _WIN64
//define something for Windows (64-bit)
//FIXME WIN64?
//#include <al.h>
//#include <alc.h>
//#include "../include/openal1.1/Win32/aldlist.h"
#elif _WIN32
//openal
#include <al.h>
#include <alc.h>
#include "../include/openal1.1/Win32/aldlist.h"
//TODO cross platform
#elif __APPLE__
//
#elif __linux
// linux
#elif __unix // all unices not caught above
// Unix
#elif __posix
// POSIX
#endif

namespace SpeechRecognizer{

	//返回结果的状态码 
	enum
	{
		SPEECHRECOGNIZER_SUCCESS = 1, //结果返回成功
		//SPEECHRECOGNIZER_NO_DATA = 2,	//没有数据
		SPEECHRECOGNIZER_INCOMPLETE = 3, //结果获取当中
		SPEECHRECOGNIZER_FAIL_OTHER = 4, //其他错误，资源初始化等其他相关操作
		SPEECHRECOGNIZER_FAIL = -1, //数据获取相关错误，错误信息通过getError接口拿
	};

	enum
	{
		SPEECHRECOGNIZER_THREAD_STOP = 0,
		SPEECHRECOGNIZER_THREAD_RUNNING = 1,
	};

	//sound params
	const int32 CAPTURE_FREQUENCY	= 16000;
	const int32 CAPTURE_ONCEBUFFERSIZE	= 4410;//one sound package size
	const int32 CAPTURE_BITSPERSAMPLE = 16;
	const int32 CAPTURE_NChannels  = 1;
	const int32	nBlockAlign = CAPTURE_NChannels * CAPTURE_BITSPERSAMPLE / 8;

	//sound result length
	const int32 CAPTURE_RESULTLENGTH = 1024;

	//name space
	using namespace std;

	class SpeechRecognizer:private utils::Uncopyable{

	public:
		SpeechRecognizer();
		~SpeechRecognizer();

		bool init();

		bool startIsrListening(const char * appid,const char * isr_params);
		bool startRecogListening(const char * appid,const char* grammar,const char * recog_params);

		bool stopListening();

		int32 getResult(char *result,int32 buffer_length,int32 &status,bool buffer_clear);
		bool getResultLength(int32 &result_length,int32 &status);
		int32 getError(char * error_str,int32 out_buffer_length);

		//
		bool set_logger_params(const char * log_path,int32 log_level);

		//TODO 
		bool get_capture_sound_thread_status(int32& thread_status);
		bool stop_capture_sound_thread();

		////factory func
		//static SpeechRecognizer* createSpeechRecognizer()
		//{
		//	return  new SpeechRecognizer();
		//}

		//TODO
		//bool destory();

	private:

		bool _capture_sound();

		bool _send_and_get_data(int32 sound_data_length,int32 voice_status);
		bool _get_data(int32& ret,int32& rslt_status);
		bool _send_missing_last_package(int32 voice_status);

		void _openal_clean();
		bool _do_the_clean_job();

		//
		bool _get_grammar(const char* filename,vector<char> &buffer,char ** _grammar_buffer);

		//
		bool _stop_capture_sound_thread(boost::thread* capture_sound_thread);

	private:

		boost::thread* _capture_sound_thread;

		//线程停止标志位
		bool _is_stop;

		//日志助手
		logger::Logger * _log;

		//openal sound captures
		int32 _result_length;
		ALchar _sound_result[CAPTURE_RESULTLENGTH];
		int32 _pos_of_result;

		//openal
		ALCdevice*  _device;
		ALCcontext* _context;
		ALCdevice* _capture_device;	// 录音设备
		ALDeviceList* _device_list;

		//一次会话的id
		char* _sess_id;

		//错误信息助手
		errorCode::errorCode * _msg_error;

		//capture sound buffer
		ALchar _Buffer[CAPTURE_ONCEBUFFERSIZE];

		//outside API
		int32 _out_status;

		//error msg
		string _sError_msg;

		//read write result buffer mutex
		boost::mutex _mu_result;

		//logger params
		const char * _log_file_path;
		int32 _log_level;

		//
		//int32 _thread_status;
	};


	//factory func
	static SpeechRecognizer* createSpeechRecognizer()
	{
		//TODO error safety
		return  new SpeechRecognizer();
	}
}