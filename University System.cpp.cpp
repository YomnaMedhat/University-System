#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*  ------------------------- STACK: Course Registration -------------------------  */
class Stack {
private:
    string courseID;
    vector<string> prerequisites;
    int top;

public:
    Stack(string id, vector<string> prereqs) : courseID(id), prerequisites(prereqs), top(-1) {}

    string getCourseID() const { return courseID; }
    vector<string> getPrerequisites() const { return prerequisites; }

    void push(const string& prereq) {
        if (top + 1 < prerequisites.size()) {
            prerequisites[++top] = prereq;
        }
        else {
            prerequisites.push_back(prereq);
            top++;
        }
    }

    void pop() {
        if (top >= 0) {
            top--;
        }
    }

    string peek() const {
        if (top >= 0) {
            return prerequisites[top];
        }
        return "";
    }

    bool isEmpty() const {
        return top == -1;
    }
};

class CourseRegistration {
private:
    Stack prereqStack;

public:
    CourseRegistration(string id, vector<string> prereqs) : prereqStack(id, prereqs) {}

    void pushPrerequisites(const vector<string>& prereqs) {
        while (!prereqStack.isEmpty()) prereqStack.pop();
        for (const auto& prereq : prereqs) {
            prereqStack.push(prereq);
        }
    }

    void popPrerequisite() {
        if (!prereqStack.isEmpty()) {
            cout << "Popping prerequisite: " << prereqStack.peek() << endl;
            prereqStack.pop();
        }
        else {
            cout << "No prerequisites to pop.\n";
        }
    }

    void validatePrerequisites(const Stack& course, const vector<string>& completedCourses) {
        pushPrerequisites(course.getPrerequisites());

        for (const auto& completed : completedCourses) {
            if (!prereqStack.isEmpty() && prereqStack.peek() == completed) {
                prereqStack.pop();
            }
        }

        if (prereqStack.isEmpty()) {
            cout << "\nStudent is eligible to register for course " << course.getCourseID() << ".\n";
        }
        else {
            cout << "\nStudent is NOT eligible to register for course " << course.getCourseID() << ".\n";
            displayRemainingPrerequisites();
        }
    }

    void displayRemainingPrerequisites() {
        Stack temp = prereqStack;
        vector<string> remaining;

        while (!temp.isEmpty()) {
            remaining.push_back(temp.peek());
            temp.pop();
        }

        cout << "Remaining prerequisites: ";
        if (remaining.empty()) {
            cout << "None\n";
            return;
        }

        for (size_t i = 0; i < remaining.size(); ++i) {
            cout << remaining[i];
            if (i != remaining.size() - 1) {
                cout << ", ";
            }
        }
        cout << "\n";
    }
};

/*  ------------------------- QUEUE: Course Waitlist -------------------------  */
struct Node {
    int studentID;
    Node* next;
};

class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue() {
        front = rear = nullptr;
    }


    void enqueue(int studentID) {
        Node* newNode = new Node();
        newNode->studentID = studentID;
        newNode->next = nullptr;

        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }

        cout << "Student with ID " << studentID << " added to the waitlist." << endl;
    }

    void dequeueByID(int studentID) {
        if (front == nullptr) {
            cout << "The waitlist is empty, no student to remove." << endl;
            return;
        }

        Node* temp = front;
        Node* prev = nullptr;

        if (temp != nullptr && temp->studentID == studentID) {
            front = temp->next;
            delete temp;
            cout << "Student with ID " << studentID << " has been removed from the waitlist." << endl;
            return;
        }

        while (temp != nullptr && temp->studentID != studentID) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Student with ID " << studentID << " not found in the waitlist." << endl;
            return;
        }

        prev->next = temp->next;
        if (temp == rear) {
            rear = prev;
        }

        delete temp;
        cout << "Student with ID " << studentID << " has been removed from the waitlist." << endl;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    void displayWaitlist() {
        if (front == nullptr) {
            cout << "The waitlist is empty." << endl;
            return;
        }

        Node* temp = front;
        cout << "Waitlist: ";
        while (temp != nullptr) {
            cout << temp->studentID << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

/*  ------------------------- LINKED LIST: Student Records -------------------------    */
class Student {
public:
    int ID;
    long long PHONE;
    string NAME, ADDRESS, EMAIL, PASSWORD;
    Student* NEXT;

    Student(int id, long long phone, string name, string address, string email, string password)
        : ID(id), PHONE(phone), NAME(name), ADDRESS(address), EMAIL(email), PASSWORD(password), NEXT(nullptr) {
    }
};

class SLL {
private:
    Student* head;

public:
    Student* getHead() { return head; }

    SLL() : head(nullptr) {}

    void add(int id, long long phone, string name, string address, string email, string password) {
        Student* newStudent = new Student(id, phone, name, address, email, password);
        if (!head) {
            head = newStudent;
        }
        else {
            Student* temp = head;
            while (temp->NEXT != nullptr) {
                temp = temp->NEXT;
            }
            temp->NEXT = newStudent;
        }
        cout << "The student added successfully\n";
    }

    void deletion(int id) {
        if (!head) {
            cout << "No student to delete, this is an empty list!\n";
            return;
        }
        if (head->ID == id) {
            Student* temp = head;
            head = head->NEXT;
            delete temp;
            cout << "Student with ID " << id << " deleted successfully.\n";
            return;
        }

        Student* current = head;
        Student* previous = nullptr;
        while (current != nullptr && current->ID != id) {
            previous = current;
            current = current->NEXT;
        }
        if (!current) {
            cout << "Student with " << id << " not founded!\n";
            return;
        }
        previous->NEXT = current->NEXT;
        delete current;
        cout << "Student with ID " << id << " deleted successfully.\n";
    }


    void display() {
        if (!head) {
            cout << "No student to display.\n";
            return;
        }
        Student* temp = head;
        while (temp != nullptr) {
            cout << "Name: " << temp->NAME << "\n";
            cout << "ID: " << temp->ID << "\n";
            cout << "Phone: " << temp->PHONE << "\n";
            cout << "Email: " << temp->EMAIL << "\n";
            cout << "Address: " << temp->ADDRESS << "\n";
            cout << "Password: " << temp->PASSWORD << "\n";
            temp = temp->NEXT;
        }
    }

    ~SLL() {
        while (head) {
            Student* temp = head;
            head = head->NEXT;
            delete temp;
        }
    }
};

/*  ------------------------- DLL: Course Enrollment History ------------------------- */
class DLLNode {
public:
    int recordId;
    string recordName;
    DLLNode* prev;
    DLLNode* next;

    DLLNode(int id, string name) : recordId(id), recordName(name), prev(nullptr), next(nullptr) {}
};

class DLL {
private:
    DLLNode* head;

public:
    DLLNode* getHead() { return head; }

    DLL() : head(nullptr) {}

    void addRecord(int id, string name) {
        DLLNode* newNode = new DLLNode(id, name);
        if (!head) {
            head = newNode;
        }
        else {
            DLLNode* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->prev = temp;
        }
        cout << "Record added successfully.\n";
    }

    void displayRecords() {
        if (!head) {
            cout << "No records to display.\n";
            return;
        }
        DLLNode* temp = head;
        while (temp != nullptr) {
            cout << "Record ID: " << temp->recordId << ", Name: " << temp->recordName << "\n";
            temp = temp->next;
        }
    }
};

/*  ------------------------- SEARCH: Sort and Sort Operations -------------------------   */
class Search {
private:
    SLL& studentList;

public:
    Search(SLL& list) : studentList(list) {}

    void linearSearch(int id) {
        if (!studentList.getHead()) {
            cout << "The student list is empty.\n";
            return;
        }
        Student* temp = studentList.getHead();
        while (temp) {
            if (temp->ID == id) {
                cout << "Student Found:\n";
                cout << "Name: " << temp->NAME << "\n";
                cout << "ID: " << temp->ID << "\n";
                cout << "Phone: " << temp->PHONE << "\n";
                cout << "Email: " << temp->EMAIL << "\n";
                cout << "Address: " << temp->ADDRESS << "\n";
                return;
            }
            temp = temp->NEXT;
        }
        cout << "Student with ID " << id << " not found!\n";
    }

    DLLNode** toSortedArray(DLLNode* head, int& size) {
        size = 0;
        DLLNode* temp = head;

        while (temp) {
            size++;
            temp = temp->next;
        }

        DLLNode** records = new DLLNode * [size];
        temp = head;

        for (int i = 0; i < size; i++) {
            records[i] = temp;
            temp = temp->next;
        }

        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (records[j]->recordId > records[j + 1]->recordId) {
                    swap(records[j], records[j + 1]);
                }
            }
        }

        return records;
    }

    void binarySearch(DLLNode* head, int id) {
        int size;
        DLLNode** records = toSortedArray(head, size);
        int low = 0, high = size - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (records[mid]->recordId == id) {
                cout << "Record Found: \n";
                cout << "Record ID: " << records[mid]->recordId << ", Name: " << records[mid]->recordName << "\n";
                delete[] records;
                return;
            } else if (records[mid]->recordId < id) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        cout << "Record with ID " << id << " not found!\n";
        delete[] records;
    }
};

/*  ------------------------- BST: Course Records ------------------------- */
class CourseRecords {
private:
    class Course {
    public:
        int courseId;
        int courseCredits;
        string courseName;
        string courseInstructor;
        Course* left;
        Course* right;

        Course(int id, string name, int credits, string instructor)
            : courseId(id), courseName(name), courseCredits(credits), courseInstructor(instructor), left(nullptr), right(nullptr) {
        }
    };

    Course* root;

    void addCourse(Course*& node, int id, string name, int credits, string instructor) {
        if (!node) {
            node = new Course(id, name, credits, instructor);
        }
        else if (id < node->courseId) {
            addCourse(node->left, id, name, credits, instructor);
        }
        else {
            addCourse(node->right, id, name, credits, instructor);
        }
    }

    void inorderTraversal(Course* node) {
        if (node) {
            inorderTraversal(node->left);
            cout << "Course ID: " << node->courseId << ", Name: " << node->courseName << ", Credits: " << node->courseCredits << ", Instructor: " << node->courseInstructor << endl;
            inorderTraversal(node->right);
        }
    }

    Course* dropCourse(Course* node, int id) {
        if (!node) return node;

        if (id < node->courseId) {
            node->left = dropCourse(node->left, id);
        }
        else if (id > node->courseId) {
            node->right = dropCourse(node->right, id);
        }
        else {
            if (!node->left) {
                Course* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right) {
                Course* temp = node->left;
                delete node;
                return temp;
            }

            Course* temp = findMin(node->right);
            node->courseId = temp->courseId;
            node->courseName = temp->courseName;
            node->courseCredits = temp->courseCredits;
            node->courseInstructor = temp->courseInstructor;

            node->right = dropCourse(node->right, temp->courseId);
        }
        return node;
    }

    Course* findMin(Course* node) {
        while (node && node->left)
            node = node->left;
        return node;
    }

public:
    CourseRecords() : root(nullptr) {}

    void addCourse(int id, string name, int credits, string instructor) {
        addCourse(root, id, name, credits, instructor);
    }

    void displayCourses() {
        inorderTraversal(root);
    }

    void dropCourse(int id) {
        root = dropCourse(root, id);
        cout << "Course with ID " << id << " has been dropped." << endl;
    }
};

/*  ------------------------- HASHING:  ------------------------- */
class HashTable {
    private:
        struct Course {
            int id;
            string name;
        };

        struct Node {
            Course course;
            Node* next;
        };

        vector<Node*> table;  

    public:
        HashTable(int size) {
            table.resize(size, nullptr);  
        }
    
        int hashFunction(int courseId) {
            return courseId % table.size();
        }   

        void insertCourse(int courseId, const string& courseName) {
            int index = hashFunction(courseId);
            
            Node* newNode = new Node;
            newNode->course.id = courseId;
            newNode->course.name = courseName;
            newNode->next = table[index];  
            
            table[index] = newNode; 

            cout << "Course added: " << courseName << " with ID " << courseId << endl;
        }   

        vector<string> searchAllWithHashing(int courseId) {
            vector<string> result;
            int index = hashFunction(courseId); 

            Node* current = table[index];
            while (current != nullptr) {
                if (current->course.id == courseId) {
                    result.push_back(current->course.name);
                }
                current = current->next;
            }   

            return result;
        }   

        void displayCourses() {
            cout << "Courses in the hash table:\n";
            for (int i = 0; i < table.size(); ++i) {
                Node* current = table[i];
                while (current != nullptr) {
                    cout << "Course ID: " << current->course.id << ", Course Name: " << current->course.name << endl;
                    current = current->next;
                }
            }
        }
};

void displayMenu() {
    cout << "\n---------------- Menu ----------------\n";
    cout << "1. Course Registration\n";
    cout << "2. Course Waitlist\n";
    cout << "3. Student Records\n";
    cout << "4. Course Enrollment History\n";
    cout << "5. Linear Search (Student Records)\n";
    cout << "6. Binary Search (Additional Records)\n";
    cout << "7. Course Records (BST)\n";
    cout << "8. Course Lookup (Hash Table)\n";
    cout << "0. Exit\n";
    cout << "--------------------------------------\n";
    cout << "Choose an option: ";
}

int main() {
    int choice;
    bool running = true;

    CourseRegistration csCourse("", {});
    Queue waitlist;
    SLL studentList;
    DLL recordList;
    Search search(studentList);
    CourseRecords courseRecords;
    HashTable courseHashTable(10); 

    while (running) {
        displayMenu();
        cin >> choice;
        switch (choice) {
            case 1: {
                string courseID;
                int prereqCount;
                vector<string> prerequisites;

                cout << "Enter course ID: ";
                cin >> courseID;
                cout << "Enter number of prerequisites: ";
                cin >> prereqCount;

                prerequisites.resize(prereqCount);
                for (int i = 0; i < prereqCount; ++i) {
                    cout << "Enter prerequisite " << i + 1 << ": ";
                    cin >> prerequisites[i];
                }

                int completedCount;
                vector<string> completedCourses;
                cout << "Enter number of completed courses: ";
                cin >> completedCount;

                completedCourses.resize(completedCount);
                for (int i = 0; i < completedCount; ++i) {
                    cout << "Enter completed course " << i + 1 << ": ";
                    cin >> completedCourses[i];
                }

                vector<string> remainingPrereqs;
                for (const string& prereq : prerequisites) {
                    if (find(completedCourses.begin(), completedCourses.end(), prereq) == completedCourses.end()) {
                        remainingPrereqs.push_back(prereq);
                    }
                }

                if (remainingPrereqs.empty()) {
                    cout << "Student is eligible to register for course " << courseID << ".\n";
                } else {
                    cout << "Student is NOT eligible to register for course " << courseID << ".\n";
                    cout << "Remaining prerequisites: ";
                    for (const auto& prereq : remainingPrereqs) {
                        cout << prereq << " ";
                    }
                    cout << endl;
                }

                break;
            }
            case 2: {
                int capacity;
                cout << "Enter course capacity: ";
                cin >> capacity;
        
                int choice;
                cout << "Choose an action:\n";
                cout << "1. Add student to the waitlist\n";
                cout << "2. Enroll student (remove from waitlist)\n";
                cout << "3. Display waitlist\n";
                cout << "4. Exit\n";
                cout << "Enter your choice: ";
                cin >> choice;
            
                switch (choice) {
                    case 1: {
                        int studentID;
                        cout << "Enter student ID to add: ";
                        cin >> studentID;
                        waitlist.enqueue(studentID);
                        break;
                    }
            
                    case 2: {
                        int studentID;
                        cout << "Enter student ID to enroll (remove from waitlist): ";
                        cin >> studentID;
                        waitlist.dequeueByID(studentID);  
                        break;
                    }
            
                    case 3: {
                        waitlist.displayWaitlist();
                        break;
                    }
                    default: {
                        cout << "Invalid choice!\n";
                    }
                }
                break;
            }

            case 3: {
                int choice;

                cout << "Choose an option:\n";
                cout << "1. Add a student\n";
                cout << "2. Delete a student\n";
                cout << "3. Display all students\n";
                cout << "Enter your choice: ";
                cin >> choice;

                if (choice == 1) { 
                    int id;
                    long long phone;
                    string name, address, email, password;

                    cout << "Enter student ID: ";
                    cin >> id;

                    cout << "Enter student phone: ";
                    cin >> phone;

                    cout << "Enter student name: ";
                    cin >> name;

                    cout << "Enter student address: ";
                    cin >> address;

                    cout << "Enter student email: ";
                    cin >> email;

                    cout << "Enter student password: ";
                    cin >> password;

                    studentList.add(id, phone, name, address, email, password);
                } 
                else if (choice == 2) { 
                    int id;

                    cout << "Enter student ID to delete: ";
                    cin >> id;

                    studentList.deletion(id);
                } 
                else if (choice == 3) { 
                    studentList.display();
                } 
                else {
                    cout << "Invalid choice. Please select a valid option.\n";
                }

                break;
            }

            case 4: {
                int choice;
                cout << "Select an option:\n";
                cout << "1. Add a record\n";
                cout << "2. Display all records\n";
                cout << "Enter your choice: ";
                cin >> choice;

                if (choice == 1) {
                    int id;
                    string name;

                    cout << "Enter record ID: ";
                    cin >> id;
                    cout << "Enter record name: ";
                    cin >> name;

                    recordList.addRecord(id, name); 
                } else if (choice == 2) {
                    cout << "Current Records:\n";
                    recordList.displayRecords(); 
                } else {
                    cout << "Invalid option. Please select either 1 or 2.\n";
                }
                break;
            }

            case 5: {
                int id;

                cout << "Enter student ID to search: ";
                cin >> id;
                search.linearSearch(id);
                break;
            }
            case 6: {
                int id;

                cout << "Enter record ID to search: ";
                cin >> id;
                search.binarySearch(recordList.getHead(), id);
                break;
            }
            case 7: {
                int id, credits;
                string name, instructor;

                cout << "Enter course ID: ";
                cin >> id;
                cout << "Enter course name: ";
                cin >> name;
                cout << "Enter course credits: ";
                cin >> credits;
                cout << "Enter course instructor: ";
                cin >> instructor;

                courseRecords.addCourse(id, name, credits, instructor);
                courseRecords.displayCourses();

                cout << "Enter course ID to drop: ";
                cin >> id;
                courseRecords.dropCourse(id);
                courseRecords.displayCourses();
                break;
            }
            case 8: {
                int courseChoice;
                cout << "1. Add Course\n";
                cout << "2. Search Course\n";
                cout << "3. Display All Courses\n";
                cout << "Enter your choice: ";
                cin >> courseChoice;
                cin.ignore();  

                switch (courseChoice) {
                    case 1: {
                        int courseId;
                        string courseName;
                        cout << "Enter course ID: ";
                        cin >> courseId;
                        cin.ignore(); 
                        cout << "Enter course name: ";
                        getline(cin, courseName);  
                        courseHashTable.insertCourse(courseId, courseName);
                        break;
                    }
                    case 2: {
                        int courseId;
                        cout << "Enter course ID to search: ";
                        cin >> courseId;
                        cin.ignore();  
                        vector<string> courses = courseHashTable.searchAllWithHashing(courseId);
                        if (courses.empty()) {
                            cout << "Course not found\n";
                        } else {
                            cout << "Courses found: ";
                            for (const auto& course : courses) {
                                cout << course << " ";
                            }
                            cout << endl;
                        }
                        break;
                    }
                    case 3: {
                        courseHashTable.displayCourses();
                        break;
                    }
                    default: {
                        cout << "Invalid choice!\n";
                    }
                }
                break;
            }

            case 0: {
                running = false;
                cout << "Exiting...\n";
                break;
            }
            default: {
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    }
    return 0;
}