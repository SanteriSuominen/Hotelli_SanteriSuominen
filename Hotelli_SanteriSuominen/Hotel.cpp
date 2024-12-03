#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Käyttäjät
{
    string email;
    string password;
    string fullName;
};

// Funktio käyttäjän luomiseksi
void LuoKäyttäjä();

int main()
{
    setlocale(LC_ALL, "fi-FI");
    string input;

    cout << "TERVETULOA HOTELLI VARAUS OHJELMAAN\n-----------------------------------\n";

    cout << "Onko sinulla jo olemassa oleva käyttäjä? (e/k): ";
    cin >> input;

    if (input == "k")
    {
        // Login logiikka (tässä ei käsitellä)
    }
    else if (input == "e")
    {
        system("cls"); // Puhdistaa ruudun
        LuoKäyttäjä();
    }

    return 0;
}

// Funktio uuden käyttäjän luomiseen
void LuoKäyttäjä()
{
    Käyttäjät uusiKäyttäjä;

    cout << "Tarvitet käyttäjän jatkaaksesi palvelussamme! Luodaan sellainen nyt!\n"
        << "-------------------------------------------------------\n"
        << "Voit aina pysäyttää Käyttäjän luonnin ja lopettaa ohjelman kirjoittamalla 'stop' käyttäjän luomisen aikana\n\n";

    // Kokonimi
    cin.ignore(); // Tyhjentää puskuriin jääneen rivinvaihdon
    cout << "Anna kokonimesi: ";
    getline(cin, uusiKäyttäjä.fullName);

    // Sähköposti
    cout << "Anna sähköpostisi: ";
    getline(cin, uusiKäyttäjä.email);

    // Tarkistetaan, onko käyttäjällä jo tili
    ifstream tiedosto(uusiKäyttäjä.email + ".txt"); // Yritetään avata tiedosto
    if (tiedosto.is_open())
    {
        cout << "Käyttäjä sähköpostilla " << uusiKäyttäjä.email << " on jo olemassa.\n";
        tiedosto.close();
    }

    // Salasana
    cout << "Luo käyttäjälle salasana: ";
    getline(cin, uusiKäyttäjä.password);

    // Tiedoston luominen ja tallentaminen
    ofstream tiedostoTallennus(uusiKäyttäjä.email + ".txt"); // Tiedoston nimi on sähköposti
    if (tiedostoTallennus.is_open())
    {
        tiedostoTallennus << "Kokonimi: " << uusiKäyttäjä.fullName << endl;
        tiedostoTallennus << "Sähköposti: " << uusiKäyttäjä.email << endl;
        tiedostoTallennus << "Salasana: " << uusiKäyttäjä.password << endl;
        tiedostoTallennus.close();

        cout << "\nLuotu käyttäjä:\n";
        cout << "Nimi: " << uusiKäyttäjä.fullName << endl;
        cout << "Sähköposti: " << uusiKäyttäjä.email << endl;
        cout << "Salasana: " << uusiKäyttäjä.password << endl;
        cout << "Käyttäjätiedot on tallennettu tiedostoon: " << uusiKäyttäjä.email + ".txt" << endl;
    }
    else
    {
        cout << "Virhe tiedoston luomisessa!" << endl;
    }
}
