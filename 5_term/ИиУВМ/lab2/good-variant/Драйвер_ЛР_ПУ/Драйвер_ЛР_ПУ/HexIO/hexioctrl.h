#include <windows.h>
#include <tchar.h>
#include <string>
#include <winsvc.h>
using namespace std;

#pragma comment( lib, "hexiosupp.lib" )
#define ALLOW_IO_OPERATIONS			\
	HexIOWrapper hwr;				\
	hwr.StartUp();					\
	hwr.AllowExclusiveAccess();		\
	hwr.ShutDown();

class HexIOWrapper
{
	public:
		
		HexIOWrapper();
		virtual ~HexIOWrapper();
		bool StartUp();
		bool ShutDown();
		string GetStatus();

		UCHAR ReadPortUCHAR(UCHAR port);
		USHORT ReadPortUSHORT(USHORT port);
		ULONG ReadPortULONG(ULONG port);

		void WritePortUCHAR(UCHAR port,UCHAR value);
		void WritePortUSHORT(USHORT port,USHORT value);
		void WritePortULONG(ULONG port,ULONG value);
		

		bool AllowExclusiveAccess();
	protected:
		HANDLE m_hdriver;
		string m_status;
		TCHAR m_szDriverName[50];
		TCHAR m_szDriverPath[MAX_PATH];

		void CatchError	();

		BOOLEAN InstallDriver(
				 SC_HANDLE  SchSCManager
			);


		BOOLEAN
		RemoveDriver(
			 SC_HANDLE  SchSCManager
			);

		BOOLEAN
		StartDriver(
			 SC_HANDLE  SchSCManager
			);

		BOOLEAN
		StopDriver(
			 SC_HANDLE  SchSCManager
			);





};
