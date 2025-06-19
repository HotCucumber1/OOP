#pragma once
#include <memory>
#include <string>

class StringList
{
private:
	struct ListNode
	{
		std::string data;
		std::unique_ptr<ListNode> next;
		ListNode* prev;
	};

public:
	template <typename ValueType, typename NodeType, bool IsConst = false>
	class BaseIterator
	{
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = std::string;
		using difference_type = std::ptrdiff_t;
		using pointer = std::conditional_t<IsConst, const ValueType*, ValueType*>;
		using reference = std::conditional_t<IsConst, const ValueType&, ValueType&>;

	public:
		explicit BaseIterator(NodeType* node, NodeType* tail)
			: m_node(node)
			, m_tail(tail)
		{
		}

		template <bool IsOtherConst, typename = std::enable_if_t<IsConst && !IsOtherConst>>
		explicit BaseIterator(const BaseIterator<ValueType, NodeType, IsOtherConst>& other)
			: m_node(other.m_node)
			, m_tail(other.m_tail)
		{
		}

		reference operator*() const { return m_node->data; }
		pointer operator->() const { return &m_node->data; }

		BaseIterator& operator++()
		{
			if (!m_node)
			{
				return *this;
			}
			m_node = m_node->next.get();
			return *this;
		}

		BaseIterator& operator--()
		{
			if (!m_node)
			{
				m_node = m_tail;
			}
			else if (m_node->prev)
			{
				m_node = m_node->prev;
			}
			else
			{
				throw std::out_of_range("Failed to decrement begin() iterator");
			}
			return *this;
		}

		bool operator==(const BaseIterator& other) const = default;

	private:
		friend class StringList;

		NodeType* m_node;
		NodeType* m_tail;
	};

	using Iterator = BaseIterator<std::string, ListNode, false>;
	using ConstIterator = BaseIterator<std::string, ListNode, true>;
	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

public:
	StringList() = default;
	StringList(const StringList& otherList);
	StringList(StringList&& otherList) noexcept;
	~StringList() noexcept;

	void PushBack(const std::string& string);
	void PushFront(const std::string& string);
	void Clear();

	void Insert(Iterator pos, const std::string& value);
	void Erase(Iterator pos);
	size_t GetLength() const;
	bool IsEmpty() const;

	StringList& operator=(const StringList& other);
	StringList& operator=(StringList&& other) noexcept;

	Iterator begin();
	Iterator end();
	ConstIterator cbegin() const;
	ConstIterator cend() const;

	ReverseIterator rbegin();
	ReverseIterator rend();
	ConstReverseIterator crbegin() const;
	ConstReverseIterator crend() const;

private:
	size_t m_length = 0;
	std::unique_ptr<ListNode> m_head = nullptr;
	ListNode* m_tail = nullptr;
};
