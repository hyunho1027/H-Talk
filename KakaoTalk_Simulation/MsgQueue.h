#pragma once
#pragma once

#include "Msg.h"
#include "LinkedQueueType.h"

/**
*	array based simple queue.
*/
class MsgQueue
{
public:
	/**
	*	default constructor.
	*/
	MsgQueue()
	{
		mq_Id = "";
		mq_Msgnum = 0;
	}

	/**
	*	destructor.
	*/
	~MsgQueue() {}

	/**
	*	@brief	Get chat name.
	*	@pre	chat is set.
	*	@post	none.
	*	@return	chat name.
	*/
	string GetId()
	{
		return mq_Id;
	}


	/**
	*	@brief	Get MsgList.
	*	@pre	non.
	*	@post	none.
	*	@return	MsgList.
	*/
	LinkedQueueType<Msg>& GetMsgList()
	{
		return mq_MsgList;
	}


	/**
	*	@brief	Get number of msgbers.
	*	@pre	none.
	*	@post	none.
	*	@return	number of msgbers.
	*/
	int GetMsgnum()
	{
		return mq_Msgnum;
	}

	/**
	*	@brief	Set MQ Id.
	*	@pre	none.
	*	@post	Id is set.
	*	@param	inId	Id.
	*/
	void SetId(string inId)
	{
		mq_Id = inId;
	}


	/**
	*	@brief	Add new msgs.
	*	@pre	none.
	*	@post	none.
	*/
	void SaveMsg(Msg data)
	{
		mq_MsgList.EnQueue(data);
		mq_Msgnum++;
	}


	/**
	*	@brief	reset number of msgbers.
	*	@pre	none.
	*	@post	none.
	*/
	void ResetMsgnum()
	{
		mq_Msgnum = 0;
	}

	/**
	*	@brief	Reset Chat record.
	*	@pre	Chat should be set.
	*	@post	user record is reset.
	*/
	void ResetRecord()
	{
		SetId("");
		mq_MsgList.MakeEmpty();
		ResetMsgnum();
	}

	/**
	*	@brief	Delete msg in this chat.
	*	@pre	none.
	*	@post	msg is deleted.
	*	@param	fin	file descriptor.
	*	@return	if delete mem in the chat return 1, otherwise 0.
	*/
	int Deletemsg(int index);

	/**
	*	Compare two Msgqueuetypes.
	*	@brief	Compare two Msgqueue types by Msgqueue id.
	*	@pre	two Msgqueue types should be initialized.
	*	@post	the target file is included the new Msgqueue record.
	*	@param	data	target Msgqueue for comparing.
	*	@return	return LESS if this.id < data.id,
	*			return GREATER if this.id > data.id then,
	*			otherwise return EQUAL.
	*/
	RelationType CompareByBase(const MsgQueue &data);

	/**
	*	@brief	operator < with two infotypes.
	*	@pre	none.
	*	@post	none.
	*	@param	data	data to compare.
	*	@return	return 1 if it is true, otherwise 0.
	*/
	bool operator<(const MsgQueue& data);

	/**
	*	@brief	operator > with two infotypes.
	*	@pre	none.
	*	@post	none.
	*	@param	data	data to compare.
	*	@return	return 1 if it is true, otherwise 0.
	*/
	bool operator>(const MsgQueue& data);

	/**
	*	@brief	operator == with two infotypes.
	*	@pre	none.
	*	@post	none.
	*	@param	data	data to compare.
	*	@return	return 1 if it is true, otherwise 0.
	*/
	bool operator==(const MsgQueue& data);

	/**
	*	@brief	Read a record from file.
	*	@pre	the target file is opened.
	*	@post	user record is set.
	*	@param	fin	file descriptor.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int mq_ReadDataFromFile(ifstream& fin);

	/**
	*	@brief	Write a record into file.
	*	@pre	the target file is opened. And the list should be initialized.
	*	@post	the target file is included the new user record.
	*	@param	fout	file descriptor.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int mq_WriteDataToFile(ofstream& fout);


protected:
	string mq_Id;			///<  name of Chat.
	LinkedQueueType<Msg> mq_MsgList;		///< list of Msgs.
	int mq_Msgnum;				///< number of msgs.
};
