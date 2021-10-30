#include "..\includes\Log.h"
#include "../includes/String.h"
#include <cstdio>

Log::Log(const String& path, const String& name)
{
	_pPath = new String(path);
	_pName = new String(name);
	_pName->InsertBack(".log");
}

Log::~Log()
{
	delete _pPath;
	delete _pName;
	_pPath = nullptr;
	_pName = nullptr;
}

Log& Log::Error(const String& errMsg)
{
	String text("[Error]");
	text.InsertBack(errMsg);
	text.InsertBack('\n');
	text.Write(_pPath->InsertBack(*_pName), "a");
	printf("%s", text.CStr());
	return *this;
}

Log& Log::Warn(const String& warnMsg)
{
	String text("[Warn]");
	text.InsertBack(warnMsg);
	text.InsertBack('\n');
	text.Write(_pPath->InsertBack(*_pName), "a");
	printf("%s", text.CStr());
	return *this;
}

Log& Log::Info(const String& infoMsg)
{
	String text("[Info]");
	text.InsertBack(infoMsg);
	text.InsertBack('\n');
	text.Write(_pPath->InsertBack(*_pName), "a");
	printf("%s", text.CStr());
	return *this;
}
