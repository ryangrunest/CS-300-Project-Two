#include <iostream>

using namespace std;

int main()
{
  string csvPath;
  int choice = 0;
  cout << "Welcome to the course planner" << endl;

  while (choice != 9)
  {
    cout << endl;
    cout << "  1. Load Data Structure." << endl;
    cout << "  2. Print Course List." << endl;
    cout << "  3. Print Course." << endl;
    cout << "  9. Exit" << endl;
    cout << endl;

    cout << "What would you like to do? ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      // load data structure
    case 2:
      // print course list
    case 3:
      // print course
    default:
      cout << choice << " is not a valid option." << endl;
      break;
    }
  }

  cout << "Thank you for using the course planner!" << endl;
}