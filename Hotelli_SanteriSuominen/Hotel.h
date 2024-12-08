#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <filesystem>// Mahdollistaa filesystem::exists(tiedoston nimi) k�yt�n jolla tarkastetaan onko tiedosto olemassa

class Hotel			// hotellin luokka
{
private:
	struct Room						// huoneen tietotyyppi
	{
		int roomNumber = 0;			// huoneen numero
		bool isSingle = true;		// kahden vai yhden hengen huone
		bool isReserved = false;	// onko varattu
	};
	
	struct Reservation																					// varausten tietotyyppi
	{
		std::string name = "null";																		// varaajan nimi; 
		int identifier = 0;																				// varausnumero
		int numOfNights = 0;																			// montako y�t�
		int roomNumber = 0;																				// varatun huoneen numero
		float price = 0;																				// hinta

		Reservation();																					// varauksen tyhj� rakentaja
		Reservation(std::string name, int identifier, int numOfNights, int roomNumber, float price);	// varauksen varsinainen rakntaja
	};

	void printHeader();
	void loadReservations();										// etsii .txt tiedostoja varausnumeron(id) pohjalta ja lis�� niit� reservaatio vectoriin
	void generateRooms();
	void printReservation(const int index);
	std::string getUserInput(std::string message = "Try again: ");	// getlinen korvaava funktio
	Room rooms[300];												// array huoneista joita on 300 (array koska m��r� ei muutu)
	std::vector<Reservation> reservations{};						// lista varauksista joilla ei ole tasaista vakio arvoa siksi vector
public:
	Hotel();														//rakentaja
	~Hotel();														//purkaja
	
	void init();													//	kutsutaan constructorissa suorittaa kaiken tarvittavan ennen ohjelman k�ytt��
	void process();													//	Hotellin suorittaminen, kutsutaan mainissa
	void help();													//	printtaa avustuksia k�ytt�j�lle menussa
	void addReservation();											//	lis�� varaus
	void findReservation();											//	etsi olemassa oleva varaus
	void removeReservation(const int index, const int identifier);	//	poista varaus, kutsutaan haun yhteydess�
	void printAllReservations();									// tulostaa varaukset
	void printRooms();												// tulostaa huoneet
};