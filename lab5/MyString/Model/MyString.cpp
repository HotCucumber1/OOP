#include "MyString.h"
#include <cassert>
#include <cstring>
#include <memory>
#include <sstream>
#include <utility>

char* Allocate(size_t size)
{
	return static_cast<char*>(operator new(size));
}

void Deallocate(const char* buffer) noexcept
{
	delete[] buffer;
}

MyString::MyString() noexcept
	: m_chars(s_emptyString)
{
}

MyString::MyString(const char* pString, size_t length)
	: m_size(length)
	, m_capacity(m_size)
	, m_chars(Allocate(m_capacity + 1))
{
	// TODO утечка памяти в Allocate
	try
	{
		if (pString == nullptr)
		{
			return;
		}
		std::uninitialized_copy_n(pString, m_size + 1, m_chars);
		m_chars[m_size] = s_emptyString[0];
	}
	catch (const std::exception& exception)
	{
		delete[] m_chars;
		throw exception;
	}
}

MyString::MyString(const char* pString)
	: MyString(
		  pString,
		  (pString == nullptr) ? 0 : strlen(pString))
{
}

MyString::MyString(const MyString& other)
	: m_size(other.m_size)
	, m_capacity(other.m_capacity)
	, m_chars(Allocate(m_capacity + 1))
{
	try
	{
		std::uninitialized_copy_n(other.m_chars, m_size + 1, m_chars);
		m_chars[m_size] = s_emptyString[0];
	}
	catch (const std::exception& exception)
	{
		operator delete(m_chars);
		throw exception;
	}
}

MyString::MyString(MyString&& other) noexcept
	: m_size(std::exchange(other.m_size, 0))
	, m_capacity(std::exchange(other.m_capacity, 0))
	, m_chars(std::exchange(other.m_chars, s_emptyString))
{
}

MyString::MyString(const std::string& stlString)
	: MyString(stlString.data(), stlString.length())
{
}

MyString::~MyString()
{
	if (m_chars != s_emptyString)
	{
		std::destroy_n(m_chars, m_size + 1);
		Deallocate(m_chars);
	}
}

size_t MyString::GetLength() const
{
	return m_size;
}

const char* MyString::GetStringData() const
{
	return m_chars;
}

MyString MyString::SubString(size_t start, size_t length) const
{
	assert(start <= m_size);
	// min (len, m_size - m_start);
	if (start > m_size)
	{
		return {};
	}
	if (length > m_size - start)
	{
		return { m_chars + start, m_size - start };
	}
	return { m_chars + start, length };
}

void MyString::Clear()
{
	if (m_chars == s_emptyString)
	{
		return;
	}
	Deallocate(m_chars);
	Allocate(1);

	m_chars = s_emptyString;
	m_size = 0;
	m_capacity = 1;
}

size_t MyString::GetCapacity() const
{
	return m_capacity;
}

MyString& MyString::operator=(const MyString& other)
{
	if (this == &other)
	{
		return *this;
	}

	if (m_capacity >= other.m_size && m_chars != s_emptyString)
	{
		std::destroy_n(m_chars, m_size + 1);
		std::uninitialized_copy_n(other.m_chars, m_size + 1, m_chars);
		m_size = other.m_size;
	}
	else
	{
		MyString copy(other);
		std::swap(m_size, copy.m_size);
		std::swap(m_capacity, copy.m_capacity);
		std::swap(m_chars, copy.m_chars);
	}
	return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept
{
	if (this != &other)
	{
		std::swap(m_size, other.m_size);
		std::swap(m_capacity, other.m_capacity);
		std::swap(m_chars, other.m_chars);
	}
	return *this;
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
	MyString resStr;
	resStr.m_size = lhs.m_size + rhs.m_size;
	resStr.m_capacity = resStr.m_size + 2;

	resStr.m_chars = Allocate(resStr.m_capacity);

	if (lhs.m_size > 0)
	{
		memcpy(resStr.m_chars, lhs.m_chars, lhs.m_size);
	}
	if (rhs.m_size > 0)
	{
		memcpy(resStr.m_chars + lhs.m_size, rhs.m_chars, rhs.m_size);
	}
	resStr.m_chars[resStr.m_size] = '\0';
	return resStr;
}

MyString operator+(const std::string& lhs, const MyString& rhs)
{
	MyString resStr;
	resStr.m_size = lhs.length() + rhs.m_size;

	return resStr + rhs;
}

MyString operator+(const char* lhs, const MyString& rhs)
{
	MyString resStr;
	resStr.m_size = strlen(lhs) + rhs.m_size;

	return resStr + rhs;
}

MyString& MyString::operator+=(const MyString& other)
{
	*this = *this + other;
	return *this;
}

const char& MyString::operator[](size_t index) const
{
	assert(index < m_size);
	if (index >= this->m_size)
	{
		throw std::out_of_range("String index out of range");
	}
	return m_chars[index];
}

char& MyString::operator[](size_t index)
{
	assert(index < m_size);
	if (index >= this->m_size)
	{
		throw std::out_of_range("String index out of range");
	}
	return m_chars[index];
}

std::ostream& operator<<(std::ostream& output, const MyString& string)
{
	for (size_t i = 0; i < string.m_size; i++)
	{
		output << string.m_chars[i];
	}
	return output;
}

std::istream& operator>>(std::istream& input, MyString& string)
{
	const size_t maxStringLength = 4096;
	char buffer[maxStringLength];

	input.getline(buffer, maxStringLength);

	string = MyString(buffer);
	return input;
}

std::strong_ordering operator<=>(const MyString& lhs, const MyString& rhs)
{
	auto cmp = std::strcmp(lhs.m_chars, rhs.m_chars);

	if (cmp < 0)
	{
		return std::strong_ordering::less;
	}
	if (cmp > 0)
	{
		return std::strong_ordering::greater;
	}
	return std::strong_ordering::equivalent;
}

bool operator==(const MyString& lhs, const MyString& rhs)
{
	return std::strcmp(lhs.m_chars, rhs.m_chars) == 0;
}

char* MyString::begin()
{
	return m_chars;
}

char* MyString::end()
{
	return m_chars + m_size;
}

const char* MyString::begin() const
{
	return m_chars;
}

const char* MyString::end() const
{
	return m_chars + m_size;
}

const char* MyString::cbegin() const
{
	return m_chars;
}

const char* MyString::cend() const
{
	return m_chars + m_size;
}

std::reverse_iterator<char*> MyString::rbegin()
{
	return std::reverse_iterator<char*>(end());
}

std::reverse_iterator<char*> MyString::rend()
{
	return std::reverse_iterator<char*>(begin());
}

std::reverse_iterator<const char*> MyString::rbegin() const
{
	return std::reverse_iterator<const char*>(end());
}

std::reverse_iterator<const char*> MyString::rend() const
{
	return std::reverse_iterator<const char*>(begin());
}

std::reverse_iterator<const char*> MyString::crbegin() const
{
	return std::reverse_iterator<const char*>(cend());
}

std::reverse_iterator<const char*> MyString::crend() const
{
	return std::reverse_iterator<const char*>(cbegin());
}
