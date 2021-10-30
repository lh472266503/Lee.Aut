#pragma once

#include <cstdio>
#include <memory>
#include <iostream>

class String
{
public:
	template<typename ...Args>
	static String Format(const char* fmt, Args... args);

	template<typename ...Args>
	String& FormatSelf(const char* fmt, Args... args);

	String();
	String(const char other);
	String(const char* other);
	String(const String& other);
	String(const size_t size, const char value);
	virtual ~String();

	const size_t Size(void) const noexcept { return _size; }
	const bool Empty(void) const noexcept { return _str == nullptr || _str == "\0"; }
	const char* CStr(void) const noexcept { return _str == nullptr ? "" : _str; }

	String& Insert(const size_t index, const String& other);
	String& InsertFront(const String& other);
	String& InsertBack(const String& other);
	String Cut(const size_t index, const size_t length) const;
	String& Write(const String& file, const String& mode) ;

	String& ToLower(void);
	String& ToUpper(void);

	friend std::ostream& operator<<(std::ostream& out, const String& other);
	friend std::istream& operator>>(std::istream& in, String& other);

	String& operator=(const String& other);
	char& operator[](const size_t index) { return _str[index]; }
	const char& operator[](const size_t index)const { return _str[index]; }
	String operator+(const String& right) const;
	String& operator+=(const String& right) { return this->InsertBack(right); }
protected:
private:
	String& _CopyFrom(const char other);
	String& _CopyFrom(const char* other);
	String& _CopyFrom(const  String& other);
private:
	char* _str{ nullptr };
	size_t _size{ 0 };
};

template<typename ...Args>
inline String String::Format(const char* fmt, Args ...args)
{
	int size = snprintf(nullptr, 0, fmt, args...);
	if (size <= 0) {
		return "\0";
	}
	String rStr(size, '\0');
	snprintf(&(rStr[0]), rStr.Size() + 1, fmt, args...);
	return rStr;
}

template<typename ...Args>
inline String& String::FormatSelf(const char* fmt, Args ...args)
{
	int size = snprintf(nullptr, 0, fmt, args...);
	if (size <= 0) {
		return *this;;
	}
	if (_str) {
		free(_str);
		_str = nullptr;
		_size = 0;
	}
	_size = size;
	_str = (char*)malloc(sizeof(char) * (_size + 1));
	memset(_str, 0, sizeof(char) * (_size + 1));
	snprintf(_str, _size + 1, fmt, args...);
	return *this;
}
