#include "Hotel.h"

// Rakentaja purkaja ja initiaatio
Hotel::Hotel()
{
	this->init();
}

Hotel::~Hotel()
{
}

void Hotel::init()
{
	this->generateRooms();
	this->loadReservations();
	this->reservations.push_back(Hotel::Reservation());
}


// Käyttöliittymän funktiot

void Hotel::addReservation()
{
	std::cout << "The name of the person booking the room: ";
	std::string tempName = "";
	std::getline(std::cin,tempName);

	int tempNights = 0;
	while(tempNights > 30 || tempNights <= 0) // voit olla 30 yötä maksimissaan kerralla
	{
		std::cout << "How many nights were you planning on staying: ";
		
		std::cin >> tempNights;
		while (true) 
		{
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				std::cin >> tempNights;
			}
			else
				break;
		}
	}

	int tempRoomNum = 0;
	while (tempRoomNum > 300 || tempRoomNum <= 0) // huoneen parametrit
	{
		std::cout << "rooms 1-150 are single rooms and rest are double rooms\n";
		std::cout << "Now you can choose a room (1-300): ";

		std::cin >> tempRoomNum;
		while (true)
		{
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				std::cin >> tempRoomNum;
			}
			else
				break;
		}
		if (tempRoomNum > 300 || tempRoomNum <= 0)
			continue;

		if (this->rooms[tempRoomNum - 1].isReserved)
		{
			std::cout << "Sorry, your selected room is taken.\n";
			continue;
		}
	}
	float priceMulti = 0.0f;
	std::random_device random;
	std::default_random_engine rSeed(random());
	std::uniform_int_distribution<int> rIntPrice(0, 2);

	priceMulti = (float)rIntPrice(rSeed)/10;
	float tempPrice = 100.0f;
	if (tempRoomNum > 150)
		tempPrice += 50.0f;

	tempPrice -= tempPrice * priceMulti;
	
	int tempIdentifier = 0;
	
	for (int i = 0; i < this->reservations.size(); i++)
	{
		if (tempIdentifier == this->reservations[i].identifier || tempIdentifier <= 0)
		{
			std::random_device randomId;
			std::default_random_engine rSeedId(randomId());
			std::uniform_int_distribution<int> rIntId(10000, 99999);
			tempIdentifier = rIntId(rSeedId);
			i = 0;
		}	
	}
	this->reservations.push_back(Hotel::Reservation(tempName, tempIdentifier, tempNights, tempRoomNum, tempPrice));
	std::cout << "Your reservation is successful, with reservation number: " << tempIdentifier << std::endl;
	std::cout << "Thank you we are waiting on your visit :)" << std::endl;
}

void Hotel::findReservation()
{
	std::cout << "Search reservation with name, room, id (name/room/id/exit)" << std::endl;
	std::cout << "Command: ";
	std::string input = "";
	std::getline(std::cin, input);
	
	while (true)
	{
		std::string tempName = "";
		int tempRoomNum = -1;
		int tempIdNum = -1;
		
		if (input == "exit")
			return;
		if (input == "name" || input == "room" || input == "id")
		{
			if (input == "name")
			{
				std::cout << "Give name of the reservation" << std::endl;
				std::cout << "Input: ";
				std::getline(std::cin, tempName);
			}

			if (input == "room")
			{
				std::cout << "Give room number for the reservation" << std::endl;
				std::cout << "Input: ";
				
				std::cin >> tempRoomNum;
				while (true)
				{
					if (std::cin.fail())
					{
						std::cin.clear();
						std::cin.ignore(INT_MAX, '\n');
						std::cin >> tempRoomNum;
					}
					else
						break;
				}
			}

			if (input == "id")
			{
				std::cout << "Give id number for the reservation" << std::endl;
				std::cout << "Input: ";

				std::cin >> tempIdNum;
				while (true)
				{
					if (std::cin.fail())
					{
						std::cin.clear();
						std::cin.ignore(INT_MAX, '\n');
						std::cin >> tempIdNum;
					}
					else
						break;
				}
			}

			for (int i = 0; i < this->reservations.size(); i++)
			{
				if (tempName == this->reservations[i].name || tempRoomNum == this->reservations[i].roomNumber || tempIdNum == this->reservations[i].identifier)
				{
					this->printReservation(i);

					std::cout << "Would you like to remove this reservation (y/n)";
					std::string temp;
					std::getline(std::cin, temp);

					while (temp != "y" || temp != "n")
					{
						std::cout << "Try again: ";
						std::getline(std::cin, temp);
					}

					if (temp == "y")
						this->removeReservation(i);

					if (temp == "n")
						return;

					return;
				}
			}
		}
	}
}

void Hotel::removeReservation(const int index)
{
}

void Hotel::printAllReservations()
{
}

void Hotel::printReservation(int reservationIndex)
{
	std::cout << "Here is your reservation." << std::endl;
	std::cout << this->reservations[reservationIndex].name << std::endl;
	std::cout << this->reservations[reservationIndex].roomNumber << std::endl;
	std::cout << this->reservations[reservationIndex].numOfNights << std::endl;
	std::cout << this->reservations[reservationIndex].price << std::endl;
	std::cout << this->reservations[reservationIndex].identifier << std::endl;
}

void Hotel::printRooms()
{
	for (int i = 0; i < 300; i++)
	{
		if (this->rooms[i].isSingle && !this->rooms[i].isReserved)
		{
			std::cout << "  Room: " << i + 1 << " Type: single, price: 100EUR/night, CURRENTLY OPEN\n" << std::endl;
		}
		else if (this->rooms[i].isSingle && this->rooms[i].isReserved)
		{
			std::cout << "  Room: " << i + 1 << " Type: single, price: 100EUR/night, CURRENTLY RESERVED\n" << std::endl;
		}
		else if (!this->rooms[i].isSingle && !this->rooms[i].isReserved)
		{
			std::cout << "  Room: " << i + 1 << " Type: double, price: 150EUR/night, CURRENTLY OPEN\n" << std::endl;
		}
		else
		{
			std::cout << "  Room: " << i + 1 << " Type: double, price: 150EUR/night, CURRENTLY RESERVED\n" << std::endl;
		}
	}
}

//Sisäinen toiminta

void Hotel::printHeader()
{
}

void Hotel::loadReservations()
{
}

void Hotel::generateRooms()
{
	// Luodaan 300 huonetta joista 150 ensimmäistä on yhden hengen ja loput kahden hengen huoneita.
	for (int i = 0; i < 300; i++)
	{
		this->rooms[i].roomNumber = i + 1;
		if (i >= 149)
			this->rooms[i].isSingle = false;
	}
}

Hotel::Reservation::Reservation()
{
}

Hotel::Reservation::Reservation(std::string name, int identifier, int numOfNights, int roomNumber, float price)
{
	this->name = name;
	this->identifier = identifier;
	this->numOfNights = numOfNights;
	this->roomNumber = roomNumber;
	this->price = price;
}
