/**********************************************************************
 *
 * Project 3: Bulls and Cows
 *
 * Author: Tianmao Jiang
 * Date:   August 12 2015
 *
 * This program is a game called "Bulls and Cows". User takes several
 * guess and program gives out how many bulls and cows there are 
 * coresponding to the guess.
 *
 **********************************************************************/

#include <bjarne/std_lib_facilities.h>

// (global) constants

const bool show_soln = false; // show solution before playing a new round
const bool debug = false;     // print debug info about the bull/cow calculation
const int num_slots = 4;     // number of slots
const int range_top = 10;    // upper bound on slot value

// for bad input data
class Bad_data{};

// for a bad frequency vector ... this shouldn't ever happen
class Bad_frequency{};

// function declarations
void offer_help();
vector<int> generate_solution();
void print_vector(string msg, vector<int> v);
bool play_one_game(vector<int> solution);
int count_cows(int bulls, vector<int> guess, vector<int> solution);
vector<int> compute_frequency(vector<int> data);
void print_debug_info(vector<int> solution_frequency, 
                      vector<int> guess_frequency, 
                      vector<int> min_frequency, int total_hits);

/*
 * main() handles top-level flow of control, as usual 
 */
int main()
{
    // pigeonhole-principle check
    if (num_slots >= range_top) {
	cerr << "Error: range_top (" << range_top
	     << ") should be greater than num_slots " << num_slots << endl; 
	return 1;
    }

    try {
	offer_help();     // ... if needed

	bool playing = true;           // play another round?
	while (playing) {
	    // generate solution, printing same if debugging
	    vector<int> solution = generate_solution();
	    if (show_soln) 
		print_vector("Actual solution: ", solution);

	    // play the game
	    bool success = play_one_game(solution);

	    // how'd we do?
	    if (success)
		cout << "Congratulations!\n";
            else
		print_vector("Too bad!  Solution was ", solution);

	    // another round?
	    cout << "\nPlay again (0/1)? ";
	    int play_again;
	    if (!(cin >> play_again))
		throw Bad_data();
	    playing = play_again != 0;
	}
    }
    catch (Bad_data) {
	cerr << "Bad input data!  I give up!\n";
	return 2;
    }
    catch (Bad_frequency) {
	cerr << "Bad frequency vector.  This can't happen!\n";
	return 3;
    }
}

/*
 * offer help, if needed
 */
void offer_help()
{
    cout << "Need help (0/1)? ";
    int need_help;
    if (!(cin >> need_help)) 
	throw Bad_data();
    // help content
    if (need_help != 0) {
	cout << "\nI will generate a pattern of " << num_slots
	     << " distinct numbers, "
	     << "each in the range 0 through" << range_top - 1 << ".\n"
	     << "You will give a series of guesses of this pattern.\n"
	     << "Each guess that you enter will be a line containing "
	     << num_slots << "integers,\n"
	     << "separated by spaces, such as\n" 
	     << "     2 4 3 1\n"
	     << "I will respond with the number of bulls and cows.\n"
	     << "For example, if the actual solution was 2 3 6 1, I'll respond\n"
	     << "     Bulls: 2, cows: 1\n"
	     << "since two guesses (2 and 1) were in the correct position\n"
	     << "and one guss (3) was in an incorrect position.\n"
	     << "See how many guesses it takes you to get the solution!\n"
	     << "If you want to give up, type a negative number for one of\n"
	     << "your guesses, and we'll tell you what the pattern was.!\n";
    }
}

/*
 * generate solution for a game of Bulls and Cows
 *
 * precondition: num_slots > 0, range_top > 0
 * return value: vector of size num_slots, with distinct entries, each
 * in the range [0..range_top)
 */

vector<int> generate_solution()
{
    // tracks which numbers have been used
    vector<bool> is_used(range_top);
    vector<int> solution;
    for (int i = 0; i < num_slots; i++) {
	int trial = randint(range_top - 1);
	while (is_used.at(trial)) 
	    trial = randint(range_top - 1);         
	solution.push_back(trial);
	is_used.at(trial) = true;
    }
    return solution;
}

/*
 * print a vector, with an initial decoration, all on one line
 * 
 * the only precondition (not easily enforceable) is that it all fits
 * on line
 */
void print_vector(string msg, vector<int> v)
{
    cout << msg;
    for (auto x: v) cout << x << " ";   
    cout << endl;
}

/*
 * accept guesses, find out both number of Bulls and Cows, and determine
 * that player continue guessing or gives up or wins
 * 
 * 
 * preconditon:  vector of solution containing (num_slots) integers,
 * num_slot > 0, range_top > 0
 * return value: return true when bulls are all found, or return false
 * when the input is less than 0, or get thrown into Bad_data()
 *
 */
bool play_one_game(vector<int> solution)
{
    int guess_num = 1;

    while (true) {                           // the loop for still playing
	cout << "\nGuess #" << guess_num << "? "; 
	vector<int> guess;
	int num;
	for (int i = 0; i < num_slots; i++) {
	    cin >> num;
	    guess.push_back(num);    //save each input into the same vector
	}

	int bulls = 0;               //reactions for inappropriate inputs
	for (int i = 0; i < guess.size(); i++){ 
	    if (guess[i] > range_top)
		throw Bad_data();
	    else if (guess[i] < 0)
		return false;        //you quit!
	    else if (guess[i] == solution[i])
		++bulls;             //count number of bulls
	}

	if (bulls == num_slots) {
	    cout << "Bulls: " << bulls << ", Cows: 0\n";
	    return true;             //you win!
	}
	else {
	    cout << "Bulls: " << bulls << ", Cows: "
	         << count_cows(bulls, guess, solution) << "\n";
	    ++guess_num;             //print out bulls and cows and
				     //keep track of guess number	    
	}
    }
}

/*
 *  setup and calculate the frequency of the solution and guess, then
 *  figure out how many Cows there are
 */
int count_cows(int bulls, vector<int> guess, vector<int> solution)
{	
    // next two lines should be
    //    vector<int> solution_frequency = ... ;
    //    vector<int> guess_frequency = ... ;
    // where you need to figure out how to fill in the right-hand side
    // of these initializations
    vector<int> solution_frequency (range_top, 0);
    vector<int> guess_frequency (range_top, 0);
    vector<int> min_frequency (range_top, 0);
    int total_hits = 0;
    solution_frequency = compute_frequency(solution);
    guess_frequency = compute_frequency(guess);  // figure out each frequency
    for (int i = 0; i < range_top; ++i)
	min_frequency[i] = min(solution_frequency[i],guess_frequency[i]);
    for (int i = 0; i < min_frequency.size(); ++i)
	total_hits += min_frequency[i];         // count total hits
   
    if (debug)
	print_debug_info(solution_frequency, guess_frequency, 
			 min_frequency, total_hits);

    return total_hits - bulls;        // return number of cows
}

/*
 * determine how many 0's, 1's, ... in a given vector
 *
 * precondition: a vector parameter containing integers
 * return value: a new integer vector 
 */
vector<int> compute_frequency(vector<int> data)
{
    vector<int> temp(range_top);
    for (auto i: data)
	temp[i] += 1;
    // a simple, yet elegant, for-loop will do the job here
    return temp;
}

/*
 * prints useful debugging information, as per the project handout
 */
void print_debug_info(vector<int> solution_frequency, 
                      vector<int> guess_frequency, 
                      vector<int> min_frequency, int total_hits)
{
    cout << "index:             ";
    for (int i = 0; i < solution_frequency.size(); i++)
	cout << " " << i;
    cout << "                   ";
    cout << endl;
    cout << "                   ";
    for (int i = 0; i < solution_frequency.size(); i++)
	cout << "--";
    cout << endl;      
    print_vector("solution frequency: ", solution_frequency);
    print_vector("guess frequency   : ", guess_frequency);
    print_vector("minimum           : ", min_frequency);
    cout << "sum minimum:        " << total_hits << endl;
}

