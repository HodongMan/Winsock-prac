#pragma once

#include "TypeLog.h"

class Logger
{

public:

	Logger( bool useTimestampFlag, bool useFileLineFlag, int stringLimitCount = -1 );
	virtual ~Logger( void );

	void			setLogLevel( const LogLevel logLevel, const char* string ) noexcept;
	void			log( const LogLevel logLevel, const char* file, const int line, const char* string ) noexcept;

protected:

	virtual void	WriteLog( const char* string ) noexcept = 0;
private:

	bool			_useTimestampFlag;
	bool			_useFileLineFlag;
	int				_stringLimitCount;
	const char*		_levelString[ static_cast<int>( LogLevel::LOG_LEVEL_COUNT ) ];

};