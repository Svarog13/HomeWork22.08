#include<iostream>

struct Node
{
	int value;
	Node* next;
	Node* prev;
	Node(int v, Node* n, Node* prev) :value(v), next(n), prev(prev) {}

};
class List
{
private:
	Node* head;
	Node* tail;
	int counter = 0;
public:

	bool isEmpty()const
	{
		return head == nullptr;
	}
	List(std::initializer_list<int>l)
	{

		for (int elem : l)
		{
			AddToTail(elem);
			counter++;
		}
		return;
	}
	List()
	{
		head = tail = nullptr;

	}
	void AddToHead(int value)
	{
		Node* newNode = new Node(value, head, nullptr);

		if (isEmpty())
		{
			head = tail = newNode;
		}
		else
		{
			head->prev = newNode;
			head = newNode;
		}
		counter++;
	}
	int GetSize() const
	{
		return counter;
	}
	int GetFirst() const
	{
		if (isEmpty())
		{
			return;
		}
		Node* current = head;
		return current->next->value;
	}
	int GetLast() const
	{
		if (isEmpty())
		{
			return -1;
		}
		Node* current = tail;
		return current->prev->value;
	}
	int GetAt(int index) const
	{
		Node* current = head;
		int i = 1;
		if (index > 0 && index <= counter)
		{
			while (current != nullptr)
			{
				if (i == index)
				{
					return current->value;
				}
				current = current->next;
				i++;
			}
		}

	}
	bool Contains(int value) const
	{
		Node* current = head;
		while (current != nullptr)
		{
			if (current->value == value)
			{
				return true;
			}
		}
		return false;
	}
	void AddToTail(int value)
	{
		Node* newNode = new Node(value, head, nullptr);
		if (head == nullptr)
		{
			head = tail = newNode;
		}
		else
		{
			tail->next = newNode;
			tail = newNode;
		}
		counter++;
	}
	void InsertAt(int value, int index)
	{
		Node* newNode = new Node(value, head, nullptr);
		if (index < 0)
		{
			return;
		}
		if (index == 0)
		{
			newNode->next = head;
			head = newNode;

			if (tail == nullptr)
			{
				tail = newNode;
			}
			return;
		}
		Node* current = head;
		int i = 0;

		while (current != nullptr && i < index - 1)
		{
			current = current->next;
			i++;
		}
		if (current == nullptr)
		{
			delete newNode;
			return;
		}
		newNode->next = current->next;
		current->next = newNode;
		if (newNode->next == nullptr)
		{
			tail = newNode;
		}
		counter++;
	}
	void DeleteAt(int index)
	{
		if (index <= 0 || head == nullptr)
		{
			return;
		}
		if (index == 1)
		{
			Node* temp = head;
			head = head->next;
			delete temp;
			return;
		}
		Node* current = head;
		int i = 1;

		while (current != nullptr && i < index - 1)
		{
			current = current->next;
			i++;
		}
		if (current == nullptr || current->next == nullptr)
		{
			return;
		}
		Node* temp = current->next;
		current->next = temp->next;
		if (temp == tail)
		{
			tail = current;
		}
		delete temp;
	}
	void Reverse()
	{
		if (head == nullptr || head->next == nullptr)
		{
			return;
		}
		Node* prev = nullptr;
		Node* current = head;
		Node* nextNode = nullptr;

		while (current != nullptr)
		{
			nextNode = current->next;
			current->next = prev;
			current->prev = nextNode;
			prev = current;
			current = nextNode;
		}
		tail = head;
		head = prev;

	}
	void PrintList() const
	{
		Node* current = head;
		while (current != nullptr)
		{
			std::cout << current->value << " ";
			current = current->next;
		}
		std::cout << std::endl;
		std::cout << "Size: " << counter << std::endl;
		std::cout << "Print Reverse : ";
		PrintReverse();
		std::cout << std::endl;
	}
	void PrintReverse() const
	{
		if (isEmpty())
		{
			return;
		}
		Node* current = tail;
		while (current != nullptr)
		{
			std::cout << current->value << " ";
			current = current->prev;
		}
	}
	int operator[](int pos)const
	{
		Node* current = head;
		int i = 1;
		if (pos > 0 && pos <= counter)
		{
			while (current != nullptr)
			{
				if (i == pos)
				{
					return current->value;
				}
				current = current->next;
				i++;
			}
		}
		return 0;
	}
	int& operator[](int pos)
	{
		Node* current = head;
		if (pos > 0 && pos <= counter)
		{
			for (int i = 1; i < pos; i++)
			{
				current = current->next;
			}
		}
		return current->value;
	}
	List& List::operator=(const List& other)
	{
		if (this != &other)
		{
			while (head != nullptr) {
				Node* temp = head;
				head = head->next;
				delete temp;
			}
			tail = nullptr;
			counter = 0;

			Node* current = other.head;
			while (current != nullptr) {
				AddToTail(current->value);
				current = current->next;
			}
		}
		return *this;
	}
	void RemoveDuplicates()
	{
		if (isEmpty())
		{
			return;
		}
		Node* current = head;
		while (current != nullptr)
		{
			Node* currentNext = current->next;
			while (currentNext != nullptr)
			{
				if (current->value == currentNext->value)
				{
					Node* tmp = currentNext;
					tmp->prev->next = tmp->next;
					delete tmp;
					counter--;
				}
			}
			current = current->next;
		}
	}

	int CountOccurrences(int value) const
	{
		if (isEmpty())
		{
			return;
		}
		Node* current = head;
		int countOccur = 0;
		while (current != nullptr)
		{
			if (current->value == value)
			{
				countOccur++;
			}
		}
		return countOccur;
	}

	~List()
	{
		while (head != nullptr)
		{
			Node* temp = head;
			head = head->next;
			delete temp;
		}
	}
};

int main()
{
	List list;

	list.AddToHead(10);
	list.AddToHead(20);
	list.AddToHead(30);

	list.PrintList();

	std::cout << "First element: " << list.GetFirst() << std::endl;
	std::cout << "Last element: " << list.GetLast() << std::endl;

	list.InsertAt(25, 2);
	list.PrintList();

	std::cout << "Element at index 2: " << list.GetAt(2) << std::endl;

	list.DeleteAt(2);
	list.PrintList();

	list.Reverse();
	list.PrintList();

	std::cout << "Element at index 1: " << list[1] << std::endl;

	List newList = { 5,15,25 };
	newList.PrintList();

	List copiedList = list;
	copiedList.PrintList();

	List assignedList = list;
	assignedList.PrintList();

	list.RemoveDuplicates();
	list.PrintList();

	int occurrences = list.CountOccurrences(10);
	std::cout << "Occurrences of 10: " << occurrences << std::endl;

	return 0;
}




