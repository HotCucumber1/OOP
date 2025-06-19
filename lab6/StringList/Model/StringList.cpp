#include "StringList.h"
#include <utility>
#include <iostream>


StringList::StringList(const StringList& otherList)
{
	if (otherList.m_head == nullptr)
	{
		m_head = nullptr;
		m_tail = nullptr;
		m_length = 0;
		return;
	}
	m_head = std::make_unique<ListNode>();
	m_head->data = otherList.m_head->data;
	m_head->prev = nullptr;

	auto currentNode = m_head.get();
	auto otherListCurrentNode = otherList.m_head.get();

	while (otherListCurrentNode->next != nullptr)
	{
		auto newNode = std::make_unique<ListNode>();
		newNode->data = otherListCurrentNode->next->data;
		newNode->prev = currentNode;

		currentNode->next = std::move(newNode);
		currentNode = currentNode->next.get();
		otherListCurrentNode = otherListCurrentNode->next.get();
	}

	m_tail = currentNode;
	m_length = otherList.m_length;
}

StringList::StringList(StringList&& otherList) noexcept
	: m_length(std::exchange(otherList.m_length, 0))
	, m_head(std::exchange(otherList.m_head, nullptr))
	, m_tail(std::exchange(otherList.m_tail, nullptr))
{
	// otherList.m_head = nullptr;
}

StringList::~StringList() noexcept
{
	Clear();
}

void StringList::PushBack(const std::string& string)
{
	auto newNode = std::make_unique<ListNode>();
	newNode->data = string;
	newNode->next = nullptr;
	newNode->prev = m_tail;

	if (IsEmpty())
	{
		m_head = std::move(newNode);
		m_tail = m_head.get();
	}
	else
	{
		m_tail->next = std::move(newNode);
		m_tail = m_tail->next.get();
	}

	m_length++;
}

void StringList::PushFront(const std::string& string)
{
	auto newNode = std::make_unique<ListNode>();
	if (!IsEmpty())
	{
		m_head->prev = newNode.get();
	}

	newNode->data = string;
	newNode->next = std::move(m_head);
	newNode->prev = nullptr;

	m_head = std::move(newNode);
	m_length++;
}

void StringList::Clear()
{
	while (m_head != nullptr)
	{
		auto next = std::move(m_head->next);
		m_head.reset();
		m_head = std::move(next);
	}
	m_length = 0;
	m_tail = nullptr;
}

void StringList::Insert(StringList::Iterator pos, const std::string& value)
{
	// TODO test
	if (pos.m_node == nullptr && pos != end())
	{
		throw std::invalid_argument("Invalid iterator position");
	}
	if (pos == end())
	{
		PushBack(value);
		return;
	}
	if (pos == begin())
	{
		PushFront(value);
		return;
	}

	ListNode* current = pos.m_node;
	auto newNode = std::make_unique<ListNode>();
	newNode->data = value;

	newNode->prev = current->prev;
	newNode->next = std::move(current->prev->next);
	current->prev = newNode.get();
	newNode->prev->next = std::move(newNode);

	m_length++;
}

void StringList::Erase(StringList::Iterator pos)
{
	if (pos == end() || pos.m_node == nullptr)
	{
		throw std::out_of_range("Cannot erase iterator");
	}

	if (m_head.get() == m_tail)
	{
		m_head.reset();
		m_tail = nullptr;
	}
	else if (pos.m_node == m_head.get())
	{
		m_head = std::move(m_head->next);
		m_head->prev = nullptr;
	}
	else if (pos.m_node == m_tail)
	{
		m_tail = m_tail->prev;
		m_tail->next.reset();
	}
	else
	{
		ListNode* prevNode = pos.m_node->prev;
		prevNode->next = std::move(pos.m_node->next);
		prevNode->next->prev = prevNode;
	}

	m_length--;
}

size_t StringList::GetLength() const
{
	return m_length;
}

bool StringList::IsEmpty() const
{
	return m_length == 0;
}

StringList& StringList::operator=(const StringList& other)
{
	if (this != &other)
	{
		StringList newList(other);
		std::swap(m_head, newList.m_head);
		std::swap(m_tail, newList.m_tail);
		std::swap(m_length, newList.m_length);
	}
	return *this;
}

StringList& StringList::operator=(StringList&& other) noexcept
{
	if (this != &other)
	{
		std::swap(m_head, other.m_head);
		std::swap(m_tail, other.m_tail);
		std::swap(m_length, other.m_length);
	}
	return *this;
}

StringList::Iterator StringList::begin()
{
	if (m_head)
	{
		return Iterator(m_head.get(), m_tail);
	}
	return Iterator(nullptr, m_tail);
}

StringList::Iterator StringList::end()
{
	return Iterator(nullptr, m_tail);
}

StringList::ConstIterator StringList::cbegin() const
{
	if (m_head)
	{
		return ConstIterator(m_head.get(), m_tail);
	}
	return ConstIterator(nullptr, m_tail);
}

StringList::ConstIterator StringList::cend() const
{
	return ConstIterator(nullptr, m_tail);
}

StringList::ReverseIterator StringList::rbegin()
{
	return ReverseIterator(end());
}

StringList::ReverseIterator StringList::rend()
{
	return ReverseIterator(begin());
}

StringList::ConstReverseIterator StringList::crbegin() const
{
	return ConstReverseIterator(cend());
}

StringList::ConstReverseIterator StringList::crend() const
{
	return ConstReverseIterator(cbegin());
}
