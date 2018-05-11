#include "MsgQueue.h"


// Delete msg in the chat
int MsgQueue::Deletemsg(int index)
{
	//msg ����� �����ϸ�
	if (mq_MsgList.DeleteByIndex(index) == 1)
	{
		mq_Msgnum--;
		return 1;
	}
	else
		return -1;
}

RelationType MsgQueue::CompareByBase(const MsgQueue &data)
{
	if (this->mq_Id > data.mq_Id)
		return GREATER;
	else if (this->mq_Id < data.mq_Id)
		return LESS;
	else
		return EQUAL;
}

// Operator < with two MsgQueues.
bool MsgQueue::operator<(const MsgQueue& data)
{
	if (this->CompareByBase(data) == LESS)
		return true;
	else
		return false;
}
// Operator > with two MsgQueues.
bool MsgQueue::operator>(const MsgQueue& data)
{
	if (this->CompareByBase(data) == GREATER)
		return true;
	else
		return false;
}
// Operator == with two MsgQueues.
bool MsgQueue::operator==(const MsgQueue& data)
{
	if (this->CompareByBase(data) == EQUAL)
		return true;
	else
		return false;
}

// Read a record from file.
int MsgQueue::mq_ReadDataFromFile(ifstream& fin)
{
	fin >> mq_Id;

	//Msg num �ӽú���
	int Msgnum = 0;
	fin >> Msgnum;
	//Msg�� �ӽ� ����
	Msg* msg;

	for (int i = 0; i < Msgnum; i++)
	{
		msg = new Msg;
		(*msg).m_ReadDataFromFile(fin);
		SaveMsg(*msg);
	}
	return 1;
}

// Write a record into file.
int MsgQueue::mq_WriteDataToFile(ofstream& fout)
{
	fout << mq_Id << " ";
	fout << mq_Msgnum << " ";

	for (int i = 0; i < mq_Msgnum; i++)
	{
		mq_MsgList[i].m_WriteDataToFile(fout);
	}
	return 1;
}
