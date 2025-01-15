#include "Sequence.h"
Sequence::Sequence():m_size(0)
{
	m_head = nullptr;
	m_tail = nullptr;
}
Sequence::~Sequence()
{
	Node* p;
	p = m_head;
	while (p != nullptr)
	{
		Node* temp = p->m_next;
		delete p;
		p = temp;
	}
}
Sequence::Sequence(const Sequence& other):m_size(0)
{
	m_head = nullptr;
	Node* p = other.m_head;
	while (p != nullptr)
	{
		insert(p->m_value);
		p = p->m_next;
	}
}
Sequence& Sequence::operator=(const Sequence& rhs)
{
	if (this != &rhs)
	{
		Sequence temp(rhs);
		swap(temp);
	}
	return(*this);

}
bool Sequence::empty() const
{
	bool retValue = false;
	if (m_size == 0)
	{
		retValue = true;
	}
	return(retValue);
}
int Sequence::size() const
{
	return(m_size);
}
int Sequence::insert(int pos, const ItemType& value)
{
	if (0 <= pos && pos <= m_size)
	{
		Node* p;
		if (m_size == 0)
		{
			m_head = new Node;
			m_head->m_value = value;
			m_head->m_next = nullptr;
			m_head->m_prev = nullptr;
			m_head->m_pos = 0;
			m_tail = m_head;
			m_size++;		
		}
		if (pos == 0) //inserting to the front of the list
		{
			p = new Node;
			p->m_value = value;
			p->m_next = m_head;
			p->m_prev = nullptr;
			p->m_pos = 0;
			m_head->m_prev = p;
			m_head = p;
			p = p->m_next;
			for (; p != nullptr; p = p->m_next)
			{
				p->m_pos++;
			}
			m_size++;
		}
		for (p = m_head; p->m_next != nullptr && p->m_pos + 1 != pos; p = p->m_next);
		if (p->m_next != nullptr) //inserting in the middle
		{
			Node* temp = p->m_next;
			temp->m_prev = new Node;
			temp->m_prev->m_prev = p;
			temp->m_prev->m_next = temp;
			temp->m_prev->m_value = value;
			p->m_next = temp->m_prev;
			p->m_next->m_pos = p->m_pos + 1;
			for (; temp != nullptr; temp = temp->m_next)
			{
				temp->m_pos++;
			}
			m_size++;
		}
		else if(p->m_next == nullptr)
		{
			p->m_next = new Node; // insert in the rear
			p->m_next->m_value = value;
			p->m_next->m_prev = p;
			p->m_next->m_pos = p->m_pos + 1;
			p->m_next->m_next = nullptr;
			m_tail = p->m_next;
			m_size++;
		}
		
		return(pos);
	}
	else
		return -1;
}
int Sequence::insert(const ItemType& value)
{
	Node* p = m_head;
	int k(0);
	while (k < m_size && p->m_value < value)
	{
		p = p->m_next;
		k++;
	}
	return(insert(k, value));
}
bool Sequence::erase(int pos)
{
	// If 0 <= pos < size(), remove the item at position pos from
	  // the sequence (so that all items that followed that item end up at
	  // positions one lower than they were at before), and return true.
	  // Otherwise, leave the sequence unchanged and return false.
	
	Node* p;
	if (pos < 0 || pos >= m_size)
	{
		return false;
	}
	if (m_size == 1)
	{
		delete m_head;
		m_head = nullptr;
		m_tail = nullptr;
		m_size--;
		return true;
	}
	if (pos == 0) //erasing the first element
	{
		p = m_head;
		m_head = p->m_next;
		m_head->m_prev = nullptr;
		p->m_next = nullptr;
		p->m_prev = nullptr;
		delete p;
		m_size = m_size - 1;

		for (p = m_head; p != nullptr; p = p->m_next) // push the positions back
		{
			p->m_pos--;
		}
		return true;
	}
	else if (pos == m_size - 1) //erasing the last element
	{
		p = m_tail;
		m_tail = p->m_prev;
		m_tail->m_next = nullptr;
		delete p;
		m_size = m_size - 1;
		// no need to push the elements bc we erased the last element
		return true;
	}
	// if no if statements are satisfied -> erase an element inside the list
	
		for (p = m_head; p->m_pos != pos; p = p->m_next)
		{
			;
		}
		p->m_next->m_prev = p->m_prev;
		p->m_prev->m_next = p->m_next;
		Node* temp = p->m_next; 
		delete p;
		m_size--;
		for (; temp != nullptr; temp = temp->m_next)
		{
			temp->m_pos--;
		}
		return true;
}
int Sequence::remove(const ItemType& value)
{
	int removed = 0;
	int i = this->find(value);
	
	while (i != -1)
	{
		this->erase(i);
		removed++;
		i = this->find(value);
	}
	return(removed);
}
bool Sequence::get(int pos, ItemType& value) const
{
	if (pos >= 0 && pos < m_size)
	{
		Node* p = m_head;
		while (p->m_pos != pos)
		{
			p = p->m_next;
		}
		value = p->m_value;
		return true;
	}
	else
		return false;

}
bool Sequence::set(int pos, const ItemType& value)
{
	if (pos >= 0 && pos < m_size)
	{
		Node* p = m_head;
		while ( p->m_pos != pos)
		{
			p = p->m_next;
		}
		p->m_value = value;
		return true;
	}
	else
		return false;

}
int Sequence::find(const ItemType& value) const
{
	Node* p = m_head;
	while (p != nullptr && p->m_value != value)
	{
		p = p->m_next;
	}
	if (p == nullptr)
	{
		return -1;
	}
	return(p->m_pos);
}
void Sequence::swap(Sequence& other)
{
	int swapsize = other.m_size;
	other.m_size = this->m_size;
	this->m_size = swapsize;

	Node* headswap = other.m_head;
	other.m_head = this->m_head;
	this->m_head = headswap;

	Node* tailswap = other.m_tail;
	other.m_tail = this->m_tail;
	this->m_tail = tailswap;
}

//Non-member function implementations:

int subsequence(const Sequence& seq1, const Sequence& seq2)
{
	ItemType p;
	ItemType n;
	bool is_subsequence = true;
	seq2.get(0, n);
	if (seq1.size() < seq2.size() || seq2.empty() == true)
	{
		return(-1);
	}
	int subseq_size = seq1.size() - seq2.size() + 1;
	for (int k = 0; k < subseq_size; k++)
	{
		seq1.get(k, p);
		if (p == n)
		{
			is_subsequence = true;
			for (int i = 1; i < seq2.size() && is_subsequence == true; i++)
			{
				seq1.get(k + i, p);
				seq2.get(i, n);
				is_subsequence = (p == n);
			}
			if (is_subsequence == true)
			{
				return(k);
			}
			seq2.get(0, n);
		}
	}
	return -1;
}
void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
	Sequence temp;

	// ensuring the copying of seq1 into seq2
	if (seq1.empty() && !(seq2.empty()))
	{
		for (int i = 0; i < seq2.size(); i++)
		{
			ItemType p; // use get and insert!
			seq2.get(i, p);
			temp.insert(i, p);
		}
	}

	// checking if seq 2 empty so we can copy seq 1 into it
	else if (seq2.empty() && !(seq1.empty()))
	{
		for (int i = 0; i < seq1.size(); i++)
		{
			ItemType p;
			seq1.get(i, p);
			temp.insert(i, p);
		}
	}

	// check which one is bigger
	else if (!seq1.empty() && !seq2.empty())
	{
		if (seq1.size() == seq2.size())
		{
			int pos_counter = 0;
			for (int i = 0; i < seq1.size(); i++)
			{
				ItemType far;
				ItemType car;
				seq1.get(i, far);
				seq2.get(i, car);
				temp.insert(pos_counter, far);
				pos_counter++;
				temp.insert(pos_counter, car);
				pos_counter++;
			}
		}
		// 1 is bigger than 2
		else if (seq1.size() < seq2.size())
		{
			int real_pos = 0;
			int pos_counter = 0;
			// start for loop
			for (int i = 0; i < seq1.size(); i++)
			{
				ItemType far;
				seq1.get(i, far); // get the value into this temp
				temp.insert(real_pos, far);
				real_pos++;
				ItemType car;
				seq2.get(i, car);
				temp.insert(real_pos, car);
				real_pos++;
				pos_counter++;
			}
			for (int j = pos_counter; j < seq2.size(); j++)
			{
				ItemType far;
				seq2.get(j, far);
				temp.insert(real_pos, far);
				real_pos++;
			}
		}

		else if (seq2.size() < seq1.size())
		{
			int real_pos = 0;
			int pos_counter = 0;
			for (int i = 0; i < seq2.size(); i++)
			{
				ItemType far;
				seq1.get(i, far);
				temp.insert(real_pos, far);
				real_pos++;
				ItemType car;
				seq2.get(i, car);
				temp.insert(real_pos, car);
				real_pos++;
				pos_counter++;
			}
			for (int j = pos_counter; j < seq1.size(); j++)
			{
				ItemType far;
				seq1.get(j, far);
				temp.insert(real_pos, far);
				real_pos++;
			}
		}
	}
	result.swap(temp); // swap temp with result
}