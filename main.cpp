#include <iostream>

class DoublyLinkedCircularList
{
 private:
  struct Node
  {
	unsigned short data;
	struct Node *next;
	struct Node *prev;
  };

  struct Node *start;

 public:
  DoublyLinkedCircularList()
  {
	start = new Node;
	start->next = nullptr;
	start->prev = nullptr;
  }

  virtual ~DoublyLinkedCircularList()
  {
	Node *temp;
	while (start !=nullptr)
	{
	  temp = start;
	  start = start->next;
	  delete temp;
	}
  }

  bool empty()
  {
	if(start->next == nullptr) return true;

	return false;
  }

  unsigned short front()
  {
	return start->next->data;
  }

  unsigned short back()
  {
	return start->prev->data;
  }

  /*
  void insertEnd(short value)
  {
	Node *last = (*start)->prev;

	auto *new_node = new Node;
	new_node->data = value;

	new_node->next = *start;
	(*start)->prev = new_node;

	new_node->prev = last;
	last->next = new_node;
  }
   */

  void push_front(unsigned short value)
  {
	Node *last = start->prev;
	Node *temp = new Node;
	temp->data = value;

	temp->next = start->next;
	temp->prev = start->prev;

	start->next = temp;
	start->prev =
  }

  void insertBegin(short value)
  {
	struct Node *last = (*start)->prev;

	auto *new_node = new Node;
	new_node->data = value;

	new_node->next = *start;
	new_node->prev = last;

	last->next = (*start)->prev = new_node;

	*start = new_node;
  }

  void insertBetween(short insertedValue, short insertedAfterThisValue)
  {
	auto *new_node = new Node;
	new_node->data = insertedValue;

	struct Node *temp = *start;

	while (temp->data!=insertedAfterThisValue)
	{
	  temp = temp->next;
	}
	struct Node *next = temp->next;

	temp->next = new_node;
	new_node->prev = temp;
	new_node->next = next;
	next->prev = new_node;
  }

  void printList()
  {
	struct Node *temp = *start;

	while (temp->next!=*start)
	{
	  std::cout << temp->data << std::endl;
	  temp = temp->next;
	}
	std::cout << temp->data << std::endl;
  }
};

int main()
{

  return 0;
}
