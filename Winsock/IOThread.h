#pragma once

class IOThread
{
public:
	IOThread( HANDLE threadHandle, HANDLE completionPortHandle );
	~IOThread( void );

	DWORD			run( void ) noexcept;

	void			doIOCPJob( void ) noexcept;

	HANDLE			getHandle( void ) const noexcept;

private:

	HANDLE _threadHandle;
	HANDLE _completionPortHandle;
};