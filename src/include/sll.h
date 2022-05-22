#ifndef SLL_H
#define SLL_H
#include <stdexcept>

template <typename key_type, typename value_type>
class SLL{
public:
	class IteratorBase; class IteratorConst; class IteratorVar;

protected:
	class ListElement
	{
		friend class SLL;
		friend class IteratorBase;
		friend class IteratorConst;
		friend class IteratorVar;

	public:
		ListElement(key_type key, value_type value, ListElement* next = nullptr);
		~ListElement();
		key_type key;
		value_type value;
		ListElement* next;
	};

public:
	class IteratorBase
	{
	public:
		IteratorBase(ListElement* current);

		IteratorBase& operator++();
		IteratorBase operator++(int);

		bool operator==(const IteratorBase& b); //{ return a.current == b.current; }
		bool operator!=(const IteratorBase& b); // { return a.current != b.current; }

	protected:
		ListElement* current;
	};

class IteratorVar : public IteratorBase
{
public:
	IteratorVar(ListElement* current);
	value_type& operator*();
	key_type& operator&();
};
class IteratorConst : public IteratorBase
{
public:
	IteratorConst(ListElement* current);
	const value_type & operator*() const;
	const key_type & operator&() const;
};

public:
	SLL();
	~SLL();
	int get_element_nr() const;
	void clear();
	bool remove(const key_type key);
	bool is_in(const key_type key) const;
	const value_type & operator[](const key_type key) const;
	value_type & operator[](const key_type key);
	value_type* insert_back(const key_type key, const value_type value);
	IteratorConst begin() const;
	IteratorVar begin();



protected:
	ListElement* first;
	ListElement* last;
	int elements_nr;
	ListElement* find(const key_type key) const;
};

template <typename key_type, typename value_type>
SLL<key_type, value_type>::SLL()
{
	/*
		This constructor just creates an empty list.
	*/
	first = nullptr;
	last = nullptr;
	elements_nr = 0;
}

template <typename key_type, typename value_type>
SLL<key_type, value_type>::~SLL()
{
	/*
	Destructor frees memory alocated for each node and makes sure that pointer on first
	element of the list and last element of this list is nullptr.
	*/

	clear();
}

template <typename key_type, typename value_type>
int SLL<key_type, value_type>::get_element_nr()const
{
	/*
	Returns the number of elements that are currently in the lists (the current length of the list)
	*/
	return elements_nr;
}

template <typename key_type, typename value_type>
void SLL<key_type, value_type>::clear()
{
	/*
	Deletes all elements (nodes) from the list.
	*/

	ListElement* current = first;
	while (current != nullptr)
	{
		ListElement* temp = current->next;
		delete current;
		current = temp;
	}
	first = nullptr;
	last = nullptr;
	elements_nr = 0;
}

template <typename key_type, typename value_type>
bool SLL<key_type, value_type>::remove(const key_type key)
{	
	for (ListElement* before = nullptr, *to_delete = first;to_delete != nullptr;
		before = to_delete, to_delete = to_delete->next)
	{
		if (to_delete->key == key)
		{
			if (before == nullptr)
			{
				first = first->next;
			}
			else
			{
				before->next = to_delete->next;
			}
			delete to_delete;
			elements_nr--;
			return true;
		}
	}
	return false;
}

template<typename key_type, typename value_type>
bool SLL<key_type, value_type>::is_in(const key_type key) const
{
	return (find(key) != nullptr);
}

template<typename key_type, typename value_type>
value_type& SLL<key_type, value_type>::operator[](const key_type key)
{
	ListElement* element = find(key);
	if (element == nullptr)
		throw std::out_of_range("The element of given key is not in this list!");

	return element->value;
}

template<typename key_type, typename value_type>
value_type* SLL<key_type, value_type>::insert_back(const key_type key, const value_type value)
{
	/*
	It inserts new node in the end of the list. Key for new node is 'key' argument
	and value of new node is 'value' argument.
	*/
	if (last == nullptr)
	{
		first = new ListElement(key, value);
		last = first;
	}
	else
	{
		last->next = new ListElement(key, value);
		last = last->next;
	}
	elements_nr++;
	return &(last->value);
}

template<typename key_type, typename value_type>
const value_type & SLL<key_type, value_type>::operator[](const key_type key) const
{
	ListElement* element = find(key);
	if (element == nullptr)
		throw std::out_of_range("The element of given key is not in this list!");

	return element->value;
}

template <typename key_type, typename value_type>
typename SLL<key_type, value_type>::ListElement* SLL<key_type, value_type>::find(const key_type key) const
{
	for (ListElement* current = first; current != nullptr; current = current->next)
	{
		if (current->key == key)
		{
			return current;
		}
	}
	return nullptr;
}

template <typename key_type, typename value_type>
typename SLL<key_type, value_type>::IteratorConst SLL<key_type, value_type>::begin() const
{
	/*
		Returns an IteratorConst object pointig on the firs element of the list. This iterator enable
		only to acces without modyfing list elements. See ITERATORS DESCRIPTION at the top of
		SLL class definition for more info.
	*/
	return IteratorConst(first);
}

template <typename key_type, typename value_type>
typename SLL<key_type, value_type>::IteratorVar SLL<key_type, value_type>::begin()
{
	/*
		Returns an IteratorVar object pointig on the firs element of the list. This iterator enable
		to both acces and modify list elements. See ITERATORS DESCRIPTION at the top of
		SLL class definition for more info.
	*/
	return IteratorVar(first);
}

// START OF LIST_ELEMENT IMPLEMENTATION
template <typename key_type, typename value_type>
SLL<key_type, value_type>::ListElement::ListElement(key_type key, value_type value, ListElement* next): key(key), value(value), next(next)
{
}

template <typename key_type, typename value_type>
SLL<key_type, value_type>::ListElement::~ListElement()
{
	next = nullptr;
}
// END OF LIST ELEMENT IMPLEMENTATION

// START OF ITERATOR IMPLEMENTATION

template <typename key_type, typename value_type>
SLL<key_type, value_type>::IteratorBase::IteratorBase(ListElement* current) : current(current)
{
}

template <typename key_type, typename value_type>
typename SLL<key_type, value_type>::IteratorBase& SLL<key_type, value_type>::IteratorBase::operator++()
{
	/*
		It moves Iterator one node up. If the iterator already points on the last element
		of the list the incrementation will result in an iterator pointing on nothing (a nullptr).
		Incrementing an Iterator poining on nothing raises an 'out of range' exception.

		(First increments and  then return).
	*/

	if (current == nullptr)
		throw std::out_of_range("End of list already reached!");

	current = current->next;
	return *this;
}

template <typename key_type, typename value_type>
typename SLL<key_type, value_type>::IteratorBase SLL<key_type, value_type>::IteratorBase::operator++(int)
{
	/*
	It moves Iterator one node up. If the iterator already points on the last element
	of the list the incrementation will result in an iterator pointing on nothing (a nullptr).
	Incrementing an Iterator poining on nothing raises an 'out of range' exception.

		(First saves copy of itself, then increments and  then return the copy.
			So it return's itself before incrementation.).
	*/

	if (current == nullptr)
		throw std::out_of_range("End of list already reached!");
	IteratorBase old = *this;
	current = current->next;
	return *this;
}

template<typename key_type, typename value_type>
bool SLL<key_type, value_type>::IteratorBase::operator==(const IteratorBase& b)
{
	return (current == b.current);
}

template<typename key_type, typename value_type>
bool SLL<key_type, value_type>::IteratorBase::operator!=(const IteratorBase& b)
{
	return (current != b.current);
}

template <typename key_type, typename value_type>
SLL<key_type, value_type>::IteratorVar::IteratorVar(ListElement* current) : IteratorBase(current)
{
}
template <typename key_type, typename value_type>
SLL<key_type, value_type>::IteratorConst::IteratorConst(ListElement* current) : IteratorBase(current)
{
}

template <typename key_type, typename value_type>
value_type& SLL<key_type, value_type>::IteratorVar::operator*()
{
	/*
		Returns a pair (std::pair) of references of key and value of node pointed by this iterator.
		Raise an 'out_of_range' exception when operator points on nothing.
		(See ITERATORS DESCRIPTION for more info).
	*/
	if (IteratorBase::current == nullptr)
		throw std::out_of_range("This iterator points on nothing.\n"
			"Propably you alredy iterated through whole list, the list is empty or list, from which this iterator was created, was cleard or delete");
	return IteratorBase::current->value;
}

template<typename key_type, typename value_type>
inline key_type& SLL<key_type, value_type>::IteratorVar::operator&()
{
	if (IteratorBase::current == nullptr)
		throw std::out_of_range("This iterator points on nothing.\n"
			"Propably you alredy iterated through whole list, the list is empty or list, from which this iterator was created, was cleard or delete");
	return IteratorBase::current->key;
}

template <typename key_type, typename value_type>
const value_type & SLL<key_type, value_type>::IteratorConst::operator*() const
{
	/*
		Returns a pair (std::pair) of copies of key and value of node pointed by this iterator.
		Raise an 'out_of_range' exception when operator points on nothing.
		(See ITERATORS DESCRIPTION for more info).
	*/
	if (IteratorBase::current == nullptr)
		throw std::out_of_range("This iterator points on nothing.\n"
			"Propably you alredy iterated through whole list, the list is empty or list, from which this iterator was created, was cleard or delete");
	return IteratorBase::current->value;
}

template<typename key_type, typename value_type>
const key_type & SLL<key_type, value_type>::IteratorConst::operator&() const
{
	if (IteratorBase::current == nullptr)
		throw std::out_of_range("This iterator points on nothing.\n"
			"Propably you alredy iterated through whole list, the list is empty or list, from which this iterator was created, was cleard or delete");
	return IteratorBase::current->key;
}

// END OF ITERATOR IMPLEMENTATION

#endif