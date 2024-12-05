#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>

class Hotel  // hotellin luokka
{
private:
	struct Room // huoneen tietotyyppi
	{
		int roomNumber = 0; // huoneen numero
		bool isSingle = true;	// kahden vai yhden hengen huone
		bool isReserved = false; // onko varattu
	};
	
	struct Reservation
	{
		std::string name = "null"; // varaajan nimi; 
		int identifier = 0; // varausnumero
		int numOfNights = 0; // montako yötä
		int roomNumber = 0; // varatun huoneen numero
		float price = 0; // hinta
		Reservation();
		Reservation(std::string name, int identifier, int numOfNights, int roomNumber, float price);
	};

	void printHeader();
	void loadReservations();
	void generateRooms();
	void printReservation(const int index);
	Room rooms[300]; // array huoneista joita on 300
	std::vector<Reservation> reservations{}; // lista varauksista jonka kokonaismäärää ei tiedetä siksi vector
public:
	Hotel();
	~Hotel();

	void init();
	void addReservation();
	void findReservation();
	void removeReservation(const int index);
	void printAllReservations();
	void printRooms();
};