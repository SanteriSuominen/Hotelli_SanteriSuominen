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
}

void Hotel::removeReservation()
{
}

void Hotel::printReservation()
{
}

void Hotel::printRooms()
{
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
