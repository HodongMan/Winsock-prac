#pragma once


class TcpSocket
{
public:
	TcpSocket( void );
	~TcpSocket( void );

	bool			initialize( void ) noexcept;

	bool			createSocket( const int afInet, int type, int protocol ) noexcept;

	bool			connectSocket( const char* address, const unsigned short port ) noexcept;
	bool			bindSocket( const char* address, const unsigned short port ) noexcept;

	int				getLastError( void ) const noexcept;
	bool			isValid( void ) const noexcept;

	bool			release( void ) noexcept;


private:


	SOCKET		_socket;
};