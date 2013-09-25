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
			string strEn="null",strCn="空";

			if(true == getErrorString(nRet,strEn,strCn))//错误代码检测
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
				strCn="成功";
				strEn="MSP_SUCCESS";
				exist=false;
				return true;
			}

			exist=true;

			switch(errorCode)
			{
			case MSP_ERROR_FAIL:
				strCn="失败";
				strEn="MSP_ERROR_FAIL";
				break;
			case MSP_ERROR_EXCEPTION:
				strCn="异常";
				strEn="MSP_ERROR_EXCEPTION";
				break;

			case MSP_ERROR_GENERAL:
				strCn="基码";
				strEn="MSP_ERROR_GENERAL";
				break;
			case MSP_ERROR_OUT_OF_MEMORY:
				strCn="内存越界";
				strEn="MSP_ERROR_OUT_OF_MEMORY";
				break;
			case MSP_ERROR_FILE_NOT_FOUND:
				strCn="没有找到文件";
				strEn="MSP_ERROR_FILE_NOT_FOUND";
				break;
			case MSP_ERROR_NOT_SUPPORT:
				strCn="不支持";
				strEn="MSP_ERROR_NOT_SUPPORT";
				break;
			case MSP_ERROR_NOT_IMPLEMENT:
				strCn="没有实现";
				strEn="MSP_ERROR_NOT_IMPLEMENT";
				break;
			case MSP_ERROR_ACCESS:
				strCn="没有权限";
				strEn="MSP_ERROR_ACCESS";
				break;
			case MSP_ERROR_INVALID_PARA:
				strCn="无效的参数";
				strEn="MSP_ERROR_INVALID_PARA";
				break;
			case MSP_ERROR_INVALID_PARA_VALUE:
				strCn="无效的参数值";
				strEn="MSP_ERROR_INVALID_PARA_VALUE";
				break;
			case MSP_ERROR_INVALID_HANDLE:
				strCn="无效的句柄";
				strEn="MSP_ERROR_INVALID_HANDLE";
				break;
			case MSP_ERROR_INVALID_DATA:
				strCn="无效的数据";
				strEn="MSP_ERROR_INVALID_DATA";
				break;
			case MSP_ERROR_NO_LICENSE:
				strCn="没有授权许可";
				strEn="MSP_ERROR_NO_LICENSE";
				break;
			case MSP_ERROR_NOT_INIT:
				strCn="没有初始化";
				strEn="MSP_ERROR_NOT_INIT";
				break;
			case MSP_ERROR_NULL_HANDLE:
				strCn="无效的Session ID";
				strEn="MSP_ERROR_NULL_HANDLE";
				break;
			case MSP_ERROR_OVERFLOW:
				strCn="溢出";
				strEn="MSP_ERROR_OVERFLOW";
				break;
			case MSP_ERROR_TIME_OUT:
				strCn="超时";
				strEn="MSP_ERROR_TIME_OUT";
				break;
			case MSP_ERROR_OPEN_FILE:
				strCn="打开文件出错";
				strEn="MSP_ERROR_OPEN_FILE";
				break;
			case MSP_ERROR_NOT_FOUND:
				strCn="没有发现";
				strEn="MSP_ERROR_NOT_FOUND";
				break;
			case MSP_ERROR_NO_ENOUGH_BUFFER:
				strCn="没有足够内存";
				strEn="MSP_ERROR_NO_ENOUGH_BUFFER";
				break;
			case MSP_ERROR_NO_DATA:
				strCn="没有数据";
				strEn="MSP_ERROR_NO_DATA";
				break;
			case MSP_ERROR_NO_MORE_DATA:
				strCn="没有更多数据";
				strEn="MSP_ERROR_NO_MORE_DATA";
				break;
				//case MSP_ERROR_SKIPPED:
				//	strCn="跳过";
				//	strEn="MSP_ERROR_SKIPPED";
				//	break;
			case MSP_ERROR_ALREADY_EXIST:
				strCn="已经存在";
				strEn="MSP_ERROR_ALREADY_EXIST";
				break;
			case MSP_ERROR_LOAD_MODULE:
				strCn="加载模块失败";
				strEn="MSP_ERROR_LOAD_MODULE";
				break;
			case MSP_ERROR_BUSY:
				strCn="忙碌";
				strEn="MSP_ERROR_BUSY";
				break;
			case MSP_ERROR_INVALID_CONFIG:
				strCn="无效的配置项";
				strEn="MSP_ERROR_INVALID_CONFIG";
				break;
			case MSP_ERROR_VERSION_CHECK:
				strCn="版本错误";
				strEn="MSP_ERROR_VERSION_CHECK";
				break;
			case MSP_ERROR_CANCELED:
				strCn="取消";
				strEn="MSP_ERROR_CANCELED";
				break;
			case MSP_ERROR_INVALID_MEDIA_TYPE:
				strCn="无效的媒体类型";
				strEn="MSP_ERROR_INVALID_MEDIA_TYPE";
				break;
			case MSP_ERROR_CONFIG_INITIALIZE:
				strCn="初始化失败";
				strEn="MSP_ERROR_CONFIG_INITIALIZE";
				break;
			case MSP_ERROR_CREATE_HANDLE:
				strCn="建立句柄错误";
				strEn="MSP_ERROR_CREATE_HANDLE";
				break;
			case MSP_ERROR_CODING_LIB_NOT_LOAD:
				strCn="编解码库未加载";
				strEn="MSP_ERROR_CODING_LIB_NOT_LOAD";
				break;

			case MSP_ERROR_NET_GENERAL:
				strCn="网络一般错误";
				strEn="MSP_ERROR_NET_GENERAL";
				break;
			case MSP_ERROR_NET_OPENSOCK:
				strCn="网络打开套接字错误";
				strEn="MSP_ERROR_NET_OPENSOCK";
				break;
			case MSP_ERROR_NET_CONNECTSOCK:
				strCn="网络套接字连接错误";
				strEn="MSP_ERROR_NET_CONNECTSOCK";
				break;
			case MSP_ERROR_NET_ACCEPTSOCK:
				strCn="网络套接字响应错误";
				strEn="MSP_ERROR_NET_ACCEPTSOCK";
				break;
			case MSP_ERROR_NET_SENDSOCK:
				strCn="网络套接字发送错误";
				strEn="MSP_ERROR_NET_SENDSOCK";
				break;
			case MSP_ERROR_NET_RECVSOCK:
				strCn="网络套接字接收错误";
				strEn="MSP_ERROR_NET_RECVSOCK";
				break;
			case MSP_ERROR_NET_INVALIDSOCK:
				strCn="网络无效的套接字";
				strEn="MSP_ERROR_NET_INVALIDSOCK";
				break;
			case MSP_ERROR_NET_BADADDRESS:
				strCn="网络无效的地址";
				strEn="MSP_ERROR_NET_BADADDRESS";
				break;
			case MSP_ERROR_NET_BINDSEQUENCE:
				strCn="网络绑定次序错误";
				strEn="MSP_ERROR_NET_BINDSEQUENCE";
				break;
			case MSP_ERROR_NET_NOTOPENSOCK:
				strCn="网络套接字没有打开";
				strEn="MSP_ERROR_NET_NOTOPENSOCK";
				break;
			case MSP_ERROR_NET_NOTBIND:
				strCn="网络没有绑定";
				strEn="MSP_ERROR_NET_NOTBIND";
				break;
			case MSP_ERROR_NET_NOTLISTEN:
				strCn="网络没有监听";
				strEn="MSP_ERROR_NET_NOTLISTEN";
				break;
			case MSP_ERROR_NET_CONNECTCLOSE:
				strCn="网络连接关闭";
				strEn="MSP_ERROR_NET_CONNECTCLOSE";
				break;
			case MSP_ERROR_NET_NOTDGRAMSOCK:
				strCn="网络非数据报套接字";
				strEn="MSP_ERROR_NET_NOTDGRAMSOCK";
				break;
			case MSP_ERROR_NET_DNS:
				strCn="DNS解析错误";
				strEn="MSP_ERROR_NET_DNS";
				break;

			case MSP_ERROR_REC_GENERAL:
				strCn="REC一般错误";
				strEn="MSP_ERROR_REC_GENERAL";
				break;
			case MSP_ERROR_REC_INACTIVE:
				strCn="REC处于不活跃状态";
				strEn="MSP_ERROR_REC_INACTIVE";
				break;
			case MSP_ERROR_REC_GRAMMAR_ERROR:
				strCn="REC语法错误";
				strEn="MSP_ERROR_REC_GRAMMAR_ERROR";
				break;
			case MSP_ERROR_REC_NO_ACTIVE_GRAMMARS:
				strCn="REC没有活跃的语法";
				strEn="MSP_ERROR_REC_NO_ACTIVE_GRAMMARS";
				break;
			case MSP_ERROR_REC_DUPLICATE_GRAMMAR:
				strCn="REC语法重复";
				strEn="MSP_ERROR_REC_DUPLICATE_GRAMMAR";
				break;
			case MSP_ERROR_REC_INVALID_MEDIA_TYPE:
				strCn="REC无效的媒体类型";
				strEn="MSP_ERROR_REC_INVALID_MEDIA_TYPE";
				break;
			case MSP_ERROR_REC_INVALID_LANGUAGE:
				strCn="REC无效的语言";
				strEn="MSP_ERROR_REC_INVALID_LANGUAGE";
				break;
			case MSP_ERROR_REC_URI_NOT_FOUND:
				strCn="REC没有对应的URI";
				strEn="MSP_ERROR_REC_URI_NOT_FOUND";
				break;
			case MSP_ERROR_REC_URI_TIMEOUT:
				strCn="REC获取URI超时";
				strEn="MSP_ERROR_REC_URI_TIMEOUT";
				break;
			case MSP_ERROR_REC_URI_FETCH_ERROR:
				strCn="REC获取URI内容时出错";
				strEn="MSP_ERROR_REC_URI_FETCH_ERROR";
				break;

			case MSP_ERROR_EP_GENERAL:
				strCn="EP一般错误";
				strEn="MSP_ERROR_EP_GENERAL";
				break;
			case MSP_ERROR_EP_NO_SESSION_NAME:
				strCn="EP连接没有名字";
				strEn="MSP_ERROR_EP_NO_SESSION_NAME";
				break;
			case MSP_ERROR_EP_INACTIVE:
				strCn="EP不活跃";
				strEn="MSP_ERROR_EP_INACTIVE";
				break;
			case MSP_ERROR_EP_INITIALIZED:
				strCn="EP初始化出错";
				strEn="MSP_ERROR_EP_INITIALIZED";
				break;

			case MSP_ERROR_RES_GENERAL:
				strCn="资源一般错误";
				strEn="MSP_ERROR_RES_GENERAL";
				break;
			case MSP_ERROR_RES_LOAD:
				strCn="资源没有加载";
				strEn="MSP_ERROR_RES_LOAD";
				break;
			case MSP_ERROR_RES_FREE:
				strCn="资源空闲";
				strEn="MSP_ERROR_RES_FREE";
				break;
			case MSP_ERROR_RES_MISSING:
				strCn="资源缺失";
				strEn="MSP_ERROR_RES_MISSING";
				break;
			case MSP_ERROR_RES_INVALID_NAME:
				strCn="资源无效的名称";
				strEn="MSP_ERROR_RES_INVALID_NAME";
				break;
			case MSP_ERROR_RES_INVALID_ID:
				strCn="资源无效的ID";
				strEn="MSP_ERROR_RES_INVALID_ID";
				break;
			case MSP_ERROR_RES_INVALID_IMG:
				strCn="资源无效的映像";
				strEn="MSP_ERROR_RES_INVALID_IMG";
				break;
			case MSP_ERROR_RES_WRITE:
				strCn="资源写操作错误";
				strEn="MSP_ERROR_RES_WRITE";
				break;
			case MSP_ERROR_RES_LEAK:
				strCn="资源泄漏错误";
				strEn="MSP_ERROR_RES_LEAK";
				break;
			case MSP_ERROR_RES_HEAD:
				strCn="资源头部错误";
				strEn="MSP_ERROR_RES_HEAD";
				break;
			case MSP_ERROR_RES_DATA:
				strCn="资源数据错误";
				strEn="MSP_ERROR_RES_DATA";
				break;
			case MSP_ERROR_RES_SKIP:
				strCn="资源跳过";
				strEn="MSP_ERROR_RES_SKIP";
				break;

			case MSP_ERROR_TTS_GENERAL:
				strCn="合成一般错误";
				strEn="MSP_ERROR_TTS_GENERAL";
				break;
			case MSP_ERROR_TTS_TEXTEND:
				strCn="合成文本结束";
				strEn="MSP_ERROR_TTS_TEXTEND";
				break;
			case MSP_ERROR_TTS_TEXT_EMPTY:
				strCn="合成文本为空";
				strEn="MSP_ERROR_TTS_TEXT_EMPTY";
				break;

			case MSP_ERROR_DB_GENERAL:
				strCn="数据库一般错误";
				strEn="MSP_ERROR_DB_GENERAL";
				break;
			case MSP_ERROR_DB_EXCEPTION:
				strCn="数据库异常";
				strEn="MSP_ERROR_DB_EXCEPTION";
				break;
			case MSP_ERROR_DB_NO_RESULT:
				strCn="数据库没有结果";
				strEn="MSP_ERROR_DB_NO_RESULT";
				break;
			case MSP_ERROR_DB_INVALID_USER:
				strCn="数据库无效的用户";
				strEn="MSP_ERROR_DB_INVALID_USER";
				break;
			case MSP_ERROR_DB_INVALID_PWD:
				strCn="数据库无效的密码";
				strEn="MSP_ERROR_DB_INVALID_PWD";
				break;
			case MSP_ERROR_DB_CONNECT:
				strCn="数据库连接错误";
				strEn="MSP_ERROR_DB_CONNECT";
				break;
			case MSP_ERROR_DB_INVALID_SQL:
				strCn="数据库无效的SQL";
				strEn="MSP_ERROR_DB_INVALID_SQL";
				break;

			case MSP_ERROR_MSG_GENERAL:
				strCn="消息一般错误";
				strEn="MSP_ERROR_MSG_GENERAL";
				break;
			case MSP_ERROR_MSG_PARSE_ERROR:
				strCn="消息解析错误";
				strEn="MSP_ERROR_MSG_PARSE_ERROR";
				break;
			case MSP_ERROR_MSG_BUILD_ERROR:
				strCn="消息构建错误";
				strEn="MSP_ERROR_MSG_BUILD_ERROR";
				break;
			case MSP_ERROR_MSG_PARAM_ERROR:
				strCn="消息参数错误";
				strEn="MSP_ERROR_MSG_PARAM_ERROR";
				break;
			case MSP_ERROR_MSG_CONTENT_EMPTY:
				strCn="消息CONTENT为空";
				strEn="MSP_ERROR_MSG_CONTENT_EMPTY";
				break;
			case MSP_ERROR_MSG_INVALID_CONTENT_TYPE:
				strCn="消息CONTENT类型无效";
				strEn="MSP_ERROR_MSG_INVALID_CONTENT_TYPE";
				break;
			case MSP_ERROR_MSG_INVALID_CONTENT_LENGTH:
				strCn="消息CONTENT长度无效";
				strEn="MSP_ERROR_MSG_INVALID_CONTENT_LENGTH";
				break;
			case MSP_ERROR_MSG_INVALID_CONTENT_ENCODE:
				strCn="消息CONTENT编码无效";
				strEn="MSP_ERROR_MSG_INVALID_CONTENT_ENCODE";
				break;
			case MSP_ERROR_MSG_INVALID_KEY:
				strCn="消息KEY无效";
				strEn="MSP_ERROR_MSG_INVALID_KEY";
				break;
			case MSP_ERROR_MSG_KEY_EMPTY:
				strCn="消息KEY为空";
				strEn="MSP_ERROR_MSG_KEY_EMPTY";
				break;
			case MSP_ERROR_MSG_SESSION_ID_EMPTY:
				strCn="消息会话ID为空";
				strEn="MSP_ERROR_MSG_SESSION_ID_EMPTY";
				break;
			case MSP_ERROR_MSG_LOGIN_ID_EMPTY:
				strCn="消息登录ID为空";
				strEn="MSP_ERROR_MSG_LOGIN_ID_EMPTY";
				break;
			case MSP_ERROR_MSG_SYNC_ID_EMPTY:
				strCn="消息同步ID为空";
				strEn="MSP_ERROR_MSG_SYNC_ID_EMPTY";
				break;
			case MSP_ERROR_MSG_APP_ID_EMPTY:
				strCn="消息应用ID为空";
				strEn="MSP_ERROR_MSG_APP_ID_EMPTY";
				break;
			case MSP_ERROR_MSG_EXTERN_ID_EMPTY:
				strCn="消息扩展ID为空";
				strEn="MSP_ERROR_MSG_EXTERN_ID_EMPTY";
				break;
			case MSP_ERROR_MSG_INVALID_CMD:
				strCn="消息无效的命令";
				strEn="MSP_ERROR_MSG_INVALID_CMD";
				break;
			case MSP_ERROR_MSG_INVALID_SUBJECT:
				strCn="消息无效的主题";
				strEn="MSP_ERROR_MSG_INVALID_SUBJECT";
				break;
			case MSP_ERROR_MSG_INVALID_VERSION:
				strCn="消息无效的版本";
				strEn="MSP_ERROR_MSG_INVALID_VERSION";
				break;
			case MSP_ERROR_MSG_NO_CMD:
				strCn="消息没有命令";
				strEn="MSP_ERROR_MSG_NO_CMD";
				break;
			case MSP_ERROR_MSG_NO_SUBJECT:
				strCn="消息没有主题";
				strEn="MSP_ERROR_MSG_NO_SUBJECT";
				break;
			case MSP_ERROR_MSG_NO_VERSION:
				strCn="消息没有版本号";
				strEn="MSP_ERROR_MSG_NO_VERSION";
				break;
			case MSP_ERROR_MSG_MSSP_EMPTY:
				strCn="消息为空";
				strEn="MSP_ERROR_MSG_MSSP_EMPTY";
				break;
			case MSP_ERROR_MSG_NEW_RESPONSE:
				strCn="新建响应消息失败";
				strEn="MSP_ERROR_MSG_NEW_RESPONSE";
				break;
			case MSP_ERROR_MSG_NEW_CONTENT:
				strCn="消息新建Content失败";
				strEn="MSP_ERROR_MSG_NEW_CONTENT";
				break;
			case MSP_ERROR_MSG_INVALID_SESSION_ID:
				strCn="消息无效的会话ID";
				strEn="MSP_ERROR_MSG_INVALID_SESSION_ID";
				break;

			case MSP_ERROR_HTTP_BASE:
				strCn="HTTP错误基码";
				strEn="MSP_ERROR_HTTP_BASE";
				break;

			case MSP_ERROR_LOGIN_SUCCESS:
				strCn="登录成功";
				strEn="MSP_ERROR_LOGIN_SUCCESS";
				break;
			case MSP_ERROR_LOGIN_NO_LICENSE:
				strCn="无授权";
				strEn="MSP_ERROR_LOGIN_NO_LICENSE";
				break;
			case MSP_ERROR_LOGIN_SESSIONID_INVALID:
				strCn="无效的SessionID";
				strEn="MSP_ERROR_LOGIN_SESSIONID_INVALID";
				break;
			case MSP_ERROR_LOGIN_SESSIONID_ERROR:
				strCn="错误的SessionID";
				strEn="MSP_ERROR_LOGIN_SESSIONID_ERROR";
				break;
			case MSP_ERROR_LOGIN_UNLOGIN:
				strCn="未登录";
				strEn="MSP_ERROR_LOGIN_UNLOGIN";
				break;
			case MSP_ERROR_LOGIN_INVALID_USER:
				strCn="无效的用户";
				strEn="MSP_ERROR_LOGIN_INVALID_USER";
				break;
			case MSP_ERROR_LOGIN_INVALID_PWD:
				strCn="无效的密码";
				strEn="MSP_ERROR_LOGIN_INVALID_PWD";
				break;
			case MSP_ERROR_LOGIN_SYSTEM_ERROR:
				strCn="系统错误";
				strEn="MSP_ERROR_LOGIN_SYSTEM_ERROR";
				break;

			default:
				strCn="其他错误";
				strEn="other";
			}
			return true;
		}

	}
}