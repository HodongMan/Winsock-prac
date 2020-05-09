#include "pch.h"

#include "IOThread.h"

#define		GQCS_TIMEOUT 20


IOThread::IOThread( HANDLE threadHandle, HANDLE completionPortHandle )
	: _threadHandle{ threadHandle }
	, _completionPortHandle{ completionPortHandle }
{

}

IOThread::~IOThread( void )
{
	CloseHandle( _threadHandle );
}

DWORD IOThread::run( void ) noexcept
{
	while ( true )
	{
		doIOCPJob();
	}

	return 1;
}

void IOThread::doIOCPJob( void ) noexcept
{
	DWORD dwTransferred			= 0;
	LPOVERLAPPED overlapped		= nullptr;

	ULONG_PTR completionKey		= 0;

	const int ret				= GetQueuedCompletionStatus( _completionPortHandle, &dwTransferred, (PULONG_PTR)&completionKey, &overlapped, GQCS_TIMEOUT );
	if ( ( 0 == ret ) || ( 0 == dwTransferred ) )
	{
	
	}

}


HANDLE IOThread::getHandle( void ) const noexcept
{
	return _threadHandle;
}
