#ifndef _LIST_
#define _LIST_

/*LISTA GENERICA MUTAVEL PARA FILA/PILHA
author: Pitágoras Alves
october 2014
*/

template <class T> class Node{
public:
	T x;
	Node<T> *next, *prev;
};

template <class T> class List{
public:
	List(){
		type = 0;
		head = createNode(NULL, NULL);
		last = head;
		size = 0;
	}

	List(int _type){
		type = _type;
		head = createNode(NULL, NULL);
		last = head;
		size = 0;
	}
	List(const List& list){
		type = list.getType();
		head = createNode(NULL, NULL);
		last = head;
		size = 0;
		for (int i = 0; i < list.getSize(); i++){
			this->push(list.get(i));
		}
	}

	~List(){
		Node<T> *n = head, *current = NULL; //initialization part

	    while(n)                               //start cleanup of nodes of the list
	    {
	        current = n;
	        n=n->next;
	        delete(current);
	    }

	    head = last = NULL;
	}

	void empty(){
		Node<T> *n = head, *current = NULL; //initialization part

		while (n)                               //start cleanup of nodes of the list
		{
			current = n;
			n = n->next;
			delete(current);
		}

		head = last = NULL;
		head = createNode(NULL, NULL);
		last = head;
		size = 0;
	}

	T get(int x) const {
		Node<T> *temp = nodeX(x);
		return temp->x;
	}

	T& operator[](const int &i) {
    	return getAdress(i);
	}
	
	List<T>& operator=(List<T> byval)
	{
		for (int i = 0; i < size; i++){
			pop();
		}
		for (int i = 0; i < byval.getSize(); i++){
			push(byval[i]);
		}
	    return *this;
	}

	int search(T x){
		if (size <= 0){
			return -1;
		} else{
			Node<T> *node = head->next;
			int i = 0;
			while (i <= size){
				if (node->x == x){
					return i;
				}else{
					node = node->next;
					i++;
				}
			}
			return -1;
		}
	}

	void push(T x){
		T temp = x;
		last->next = createNode(last, temp, NULL);
		last = last->next;
		size++;
	}

	bool remove(int x){
		if (x < 0 || x >= size){
			return false;
		}else{
			Node<T> *temp = nodeX(x);
			if (temp == last){
				last = temp->prev;
				last->next = NULL;
			}else{
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
			}
			delete temp;
			size--;
			return true;
		}
	}

	T pop(){
			if (type == 1 || type == 0){
				T result = get(0);
				remove(0);
				return result;
			}else if (type == 2){
				T result = get(size-1);
				remove(size-1);
				return result;
			}
	}

	T top(){
			if (type == 1 || type == 0){
				T result = get(0);
				return result;
			}else if (type == 2){
				T result = get(size-1);
				return result;
			}
	}

	/*void print(){
		if(size > 0){
			Node<T> *node = head->next;
			while(node != last){
				std::cout << node->x << ", ";
				node = node->next;
			}
			std::cout << node->x << ";\n";
		}
	}*/

	int getSize() const {
		return size;
	}
	int getType() const {
		return type;
	}

	Node<T>* nodeX(int x) const {
		if (x >= size){
			return NULL;
		}
		Node<T> *node = head->next;
		int i = 0;
		while (i < x){
			node = node->next;
			i++;
		}
		return node;
	}

protected:

	T& getAdress(int x){
		//if (x > size){
		//	return NULL;
		//}
		Node<T> *node = head->next;
		int i = 0;
		while (i < x){
			node = node->next;
			i++;
		}

		//lastLocation = x;
		//lastAdress = node;
		return node->x;
	}

	

	Node<T>* createNode(Node<T> *_prev, Node<T> *_next){
		Node<T> *node = new Node<T>;
		node->prev = _prev;
		node->next = _next;
		return node;
	}

	Node<T>* createNode(Node<T> *_prev, T value, Node<T> *_next){
		Node<T> *node = new Node<T>;
		node->prev = _prev;
		node->next = _next;
		node->x = value;
		return node;
	}
	
	Node<T> *head, *last;
	int size;
	int type; // 0 = list, 1 = queue, 2 = stack
	//T *lastAdress;
	//int lastLocation;
};

#endif