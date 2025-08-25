#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <cctype>
#include <fstream>

using namespace std;

char character;
string input;
string output;
int character_case;
string st_file_read;
char ch_file_read[26] = { 'd', 't', 'a', 'h', 'x', 'i', 'e', 'g' };
string command;

/*
	a is used for length of I/O
	i is used for 0 - 26 rotor looping
	t is used for rotor and reflector selection
	x is used for other rotor looping
	y is used for looping through plugboard
*/
int a;
int i;
int t;
int x;
int y;

/*
	variables represent rotor rotation position
	c = rotor1
	cc = rotor2
	ccc = rotor3
*/
int c = 0;
int cc = 0;
int ccc = 0;

/*
	variables represent rotor rotating position
	d = rotor1
	dd = rotor2
	ddd = rotor3
*/
int d = 26;
int dd = 26;
int ddd = 26;

/*
	variables represent the rotor and reflectors chosen
*/
int rotor1[26];
int rotor2[26];
int rotor3[26];
int reflector[26];

char alphabet[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

int rotorI[26] = { 4, 10, 12, 5, 11, 6, 3, 16, 21, 25, 13, 19, 14, 22, 24, 7, 23, 20, 18, 15, 0, 8, 1, 17, 2, 9 };
int rotorII[26] = { 0, 9, 3, 10, 18, 8, 17, 20, 23, 1, 11, 7, 22, 19, 12, 2, 16, 6, 25, 13, 15, 24, 5, 21, 14, 4 };
int rotorIII[26] = { 1, 3, 5, 7, 9, 11, 2, 15, 17, 19, 23, 21, 25, 13, 24, 4, 8, 22, 6, 0, 10, 12, 20, 18, 16, 14 };
int rotorIV[26] = { 4, 18, 14, 21, 15, 25, 9, 0, 24, 16, 20, 8, 17, 7, 23, 11, 13, 5, 19, 6, 10, 3, 2, 12, 22, 1 };
int rotorV[26] = { 21, 25, 1, 17, 6, 8, 19, 24, 20, 15, 18, 3, 13, 7, 11, 23, 0, 22, 12, 9, 16, 14, 5, 4, 2, 10 };
int rotorVI[26] = { 9, 15, 6, 21, 14, 20, 12, 5, 24, 16, 1, 4, 13, 7, 25, 17, 3, 10, 0, 18, 23, 11, 8, 2, 19, 22 };
int rotorVII[26] = { 13, 25, 9, 7, 6, 17, 2, 23, 12, 24, 18, 22, 1, 14, 20, 5, 0, 8, 21, 11, 15, 4, 10, 16, 3, 19 };
int rotorVIII[26] = { 5, 10, 16, 7, 19, 11, 23, 14, 2, 1, 9, 18, 15, 3, 25, 17, 0, 12, 4, 22, 13, 8, 20, 24, 6, 21 };

int rotor_selection[26];

char plugboard_switches[26];

/*
	Alphabet:	ABCDEFGHIJKLMNOPQRSTUVWXYZ
	Rotor I:	EKMFLGDQVZNTOWYHXUSPAIBRCJ
	Rotor II:	AJDKSIRUXBLHWTMCQGZNPYFVOE
	Rotor III:	BDFHJLCPRTXVZNYEIWGAKMUSQO
	Rotor IV:	ESOVPZJAYQUIRHXLNFTGKDCMWB
	Rotor V:	VZBRGITYUPSDNHLXAWMJQOFECK
	Rotor VI:	JPGVOUMFYQBENHZRDKASXLICTW
	Rotor VII:	NZJHGRCXMYSWBOUFAIVLPEKQDT
	Rotor VIII:	FKQHTLXOCBJSPDZRAMEWNIUYGV
*/

/*
	Controls:
	Left Right arrow keys for config settings
	Up Down arrow keys for navigation between config & input
	Enter to clear input and output for new text
	Enter to lock config settings
	Text/Numbers/Symbols for I/O
*/

/*
	Text:
	Config Settings Used
	Config Settings Options
	Controls
	Rotor Positions
	I/O
*/

/*
	Config Settings:
	Plugboard Pugs
	Rotors Used
	Reflector Used
	Rotor Starting Position
*/

// plugboard control
char plugboard()
{
	y = 0;
	// loop through possible numbers where the character matches the plugboard
	while (character != plugboard_switches[y])
	{
		y++;
		if (y == 26)
		{
			break;
		}
	}
	// if statement where there is no plugboard change
	if (y == 26)
	{
		return character;
	}
	// if statement where the even number is y
	else if (y % 2 == 0)
	{
		return plugboard_switches[y + 1];
	}
	// else condition where the odd number is y
	else
	{
		return plugboard_switches[y - 1];
	}
}

void setup()
{
	system("CLS");
	cout << "Enigma Configuration Settings\n";
	cout << "Here are your current config settings:\n";
	ifstream setupFileRead;
	setupFileRead.open("config_settings.txt", ios::in);
	setupFileRead >> st_file_read;
	cout << "\nPlugboard Settings: " << st_file_read;
	setupFileRead >> st_file_read;
	cout << "\nRotor 1 Selection: " << st_file_read;
	setupFileRead >> st_file_read;
	cout << "\nRotor 2 Selection: " << st_file_read;
	setupFileRead >> st_file_read;
	cout << "\nRotor 3 Selection: " << st_file_read;
	setupFileRead >> st_file_read;
	cout << "\nReflector Selection: " << st_file_read;
	setupFileRead.close();
	cout << endl << "\nResetting settings for re-input...\n";
	cout << "Sucuess! Please enter your new settings.\n\n";
	ofstream setupFileWrite;
	setupFileWrite.open("config_settings.txt", ios::out | ios::trunc);
	setupFileWrite << ch_file_read << endl;
	cout << "Rotor Options: I, II, III, IV, V, VI, VII, VIII\n";
	cout << "Rotor 1: ";
	cin >> st_file_read;
	setupFileWrite << st_file_read << endl;
	cout << "Rotor 2: ";
	cin >> st_file_read;
	setupFileWrite << st_file_read << endl;
	cout << "Rotor 3: ";
	cin >> st_file_read;
	setupFileWrite << st_file_read << endl;
	cout << "Reflector: ";
	cin >> st_file_read;
	setupFileWrite << st_file_read << endl;
	setupFileWrite.close();
	ifstream setupFileConfig;
	setupFileConfig.open("config_settings.txt", ios::in);
	for (int t = 0; t < sizeof(ch_file_read) / sizeof(char); t++)
	{
		setupFileConfig >> plugboard_switches[t];
	}
	for (int t = 0; t < 3; t++)
	{
		setupFileConfig >> st_file_read;
		if (st_file_read == "I")
		{
			for (i = 0; i < 26; i++)
			{
				rotor_selection[i] = rotorI[i];
			}
		}
		if (st_file_read == "II")
		{
			for (i = 0; i < 26; i++)
			{
				rotor_selection[i] = rotorII[i];
			}
		}
		if (st_file_read == "III")
		{
			for (i = 0; i < 26; i++)
			{
				rotor_selection[i] = rotorIII[i];
			}
		}
		if (st_file_read == "IV")
		{
			for (i = 0; i < 26; i++)
			{
				rotor_selection[i] = rotorIV[i];
			}
		}
		if (st_file_read == "V")
		{
			for (i = 0; i < 26; i++)
			{
				rotor_selection[i] = rotorV[i];
			}
		}
		if (st_file_read == "VI")
		{
			for (i = 0; i < 26; i++)
			{
				rotor_selection[i] = rotorVI[i];
			}
		}
		if (st_file_read == "VII")
		{
			for (i = 0; i < 26; i++)
			{
				rotor_selection[i] = rotorVII[i];
			}
		}
		if (st_file_read == "VIII")
		{
			for (i = 0; i < 26; i++)
			{
				rotor_selection[i] = rotorVIII[i];
			}
		}
		switch (t)
		{
		case 0:
			for (i = 0; i < 26; i++)
			{
				rotor1[i] = rotor_selection[i];
			}
			break;
		case 1:
			for (i = 0; i < 26; i++)
			{
				rotor2[i] = rotor_selection[i];
			}
			break;
		case 2:
			for (i = 0; i < 26; i++)
			{
				rotor3[i] = rotor_selection[i];
			}
			break;
		}
		setupFileConfig.close();
	}
}



// main statement
int main()
{	
	ofstream setupFile;
	setupFile.open("config_settings.txt", ios::out | ios::trunc);
	setupFile << "none\n";
	setupFile << "none\n";
	setupFile << "none\n";
	setupFile << "none\n";
	setupFile << "none\n";
	setupFile.close();

	setup();

	// loop forever (maybe?)
	while (1)
	{
		// clear screen and print
		system("CLS");
		cout << "Enigma Machine Converter\n";
		cout << "\nConfiguration Settings:";
		ifstream setupFilePrint;
		setupFilePrint.open("config_settings.txt", ios::in);
		setupFilePrint >> st_file_read;
		cout << "\nPlugboard Settings: " << st_file_read;
		setupFilePrint >> st_file_read;
		cout << "\nRotor 1 Selection: " << st_file_read;
		setupFilePrint >> st_file_read;
		cout << "\nRotor 2 Selection: " << st_file_read;
		setupFilePrint >> st_file_read;
		cout << "\nRotor 3 Selection: " << st_file_read;
		setupFilePrint >> st_file_read;
		cout << "\nReflector Selection: " << st_file_read;
		setupFilePrint.close();
		cout << "\n\nControls:\n";
		cout << "Type \"Config\" to modify the current Enigma Settings\n";
		cout << "Type \"Input\" to encode or decode messages in Enigma\n";
		cout << "Type \"Close\" to print the messages and close Enigma\n";
		cout << "Any other input will refresh the screen and program\n" << endl;
		cout << "\nCommand Line: ";
		cin >> command;
		// wait for key pressed
		while (!_kbhit())
		{

		}
		// get the key pressed
		character = _getch();
		input = input + character;
		character_case = 0;
		// check for upper or lower case
		if (isupper(character))
		{
			character_case = 1;
			// convert to lowercase
			character = tolower(character);
		}
		// run through plugboard
		character = plugboard();
		// 
		for (i = 0; i < 26; i++)
		{
			x = i + c - 26;
			if (i + c > 25)
			{
				if (alphabet[i] == character)
				{
					character = alphabet[rotor1[x]];
					break;
				}
			}
			else
			{
				if (alphabet[i] == character)
				{
					character = alphabet[rotor1[i + c]];
					break;
				}
			}
		}
		for (i = 0; i < 26; i++)
		{
			x = i + cc - 26;
			if (i + cc > 25)
			{
				if (alphabet[i] == character)
				{
					character = alphabet[rotor2[x]];
					break;
				}
			}
			else
			{
				if (alphabet[i] == character)
				{
					character = alphabet[rotor2[i + cc]];
					break;
				}
			}
		}
		for (i = 0; i < 26; i++)
		{
			x = i + ccc - 26;
			if (i + ccc > 25)
			{
				if (alphabet[i] == character)
				{
					character = alphabet[rotor3[x]];
					break;
				}
			}
			else
			{
				if (alphabet[i] == character)
				{
					character = alphabet[rotor3[i + ccc]];
					break;
				}
			}
		}
		for (i = 0; i < 26; i++)
		{
			if (alphabet[i] == character)
			{
				character = alphabet[reflector[i]];
				break;
			}
		}
		for (i = 0; i < 26; i++)
		{
			x = i + ccc - 26;
			if (i + ccc > 25)
			{
				if (alphabet[rotor3[x]] == character)
				{
					character = alphabet[i];
					break;
				}
			}
			else
			{
				if (alphabet[rotor3[i + ccc]] == character)
				{
					character = alphabet[i];
					break;
				}
			}
		}
		for (i = 0; i < 26; i++)
		{
			x = i + cc - 26;
			if (i + cc > 25)
			{
				if (alphabet[rotor2[x]] == character)
				{
					character = alphabet[i];
					break;
				}
			}
			else
			{
				if (alphabet[rotor2[i + cc]] == character)
				{
					character = alphabet[i];
					break;
				}
			}
		}
		for (i = 0; i < 26; i++)
		{
			x = i + c - 26;
			if (i + c > 25)
			{
				if (alphabet[rotor1[x]] == character)
				{
					character = alphabet[i];
					break;
				}
			}
			else
			{
				if (alphabet[rotor1[i + c]] == character)
				{
					character = alphabet[i];
					break;
				}
			}
		}
		// run through plugboard again
		character = plugboard();
		// convert to uppercase if needed
		if (character_case == 1)
		{
			character = toupper(character);
		}
		// print output
		output = output + character;
		// loop through rotor turning
		c++;
		if (c == d)
		{
			c = 0;
			cc++;
		}
		if (cc == dd)
		{
			cc = 0;
			ccc++;
		}
		if (ccc == ddd)
		{
			ccc = 0;
		}
	}
}