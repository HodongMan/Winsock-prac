#include "pch.h"

#include "TcpSocket.h"

TcpSocket::TcpSocket( void )
{
}

TcpSocket::~TcpSocket( void )
{
#ifdef _WIN32
	closesocket( _socket );

#endif

}

bool TcpSocket::initialize( void ) noexcept
{
#ifdef _WIN32
	WSADATA wsaData;
	if ( 0 != WSAStartup( MAKEWORD( 2, 2 ), &wsaData ) )
	{
		return false;
	}

	return true;
#endif

	return false;
}

bool TcpSocket::createSocket( const int afInet, int type, int protocol ) noexcept
{
#ifdef _WIN32
	return WSASocket( afInet, type, protocol, NULL, 0, WSA_FLAG_OVERLAPPED );
#endif

	return false;
}

bool TcpSocket::connectSocket( const char * address, const unsigned short port ) noexcept
{
	if ( nullptr == address )
	{
		return false;
	}

	sockaddr_in  socketAddress;
	memset( &socketAddress, 0, sizeof( socketAddress ) );
	socketAddress.sin_family			= AF_INET;
	socketAddress.sin_port				= htons( port );
	inet_pton( AF_INET, address, &socketAddress.sin_addr );

	if ( 0 == WSAConnect( _socket,( const sockaddr* )&socketAddress, sizeof( socketAddress ), NULL, NULL, NULL, NULL ) )
	{
		return true;
	}

	const int error = getLastError();
	if( ( WSAEWOULDBLOCK == error ) || ( WSAEINPROGRESS == error ) )
	{
		return true;
	}

	return false;
}

bool TcpSocket::bindSocket( const char * address, const unsigned short port ) noexcept
{
	if ( nullptr == address )
	{
		return false;
	}
	if ( nullptr == address )
	{
		return false;
	}

	sockaddr_in  socketAddress;
	ZeroMemory( &socketAddress, 0, sizeof( socketAddress ) );
	socketAddress.sin_family			= AF_INET;
	socketAddress.sin_port				= htons( port );
	socketAddress.sin_addr.s_addr		= htonl( INADDR_ANY );

	if ( SOCKET_ERROR == bind( _socket, (const SOCKADDR*)&socketAddress, sizeof( socketAddress ) ) )
	{
		return false;
	}
	
	return true;
}

int TcpSocket::getLastError( void ) const noexcept
{
#ifdef _WIN32
	return WSAGetLastError();
#endif

	return 0;
}

bool TcpSocket::isValid( void ) const noexcept
{
	if ( ( 0 == _socket ) || ( INVALID_SOCKET == _socket ) )
	{
		return false;
	}

	return true;
}

bool TcpSocket::release( void ) noexcept
{
#ifdef _WIN32
	return 0 == WSACleanup();
#endif

	return false;
}
