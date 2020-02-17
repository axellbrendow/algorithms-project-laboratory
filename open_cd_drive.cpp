/**
 * Creative Mind Researcher: ( https://github.com/xXHachimanXx )
 */

#include <windows.h>
#include <iostream>

using namespace std;

typedef MCIERROR WINAPI (*CDROM)(const char *, char *, unsigned, HWND);

CDROM pCD;

void AbrirCD()
{
    pCD("Set CDAudio Door Open", NULL, 0, NULL);
}

void FecharCD()
{
    pCD("Set CDAudio Door Closed", NULL, 0, NULL);
}

int menu()
{
    int choice;

    cout << "você deseja abrir ou fechar o drive de cd?\n";

    cout << "[1]Abrir\n";

    cout << "[2]Fechar\n";

    cin >> choice;

    switch (choice)
    {

    case 1:

        AbrirCD();

        break;

    case 2:

        FecharCD();

        break;

    default:

        cout << "opcao inexistente\n";

        Sleep(250);

        exit(0);
    }

    exit(0);

    return 0;
}

int main()
{
    HINSTANCE dll = LoadLibrary("winmm.dll");

    if (!dll)

        return 1;

    pCD = (CDROM)GetProcAddress(dll, "mciSendStringA");

    if (!pCD)

        return 1;

    menu();

    return 0;
}
