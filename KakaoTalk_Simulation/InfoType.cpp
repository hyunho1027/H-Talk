#include "InfoType.h"


// Set user id from keyboard.
void InfoType::SetIdFromKB()
{
	cout << "\t ID : ";
	cin >> u_Id;
	transform(u_Id.begin(), u_Id.end(), u_Id.begin(), ::tolower);
}

// Set user pw from keyboard.
void InfoType::SetPwFromKB()
{
	cout << "\t Pw : ";
	cin >> u_Pw;
}

// Set user name from keyboard.
void InfoType::SetNameFromKB()
{
	cout << "\t Name : ";
	cin >> u_Name;
}

// Set user Phonenum from keyboard.
void InfoType::SetPhonenumFromKB()
{
	cout << "\t Phonenum : 010";
	cin >> u_Phonenum;
}

// Set user Birth from keyboard.
void InfoType::SetBirthFromKB()
{
	cout << "\t Birth : ";
	cin >> u_Birth;
}

// Set user Gender from keyboard.
void InfoType::SetGenderFromKB()
{
	cout << "\t Gender : ";
	cin >> u_Gender;
}

// Set user Picture from keyboard.
void InfoType::SetPicFromKB()
{
	cout << "\t Pic : ";
	cin >> u_Pic;
}

// Set user Backpicture from keyboard.
void InfoType::SetBackpicFromKB()
{
	cout << "\t Backpic : ";
	cin >> u_Backpic;
}

// Set user Backtext from keyboard.
void InfoType::SetBacktextFromKB()
{
	cout << "\t BackText : ";
	cin.get();
	getline(cin, u_Backtext);
}

// Set user record from keyboard.
void InfoType::SetRecordFromKB()
{
	SetIdFromKB();
	SetPwFromKB();
	SetNameFromKB();
	SetPhonenumFromKB();
	SetBirthFromKB();
	SetGenderFromKB();
}


// Read a record from file.
int InfoType::ReadDataFromFile(ifstream& fin)
{
	fin >> u_Id;
	transform(u_Id.begin(), u_Id.end(), u_Id.begin(), ::tolower);
	fin >> u_Pw;
	fin >> u_Name;
	fin >> u_Phonenum;
	fin >> u_Birth;
	fin >> u_Gender;
	fin >> u_Pic;
	fin >> u_Backpic;
	char data[255];
	fin.get();
	fin.getline(data, 255);
	u_Backtext = data;
	fin >> u_Lastdate;
	fin >> u_Friendnum;
	string subfrd;
	for (int i = 0; i < u_Friendnum; i++)
	{
		fin >> subfrd;
		u_Friends.Add(subfrd);
	}
	fin >> u_Chatnum;

	return 1;
};

// Write a record into file.
int InfoType::WriteDataToFile(ofstream& fout)
{
	fout << endl;
	fout << u_Id << " ";
	fout << u_Pw << " ";
	fout << u_Name << " ";
	fout << u_Phonenum << " ";
	fout << u_Birth << " ";
	fout << u_Gender << " ";
	fout << u_Pic << " ";
	fout << u_Backpic << " ";
	fout << u_Backtext << "\n";
	fout << u_Lastdate << " ";
	fout << u_Friendnum << " ";
	DoublyIterator<string> iter(u_Friends);
	while (iter.NotNull())
	{
		fout << iter.Next() << " ";
	}
	fout << u_Chatnum << " ";
	return 1;
}


// Compare two Infotypes.
RelationType InfoType::CompareByBase(const InfoType &data)
{
	if (this->u_Id > data.u_Id)
		return GREATER;
	else if (this->u_Id < data.u_Id)
		return LESS;
	else
		return EQUAL;
}

// Compare two Infotypes.
RelationType InfoType::CompareByPw(const InfoType &data)
{
	if (this->u_Pw > data.u_Pw)
		return GREATER;
	else if (this->u_Pw < data.u_Pw)
		return LESS;
	else
		return EQUAL;
}

// Compare two Infotypes.
RelationType InfoType::CompareByName(const InfoType &data)
{
	if (this->u_Name > data.u_Name)
		return GREATER;
	else if (this->u_Name < data.u_Name)
		return LESS;
	else
		return EQUAL;
}

// Search friend at users friends
int InfoType::Searchfriend(string Id)
{
	for (int i = 0; i < u_Friendnum; i++)
	{
		if (u_Friends[i] == Id)
			return i;
	}
	return -1;
}

// Search friend at users friends
int InfoType::SearchChatcode(int code)
{
	if (!u_Chats.GetLength())
		return -1;
	for (int i = 0; i < u_Chatnum; i++)
	{
		if (u_Chats[i].GetChatcode() == code)
			return i;
	}
	return -1;
}

// Operator < with two Infotypes.
bool InfoType::operator<(const InfoType& data)
{
	if (this->CompareByBase(data) == LESS)
		return true;
	else
		return false;
}
// Operator > with two Infotypes.
bool InfoType::operator>(const InfoType& data)
{
	if (this->CompareByBase(data) == GREATER)
		return true;
	else
		return false;
}
// Operator == with two Infotypes.
bool InfoType::operator==(const InfoType& data)
{
	if (this->CompareByBase(data) == EQUAL)
		return true;
	else
		return false;
}