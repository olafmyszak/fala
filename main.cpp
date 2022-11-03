#include <iostream>

class Doubly_linked_circular_list
{
 private:
  struct Node
  {
	unsigned short data;
	Node *next;
	Node *prev;
  };

  Node *head;
  unsigned int size;

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

	  printf("Value not found.\n");
	  return nullptr;
  }

 public:
  Doubly_linked_circular_list()
  {
	  head = nullptr;
	  size = 0;
  }

  ~Doubly_linked_circular_list()
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

  void push_back(unsigned short value)
  {
	  Node *node = new Node;
	  node->data = value;

	  ++size;

	  if (head==nullptr)
	  {
		  node->next = node;
		  node->prev = node;
		  head = node;
	  }

	  Node *tail = head->prev;
	  tail->next = node;
	  node->prev = tail;
	  node->next = head;
	  head->prev = node;
  }

  void push_front(unsigned short value)
  {
	  Node *node = new Node;
	  node->data = value;

	  ++size;

	  Node *tail = head->prev;
	  node->next = head;
	  node->prev = tail;
	  tail->next = node;
	  head = node;
  }

  void erase(unsigned short value)
  {
	  if (empty())
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

	  --size;

	  Node *tail = head->prev;

	  if (node==head && node==tail)
	  {
		  head = tail = nullptr;
		  delete node;
		  return;
	  }

	  if (node==head)
	  {
		  pop_front();
	  } else if (node==tail)
	  {
		  pop_back();
	  } else
	  {
		  Node *prev_node = node->prev;
		  Node *next_node = node->next;

		  prev_node->next = next_node;
		  next_node->prev = prev_node;

		  delete node;
	  }
  }

  void erase(Node *p)
  {
	  if (empty())
	  {
		  printf("List is empty.\n");
		  return;
	  }

	  if (p==nullptr)
	  {
		  printf("No such element.\n");
		  return;
	  }

	  --size;

	  Node *tail = head->prev;
	  Node *node = p->next;

	  if (node==head && node==tail)
	  {
		  head = tail = nullptr;
		  delete node;
	  } else if (node==head)
	  {
		  pop_front();
	  } else if (node==tail)
	  {
		  pop_back();
	  } else
	  {
		  Node *prev_node = node->prev;
		  Node *next_node = node->next;

		  prev_node->next = next_node;
		  next_node->prev = prev_node;

		  delete node;
	  }
  }

  int pop_front()
  {
	  Node *temp = head;
	  Node *tail = head->prev;
	  int value = temp->data;

	  head = head->next;
	  head->prev = tail;
	  tail->next = head;

	  --size;

	  delete temp;
	  return value;
  }

  void pop_back()
  {
	  Node *tail = head->prev;
	  Node *temp = tail;

	  tail = tail->prev;
	  tail->next = head;
	  head->prev = tail;

	  --size;

	  delete temp;
  }

  void insert(unsigned short position, unsigned short value)
  {
	  if (empty())
	  {
		  push_back(value);
		  ++size;
	  }

	  Node *after = search(position);

	  if (after!=nullptr)
	  {
		  Node *before = after->next;
		  Node *node = new Node;
		  node->data = value;

		  after->next = node;
		  node->next = before;
		  node->prev = after;
		  before->prev = node;

		  ++size;
		  return;
	  }

	  printf("Value not found.\n");
  }

  /*
  void insert(Node *p, unsigned short value)
  {
	if (empty())
	{
	  push_back(value);
	}

	if (p!=nullptr)
	{
	  Node *node = new Node;
	  node->data = value;
	  node->next = p->next;
	  node->prev = p;
	  p->next = node;
	}
  }
  */

  void insert(Node *p, Node *value)
  {
	  if (p!=nullptr)
	  {
		  Node *node = new Node;
		  node->data = value->data;
		  node->next = p->next;
		  p->next = node;
		  node->prev = p;
		  ++size;
	  }
  }

  Node *first()
  {
	  return head;
  }

  Node *last()
  {
	  return head->prev;
  }

  Node *next(Node *p)
  {
	  if (p==nullptr)
		  return head;

	  return p->next;
  }

  Node *pos(unsigned short value)
  {
	  Node *node = search(value);

	  return node;
  }

  bool empty()
  {
	  if (head==nullptr)
		  return true;

	  return false;
  }

  void print_list(bool direction)
  {

	  if (!empty())
	  {
		  if (direction==false)
		  {
			  Node *tmp = head;

			  while (tmp->next!=head)
			  {
				  printf("%d ", tmp->data);
				  tmp = tmp->next;
			  }
			  printf("%d\n", tmp->data);
		  } else
		  {
			  Node *tmp = head->prev;

			  printf("%d ", head->data);
			  while (tmp->prev!=head->prev)
			  {
				  printf("%d ", tmp->data);
				  tmp = tmp->prev;
			  }
			  printf("\n");
		  }

	  } else
	  {
		  printf("List is empty\n");
	  }
  }

  void change_head(unsigned short value)
  {
	  Node *node = search(value);

	  if (node!=nullptr)
	  {
		  head = node;
		  head->next = node->next;
		  head->prev = node->prev;

		  Node *tail = head->prev;
		  tail->next = head;
		  tail->prev = node->prev->prev;
	  }
  }

  void change_head(Node *pos)
  {
	  if (pos!=nullptr)
	  {
		  head = pos;
		  head->next = pos->next;
		  head->prev = pos->prev;

		  Node *tail = head->prev;
		  tail->next = head;
		  tail->prev = pos->prev->prev;
	  }
  }

  void move(unsigned int n, bool direction)
  {
	  Node *pos = head;

	  if (direction==0)
	  {
		  for (int i = 0; i < n; ++i)
		  {
			  pos = pos->next;
		  }
	  } else
	  {
		  for (int i = 0; i < n; ++i)
		  {
			  pos = pos->prev;
		  }
	  }
	  change_head(pos);
  }

  unsigned int get_size() const
  {
	  return size;
  }


};

int main()
{

	unsigned short num_of_pairs, current_pair, num_of_ops, op, x;
	bool direction, flag;

	short temp;
	scanf("%hd %hd %hd", &num_of_pairs, &current_pair, &temp);
	direction = temp; //0 zgodnie 1 przeciwnie

	Doubly_linked_circular_list list = Doubly_linked_circular_list();
	Doubly_linked_circular_list eliminated = Doubly_linked_circular_list();


	for (int i = 0; i < num_of_pairs; ++i)
	{
		list.push_back(i);
	}

	list.insert(0, num_of_pairs - 1);
	for (int i = 1; i < num_of_pairs - 1; ++i)
	{
		list.insert(i, i - 1);
	}
	list.push_back(list.last()->data - 1);

	list.print_list(false);
	list.pop_front();
	list.pop_back();

	list.move(current_pair*2, false);

	scanf("%hd", &num_of_ops);

	for (unsigned short i = 0; i < num_of_ops; ++i)
	{
		scanf("%hd", &op);

		if (op==1)
		{
			scanf("%hd %hd", &x, &temp);
			flag = temp;
		} else
		{
			scanf("%hd", &x);
		}

		switch (op)
		{
			case 0:
			{
				list.move(x - 1, direction);
				list.print_list(direction);
				break;
			}

			case 1:
			{
				if (flag==0)
				{
					if (list.get_size() > 3)
					{
						list.move(x - 1, direction);
						eliminated.push_back(list.pop_front());

					} else
					{

					}
				}
				direction = !direction;
				break;
			}

			case 2:
			{
				list.move(x - 1, direction);
				direction = !direction;
				break;
			}

			default: printf("Switch error.\n");
				break;
		}
	}

	return 0;
}