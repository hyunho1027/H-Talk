#include "Msg.h"


// Set user name from keyboard.
void Msg::SetTextFromKB()
{
	cout << "\tText : ";
	cin.get();
	getline(cin, m_Text);
}

// Compare two Infotypes.
RelationType Msg::CompareByBase(const Msg &data)
{
	if (this->m_Date > data.m_Date)
		return GREATER;
	else if (this->m_Date < data.m_Date)
		return LESS;
	else
		return EQUAL;
}

// Operator < with two Msgs.
bool Msg::operator<(const Msg& data)
{
	if (this->CompareByBase(data) == LESS)
		return true;
	else
		return false;
}
// Operator > with two Msgs.
bool Msg::operator>(const Msg& data)
{
	if (this->CompareByBase(data) == GREATER)
		return true;
	else
		return false;
}
// Operator == with two Msgs.
bool Msg::operator==(const Msg& data)
{
	if (this->CompareByBase(data) == EQUAL)
		return true;
	else
		return false;
}

// Read a record from file.
int Msg::m_ReadDataFromFile(ifstream& fin)
{
	fin >> m_SendId;
	char text[255];
	fin.get();
	fin.getline(text, 255);
	m_Text = text;
	fin >> m_Date;

	return 1;
};

// Write a record into file.
int Msg::m_WriteDataToFile(ofstream& fout)
{
	fout << endl;
	fout << m_SendId << " ";
	fout << m_Text << "\n";
	fout << m_Date << " ";

	return 1;
}