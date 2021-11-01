#include "..\includes\Log.h"
#include "../includes/String.h"
#include <cstdio>

Log::Log(const String& path, const String& name)
{
	_pPath = new String(path);
	_pName = new String(name);
	_pName->PushBack(".log");
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
	text.PushBack(errMsg);
	text.PushBack('\n');
	text.Write(_pPath->PushBack(*_pName), "a");
	printf("%s", text.C_Str());
	return *this;
}

Log& Log::Warn(const String& warnMsg)
{
	String text("[Warn]");
	text.PushBack(warnMsg);
	text.PushBack('\n');
	text.Write(_pPath->PushBack(*_pName), "a");
	printf("%s", text.C_Str());
	return *this;
}

Log& Log::Info(const String& infoMsg)
{
	String text("[Info]");
	text.PushBack(infoMsg);
	text.PushBack('\n');
	text.Write(_pPath->PushBack(*_pName), "a");
	printf("%s", text.C_Str());
	return *this;
}