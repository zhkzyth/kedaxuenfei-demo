//os specified
#ifdef _MSC_VER
#include <Windows.h>
#ifdef _WIN64
#pragma comment(lib,"../lib/kedaxunfei/msc_x64.lib")//x64
#pragma comment(lib,"../lib/openal/Win64/OpeanAL32.lib")//x64
#else _WIN32
#pragma comment(lib,"../lib/kedaxunfei/msc.lib")//86
#pragma comment(lib,"../lib/openal/Win32/OpenAL32.lib")//86
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

//api header 
#include "SpeechRecognizer.h"
//logger
#include "logger.h"
//file handler for RAII
#include "stdioFile.h"
//helper funcs
#include "utils.h"

//xunfei specified
#include "kedaxunfei/qisr.h"
#include "errorCode.h"

namespace SpeechRecognizer {

	using namespace std;

	//TODO RAII
	SpeechRecognizer::SpeechRecognizer():
	_capture_sound_thread(NULL),
		_is_stop(false),_log(NULL),
		_result_length(0),
		_sound_result(),
		_pos_of_result(0),
		_device(NULL),
		_context(NULL),
		_capture_device(NULL),
		_device_list(NULL),
		_sess_id(NULL),
		_msg_error(NULL),
		_Buffer(),
		_out_status(NULL),
		_sError_msg(),
		_mu_result(),
		_log_file_path(NULL),
		_log_level(logger::INFO)
	{}

	SpeechRecognizer::~SpeechRecognizer()
	{
		//TODO safe destruct?
		if (  _capture_sound_thread && _capture_sound_thread->joinable() )
		{
			_stop_capture_sound_thread(_capture_sound_thread);
			delete _capture_sound_thread;
			_capture_sound_thread = NULL;
		}

		if (_capture_device)
		{
			alcCaptureCloseDevice(_capture_device);
			_capture_device = NULL;
		}

		if( _device )
		{
			_do_the_clean_job();
			_device = NULL;
		}

		if( _device_list )
		{
			delete _device_list;
			_device_list = NULL;
		}

		if(_context){
			delete _context;
			_context = NULL;
		}

		if(_log)
		{
			delete _log;
			_log = NULL;
		}

		if(_msg_error)
		{
			delete _msg_error;
			_msg_error = NULL;
		}

	}

	bool 
		SpeechRecognizer::init()
	{
		//flag show whether stop capture or not
		_is_stop = false;

		//set log file
		_log = new logger::Logger();
		try{
			//log params
			_log->set_file(_log_file_path?_log_file_path:"speechRecognizer.log");
		}
		catch(const runtime_error& r_error)
		{
			_log->error()<<r_error.what()<<endl;
			//throw;
			_out_status = SPEECHRECOGNIZER_FAIL_OTHER;
			return false;
		}

		//set log level
		_log->set_level(_log_level?_log_level:logger::INFO);

		//error msg class
		_msg_error = new errorCode::errorCode();

		//
		_out_status = SPEECHRECOGNIZER_INCOMPLETE;

		//
		_sError_msg = "错误类型不可知";

		_device_list = new  ALDeviceList();
		_device = alcOpenDevice(_device_list->GetDeviceName(0));
		if(_device==NULL)
		{
			//_openal_clean();
			_log->error()<<"Type:capture;Msg:default device not found!!"<<endl;
			_out_status = SPEECHRECOGNIZER_FAIL_OTHER;
			return false;
		}

		_context = alcCreateContext(_device, NULL);
		alcMakeContextCurrent( _context );
		if (alcIsExtensionPresent(_device, "ALC_EXT_CAPTURE") != AL_FALSE)
		{
			// Open the default Capture device
			const ALCchar* default_capture_device = alcGetString(NULL, ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER);
			_capture_device = alcCaptureOpenDevice(default_capture_device, CAPTURE_FREQUENCY, CAPTURE_BITSPERSAMPLE == 16 ? AL_FORMAT_MONO16 : AL_FORMAT_MONO8, CAPTURE_ONCEBUFFERSIZE); //默认单声道
		}
		if (!_capture_device)
		{
			//_openal_clean();
			_log->error()<<"type:capture;msg:create capture device failed!!"<<endl;
			_out_status = SPEECHRECOGNIZER_FAIL_OTHER;
			return false;
		}

		return true;
	}

	bool 
		SpeechRecognizer::startIsrListening(const char * appid,const char * isr_params){

			_log->info()<<"start Isr listening"<<endl;

			//TODO thread alread start.May _capture_sound_thread->joinable() is better.
			if( _capture_sound_thread && _capture_sound_thread->joinable()){
				return false;
			}

			//初始化讯飞语音
			int32 ret = QISRInit(appid);

			if(ret != MSP_SUCCESS)
			{
				_log->error()<<"QISRSessionInit err: "<<ret<<endl;
				_out_status = SPEECHRECOGNIZER_FAIL_OTHER;
				return false;
			}

			//capture sound params
			_sess_id = (char *)QISRSessionBegin(NULL, isr_params, &ret);//开始一路会话
			if ( MSP_SUCCESS != ret )
			{
				_log->error()<<"QISRSessionBegin err: "<<ret<<endl;
				_out_status = SPEECHRECOGNIZER_FAIL_OTHER;
				return false;
			}

			_capture_sound_thread = new boost::thread( boost::bind( &SpeechRecognizer::_capture_sound, this));

			return true;
	}

	bool 
		SpeechRecognizer::startRecogListening(const char * appid,const char* grammar,const char * recog_params){

			_log->info()<<"start Recog listening"<<endl;

			char * _grammar_buffer = NULL;
			vector<char> buffer(2048);//TODO 2k is enough?

			try
			{
				_get_grammar(grammar,buffer,&_grammar_buffer);
			}
			catch(...)
			{
				_log->error()<<"get grammmar file error"<<endl;
				_out_status = SPEECHRECOGNIZER_FAIL_OTHER;
				return false;
			}

			//初始化讯飞语音
			int32 ret = QISRInit(appid);

			if(ret != MSP_SUCCESS)
			{
				_log->error()<<"QISRSessionInit err: "<<ret<<endl;
				_out_status = SPEECHRECOGNIZER_FAIL_OTHER;
				return false;
			}


			//capture sound params
			_sess_id = (char *)QISRSessionBegin(_grammar_buffer, recog_params, &ret);//开始一路会话
			if ( MSP_SUCCESS != ret )
			{
				_log->error()<<"QISRSessionBegin err: "<<ret<<endl;
				_out_status = SPEECHRECOGNIZER_FAIL_OTHER;
				return false;
			}

			_capture_sound_thread = new boost::thread( boost::bind( &SpeechRecognizer::_capture_sound, this));

			return true;
	}

	bool 
		SpeechRecognizer::_get_grammar(const char *grammar,vector<char> &buffer,char ** _grammar_buffer)
	{
		//try catch
		try
		{
			stdioFile::stdioFile file(grammar, "r");

			int hasRead = 0;

			hasRead = file.read(buffer);

			buffer[hasRead] = '\0';

			//do the dirty cast
			*_grammar_buffer = reinterpret_cast<char*> (&buffer[0]);
		}
		catch(const runtime_error& r_error)
		{
			_log->error()<<"stdFile::"<<r_error.what()<<endl;
			throw;
			return false;
		}

		return true;
	}

	bool
		SpeechRecognizer::_capture_sound()
	{
		int32 loop_count = 0;
		ALint iSamplesAvailable = 0;
		int32 voice_status = MSP_AUDIO_SAMPLE_CONTINUE;

		int32	 ret = 0;
		int32 ep_status = -1, rec_status = -1;
		int32 rslt_status;

		bool is_sample_last_send = false;

		//status shows whether we should keep on processing
		bool result_status = true;

		// Start audio capture
		alcCaptureStart(_capture_device);

		//------------------------------阶段一：录音
		while(!_is_stop)
		{
			//set an interruption point.
			try{
				boost::this_thread::interruption_point();
			}
			catch(const boost::thread_interrupted&)
			{
				//release source
				alcCaptureStop(_capture_device);
				_log->info()<<"Thread interrupt::recording phase::_capture_device has been stopped."<<endl;

				//_do_the_clean_job();
				_log->info()<<"_stop_capture_sound_thread"<<endl;
				return false;
			}

			// Find out how many samples have been captured
			alcGetIntegerv(_capture_device, ALC_CAPTURE_SAMPLES, 1, &iSamplesAvailable);

			// When we have enough data to fill our BUFFERSIZE byte buffer, grab the samples
			if (iSamplesAvailable > (CAPTURE_ONCEBUFFERSIZE / nBlockAlign))
			{
				_log->info()<<"sending and getting data from server"<<endl;
				result_status = _send_and_get_data(CAPTURE_ONCEBUFFERSIZE,voice_status);

				if(result_status == false){
					break;
				}
			}
		}

		// Stop capture
		alcCaptureStop(_capture_device);
		_log->info()<<"_capture_device has been stopped"<<endl;

		//check whether we encounter some errors
		if(result_status == false)
		{
			//_do_the_clean_job();
			return false;
		}

		//------------------------------阶段二：发送剩下的语音包
		// Check if any Samples haven't been consumed yet
		alcGetIntegerv(_capture_device, ALC_CAPTURE_SAMPLES, 1, &iSamplesAvailable); //only ask once 

		//send buffered data
		while (iSamplesAvailable)
		{

			//set an interruption point.
			try{
				boost::this_thread::interruption_point();
			}
			catch(const boost::thread_interrupted&)
			{
				//release source
				alcCaptureStop(_capture_device);
				_log->info()<<"Thread interrupt::send bufferd data phase::_capture_device has been stopped."<<endl;

				//_do_the_clean_job();
				_log->info()<<"_stop_capture_sound_thread"<<endl;
				return false;
			}

			_log->info()<<"sending the last sample data to server."<<endl;

			if (iSamplesAvailable > (CAPTURE_ONCEBUFFERSIZE / nBlockAlign))
			{
				//sound_data_length = CAPTURE_ONCEBUFFERSIZE;
				result_status = _send_and_get_data(CAPTURE_ONCEBUFFERSIZE,voice_status);
				if(result_status == false){
					break;
				}

				iSamplesAvailable -= (CAPTURE_ONCEBUFFERSIZE / nBlockAlign);
			}
			else
			{
				voice_status = MSP_AUDIO_SAMPLE_LAST;
				is_sample_last_send = true;

				result_status = _send_and_get_data(iSamplesAvailable*nBlockAlign,voice_status);
				if(result_status == false){
					break;
				}

				iSamplesAvailable = 0;
			}
		}
		if( result_status == false)
		{
			_log->error()<<"buffered data send error"<<endl;
			//_do_the_clean_job();
			return false;
		}

		//help func to avoid none stop of sample last
		if( voice_status != MSP_AUDIO_SAMPLE_LAST)
		{
			_log->warning()<<"sample last not send.we make a fake package"<<endl;
			voice_status = MSP_AUDIO_SAMPLE_LAST;
			result_status = _send_missing_last_package(voice_status);
			if(result_status == false)
			{
				_log->warning()<<"sample last send error"<<endl;
				//_do_the_clean_job();
				return false;
			}
		}

		//------------------------------阶段三：向获取服务器轮询结果
		do 
		{
			//set an interruption point.
			try{
				boost::this_thread::interruption_point();
			}
			catch(const boost::thread_interrupted&)
			{
				//release source
				alcCaptureStop(_capture_device);
				_log->info()<<"Thread interrupt::loop for data phase::_capture_device has been stopped."<<endl;

				//_do_the_clean_job();
				_log->info()<<"_stop_capture_sound_thread"<<endl;
				return false;
			}

			_log->info()<<"get recog result back"<<endl;
			result_status = _get_data(ret,rslt_status);
			if(result_status == false)
			{
				_log->info()<<"opps,getting result back error"<<endl;
				break;
			}
			boost::this_thread::sleep(boost::posix_time::milliseconds(200));

		} while (rslt_status != MSP_REC_STATUS_COMPLETE && loop_count++ < 30);

		_log->info()<<"final result is:"<<_sound_result<<"\n"<<"and length is: "<<_result_length<<endl;


		//------------------------------阶段四：释放获取的资源
		if(result_status)
		{	
			_log->info()<<"finally get data"<<endl;
			_out_status = SPEECHRECOGNIZER_SUCCESS;
			//_do_the_clean_job();
			return true;
		}
		else
		{
			_log->info()<<"no data"<<endl;
			//_do_the_clean_job();
			_out_status = SPEECHRECOGNIZER_FAIL;
			return false;
		}
	}

	void
		SpeechRecognizer::_openal_clean()
	{
		alcMakeContextCurrent(NULL);

		alcDestroyContext(_context);

		alcCloseDevice(_device);

	}

	bool
		SpeechRecognizer::_do_the_clean_job()
	{
		int ret;

		//close openal capture
		alcCaptureCloseDevice(_capture_device);
		//release the sources
		_openal_clean();

		_log->info()<<"Type:clean; Msg:shut down device."<<endl;

		//end of qisr session
		QISRSessionEnd(_sess_id, "normal end");
		ret = QISRFini();
		if( 0 != ret )
		{
			_msg_error->formatErrorString(ret,__LINE__,_sError_msg);
			_log->error()<<_sError_msg<<endl;
			_out_status = SPEECHRECOGNIZER_FAIL_OTHER;
			return false;
		}

		return true;
	}

	bool 
		SpeechRecognizer::_send_and_get_data(int32 sound_data_length,int32 voice_status)
	{
		int32	 ret = 0;
		int32 ep_status = -1, rec_status = -1;
		int32 rslt_status = -1;
		bool result_status = true;

		// Consume Samples
		alcCaptureSamples(_capture_device, _Buffer, sound_data_length / nBlockAlign);

		//_send_data_to_server
		ret = QISRAudioWrite(_sess_id, _Buffer, sound_data_length, voice_status, &ep_status, &rec_status);

		//
		if ( ret != MSP_SUCCESS )
		{
			_msg_error->formatErrorString(ret,__LINE__,_sError_msg);
			_log->error()<<_sError_msg<<endl;
			_out_status = SPEECHRECOGNIZER_FAIL;
			return false;
			//break;
		}

		if ( rec_status == MSP_REC_STATUS_SUCCESS )
		{
			result_status = _get_data(ret,rslt_status);

			if( result_status != true )
				return false;

		}

		return true;
	}

	bool
		SpeechRecognizer::_get_data(int32& ret,int32& rslt_status){

			string str;

			const char* result = QISRGetResult(_sess_id, &rslt_status, 0, &ret);
			//
			if ( ret != MSP_SUCCESS )
			{
				_msg_error->formatErrorString(ret,__LINE__,_sError_msg);
				_log->error()<<_sError_msg<<endl;
				//TODO should be commented?
				_out_status = SPEECHRECOGNIZER_FAIL;
				return false;
			}
			else if( rslt_status == MSP_REC_STATUS_NO_MATCH )
			{
				//TODO result no match.Stop getting it or what?
				_log->warning()<<"get result nomatch"<<endl;
			}
			else
			{
				str = utils::string_format("get result[%d/%d]:\n",ret,rslt_status);
				_log->info()<<str<<endl;

				if ( result != NULL )
				{
					str =  utils::string_format("get result[%d/%d]:len:%d\n %s\n",ret,rslt_status,strlen(result),result);
					_log->info()<<str<<endl;

					{
						boost::mutex::scoped_lock lock(_mu_result);
						strcpy(_sound_result+_pos_of_result,result);
						_pos_of_result += (int32)strlen(result);
						_result_length += (int32)strlen(result);
					}

				}
			}
			return true;
	}

	bool
		SpeechRecognizer::_send_missing_last_package(int32 voice_status)
	{
		int32	 ret = 0;
		int32 ep_status = -1, rec_status = -1;
		int32 rslt_status=-1;
		int32 sound_data_length = 1;
		bool result_status = true;

		// Consume Samples
		alcCaptureSamples(_capture_device, _Buffer, sound_data_length / nBlockAlign);

		//_send_data_to_server
		ret = QISRAudioWrite(_sess_id, _Buffer, sound_data_length, voice_status, &ep_status, &rec_status);
		//
		if ( ret != MSP_SUCCESS )
		{
			_msg_error->formatErrorString(ret,__LINE__,_sError_msg);
			_log->error()<<_sError_msg<<endl;
			_out_status = SPEECHRECOGNIZER_FAIL;
			return false;
		}

		if ( rec_status == MSP_REC_STATUS_SUCCESS )
		{
			result_status = _get_data(ret,rslt_status);

			if(result_status != true)
				return false;

		}

		return true;
	}

	bool
		SpeechRecognizer::stopListening()
	{
		_is_stop = true;
		return true;
	}

	int32 
		SpeechRecognizer::getResult(char * out_result,int32 out_buffer_length,int32 &status, bool buffer_clear){

			int32 copy_length = 0;
			status = _out_status; //mark intern status

			switch( _out_status )
			{
			case SPEECHRECOGNIZER_FAIL_OTHER: //resources ref errors
				break;

			case SPEECHRECOGNIZER_INCOMPLETE:
			case SPEECHRECOGNIZER_SUCCESS:

				{
					boost::mutex::scoped_lock lock(_mu_result);

					copy_length = min(_result_length,out_buffer_length);
					memcpy(out_result, _sound_result, copy_length);

					if(buffer_clear){

						memset(_sound_result,'\0',sizeof(_sound_result));
						_result_length = 0;
						_pos_of_result = 0;

					}
				}

				break;

			default:
				return SPEECHRECOGNIZER_FAIL; //error -1
			}
			return copy_length;
	}

	bool
		SpeechRecognizer::getResultLength(int32 &result_length,int32 &status){

			{
				boost::mutex::scoped_lock lock(_mu_result);
				result_length = _result_length;
				status  = _out_status; //mark intern status
			}

			return true;
	}

	int32
		SpeechRecognizer::getError(char * error_str,int32 out_buffer_length)
	{
		int32 copy_length = 0;

		try{
			copy_length = _sError_msg.copy(error_str,out_buffer_length);
		}
		catch(...)
		{
			return -1;
		}

		return copy_length;
	}

	bool 
		SpeechRecognizer::set_logger_params(const char * log_path,int32 log_level)
	{
		_log_file_path = log_path;
		_log_level = log_level;
		return true;
	}

	bool SpeechRecognizer::_stop_capture_sound_thread(boost::thread* capture_sound_thread)
	{
		//interrupt request
		_capture_sound_thread->interrupt();

		//set an interruption point.
		try{
			//interuption point
			_capture_sound_thread->join();
			_log->info()<<"Thread has completed.No need to interupt."<<endl;
		}
		catch(const boost::thread_interrupted&)
		{
			//release source
			alcCaptureStop(_capture_device);
			_log->info()<<"Thread interrupt::destructor phase::_capture_device has been stopped."<<endl;
			_log->info()<<"_stop_capture_sound_thread"<<endl;
		}

		return true;
	}


	//TODO ********or just delete it and restart a new one may be better.********
	//bool get_capture_sound_thread_status(int32& thread_status)
	//{
	//	thread_status = _thread_status;

	//	return true;
	//}
	//
	//bool stop_capture_sound_thread()
	//{
	//	if (  _capture_sound_thread && _capture_sound_thread->joinable() )
	//	{
	//		try
	//		{
	//			_log->info()<<"Begin to stop capture sound thread."<<endl;
	//			_stop_capture_sound_thread(_capture_sound_thread); //block the call thread
	//			_log->info()<<"Success to stop capture sound thread."<<endl;
	//		}
	//		catch(...)
	//		{
	//			//should not happen
	//			_log->error()<<"stop_capture_sound_thread failed."<<endl;
	//			throw;
	//		}

	//		//do the clean job
	//		delete _capture_sound_thread;
	//		_capture_sound_thread = NULL;

	//		_reset_init_vars();

	//		//
	//		return true;
	//	}
	//
	//	//thred has been stopped or not begin yet?
	//	return true;
	//}

	//bool _reset_init_vars()
	//{
	//	//FIXME set location.
	//	//reset the thread status
	//	_thread_status = SPEECHRECOGNIZER_THREAD_STOP;

	//	//flag show whether stop capture or not
	//	_is_stop = false;

	//	//
	//	_out_status = SPEECHRECOGNIZER_INCOMPLETE;

	//	//
	//	_sError_msg = "错误类型不可知";

	//	//
	//	memset(_sound_result,'\0',sizeof(_sound_result));
	//	_result_length = 0;
	//	_pos_of_result = 0;

	//	//more??

	//	return true;
	//}
}