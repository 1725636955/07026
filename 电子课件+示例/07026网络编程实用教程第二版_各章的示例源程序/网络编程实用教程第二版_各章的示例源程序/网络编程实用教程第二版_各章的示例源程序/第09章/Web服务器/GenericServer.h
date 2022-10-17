/****************************************************************************************
* ///////////////////////////////////////////////////////////////////////////////////////
*	Original Filename: 	genericserver.h
*
*	History:
*	Created/Modified by				Date			Main Purpose/Changes
*	Souren M. Abeghyan				2001/05/25		Interface for the CGenericServer class
*	
*	Comments:	
* \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
****************************************************************************************/
#if !defined(AFX_GENERICSERVER_H__6C21FFA2_485A_11D5_9692_0050BA8CD8A0__INCLUDED_)
#define AFX_GENERICSERVER_H__6C21FFA2_485A_11D5_9692_0050BA8CD8A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define THREADKILL_TO		1000
#define THREADWAIT_TO		30000
#define TICK				100
#define THREADEXIT_SUCCESS	0x1234
#define SERVERPORT			80
#define MAX_BUFFER			100000
#define SENDBLOCK			200000
#define LOGFILENAME			"UMServer.log"


#pragma warning(disable:4786)

#include <winsock2.h>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <algorithm>
#include <list>
#include <functional>
#include <process.h>

#include "Log.h"

using namespace std;

struct NewConnectionTag;

struct ThreadTag
{
	HANDLE				hThread;
	unsigned int		threadID;
};


struct IDCompare : binary_function<ThreadTag, unsigned int, bool>
{
	bool operator()(const ThreadTag& _X, const unsigned int& _Y) const
	{
		return (_X.threadID == _Y); 
	}
};


typedef list<ThreadTag>					THREADLIST;
typedef list<HANDLE>					HANDLELIST;
typedef vector<string>					STRVECT;

struct StatisticsTag
{
	long					nClientsConnected;
	long					nTotalHits;
	double					nTotalSent;
	double					nTotalRecv;
	double					nErrosCount;
	long					nVisitors;
};


class CGenericServer : public CLog
{
public:
							CGenericServer();
	virtual					~CGenericServer();
public:						
	void					GetStats(StatisticsTag&);
	void					Reset();
	BOOL					Run(int, int);
	BOOL					Shutdown();
protected:					
	virtual int				GotConnection(char*, int)				= 0;
	virtual int				DataSent(DWORD)							= 0;
	virtual BOOL			IsComplete(string)						= 0;
	virtual BOOL			ParseRequest(string, string&, BOOL&)	= 0;
private:				
	static UINT	__stdcall	AcceptThread(LPVOID);
	static UINT __stdcall 	ClientThread(LPVOID);
	static UINT __stdcall 	HelperThread(LPVOID);
	
	BOOL					AddClient(SOCKET, char*, int);
	void					CleanupThread(WSAEVENT, SOCKET, NewConnectionTag*, DWORD);
	void					CleanupThread(WSAEVENT, WSAEVENT, SOCKET);
private:					
	HANDLE					ThreadA; // Accept Thread
	unsigned int			ThreadA_ID;
	HANDLE					ThreadC; // Cleanup Thread
	unsigned int			ThreadC_ID;
							
	WSAEVENT				ShutdownEvent;
							
	HANDLE					ThreadLaunchedEvent;
	HANDLE					WaitForCloseEvent;
							
	THREADLIST				ThreadList;
	HANDLELIST				HandleList;
							
	StatisticsTag			Stats;
	CRITICAL_SECTION		cs;
	CRITICAL_SECTION		_cs;

	int						ServerPort;
	int						PersistenceTO;

	BOOL					bRun;
protected:
	STRVECT					Visitors;
};

struct NewConnectionTag
{
	CGenericServer			*pGenericServer;
	SOCKET					s;
};


#endif // !defined(AFX_GENERICSERVER_H__6C21FFA2_485A_11D5_9692_0050BA8CD8A0__INCLUDED_)
