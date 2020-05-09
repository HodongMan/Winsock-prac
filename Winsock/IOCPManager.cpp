#include "pch.h"

#include "IOCPManager.h"

#include "TypeSession.h"
#include "IOThread.h" 


IOCPManager::IOCPManager( void )
	: _completionPortHandle{ NULL }
{
	ZeroMemory( _ioWorkerThread, 0, sizeof( mIoWorkerThread ) );
}

IOCPManager::~IOCPManager( void )
{

}

IOCPManager* IOCPManager::getInstance(void) noexcept
{
	static IOCPManager iocpManager;

	return &iocpManager;
}

bool IOCPManager::initialize( const int port ) noexcept
{
	_completionPortHandle = CreateIoCompletionPort( INVALID_HANDLE_VALUE, NULL, 0, 0 );
	if ( NULL == _completionPortHandle )
	{
		return false;
	}

	return true;
}

void IOCPManager::release( void ) noexcept
{
	for ( int ii = 0; ii < MAX_WORKER_THREAD; ++ii )
	{
		CloseHandle( _ioWorkerThread[ii]->getHandle() );
	}

	CloseHandle( _completionPortHandle );
}

bool IOCPManager::startIOThread( void ) noexcept
{
	for ( int ii = 0; ii < MAX_WORKER_THREAD; ++ii )
	{
		DWORD dwThreadId;
		HANDLE threadHandle = (HANDLE)_beginthreadex( NULL, 0, WorkerThreadFunc, reinterpret_cast<LPVOID>( ii ), CREATE_SUSPENDED, ( unsigned int* )&dwThreadId );
		if ( NULL == threadHandle )
		{
			return false;
		}

		_ioWorkerThread[ii] = new IOThread( threadHandle, _completionPortHandle );
	}

	for ( int ii = 0; ii < MAX_WORKER_THREAD; ++ii )
	{
		ResumeThread( _ioWorkerThread[ii]->getHandle() );
	}

	return true;
}

HANDLE IOCPManager::getComletionPort( void ) const noexcept
{
	return _completionPortHandle;
}

unsigned int WINAPI IOCPManager::WorkerThreadFunc( LPVOID lpParam )
{

}