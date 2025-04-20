#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

const unsigned int DEFAULT_SIZE = 179;

struct Course
{
  string courseCode;
  string courseName;
};

class HashTable
{

private:
  // Define structures to hold bids
  struct Node
  {
    Course course;
    unsigned int key;
    Node *next;

    // default constructor
    Node()
    {
      key = UINT_MAX;
      next = nullptr;
    }

    // initialize with a bid
    Node(Course courseArg) : Node()
    {
      course = courseArg;
    }

    // initialize with a bid and a key
    Node(Course courseArg, unsigned int aKey) : Node(courseArg)
    {
      key = aKey;
    }
  };

  vector<Node> nodes;

  unsigned int tableSize = DEFAULT_SIZE;

  unsigned int hash(int key);

public:
  HashTable();
  HashTable(unsigned int size);
  virtual ~HashTable();
  void LoadDataStructure();
  void PrintCourseList();
  unsigned int PrintCourse(string courseId);
  size_t Size();

private:
  void DisplayCourse(Course course);
  void Insert(Course course);
  void Remove(Course course);
};

/**
 * Default constructor
 */
HashTable::HashTable()
{
  // Initalize node structure by resizing tableSize
  nodes.resize(tableSize);
}

/**
 * Constructor for specifying size of the table
 * Use to improve efficiency of hashing algorithm
 * by reducing collisions without wasting memory.
 */
HashTable::HashTable(unsigned int size)
{
  // invoke local tableSize to size with this->
  this->tableSize = size;
  // resize nodes size
  nodes.resize(tableSize);
}

/**
 * Destructor
 */
HashTable::~HashTable()
{
  // Iterate through each bucket in the hash table
  for (unsigned int i = 0; i < tableSize; ++i)
  {
    // Get the head of the chain at this bucket
    Node *current = nodes[i].next;

    // Traverse the chain and delete each node
    while (current != nullptr)
    {
      Node *temp = current;    // Store the current node
      current = current->next; // Move to the next node
      delete temp;             // Delete the stored node
    }
  }
}

// hash function
// Hash function to compute the index for a given key
// This function uses the modulo operator to ensure the index is within the bounds of the hash table size
unsigned int HashTable::hash(int key)
{
  // Implement the hash function
  return key % tableSize;
}

// load data structure
// Load the data structure from a CSV file
// This function reads the CSV file and populates the hash table with course data
void HashTable::LoadDataStructure()
{
  cout << "Loading data structure..." << endl;
  // Load the data structure from a CSV file
  // Implement the logic to read the CSV file and populate the data structure

  // Open the CSV file
  ifstream file("ProjectTwoProgramInput.csv");
  if (!file.is_open())
  {
    cerr << "Error: Could not open the file." << endl;
    return;
  }

  string line;
  // Read the file line by line
  while (getline(file, line))
  {
    stringstream ss(line);
    string courseCode, courseName, prereq1, prereq2;

    // Parse the line (split by commas)
    getline(ss, courseCode, ',');
    getline(ss, courseName, ',');
    getline(ss, prereq1, ',');
    getline(ss, prereq2, ',');

    // Create a Course object
    Course course;
    course.courseCode = courseCode;
    course.courseName = courseName;

    // Insert the course into the hash table
    Insert(course);
  }

  // Close the file
  file.close();
  cout << "Data structure loaded successfully." << endl;
}

// print course list
// Print the list of courses in the hash table
// This function iterates through the hash table and prints all courses
void HashTable::PrintCourseList()
{
  cout << "Printing course list..." << endl;

  // Create a vector to store all courses
  vector<Course> courseList;

  // Iterate through each bucket in the hash table
  for (unsigned int i = 0; i < tableSize; ++i)
  {
    // Get the current node in the bucket
    Node *current = &nodes[i];

    // If the bucket is not empty (key is not UINT_MAX)
    if (current->key != UINT_MAX)
    {
      // Add the course in the current node to the list
      courseList.push_back(current->course);

      // Traverse the chain (if any) and add all courses
      current = current->next;
      while (current != nullptr)
      {
        courseList.push_back(current->course);
        current = current->next;
      }
    }
  }

  // Sort the vector alphanumerically by courseCode
  sort(courseList.begin(), courseList.end(), [](const Course &a, const Course &b)
       { return a.courseCode < b.courseCode; });

  // Print the sorted list of courses
  for (const Course &course : courseList)
  {
    DisplayCourse(course);
  }
}

// print course
// Print a specific course based on the courseId
// This function searches for the course in the hash table and prints its details
// If the course is not found, it prints an error message
unsigned int HashTable::PrintCourse(string courseId)
{
  int courseFound = 9;
  // Hash the courseId to find the index in the hash table
  unsigned int index = hash(courseId.length());

  // Get the head of the chain at the hashed index
  Node *current = &nodes[index];

  // Traverse the chain to find the course
  while (current != nullptr && current->key != UINT_MAX)
  {
    if (current->course.courseCode == courseId)
    {
      // Course found, display it
      DisplayCourse(current->course);
      courseFound = 0;
      return courseFound;
    }
    current = current->next;
  }

  // If the course is not found
  cout << "Course with ID " << courseId << " not found." << endl;

  return courseFound;
}

// display course
// Display the details of a course
// This function prints the course code and name
void HashTable::DisplayCourse(Course course)
{
  // Implement the logic to display a course
  cout << course.courseCode << ", " << course.courseName << endl;
}

// insert course
// Insert a course into the hash table
// This function computes the hash index and inserts the course into the appropriate bucket
// If there is a collision, it uses chaining to handle it
void HashTable::Insert(Course course)
{
  // Implement the logic to insert a course into the hash table
  unsigned int index = hash(course.courseCode.length());
  Node *newNode = new Node(course, course.courseCode.length());

  if (nodes[index].key == UINT_MAX)
  {
    nodes[index] = *newNode;
  }
  else
  {
    Node *current = &nodes[index];
    while (current->next != nullptr)
    {
      current = current->next;
    }
    current->next = newNode;
  }
}

int main()
{
  string csvPath;
  int choice = 0;
  HashTable *courseTable;

  courseTable = new HashTable();

  cout << "Welcome to the course planner" << endl;

  string courseId;

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
      courseTable->LoadDataStructure();
      break;
    case 2:
      // print course list
      courseTable->PrintCourseList();
      break;
    case 3:
      // print course
      cout << "Enter course ID: ";
      cin >> courseId;
      courseTable->PrintCourse(courseId);
      break;
    case 9:
      cout << "Thank you for using the course planner!" << endl;
      break;
    default:
      cout << choice << " is not a valid option." << endl;
      break;
    }
  }

  return 0;
}