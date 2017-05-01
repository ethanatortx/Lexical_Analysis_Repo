#include <iostream>
#include <cstdlib>
#include "btree.h"
#include "csv\csv.h"

int main()
{
	io::csv reader();
	reader.open_file("USAirportCodes.csv");

	return 0;
}