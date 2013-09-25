#include "errorCode.h"
#include "kedaxunfei/msp_types.h"
#include "utils.h"

namespace SpeechRecognizer{

	namespace errorCode{

		errorCode::errorCode(void):exist(false)
		{
		}

		errorCode::~errorCode(void)
		{
		}

		void errorCode::formatErrorString(int nRet,int line , string &str)
		{
			string strEn="null",strCn="��";

			if(true == getErrorString(nRet,strEn,strCn))//���������
			{
				//TODO string type in var_list has bugs.Dirty workaround here.
				const char *cstrEn  = strEn.c_str();
				const char *cstrCn  = strCn.c_str();
				str = utils::string_format("error %d:line %d, %s, %s\n",nRet,line,cstrEn,cstrCn);
			}
		}

		bool errorCode::getErrorString(int errorCode , string &strEn , string &strCn)
		{
			if(exist)	return false;

			if(errorCode==MSP_SUCCESS)
			{
				strCn="�ɹ�";
				strEn="MSP_SUCCESS";
				exist=false;
				return true;
			}

			exist=true;

			switch(errorCode)
			{
			case MSP_ERROR_FAIL:
				strCn="ʧ��";
				strEn="MSP_ERROR_FAIL";
				break;
			case MSP_ERROR_EXCEPTION:
				strCn="�쳣";
				strEn="MSP_ERROR_EXCEPTION";
				break;

			case MSP_ERROR_GENERAL:
				strCn="����";
				strEn="MSP_ERROR_GENERAL";
				break;
			case MSP_ERROR_OUT_OF_MEMORY:
				strCn="�ڴ�Խ��";
				strEn="MSP_ERROR_OUT_OF_MEMORY";
				break;
			case MSP_ERROR_FILE_NOT_FOUND:
				strCn="û���ҵ��ļ�";
				strEn="MSP_ERROR_FILE_NOT_FOUND";
				break;
			case MSP_ERROR_NOT_SUPPORT:
				strCn="��֧��";
				strEn="MSP_ERROR_NOT_SUPPORT";
				break;
			case MSP_ERROR_NOT_IMPLEMENT:
				strCn="û��ʵ��";
				strEn="MSP_ERROR_NOT_IMPLEMENT";
				break;
			case MSP_ERROR_ACCESS:
				strCn="û��Ȩ��";
				strEn="MSP_ERROR_ACCESS";
				break;
			case MSP_ERROR_INVALID_PARA:
				strCn="��Ч�Ĳ���";
				strEn="MSP_ERROR_INVALID_PARA";
				break;
			case MSP_ERROR_INVALID_PARA_VALUE:
				strCn="��Ч�Ĳ���ֵ";
				strEn="MSP_ERROR_INVALID_PARA_VALUE";
				break;
			case MSP_ERROR_INVALID_HANDLE:
				strCn="��Ч�ľ��";
				strEn="MSP_ERROR_INVALID_HANDLE";
				break;
			case MSP_ERROR_INVALID_DATA:
				strCn="��Ч������";
				strEn="MSP_ERROR_INVALID_DATA";
				break;
			case MSP_ERROR_NO_LICENSE:
				strCn="û����Ȩ���";
				strEn="MSP_ERROR_NO_LICENSE";
				break;
			case MSP_ERROR_NOT_INIT:
				strCn="û�г�ʼ��";
				strEn="MSP_ERROR_NOT_INIT";
				break;
			case MSP_ERROR_NULL_HANDLE:
				strCn="��Ч��Session ID";
				strEn="MSP_ERROR_NULL_HANDLE";
				break;
			case MSP_ERROR_OVERFLOW:
				strCn="���";
				strEn="MSP_ERROR_OVERFLOW";
				break;
			case MSP_ERROR_TIME_OUT:
				strCn="��ʱ";
				strEn="MSP_ERROR_TIME_OUT";
				break;
			case MSP_ERROR_OPEN_FILE:
				strCn="���ļ�����";
				strEn="MSP_ERROR_OPEN_FILE";
				break;
			case MSP_ERROR_NOT_FOUND:
				strCn="û�з���";
				strEn="MSP_ERROR_NOT_FOUND";
				break;
			case MSP_ERROR_NO_ENOUGH_BUFFER:
				strCn="û���㹻�ڴ�";
				strEn="MSP_ERROR_NO_ENOUGH_BUFFER";
				break;
			case MSP_ERROR_NO_DATA:
				strCn="û������";
				strEn="MSP_ERROR_NO_DATA";
				break;
			case MSP_ERROR_NO_MORE_DATA:
				strCn="û�и�������";
				strEn="MSP_ERROR_NO_MORE_DATA";
				break;
				//case MSP_ERROR_SKIPPED:
				//	strCn="����";
				//	strEn="MSP_ERROR_SKIPPED";
				//	break;
			case MSP_ERROR_ALREADY_EXIST:
				strCn="�Ѿ�����";
				strEn="MSP_ERROR_ALREADY_EXIST";
				break;
			case MSP_ERROR_LOAD_MODULE:
				strCn="����ģ��ʧ��";
				strEn="MSP_ERROR_LOAD_MODULE";
				break;
			case MSP_ERROR_BUSY:
				strCn="æµ";
				strEn="MSP_ERROR_BUSY";
				break;
			case MSP_ERROR_INVALID_CONFIG:
				strCn="��Ч��������";
				strEn="MSP_ERROR_INVALID_CONFIG";
				break;
			case MSP_ERROR_VERSION_CHECK:
				strCn="�汾����";
				strEn="MSP_ERROR_VERSION_CHECK";
				break;
			case MSP_ERROR_CANCELED:
				strCn="ȡ��";
				strEn="MSP_ERROR_CANCELED";
				break;
			case MSP_ERROR_INVALID_MEDIA_TYPE:
				strCn="��Ч��ý������";
				strEn="MSP_ERROR_INVALID_MEDIA_TYPE";
				break;
			case MSP_ERROR_CONFIG_INITIALIZE:
				strCn="��ʼ��ʧ��";
				strEn="MSP_ERROR_CONFIG_INITIALIZE";
				break;
			case MSP_ERROR_CREATE_HANDLE:
				strCn="�����������";
				strEn="MSP_ERROR_CREATE_HANDLE";
				break;
			case MSP_ERROR_CODING_LIB_NOT_LOAD:
				strCn="������δ����";
				strEn="MSP_ERROR_CODING_LIB_NOT_LOAD";
				break;

			case MSP_ERROR_NET_GENERAL:
				strCn="����һ�����";
				strEn="MSP_ERROR_NET_GENERAL";
				break;
			case MSP_ERROR_NET_OPENSOCK:
				strCn="������׽��ִ���";
				strEn="MSP_ERROR_NET_OPENSOCK";
				break;
			case MSP_ERROR_NET_CONNECTSOCK:
				strCn="�����׽������Ӵ���";
				strEn="MSP_ERROR_NET_CONNECTSOCK";
				break;
			case MSP_ERROR_NET_ACCEPTSOCK:
				strCn="�����׽�����Ӧ����";
				strEn="MSP_ERROR_NET_ACCEPTSOCK";
				break;
			case MSP_ERROR_NET_SENDSOCK:
				strCn="�����׽��ַ��ʹ���";
				strEn="MSP_ERROR_NET_SENDSOCK";
				break;
			case MSP_ERROR_NET_RECVSOCK:
				strCn="�����׽��ֽ��մ���";
				strEn="MSP_ERROR_NET_RECVSOCK";
				break;
			case MSP_ERROR_NET_INVALIDSOCK:
				strCn="������Ч���׽���";
				strEn="MSP_ERROR_NET_INVALIDSOCK";
				break;
			case MSP_ERROR_NET_BADADDRESS:
				strCn="������Ч�ĵ�ַ";
				strEn="MSP_ERROR_NET_BADADDRESS";
				break;
			case MSP_ERROR_NET_BINDSEQUENCE:
				strCn="����󶨴������";
				strEn="MSP_ERROR_NET_BINDSEQUENCE";
				break;
			case MSP_ERROR_NET_NOTOPENSOCK:
				strCn="�����׽���û�д�";
				strEn="MSP_ERROR_NET_NOTOPENSOCK";
				break;
			case MSP_ERROR_NET_NOTBIND:
				strCn="����û�а�";
				strEn="MSP_ERROR_NET_NOTBIND";
				break;
			case MSP_ERROR_NET_NOTLISTEN:
				strCn="����û�м���";
				strEn="MSP_ERROR_NET_NOTLISTEN";
				break;
			case MSP_ERROR_NET_CONNECTCLOSE:
				strCn="�������ӹر�";
				strEn="MSP_ERROR_NET_CONNECTCLOSE";
				break;
			case MSP_ERROR_NET_NOTDGRAMSOCK:
				strCn="��������ݱ��׽���";
				strEn="MSP_ERROR_NET_NOTDGRAMSOCK";
				break;
			case MSP_ERROR_NET_DNS:
				strCn="DNS��������";
				strEn="MSP_ERROR_NET_DNS";
				break;

			case MSP_ERROR_REC_GENERAL:
				strCn="RECһ�����";
				strEn="MSP_ERROR_REC_GENERAL";
				break;
			case MSP_ERROR_REC_INACTIVE:
				strCn="REC���ڲ���Ծ״̬";
				strEn="MSP_ERROR_REC_INACTIVE";
				break;
			case MSP_ERROR_REC_GRAMMAR_ERROR:
				strCn="REC�﷨����";
				strEn="MSP_ERROR_REC_GRAMMAR_ERROR";
				break;
			case MSP_ERROR_REC_NO_ACTIVE_GRAMMARS:
				strCn="RECû�л�Ծ���﷨";
				strEn="MSP_ERROR_REC_NO_ACTIVE_GRAMMARS";
				break;
			case MSP_ERROR_REC_DUPLICATE_GRAMMAR:
				strCn="REC�﷨�ظ�";
				strEn="MSP_ERROR_REC_DUPLICATE_GRAMMAR";
				break;
			case MSP_ERROR_REC_INVALID_MEDIA_TYPE:
				strCn="REC��Ч��ý������";
				strEn="MSP_ERROR_REC_INVALID_MEDIA_TYPE";
				break;
			case MSP_ERROR_REC_INVALID_LANGUAGE:
				strCn="REC��Ч������";
				strEn="MSP_ERROR_REC_INVALID_LANGUAGE";
				break;
			case MSP_ERROR_REC_URI_NOT_FOUND:
				strCn="RECû�ж�Ӧ��URI";
				strEn="MSP_ERROR_REC_URI_NOT_FOUND";
				break;
			case MSP_ERROR_REC_URI_TIMEOUT:
				strCn="REC��ȡURI��ʱ";
				strEn="MSP_ERROR_REC_URI_TIMEOUT";
				break;
			case MSP_ERROR_REC_URI_FETCH_ERROR:
				strCn="REC��ȡURI����ʱ����";
				strEn="MSP_ERROR_REC_URI_FETCH_ERROR";
				break;

			case MSP_ERROR_EP_GENERAL:
				strCn="EPһ�����";
				strEn="MSP_ERROR_EP_GENERAL";
				break;
			case MSP_ERROR_EP_NO_SESSION_NAME:
				strCn="EP����û������";
				strEn="MSP_ERROR_EP_NO_SESSION_NAME";
				break;
			case MSP_ERROR_EP_INACTIVE:
				strCn="EP����Ծ";
				strEn="MSP_ERROR_EP_INACTIVE";
				break;
			case MSP_ERROR_EP_INITIALIZED:
				strCn="EP��ʼ������";
				strEn="MSP_ERROR_EP_INITIALIZED";
				break;

			case MSP_ERROR_RES_GENERAL:
				strCn="��Դһ�����";
				strEn="MSP_ERROR_RES_GENERAL";
				break;
			case MSP_ERROR_RES_LOAD:
				strCn="��Դû�м���";
				strEn="MSP_ERROR_RES_LOAD";
				break;
			case MSP_ERROR_RES_FREE:
				strCn="��Դ����";
				strEn="MSP_ERROR_RES_FREE";
				break;
			case MSP_ERROR_RES_MISSING:
				strCn="��Դȱʧ";
				strEn="MSP_ERROR_RES_MISSING";
				break;
			case MSP_ERROR_RES_INVALID_NAME:
				strCn="��Դ��Ч������";
				strEn="MSP_ERROR_RES_INVALID_NAME";
				break;
			case MSP_ERROR_RES_INVALID_ID:
				strCn="��Դ��Ч��ID";
				strEn="MSP_ERROR_RES_INVALID_ID";
				break;
			case MSP_ERROR_RES_INVALID_IMG:
				strCn="��Դ��Ч��ӳ��";
				strEn="MSP_ERROR_RES_INVALID_IMG";
				break;
			case MSP_ERROR_RES_WRITE:
				strCn="��Դд��������";
				strEn="MSP_ERROR_RES_WRITE";
				break;
			case MSP_ERROR_RES_LEAK:
				strCn="��Դй©����";
				strEn="MSP_ERROR_RES_LEAK";
				break;
			case MSP_ERROR_RES_HEAD:
				strCn="��Դͷ������";
				strEn="MSP_ERROR_RES_HEAD";
				break;
			case MSP_ERROR_RES_DATA:
				strCn="��Դ���ݴ���";
				strEn="MSP_ERROR_RES_DATA";
				break;
			case MSP_ERROR_RES_SKIP:
				strCn="��Դ����";
				strEn="MSP_ERROR_RES_SKIP";
				break;

			case MSP_ERROR_TTS_GENERAL:
				strCn="�ϳ�һ�����";
				strEn="MSP_ERROR_TTS_GENERAL";
				break;
			case MSP_ERROR_TTS_TEXTEND:
				strCn="�ϳ��ı�����";
				strEn="MSP_ERROR_TTS_TEXTEND";
				break;
			case MSP_ERROR_TTS_TEXT_EMPTY:
				strCn="�ϳ��ı�Ϊ��";
				strEn="MSP_ERROR_TTS_TEXT_EMPTY";
				break;

			case MSP_ERROR_DB_GENERAL:
				strCn="���ݿ�һ�����";
				strEn="MSP_ERROR_DB_GENERAL";
				break;
			case MSP_ERROR_DB_EXCEPTION:
				strCn="���ݿ��쳣";
				strEn="MSP_ERROR_DB_EXCEPTION";
				break;
			case MSP_ERROR_DB_NO_RESULT:
				strCn="���ݿ�û�н��";
				strEn="MSP_ERROR_DB_NO_RESULT";
				break;
			case MSP_ERROR_DB_INVALID_USER:
				strCn="���ݿ���Ч���û�";
				strEn="MSP_ERROR_DB_INVALID_USER";
				break;
			case MSP_ERROR_DB_INVALID_PWD:
				strCn="���ݿ���Ч������";
				strEn="MSP_ERROR_DB_INVALID_PWD";
				break;
			case MSP_ERROR_DB_CONNECT:
				strCn="���ݿ����Ӵ���";
				strEn="MSP_ERROR_DB_CONNECT";
				break;
			case MSP_ERROR_DB_INVALID_SQL:
				strCn="���ݿ���Ч��SQL";
				strEn="MSP_ERROR_DB_INVALID_SQL";
				break;

			case MSP_ERROR_MSG_GENERAL:
				strCn="��Ϣһ�����";
				strEn="MSP_ERROR_MSG_GENERAL";
				break;
			case MSP_ERROR_MSG_PARSE_ERROR:
				strCn="��Ϣ��������";
				strEn="MSP_ERROR_MSG_PARSE_ERROR";
				break;
			case MSP_ERROR_MSG_BUILD_ERROR:
				strCn="��Ϣ��������";
				strEn="MSP_ERROR_MSG_BUILD_ERROR";
				break;
			case MSP_ERROR_MSG_PARAM_ERROR:
				strCn="��Ϣ��������";
				strEn="MSP_ERROR_MSG_PARAM_ERROR";
				break;
			case MSP_ERROR_MSG_CONTENT_EMPTY:
				strCn="��ϢCONTENTΪ��";
				strEn="MSP_ERROR_MSG_CONTENT_EMPTY";
				break;
			case MSP_ERROR_MSG_INVALID_CONTENT_TYPE:
				strCn="��ϢCONTENT������Ч";
				strEn="MSP_ERROR_MSG_INVALID_CONTENT_TYPE";
				break;
			case MSP_ERROR_MSG_INVALID_CONTENT_LENGTH:
				strCn="��ϢCONTENT������Ч";
				strEn="MSP_ERROR_MSG_INVALID_CONTENT_LENGTH";
				break;
			case MSP_ERROR_MSG_INVALID_CONTENT_ENCODE:
				strCn="��ϢCONTENT������Ч";
				strEn="MSP_ERROR_MSG_INVALID_CONTENT_ENCODE";
				break;
			case MSP_ERROR_MSG_INVALID_KEY:
				strCn="��ϢKEY��Ч";
				strEn="MSP_ERROR_MSG_INVALID_KEY";
				break;
			case MSP_ERROR_MSG_KEY_EMPTY:
				strCn="��ϢKEYΪ��";
				strEn="MSP_ERROR_MSG_KEY_EMPTY";
				break;
			case MSP_ERROR_MSG_SESSION_ID_EMPTY:
				strCn="��Ϣ�ỰIDΪ��";
				strEn="MSP_ERROR_MSG_SESSION_ID_EMPTY";
				break;
			case MSP_ERROR_MSG_LOGIN_ID_EMPTY:
				strCn="��Ϣ��¼IDΪ��";
				strEn="MSP_ERROR_MSG_LOGIN_ID_EMPTY";
				break;
			case MSP_ERROR_MSG_SYNC_ID_EMPTY:
				strCn="��Ϣͬ��IDΪ��";
				strEn="MSP_ERROR_MSG_SYNC_ID_EMPTY";
				break;
			case MSP_ERROR_MSG_APP_ID_EMPTY:
				strCn="��ϢӦ��IDΪ��";
				strEn="MSP_ERROR_MSG_APP_ID_EMPTY";
				break;
			case MSP_ERROR_MSG_EXTERN_ID_EMPTY:
				strCn="��Ϣ��չIDΪ��";
				strEn="MSP_ERROR_MSG_EXTERN_ID_EMPTY";
				break;
			case MSP_ERROR_MSG_INVALID_CMD:
				strCn="��Ϣ��Ч������";
				strEn="MSP_ERROR_MSG_INVALID_CMD";
				break;
			case MSP_ERROR_MSG_INVALID_SUBJECT:
				strCn="��Ϣ��Ч������";
				strEn="MSP_ERROR_MSG_INVALID_SUBJECT";
				break;
			case MSP_ERROR_MSG_INVALID_VERSION:
				strCn="��Ϣ��Ч�İ汾";
				strEn="MSP_ERROR_MSG_INVALID_VERSION";
				break;
			case MSP_ERROR_MSG_NO_CMD:
				strCn="��Ϣû������";
				strEn="MSP_ERROR_MSG_NO_CMD";
				break;
			case MSP_ERROR_MSG_NO_SUBJECT:
				strCn="��Ϣû������";
				strEn="MSP_ERROR_MSG_NO_SUBJECT";
				break;
			case MSP_ERROR_MSG_NO_VERSION:
				strCn="��Ϣû�а汾��";
				strEn="MSP_ERROR_MSG_NO_VERSION";
				break;
			case MSP_ERROR_MSG_MSSP_EMPTY:
				strCn="��ϢΪ��";
				strEn="MSP_ERROR_MSG_MSSP_EMPTY";
				break;
			case MSP_ERROR_MSG_NEW_RESPONSE:
				strCn="�½���Ӧ��Ϣʧ��";
				strEn="MSP_ERROR_MSG_NEW_RESPONSE";
				break;
			case MSP_ERROR_MSG_NEW_CONTENT:
				strCn="��Ϣ�½�Contentʧ��";
				strEn="MSP_ERROR_MSG_NEW_CONTENT";
				break;
			case MSP_ERROR_MSG_INVALID_SESSION_ID:
				strCn="��Ϣ��Ч�ĻỰID";
				strEn="MSP_ERROR_MSG_INVALID_SESSION_ID";
				break;

			case MSP_ERROR_HTTP_BASE:
				strCn="HTTP�������";
				strEn="MSP_ERROR_HTTP_BASE";
				break;

			case MSP_ERROR_LOGIN_SUCCESS:
				strCn="��¼�ɹ�";
				strEn="MSP_ERROR_LOGIN_SUCCESS";
				break;
			case MSP_ERROR_LOGIN_NO_LICENSE:
				strCn="����Ȩ";
				strEn="MSP_ERROR_LOGIN_NO_LICENSE";
				break;
			case MSP_ERROR_LOGIN_SESSIONID_INVALID:
				strCn="��Ч��SessionID";
				strEn="MSP_ERROR_LOGIN_SESSIONID_INVALID";
				break;
			case MSP_ERROR_LOGIN_SESSIONID_ERROR:
				strCn="�����SessionID";
				strEn="MSP_ERROR_LOGIN_SESSIONID_ERROR";
				break;
			case MSP_ERROR_LOGIN_UNLOGIN:
				strCn="δ��¼";
				strEn="MSP_ERROR_LOGIN_UNLOGIN";
				break;
			case MSP_ERROR_LOGIN_INVALID_USER:
				strCn="��Ч���û�";
				strEn="MSP_ERROR_LOGIN_INVALID_USER";
				break;
			case MSP_ERROR_LOGIN_INVALID_PWD:
				strCn="��Ч������";
				strEn="MSP_ERROR_LOGIN_INVALID_PWD";
				break;
			case MSP_ERROR_LOGIN_SYSTEM_ERROR:
				strCn="ϵͳ����";
				strEn="MSP_ERROR_LOGIN_SYSTEM_ERROR";
				break;

			default:
				strCn="��������";
				strEn="other";
			}
			return true;
		}

	}
}