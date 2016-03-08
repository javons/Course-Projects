/**********************************************************************
 *
 * Project 4: Temperature Processing
 *
 * This program will read a file of temperature and hour, find out 
 * errors, sort them in order, calculate the mean temperature, find
 * out the median temperature and print out the result. 
 *
 * Author: Tianmao Jiang
 * Date: August 17 2015  
 *
 **********************************************************************/

#include <bjarne/std_lib_facilities.h>

/*
 * the Reading class represents a temperature reading
 */
struct Reading {
    int hour;
    double temperature;
    Reading(int h, double t): hour(h), temperature(t) { }
};

// how we sort the temperatures by value and the time
bool operator<(const Reading &r1, const Reading& r2);

/*
 * function declarations
 */
 
// establish a new form of hour and temperature
ostream& operator<<(ostream& ost, const Reading &r);

// ask a file name to open, generate a new list of fahrenheit
// temperature after checking and adjusting
vector<Reading> get_temps();

// check if contents are legitimate, give out error messages and 
// use fahrenheit for all temperatures
double check_adjust_temp(double temperature, char scale);

// convert celsius to fahrenheit
double c_to_f(double temperature);

// solve the mean of temps
double mean(vector<Reading> temps);
 
// find the median of temps
double median(vector<Reading> temps);

// print out the list of sorted temperatures, the mean and the median
void print_results(const vector<Reading>& temps, double mean_temp, 
		   double median_temp);

int main()
    try {
	vector<Reading> temps = get_temps(); 
	if (temps.size() == 0) error("no temperatures given!");
	double mean_temp = mean(temps);
	sort(temps);
	double median_temp = median(temps);
	print_results(temps, mean_temp, median_temp);
    }
// give out error messages
    catch (exception& e) { 
	cerr << "error: " << e.what() << '\n'; 
	return 1;
    }
    catch (...) {
	cerr << "Oops: unknown exception!\n"; 
	return 2;
    }

/*
 * function definitions
 */

bool operator<(const Reading &r1, const Reading& r2) 
{
    if (r1.temperature < r2.temperature)
	return true;
    else if (r1.temperature > r2.temperature)
	return false;
// if temperature same, we compare time, the earlier comes the first
    else{
	if (r1.hour < r2.hour)
	    return true;
	else
	    return false;
    }
}

ostream& operator<<(ostream& ost, const Reading &r)
{
// the layout of the contents
    ost << setw(2) << r.hour << ":" << setw(8) << fixed
	<< setprecision(2) << r.temperature << " F\n"; 
    return ost; 
}

vector<Reading> get_temps()
{
    vector<Reading> temps;
    string iname;
    cout << "Please enter input file name:";
    cin >> iname;
    ifstream ist(iname.c_str());
    if (!ist) error("can't open input file ", iname);
    int hour;
    double temperature;
    char scale;
    
// continue reading, convert every celsius temp to fahrenheit, give
// out error messages if necessary and store every pair of hour and
// temperature read into a new reading vector and return it
    
    while (ist >> hour >> temperature >> scale){   
	double fahrenheit_temp;
	fahrenheit_temp = check_adjust_temp(temperature, scale);
	temps.push_back(Reading(hour, fahrenheit_temp));
    }
    return temps;
}

double check_adjust_temp(double temperature, char scale)
{
    if (scale != 'C' && scale != 'c' && scale != 'F' && scale != 'f')
	error("illegal temperature scale");
// temperature of absolute zero is: -273.15 degrees in celsius and
// -459.67 degrees in fahrenheit
    else if (scale == 'F' || scale == 'f' && temperature > -459.67)
	return temperature;
    else if (scale == 'C' || scale == 'c' && temperature > -273.15)
	return c_to_f(temperature);
    else
	error("temperature too cold");  	
}
double c_to_f(double temperature)
{
    return 1.8 * temperature + 32;
}

double mean(vector<Reading> temps)
{
    double total = 0;
    for (int i = 0; i < temps.size(); ++i){
	total += temps[i].temperature;
    }                             // add up to total and divide it by 
    return total/temps.size();    // size number to get the mean
}

double median(vector<Reading> temps)
{
    int size = temps.size();
    if (size % 2 != 0)
	return temps[size/2].temperature;
    else
	return 0.5*(temps[size/2].temperature +
		    temps[size/2 - 1].temperature);
}

void print_results(const vector<Reading>& temps, double mean_temp,
		   double median_temp)
{
    cout << "\nThe sorted temperatures are:\n";
// print out every pair of hour and temperature read before
    for (int i = 0; i < temps.size(); ++i)
	cout << temps[i];
    cout << "\nThe mean temperature is " << mean_temp << "F.\n"
	 << "The median temperature is " << median_temp << "F.\n";
}  
