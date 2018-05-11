#pragma once
#pragma once

#include "DoublyLinkedList.h"
#include "DoublyNodeType.h"


/**
*	template ���� ���� ����
*/
template <typename T>
class DoublyLinkedList;

/**
*	Iterator class for DoublyLinkedList.  (not using header and trailer nodes).
*	���õ� ADT�� ���� ����
*	- ��ü return�ϴ� �޼��忡�� ����� null�� ��� return�� ���� ���� �߻�
*	- ��ü ���ٴ� �����Ͱ� (nullptr�� ����) �� �������� �б⹮ ������ ���� ���� �� ����.
*/
template <typename T>
class DoublyIterator
{
	friend class DoublyLinkedList<T>;

public:
	/**
	*	Initialize List and CurPointer. (constructor overloading)
	*/
	DoublyIterator(const DoublyLinkedList<T>& list) : List(list), CurPointer(list.Head) {}

	/**
	*	@brief	���� ��带 ����Ű�� �����Ͱ� null���� �ƴ��� �Ǵ��ϴ� �޼���.
	*	@pre	Iterator has been initialized.
	*	@post	None.
	*	@return	nullptr true, otherwise false.
	*/
	bool NotNull();

	/**
	*	@brief	���� ��� �������� ���� ��尡 null���� �ƴ��� �Ǵ��ϴ� �޼���.
	*	@pre	Iterator has been initialized.
	*	@post	None.
	*	@return	nullptr true, otherwise false.
	*/
	bool NextNotNull();

	/**
	*	@brief	Get first data of the list.
	*	@pre	Iterator has been initialized.
	*	@post	Current pointer is moved to the first node.
	*	@return	Return first data of the list.
	*/
	T First();

	/**
	*	@brief	Get next data of the current pointer.
	*	@pre	Iterator has been initialized.
	*	@post	Current pointer is moved to the next node.
	*	@return	Return next data of the list.
	*/
	T Next();

	/**
	*	@brief	Get current data of the list and go to the next node. ���� ���. ��ü��ȯ�� return by value
	*	@pre	Iterator has been initialized.
	*	@post	Current pointer is moved to next node.
	*	@return	Return current data of the list.
	*/
	DoublyNodeType<T> GetCurrentNode();

private:
	const DoublyLinkedList<T>& List;	///< ����� ����Ʈ�� ���� ����
	DoublyNodeType<T>* CurPointer;	///< Node pointer for pointing current node to use iteration.
};


// ���� ���Ұ� null���� �˻�
template <typename T>
bool DoublyIterator<T>::NotNull() {
	if (CurPointer == nullptr)
		return false;

	else return true;
}

// ���� ���Ұ� null���� �˻�
template <typename T>
bool DoublyIterator<T>::NextNotNull()
{
	if (CurPointer->next == nullptr)
		return false;

	else return true;
}

// ù ��° node
template <typename T>
T DoublyIterator<T>::First()
{
	if (List.IsEmpty())
	{
		CurPointer = List.Head;
		return CurPointer->component;
	}
}

// ���� node�� �̵� �� item�� return.
template <typename T>
T DoublyIterator<T>::Next()
{
	T output = CurPointer->component;
	if (NotNull())
		CurPointer = CurPointer->next;
	return output;
}

// ���� node�� return
template <typename T>
DoublyNodeType<T> DoublyIterator<T>::GetCurrentNode()
{
	return *CurPointer;
}