////////////////////////////////////////////////////////////////
// MSDN Magazine -- July 2002
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with Visual Studio 6.0 and Visual Studio .NET
// Runs in Windows XP and probably Windows 2000 too.
//
#include "stdafx.h"
#include "EnumProc.h"
#include "Psapi.h"

CWindowIterator::CWindowIterator(DWORD nAlloc)
{
	ASSERT(nAlloc > 0);
	m_current = m_count = 0;
	m_hwnds = new HWND [nAlloc];
	m_nAlloc = nAlloc;
}

CWindowIterator::~CWindowIterator()
{
	delete [] m_hwnds;
}

//////////////////
// Move to first top-level window.

// Stuff entire array and return the first HWND.

//列举出当前线程所有的窗口，返回第一个窗口

HWND CWindowIterator::First()
{
	//回调函数EnumProc的参数是(LPARAM)this！！！！！
	
	::EnumWindows(EnumProc, (LPARAM)this);
	
	m_current = 0;
	
	//返回第0个窗口
	
	return Next();
}

//////////////////
// Static enumerator passes to virtual fn.
//
BOOL CALLBACK CWindowIterator::EnumProc(HWND hwnd, LPARAM lp)
{
	return ((CWindowIterator*)lp)->OnEnumProc(hwnd);
}

//////////////////
// Virtual enumerator proc: add HWND to array if OnWindow is TRUE.
//
BOOL CWindowIterator::OnEnumProc(HWND hwnd)
{
	//如果窗口可见，而且和当前窗口的id相同
	
	if (OnWindow(hwnd))
	{
		//把当前窗口添加到窗口数组
		
		if (m_count < m_nAlloc)
		{
			m_hwnds[m_count++] = hwnd;
		}
	}
	
	return TRUE; // keep looking
}

//////////////////
// Main window iterator: special case to iterate main windows of a process.
//
CMainWindowIterator::CMainWindowIterator(DWORD pid, DWORD nAlloc)
: CWindowIterator(nAlloc)
{
	m_pid = pid;
}

CMainWindowIterator::~CMainWindowIterator()
{
}

//////////////////
// virtual override: is this window a main window of my process?
//
BOOL CMainWindowIterator::OnWindow(HWND hwnd)
{
	//如果窗口可见
	
	if (GetWindowLong(hwnd,GWL_STYLE) & WS_VISIBLE) 
	{
		DWORD pidwin;
		
		//获得窗口对应的threadid，如果和当前的线程id
		
		//相等返回true
		
		GetWindowThreadProcessId(hwnd, &pidwin);
		
		if (pidwin == m_pid)
		{
			return TRUE;
		}
		
	}
	return FALSE;
}

CProcessIterator::CProcessIterator()
{
	m_pids = NULL;
}

CProcessIterator::~CProcessIterator()
{
	delete [] m_pids;
}

//////////////////
// Get first process.
// Call EnumProcesses to initialize entire array, then return first one.
//
DWORD CProcessIterator::First()
{
	m_current = (DWORD)-1;
	
	m_count = 0;
	
	DWORD nalloc = 1024;
	
	do {
		delete [] m_pids;
		
		m_pids = new DWORD [nalloc];// 创建一个1024大的一个数组
		
		//获得所有的线程，保存到m_pids数组里面，m_count保存了获得线程的数目
		
		if ( ::EnumProcesses(m_pids, nalloc*sizeof(DWORD), &m_count) ) 
		{
			m_count /= sizeof(DWORD);
			
			//m_current指向第一个节点，跳过第0个idle process
			
			m_current = 1; // important: skip IDLE process with pid=0.
		}
		
	} while (nalloc <= m_count);
	
	return Next();
}

CProcessModuleIterator::CProcessModuleIterator(DWORD pid)
{
	// open the process
	
	m_hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
		FALSE, pid);
}

CProcessModuleIterator::~CProcessModuleIterator()
{
	CloseHandle(m_hProcess);
	
	delete [] m_hModules;
}

//////////////////
// Get first module in process. Call EnumProcesseModules to
// initialize entire array, then return first module.
//
HMODULE CProcessModuleIterator::First()
{
	m_count = 0;
	m_current = (DWORD) -1; 
	m_hModules = NULL;
	if (m_hProcess) 
	{
		DWORD nalloc = 1024;
		do {
			delete [] m_hModules;
			m_hModules = new HMODULE [nalloc];
			if (EnumProcessModules(m_hProcess, m_hModules,
				nalloc*sizeof(DWORD), &m_count)) 
			{
				m_count /= sizeof(HMODULE);
				m_current = 0;
			}
		} while (nalloc <= m_count);
	}
	return Next();
}

