#pragma once
#include <string>

class MyString
{
public:
	MyString() noexcept;
	explicit MyString(const char* pString);
	MyString(const char* pString, size_t length);
	MyString(const MyString& other);
	MyString(MyString&& other) noexcept;
	explicit MyString(const std::string& stlString);

	~MyString();
	void Clear();

	size_t GetLength() const;
	const char* GetStringData() const;
	size_t GetCapacity() const;

	MyString SubString(size_t start, size_t length = SIZE_MAX) const;

	MyString& operator=(const MyString& other);
	MyString& operator=(MyString&& other) noexcept;
	friend MyString operator+(const MyString& lhs, const MyString& rhs);
	friend MyString operator+(const std::string& lhs, const MyString& rhs);
	friend MyString operator+(const char* lhs, const MyString& rhs);
	MyString& operator+=(const MyString& other);
	friend std::strong_ordering operator<=>(const MyString& lhs, const MyString& rhs);
	friend bool operator==(const MyString& lhs, const MyString& rhs);
	const char& operator[](size_t index) const;
	char& operator[](size_t index);
	friend std::ostream& operator<<(std::ostream& output, const MyString& string);
	friend std::istream& operator>>(std::istream& input, MyString& string);

	char* begin();
	char* end();

	const char* begin() const;
	const char* end() const;

	const char* cbegin() const;
	const char* cend() const;

	std::reverse_iterator<char*> rbegin();
	std::reverse_iterator<char*> rend();

	std::reverse_iterator<const char*> rbegin() const;
	std::reverse_iterator<const char*> rend() const;

	std::reverse_iterator<const char*> crbegin() const;
	std::reverse_iterator<const char*> crend() const;

private:
	inline static char s_emptyString[] = { '\0' };

	size_t m_size = 0;
	size_t m_capacity = 0;
	char* m_chars;
};