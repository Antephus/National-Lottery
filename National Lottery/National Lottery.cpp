#include <iostream>
#include <random>
using namespace std;



class LotteryDraw
{
private:
	int lottery_numbers[6];

public:
	LotteryDraw();
	void draw_lottery_nums();
	void sort_lottery_nums();
	void display_lottery_nums();
	void check_results();
	void reset_lottery_nums();
};


// Display a menu of options for users to choose until the user indicates they are finished using the program
int main()
{
	int choice;
	LotteryDraw wed_lotto;
	LotteryDraw sat_lotto;
	bool wed_lotto_drawn = false;
	bool sat_lotto_drawn = false;

	cout << "Hello and welcome to the National Lottery!" << endl << endl;

	// Menu loop
	do
	{
		cout << "-------------------------- MAIN MENU --------------------------" << endl;
		cout << "1. Draw Wednesday's Lotto" << endl;
		cout << "2. Draw Saturday's Lotto" << endl;
		cout << "3. Check results" << endl;
		cout << "4. Clear all lottery draws and begin a new week" << endl;
		cout << "---------------------------------------------------------------" << endl;
		cout << "Please enter the number of your choice (1-4) or 0 to exit: ";
		cin >> choice;
		
		cout << endl << endl;


		// Draw Wednesday's lotto and display it in ascending order to the user
		if (choice == 1)
		{
			if (wed_lotto_drawn == false)
			{
				wed_lotto.draw_lottery_nums();
				wed_lotto.sort_lottery_nums();

				cout << "The results of this week's Wednesday National Lotto draw are the following 6 numbers... " << endl;
				wed_lotto.display_lottery_nums();
				wed_lotto_drawn = true;
			}
			// display message if numbers already drawn
			else
				cout << "This week's Wednesday Lotto has already been drawn; you can begin a new week or draw from the main menu." << endl << endl;
		}


		// Draw Saturday's lotto and display it in ascending order to the user
		else if (choice == 2)
		{
			if (sat_lotto_drawn == false)
			{
				sat_lotto.draw_lottery_nums();
				sat_lotto.sort_lottery_nums();

				cout << "The results of this week's Saturday National Lotto draw are the following 6 numbers... " << endl;
				sat_lotto.display_lottery_nums();
				sat_lotto_drawn = true;
			}
			// display message if numbers already drawn
			else
				cout << "This week's Saturday Lotto has already been drawn; you can begin a new week or draw from the main menu." << endl << endl;
		}


		// Check the user's lottery numbers against the draws to see how many matches they have
		else if (choice == 3)
		{
			int results_choice = -1;
			int tickets = 0;
			int ticket_counter;

			// Sub-menu loop
			do
			{
				cout << "-----------------------------------------------    SUB MENU    -----------------------------------------------" << endl;
				cout << "Which draw(s) would you like to check results for? Enter the number to select, or 0 to exit to the main menu: " << endl;
				cout << "1. Saturday's Lotto Draw" << endl;
				cout << "2. Wednesday's Lotto Draw" << endl;
				cout << "--------------------------------------------------------------------------------------------------------------" << endl;
				cin >> results_choice;
				cout << endl;
				
				// As long as Saturday's draw is done, check their tickets; otherwise print message
				if (results_choice == 1)
				{

					if (sat_lotto_drawn)
					{
						sat_lotto.check_results();
					}
					else
					{
						cout << "Sorry but the Saturday Lotto numbers have yet to be drawn this week! Please try again when they've been drawn." << endl << endl << endl;
					}
				}	
				// As long as Wednesday's draw is done, check their tickets; otherwise print message
				else if (results_choice == 2)
				{
					if (wed_lotto_drawn)
					{
						wed_lotto.check_results();
					}
					else
					{
						cout << "Sorry but the Wednesday Lotto numbers have yet to be drawn this week! Please try again when they've been drawn." << endl << endl << endl;
					}
				}
				// Print error message if user input is invalid for sub-menu
				else if (results_choice != 0)
				{
					cout << "That's not a valid choice, please enter 1 or 2, or 0 to exit to the main menu: " << endl;
					cin >> results_choice;
					cout << endl;
				}
			// End of sub-menu and end of choice 3 if statement (for checking results)
			} while (results_choice != 0);
		}


		// Reset everything for the beginning of a "new week"
		else if (choice == 4)
		{
			sat_lotto.reset_lottery_nums();
			wed_lotto.reset_lottery_nums();
			sat_lotto_drawn = false;
			wed_lotto_drawn = false;

			cout << "Thank you, a new week has begun and the Wednesday and Saturday Lottos are yet to be drawn." << endl << endl;
		}


		// Get a new choice input if it's not a valid selection for main menu
		else if (choice != 0)
		{
			cout << "That's not a valid choice, please enter 1-3, or 0 to exit: " << endl;
			cin >> choice;
		}

	//end of wmain menu
	} while (choice != 0);

	cout << "Thank you, good bye :)" << endl;	

	return 0;
}


// Constructor
LotteryDraw::LotteryDraw()
{
	// Initialise empty lottery draw
	for (int counter = 0; counter < 6; counter++)
		lottery_numbers[counter] = { 0 };
}



// Generates 6 unique, random nums and puts them into the lottery array
void LotteryDraw::draw_lottery_nums()
{
	int random_num;
	int current_position = 0;
	int numbers_counter = 0;

	// Needed to generate a random number in range 1 - 59 where distribution is uniform
	// i.e. all numbers have an equal chance of being selected
	random_device generator;
	uniform_int_distribution<int> distribution(1, 59);


	do // For 6 numbers
	{
		// Get random number
		random_num = distribution(generator);


		// For any and all previously drawn numbers, check if it's the same as the random number and get a new random number if it is
		while (current_position < numbers_counter)
		{
			while (random_num == lottery_numbers[current_position])
			{
				random_num = distribution(generator);
				current_position = 0;
			}

			// Otherwise, move on to check the next number in the array
			current_position++;
		}

		// Add accepted random number to the array, one to the counter, and reset array position back to start for next number's checks
		lottery_numbers[numbers_counter] = random_num;
		numbers_counter++;
		current_position = 0;

	} while (numbers_counter < 6);
}



// Sorts the lottery numbers into ascending order in the array
void LotteryDraw::sort_lottery_nums()
{
	int to_sort, being_tested, current_position;

	// For each lottery number after the first
	for (current_position = 1; current_position < 6; current_position++)
	{
		to_sort = lottery_numbers[current_position]; 
		being_tested = current_position - 1;
		
		// While num is less than its predecessor and there are more numbers to test, move the larger number up and move on to next test
		while (being_tested >= 0 && to_sort < lottery_numbers[being_tested])
		{
			lottery_numbers[being_tested + 1] = lottery_numbers[being_tested];
			being_tested--;
		}

		// Insert the number being sorted into the space created
		lottery_numbers[being_tested + 1] = to_sort;
	}
}



// Display the 6 lottery numbers
void LotteryDraw::display_lottery_nums()
{
	for (int counter = 0; counter < 6; counter++)
	{
		cout << lottery_numbers[counter] << "  ";

	}
	cout << endl << endl << endl;
}



// Ask user how many tickets they want to check and count how many numbers they matched with lottery nums for each ticket
void LotteryDraw::check_results()
{
	int users_nums[6] = { 0 };
	int matches = 0;
	int tickets = 0;

	cout << "Please enter how many Lotto tickets you would like to check: " << endl;
	cin >> tickets;
	cout << endl << endl << "Wednesday's Lotto Draw Results " << endl;

	for (int ticket_counter = 0; ticket_counter < tickets; ticket_counter++)
	{
		cout << "Ticket " << ticket_counter + 1 << ": " << endl;

		cout << "Please enter the 6 lottery numbers you want to check: " << endl;

		// Get the user's lottery numbers
		for (int u_counter = 0; u_counter < 6; u_counter++)
		{
			cout << u_counter + 1 << ": ";
			cin >> users_nums[u_counter];
			while (users_nums[u_counter] < 1 || users_nums[u_counter] > 59)
			{
				cout << "Sorry but that's not a valid lottery number, you must have typoed! Try again: " << endl;
				cin >> users_nums[u_counter];
			}

			// Compare it against all drawn lottery numbers and for each match add 1 to the matches counter
			for (int d_counter = 0; d_counter < 6; d_counter++)
			{
				if (users_nums[u_counter] == lottery_numbers[d_counter])
				{
					matches++;
				}
			}
		}

		cout << endl << endl;

		// Print a message letting the user know their matches, if any.
		if (matches == 0)
			cout << "Sorry but you have no matches this time :< Try again next week!" << endl << endl;
		else
			cout << "Congratulations, it looks like you matched " << matches << " numbers! " << endl << endl;
	}
}


// Clear out the lottery drawn and reset everything to zero/empty
void LotteryDraw::reset_lottery_nums()
{
	for (int counter = 0; counter < 6; counter++)
		lottery_numbers[counter] = { 0 };
}