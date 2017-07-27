
//copy on write
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;

class String
{
public:
	String(char* str = "")
		:_str(new char[(strlen(str) + 5)])
	{
		*((int*)_str) = 1;
		str += 4;
		strcpy(_str, str);
	}

	String(const String& s)
	{
		_str = s._str;
		++GetRefCount();
	}

	String& operator=(const String& s)
	{
		if (_str != s._str)
		{
			if (--(GetRefCount()) == 0)
			{
				delete[] _str;
			}

			_str = s._str;
			++(GetRefCount());

		}

		return *this;
	}

	~String()
	{
		if (--(GetRefCount()) == 0)
		{
			delete[](_str - 4);
		}
	}

	int& GetRefCount()
	{
		return *((int*)(_str - 4));
	}
private:
	char* _str;
};

//Deep Copy
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<cstdlib>
#include<cassert>
using namespace std;

class String
{
public:
	String(char* str = "")
		:_str((char*)malloc(strlen(str) + 1))
	{
		strcpy(_str, str);
		_size = strlen(str);
		_capacity = _size;
	}
	String(const String& s)
	{
		String tmp(s._str);
		Swap(tmp);
	}
	String& operator=(String str)
	{
		Swap(str);
		return *this;
	}
	~String()
	{
		free(_str);
		_size = 0;
		_capacity = 0;
	}
public:
	void Swap(String& s)
	{
		swap(_str, s._str);
		_size = s._size;
		_capacity = s._capacity;
	}
	char* GetStr()
	{
		return _str;
	}
	size_t Size()
	{
		return _size;
	}
	size_t capacity()
	{
		return _capacity;
	}
	//ÔöÉ¾²é¸Ä
public:
	void Expand(size_t n)
	{
		char* tmp = (char*)realloc(_str, n + 1);
		if (tmp != NULL)
		{
			_str = tmp;
		}
		_capacity = n;
	}

	char& operator[](size_t pos)
	{
		assert(pos < _size);

		return *(_str + pos);
	}

	void PushBack(char ch)
	{
		if (_size = _capacity)
		{
			Expand(_size * 2);
		}
		_str[_size] = ch;
		_size += 1;
		_str[_size] = '\0';
	}

	void PushBack(const char* str)
	{
		assert(str);

		size_t len = strlen(str);
		if (_size + len > _capacity)
		{
			Expand(_size + len);
		}

		while (*str)
		{
			_str[_size++] = *(str++);
		}
		_str[_size] = '\0';

		_size += len;
	}

	void Insert(size_t pos, char ch)
	{
		assert(pos < _size);

		int end = _size;

		if (_size == _capacity)
		{
			Expand(_size * 2);
		}

		while (end >= (int)pos)
		{
			_str[end + 1] = _str[end];
			--end;
		}
		_str[pos] = ch;
	}

	void Insert(size_t pos, const char* str)
	{
		assert(pos < _size);

		int len = strlen(str);
		int end = _size;

		if ((_size + len) > _capacity)
		{
			Expand(_size + len);
		}

		while (end >= (int)pos)
		{
			_str[end + len] = _str[end];
			--end;
		}
		while (*str)
		{
			_str[pos++] = *(str++);
		}
		_size += len;
	}

	void Erase(size_t pos, size_t count)
	{
		assert(pos < _size);

		if (pos + count >= _size)
		{
			_str[pos] = '\0';
			_size = pos;
			return;
		}
		else
		{
			while (pos <= _size - count)
			{
				_str[pos] = _str[pos + count];
				++pos;
			}
			_size -= count;
			return;
		}
	}

	size_t Find(char ch) const
	{
		size_t pos = 0;
		while ((_str[pos] != ch) && (_str[pos] != '\0'))
		{
			pos += 1;
		}
		if (_str[pos] == '\0')
			return -1;
		else
			return pos;
	}

	size_t Find(const char* str) const
	{
		assert(str);

		int len = strlen(str);
		size_t src = 0;
		size_t pos = 0;

		while (pos + len <= _size)
		{
			size_t sub = 0;
			src = pos;

			while ((_str[src] == str[sub]) && ((int)sub < len))
			{
				src += 1;
				sub += 1;
			}

			if (sub == len)
				return pos;

			++pos;
		}
		return -1;
	}

public:
	inline bool operator<(const String& s) const
	{
		size_t src = 0;
		size_t sub = 0;

		while ((_str[src] != '\0') && ((s._str[sub] != '\0')))
		{
			if ((_str[src])<s._str[sub])
			{
				return true;
			}
			else if ((_str[src])>(s._str[sub]))
			{
				return false;
			}
			src++;
			sub++;
		}

		if (_str[src] != '\0')
			return true;
		return false;
	}

	inline bool operator<=(const String& s) const
	{
		return (*this < s) || (*this == s);
	}

	inline bool operator>(const String& s) const
	{
		return !((*this) <= (s));
	}

	inline bool operator>=(const String& s) const
	{
		return !((*this) < (s));
	}

	inline bool operator==(const String& s) const
	{
		size_t src = 0;
		size_t sub = 0;

		while ((_str[src] != '\0') && ((s._str[sub] != '\0')))
		{
			if (_str[src] != s._str[sub])
			{
				return false;
			}
			++src;
			++sub;
		}

		if ((_str[src] == '\0') && (s._str[sub] == '\0'))
			return true;
		return false;
	}

	inline bool operator!=(const String& s)const
	{
		return !((*this) == (s));
	}
private:
	char* _str;
	size_t _size;
	size_t _capacity;
};

