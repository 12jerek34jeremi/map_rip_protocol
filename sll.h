#ifndef SLL_H
#define SLL_H

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

	private:
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

		friend bool operator==(const IteratorBase& a, const IteratorBase& b); //{ return a.current == b.current; }
		friend bool operator!=(const IteratorBase& a, const IteratorBase& b); // { return a.current != b.current; }

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
	value_type operator*();
	key_type operator&();
};


protected:
	ListElement* first;
	ListElement* last;
	int elements_nr;
	ListElement* find(const key_type key, int occurence = 1) const;

public:
	SLL();
	~SLL();
	int get_element_nr();
	void clear();
	bool remove(key_type key);

};

#endif