#include "Address.h"

using namespace std;

Address::Address() {}

Address::Address(const Address &address)
{
	county = address.county;
	locality = address.locality;
	street = address.street;
	number = address.number;
	block = address.block;
	apartment = address.apartment;
}

Address::Address(const string &jud, const string &loc, const string &str, int nr, const string &bl, int ap)
{
	county = jud;
	locality = loc;
	street = str;
	number = nr;
	block = bl;
	apartment = ap;
}

const Address &Address::operator=(const Address &adr)
{
	county = adr.county;
	locality = adr.locality;
	street = adr.street;
	number = adr.number;
	block = adr.block;
	apartment = adr.apartment;
	return *this;
}

void Address::setStrada(const string &str)
{
	street = str;
}

void Address::setNumber(int nr)
{
	number = nr;
}

void Address::setBlock(const string &bl)
{
	block = bl;
}

void Address::setApartment(int ap)
{
	apartment = ap;
}

void Address::setCounty(const string &jud)
{
	county = jud;
}

void Address::setLocality(const string &loc)
{
	locality = loc;
}

string &Address::getStreet()
{
	return street;
}

int Address::getNumber()
{
	return number;
}
string &Address::getBlock()
{
	return block;
}

int Address::getApartment()
{
	return apartment;
}

string &Address::getCounty()
{
	return county;
}

string &Address::getLocality()
{
	return locality;
}

bool Address::operator==(const Address &address)
{
	if (county == address.county
		&& locality == address.locality
		&& street == address.street
		&& number == address.number
		&& block == address.block
		&& apartment == address.apartment)
			return true;
	return false;
}

bool Address::operator!=(const Address &address)
{
	return !(*this == address);
}

ostream &operator<<(ostream &os, const Address &a)
{
	os << a.county  << " "
	   << a.locality << " "
	   << a.street << " "
	   << a.number << " "
	   << a.block << " "
	   << a.apartment;
	return os;
}

json Address::toJSON()
{
	return json(*this);
}