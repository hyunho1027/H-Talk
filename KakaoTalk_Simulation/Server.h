#pragma once

#include "ServerChat.h"
#include "InfoType.h"
#include <vector>
#include <windows.h>
using namespace std;


const string FILENAME_USER = "db_user.txt";
const int NAMESIZE_USER = int(FILENAME_USER.size());
const string FILENAME_CHAT = "db_chat.txt";
const int NAMESIZE_CHAT = int(FILENAME_CHAT.size());
#define FILENAMESIZE 1024
enum StatusType { OFF, SERVER, LOGIN, FRIENDMANAGE, CHATMANAGE, PROFILEMANAGE, CHAT };
enum DisPlayType { NONE, DISPLAYALLINFO, RETRIEVEBYID, DISPLAYALLFRIENDS, SEARCHFRIENDS, DISPLAYRECOMMENDFRIENDS, DISPLAYBIRTHFRIENDS, DISPLAYALLCHATS, DISPLAYMYINFO, DISPLAYALLMSG, SEARCHMSG };
/**
*	server.
*/
class Server
{
	friend class Application;
public:
	/**
	*	default constructor.
	*/
	Server()
	{
		Curr_Schat = nullptr;
		ReadDataFromFile();
	}

	/**
	*	destructor.
	*/
	~Server() {}

	/**
	*	@brief	Program driver.
	*	@pre	program is started.
	*	@post	program is finished.
	*/
	void Run(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext, int func_code);

	/**
	*	@brief	Add new record into list.
	*	@pre	list should be initialized.
	*	@post	new record is added into the list.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int AddInfo(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	/**
	*	@brief	Member login.
	*	@pre	list should be non-empty.
	*	@post	Logined.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int MemberLogin(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	/**
	*	@brief	Display all records in the list on screen.
	*	@pre	none.
	*	@post	none.
	*/
	void DisplayAllInfo(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	/**
	*	@brief	Display record in the list on screen.
	*	@pre	none.
	*	@post	none.
	*/
	void RetrieveById(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	//-------------------------LOGIN-------------------------------

	/**
	*	@brief	Move to Friendmanage.
	*	@pre	should be logined.
	*	@post	Go to friendmanage.
	*/
	void GoFriendmanage(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	/**
	*	@brief	Move to chatmanage.
	*	@pre	should be logined.
	*	@post	Go to chatmanage.
	*/
	void GoChatmanage(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	/**
	*	@brief	Move to profilemanage.
	*	@pre	should be logined.
	*	@post	Go to profilemanage.
	*/
	void GoProfilemanage(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	/**
	*	@brief	Member logout.
	*	@pre	should be logined..
	*	@post	Logouted.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int MemberLogout(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	//-------------------------FRIENDMANAGE-------------------------------

	/**
	*	@brief	Add Curr_Info's friend.
	*	@pre	none.
	*	@post	friend is set.
	*/
	int Addnewfriend(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	/**
	*	@brief	Display an user's friends on screen.
	*	@pre	user's friends is set.
	*	@post	user's friends is on screen.
	*/
	void Displayallfriends(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	/**
	*	@brief	Display an user's birth friends on screen.
	*	@pre	user's birth friends is set.
	*	@post	user's birth friends is on screen.
	*/
	void Birthfriend(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	/**
	*	@brief	Display an user's recommended friends on screen.
	*	@pre	user's recommended friends is set.
	*	@post	user's recommended friends is on screen.
	*/
	void Recfriend(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	/**
	*	@brief	Search friend
	*	@pre	user's friends is set.
	*	@post	user's friends is on screen.
	*/
	void Searchfriends(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	/**
	*	@brief	Delete Curr_Info's friend.
	*	@pre	friend is set.
	*	@post	friend is deleted.
	*/
	int Deletefriend(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	//-------------------------CHATMANAGE-------------------------------

	/**
	*	@brief	Add new record into list.
	*	@pre	list should be initialized.
	*	@post	new record is added into the list.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int AddChat(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	/**
	*	@brief	Attend chat by chatname.
	*	@pre	none.
	*	@post	none.
	*	@return	return true if it works well return 1, otherwise return 0.
	*/
	int Openchat(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	/**
	*	@brief	Display an user's chat on screen.
	*	@pre	user's chat is set.
	*	@post	user's chat is on screen.
	*/
	void Displayallchats(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	//-------------------------PROFILEMANAGE-------------------------------

	/**
	*	@brief	edit pic
	*	@pre	user should be set.
	*	@post	pic changed.
	*/
	void EditPic(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	/**
	*	@brief	edit backpic
	*	@pre	user should be set.
	*	@post	backpic changed.
	*/
	void EditBackpic(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	/**
	*	@brief	edit user backtext
	*	@pre	user should be set.
	*	@post	backtext changed.
	*/
	void EditBacktext(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	/**
	*	@brief	edit user record
	*	@pre	user should be set.
	*	@post	user record changed.
	*/
	void EditRecord(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	/**
	*	@brief	edit user pw
	*	@pre	user should be set.
	*	@post	user pw changed.
	*/
	void EditPw(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	/**
	*	@brief	Delete record of list.
	*	@pre	list should be non-empty.
	*	@post	record of the list and chat is deleted.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	void Memleave(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);


	//-------------------------CHAT-------------------------------

	/**
	*	@brief	Add new msg into chat.
	*	@pre	chat should be initialized.
	*	@post	new msg is added into the chat.
	*/
	void Sendmsg(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	/**
	*	@brief	Display all msgs on screen.
	*	@pre	msg is set.
	*	@post	display all msgs on screen.
	*/
	void Displayallmsg(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	/**
	*	@brief	member leaves the chat
	*	@pre	list should be in chat.
	*	@post	mem of the chat is leaved.
	*/
	void LeaveChat(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	/**
	*	@brief	edit chat info
	*	@pre	chat should be set.
	*	@post	chat info changed.
	*/
	void EditChat(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	/**
	*	@brief	Invite mem
	*	@pre	chat should be set.
	*	@post	new mem added.
	*/
	int AddMem(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	/**
	*	@brief	Delete msg (if opponent does not check it then delete.)
	*	@pre	msg should be set
	*	@post	selected msg is deleted.
	*/
	int Deletemsg(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	/**
	*	@brief	exit chat.
	*	@pre	should be in chat.
	*	@post	exit chat.
	*/
	void ExitChat(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	/**
	*	@brief	Add new emotion msg into chat.
	*	@pre	chat should be initialized.
	*	@post	new emotion msg is added into the chat.
	*/
	void SendEmotion(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	/**
	*	@brief	Display msgs we are looking for on screen.
	*	@pre	msg is set.
	*	@post	display all msgs on screen.
	*/
	void Searchmsg(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	/**
	*	@brief	Copy msg.
	*	@pre	msg is set.
	*	@post	Copy msg.
	*/
	int Copymsg(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	/**
	*	@brief	Paste msg.
	*	@pre	msg is set.
	*	@post	Paste msg.
	*/
	int Pastemsg(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	/**
	*	@brief	Deliver msg.
	*	@pre	msg is set.
	*	@post	Deliver msg.
	*/
	int Delivermsg(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);
	//-------------------------SUB-------------------------------


	/**
	*	@brief	Move to LOGIN.
	*	@pre	should be logined.
	*	@post	Go to LOGIN.
	*/
	void GoBack(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	/**
	*	@brief	Update New from Sever.
	*	@pre	chat should be set.
	*	@post	News loaded.
	*/
	void UpdateChats(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext);

	/**
	*	@brief	Open a file by file descriptor as an input file.
	*	@pre	a file for reading is exist.
	*	@post	open the file for reading.
	*	@param	fileName	a filename to open for reading.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int OpenInFile(char *fileName);

	/**
	*	@brief	Open a file by file descriptor as an output file.
	*	@pre	list should be initialized.
	*	@post	open the file for writing.
	*	@param	fileName	a filename to open for writing.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int OpenOutFile(char *fileName);

	/**
	*	@brief	Open a file as a read mode, read all data on the file, and set list by the data.
	*	@pre	The file is not opened.
	*	@post	list holds all records from the file.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int ReadDataFromFile();

	/**
	*	@brief	Open a file as a write mode, and write all data into the file,
	*	@pre	The file is not opened.
	*	@post	the list is stored in the output file.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int WriteDataToFile();

	/**
	*	@brief Get current time
	*	@return buff current time with string
	*/
	string GetCurrentDate()
	{
		time_t timer;
		struct tm t;
		char buff[80];

		// 현재 시스템의 시간정보를 얻어온다.
		timer = time(NULL);
		localtime_s(&t, &timer);

		// 시간정보로 (년월일시간) 문자열을 만들어 반환.
		strftime(buff, sizeof(buff), "%m%d", &t);

		return buff;
	}
private:
	ifstream u_InFile;		///< input file descriptor.
	ofstream u_OutFile;		///< output file descriptor.
	DoublyLinkedList<InfoType> u_List;		///< Info list.
	DoublyLinkedList<ServerChat> c_List;	///< Chat list.
	ServerChat* Curr_Schat;
};