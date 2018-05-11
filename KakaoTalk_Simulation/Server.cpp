#include "Server.h"


void Server::Run(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext, int func_code)
{
	switch (func_code)
	{
	case 10010001:
		AddInfo(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10010002:
		MemberLogin(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10010003:
		DisplayAllInfo(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10010004:
		RetrieveById(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10020001:
		GoFriendmanage(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10020002:
		GoChatmanage(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10020003:
		GoProfilemanage(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10020004:
		MemberLogout(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10030001:
		Addnewfriend(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10030002:
		Displayallfriends(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10030003:
		Birthfriend(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10030004:
		Recfriend(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10030005:
		Searchfriends(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10030006:
		Deletefriend(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10040001:
		AddChat(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10040002:
		Openchat(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10040003:
		Displayallchats(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10050001:
		EditPic(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10050002:
		EditBackpic(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10050003:
		EditBacktext(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10050004:
		EditRecord(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10050005:
		EditPw(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10050006:
		Memleave(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10060001:
		Sendmsg(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10060002:
		Displayallmsg(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10060003:
		LeaveChat(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10060004:
		EditChat(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10060005:
		AddMem(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10060006:
		Deletemsg(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10060007:
		ExitChat(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10060008:
		SendEmotion(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10060009:
		Searchmsg(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10060010:
		Copymsg(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10060011:
		Pastemsg(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10060012:
		Delivermsg(Client, Client_Chat, status, alarm, display, temptext);
		break;
	case 10090001:
		GoBack(Client, Client_Chat, status, alarm, display, temptext);
		break;
	default:
		break;
	}


	if (status != SERVER)
		//���� �������� �ʱ�ȭ
		u_List[u_List.Search(*Client)].SetLastDate();


}


//-------------------------SERVER-------------------------------


// Add new record into list. CDOE = 10010001
int Server::AddInfo(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	InfoType Info;
	Info.SetIdFromKB();

	//���� ���̵� /0�̸� �ǵ�����.
	if (Info.GetId() == "/0")
		return 0;

	//���̵� �ߺ� �˻�
	if (u_List.Search(Info) == -1)
	{
		//������ ���� ����
		Info.SetPwFromKB();
		Info.SetNameFromKB();
		Info.SetPhonenumFromKB();
		Info.SetBirthFromKB();
		Info.SetGenderFromKB();

		//��������Ʈ�� �߰�.
		u_List.Add(Info);
		alarm = "Add Succesively.";

		//�������� DB ����
		string Id = Info.GetId();
		Id.append("_db.txt");
		int leng = int(Id.length());

		//char* ���·� �����̸� ����
		char* filename;
		filename = new char[leng];
		for (int i = 0; i <= leng; i++)
		{
			filename[i] = Id[i];
		}

		//DB ����
		std::ofstream outfile(filename);

		return 1;
	}
	else
	{
		//���̵� �ߺ���
		alarm = "This Id Exists already.";
		return -1;
	}

}

// Login. CODE = 10010002
int Server::MemberLogin(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	InfoType user;
	user.SetIdFromKB();
	//�������̵� ã��
	int curIndex = u_List.Search(user);
	//�������̵� ���� ���
	if (curIndex != -1)
	{
		InfoType comp; //���� �ӽú���
		u_List.Get(comp, curIndex);
		user.SetPwFromKB();
		//Pw Ȯ��
		if (user.CompareByPw(comp) == EQUAL)
		{
			// �λ縻
			alarm = "Hello ";
			alarm.append(comp.GetName());
			alarm.append(" !\n");

			//�ֱ��������� ���
			if (comp.GetLastdate().compare("none"))
			{
				alarm.append("\tLast date user on. : ");
				alarm.append(comp.GetLastdate());
			}

			//���� LOGIN���� ����
			status = LOGIN;

			//Client ���� ������ ����
			Client->SetRecord(comp.GetId(), comp.GetPw(), comp.GetName(), comp.GetPhonenum(), comp.GetBirth(), comp.GetGender());
			Client->SetPic(comp.GetPic());
			Client->SetBackpic(comp.GetBackpic());
			Client->SetBacktext(comp.GetBacktext());
			for (int i = 0; i < comp.GetFriendnum(); i++)
			{
				//ģ�� ����
				Client->AddFriend(comp.GetFriends()[i]);
			}
			//ä�ð��� ����
			Client->SetChatnum(comp.GetChatnum());


			return 1;
		}
		//Pw�� �ٸ� ���
		else
		{
			alarm = "Check the Password again.";
			return 0;
		}
	}
	//�������̵� ���� ���
	else
	{
		alarm = "Check the ID again.";
		return 0;
	}
}

// Display all records in the list on screen. CODE = 10010003
void Server::DisplayAllInfo(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//������ ���°��
	if (u_List.GetLength() == 0)
	{

		cout << "\n\t Empty List." << endl;
	}
	//������ ������
	else
	{

		cout << "\n\tCurrent list" << endl << endl;

		// list�� ��� �����͸� ȭ�鿡 ���
		DoublyIterator<InfoType> iter(u_List);

		while (iter.NotNull())
			iter.Next().DisplayRecordOnScreen();
	}
}

// Display the record in the list on screen. CODE = 10010004
void Server::RetrieveById(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//������ ���°��
	if (u_List.GetLength() == 0)
	{
		cout << "\n\t Empty List." << endl;
	}
	//������ ������
	else
	{
		//ã�� ���̵��� �ӽú���
		string Id;
		cout << "\n\t Enter the ID you want to find. : ";
		cin >> Id;

		//�ǵ�����
		if (Id == "/0")
			return;

		//�ҹ��ڷ� ��ȯ
		transform(Id.begin(), Id.end(), Id.begin(), ::tolower);

		InfoType data;
		data.SetId(Id);
		//�ӽú��� ������
		if (u_List.Search(data) != -1)
		{
			int curIndex = u_List.Search(data);
			InfoType data;
			u_List.Get(data, curIndex);
			data.DisplayRecordOnScreen();
		}

		//�ӽú��� ������
		else
		{
			cout << "\n\t Can not find" << endl;
		}
	}
}

//-------------------------LOGIN-------------------------------

// move to friendmanage CODE = 10020001
void Server::GoFriendmanage(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	status = FRIENDMANAGE;
}

// move to chatmanage CODE = 10020002
void Server::GoChatmanage(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	status = CHATMANAGE;
	display = DISPLAYALLCHATS;
}

// move to profilemanage CODE = 10020003
void Server::GoProfilemanage(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	status = PROFILEMANAGE;
}

// Logout. CODE = 10020004
int Server::MemberLogout(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//���� �ǻ� Ȯ��
	cout << "\n\t Wanna Logout seriously? (Y/N): ";
	string ans;
	cin >> ans;

	//������ ���� �ϸ�
	if (ans == "Y" || ans == "y")
	{
		alarm = "Logouted Successively.";

		//������ �̿�ð� ����
		Client->SetLastDate();

		//���� ����
		status = SERVER;
		Client->ResetRecord();
		return 1;
	}
	else
	{
		alarm = "Not Logouted.";
		return 0;
	}
}


//-------------------------FRIENDMANAGE-------------------------------

// Add new friend into u_friend list CODE = 10030001
int Server::Addnewfriend(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	DisplayAllInfo(Client, Client_Chat, status, alarm, display, temptext);
	cout << "\n\t Who do you want." << endl;

	// ���̵� �Է�
	InfoType data;
	data.SetIdFromKB();

	//�ǵ�����
	if (data.GetId() == "/0")
		return 0;

	// ���̵� ����Ʈ�� ������
	if (!(u_List.Search(data) < 0))
	{
		// ���̵� �ڱ� �ڽ��̸�
		if (data.GetId() == Client->GetId())
		{
			alarm = "Can not Add myself.";
			return -1;
		}

		// ���̵� �̹� ģ���̸�
		else if (Client->Searchfriend(data.GetId()) != -1)
		{
			alarm = "Friend already.";
			return -1;
		}

		// �Ѵ� �ƴϸ�
		else
		{
			//���� ���� ��Ͽ� ģ�� �߰�
			u_List[u_List.Search(*Client)].AddFriend(data.GetId());
			//���� �α��ε� �������� ģ���߰�.
			Client->AddFriend(data.GetId());
			alarm = "Add successively.";
			return 1;
		}
	}
	return -1;
}

// Display all friends On Screen CODE = 10030002
void Server::Displayallfriends(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	// ģ���� ���ٸ�
	if (Client->GetFriendnum() == 0)
	{
		cout << "\n\t No friends." << endl;
	}
	//ģ���� ������
	else
	{
		cout << "\n\t -----------Friends List-------------" << endl;

		// ��¿��ӽ� ���� ����
		std::vector<string> frd;
		// it ����
		std::vector<string>::iterator it;
		// ģ��Id ����  �ΰ��� �ӽ� ����
		InfoType info, iinfo;
		// int�� �ӽ� ����
		int index = 0;
		//���� ������ ģ������ �̸������� ���� ����
		for (int i = 0; i < Client->GetFriendnum(); i++)
		{
			//ó������ �ٷ� ����
			if (i == 0)
				frd.push_back(Client->GetFriends()[i]);
			else
			{
				//iterator �ʱ�ȭ
				it = frd.begin();

				//frd�� �� ģ��
				info.SetId(Client->GetFriends()[i]);
				while (1)
				{
					//frd�� �ִ� ģ��
					iinfo.SetId(*it);
					//���� ģ���� ���� ģ������ �̸��� ������
					if (u_List[u_List.Search(info)].GetName() < iinfo.GetName())
					{
						frd.insert(it, Client->GetFriends()[i]);
						break;
					}
					//���� frd�� �������̸� �������� ����
					else if ((*it) == frd[i - 1])
					{
						frd.push_back(Client->GetFriends()[i]);
						break;
					}
					//�ƴϸ�
					else
						it++;
				}
			}
		}
		for (int i = 0; i < Client->GetFriendnum(); i++)
		{
			//info ��Ȱ��
			info.SetId(frd[i]);
			u_List[u_List.Search(info)].DisplayRecordOnScreen();
			cout << endl;
		}

	}
}

// Display Birthday friends On Screen CODE = 10030003
void Server::Birthfriend(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//ģ�� �� �ޱ�
	int frdnum = Client->GetFriendnum();
	if (frdnum > 0)
	{
		//������ ģ�� �ӽú���
		InfoType info;
		bool check = false;
		cout << "\n\t ----------Birth day friends-------------" << endl << endl;

		for (int i = 0; i < frdnum; i++)
		{
			// ģ������Ʈ���� ���̵� �޾ƿ���
			info.SetId(Client->GetFriends()[i]);
			// ģ���������� �Ѹ� ���糯¥�� ������ Ȯ��
			if (u_List[u_List.Search(info)].GetBirth() % 10000 == std::stoi(GetCurrentDate()))
			{
				u_List[u_List.Search(info)].DisplayRecordOnScreen();
				check = true;
			}
		}
		// ���� ������ ģ���� ���ٸ�
		if (!check)
			cout << "\n\t Nobody birthday." << endl;
	}
	// ���� ģ���� ���ٸ�
	else
		cout << "\n\t Do not have friends." << endl;
}

// Display Recommend friend CODE = 10030004
void Server::Recfriend(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	InfoType info;
	int leng = u_List.GetLength();
	bool check = false;

	cout << "\n\t ----------Recommend friends-------------" << endl << endl;

	for (int i = 0; i < leng; i++)
	{
		// i��° ������ Client�� �ƴϰ� Client�� ģ���� �ƴҶ�
		if ((u_List[i].GetId() != Client->GetId()) && Client->Searchfriend(u_List[i].GetId()) == -1)
		{
			// i��° ������ ģ������Ʈ�� Client�� ������
			if (u_List[i].Searchfriend(Client->GetId()) != -1)
			{
				u_List[i].DisplayRecordOnScreen();
				check = true;
			}
		}
	}
	// ���� ��õģ���� ������
	if (!check)
		cout << "\n\t Nobody recommend" << endl;
}

// Display all friends On Screen CODE = 10030005
void Server::Searchfriends(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	// ģ���� ���ٸ�
	if (Client->GetFriendnum() == 0)
	{
		cout << "\n\t No friends." << endl;
	}
	//ģ���� ������
	else
	{
		//ã�� �̸� �ӽú���
		string name;
		//���� �̸� ���� �ӽ� ����
		InfoType tmpinfo;
		//bool�� �ӽ� ����
		bool check = false;
		cout << "\n\t Enter the name you want to look for. : ";
		cin >> name;

		//�ǵ�����
		if (name == "/0")
			return;

		cout << "\n\t -----------Friends List-------------" << endl;

		// Ŭ���̾�Ʈ�� ��� ģ�� Ȯ��
		for (int i = 0; i < Client->GetFriendnum(); i++)
		{
			//�ӽú����� ���̵� set
			tmpinfo.SetId(Client->GetFriends()[i]);
			//���ϴ� �ܾ �̸��� ���ԵǸ�
			if (0<u_List[u_List.Search(tmpinfo)].GetName().find(name) && u_List[u_List.Search(tmpinfo)].GetName().find(name)<u_List[u_List.Search(tmpinfo)].GetName().length())
			{
				//���
				u_List[u_List.Search(tmpinfo)].DisplayRecordOnScreen();
				check = true;
			}
		}

		if (!check)
			cout << "\n\t No friends." << endl;
	}
}

// Delete friend into u_friend list CODE = 10030006
int Server::Deletefriend(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	Displayallfriends(Client, Client_Chat, status, alarm, display, temptext);
	cout << "\n\t Who do you want to delete. :";

	// ���̵� �Է�
	string data;
	cin >> data;

	//�ǵ�����
	if (data == "/0")
		return 0;

	if (Client->Searchfriend(data) != -1)
	{
		u_List[u_List.Search(*Client)].Deletefriend(data);
		Client->Deletefriend(data);
		alarm = "Delete successively.";
		return 1;
	}
	else
		return 0;
}

//-------------------------CHATMANAGE-------------------------------

// Add new record into list. CODE = 10040001 
int Server::AddChat(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{

	//��ȭ�� �� �ִ� ģ�� ���
	Displayallfriends(Client, Client_Chat, status, alarm, display, temptext);
	cout << "\n\t Who you want to talk." << endl;

	//UI ���
	display = DISPLAYALLCHATS;

	// ��ȭ��� �ӽú���
	InfoType info;
	info.SetIdFromKB();

	//���� ���̵� /0�̸� �ǵ�����.
	if (info.GetId() == "/0")
		return 0;

	u_List.Get(info, u_List.Search(info));


	// ���ϴ� ��ȭ��밡 ģ���� �ƴ϶��
	if (Client->Searchfriend(info.GetId())<0)
	{
		//UI ���
		display = DISPLAYALLCHATS;

		alarm = "Dose not exists.";
		return -1;
	}
	else
	{
		//������ ������ ����ê �ӽú���
		ServerChat schat;
		schat.AddMembers(Client->GetId(), Client->GetName());
		schat.AddMembers(info.GetId(), info.GetName());
		schat.SetChatnameFromKB();
		schat.SetChatcode(c_List.GetLength());

		//����Ʈ�� ����
		c_List.Add(schat);


		//���� ������ ������ ä�� �ӽú���
		Chat chat;
		chat.SetChatcode(schat.GetChatcode());
		chat.SetChatname(schat.GetChatname());
		chat.SetMem(schat.GetMem());
		chat.SetMemnum();
		//���� Ŭ���̾�Ʈ�� ����
		Client->AddChat(chat);
		//��������Ʈ ����� ���� ������ ä�ü� ����
		u_List[u_List.Search(*Client)].SetChatnum(Client->GetChatnum());

		//���� ����ê,ê ������ ��ȯ
		Curr_Schat = &c_List[c_List.GetLength() - 1];

		//Chat �� ������ ��¥�� ���� ū�� �� ������ ���� ���� ���
		Client_Chat = &Client->GetChats()[0];
		status = CHAT;

		//ä�ù� ������� ����
		Msg newmsg;
		newmsg.SetSendId("/SERVER");
		newmsg.SetText("Chat Open!");
		newmsg.SetDate();
		Curr_Schat->AddNewMsg(newmsg);

		//���ο� ��¥�� �˸��� ������ ��
		Msg alarmdate;
		alarmdate.SetSendId("/SERVER");
		alarmdate.SetDate();
		alarmdate.SetText(alarmdate.GetDate().substr(0, 10));
		Curr_Schat->AddNewMsg(alarmdate);

		//UI���
		display = DISPLAYALLMSG;
		return 1;
	}
	return -1;
}

// Open chat CODE = 10040002
int Server::Openchat(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//���� ������ ä���� �ִٸ�
	if (Client->GetChatnum())
	{

		cout << "\t Choose the Chat number--> ";
		//ä�ù� ��ȣ ����
		int getcommend;
		cin >> getcommend;

		int num = Client->GetChatnum();

		if (0 < getcommend&&getcommend <= num)
		{
			//���� ���� ä�������� ��ȯ
			Client_Chat = &Client->GetChats()[getcommend - 1];

			//ä�ù�ѹ� �ӽú���
			int Chatcode;

			//���õ� ��ȣ�� ä�ù��� ä�ù�ѹ� �ޱ�
			Chatcode = Client_Chat->GetChatcode();

			//���� ���ӵ� ä�ù����� ����
			Curr_Schat = &c_List[Chatcode];

			status = CHAT;
			display = DISPLAYALLMSG;
			return 1;
		}
		else
		{
			//UI ���
			display = DISPLAYALLCHATS;
			alarm = "Check the number again.";
			return -1;
		}
	}
	else
	{
		alarm = "Does not Exist.";
		return-1;
	}
}

// Display all chats On Screen CODE = 10040003
void Server::Displayallchats(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//������ ä�� ���� 0�̶��
	if (!Client->GetChatnum())
		alarm = "Empty List.";
	else
	{
		cout << "\t -----------Chats List-------------" << endl;
		//ä�� ��
		int num = Client->GetChatnum();

		for (int i = 0; i < num; i++)
		{
			cout << "\t" << i + 1 << ". " << endl;
			Client->GetChats()[i].DisplayChatOnScreen();
		}
	}
}


//-------------------------PROFILEMANAGE-------------------------------

// Edit users pic CODE = 10050001
void Server::EditPic(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	u_List[u_List.Search(*Client)].SetPicFromKB();
	Client->SetPic(u_List[u_List.Search(*Client)].GetPic());
	alarm = "Changed Successively.";

}

// Edit users pic  CODE = 10050002
void Server::EditBackpic(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	u_List[u_List.Search(*Client)].SetBackpicFromKB();
	Client->SetBackpic(u_List[u_List.Search(*Client)].GetBackpic());
	alarm = "Changed Successively.";

}

// Edit users pic CODE = 10050003
void Server::EditBacktext(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	u_List[u_List.Search(*Client)].SetBacktextFromKB();
	Client->SetBacktext(u_List[u_List.Search(*Client)].GetBacktext());
	alarm = "Changed Successively.";

}

// Edit users record CODE = 10050004
void Server::EditRecord(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//�̸� ����
	u_List[u_List.Search(*Client)].SetNameFromKB();
	Client->SetName(u_List[u_List.Search(*Client)].GetName());
	//�ڵ��� ��ȣ ����
	u_List[u_List.Search(*Client)].SetPhonenumFromKB();
	Client->SetPhonenum(u_List[u_List.Search(*Client)].GetPhonenum());
	//���� ����
	u_List[u_List.Search(*Client)].SetBirthFromKB();
	Client->SetBirth(u_List[u_List.Search(*Client)].GetBirth());
	//���� ����
	u_List[u_List.Search(*Client)].SetGenderFromKB();
	Client->SetGender(u_List[u_List.Search(*Client)].GetGender());

	alarm = "Changed Successively.";
}

// Edit users password CODE = 10050005
void Server::EditPw(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//��й�ȣ ���� �ӽú���
	InfoType info;
	cout << "\n\t Enter the Password." << endl;
	info.SetPwFromKB();

	//��й�ȣ�� ���� ��
	if (Client->CompareByPw(info) == EQUAL)
	{
		cout << "\n\t Enter the New Password." << endl;
		//��й�ȣ ����
		u_List[u_List.Search(*Client)].SetPwFromKB();
		Client->SetPw(u_List[u_List.Search(*Client)].GetPw());
		alarm = "Changed Successively.";
	}
	//��й�ȣ�� �ٸ� ��
	else
		alarm = "Check Password again.";
}

// Mem Leave by Client CODE = 10050006
void Server::Memleave(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//�ǻ� Ȯ��
	cout << "\n\t Wanna delete seriously? (Y/N): ";

	//char�� �ӽú���
	char ans;
	cin >> ans;
	//�����ϸ�
	if (ans == 'Y' || ans == 'y')
	{
		//c_List ����
		for (int i = 0; i < c_List.GetLength(); i++)
		{
			//���� ����ê ��Ͽ� ���� ������ ������ (���� üũ�ϴ� ������ ���� ������ ���� ä�ù��� ������� ������ �׸�ŭ ����.)
			if (c_List[i].Checkmem(Client->GetId()))
				//����
				c_List[i].Deletemem(Client->GetId());
		}

		//u_List����
		for (int i = 0; i < u_List.GetLength(); i++)
		{
			//i��° ������ �ڱ��ڽ��̸� �Ѿ��.
			if (u_List[i].GetId() == Client->GetId())
				continue;
			else
				//���� ���� ������ i��° ������ ģ�����
				if (u_List[i].Searchfriend(Client->GetId()) != -1)
					//����
					u_List[i].Deletefriend(Client->GetId());
		}
		//���� ����
		u_List.Delete(*Client);
		//���� ���������� ��ȯ
		Client->ResetRecord();
		//������� ��ȯ
		status = SERVER;

		alarm = "Delete Successively.";
	}
	//�����ϸ�
	else
	{
		alarm = "Not deleted.";
	}


}


//-------------------------CHAT-------------------------------

// Send msg in Client_Chat CODE = 10060001
void Server::Sendmsg(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	Msg newmsg;
	newmsg.SetSendId(Client->GetId());
	newmsg.SetTextFromKB();
	newmsg.SetDate();
	//���� ä�ù� �� �� ���� �޶�������
	if (newmsg.GetDate().substr(0, 10) != Client_Chat->GetLastdate().substr(0, 10))
	{
		//���ο� ��¥�� �˸��� ������ ��
		Msg alarmdate;
		alarmdate.SetSendId("/SERVER");
		alarmdate.SetDate();
		alarmdate.SetText(alarmdate.GetDate().substr(0, 10));
		Curr_Schat->AddNewMsg(alarmdate);

		//���� �޽����� ��¥�˸� ���� �ڷ� ������
		newmsg.SetDate();
	}
	Curr_Schat->AddNewMsg(newmsg);
	display = DISPLAYALLMSG;
}

// Printallmsg CODE = 10060002
void Server::Displayallmsg(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	Client_Chat->DisplayallMsgOnScreen(Client->GetId());
}

// Chat Leave by phonenum&name CODE = 10060003
void Server::LeaveChat(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//��� ���� ����
	Msg newmsg;
	newmsg.SetSendId("/SERVER");
	newmsg.SetText("Good Bye " + Client->GetName() + " ~");
	newmsg.SetDate();
	Curr_Schat->AddNewMsg(newmsg);

	//���� Ŭ���̾�Ʈ�� ä�ù� ����
	Client->GetChats().Delete(*Client_Chat);
	//���� ��������Ʈ ä�ù� �� ����
	u_List[u_List.Search(*Client)].SetChatnum(Client->GetChatnum());

	Client->SetChatnum();
	Curr_Schat->Deletemem(Client->GetId());

	status = CHATMANAGE;
	//��� �� ��ȯ
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	//UI���
	display = DISPLAYALLCHATS;
	Client_Chat = nullptr;
	Curr_Schat = nullptr;
}

// Edit chat info CODE = 10060004
void Server::EditChat(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//UI���
	display = DISPLAYALLMSG;

	Curr_Schat->SetChatnameFromKB();
}

// Add new mem at chat CODE = 10060005
int Server::AddMem(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//UI���
	display = DISPLAYALLMSG;

	Displayallfriends(Client, Client_Chat, status, alarm, display, temptext);

	cout << "\n\t Who you want to talk." << endl;
	InfoType info;
	info.SetIdFromKB();

	//���� ���ϴ� ��ȭ��밡 ������ ģ�����
	if (Client->Searchfriend(info.GetId()) == -1)
	{
		alarm = "Dose not exists.";
		return -1;
	}
	//�ƴ϶��
	else
	{
		//���� ģ���� ���� �޾ƿ���
		u_List.Get(info, u_List.Search(info));

		//���� �̹� ä�ù濡 �ִ� ģ�����
		if (Curr_Schat->Checkmem(info.GetId()) == 1)
		{
			alarm = "Exist already.";
			return -1;
		}
		//ä�ù濡 ���ٸ�
		else
		{
			Curr_Schat->AddMembers(info.GetId(), info.GetName());

			//���ο� ��� �ʴ�� ����
			Msg newmsg;
			newmsg.SetSendId("/SERVER");
			newmsg.SetText("Wellcome " + info.GetName() + " !");
			newmsg.SetDate();
			Curr_Schat->AddNewMsg(newmsg);

			return 1;
		}
	}
}

// Delete msg (if opponent does not check it then delete.) CODE = 10060006
int Server::Deletemsg(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//UI���
	display = DISPLAYALLMSG;

	//�ؿ������� ���° �޽��� ���� Ȯ��
	cout << "\t Enter the number from the bottom. : ";

	int index;
	cin >> index;

	//Msg �ӽú���
	Msg msg;
	//�����Ϸ��� �޽��� �ӽ�����
	//���������� ���°������ �ٲ㼭 ����
	Client_Chat->GetMsgList().Get(msg, Client_Chat->GetMsgnum() - index);

	//�ε��� ��ȿ���� Ȯ��
	if (0 < index&&index <= Client_Chat->GetMsgnum())
	{
		// ���� ���� �޽����� �ƴ϶��
		if (msg.GetSendId() != "/SERVER")
		{
			//���� ä�ù濡�� ����
			if (Client_Chat->Deletemsg(Client_Chat->GetMsgnum() - index) == 1)//�����ϸ�
			{
				//������ ���� ���� �޽������ ������ ����Ǿ��ִ� �޽��� ť������ ����
				for (int i = 0; i < Curr_Schat->GetMemnum(); i++)
				{
					//�޽���ť���� �޽��� ������ŭ Ȯ��
					for (int j = 0; j < Curr_Schat->GetMsgQueueList()[i].GetMsgnum(); j++)
					{
						//i��° �޽���ť�� j��° �޽���
						if (msg.GetSendId() == Curr_Schat->GetMsgQueueList()[i].GetMsgList()[j].GetSendId())//�޽����� �۽��� �̸��̰���
							if (msg.GetText() == Curr_Schat->GetMsgQueueList()[i].GetMsgList()[j].GetText())//�޽����� �ؽ�Ʈ ������ ����
								if (msg.GetDate() == Curr_Schat->GetMsgQueueList()[i].GetMsgList()[j].GetDate())//�޽����� ���� �ð��� ������
								{
									//i��° �޽��� ť�� j��° �޽��� ����
									Curr_Schat->GetMsgQueueList()[i].Deletemsg(j);
									break;
								}
					}
				}
				return 1;
			}
			else
				return -1;
		}
		// ���� �޽��� ���
		else
		{
			alarm = "Cannot delete Sever Msg.";
			return -1;
		}
	}
	//��ȿ���� �ʴٸ�
	else
		return -1;
}

// Exit the chat. CODE = 10060007
void Server::ExitChat(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	status = CHATMANAGE;
	//��� �� ��ȯ
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	//UI���
	display = DISPLAYALLCHATS;
	Client_Chat = nullptr;
	Curr_Schat = nullptr;
}

// Send msg in Client_Chat CODE = 10060008
void Server::SendEmotion(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//�ӽ� ���� ����
	string emotion;
	string emotions[5] = { "(^ _ ^)","(��_��)","(��_��)","(- _ -)","(O _ O)" };

	for (int i = 0; i < 5; i++)
		cout << '\t' << i + 1 << ". " << emotions[i] << endl;

	//�̸�Ƽ�� ���� ����
	int num;

	cout << "\n\t What do you want. : ";
	cin >> num;

	//�ε����� ��ȯ
	num = num - 1;

	if (0 <= num && num < 5)
		emotion = emotions[num];
	else
	{
		alarm = "Wrong control.";
		return;
	}

	//�ӽ� �޽��� ����
	Msg newmsg;
	newmsg.SetSendId(Client->GetId());
	newmsg.SetText(emotion);
	newmsg.SetDate();
	//���� ä�ù� �� �� ���� �޶�������
	if (newmsg.GetDate().substr(0, 10) != Client_Chat->GetLastdate().substr(0, 10))
	{
		//���ο� ��¥�� �˸��� ������ ��
		Msg alarmdate;
		alarmdate.SetSendId("/SERVER");
		alarmdate.SetDate();
		alarmdate.SetText(alarmdate.GetDate().substr(0, 10));
		Curr_Schat->AddNewMsg(alarmdate);

		//���� �޽����� ��¥�˸� ���� �ڷ� ������
		newmsg.SetDate();
	}
	Curr_Schat->AddNewMsg(newmsg);
	display = DISPLAYALLMSG;
}

// Printallmsg CODE = 10060009
void Server::Searchmsg(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//UI���
	Displayallmsg(Client, Client_Chat, status, alarm, display, temptext);

	//ã���� �ϴ� �ؽ�Ʈ
	string text;

	cout << "\n\t Enter the word wanna look for. :";
	cin.get();
	getline(cin, text);

	//UI���
	system("cls");

	//�޽��� ã��
	Client_Chat->SearchMsg(Client->GetId(), text);
}

// Copy msg CODE = 10060010
int Server::Copymsg(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//UI���
	display = DISPLAYALLMSG;

	//�ؿ������� ���° �޽��� ���� Ȯ��
	cout << "\t Enter the number from the bottom. : ";

	//�ӽ� �ε���
	int index;
	cin >> index;

	//Msg �ӽú���
	Msg msg;

	//�ε��� ��ȿ���� Ȯ��
	if (0 < index&&index <= Client_Chat->GetMsgnum())
	{
		//���������� ���°������ �ٲ㼭 ����
		Client_Chat->GetMsgList().Get(msg, Client_Chat->GetMsgnum() - index);

		//�޽��� ����
		temptext = msg.GetText();
		return 1;
	}
	else
		return 0;
}

// Paste msg in Client_Chat CODE = 10060011
int Server::Pastemsg(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//���� �ٿ��ֱ� �� ���� ���ٸ�
	if (temptext.empty())
	{
		alarm = "Nothing to Paste.";

		//UI���
		display = DISPLAYALLMSG;
		return 0;
	}
	else
	{
		Msg newmsg;
		newmsg.SetSendId(Client->GetId());
		newmsg.SetText(temptext);
		newmsg.SetDate();
		//���� ä�ù� �� �� ���� �޶�������
		if (newmsg.GetDate().substr(0, 10) != Client_Chat->GetLastdate().substr(0, 10))
		{
			//���ο� ��¥�� �˸��� ������ ��
			Msg alarmdate;
			alarmdate.SetSendId("/SERVER");
			alarmdate.SetDate();
			alarmdate.SetText(alarmdate.GetDate().substr(0, 10));
			Curr_Schat->AddNewMsg(alarmdate);

			//���� �޽����� ��¥�˸� ���� �ڷ� ������
			newmsg.SetDate();
		}
		Curr_Schat->AddNewMsg(newmsg);
		display = DISPLAYALLMSG;
		return 1;
	}
}

// Delive msg CODE = 10060012
int Server::Delivermsg(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{

	//�ؿ������� ���° �޽��� ���� Ȯ��
	cout << "\t Enter the number from the bottom. : ";

	//�ӽ� �ε���
	int index;
	cin >> index;

	//Msg �ӽú���
	Msg msg;

	//�ε��� ��ȿ���� Ȯ��
	if (0 < index&&index <= Client_Chat->GetMsgnum())
	{
		//���������� ���°������ �ٲ㼭 ����
		Client_Chat->GetMsgList().Get(msg, Client_Chat->GetMsgnum() - index);

		Msg newmsg;
		newmsg.SetSendId(Client->GetId());
		newmsg.SetText(msg.GetText());
		newmsg.SetDate();

		//������ ä�ù� ��
		Displayallchats(Client, Client_Chat, status, alarm, display, temptext);

		cout << "\t Choose the Chat number to deliver--> ";
		//ä�ù� ��ȣ ����
		int getcommend;
		cin >> getcommend;

		int num = Client->GetChatnum();

		if (0 < getcommend&&getcommend <= num)
		{
			//���� ���� ä�������� ��ȯ
			Client_Chat = &Client->GetChats()[getcommend - 1];

			//ä�ù�ѹ� �ӽú���
			int Chatcode;

			//���õ� ��ȣ�� ä�ù��� ä�ù�ѹ� �ޱ�
			Chatcode = Client_Chat->GetChatcode();

			//���� ���ӵ� ä�ù����� ����
			Curr_Schat = &c_List[Chatcode];


			//���� ä�ù� �� �� ���� �޶�������
			if (newmsg.GetDate().substr(0, 10) != Client_Chat->GetLastdate().substr(0, 10))
			{
				//���ο� ��¥�� �˸��� ������ ��
				Msg alarmdate;
				alarmdate.SetSendId("/SERVER");
				alarmdate.SetDate();
				alarmdate.SetText(alarmdate.GetDate().substr(0, 10));
				Curr_Schat->AddNewMsg(alarmdate);

				//���� �޽����� ��¥�˸� ���� �ڷ� ������
				newmsg.SetDate();
			}
			//�޽��� ������
			Curr_Schat->AddNewMsg(newmsg);
			display = DISPLAYALLMSG;
			return 1;
		}
		else
		{
			alarm = "Check the number again.";
			return -1;
		}
	}
	else
		return 0;

}

//-------------------------SUB-------------------------------

// move to Login CDOE = 10090001
void Server::GoBack(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	status = LOGIN;
}

// Update Chats from server
void Server::UpdateChats(InfoType*& Client, Chat*& Client_Chat, StatusType& status, string& alarm, DisPlayType& display, string& temptext)
{
	//���� ������ �ƹ� ä�õ� ���ٸ�

	if (!c_List.GetLength())
		return;


	//������ ä���ڵ带 ���� ����
	vector<int> code;
	//������ ä�ù� ��
	int num = Client->GetChatnum();

	//chat���� �ӽ� ����
	Chat* chat;
	//msg���� �ӽ� ����
	Msg msg;



	//����ä���� ������ �ڵ带 ���� �ӽú���
	int lastcode;
	//���� ���� ä�ù��� ���ٸ�
	if (!num)
		lastcode = 0;
	else
	{
		for (int i = 0; i < num; i++)
		{
			//���������� ä�ù� �ڵ带 �޾ƿ�
			code.push_back(Client->GetChats()[i].GetChatcode());
			// �ڵ��ȣ ������������ ����
			std::sort(code.begin(), code.end());
		}
		lastcode = code[num - 1] + 1;
	}

	//���ο� ��ȭ�� ������� Ȯ��
	for (int i = lastcode; i < c_List.GetLength(); i++)//���� ��ȭâ�� �ִ� �Ǹ����� �ڵ尡 ���� �������� ���� ä�� ->���ϸ����� ������ �ڵ� �������� ã��
	{
		//���ο� ��ȭ�� �ִٸ�
		if (c_List[i].Checkmem(Client->GetId()) == 1)
		{
			chat = new Chat;
			//chat�� �ӽ�����
			(*chat).SetChatcode(c_List[i].GetChatcode());
			(*chat).SetChatname(c_List[i].GetChatname());
			(*chat).SetMem(c_List[i].GetMem());
			(*chat).SetMemnum();

			//���� �������� ä�� �߰�
			Client->AddChat((*chat));
			//code�迭�� �߰�����
			code.push_back(c_List[i].GetChatcode());
			num++;
		}
	}

	//code vector �ٽ� �ʱ�ȭ
	code.clear();
	//���Է�
	for (int i = 0; i < num; i++)
		//���������� ä�ù� �ڵ带 �޾ƿ�
		code.push_back(Client->GetChats()[i].GetChatcode());


	for (int i = 0; i < num; i++)
	{
		//ä�ù��̸� �ٿ�ε�
		Client->GetChats()[i].SetChatname(c_List[code[i]].GetChatname());

		//ä�ù����� �ٿ�ε�
		Client->GetChats()[i].SetMem(c_List[code[i]].GetMem());
		Client->GetChats()[i].SetMemnum();

		//�޽��� ����Ʈ�� �޾ƿ�
		for (int j = 0; j < c_List[code[i]].GetMemnum(); j++)
		{
			// ���� code�� ������ �ִ� ä�ù��� MQ����Ʈ�� ���� ������ ���̸�
			if (c_List[code[i]].GetMsgQueueList()[j].GetId() == Client->GetId())
			{
				//MsgQ�� �׿��ִ� �޽��� ��ŭ ���ο� �˸����� ��ȯ
				Client->GetChats()[i].SetNewmsg(c_List[code[i]].GetMsgQueueList()[j].GetMsgnum());

				//�޽��� ť�� empty�� �ɶ� ����
				while (!c_List[code[i]].GetMsgQueueList()[j].GetMsgList().IsEmpty())
				{
					// Msg�� �ϳ��� ������ �ű��.
					c_List[code[i]].GetMsgQueueList()[j].GetMsgList().DeQueue(msg);
					Client->GetChats()[i].AddNewMsg(msg);
				}
				c_List[code[i]].GetMsgQueueList()[j].ResetMsgnum();
				break;
			}
		}
	}
}

// Open a file by file descriptor as an input file.
int Server::OpenInFile(char *fileName)
{
	u_InFile.open(fileName);	// file open for reading.

								// ���� ���¿� �����ϸ� 1, �׷��� �ʴٸ� 0�� ����.
	if (!u_InFile)	return 0;
	else	return 1;
}

// Open a file by file descriptor as an output file.
int Server::OpenOutFile(char *fileName)
{
	u_OutFile.open(fileName);	// file open for writing.

								// ���� ���¿� �����ϸ� 1, �׷��� �ʴٸ� 0�� ����.
	if (!u_OutFile)	return 0;
	else	return 1;
}

// Open a file as a read mode, read all data on the file, and set list by the data.
int Server::ReadDataFromFile()
{
	int index = 0;
	InfoType* data;	// �б�� �ӽ� ����

	char filename_user[FILENAMESIZE];
	for (int i = 0; i <= NAMESIZE_USER; i++)
		filename_user[i] = FILENAME_USER[i];

	// file open, open error�� �߻��ϸ� 0�� ����
	if (!OpenInFile(filename_user))
		return 0;

	// ������ ��� ������ �о� list�� �߰�
	while (!u_InFile.eof())
	{
		// array�� �л����� ������ ����ִ� structure ����
		data = new InfoType;
		(*data).ReadDataFromFile(u_InFile);
		if (!u_InFile.eof())
			u_List.Add(*data);
		else
			delete data;
	}

	u_InFile.close();	// file close

	ServerChat* schat;	// �б�� �ӽ� ����
	MsgQueue* msgq;      // �б�� �ӽ� ����
	char filename_chat[FILENAMESIZE];
	for (int i = 0; i <= NAMESIZE_CHAT; i++)
		filename_chat[i] = FILENAME_CHAT[i];

	// file open, open error�� �߻��ϸ� 0�� ����
	if (!OpenInFile(filename_chat))
		return 0;

	//�ӽû��
	index = 0;

	// ������ ��� ������ �о� list�� �߰�
	while (!u_InFile.eof())
	{
		schat = new ServerChat;
		// Serverchat �� �о����
		(*schat).sc_ReadDataFromFile(u_InFile);
		if (!u_InFile.eof())
		{
			c_List.Add(*schat);
			for (int i = 0; i < (*schat).GetMemnum(); i++)
			{
				msgq = new MsgQueue;
				(*msgq).mq_ReadDataFromFile(u_InFile);
				c_List[index].AddNewMsgQueue(*msgq);
			}
			index++;
		}
		else
			delete schat;
	}

	u_InFile.close();	// file close

	return 1;
}

// Open a file as a write mode, and write all data into the file,
int Server::WriteDataToFile()
{
	InfoType data;	// ����� �ӽ� ����

	char filename_user[FILENAMESIZE];

	for (int i = 0; i <= NAMESIZE_USER; i++)
	{
		filename_user[i] = FILENAME_USER[i];
	}

	// file open, open error�� �߻��ϸ� 0�� ����
	if (!OpenOutFile(filename_user))
		return 0;

	// list�� ��� �����͸� ���Ͽ� ����
	int length = u_List.GetLength();
	for (int i = 0; i < length; i++)
	{
		u_List[i].WriteDataToFile(u_OutFile);
	}

	u_OutFile.close();	// file close


	char filename_chat[FILENAMESIZE];


	for (int i = 0; i <= NAMESIZE_CHAT; i++)
	{
		filename_chat[i] = FILENAME_CHAT[i];
	}

	// file open, open error�� �߻��ϸ� 0�� ����
	if (!OpenOutFile(filename_chat))
		return 0;


	// list�� ��� �����͸� ���Ͽ� ����
	length = c_List.GetLength();
	for (int i = 0; i < length; i++)
	{
		c_List[i].sc_WriteDataToFile(u_OutFile);
		for (int j = 0; j < c_List[i].GetMemnum(); j++)
		{
			c_List[i].GetMsgQueueList()[j].mq_WriteDataToFile(u_OutFile);
		}
	}

	u_OutFile.close();	// file close

	return 1;
}