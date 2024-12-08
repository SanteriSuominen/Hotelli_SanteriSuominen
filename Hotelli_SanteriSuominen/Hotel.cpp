#include "Hotel.h"

// Rakentaja purkaja ja initiaatio
Hotel::Hotel()
{
	this->init();
}

Hotel::~Hotel()
{
}

void Hotel::init() // Tänne kaikki mitä haluaa kutsua ennen ohjelman käyttöä
{
	this->generateRooms();
	this->reservations.push_back(Hotel::Reservation()); // luomme tyhjän varauksen jolla alustamme vectorin
	this->loadReservations();
}

void Hotel::process()	//	Main logiikka eli käyttö logiikka
{
	std::string tempCommand = "";
	this->printHeader();
	while (tempCommand != "exit")
	{	
		// kutsuu komentoa vastaavan metodin
		std::cout << "\nCommand: ";
		tempCommand = getUserInput("Command: ");
		std::cout << "\n";
		if (tempCommand == "help")
			this->help();

		if (tempCommand == "add")
			this->addReservation();

		if (tempCommand == "find")
			this->findReservation();

		if (tempCommand == "printAll")
			this->printAllReservations();

		if (tempCommand == "printRooms")
			this->printRooms();

		if (tempCommand == "clear")
		{
			system("cls");
			this->printHeader();
		}
	}
}

// Käyttöliittymän funktiot

void Hotel::addReservation()
{
	std::cout << "The name of the person booking the room: ";
	std::string tempName = getUserInput(); // syötteen vastaanotto ja tarkistus
	

	int tempNights = 0;
	while(tempNights > 30 || tempNights <= 0) // voit olla 30 yötä maksimissaan kerralla
	{
		std::cout << "How many nights were you planning on staying: ";
		
		std::cin >> tempNights;
		while (true)						// syötteen tarkistus
		{
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				std::cout << "invalid Input, try again: ";
				std::cin >> tempNights;
			}
			else
				break;
		}
	}

	int tempRoomNum = 0;
	while (tempRoomNum > 300 || tempRoomNum <= 0) // tempRoomNum on nolla joten se aloitta while loopin
	{
		std::cout << "\nrooms 1-150 are single rooms and rest are double rooms\n";
		std::cout << "Now you can choose a room (1-300): ";

		std::cin >> tempRoomNum;
		while (true)
		{
			if (std::cin.fail())
			{
				std::cin.clear();				// syötteen tarkistus
				std::cin.ignore(INT_MAX, '\n');
				std::cout << "\ninvalid Input, try again: ";
				std::cin >> tempRoomNum;
			}
			else
				break;
		}
		if (tempRoomNum > 300 || tempRoomNum <= 0)	// huoneen parametrit, huoneita on 300 et voi valita yli 300 tai alle 0
			continue;

		
		if (this->rooms[tempRoomNum - 1].isReserved)	// jos huone on varattu
		{
			std::cout << "\nSorry, your selected room is taken.\n";
			tempRoomNum = 0;
			continue;
		}
		
	}
	float priceMulti = 0.0f;							
	std::random_device random;							
	std::default_random_engine rSeed(random());			
	std::uniform_int_distribution<int> rIntPrice(0, 2);		// antaa arvon 0, 1 tai 2 "satunnaisesti" joka määrää alennus prosentin suuruuden

	priceMulti = (float)rIntPrice(rSeed)/10;				// lasketaan satunnaisen arvon perusteella alennus kerroin
	float tempPrice = 100.0f;
	if (tempRoomNum > 150)
		tempPrice += 50.0f;			//muutetaan alennus desimaaliksi, päätetään onko hinta 100 vai 150 huoneen indexin perusteella

	tempPrice -= tempPrice * priceMulti;	//kerrotaan hinta alennus kerotimella eli 0, 0.1 tai 0.2 / 0 %, 10 % ja 20 %
	
	int tempIdentifier = 0;
																	// luodaan satunnainen arvo 10000 ja 99999 väliltä jos arvottu luku on jo käytössä niin se pyörii niin kauan että ei ole
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
	std::string fileName = std::to_string(tempIdentifier) + ".txt";				// Annetaan tiedostonimeksi varauksen uniikki identifier joka muutetaan intistä stringiksi valmiilla to_string funktiolla
	std::ofstream file(fileName);
	
	if (file.is_open())		// avataan tiedosto ja syötetään sinne varauksen tiedot jokainen omalle rivilleen sitten suljetaan tiedosto
	{
		file << tempName << "\n";
		file << tempRoomNum << "\n";
		file << tempNights << "\n";
		file << tempPrice << "\n";
		file << tempIdentifier << "\n";
		file.close();
	}

	this->reservations.push_back(Hotel::Reservation(tempName, tempIdentifier, tempNights, tempRoomNum, tempPrice)); // lisätään varaustiedot Reservation tietotyyppi vectoriin
	this->rooms[tempRoomNum-1].isReserved = true;	// merkataan varauksessa varattu huone varatuksi
	std::cout << "\nNew reservation: \n";
	this->printReservation(this->reservations.size()-1);	// printtaa vielä näkyviin tehdyn varauksen tiedot
	std::cout << "\nYour reservation is successful, with reservation number: " << tempIdentifier << std::endl;
	std::cout << "Thank you we are waiting on your visit :)" << std::endl;

	std::cout << "\nIf you made this reservation on mistake you can cancel it using \"find\" command!" << std::endl;
}

void Hotel::findReservation()		// etsitään tehty varaus ja jatko toimenpiteet
{
	std::cout << "Search reservation with name, room, id (name/room/id/cancel)" << std::endl; // ksysytään komentoa neljästä eri vaihtoehdosta
	std::cout << "Find: ";
	std::string input = getUserInput();
	std::cout << "\n";
	
	std::string tempName = "null_no_search";	// varmistutaan siitä että jos nimeä ei käytetä siksi tämä alku arvo
	int tempRoomNum = -1;
	int tempIdNum = -1;

	if (input == "cancel")
		return;
	if (input == "name" || input == "room" || input == "id") // varmistutaan millä halutaan löytää varaus
	{
		if (input == "name")
		{
			std::cout << "Give name of the reservation" << std::endl;
			std::cout << "Input: ";
			tempName = getUserInput();
		}

		if (input == "room")
		{
			std::cout << "Give room number for the reservation" << std::endl;
			std::cout << "Input: ";

			std::cin >> tempRoomNum;
			while (true)
			{
				if (std::cin.fail())	// syötteen tarkistus
				{
					std::cin.clear();
					std::cin.ignore(INT_MAX, '\n');
					std::cout << "invalid Input, try again: ";
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
				if (std::cin.fail())		// syötteen tarkistus
				{
					std::cin.clear();
					std::cin.ignore(INT_MAX, '\n');
					std::cout << "invalid Input, try again: ";
					std::cin >> tempIdNum;
				}
				else
					break;
			}
		}
		bool found = false;
		for (int i = 0; i < this->reservations.size(); i++)
		{
			if (tempName == this->reservations[i].name || tempRoomNum == this->reservations[i].roomNumber || tempIdNum == this->reservations[i].identifier)
			{
				std::cout << "\nSReservation found.\n" << std::endl;
				this->printReservation(i);
				found = true;
				if (tempName == "null_no_search") // Huom käyttäjä voi löytää varauksen nimellä mutta ei poistaa sitä sillä nimellä voi olla useampi varaus jolloin ohjelma kehottaa hakemaan identifierilla tai huone numerolla
				{
					std::cout << "\nWould you like to remove this reservation (y/n)" << std::endl; // haluakko poistaa varauksen
					std::string temp = "";

					while (temp != "y" && temp != "n")
					{
						temp = getUserInput();
					}

					if (temp == "y")
						this->removeReservation(i, this->reservations[i].identifier);	// jos kyllä kutsutaan removeReservation funktio ja anna sille varauksen index ja identifier

					if (temp == "n")
						return;

					return;
				}

				else
				{
					std::cout << "\nIf you want to remove this reservation please find with id or room number\n\n";
				}
			}
		}
		if (!found)
			std::cout << "No reservation found\n";
	}

	else
	{
		std::cout << "\n\"find\" was interrupted due to invalid command.\nWrite \"find\" if you want to return.\n";
	}
}

void Hotel::removeReservation(const int index, const int identifier)	// poistaa varauksen vectorista ja txt tiedoston ja muuttaa huoneen taas avoimeksi
{	
	this->rooms[this->reservations[index].roomNumber - 1].isReserved = false;
	this->reservations.erase(this->reservations.begin() + index);

	std::string fileName = std::to_string(identifier) + ".txt";
	if (std::filesystem::exists(fileName))	// huom jos aiheuttaa ongelmia tarvitset verison c++ 17 standardin tai uudemman "Solutin Explorer --> properties --> language --> c++ language standard --> valitse c++ 17 standard"
	{										// itsellä oli vakiona vanhempi versio
		std::filesystem::remove(fileName);
		std::cout << "Reservation " << identifier << " removed successfully.\n";
	}
	return;
}

void Hotel::printAllReservations() // printtaa jokaisen reservaation ruudulle (lisämetodi havainnolistamaan kuinka kokonaisuus toimii) 
{
	std::cout << "Here are all reservations." << std::endl;
	for (int i = 0; i < this->reservations.size(); i++)
	{
		std::cout << "\n Reservation index: " << i << "\n\n";
		this->printReservation(i);
	}
}

void Hotel::printReservation(int reservationIndex)	// vastaan ottaa reservaatio indexin ja etsii tietyn reservaation vectorista ja printtaa varauksen kaikki tideot
{
	std::cout << "-Name: "<< this->reservations[reservationIndex].name << std::endl;
	std::cout << "-Room: " << this->reservations[reservationIndex].roomNumber << std::endl;
	std::cout << "-Nights: " << this->reservations[reservationIndex].numOfNights << std::endl;
	std::cout << "-Price: " << this->reservations[reservationIndex].price << std::endl;
	std::cout << "-id: " << this->reservations[reservationIndex].identifier << std::endl;
}

std::string Hotel::getUserInput(std::string message)  // luotu korvaamaan getlinen sillä getline tuotti ongelmia funktioiden siirtymisen välillä
{
	std::string temp = "";
	std::cin >> temp;
	while (true)
	{
		if (std::cin.fail())	// jos syötteen lukeminen epäonnistui
		{
			std::cin.clear();	// tyhjennetään virhetila
			std::cin.ignore(INT_MAX, '\n');	// tyhjennetään syöte puskuri
			std::cout << message << std::endl;	// tulostetaan virhe viesti
			std::cin >> temp;	//yritetään uudelleen
		}
		else
			break;
	}
	return temp;
}

void Hotel::printRooms()	// printtaa joka huoneen järjestyksessä 1-300 ja niihin liityvät tiedot onko vapaana, hinta ja onko single vai double
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

void Hotel::printHeader() // printtaa alku headerin, lähtökohtaisesti aina kun käyttäjä päätää tyhjentää konsoli clear komennolla
{
	std::cout << "-----------------------------------------\n";
	std::cout << "Hotel Service Program by Santeri Suominen\n";
	std::cout << "-----------------------------------------\n";
	std::cout << "Write \"help\" for info\n";
}

void Hotel::help() // help tulostaa avustus taulukon käyttäjälle josta hän näkee kaikki commandit
{
	std::cout << "Possible commands are marked as (command/command/command)\n\n";
	std::cout << "\"help\"		 Gives info about the program \n";
	std::cout << "\"add\"		 Add a reservation \n";
	std::cout << "\"find\"		 Find and possibly remove reservation \n";
	std::cout << "\"printAll\"	 Prints all excisting reservations\n";
	std::cout << "\"printRooms\"	 Prints all rooms and their states\n";
	std::cout << "\"clear\"		 Clears the console view\n";
	std::cout << "\"exit\"		 Exit Program\n";

}

void Hotel::loadReservations()	// käy läpi kaikki mahdolliset kansio nimet eli 10000-99999 ja jos on olemassa vastaava tiedosto ottaa se tiedot rivi riviltä ja luo tiedoilla reservaation vectoriin
{
	std::string tempName = "";
	int tempIdentifier = 0, tempNights = 0, tempRoomNum = 1;
	float tempPrice = 0;
	for (int i = 10000; i < 100000; i++)
	{
		std::string fileName = std::to_string(i) + ".txt";
		if (std::filesystem::exists(fileName))
		{
			std::ifstream file(fileName);
			std::string line1, line2, line3, line4, line5;


			// lukee tiedot 
			if (std::getline(file, line1)) {
				tempName = line1;
			}
			if (std::getline(file, line2)) {
				tempRoomNum = std::stoi(line2);
			}
			if (std::getline(file, line3)) {
				tempNights = std::stoi(line3);
			}
			if (std::getline(file, line4)) {
				tempPrice = std::stof(line4);
			}
			if (std::getline(file, line5)) {
				tempIdentifier = std::stoi(line5);
			}

			// lisää reservaatio listaan, ja merkkaa huoneet varatuksi
			this->reservations.push_back(Hotel::Reservation(tempName, tempIdentifier, tempNights, tempRoomNum, tempPrice));
			this->rooms[tempRoomNum - 1].isReserved = true;
			file.close();
		}
	}
}

void Hotel::generateRooms()	// luodaan huoneet puolet ja puolet singlejä ja doubleja simppelillä booleanilla
{
	// Luodaan 300 huonetta joista 150 ensimmäistä on yhden hengen ja loput kahden hengen huoneita.
	for (int i = 0; i < 300; i++)
	{
		this->rooms[i].roomNumber = i + 1;
		if (i >= 149)
			this->rooms[i].isSingle = false;
	}
}

Hotel::Reservation::Reservation() // Tyhjä rakentaja
{
}

Hotel::Reservation::Reservation(std::string name, int identifier, int numOfNights, int roomNumber, float price) // Vakio rakentaja
{
	this->name = name;
	this->identifier = identifier;
	this->numOfNights = numOfNights;
	this->roomNumber = roomNumber;
	this->price = price;
}
