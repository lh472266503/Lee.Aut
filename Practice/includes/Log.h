#pragma once

class String;

class Log
{
public:
	Log(const String& path, const String& name);
	~Log();

	Log& Error(const String& errMsg);
	Log& Warn(const String& warnMsg);
	Log& Info(const String& infoMsg);
private:
	String* _pPath{ nullptr };
	String* _pName{ nullptr };
};