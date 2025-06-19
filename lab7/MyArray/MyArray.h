#pragma once
#include <iterator>
#include <utility>

template <typename T>
class MyArray
{
public:
	MyArray() = default;

	MyArray(const MyArray& other)
		: m_size(other.m_size)
		, m_capacity(other.m_capacity)
	{
		m_content = new T[other.m_size];
		for (size_t i = 0; i < other.m_size; i++)
		{
			m_content[i] = other.m_content[i];
		}
	}

	MyArray(MyArray&& other) noexcept
		: m_size(std::exchange(other.m_size, 0))
		, m_capacity(std::exchange(other.m_capacity, 0))
		, m_content(std::exchange(other.m_content, nullptr))
	{
	}

	~MyArray() noexcept
	{
		Clear();
	}

	void PushBack(const T& newItem)
	{
		if (m_capacity <= m_size + 1)
		{
			size_t newCapacity = m_capacity * 2 + 1;
			T* temp = new T[newCapacity];

			try
			{
				for (size_t i = 0; i < m_size; i++)
				{
					temp[i] = std::move(m_content[i]);
				}
			}
			catch (...)
			{
				delete[] temp;
				throw;
			}

			delete[] m_content;
			m_content = temp;
			m_capacity = newCapacity;
		}
		m_content[m_size++] = newItem;
	}

	size_t GetSize() const
	{
		return m_size;
	}

	void Clear() noexcept
	{
		delete[] m_content;
		m_content = nullptr;
		m_size = 0;
		m_capacity = 0;
	}

	void Resize(size_t size)
	{
		if (size == m_size)
		{
			return;
		}

		T* newContent = new T[size];
		size_t minSize = std::min(m_size, size);
		for (size_t i = 0; i < minSize; i++)
		{
			newContent[i] = m_content[i];
		}
		for (size_t i = m_size; i < size; i++)
		{
			newContent[i] = T();
		}

		delete[] m_content;
		m_content = newContent;
		m_size = size;
		m_capacity = size;
	}

	MyArray& operator=(const MyArray& other) noexcept
	{
		if (&other == this)
		{
			return *this;
		}
		MyArray temp(other);
		this = std::move(temp);

		return *this;
	}

	MyArray& operator=(MyArray&& other) noexcept
	{
		if (&other == this)
		{
			return *this;
		}

		delete[] m_content;
		m_content = other.m_content;
		m_size = other.m_size;
		m_capacity = other.m_capacity;
		other.Clear();

		return *this;
	}

	template <typename V>
	MyArray& operator=(const MyArray<V>& other)
	{
		if (reinterpret_cast<const void*>(&other) == reinterpret_cast<const void*>(this))
		{
			return *this;
		}
		T* newContent = new T[other.GetSize()];
		try
		{
			for (size_t i = 0; i < other.GetSize(); i++)
			{
				newContent[i] = static_cast<T>(other[i]);
			}
		}
		catch (...)
		{
			delete[] newContent;
			throw;
		}

		delete[] m_content;
		m_content = newContent;
		m_size = other.GetSize();
		m_capacity = other.GetSize() + 1;

		return *this;
	}

	T& operator[](size_t index)
	{
		if (index >= m_size)
		{
			throw std::out_of_range("Index out of range");
		}
		return m_content[index];
	}

	const T& operator[](size_t index) const
	{
		if (index >= m_size)
		{
			throw std::out_of_range("Index out of range");
		}
		return m_content[index];
	}

	T* begin()
	{
		return m_content;
	}

	T* end()
	{
		return m_content + m_size;
	}

	std::reverse_iterator<T*> rbegin()
	{
		return std::reverse_iterator<T*>(end());
	}
	std::reverse_iterator<T*> rend()
	{
		return std::reverse_iterator<T*>(begin());
	}

private:
	T* m_content = nullptr;
	size_t m_size = 0;
	size_t m_capacity = 0;
};
