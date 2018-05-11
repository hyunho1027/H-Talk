#pragma once

#include "Chat.h"
#include "DoublyLinkedList.h"

/**
*	template 참조 에러 방지
*/
template <typename T>
class DoublyLinkedList;

/**
*	template 참조 에러 방지
*/
template <typename T>
struct DoublyNodeType;


/**
*	Info information class.
*/
class InfoType
{
public:
	/**
	*	default constructor.
	*/
	InfoType()
	{
		u_Id = "";
		u_Pw = "";
		u_Name = "";
		u_Phonenum = 0;
		u_Birth = 0;
		u_Gender = "";
		u_Pic = "empty";
		u_Backpic = "empty";
		u_Backtext = "empty";
		u_Friendnum = 0;
		u_Chatnum = 0;
		u_Lastdate = "none";
	}

	/**
	*	destructor.
	*/
	~InfoType() {}

	/**
	*	@brief	Get user id.
	*	@pre	user id is set.
	*	@post	none.
	*	@return	user id.
	*/
	string GetId()
	{
		return u_Id;
	}

	/**
	*	@brief	Get user Pw.
	*	@pre	user Pw is set.
	*	@post	none.
	*	@return	user Pw.
	*/
	string GetPw()
	{
		return u_Pw;
	}

	/**
	*	@brief	Get user name.
	*	@pre	user name is set.
	*	@post	none.
	*	@return	user name.
	*/
	string GetName()
	{
		return u_Name;
	}

	/**
	*	@brief	Get user phonenum.
	*	@pre	user phonenum is set.
	*	@post	none.
	*	@return	user phone num.
	*/
	int GetPhonenum()
	{
		return u_Phonenum;
	}

	/**
	*	@brief	Get user Birth
	*	@pre	user Birth is set.
	*	@post	none.
	*	@return	user Birth.
	*/
	int GetBirth()
	{
		return u_Birth;
	}

	/**
	*	@brief	Get user gender
	*	@pre	user gender is set.
	*	@post	none.
	*	@return	user gender.
	*/
	string GetGender()
	{
		return u_Gender;
	}

	/**
	*	@brief	Get user picturer
	*	@pre	user picture is set.
	*	@post	none.
	*	@return	user picture.
	*/
	string GetPic()
	{
		return u_Pic;
	}

	/**
	*	@brief	Get user Backpicturer
	*	@pre	user Backpicture is set.
	*	@post	none.
	*	@return	user Backpicture.
	*/
	string GetBackpic()
	{
		return u_Backpic;
	}

	/**
	*	@brief	Get user Backtext
	*	@pre	user Bactext is set.
	*	@post	none.
	*	@return	user Backtext.
	*/
	string GetBacktext()
	{
		return u_Backtext;
	}

	/**
	*	@brief	Get user Friends num
	*	@pre	user Friends num.
	*	@post	none.
	*	@return	user friendsnum.
	*/
	int GetFriendnum()
	{
		return u_Friendnum;
	}

	/**
	*	@brief	Get user Friends
	*	@pre	user Friends.
	*	@post	none.
	*	@return	user friends.
	*/
	DoublyLinkedList<string> GetFriends()
	{
		return u_Friends;
	}

	/**
	*	@brief	Get user Chats num
	*	@pre	user Chats num.
	*	@post	none.
	*	@return	user chatsnum.
	*/
	int GetChatnum()
	{
		return u_Chatnum;
	}

	/**
	*	@brief	Get user Chats
	*	@pre	user Chats.
	*	@post	none.
	*	@return	user Chats.
	*/
	DoublyLinkedList<Chat>& GetChats()
	{
		return u_Chats;
	}

	/**
	*	@brief	Get user lastdate
	*	@pre	user login.
	*	@post	none.
	*	@return	user lastdate.
	*/
	string GetLastdate()
	{
		return u_Lastdate;
	}

	/**
	*	@brief	Set user id.
	*	@pre	none.
	*	@post	user id is set.
	*	@param	inId	user id.
	*/
	void SetId(string inId)
	{
		u_Id = inId;
		transform(u_Id.begin(), u_Id.end(), u_Id.begin(), ::tolower);
	}

	/**
	*	@brief	Set user pw.
	*	@pre	none.
	*	@post	user pw is set.
	*	@param	inId	user pw.
	*/
	void SetPw(string inPw)
	{
		u_Pw = inPw;
	}

	/**
	*	@brief	Set user name.
	*	@pre	none.
	*	@post	user name is set.
	*	@param	inName	user name.
	*/
	void SetName(string inName)
	{
		u_Name = inName;
	}

	/**
	*	@brief	Set user phonenum.
	*	@pre	none.
	*	@post	user phonenum is set.
	*	@param	inPhonenum	user Phonenum.
	*/
	void SetPhonenum(int inPhonenum)
	{
		u_Phonenum = inPhonenum;
	}

	/**
	*	@brief	Set user Birth.
	*	@pre	none.
	*	@post	user birth is set.
	*	@param	inBirth	user birth.
	*/
	void SetBirth(int inBirth)
	{
		u_Birth = inBirth;
	}

	/**
	*	@brief	Set user gender.
	*	@pre	none.
	*	@post	user gender is set.
	*	@param	inGender user gender.
	*/
	void SetGender(string inGender)
	{
		u_Gender = inGender;
	}

	/**
	*	@brief	Set user picture.
	*	@pre	none.
	*	@post	user picture is set.
	*	@param	inPic user picture.
	*/
	void SetPic(string inPic)
	{
		u_Pic = inPic;
	}

	/**
	*	@brief	Set user Backpicture.
	*	@pre	none.
	*	@post	user Backpicture is set.
	*	@param	inBackpic user Backpicture.
	*/
	void SetBackpic(string inBackpic)
	{
		u_Backpic = inBackpic;
	}

	/**
	*	@brief	Set user Backtextture.
	*	@pre	none.
	*	@post	user Backtextture is set.
	*	@param	inBacktext user Backtextture.
	*/
	void SetBacktext(string inBacktext)
	{
		u_Backtext = inBacktext;
	}

	/**
	*	@brief	Set user friendnum.
	*	@pre	none.
	*	@post	user friends are set.
	*/
	void SetFriendnum()
	{
		u_Friendnum = int(u_Friends.GetLength());
	}

	/**
	*	@brief	Set user friendnum.
	*	@pre	none.
	*	@post	user friends are set.
	*/
	void SetFriendnum(int num)
	{
		u_Friendnum = num;
	}

	/**
	*	@brief	Set user Chatnum.
	*	@pre	none.
	*	@post	user Chats are set.
	*/
	void SetChatnum()
	{
		u_Chatnum = int(u_Chats.GetLength());
	}

	/**
	*	@brief	Set user Chatnum.
	*	@pre	none.
	*	@post	user Chats are set.
	*/
	void SetChatnum(int num)
	{
		u_Chatnum = num;
	}

	/**
	*	@brief	Add friend by Id.
	*	@pre	none.
	*	@post	friend is set.
	*/
	void AddFriend(string Id)
	{
		u_Friends.Add(Id);
		SetFriendnum();
	}

	/**
	*	@brief	Add New CHat.
	*	@pre	none.
	*	@post	Chat is set.
	*/
	void AddChat(Chat inchat)
	{
		u_Chats.Add(inchat);
		SetChatnum();
	}

	/**
	*	@brief	Delete friend by Id.
	*	@pre	none.
	*	@post	friend is set.
	*/
	void Deletefriend(string Id)
	{
		u_Friends.Delete(Id);
		SetFriendnum();
	}

	/**
	*	@brief	Set user Lastdate.
	*	@pre	none.
	*	@post	user lastdate is set.
	*/
	void SetLastDate()
	{
		u_Lastdate = GetCurrentTime();
	}

	/**
	*	@brief	Set user record.
	*	@pre	none.
	*	@post	user record is set.
	*	@param	inId	user id.
	*	@param	inPw	user pw.
	*	@param	inName	user name.
	*	@param	inBirth	user Birth.
	*	@param	inGender user Gender.
	*/
	void SetRecord(string inId, string inPw, string inName, int inPhonenum, int inBirth, string inGender)
	{
		SetId(inId);
		SetPw(inPw);
		SetName(inName);
		SetPhonenum(inPhonenum);
		SetBirth(inBirth);
		SetGender(inGender);
	}

	/**
	*	@brief	Reset user record.
	*	@pre	none.
	*	@post	user record is reset.
	*/
	void ResetRecord()
	{
		SetId("");
		SetPw("");
		SetName("");
		SetPhonenum(0);
		SetBirth(0);
		SetGender("");
		SetPic("empty");
		SetBackpic("empty");
		SetBacktext("empty");
		u_Friends.MakeEmpty();
		u_Friendnum = 0;
		u_Chats.MakeEmpty();
		u_Chatnum = 0;
	}


	/**
	*	@brief	Display user id on screen.
	*	@pre	user id is set.
	*	@post	user id is on screen.
	*/
	void DisplayIdOnScreen()
	{
		cout << "\t ID   : " << u_Id << endl;
	};

	/**
	*	@brief	Display user password on screen.
	*	@pre	user password is set.
	*	@post	user password is on screen.
	*/
	void DisplayPasswordOnScreen()
	{
		cout << "\t Password   : " << u_Id << endl;
	};

	/**
	*	@brief	Display user name on screen.
	*	@pre	user name is set.
	*	@post	user name is on screen.
	*/
	void DisplayNameOnScreen()
	{
		cout << "\t Name : " << u_Name << endl;
	};

	/**
	*	@brief	Display user Phonenum on screen.
	*	@pre	user Phonenum is set.
	*	@post	user Phonenum is on screen.
	*/
	void DisplayPhonenumOnScreen()
	{
		cout << "\t Phonenum : 010" << u_Phonenum << endl;
	};

	/**
	*	@brief	Display user Birth on screen.
	*	@pre	user birth is set.
	*	@post	user birth is on screen.
	*/
	void DisplayBirthOnScreen()
	{
		cout << "\t Birth : " << u_Birth << endl;
	};

	/**
	*	@brief	Display user Gender on screen.
	*	@pre	user gender is set.
	*	@post	user gender is on screen.
	*/
	void DisplayGenderOnScreen()
	{
		cout << "\t Gender : " << u_Gender << endl;
	};

	/**
	*	@brief	Display user Picture on screen.
	*	@pre	user picture is set.
	*	@post	user picture is on screen.
	*/
	void DisplayPicOnScreen()
	{
		cout << "\t Picture : " << u_Pic << endl;
	};

	/**
	*	@brief	Display user Backpicture on screen.
	*	@pre	user Backpicture is set.
	*	@post	user Backpicture is on screen.
	*/
	void DisplayBackpicOnScreen()
	{
		cout << "\t Backpicture : " << u_Backpic << endl;
	};

	/**
	*	@brief	Display user Backtext on screen.
	*	@pre	user Backtext is set.
	*	@post	user Backtext is on screen.
	*/
	void DisplayBacktextOnScreen()
	{
		cout << "\t Backtext : " << u_Backtext << endl;
	};

	/**
	*	@brief	Display an user record on screen.
	*	@pre	user record is set.
	*	@post	user record is on screen.
	*/
	void DisplayRecordOnScreen()
	{
		cout << endl;
		DisplayIdOnScreen();
		DisplayNameOnScreen();
		DisplayPhonenumOnScreen();
		DisplayBirthOnScreen();
		DisplayGenderOnScreen();
		DisplayPicOnScreen();
		DisplayBackpicOnScreen();
		DisplayBacktextOnScreen();
	};


	/**
	*	@brief	Set user id from keyboard.
	*	@pre	none.
	*	@post	user id is set.
	*/
	void SetIdFromKB();

	/**
	*	@brief	Set user pw from keyboard.
	*	@pre	none.
	*	@post	user pw is set.
	*/
	void SetPwFromKB();

	/**
	*	@brief	Set user name from keyboard.
	*	@pre	none.
	*	@post	user name is set.
	*/
	void SetNameFromKB();

	/**
	*	@brief	Set user Phonenum from keyboard.
	*	@pre	none.
	*	@post	user Phonenum is set.
	*/
	void SetPhonenumFromKB();

	/**
	*	@brief	Set user Birth from keyboard.
	*	@pre	none.
	*	@post	user birth is set.
	*/
	void SetBirthFromKB();

	/**
	*	@brief	Set user Gender from keyboard.
	*	@pre	none.
	*	@post	user genderis set.
	*/
	void SetGenderFromKB();

	/**
	*	@brief	Set user picture from keyboard.
	*	@pre	none.
	*	@post	user picture is set.
	*/
	void SetPicFromKB();

	/**
	*	@brief	Set user Backpicture from keyboard.
	*	@pre	none.
	*	@post	user Backpicture is set.
	*/
	void SetBackpicFromKB();

	/**
	*	@brief	Set user Backtext from keyboard.
	*	@pre	none.
	*	@post	user Backtext is set.
	*/
	void SetBacktextFromKB();

	/**
	*	@brief	Set user record from keyboard.
	*	@pre	none.
	*	@post	user record is set.
	*/
	void SetRecordFromKB();


	/**
	*	@brief	Read a record from file.
	*	@pre	the target file is opened.
	*	@post	user record is set.
	*	@param	fin	file descriptor.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int ReadDataFromFile(ifstream& fin);

	/**
	*	@brief	Write a record into file.
	*	@pre	the target file is opened. And the list should be initialized.
	*	@post	the target file is included the new user record.
	*	@param	fout	file descriptor.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int WriteDataToFile(ofstream& fout);

	/**
	*	Compare two Infotypes.
	*	@brief	Compare two Info types by Info id.
	*	@pre	two Info types should be initialized.
	*	@post	the target file is included the new Info record.
	*	@param	data	target Info for comparing.
	*	@return	return LESS if this.id < data.id,
	*			return GREATER if this.id > data.id then,
	*			otherwise return EQUAL.
	*/
	RelationType CompareByBase(const InfoType &data);

	/**
	*	Compare password of two Infotypes.
	*	@brief	Compare two Info types by Info pw.
	*	@pre	two Info types should be initialized.
	*	@post	the target file is included the new Info record.
	*	@param	data	target Info for comparing.
	*	@return	return LESS if this.pw < data.pw,
	*			return GREATER if this.pw > data.pw then,
	*			otherwise return EQUAL.
	*/
	RelationType CompareByPw(const InfoType &data);

	/**
	*	Compare password of two Infotypes.
	*	@brief	Compare two Info types by Info Name.
	*	@pre	two Info types should be initialized.
	*	@post	the target file is included the new Info record.
	*	@param	data	target Info for comparing.
	*	@return	return LESS if this.Name < data.Name,
	*			return GREATER if this.Name > data.Name then,
	*			otherwise return EQUAL.
	*/
	RelationType CompareByName(const InfoType &data);


	/**
	*	@brief	Search Info with same Id.
	*	@pre	friendslist should be non-empty.
	*	@post	If there is same Id which you enter in list then return its index.
	*	@param	Id	Id of data you want to search.
	*	@return	return its index if this function works well, otherwise -1.
	*/
	int Searchfriend(string Id);

	/**
	*	@brief	Search Chat with same code.
	*	@pre	chatlist should be non-empty.
	*	@post	If there is same Id which you enter in list then return its index.
	*	@param	cod	code of data you want to search.
	*	@return	return its index if this function works well, otherwise -1.
	*/
	int SearchChatcode(int code);

	/**
	*	@brief	operator < with two infotypes.
	*	@pre	none.
	*	@post	none.
	*	@param	data	data to compare.
	*	@return	return 1 if it is true, otherwise 0.
	*/
	bool operator<(const InfoType& data);

	/**
	*	@brief	operator > with two infotypes.
	*	@pre	none.
	*	@post	none.
	*	@param	data	data to compare.
	*	@return	return 1 if it is true, otherwise 0.
	*/
	bool operator>(const InfoType& data);

	/**
	*	@brief	operator == with two infotypes.
	*	@pre	none.
	*	@post	none.
	*	@param	data	data to compare.
	*	@return	return 1 if it is true, otherwise 0.
	*/
	bool operator==(const InfoType& data);

	/**
	*	@brief Get current time
	*	@return buff current time with string
	*/
	string GetCurrentTime()
	{
		time_t timer;
		struct tm t;
		char buff[80];

		// 현재 시스템의 시간정보를 얻어온다.
		timer = time(NULL);
		localtime_s(&t, &timer);

		// 시간정보로 (년월일시간) 문자열을 만들어 반환.
		strftime(buff, sizeof(buff), "%Y-%m-%d/%H:%M:%S", &t);

		return buff;
	}

protected:
	string u_Id;				///< user Id.
	string u_Pw;				///< user password.
	string u_Name;				///< user name.
	int u_Birth;				///< user birth.
	int u_Phonenum;				///< user's phonenum
	string u_Gender;			///< user gender
	string u_Pic;				///< user picture
	string u_Backpic;			///< user backpicture
	string u_Backtext;			///< user backtext
	int u_Friendnum;			///< user friends num;
	DoublyLinkedList<string> u_Friends;	///< user's friends
	int u_Chatnum;				///< the num of user chats
	DoublyLinkedList<Chat> u_Chats;	///< user's Chats
	string u_Lastdate;			///< user's latsdate
};

