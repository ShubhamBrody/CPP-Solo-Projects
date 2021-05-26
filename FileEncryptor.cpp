#include<iostream>
#include<fstream>
#include<conio.h>
#include<time.h>
#include<string.h>
#include<thread>
#include<windows.h>

#define PROCESS Byte + 666 * c - 342 * c


using namespace std;

int loadernum = 1, loadfin = 0;
long long converted = 0;
time_t startTime, endTime;
double perc = 0.0;
int X = 0, Y = 7;
int etaStart, etaEnd;
long long file_size = 0;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO info;

void timePrinter(int seconds)
{
    int hours = 0, minutes = 0;

    minutes = seconds / 60;
    seconds = seconds % 60;
    hours = minutes / 60;
    minutes = minutes % 60;

    if(hours != 0)
    {
        cout << hours << " hour";
        if(hours > 1)
            cout <<"s ";
        cout << minutes << " minute";
            if(minutes > 1)
                cout << "s ";
            cout << " ";
    }
    else
    {
        if(minutes != 0)
        {
            cout << minutes << " minute";
            if(minutes > 1)
                cout << "s";
            cout << " ";
        }

    }
    cout << seconds << " second";
    if(seconds > 1)
        cout << "s";
}

void progressPrinter(float offset = 0.0f)
{
    char c = 219, cc = 249;
    COORD pos = {0, 8};
        SetConsoleCursorPosition(hConsole, pos);
        perc = (converted * 100) / file_size;
        printf("|");
        for(int i = 0;i < 100;i+=2)
        {
            if(i < perc)
            printf("%c",c);
            else
                printf(" ");
        }
        printf("|");
        printf(" %.0f", perc);
        printf("% DONE");
        printf(" %c ",cc);
        if(perc >= 1)
        {
            etaEnd = time(NULL);
            printf("TimeLeft = ");
            int time_left = (int)((double)((etaEnd-etaStart) / perc) * (100 - perc) - offset);
            double insps = (double)converted / (etaEnd - etaStart);
            timePrinter(time_left);
            printf(" %c ",cc);
            printf(" Conversion Speed = %.2f characters per second", insps);
            cout << "                                                                  ";
        }
        pos = {X+1, Y};
        SetConsoleCursorPosition(hConsole, pos);
}

void patternPrinter(int rep_time)
{
    for(int i = 0;i < rep_time;i++)
    {
        printf("/");
        GetConsoleScreenBufferInfo(hConsole, &info);
        X = info.dwCursorPosition.X;
        Y = info.dwCursorPosition.Y;
        progressPrinter();
        Sleep(62.5);
        printf("\b\b \b");
        printf("-");
        GetConsoleScreenBufferInfo(hConsole, &info);
        X = info.dwCursorPosition.X;
        Y = info.dwCursorPosition.Y;
        progressPrinter();
        Sleep(62.5);
        printf("\b\b \b");
        printf("\\");
        GetConsoleScreenBufferInfo(hConsole, &info);
        X = info.dwCursorPosition.X;
        Y = info.dwCursorPosition.Y;
        progressPrinter();
        Sleep(62.55);
        printf("\b\b \b");
        printf("|");
        GetConsoleScreenBufferInfo(hConsole, &info);
        X = info.dwCursorPosition.X;
        Y = info.dwCursorPosition.Y;
        progressPrinter();
        Sleep(62.5);
        printf("\b\b \b");
    }
    X = 10;
    Y = 7;
}

void loadingScreen(int mode, int fsize)
{
    etaStart = time(NULL);
    Sleep(500);
    etaEnd = time(NULL);

    char ch[] = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '{', '}', '[', ']'};
    srand(time(0));
    char pri[] = {'E', 'N', 'C', 'R', 'Y', 'P', 'T', 'I' ,'N', 'G'};

    if(mode == -1){
        pri[0] = 'D';
        pri[1] = 'E';
    }

    int counter = 0;
    int prinval = 0;
    while(perc <= 100)
    {
        if(loadernum == 0)
            break;
        printf("*");

        progressPrinter();

        for(int i = 0;i < 5;i++){
            if(i == 4)
            {
                printf("\b \b%c", pri[prinval]);
                    prinval++;
                GetConsoleScreenBufferInfo(hConsole, &info);
                X = info.dwCursorPosition.X;
                Y = info.dwCursorPosition.Y;
                break;
            }
            printf("\b \b%c", ch[rand() % 14]);
            Sleep(40);
        }
        counter++;
        if(counter == 10){
            patternPrinter(4);
            for(int j = 0;j < 10;j++)
            {
                printf("\b \b");
                GetConsoleScreenBufferInfo(hConsole, &info);
                X = info.dwCursorPosition.X - 1;
                Y = info.dwCursorPosition.Y;
                progressPrinter();
                Sleep(70);
            }
            GetConsoleScreenBufferInfo(hConsole, &info);
            X = info.dwCursorPosition.X;
            Y = info.dwCursorPosition.Y;
            counter = 0;
            prinval = 0;
        }
    }
    COORD pos = {0, 7};
    SetConsoleCursorPosition(hConsole, pos);
    if(mode == -1)
    cout << "DECRYPTED SUCCESSFULLY";
    else
    cout << "ENCRYPTED SUCCESSFULLY";
    X = 0;
    Y = 10;
    perc = 100;
    progressPrinter();
    pos = {0, 10};
    SetConsoleCursorPosition(hConsole, pos);
    loadfin = 1;
}

void sizePrinter(long long size_bytes)
{
    //Since the constraint is only till 1GB hence I am not considering file sizes in TeraBytes.
    int i = -1;
    double size_new = size_bytes;
    while(size_bytes >= 1024)
    {
        size_new = size_bytes / 1024.0;
        size_bytes = size_bytes / 1024.0;
        i++;
    }
    cout<<"Size of the file is"<< " " ;
    printf("%.2f", size_new);
    if(i == -1)
        cout <<" bytes" << endl;
    else if(i == 0)
        cout << " KB" << endl;
    else if(i == 1)
        cout << " MB" << endl;
    else
        cout << " GB" << endl;
}

string lineEnDecryptor(string line, int c)
{
    int i = 0;
	    while(i < line.length()){
            if(c == -1 && line[i] == (char)0)
                line[i] = '\n';
            line[i] = line[i] + (666 * c);
            if(c == 1 && line[i] == '\n')
                line[i] = (char)0;
            i++;
	    }
	    return line;
}

string passwordHider()
{
    string password = "";

    while(1)
    {
    if(_kbhit())
    {
        char ch = _getch();
        if(ch == (char)13 || ch == (char)27)
        {
            if(password.length() >= 4)
            break;
            else
            {
                cout << " LENGTH SHORT";
                Sleep(500);
                for(int i = 0; i < 13; i++)
                {
                    cout << "\b \b";
                }
            }
        }
        else if(ch == (char)8)
        {
            if(password.length() == 1)
            {
                password= "";
                printf("\b \b");
            }
            else if(password.length())
            {
                password = password.substr(0,password.length()-1);
                printf("\b \b");
            }
        }
        else
        {
            cout << "*";
            password += ch;
        }
    }
    }

    char opt;
    cout << "\n\n Do You Want To View Your Password : " << endl;
    cin >> opt;

    if(opt == 'y' || opt == 'Y')
    {
        cout << password;
        cout << "\nPress any key to proceed." << endl;
        _getch();
    }
    return password;
}

void worker(string f, int c)
{
    if(c != 1 && f.substr(f.find_last_of('.')) != ".encrypt")
    {
        cout << "An Encrypted File with \'.encrypt\' file extension is required to Decrypt.";
        cout << "Press any key to exit" << endl;
        _getch();
        exit(0);
    }
    ifstream in_file(f, ios::binary);
    if(!in_file)
    {
        cout << "ERROR OCCURED WHILE OPENING THE FILE" << endl;
        cout << "Press any key to exit" << endl;
        _getch();
        exit(0);
    }
    in_file.seekg(0, ios::end);
    file_size = in_file.tellg();
    in_file.close();

    string fo;
    if(c == 1)
        fo = f + ".encrypt";
    else
        fo = f.substr(0,f.find_last_of('.'));

    char* f_unfound = &fo[0];
    char* fname = &f[0];
    ifstream read(fname, ios::binary);
    if(!read)
    {
        cout << "ERROR OCCURED WHILE OPENING THE FILE" << endl;
        cout << "Press any key to exit" << endl;
        _getch();
        exit(0);
    }
    ofstream write(f_unfound, ios::binary);
    if(!write)
    {
        cout << "ERROR OCCURED WHILE OPENING THE FILE" << endl;
        cout << "Press any key to exit" << endl;
        _getch();
        exit(0);
    }
    if(c == 1)
    {
        string p1;
        cout << "Enter the password to protect the file." << endl;
        p1 = passwordHider();
        p1 = lineEnDecryptor(p1, c);
        write << p1 << endl;
    }
    else{
        string p1, saved;
        cout << "Enter the password to decrypt the file." << endl;
        getline(cin, p1);
        getline(read, saved);
        converted += saved.length();
        saved = lineEnDecryptor(saved, c);
        if(saved != p1)
        {
            cout << "The password is INCORRECT.";
            cout << "Press any key to exit" << endl;
            _getch();
            exit(1);
        }
    }

    system("cls");

    sizePrinter(file_size);

    char Byte;

    COORD poss = {0,1};
	SetConsoleCursorPosition(hConsole, poss);
	cout << "+---------------------------------------+           "<< endl;
    Sleep(100);
    cout << "| |     | +---+ +--+ | / + |\\   | +---- |          " << endl;
    Sleep(100);
    cout << "| |     | |   | |__| |/  | | \\  | |___  |          " << endl;
    Sleep(100);
    cout << "| |  /\\ | |   | |  \\ |\\  | |  \\ | |   | |       " << endl;
    Sleep(100);
    cout << "|  \\/  \\/ +---+ |  | | \\ + |   \\| +---+ |       " << endl;
    Sleep(100);
    cout << "+---------------------------------------+           "<< endl;
    Sleep(100);

    thread t(loadingScreen, c, file_size);

     while(1)
    {
       Byte = read.get();
       converted++;
       if (read.fail()){
       break;
       }
       Byte = PROCESS;
       write.put(Byte);
   }
   read.close();
   write.close();

    loadernum = 0;
	while(loadfin!=1){}
	printf("\r");

	COORD pos = {0, 1};
	SetConsoleCursorPosition(hConsole, pos);

	X = 0;
	Y = 1;
	perc = 100;
	progressPrinter();

	cout << "+--------------------------------------------------------+ "<< endl;
    Sleep(100);
    cout << "| |     | +---+ +--+ | /   -+----  +---+ |\\      | +---- | " << endl;
    Sleep(100);
    cout << "| |     | |   | |__| |/     |    | |   | |  \\    | |___  | " << endl;
    Sleep(100);
    cout << "| |  /\\ | |   | |  \\ |\\     |    | |   | |    \\  | |     | " << endl;
    Sleep(100);
    cout << "|  \\/  \\/ +---+ |  | |  \\  -+----  +---+ |      \\| +---+ | " << endl;
    Sleep(100);
    cout << "+--------------------------------------------------------+ "<< endl;
    Sleep(100);

    pos = {0, 11};
	SetConsoleCursorPosition(hConsole, pos);

	char req;

	endTime = time(NULL);
	cout << "Do you want to delete the file processed?(Y/N)" << endl;
	cout << "Option : ";
	cin >> req;
	if(req == 'Y' || req == 'y')
    {
        remove(fname);
        cout << "The file " << fname << " is deleted successfully." << endl;

    }
    string mod;
    if(c == 1){
        mod = "en";
    }
    else{
        mod = "de";
    }

	cout<<"\n\nFile "<<fname << " " + mod + "crypted successfully..!!" << endl;
	cout << "\nTotal time required to " + mod + "crypt the file is : ";
	timePrinter(endTime - startTime);
	cout << "\n\nPress any key to exit." << endl;
	_getch();
	t.~thread();
}

inline string inputter()
{
    cin.ignore();
    string str;
    getline(cin, str);
    return str;
}

void fullscreen()
{
keybd_event(VK_MENU,0x38,0,0);
keybd_event(VK_RETURN,0x1c,0,0);
keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}

int main()
{
    int ch;
	string fname;
	system("cls");
	fullscreen();

	cout << "Enter your choice as 1 or 2 accordingly : " << endl;
	cout << "1. Encrypt a file." << endl;
	cout << "2. Decrypt a file." << endl;
	cout << "(Any number other than 1 and 2). Exit the application" << endl;

	cin >> ch; // Here I am RECIEVING THE CHOICE FOR THE WORK TO BE DONE.

	switch(ch)
	{
case 1 :
    cout<<"Enter file name (with extension like file.txt or file.pdf and with complete file path) to encrypt : ";
    fname = inputter();
    startTime = time(NULL);
    srand(time(0));
	worker(fname, 1);
	break;
case 2 :
    cout<<"Enter file name (with extension like file.encrypt and with complete file path) to decrypt : ";
    fname = inputter();
    startTime = time(NULL);
	worker(fname, -1);
	break;
default:
    cout << "Wrong number!!!" << endl;
    cout << "\nEnding the application" << endl;
    exit(0);
	}
	exit(0);
}
