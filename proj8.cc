/**********************************************************************
 *
 * Project 8: Timing Has Come Today
 *
 * This program will determine the time it takes to fill and sort three 
 * different containers with a given number of randomly-generated data
 * values.
 *
 * Author: Tianmao Jiang
 * Date: August 27 2015
 *
 **********************************************************************/

#include <std_lib_facilities.h>
#include <chrono>
#include <numeric>
#include <set>

using namespace std;
using namespace std::chrono;

using Inserter = void(const vector<double>&);

// insert vector's data into a new list and sort them as well as double
// check if sorted
void insert_list(const vector<double>& data);
// insert vector's data into a new set and double check if sorted
void insert_set(const vector<double>& data);
// insert vector's data into a new vector and sort then double check
// if it is sorted
void insert_vector(const vector<double>& data);
// generate a random vector of n elements
vector<double> random_vector(int n);
// count the time it takes to run the inserter program and print a
// message to show the result
void time_insert(Inserter inserter, const vector<double>& data);
// print a message describing container kind and whether container 
// spanned by [from, last) is sorted 
template <class Iter> void check_sort(Iter first, Iter last,
				      string cont_kind);

int main()
    try {	
	cout << "How many elements for container? ";
	int num_elts;
	// continue asking for element number
	while (cin >> num_elts) {
	    // element number should not be lower than 1
	    if (num_elts < 1)
		cout << "\nAsking for empty container---ignored.\n";
	    else {
		vector<double> data = random_vector(num_elts);
		// insert, sort into new container, check if sorted
		// time the process and print out the result
		time_insert(insert_list, data);	
		time_insert(insert_set, data);
		time_insert(insert_vector, data);
	    }
	    cout << "\nHow many elements for container? ";
	}
	return 0;
    }
// give out error messages
    catch(exception& e) {
	cerr << "Error: " << e.what() << "\n";
	return 1;
    }
    catch(...) {
	cerr << "Oops: unknown exception!\n";
	return 2;
    }

vector<double> random_vector(int n)
{
    vector<double> v(n);
    static default_random_engine ran{};      // generate integers
    uniform_real_distribution<>ureal{0,1};   // maps ints into doubles
					     // in [0:1)
    for (int i = 0; i < n; ++i)
	v[i] = ureal(ran);

    return v;
}
    
void time_insert(Inserter inserter, const vector<double>& data)
{
    auto t1 = system_clock::now();               // begin time
    inserter(data);                              // program measured
    auto t2 = system_clock::now();               // end time
    cout << "Elapsed time: "
	 << duration_cast<milliseconds>(t2-t1).count()
	 << "milliseconds\n";
}

class Larger_than { 
    double v;
public: 
    Larger_than(double vv) : v(vv){}              // store the argument
    bool operator()(double x) const {return x>v;} // compare
};

void insert_list(const vector<double>& data)
{
    list<double>l;                            // reset for each entry
    for(int i = 0; i < data.size(); i++){
        list<double>::iterator p =
	    find_if(l.begin(), l.end(), Larger_than(data[i]));
	l.insert(p, data[i]);                 // sort and insert data
    }
    check_sort(l.begin(), l.end(), "list");   // double check if sorted
}

void insert_set(const vector<double>& data)
{
    set<double>s;
    for(int i = 0; i < data.size(); i++) {
	s.set::insert(data[i]);               // no need for find-if
    }                                         // a set is sorted
    check_sort(s.begin(), s.end(), "set");
}

void insert_vector(const vector<double>& data)
{
    vector<double>v;
    for(int i=0; i < data.size(); i++){
        vector<double>::iterator p =
	    find_if(v.begin(),v.end(), Larger_than(data[i]));
	v.insert(p, data[i]);                 // sort and insert data
    }
    check_sort(v.begin(), v.end(), "vector");
}
 
template <class Iter> void check_sort(Iter first, Iter last,
				      string cont_kind)  
{
    if (cont_kind == "set")
	cout << "Don't need to check that a set is sorted...";
    else {
	cout << "Check: " << cont_kind << " is "; 
	if (!is_sorted(first, last)) cout << "not ";
	cout << "sorted...";
    }
} 
