#include <iostream>
#include <string>
using namespace std;

template<typename Object>
class List
{
private:
	struct Node
	{
		Object data;
		Node* pre;
		Node* next;
		Node() {}
		Node(Object d, Node* pre, Node* next) : data(d), pre(pre), next(next) {}
	};
public:
	class const_iterator
	{
	public:
		const_iterator():current(NULL) {}

		Object& operator*() const {return retrieve();}
		const_iterator& operator++() { current = current->next; return *this; }
		const_iterator operator++(int) { const_iterator temp = *this; ++*this; return temp;}

		bool operator==(const const_iterator & itr)
		{
			return current == itr.current;
		}

		bool operator!=(const const_iterator & itr)
		{
			return !(*this == itr);
		}

	protected:
		const_iterator(Node* n) : current(n) {}
		Node* current;

		Object & retrieve() const {return current->data;}
		friend class List<Object>;
	};

	class iterator : public const_iterator
	{
	public:
		iterator() {}
		Object & operator*() { return const_iterator::retrieve(); }
		const Object & operator*() const { return const_iterator::operator*(); }

		iterator& operator++() {const_iterator::current = const_iterator::current->next; return *this; }
		iterator operator++(int) { iterator p = *this; ++(*this); return p;}

		iterator& operator--() { const_iterator::current = const_iterator::current->pre; return *this;}
		iterator operator--(int	) { iterator p = *this; --(*this); return p;}


	protected:
		iterator(Node* p) : const_iterator(p) {}

		friend class List<Object>;
	};
public:
	List() { init(); }
	List(const List& rhs)
	{
		init();
		*this = rhs;
	}

	const List & operator =(const List & rhs)
	{
		if(this = &rhs)
			return *this;
		clear();
		for(const_iterator itr = rhs.cbegin(); itr != rhs.cend(); itr++)
			push_back(*itr);
		return *this;
	}


	iterator begin() { return iterator(head->next); }
	const const_iterator cbegin() const { return const_iterator(head->next); }
	iterator end() { return iterator(tail); }
	const const_iterator cend() const { return const_iterator(tail); }

	void pop_front()
	{
		erase(begin());
	}
	void push_back(const Object & data)
	{
		insert(end(), data);
	}

	bool isEmpty() const { return theSize == 0; }
	void clear()
	{
		while(!isEmpty())
			pop_front();
	}

	iterator insert(iterator itr,const Object& data)
	{
		Node* p = itr.current;
		theSize++;
		return iterator(p-> pre = p->pre->next = new Node(data, p->pre, p));
	}

	iterator erase(iterator itr)
	{
		Node *p = itr.current;
		++itr;
		theSize--;
		p->pre->next = p->next;
		p->next->pre = p->pre;
		delete p;
		return itr;

	}

	~List()
	{
		clear();
		delete head;
		delete tail;
	}
private:
	int theSize;
	Node* head;
	Node* tail;
	void init()
	{
		theSize = 0;
		head = new Node;
		tail = new Node;
		head->next = tail;
		tail->pre = head;
		head->pre = tail->next = NULL;
	}
};


int main(int argc, char const *argv[])
{
	List<string> sb;
	sb.push_back("3");
	sb.push_back("4");
	cout<<*sb.begin()<<endl;
	*sb.begin() = "hehe";
	cout<<*sb.begin()<<endl;

	for(List<string>::const_iterator a = sb.begin(); a != sb.end(); a++)
		cout<<*a;

	List<int> zl;
	return 0;
}