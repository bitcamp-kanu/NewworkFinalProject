#include "DBService.h"

#include "..\Public\DefineSchema.h"
#include "..\Public\WIUtility.h"
#include "..\Public\PublicDefine.h"

#include "DBManagerEx.h"

DBService::DBService(void)
{
	m_pDbManagerEx = new DBManagerEx();
	m_pDbManagerEx->Open();
}


DBService::~DBService(void)
{
}

int DBService::ReceiveEvent(SockBase* pSockBase,char* pData, int len)
{

	try
	{
		if(WIUtility::IsCommand(pData,"AL")) //테스트 LO 이면
		{
			_Login logData;
			memcpy(&logData,pData,sizeof(_Login));
			cout << "DB Server 수신 " << logData.ToString() << endl;

			if(m_pDbManagerEx->IsUserPasswordEx(logData.id,logData.pass))
			{
				m_pDbManagerEx->InsertSecretKey(logData.id, logData.header.SecretKey);
				logData.header.pakID = 111;
			}
			else
			{
				logData.header.pakID = 110;
			}
			logData.cont++;
			int error = pSockBase->Send((char*)&logData,sizeof(_Login));
		}
		else if (WIUtility::IsCommand(pData, "EC")) //보안키를 확인 한다.
		{
			_SecretKeyChedk sechtKey;
			memcpy(&sechtKey, pData, sizeof(_SecretKeyChedk));
			cout << "DB Server 수신 " << sechtKey.ToString() << endl;
			if(m_pDbManagerEx->IsSecretKeyEx(sechtKey.header.id, sechtKey.header.SecretKey))
			{
				sechtKey.header.pakID = 201; //인증 성공
			}
			else
			{ 
				sechtKey.header.pakID = 200; //인증 실패.
			}

			int error = pSockBase->Send((char*)&sechtKey, sizeof(_SecretKeyChedk));
		}
		else if(WIUtility::IsCommand(pData,"US")) //USER 정보 요청
		{
			_DemandUserInfo userInof;
			memcpy(&userInof,pData,sizeof(_DemandUserInfo));
			vector<_Tb_Class*> vec = m_pDbManagerEx->SelectClassInfo(userInof.header.id);
			if(vec.size() > 0)
			{
				strcpy(userInof.ClassId		,vec[0]->ClassId.c_str());
				strcpy(userInof.ClassName	,vec[0]->ClassName.c_str());
				strcpy(userInof.UName		,vec[0]->UName.c_str());
				userInof.header.pakID = 901;
			}
			else
			{
				userInof.header.pakID = 900;
			}
			int error = pSockBase->Send((char*)&userInof, sizeof(_DemandUserInfo));

		}
		else if(WIUtility::IsCommand(pData,"AA")) //테스트 CMD 이면
		{
			_WorkDataEx workDataEx;
			memcpy(&workDataEx,pData,sizeof(_WorkDataEx));
			vector<_Student*> vec = m_pDbManagerEx->SelectStudent(workDataEx.ClassId,workDataEx.ClassNum,workDataEx.SName);			
			_WorkPacket* pData = new _WorkPacket[vec.size()];
			memset(pData,0x00,sizeof(_WorkPacket) * vec.size());
			workDataEx.len = vec.size();
			for(int i = 0 ; i < vec.size() ; i++)
			{
				pData[i].ClassNum		= atoi(vec[i]->ClassNum.c_str());
				strcpy(pData[i].ClassId	,vec[i]->ClassId.c_str());
				strcpy(pData[i].SName	,vec[i]->SName.c_str());
				pData[i].SSex			= vec[i]->SSex[0];
				strcpy(pData[i].STel	,vec[i]->STelNo.c_str());
				pData[i].C				= atoi(vec[i]->C.c_str());
				pData[i].CPP			= atoi(vec[i]->CPP.c_str());
				pData[i].CSharp			= atoi(vec[i]->CSharp.c_str());
				pData[i].Network		= atoi(vec[i]->Network.c_str());
				pData[i].Unity			= atoi(vec[i]->Unity.c_str());
				pData[i].Total			= atoi(vec[i]->Total.c_str());
				pData[i].Ave			= atof(vec[i]->Avg.c_str());
				strcpy(pData[i].UDate	,vec[i]->UDate.c_str());
				//if(i == 20) //20개 까지만 처리.
				//{
				//	workDataEx.len = 20;
				//	break;
				//}
			}
			int len = sizeof(_WorkDataEx) + sizeof(_WorkPacket) * workDataEx.len;
			char* buff = new char[len];

			len = 0;
			memcpy(buff + len,&workDataEx,sizeof(_WorkDataEx));
			len = sizeof(_WorkDataEx);
			memcpy(buff + len,pData,sizeof(_WorkPacket) * workDataEx.len);
			len += sizeof(_WorkPacket) * workDataEx.len;
			pSockBase->Send(buff,len);

			for(int i = 0 ; i < vec.size() ; i++)
			{
				delete vec[i];
				vec[i] = NULL;
			}

		}
		else if(WIUtility::IsCommand(pData,"SC")) //테스트 CMD 이면
		{
			_WorkData workData;
			try
			{				
				//string sex = WIUtility::GetFormatString("%c",workData.SSex);

				memcpy(&workData,pData,sizeof(_WorkData));
				if(m_pDbManagerEx->InsertStudentEx(workData.ClassId,workData.SName,workData.SSex,workData.STel))
				{					
					workData.header.pakID = 901;
				}
				else
				{
					workData.header.pakID = 900;
				}
				int error = pSockBase->Send((char*)&workData, sizeof(_WorkData));
			}
			catch (exceptionDB e)
			{
				cout << e.what() << endl;
			}
		}
		else if(WIUtility::IsCommand(pData,"SG")) 
		{
			_WorkData workData;
			try
			{				
				//string sex = WIUtility::GetFormatString("%c",workData.SSex);
				memcpy(&workData,pData,sizeof(_WorkData));
				if(m_pDbManagerEx->UpdateStudentGrade(0,workData.ClassId,workData.ClassNum,workData.C,workData.CPP,workData.CSharp,workData.Network,workData.Unity))
				{					
					workData.header.pakID = 901;
				}
				else
				{
					workData.header.pakID = 900;
				}
				int error = pSockBase->Send((char*)&workData, sizeof(_WorkData));
			}
			catch (exceptionDB e)
			{
				cout << e.what() << endl;
			}
		}
		else if(WIUtility::IsCommand(pData,"TL")) //테스트 CMD 이면
		{
			WorkTeset(pSockBase,pData,len);
		}
		else if(WIUtility::IsCommand(pData,"TG")) //테스트 CMD 이면
		{
			WorkTeset(pSockBase,pData,len);
		}
		else if(WIUtility::IsCommand(pData,"TW")) //테스트 CMD 이면
		{
			WorkTeset(pSockBase,pData,len);
		}
	}
	catch (exceptionCS e)
	{
		cout << "Client Socket 이 문제가 발생하였습니다." << endl;
		cout << e.what();
	}
	catch (exceptionRS e)
	{
		cout << "Recvive Socket 이 문제가 발생하였습니다." << endl;
		cout << e.what();
	}
	return true;
}

int DBService::WorkTeset(SockBase* pSockBase,char* pData, int len)
{
	_Login logData;
	logData.SetCopyBuff(pData);
	memcpy(&logData,pData,sizeof(_Login));
	if(logData.header.cmd2 == 'L')
	{
		cout << "DBServer: Login Server 에서 데이터 수신" << logData.ToString() << endl;
	}
	else if(logData.header.cmd2 == 'G')
	{
		cout << "DBServer: GateWay Server 에서 데이터 수신" << logData.ToString() << endl;
	}
	else if(logData.header.cmd2 == 'W')
	{
		cout << "DBServer: Work Server 에서 데이터 수신" << logData.ToString() << endl;
	}			

	logData.cont++;
	pSockBase->Send((char*)&logData,sizeof(_Login));
	if(logData.header.cmd2 == 'L')
	{
		cout << "DBServer: Login Server 에 데이터 전송" << logData.ToString() << endl;
	}
	else if(logData.header.cmd2 == 'G')
	{
		cout << "DBServer: GateWay Server 에 데이터 전송" << logData.ToString() << endl;
	}
	else if(logData.header.cmd2 == 'W')
	{
		cout << "DBServer: Work Server 에 데이터 전송" << logData.ToString() << endl;
	}	
	return 0;
}