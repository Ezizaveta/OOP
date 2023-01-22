#pragma once
#include <stdexcept>
#include <iterator>
#include <vector>
#include <functional>
#include <array>
#include <memory>
#include <utility>

template <typename Key,
	typename Value,
	typename Compare = std::less<Key>,
	typename Alloc = std::allocator<std::pair<const Key, Value> > >
class SkipList final {
	struct SkipNode;
	static const size_t MaxLevel = 10;
public:
	using key_type = Key;
	using mapped_type = Value;
	using value_type = std::pair<const Key, Value>;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using key_compare = Compare;
	using allocator_type = Alloc;
	using reference = value_type&;
	using const_reference = const value_type&;
	using pointer = typename std::allocator_traits<Alloc>::pointer;
	using const_pointer = typename std::allocator_traits<Alloc>::const_pointer;

	using sh_ptr = std::shared_ptr<SkipNode>;
	using w_ptr = std::weak_ptr<SkipNode>;
	using value_type = std::pair<const Key, Value>;

private:
	using value_ptr = std::unique_ptr<value_type, std::function<void(value_type*)>>;
	struct SkipNode
	{
		value_ptr value;
		std::array<w_ptr, MaxLevel> previous;
		std::array<sh_ptr, MaxLevel> next;
		SkipNode() : value(nullptr) {};
		SkipNode(value_ptr&& _value) : value(std::move(_value)) {};
		bool operator==(const SkipNode& other) const
		{
			return is_equal(value.first, other.value.first) && value.second == other.value.second;
		}
	};
	sh_ptr make_node(const value_type& pair)
	{
		auto ptr = m_alloc.allocate(1);
		auto v_ptr = value_ptr(new(ptr) value_type(pair),
			[this](value_type* ptr1) { ptr1->~value_type(); m_alloc.deallocate(ptr1, 1); });
		return std::make_shared<SkipNode>(std::move(v_ptr));
	}

	
	std::shared_ptr<SkipNode> m_begin;
	std::shared_ptr<SkipNode> m_end;
	size_t level = 0;
	size_type m_size = 0;
	Compare m_comp;
	Alloc m_alloc;

	bool is_equal(const Key& key1, const Key& key2) const
	{
		return (!(m_comp(key1, key2)) && !m_comp(key2, key1));
	}
	
	size_t NewLevel()
	{
		size_t lvl = rand() % (MaxLevel);
		
		return lvl;
	}


private:
	friend class skip_list_iterator;
	template <bool is_const>
	class skip_list_iterator final
	{
		using iterator_category = std::forward_iterator_tag;
		using list_type = std::conditional_t<is_const, const SkipList, SkipList>;
		friend class SkipList;
		list_type* current_list{};
		std::weak_ptr<SkipNode> current_node;
	public:
		using key_type = typename SkipList::value_type;
		using mapped_type = typename SkipList::mapped_type;
		using value_type = typename SkipList::value_type;
		using size_type = typename SkipList::size_type;
		using difference_type = typename SkipList::difference_type;
		using key_compare = typename SkipList::key_compare;
		using allocator_type = typename SkipList::allocator_type;
		using reference = typename std::conditional_t<is_const, typename SkipList::const_reference, typename SkipList::reference >; //use std::conditional
		using pointer = typename std::conditional<is_const, typename SkipList::const_pointer, typename SkipList::pointer>;//use std::conditional

		skip_list_iterator() = default;
		skip_list_iterator(list_type& list) :
			current_list{ &list }, current_node{ list.m_begin->next[0] } {}

		skip_list_iterator(const skip_list_iterator& other) :
			current_list{ other.current_list }, current_node{ other.current_node } {}

		skip_list_iterator& operator++()
		{
			if (current_node.lock())
			{
				current_node = current_node.lock()->next[0];
			}
			return *this;
		}
		skip_list_iterator operator++(int)
		{
			auto tmp = *this;
			this->operator++();
			return tmp;
		}

		skip_list_iterator& operator+=(size_t n) {
			for (size_t i = 0; i < n && current_node.lock(); i++)
			{
				current_node = current_node.lock()->next[0];
			}
			return *this;
		}

		pointer operator->() const
		{
			auto sh_ptr_node = current_node.lock();
			if (!sh_ptr_node)
			{
				throw std::out_of_range("Can't dereference null iterator!");
			}
			return sh_ptr_node->value.get();
		}
		reference operator*() const
		{
			auto sh_ptr_node = current_node.lock();
			if (!sh_ptr_node)
			{
				throw std::out_of_range("Can't dereference null iterator!");
			}
			return *sh_ptr_node->value;
		}
		skip_list_iterator& operator=(const skip_list_iterator& other) {
			current_list = other.current_list;
			current_node = other.current_node;
			return *this;
		}
		bool operator==(const skip_list_iterator& it) const { return current_node.lock() == it.current_node.lock(); };
		bool operator!=(const skip_list_iterator& it) const { return !operator == (it); };
		bool operator!() const { return current_list.lock() != nullptr; }
	};

public:

	using iterator = skip_list_iterator<false>;
	using const_iterator = skip_list_iterator<true>;

	SkipList() : m_begin(new SkipNode()), m_end(new SkipNode()) {};
	explicit SkipList(const Compare& comp, const Alloc& alloc = Alloc()) : SkipList()
	{
		m_comp = comp;
		m_alloc = alloc;
	};

	SkipList(const SkipList& another) : SkipList(another.m_comp, another.m_alloc)
	{
		for (auto it = another.begin(); it != another.end(); ++it) {
			insert(*it);
		}
	}
	~SkipList() { clear(); }
	SkipList& operator=(const SkipList& another)
	{
		if (this == &another)
		{
			throw std::invalid_argument("Self-assign!");
		}
		clear();

		m_comp = another.m_comp;
		m_alloc = another.m_alloc;

		for (auto it = another.begin(); it != another.end(); ++it) {
			insert(*it);
		}
		return *this;
	}

	iterator begin() { return iterator(*this); }
	const_iterator begin() const { return const_iterator(*this); };
	iterator end()
	{
		iterator ReturnValue(*this);
		ReturnValue += ReturnValue.current_list->size();
		return ReturnValue;
	}
	const_iterator end() const
	{
		const_iterator ReturnValue(*this);
		ReturnValue += ReturnValue.current_list->size();
		return ReturnValue;
	};

	bool empty() const { return m_size == 0; }

	size_t size() const { return m_size; }

	Value& operator[](const Key& key)
	{
		iterator it = find(key);

		if (it == end())
		{
			return (*(insert(std::make_pair(key, mapped_type())).first)).second;
		}
		return (*it).second;
	}

	Value& at(const Key& key)
	{
		iterator iter = find(key);
		if (iter == end())
		{
			throw std::out_of_range("Such key doesn't exist");
		}
		return (*iter).second;
	}
	const_reference at(const Key& key) const
	{
		const_iterator iter = find(key);
		if (iter == end()) {
			throw std::out_of_range("Such key doesn't exist");
		}
		return (*iter).second;
	};

	std::pair<iterator, bool> insert(const value_type& pair)
	{
		std::array<sh_ptr, MaxLevel> update;
		std::array<sh_ptr, MaxLevel> rupdate;

		update.fill(m_begin);
		rupdate.fill(m_end);

		auto current = m_begin;
		for (int i = (int)level; i >= 0; --i)
		{
			while (current->next[i] && m_comp(current->next[i]->value->first, pair.first))
				current = current->next[i];

			rupdate[i] = current->next[i] ? current->next[i] : m_end;
			update[i] = current;
		}
		current = current->next[0];
		if ((current && current->value->first == pair.first)) {
			return std::make_pair(iterator(*this), false);
		}

		size_t new_lvl = NewLevel();
		if (new_lvl > level)
			level = new_lvl;

		sh_ptr node_to_insert = make_node(std::move(pair));

		for (size_t i = 0; i <= new_lvl; ++i) {
			node_to_insert->previous[i] = rupdate[i]->previous[i];
			rupdate[i]->previous[i] = node_to_insert;

			node_to_insert->next[i] = update[i]->next[i];
			update[i]->next[i] = node_to_insert;
		}
		++m_size;
		return std::make_pair(iterator(*this), true);
	}

	void erase(iterator position)
	{
		if (position == end() || !position.current_node.lock()) {
			throw std::out_of_range("Can't erase element");
		}
		auto current_ptr = position.current_node.lock();
		this->erase(current_ptr->value->first);
	}
	size_type erase(const Key& key)
	{
		if (empty())
		{
			throw std::out_of_range("Empty skip list!");
		}
		std::array<sh_ptr, MaxLevel> update;
		update.fill(m_begin);

		std::array<sh_ptr, MaxLevel> rupdate;
		rupdate.fill(m_end);

		auto current = m_begin;
		for (int i = (int)level; i >= 0; --i) 
		{
			while (current->next[i] && m_comp(current->next[i]->value->first, key))
				current = current->next[i];

			rupdate[i] = current->next[i] ? current->next[i] : m_end;
			update[i] = current;
		}
		current = current->next[0];

		if (current && current->value->first == key) {
			for (size_t i = 0; i <= level; i++) {
				if (update[i]->next[i] != current)
					break;
				update[i]->next[i] = current->next[i];
				rupdate[i]->previous[i] = current->previous[i];
			}
			while (level > 0 && !(m_begin->next[level])) {
				--level;
			}
			--m_size;
			return 1;
		}
		return 0;
	}

	void erase(iterator first, iterator last)
	{
		if (empty())
		{
			throw std::out_of_range("Empty skip list!");
		}
		for (auto it = first; it != last;) {
			auto tmp = it++;
			erase(tmp);
		}
	}

	void swap(SkipList& another)
	{
		auto copy = std::move(*this);
		*this = std::move(another);
		another = std::move(copy);
	}

	void clear()
	{
		m_size = 0;
		level = 0;

		auto current = m_begin->next[0];
		for (size_t i = 0; i < MaxLevel; i++)
		{
			m_begin->next[i].reset();
			m_end->previous[i].reset();
		}

		while (current) 
		{
			auto next_node = current->next[0];
			for (size_t i = 0; i < MaxLevel && current->next[i]; ++i) {
				current->next[i]->previous[i].reset();
				current->next[i].reset();
			}
			current = next_node;
		}
	}

	iterator find(const Key& key)
	{
		iterator result(*this);
		while (result != end() && !(is_equal((*result).first, key))) //use compare
		{
			++result;
		}
		return result;
		
	}
	const_iterator find(const Key& key) const
	{
		const_iterator result(*this);
		while (result != end() && !(is_equal((*result).first, key))) //use compare
		{
			++result;
		}
		return result;
	}

	bool operator==(const SkipList& x) const
	{
		if (size() != x.size())
			return false;

		for (auto it1 = begin(); it1 != end(); ++it1) {
			auto it2 = x.find((*it1).first);
			if (it2 == x.end() || (*it1).second != (*it2).second)
				return false;
		}
		return true;
	}
	bool operator!=(const SkipList& x) const {
		return  !(*this == x);
	}
};