#pragma once


#include "DoublyIterator.h"
#include "DoublyNodeType.h"

/**
*	Soreted Doubly linked list.
*/
template  <typename T>
class DoublyLinkedList
{
	friend class DoublyIterator<T>;
public:
	/**
	*	default constructor.
	*/
	DoublyLinkedList()
	{
		Length = 0;
		Head = nullptr;
		Tail = nullptr;
	}

	/**
	*	destructor.
	*/
	~DoublyLinkedList() {}

	/**
	*	@brief	Make list empty.
	*	@pre	none.
	*	@post	clear list.
	*/
	void MakeEmpty();

	/**
	*	@brief	Check whether it is empty or not.
	*	@pre	none.
	*	@post	none.
	*	@return	return 1 if it is empty otherwise return 0.
	*/
	bool IsEmpty();

	/**
	*	@brief	Get a number of records in current list.
	*	@pre	none.
	*	@post	none.
	*	@return	number of records in current list.
	*/
	int GetLength();

	/**
	*	@brief	Check capacity of list is full.
	*	@pre	none.
	*	@post	none.
	*	@return	return true if list capacity reached to the upper bound, otherwise return false.
	*/
	int Add(T data);

	/**
	*	@brief	delete a data of list.
	*	@pre	list should be non-empty.
	*	@post	If Id which you want to delete exists in list then delete it.
	*	@param	data	data of data you want to delete.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int Delete(T data);

	/**
	*	@brief	delete a data of list by Index.
	*	@pre	list should be non-empty.
	*	@post	If Id which you want to delete exists in list then delete it.
	*	@param	index	the index you want to delete.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int DeleteByIndex(int index);

	/**
	*	@brief	Search Info with same Id.
	*	@pre	list should be non-empty.
	*	@post	If there is same Id which you enter in list then return its index.
	*	@param	data	data of data you want to search.
	*	@return	return its index if this function works well, otherwise -1.
	*/
	int Search(T data);

	/**
	*	@brief	(�ּ�) Retrieve list element whose key matches item's key (if present).
	*	@pre	Key member of item is initialized.
	*	@post	If there is an element whose key matches with item's key then the element's record is copied to the item.
	*	@return	1 if any element's primary key matches with item's, otherwise 0.
	*/
	int Get(T& item, int index);


	/**
	*	@brief	user's data .
	*	@pre	user's data is set.
	*	@param	index wanna get index
	*	@post	get user's data .
	*	@return	return data by index.
	*/
	T& operator[](int index);

private:
	DoublyNodeType<T>* Head;		///< Pointer for pointing a first node.
	DoublyNodeType<T>* Tail;
	int Length;					///< Number of node in the list.
};

// Make list empty.
template  <typename T>
void DoublyLinkedList<T>::MakeEmpty()
{
	// ����Ʈ���� ��� ��� ���� �ϰ� ����Ʈ�� length�� �ʱ�ȭ
	DoublyNodeType<T>* tempPtr;
	DoublyIterator<T> iter(*this);

	while (iter.NotNull())
	{
		tempPtr = iter.CurPointer;
		iter.Next();
		delete tempPtr;
	}
	Head = nullptr;
	Tail = nullptr;
	Length = 0;
}

// check whether it is empty or not.
template  <typename T>
bool DoublyLinkedList<T>::IsEmpty()
{
	if (Head == nullptr)
		return true;

	else return false;
}

// Get a number of records in current list.
template  <typename T>
int DoublyLinkedList<T>::GetLength()
{
	return Length;
}

// add a new data into list.
template  <typename T>
int DoublyLinkedList<T>::Add(T inData)
{
	//�߰��� ���� ���� �ӽ��ڷ���
	DoublyNodeType<T>* node = new DoublyNodeType<T>;
	DoublyNodeType<T>* tmpPtr;

	node->component = inData;
	node->pre = nullptr;
	node->next = nullptr;


	// ����ִ� ���
	if (IsEmpty())
	{
		Head = node;
		Tail = Head;
	}
	// 1�� �̻�
	else {
		//MsgList�� ����� �ڿ������� ����
		tmpPtr = Tail;
		while (tmpPtr != nullptr)
		{
			if (!(node->component < tmpPtr->component))
			{ // �������� �ϴ°� �� ũ�ų� ������
				node->pre = tmpPtr;
				if (tmpPtr == Tail)
				{	// �� ��
					node->pre = Tail;
					Tail->next = node;
					Tail = node;
				}
				else
				{	// �߰�
					node->pre = tmpPtr;
					node->next = tmpPtr->next;
					tmpPtr->next->pre = node;
				}
				tmpPtr->next = node;
				break;
			}
			else
				tmpPtr = tmpPtr->pre;
		}
		if (tmpPtr == nullptr)
		{	// �� ��

			node->next = Head;
			Head->pre = node;
			Head = node;
		}
	}
	Length++;
	return 1;
}

// delete data of list.
template  <typename T>
int DoublyLinkedList<T>::Delete(T data)
{
	//������ ��带 ����ų ���
	DoublyNodeType<T>* pNode = Head;
	//����Ʈ �ȿ� �����ϴ��� Ȯ��
	int positionIndex = Search(data);
	if (positionIndex != -1)
	{
		for (int i = 0; i < positionIndex; i++)
			pNode = pNode->next;
		if (pNode->next != nullptr)// ���� �ƴϸ�
			pNode->next->pre = pNode->pre;
		else
			Tail = pNode->pre;
		if (pNode->pre != nullptr)// ó���� �ƴϸ�
			pNode->pre->next = pNode->next;
		else
			Head = pNode->next;
		delete pNode;
		Length--;
		return 1;
	}
	else
		return 0;
}


// delete data of list by index.
template  <typename T>
int DoublyLinkedList<T>::DeleteByIndex(int index)
{
	//���� ���̺��� �ε����� ������
	if (index < Length)
	{
		//�ӽú���
		DoublyNodeType<T>* tempPtr;

		tempPtr = Head;

		//�ε��� ����
		for (int i = 0; i < index; i++)
			tempPtr = tempPtr->next;

		//���� ù ��� ���
		if (index == 0)
		{
			tempPtr->next->pre = nullptr;
			Head = tempPtr->next;
		}
		//������ �����
		else if (index == (Length - 1))
		{
			tempPtr->pre->next = nullptr;
			Tail = tempPtr->pre;
		}
		//�߰� �����
		else
		{
			tempPtr->pre->next = tempPtr->next;
			tempPtr->next->pre = tempPtr->pre;
		}
		//��� ����
		delete tempPtr;
		Length--;

		return 1;
	}
	else
		return -1;
}

// Search Info
template  <typename T>
int DoublyLinkedList<T>::Search(T data)
{
	//���̰� 0�̸�
	if (!Length)
		return -1;

	//ã�� ��带 ����Ű�� ������
	DoublyNodeType<T>* tempPtr;
	tempPtr = Head;
	int index = 0;

	while (tempPtr != nullptr)
	{
		//��尡 ã�� �����
		if (tempPtr->component == data)
			return index;
		else
		{
			tempPtr = tempPtr->next;
			index++;
		}
	}
	return -1;
}

// Get info by index
template <typename T>
int DoublyLinkedList<T>::Get(T&item, int index)
{
	//����Ʈ �ȿ� �����ϸ�
	if (index >= 0)
	{
		item = (*this)[index];
		return 1;
	}
	else
		return 0;
}


// operator[]
template  <typename T>
T& DoublyLinkedList<T>::operator[](int index)
{
	DoublyNodeType<T>* tempPtr;

	tempPtr = Head;
	//�ε��� ����
	for (int i = 0; i < index; i++)
		tempPtr = tempPtr->next;

	return tempPtr->component;
}

