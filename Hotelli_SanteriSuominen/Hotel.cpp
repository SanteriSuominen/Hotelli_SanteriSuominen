#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct K�ytt�j�t
{
    string email;
    string password;
    string fullName;
};

// Funktio k�ytt�j�n luomiseksi
void LuoK�ytt�j�();

int main()
{
    setlocale(LC_ALL, "fi-FI");
    string input;

    cout << "TERVETULOA HOTELLI VARAUS OHJELMAAN\n-----------------------------------\n";

    cout << "Onko sinulla jo olemassa oleva k�ytt�j�? (e/k): ";
    cin >> input;

    if (input == "k")
    {
        // Login logiikka (t�ss� ei k�sitell�)
    }
    else if (input == "e")
    {
        system("cls"); // Puhdistaa ruudun
        LuoK�ytt�j�();
    }

    return 0;
}

// Funktio uuden k�ytt�j�n luomiseen
void LuoK�ytt�j�()
{
    K�ytt�j�t uusiK�ytt�j�;

    cout << "Tarvitet k�ytt�j�n jatkaaksesi palvelussamme! Luodaan sellainen nyt!\n"
        << "-------------------------------------------------------\n"
        << "Voit aina pys�ytt�� K�ytt�j�n luonnin ja lopettaa ohjelman kirjoittamalla 'stop' k�ytt�j�n luomisen aikana\n\n";

    // Kokonimi
    cin.ignore(); // Tyhjent�� puskuriin j��neen rivinvaihdon
    cout << "Anna kokonimesi: ";
    getline(cin, uusiK�ytt�j�.fullName);

    // S�hk�posti
    cout << "Anna s�hk�postisi: ";
    getline(cin, uusiK�ytt�j�.email);

    // Tarkistetaan, onko k�ytt�j�ll� jo tili
    ifstream tiedosto(uusiK�ytt�j�.email + ".txt"); // Yritet��n avata tiedosto
    if (tiedosto.is_open())
    {
        cout << "K�ytt�j� s�hk�postilla " << uusiK�ytt�j�.email << " on jo olemassa.\n";
        tiedosto.close();
    }

    // Salasana
    cout << "Luo k�ytt�j�lle salasana: ";
    getline(cin, uusiK�ytt�j�.password);

    // Tiedoston luominen ja tallentaminen
    ofstream tiedostoTallennus(uusiK�ytt�j�.email + ".txt"); // Tiedoston nimi on s�hk�posti
    if (tiedostoTallennus.is_open())
    {
        tiedostoTallennus << "Kokonimi: " << uusiK�ytt�j�.fullName << endl;
        tiedostoTallennus << "S�hk�posti: " << uusiK�ytt�j�.email << endl;
        tiedostoTallennus << "Salasana: " << uusiK�ytt�j�.password << endl;
        tiedostoTallennus.close();

        cout << "\nLuotu k�ytt�j�:\n";
        cout << "Nimi: " << uusiK�ytt�j�.fullName << endl;
        cout << "S�hk�posti: " << uusiK�ytt�j�.email << endl;
        cout << "Salasana: " << uusiK�ytt�j�.password << endl;
        cout << "K�ytt�j�tiedot on tallennettu tiedostoon: " << uusiK�ytt�j�.email + ".txt" << endl;
    }
    else
    {
        cout << "Virhe tiedoston luomisessa!" << endl;
    }
}
