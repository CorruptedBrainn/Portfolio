#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <cctype>
#include <fstream>

using namespace std;

fstream setupFile;
fstream ioFile;

char character;
int characterval;
int characterCase;
string io;
char commandArray[7] = { 'K' };

string strFileRead;
char chrFileRead[26];

char alphabet[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

int rotors[26 * 8] =
{
    4, 10, 12, 5, 11, 6, 3, 16, 21, 25, 13, 19, 14, 22, 24, 7, 23, 20, 18, 15, 0, 8, 1, 17, 2, 9,
    0, 9, 3, 10, 18, 8, 17, 20, 23, 1, 11, 7, 22, 19, 12, 2, 16, 6, 25, 13, 15, 24, 5, 21, 14, 4,
    1, 3, 5, 7, 9, 11, 2, 15, 17, 19, 23, 21, 25, 13, 24, 4, 8, 22, 6, 0, 10, 12, 20, 18, 16, 14,
    4, 18, 14, 21, 15, 25, 9, 0, 24, 16, 20, 8, 17, 7, 23, 11, 13, 5, 19, 6, 10, 3, 2, 12, 22, 1,
    21, 25, 1, 17, 6, 8, 19, 24, 20, 15, 18, 3, 13, 7, 11, 23, 0, 22, 12, 9, 16, 14, 5, 4, 2, 10,
    9, 15, 6, 21, 14, 20, 12, 5, 24, 16, 1, 4, 13, 7, 25, 17, 3, 10, 0, 18, 23, 11, 8, 2, 19, 22,
    13, 25, 9, 7, 6, 17, 2, 23, 12, 24, 18, 22, 1, 14, 20, 5, 0, 8, 21, 11, 15, 4, 10, 16, 3, 19,
    5, 10, 16, 7, 19, 11, 23, 14, 2, 1, 9, 18, 15, 3, 25, 17, 0, 12, 4, 22, 13, 8, 20, 24, 6, 21
};

int reflectors[26 * 3] =
{
    4, 9, 12, 25, 0, 11, 24, 23, 21, 1, 22, 5, 2, 17, 16, 20, 14, 13, 19, 18, 15, 8, 10, 7, 6, 3,
    24, 17, 20, 7, 16, 18, 11, 3, 15, 23, 13, 6, 14, 10, 12, 8, 4, 1, 5, 25, 2, 22, 21, 9, 0, 19,
    5, 21, 15, 9, 8, 0, 14, 24, 4, 3, 17, 25, 23, 22, 6, 2, 19, 10, 20, 16, 18, 1, 13, 12, 7, 11
};

char plugboardSwitches[26];

int rotorOne[26];
int rotorTwo[26];
int rotorThree[26];
int reflector[26];

int rotorOnePosition = 0;
int rotorTwoPosition = 0;
int rotorThreePosition = 0;

int rotorOneChange[2] = { 0 };
int rotorTwoChange[2] = { 0 };

int loopingVariable1;
int loopingVariable2;
int storageVariable1;

int closeCheck = 0;

void rotorPosition()
{
    rotorOnePosition++;
    if (rotorOnePosition == 26)
    {
        rotorOnePosition = 0;
    }
    if (rotorOnePosition == rotorOneChange[0] or rotorOnePosition == rotorOneChange[1])
    {
        rotorTwoPosition++;
        if (rotorTwoPosition == 26)
        {
            rotorTwoPosition = 0;
        }
        if (rotorTwoPosition == rotorTwoChange[0] or rotorTwoPosition == rotorTwoChange[1])
        {
            rotorThreePosition++;
            if (rotorThreePosition == 26)
            {
                rotorThreePosition = 0;
            }
        }
    }
}

char plugboard()
{
    loopingVariable1 = 0;
    while (character != plugboardSwitches[loopingVariable1])
    {
        loopingVariable1++;
        if (loopingVariable1 == 26)
        {
            break;
        }
    }
    if (loopingVariable1 == 26)
    {
        return character;
    }
    else if (loopingVariable1 % 2 == 0)
    {
        return plugboardSwitches[loopingVariable1 + 1];
    }
    else
    {
        return plugboardSwitches[loopingVariable1 - 1];
    }
}

char rotor(char characterRotor)
{
    for (loopingVariable1 = 0; loopingVariable1 < 26; loopingVariable1++)
    {
        loopingVariable2 = loopingVariable1 + rotorOnePosition - 26;
        if (loopingVariable1 + rotorOnePosition > 25)
        {
            if (alphabet[loopingVariable1] == characterRotor)
            {
                characterRotor = alphabet[rotorOne[loopingVariable2]];
                break;
            }
        }
        else
        {
            if (alphabet[loopingVariable1] == characterRotor)
            {
                characterRotor = alphabet[rotorOne[loopingVariable1 + rotorOnePosition]];
                break;
            }
        }
    }
    for (loopingVariable1 = 0; loopingVariable1 < 26; loopingVariable1++)
    {
        loopingVariable2 = loopingVariable1 + rotorTwoPosition - 26;
        if (loopingVariable1 + rotorTwoPosition > 25)
        {
            if (alphabet[loopingVariable1] == characterRotor)
            {
                characterRotor = alphabet[rotorTwo[loopingVariable2]];
                break;
            }
        }
        else
        {
            if (alphabet[loopingVariable1] == characterRotor)
            {
                characterRotor = alphabet[rotorTwo[loopingVariable1 + rotorTwoPosition]];
                break;
            }
        }
    }
    for (loopingVariable1 = 0; loopingVariable1 < 26; loopingVariable1++)
    {
        loopingVariable2 = loopingVariable1 + rotorThreePosition - 26;
        if (loopingVariable1 + rotorThreePosition > 25)
        {
            if (alphabet[loopingVariable1] == characterRotor)
            {
                characterRotor = alphabet[rotorThree[loopingVariable2]];
                break;
            }
        }
        else
        {
            if (alphabet[loopingVariable1] == characterRotor)
            {
                characterRotor = alphabet[rotorThree[loopingVariable1 + rotorThreePosition]];
                break;
            }
        }
    }
    for (loopingVariable1 = 0; loopingVariable1 < 26; loopingVariable1++)
    {
        if (alphabet[loopingVariable1] == characterRotor)
        {
            characterRotor = alphabet[reflector[loopingVariable1]];
            break;
        }
    }
    for (loopingVariable1 = 0; loopingVariable1 < 26; loopingVariable1++)
    {
        loopingVariable2 = loopingVariable1 + rotorThreePosition - 26;
        if (loopingVariable1 + rotorThreePosition > 25)
        {
            if (alphabet[rotorThree[loopingVariable2]] == characterRotor)
            {
                characterRotor = alphabet[loopingVariable1];
                break;
            }
        }
        else
        {
            if (alphabet[rotorThree[loopingVariable1 + rotorThreePosition]] == characterRotor)
            {
                characterRotor = alphabet[loopingVariable1];
                break;
            }
        }
    }
    for (loopingVariable1 = 0; loopingVariable1 < 26; loopingVariable1++)
    {
        loopingVariable2 = loopingVariable1 + rotorTwoPosition - 26;
        if (loopingVariable1 + rotorTwoPosition > 25)
        {
            if (alphabet[rotorTwo[loopingVariable2]] == characterRotor)
            {
                characterRotor = alphabet[loopingVariable1];
                break;
            }
        }
        else
        {
            if (alphabet[rotorTwo[loopingVariable1 + rotorTwoPosition]] == characterRotor)
            {
                characterRotor = alphabet[loopingVariable1];
                break;
            }
        }
    }
    for (loopingVariable1 = 0; loopingVariable1 < 26; loopingVariable1++)
    {
        loopingVariable2 = loopingVariable1 + rotorOnePosition - 26;
        if (loopingVariable1 + rotorOnePosition > 25)
        {
            if (alphabet[rotorOne[loopingVariable2]] == characterRotor)
            {
                characterRotor = alphabet[loopingVariable1];
                break;
            }
        }
        else
        {
            if (alphabet[rotorOne[loopingVariable1 + rotorOnePosition]] == characterRotor)
            {
                characterRotor = alphabet[loopingVariable1];
                break;
            }
        }
    }
    return characterRotor;
}

void convert()
{
    io.clear();
    rotorOnePosition = 0;
    rotorTwoPosition = 0;
    rotorThreePosition = 0;
    while (1)
    {
        characterCase = 0;
        system("CLS");
        cout << "Enigma Machine Encoder / Decoder\n";
        cout << "\nConfiguration Settings:";
        setupFile.open("config_settings.txt", ios::in);
        setupFile >> strFileRead;
        cout << "\nPlugboard Settings: " << strFileRead;
        setupFile >> strFileRead;
        cout << "\nRotor 1 Selection: " << strFileRead;
        setupFile >> strFileRead;
        cout << "\nRotor 2 Selection: " << strFileRead;
        setupFile >> strFileRead;
        cout << "\nRotor 3 Selection: " << strFileRead;
        setupFile >> strFileRead;
        cout << "\nReflector Selection: " << strFileRead;
        setupFile.close();
        cout << "\n\nControls:\n";
        cout << "Press any letter to put it through Enigma\n";
        cout << "Press \"Enter\" to move down a line\n";
        cout << "Press \"Escape\" to go back to the main page\n" << endl;
        ioFile.open("enigma_io.txt", ios::out | ios::app);
        cout << "Input: " << io;
        while (!_kbhit())
        {

        }
        characterval = _getch();
        if (characterval == 27)
        {
            ioFile << "\n" << io << endl;
            ioFile.close();
            break;
        }
        else if (characterval == 13)
        {
            ioFile << "\n" << io << endl;
            io.clear();
        }
        else
        {
            rotorPosition();
            character = characterval;
            ioFile << character;
            ioFile.flush();
            if (isupper(character))
            {
                characterCase = 1;
                character = tolower(character);
            }
            character = plugboard();
            character = rotor(character);
            character = plugboard();
            if (characterCase == 1)
            {
                character = toupper(character);
            }
            io = io + character;
        }
        ioFile.close();
    }
}

void print()
{

}

void setup()
{
    system("CLS");
    cout << "Enigma Configuration Settings\n";
    cout << "Here are your current config settings:\n";
    setupFile.open("config_settings.txt", ios::in);
    setupFile >> strFileRead;
    cout << "\nPlugboard Settings: " << strFileRead;
    setupFile >> strFileRead;
    cout << "\nRotor 1 Selection: " << strFileRead;
    setupFile >> strFileRead;
    cout << "\nRotor 2 Selection: " << strFileRead;
    setupFile >> strFileRead;
    cout << "\nRotor 3 Selection: " << strFileRead;
    setupFile >> strFileRead;
    cout << "\nReflector Selection: " << strFileRead;
    setupFile.close();
    cout << endl << "\nResetting settings for re-input...\n";
    cout << "Sucuess! Please enter your new settings.\n\n";
    setupFile.open("config_settings.txt", ios::out | ios::trunc);
    cout << "Enter an even amount of letters for the plugboard\n";
    cout << "Plugboard: ";
    cin >> chrFileRead;
    setupFile << chrFileRead << endl;
    cout << "\nRotor Options: I, II, III, IV, V, VI, VII, VIII\n";
    cout << "Rotor 1: ";
    cin >> strFileRead;
    setupFile << strFileRead << endl;
    cout << "Rotor 2: ";
    cin >> strFileRead;
    setupFile << strFileRead << endl;
    cout << "Rotor 3: ";
    cin >> strFileRead;
    setupFile << strFileRead << endl;
    cout << "\nReflector Options: A, B, C\n";
    cout << "Reflector: ";
    cin >> strFileRead;
    setupFile << strFileRead << endl;
    setupFile.close();
    setupFile.open("config_settings.txt", ios::in);
    for (int loopingVariable1 = 0; loopingVariable1 < 26; loopingVariable1++)
    {
        setupFile >> plugboardSwitches[loopingVariable1];
    }
    for (int loopingVariable1 = 0; loopingVariable1 < 3; loopingVariable1++)
    {
        setupFile >> strFileRead;
        if (strFileRead == "I")
        {
            storageVariable1 = 0;
        }
        else if (strFileRead == "II")
        {
            storageVariable1 = 1;
        }
        else if (strFileRead == "III")
        {
            storageVariable1 = 2;
        }
        else if (strFileRead == "IV")
        {
            storageVariable1 = 3;
        }
        else if (strFileRead == "V")
        {
            storageVariable1 = 4;
        }
        else if (strFileRead == "VI")
        {
            storageVariable1 = 5;
        }
        else if (strFileRead == "VII")
        {
            storageVariable1 = 6;
        }
        else if (strFileRead == "VIII")
        {
            storageVariable1 = 7;
        }
        switch (loopingVariable1)
        {
        case 0:
            for (loopingVariable2 = storageVariable1 * 26; loopingVariable2 < (storageVariable1 + 1) * 26; loopingVariable2++)
            {
                rotorOne[loopingVariable2 % 26] = rotors[loopingVariable2];
            }
            break;
        case 1:
            for (loopingVariable2 = storageVariable1 * 26; loopingVariable2 < (storageVariable1 + 1) * 26; loopingVariable2++)
            {
                rotorTwo[loopingVariable2 % 26] = rotors[loopingVariable2];
            }
            break;
        case 2:
            for (loopingVariable2 = storageVariable1 * 26; loopingVariable2 < (storageVariable1 + 1) * 26; loopingVariable2++)
            {
                rotorThree[loopingVariable2 % 26] = rotors[loopingVariable2];
            }
            break;
        }
    }
    setupFile >> strFileRead;
    if (strFileRead == "A")
    {
        storageVariable1 = 0;
    }
    else if (strFileRead == "B")
    {
        storageVariable1 = 1;
    }
    else if (strFileRead == "C")
    {
        storageVariable1 = 2;
    }
    for (loopingVariable1 = storageVariable1 * 26; loopingVariable1 < (storageVariable1 + 1) * 26; loopingVariable1++)
    {
        reflector[loopingVariable1 % 26] = reflectors[loopingVariable1];
    }
    setupFile.close();
}

void close()
{

}

void commands()
{
    while (closeCheck == 0)
    {
        system("CLS");
        cout << "Enigma Machine Converter\n";
        cout << "\nConfiguration Settings:";
        setupFile.open("config_settings.txt", ios::in);
        setupFile >> strFileRead;
        cout << "\nPlugboard Settings: " << strFileRead;
        setupFile >> strFileRead;
        cout << "\nRotor 1 Selection: " << strFileRead;
        setupFile >> strFileRead;
        cout << "\nRotor 2 Selection: " << strFileRead;
        setupFile >> strFileRead;
        cout << "\nRotor 3 Selection: " << strFileRead;
        setupFile >> strFileRead;
        cout << "\nReflector Selection: " << strFileRead;
        setupFile.close();
        cout << "\n\nControls:\n";
        cout << "Type \"Convert\" to encode or decode messages in Enigma\n";
        cout << "Type \"Config\" to modify the current Enigma Settings\n";
        cout << "Type \"Print\" to print all encoded and decoded messages\n";
        cout << "Type \"Close\" to print the messages and close Enigma\n";
        cout << "Command Line: ";
        cin >> commandArray;
        for (loopingVariable1 = 0; loopingVariable1 < 7; loopingVariable1++)
        {
            commandArray[loopingVariable1] = tolower(commandArray[loopingVariable1]);
        }
        if (_stricmp(commandArray, "config") == 0)
        {
            setup();
        }
        else if (_stricmp(commandArray, "convert") == 0)
        {
            convert();
        }
        else if (_stricmp(commandArray, "print") == 0)
        {
            print();
        }
        else if (_stricmp(commandArray, "close") == 0)
        {
            close();
        }
    }
    close();
}

int main()
{
    setupFile.open("config_settings.txt", ios::out | ios::trunc);
    setupFile << "none\n";
    setupFile << "none\n";
    setupFile << "none\n";
    setupFile << "none\n";
    setupFile << "none\n";
    setupFile.close();
    ioFile.open("enigma_io.txt", ios::out | ios::trunc);
    ioFile << "Input | Output | Config Settings" << endl;
    ioFile.close();
    
    setup();
    commands();
    return 0;
}