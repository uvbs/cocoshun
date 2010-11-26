////////////////////////////////////////////////////////////////
// MSDN Magazine -- July 2002
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with Visual Studio 6.0 and Visual Studio .NET
// Runs in Windows XP and probably Windows 2000 too.
//
#pragma once

//////////////////
// Iterate the top-level windows. Encapsulates ::EnumWindows.

//封装了一个HWND 数组

class CWindowIterator 
{

protected:

 HWND* m_hwnds;    // array of hwnds for this PID

 DWORD m_nAlloc;   // size of array

 DWORD m_count;    // number of HWNDs found

 DWORD m_current;   // current HWND

 static BOOL CALLBACK EnumProc(HWND hwnd, LPARAM lp);

 // virtual enumerator

 virtual BOOL OnEnumProc(HWND hwnd);

 // override to filter different kinds of windows

 virtual BOOL OnWindow(HWND hwnd) 
 {
  return TRUE;
 }

public:

 CWindowIterator(DWORD nAlloc=1024);

 ~CWindowIterator();
 
 DWORD GetCount() 
 { 
  return m_count;
 }


 HWND First();

 HWND Next() 
 {
  return m_hwnds && m_current < m_count ? m_hwnds[m_current++] : NULL;
 }

};

//////////////////
// Iterate the top-level windows in a process.
//
class CMainWindowIterator : public CWindowIterator 
{

protected:

 DWORD m_pid; // process id

 virtual BOOL OnWindow(HWND hwnd);

public:

 CMainWindowIterator(DWORD pid, DWORD nAlloc=1024);

 ~CMainWindowIterator();

};

//////////////////
// Process iterator -- iterator over all system processes
// Always skips the first (IDLE) process with PID=0.

//封装了一个DWORD数组

class CProcessIterator
{

protected:

 DWORD* m_pids;   // array of procssor IDs

 DWORD  m_count;   // size of array

 DWORD  m_current;  // next array item

public:

 CProcessIterator();

 ~CProcessIterator();

 DWORD GetCount() // 返回当前的count
 { 
  return m_count; 
 }

 DWORD First();

 DWORD Next() // 返回当前的DWORD id，同时iterator递增指向下一个，到末尾时返回NULL
 {
  return m_pids && m_current < m_count ? m_pids[m_current++] : 0;
 }

};

//////////////////
// Iterate the modules in a process. Note that the first module is the
// main EXE that started the process.
//
class CProcessModuleIterator 
{

protected:

 //保存当前线程的句柄

 HANDLE m_hProcess;   // process handle

 HMODULE* m_hModules;   // array of module handles

 DWORD  m_count;    // size of array

 DWORD  m_current;   // next module handle

public:

 CProcessModuleIterator(DWORD pid);

 ~CProcessModuleIterator();

 HANDLE GetProcessHandle() 
 { 
  return m_hProcess; 
 }

 DWORD GetCount()    
 { 
  return m_count; 
 }

 HMODULE First();

 HMODULE Next() 
 {
  return m_hProcess && m_current < m_count ? m_hModules[m_current++] : 0;
 }

};
