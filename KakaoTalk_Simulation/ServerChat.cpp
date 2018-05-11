#include "ServerChat.h"


// Set user ServerChatname from keyboard.
void ServerChat::SetChatnameFromKB()
{
	cout << "\t Chatname : ";
	cin >> sc_Chatname;
}

// Check member in the chat.
int ServerChat::Checkmem(string Id)
{
	if (sc_Members.find(Id) == sc_Members.end())
		return 0;
	else
		return 1;
}

// Delete member in the ServerChat.
int ServerChat::Deletemem(string Id)
{
	// 입력받은 아이디를 채팅창 멤버에서 삭제
	map<string, string>::iterator it = sc_Members.begin();
	while (it != sc_Members.end())
	{
		if (it->first == Id)
		{
			sc_Members.erase(it);
			break;
		}
		else
			it++;
	}
	// 입력받은 아이디를 가진 메시지큐리스트 삭제
	for (int i = 0; i < sc_Memnum; i++)
	{
		if (sc_MQList[i].GetId() == Id)
		{
			//MsgQueue형 임시변수
			MsgQueue msgq;
			msgq.SetId(Id);
			//MQ리스트에서 삭제
			sc_MQList.Delete(msgq);
		}
	}
	sc_Memnum--;
	return -1;
}

// Compare two Infotypes.
RelationType ServerChat::CompareByBase(const ServerChat &data)
{
	if (this->GetChatcode() > data.sc_Chatcode)
		return GREATER;
	else if (this->GetChatcode() < data.sc_Chatcode)
		return LESS;
	else
		return EQUAL;
}

// Operator < with two ServerChats.
bool ServerChat::operator<(const ServerChat& data)
{
	if (this->CompareByBase(data) == LESS)
		return true;
	else
		return false;
}
// Operator > with two ServerChats.
bool ServerChat::operator>(const ServerChat& data)
{
	if (this->CompareByBase(data) == GREATER)
		return true;
	else
		return false;
}
// Operator == with two ServerChats.
bool ServerChat::operator==(const ServerChat& data)
{
	if (this->CompareByBase(data) == EQUAL)
		return true;
	else
		return false;
}

// Read a record from file.
int ServerChat::sc_ReadDataFromFile(ifstream& fin)
{
	fin >> sc_Chatcode;
	fin >> sc_Chatname;
	fin >> sc_Memnum;
	string inId;
	string inName;
	for (int i = 0; i < sc_Memnum; i++)
	{
		fin >> inId;
		fin >> inName;
		sc_Members[inId] = inName;
	}
	return 1;
}

// Write a record into file.
int ServerChat::sc_WriteDataToFile(ofstream& fout)
{
	fout << sc_Chatcode << " ";
	fout << sc_Chatname << " ";
	fout << sc_Memnum << " ";
	map<string, string>::iterator it = sc_Members.begin();
	while (it != sc_Members.end())
	{
		fout << (*it).first << " " << (*it).second << " ";
		it++;
	}
	return 1;
}
