#pragma once

#include "TypeSession.h"

class IOThread;


class IOCPManager
{
public:

	~IOCPManager( void );

	static IOCPManager*		getInstance( void ) noexcept;

	bool					initialize( const int port ) noexcept;
	void					release( void ) noexcept;

	bool					startIOThread( void ) noexcept;

	HANDLE					getComletionPort( void ) const noexcept;

private:

	IOCPManager( void );

	static unsigned int WINAPI WorkerThreadFunc( LPVOID lpParam ) noexcept;

private:

	HANDLE					_completionPortHandle;

	IOThread*				_ioWorkerThread[ MAX_WORKER_THREAD ];
};