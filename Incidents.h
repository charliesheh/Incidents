//Implementation file for Incidents class
//IDE: Visual Studio 2017
#ifndef _INCIDENTS
#define _INCIDENTS

#include <string>
#include <iomanip>
#include <iostream>

using std::string;
using std::ostream;

class Incidents
{
private:
	string ID;				// unique key, id of shooting case
	string state;		// location of shooting
	string date;			// date of shooting
	int fatalities;			// number of fataliities due to shooting
	string race;			// race of the shooter
	string gender;			// gender of the shooter

public:
	// constructor definitions
	Incidents();
	Incidents(string sID, string sState, string sDate, int sFatalities, string sRace, string sGender);

	// setters to set respective data properties
	void setID(string sID);
	void setState(string sState);
	void setDate(string sDate);
	void setFatalities(int sFatalities);
	void setRace(string sRace);
	void setGender(string sGender);

	// getters to get respective data properties
	string getID() const;
	string getState() const;
	string getDate() const;
	int getFatalities() const;
	string getRace() const;
	string getGender() const;


	// overloading function

	
	//bool operator == (const Incidents& toyData);
	//bool operator < (const Shootings& toyData);
	bool operator > (const Incidents &inc);
	bool operator < (const Incidents &inc);
	bool operator == (const Incidents &inc);

	//friend ostream& operator << (ostream& os, const Incidents& toyData);

	//friend ostream &operator << (ostream &strem, Mountain &obj);

	
};

#endif
