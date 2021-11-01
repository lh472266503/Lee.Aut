#include "../includes/String.h"
#include "../includes/Log.h"
#include <memory>
#include <cstdarg>

static Log sLog("F:\\Microsoft Visual Studio\\2019\\Projects\\Lee.Aut\\Practice\\log\\", "String");

String String::Slice(const size_t index, const size_t length, const String& dstStr)
{
	if (length == 0) {
		sLog.Warn("Cut length is 0.");
		return "\0";
	}
	if (index + length > dstStr._size) {
		sLog.Error("Cut index with length is overflow string length.");
		return "\0";
	}
	char* cutStr = (char*)malloc(sizeof(char) * (length + 1));
	memset(cutStr, 0, sizeof(char) * (length + 1));
	memcpy(cutStr, &(dstStr._str[index]), sizeof(char) * length);
	String rStr(cutStr);
	free(cutStr);
	return rStr;
}

String::String()
{
}

String::String(const char other)
{
	_CopyFrom(other);
}

String::String(const char* other)
{
	_CopyFrom(other);
}

String::String(const String& other)
{
	_CopyFrom(other);
}

String::String(const size_t size, const char value)
{
	if (size == 0) {
		sLog.Error("String length can not equal to zero.");
		return;
	}
	_size = size;
	_str = (char*)malloc(sizeof(char) * (_size + 1));
	memset(_str, value, sizeof(char) * _size);
	_str[_size] = '\0';
}

String::~String()
{
	free(_str);
	_str = nullptr;
	_size = 0;
}

String& String::Insert(const size_t index, const String& other)
{
	if (index > _size) {
		sLog.Error("Insert index is greater than string length.");
		return *this;
	}
	if (Empty()) {
		return _CopyFrom(other);
	}
	size_t rSize = _size + other._size;
	char* rStr = (char*)malloc(sizeof(char) * (rSize + 1));
	memset(rStr, 0, sizeof(char) * (rSize + 1));
	memcpy(rStr, _str, sizeof(char) * index);
	memcpy(&(rStr[index]), other._str, sizeof(char) * other._size);
	memcpy(&(rStr[index + other._size]), &(_str[index]), sizeof(char) * (_size - index));
	free(_str);
	_str = rStr;
	rStr = nullptr;
	_size = rSize;
	return *this;
}

String& String::PushFront(const String& other)
{
	return Insert(0, other);
}

String& String::PushBack(const String& other)
{
	return Insert(_size, other);
}

String String::Slice(const size_t index, const size_t length) const
{
	if (length == 0) {
		sLog.Warn("Cut length is 0.");
		return "\0";
	}
	if (index + length > _size) {
		sLog.Error("Cut index with length is overflow string length.");
		return "\0";
	}
	char* cutStr = (char*)malloc(sizeof(char) * (length + 1));
	memset(cutStr, 0, sizeof(char) * (length + 1));
	memcpy(cutStr, &(_str[index]), sizeof(char) * length);
	String rStr(cutStr);
	free(cutStr);
	return rStr;
}

String& String::Write(const String& file, const String& mode)
{
	if (Empty()) {
		sLog.Warn("String is empty, can not write in file.");
		return *this;
	}
	FILE* wFile = nullptr;
	fopen_s(&wFile, file.C_Str(), mode.C_Str());
	if (!wFile) {
		sLog.Error("Log file open failed.");
		return *this;
	}
	fprintf(wFile, "%s", _str);
	fclose(wFile);
	return *this;
}
String& String::ToLower(void)
{
	if (Empty()) {
		sLog.Warn("String is empty, can not convert to lower.");
		return *this;
	}
	for (size_t i = 0; i < _size; ++i) {
		if (_str[i] >= 'A' && _str[i] <= 'Z') {
			_str[i] += 32;
		}
	}
	return *this;
}

String& String::ToUpper(void)
{
	if (Empty()) {
		sLog.Warn("String is empty, can not convert to upper.");
		return *this;
	}
	for (size_t i = 0; i < _size; ++i) {
		if (_str[i] >= 'a' && _str[i] <= 'z') {
			_str[i] -= 32;
		}
	} return *this;
}

String& String::operator=(const String& other)
{
	return _CopyFrom(other);
}

String String::operator+(const String& right) const
{
	String rStr(_str);
	return rStr.PushBack(right);
}

String& String::_CopyFrom(const char other)
{
	if (_str) {
		free(_str);
		_str = nullptr;
		_size = 0;
	}
	_size = 1;
	_str = (char*)malloc(sizeof(char) * (_size + 1));
	memset(_str, 0, sizeof(char) * (_size + 1));
	memcpy(_str, &other, sizeof(char) * _size);
	return *this;
}

String& String::_CopyFrom(const char* other)
{
	if (_str) {
		free(_str);
		_str = nullptr;
		_size = 0;
	}
	_size = strlen(other);
	_str = (char*)malloc(sizeof(char) * (_size + 1));
	memset(_str, 0, sizeof(char) * (_size + 1));
	memcpy(_str, other, sizeof(char) * _size);
	return *this;
}

String& String::_CopyFrom(const String& other)
{
	if (this == &other) {
		return *this;
	}
	if (_str) {
		free(_str);
		_str = nullptr;
		_size = 0;
	}
	if (other.Empty()) {
		sLog.Warn("Please don't copy a empty string.");
		return *this;
	}
	_size = other._size;
	_str = (char*)malloc(sizeof(char) * (_size + 1));
	memset(_str, 0, sizeof(char) * (_size + 1));
	memcpy(_str, other._str, sizeof(char) * _size);
	return *this;
}

std::ostream& operator<<(std::ostream& out, const String& other)
{
	return other.Empty() ? out << "\0" : out << other._str;
}

std::istream& operator>>(std::istream& in, String& other)
{
	char temp = '\0';
	while ((temp = getchar()) != '\n')
	{
		other.PushBack(temp);
	}
	return in;
}