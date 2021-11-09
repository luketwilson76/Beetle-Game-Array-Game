/**
Luke Wilson
L3 Beetle Game: make a game where you try to build a beetle using a die
See the requirements list in the Lab description for what to do
Beetle image, GetRandom, and Dice by Dr. Jan Pearce, Berea College
Acknowledgments: 
Dr. Mario Nakazawa: showed me how to use get functions
Anish Kharel: helped debug my main()
*/

#include <iostream>
#include <string>
#include <random> //needed for GetRandom
#include <chrono> 
using namespace std;
int turn = 2;
string partial_beetle[6];

class GetRandom {
	/** Uses <random> from C++11 to return a random integer in range [1..size] */
public:
	GetRandom(int size) {
		random_device rd; // declares a random_device object that need to generate a random number.
		mt19937 gen(rd()); //mt19937 is an efficient pseudo-random number generator using the Mersenne twister algorithm.
		uniform_int_distribution<int> intdist(1, size); //create a uniform distribution object to turn the pseudorandom result into a random digit between 1 and size.
		self_rand_int_ = intdist(gen); //generates the random number.
	}
	int roll() {
		return self_rand_int_;
	}
private:
	int self_rand_int_;
}; // end of GetRandom


class Dice {
	/** class that can be used to make dice.
	Dependent upon the Getrandom class above. */
public:
	Dice() {// default constructor assumes a 6-sided die.
		self_roll_count_ = 0;
		self_sides_ = 6;
	}
	Dice(int sides) {        // constructor for any size dice
		self_roll_count_ = 0;
		self_sides_ = sides;
	}
	int roll() {             // return the random roll of the die
		// postcondition: number of rolls updated, random 'die' roll returned

		GetRandom newrandom(self_sides_);
		self_roll_count_ = self_roll_count_ + 1;         // update # of times die rolled
		return(newrandom.roll());
	}
	int get_sides() const {   // how many sides this die has
		// postcondition: return # of sides of die
		return self_sides_;
	}
	int get_roll_count() const {   // # times this die rolled
		// postcondition: return # of times die has been rolled
		return self_roll_count_;
	}
private:
	int self_roll_count_;       // # times die rolled
	int self_sides_;           // # sides on die
};

class Beetle {
public:
	Beetle() {
		//intializes attributes of beetle class
		body = 0; 
		head = 0; 
		legs = 0; 
		eyes = 0; 
		feelers = 0; 
		tail = 0;
	}
	//gets return values for attributes
	int get_eyes() {
		return eyes;
	}
	int get_tail() {
		return tail;
	}
	int get_legs() {
		return legs;
	}
	int get_feelers() {
		return feelers;
	}
	//adds parts to beetle depending on die roll
	string roll_die(int roll, bool print) {
		if (body < 1 & roll == 1) {
			string txt = "1: body added to beetle\n";
			body = 1;
			if (print == true) {
				partial_beetle[2] = " {   }\n";
				partial_beetle[3] = " {   }\n";
				partial_beetle[4] = " {   }\n";
			}
			return txt;
		}
		if (body == 1 & head < 1 & roll == 2) {
			string txt = "2: head added to beetle\n";
			head = 1;
			if (print == true) {
				partial_beetle[1] = " {  }\n";
			}
			return txt;
		}
		if (legs < 6 & body == 1 & roll == 3) {
			string txt = "3: leg added to beetle\n";
			legs = legs + 1;
			if (print == true) {
				if (legs == 1) {
					partial_beetle[2] = "-{   }\n";
				}
				if (legs == 2) {
					partial_beetle[2] = "-{   }-\n";
				}
				if (legs == 3) {
					partial_beetle[3] = "-{   }\n";
				}
				if (legs == 4) {
					partial_beetle[3] = "-{   }-\n";
				}
				if (legs == 5) {
					partial_beetle[4] = "-{   }\n";
				}
				if (legs == 6) {
					partial_beetle[4] = "-{   }-\n";
				}
			}
			return txt;
		}
		if (eyes < 2 & head == 1 & roll == 4) {
			string txt = "4: eye added to beetle\n";
			eyes = eyes + 1;
			if (print == true) {
				if (eyes == 1) {
					partial_beetle[1] = " {. }\n";
				}
				if (eyes == 2) {
					partial_beetle[1] = " {..}\n";
				}
			}
			return txt;
		}
		if (roll == 5 & feelers < 2 & head == 1) {
			string txt = "5: feeler added to beetle\n";
			feelers = feelers + 1;
			if (print == true) {
				if (feelers == 1) {
					partial_beetle[0] = "  ;\n";
				}
				if (feelers == 2) {
					partial_beetle[0] = "  ;;\n";
				}
			}
			return txt;
		}
		if (tail < 1 & body == 1 & roll == 6) {
			string txt = "6: tail added to beetle\n";
			tail = tail + 1;
			if (print == true) {
				if (tail == 1) {
					partial_beetle[5] = "   V\n";
				}
			}
			return txt;
		}
		else {
			string txt ="an invalid dice roll. Next player's turn.\n";
			turn = turn + 1;
			return txt;
		}
	}
	//overloads << operator
	friend ostream& operator << (ostream& stream, const Beetle& beetle);
	private:
	int head;
	int eyes;
	int feelers;
	int body;
	int legs;
	int tail;
};
//prints the score of the player/# of beetle parts on beetle object
	ostream& operator << (ostream& stream, const Beetle& beetle){
	stream << " has " << beetle.body << " BODY " << beetle.head << " HEAD " << beetle.eyes << " EYES " << beetle.legs << " LEGS " << beetle.feelers << " FEELERS " << beetle.tail << " TAIL\n";
	return stream;}

int main() {
	Dice dice;
	Beetle beetle1;
	Beetle beetle2;
	char a;
	string win_name = " ";
	int win = 0;
	while (win == 0) {
		if (turn %2 ==0) {//player 1's turn
			cin >> a;
			cout << "player 1 rolled " <<beetle1.roll_die(dice.roll(), true);
			cout << "player 1" << beetle1;
			for (int i = 0; i < 6; i++) {
				cout << partial_beetle[i];
			}
			cout << "\n";
		}
		if (turn % 2 == 1) {//player 2's turn
			cout << "player 2 rolled " << beetle2.roll_die(dice.roll(), false);
			cout << "player 2" << beetle2;
			cout << "\n";
		}

		//prints win screen with player's name
		if (beetle1.get_feelers() + beetle1.get_eyes() + beetle1.get_legs() + beetle1.get_tail() == 11) {
			win_name = "player 1";
			win = 1;
		}
		if (beetle2.get_feelers() + beetle2.get_eyes() + beetle2.get_legs() + beetle2.get_tail() == 11) {
			win_name = "player 2";
			win = 1;
		}
	}
	cout << win_name + " wins\n";
	return 0;
	}