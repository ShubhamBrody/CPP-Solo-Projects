#include<iostream>
#include<dirent.h>
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<thread>

using namespace std;
DIR *dr;
struct dirent *en;
int endLog = 100000;
char* path;
string nameArr[100];


int dirPrinter(int selected)
{
    int i = 0;

    dr = opendir(path); //open all directory
    if (dr) {
            system("cls");
    while ((en = readdir(dr)) != NULL)
    {
        if(i == selected)
            cout << "-> ";
        else
            cout << "   ";
         nameArr[i] = en->d_name;
         i++;
         cout << en->d_name << "\n"; //print all directory name
    }
    endLog = i-1;
    cout << "endlog " << endLog << endl;
    closedir(dr); //close all directory
    return 1;
   }
   else
    return 0;
}

void dirOpener()
{
   int selected = 0;
   dirPrinter(0);
   char ch = (char)-1;
   do
   {
    if(_kbhit())
    {
       ch = _getch();
       if(ch == (char)13)
       {
          string fu(path);
          fu = fu + "/" + nameArr[selected];
          path = &fu[0];
          int k = dirPrinter(0);
          if(k)
            selected = 0;
       }
       if(ch == (char)72)//UP
       {
           if(selected-1 < 0)
           selected = 1;
           dirPrinter(--selected);
       }
       if(ch == (char)80)//DOWN
       {
           if(selected+1 > endLog)
           selected = endLog-1;
           dirPrinter(++selected);
       }
    }
   }while(1);
}

int main()
{
    string iniPath;
    cout << "Enter the initial directory : " << endl;
    getline(cin, iniPath);
    path = &iniPath[0];
    dirOpener();
}
