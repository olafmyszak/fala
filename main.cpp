#include <iostream>

class doubly_linked_circular_list
{
 private:
  struct Node
  {
	unsigned short data;
	Node *next;
	Node *prev;
  };

  Node *head, *tail;

  struct Node *search(unsigned short value)
  {
	Node *result = head;

	while (result->next!=head)
	{
	  if (result->data==value)
	  {
		return result;
	  }

	  result = result->next;
	}

	if (result->data==value)
	{
	  return result;
	}

	return nullptr;
  }

 public:
  doubly_linked_circular_list()
  {
	head = nullptr;
	tail = nullptr;
  }

  ~doubly_linked_circular_list()
  {
	if (head)
	{
	  Node *tmp = head;
	  while (tmp->next!=head)
	  {
		Node *t = tmp;
		tmp = tmp->next;
		delete t;
	  }
	  delete tmp;
	  head = nullptr;
	}
  }

  void append(unsigned short value)
  {
	Node *node = new Node;
	node->data = value;

	if (head==nullptr)
	{
	  node->next = node;
	  node->prev = node;
	  head = node;
	  tail = node;
	}

	tail = head->prev;
	tail->next = node;
	node->prev = tail;
	node->next = head;
	head->prev = node;
	tail = node;
  }

  void delete_node(unsigned short value)
  {
	if (is_empty())
	{
	  printf("List is empty.\n");
	  return;
	}

	Node *node = search(value);

	if (node==nullptr)
	{
	  printf("Value not found.\n");
	  return;
	}

	tail = head->prev;

	if(node == head && node == tail)
	{
	  head = tail = nullptr;
	  delete node;
	  return;
	}

	if (node==head)
	{
	  head = head->next;
	  tail->next = head;
	  head->prev = tail;
	  delete node;
	}
	else if (node==tail)
	{
	  tail = tail->prev;
	  tail->next = head;
	  head->prev = tail;
	  delete node;
	}
	else
	{
	  Node *prev_node = node->prev;
	  Node *next_node = node->next;

	  prev_node->next = next_node;
	  next_node->prev = prev_node;

	  delete node;
	}
  }

  bool is_empty()
  {
	if(head==nullptr)
	  return true;

	return false;
  }

  void print_list()
  {
	if (!is_empty())
	{
	  Node *tmp = head;

	  while (tmp->next!=head)
	  {
		printf("%d ", tmp->data);
		tmp = tmp->next;
	  }
	  printf("%d\n", tmp->data);
	}
	else
	{
	  printf("List is empty\n");
	}
  }
};

int main()
{
  doubly_linked_circular_list list = doubly_linked_circular_list();
  list.delete_node(5);

  return 0;
}