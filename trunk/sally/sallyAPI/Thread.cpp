////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file	sallyAPI\Thread.cpp
///
/// \brief	Implements the thread class. 
///
/// \author	Christian Knobloch
/// \date	13.09.2010
///
/// This file is part of the Sally Project
/// 
/// Copyright(c) 2008-2010 Sally Project
/// http://www.sally-project.de/
///
/// This program is free software: you can redistribute it and/or modify
/// it under the terms of the GNU Lesser General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
/// 
/// This program is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
/// GNU Lesser General Public License for more details.
/// 
/// You should have received a copy of the GNU Lesser General Public License
/// along with this program. If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Thread.h"

using namespace SallyAPI::System;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	CThread::CThread()
///
/// \brief	Default constructor. 
///
/// \author	Christian Knobloch
/// \date	19.04.2010
////////////////////////////////////////////////////////////////////////////////////////////////////

CThread::CThread()
{
	m_hThread = NULL;
	m_eStatus = THREAD_STOPPED;
	m_bPleaseStop = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	CThread::~CThread()
///
/// \brief	Destructor. 
///
/// \author	Christian Knobloch
/// \date	19.04.2010
////////////////////////////////////////////////////////////////////////////////////////////////////

CThread::~CThread()
{
	m_eStatus = THREAD_STOPPED;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	DWORD WINAPI CThread::Thread(PVOID pvoid)
///
/// \brief	Threads. 
///
/// \author	Christian Knobloch
/// \date	19.04.2010
///
/// \param	pvoid	The pvoid. 
///
/// \return	. 
////////////////////////////////////////////////////////////////////////////////////////////////////

DWORD WINAPI CThread::Thread(PVOID pvoid)
{
	CThread* parent = reinterpret_cast<CThread*>(pvoid);

	parent->Run();

	ExitThread(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	ThreadStatus CThread::GetStatus()
///
/// \brief	Gets the status. 
///
/// \author	Christian Knobloch
/// \date	19.04.2010
///
/// \return	The status. 
////////////////////////////////////////////////////////////////////////////////////////////////////

ThreadStatus CThread::GetStatus()
{
	SallyAPI::System::CAutoLock lock(&m_Lock);

	return m_eStatus;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void CThread::Start()
///
/// \brief	Starts this object. 
///
/// \author	Christian Knobloch
/// \date	19.04.2010
////////////////////////////////////////////////////////////////////////////////////////////////////

void CThread::Start()
{
	SallyAPI::System::CAutoLock lock(&m_Lock);

	if (m_hThread != NULL)
		return;

	m_eStatus = THREAD_RUNNING;
	m_hThread = ::CreateThread(NULL, NULL, CThread::Thread, this, 0, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void CThread::Stop(bool force)
///
/// \brief	Stops. 
///
/// \author	Christian Knobloch
/// \date	19.04.2010
///
/// \param	force	true to force. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void CThread::Stop(bool force)
{
	SallyAPI::System::CAutoLock lock(&m_Lock);

	if (m_eStatus == THREAD_STOPPED)
		return;

	m_bPleaseStop = true;

	if (force)
	{
		TerminateThread(m_hThread, 0);
		m_eStatus = THREAD_STOPPED;
		m_hThread = NULL;
		m_bPleaseStop = false;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void CThread::WaitForStop(bool force)
///
/// \brief	Wait for stop. 
///
/// \author	Christian Knobloch
/// \date	19.04.2010
///
/// \param	force	true to force. 
////////////////////////////////////////////////////////////////////////////////////////////////////

void CThread::WaitForStop(bool force)
{
	Stop(force);

	// now wait for the stop
	while (m_eStatus == THREAD_RUNNING)
	{
		Sleep(1);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void CThread::Run()
///
/// \brief	Runs this object. 
///
/// \author	Christian Knobloch
/// \date	19.04.2010
////////////////////////////////////////////////////////////////////////////////////////////////////

void CThread::Run()
{
	RunEx();

	SallyAPI::System::CAutoLock lock(&m_Lock);

	m_eStatus = THREAD_STOPPED;
	m_hThread = NULL;
	m_bPleaseStop = false;
}