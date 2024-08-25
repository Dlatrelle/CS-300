
# include <iostream>
# include <iomanip>
# include <string>
# include <vector>
# include <sstream>
# include <fstream>

using namespace std;

///--------------
/// Course Struct
///--------------
struct Course {
    string courseNum;
    string courseName;

    vector<string> PreReqs;


    Course() {};
   
    Course(string aCourseNum, string aCourseName) {
        courseNum = aCourseNum;
        courseName = aCourseName;
    }
 
    Course(string aCourseNum, string aCourseName, vector<string> prereqs) {
        courseNum = aCourseNum;
        courseName = aCourseName;
        vector<string> PreReqs = prereqs;
    }
};

///------------
/// Node Struct
///------------
struct Node {
    Course course;
    Node* left;
    Node* right;

    //default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    Node(Course acourse) : Node() {
        this->course = acourse;
    }
};

///-----------
/// BST Class
///-----------
class BST {
private:
    Node* root;
    void addNode(Course acourse, Node* node);
    void inOrder(Node* node);
    void printCourse(Node* node, string courseNum);

public:
    BST();
    void InOrder();
    void PrintCourse(string courseNum);
    bool loadData();
    bool validatePreReqs(Course course);
    void insert(Course course);
};


BST::BST() {
    root = nullptr;
}

void BST::InOrder() {
    this->inOrder(root);
}

void BST::PrintCourse(string courseNum) {
    this->printCourse(root, courseNum);
}

///------------------
/// Insert a New Node
///------------------
void BST::insert(Course course) {
    if (root == nullptr) {
        root = new Node(course);
    }
    else {
        this->addNode(course, root);
    }
}

///-----------------
/// Add Node to Tree
///-----------------
void BST::addNode(Course acourse, Node* node) {

    if (node->course.courseNum.compare(acourse.courseNum) > 0) {
       
        if (node->left == nullptr) {
            node->left = new Node(acourse);
        }
       
        else {
            this->addNode(acourse, node->left);
        }
    }
    else {
        if (node->right == nullptr) {
            node->right = new Node(acourse);
        }
        else {
            this->addNode(acourse, node->right);
        }
    }
}

///--------------------------------
/// Print Courses In Order: private
///--------------------------------
void BST::inOrder(Node* node) {

    if (node != nullptr) {
        inOrder(node->left);
        cout << "Course Number: " << node->course.courseNum;
        cout << " Course Name: " << node->course.courseName;
        cout << " Prerequisite(s): ";
        for (int i = 0; i < node->course.PreReqs.size(); ++i) {
            cout << node->course.PreReqs[i] << " ";
        }
        if (node->course.PreReqs.size() == 0) {
            cout << "None";
        }
        cout << "\n";

        inOrder(node->right);
    }
    return;
}

///---------------------------------
/// Print Individual Course: private
///---------------------------------
void BST::printCourse(Node* node, string courseNum) {

    while (node != nullptr) {
        if (node->course.courseNum.compare(courseNum) == 0) {
            cout << "Course Number: " << node->course.courseNum;
            cout << "  Course Name: " << node->course.courseName;
            cout << "  Prerequisite(s): ";
            for (int i = 0; i < node->course.PreReqs.size(); ++i) {
                cout << node->course.PreReqs[i] << " ";
            }

            if (node->course.PreReqs.size() == 0) {
                cout << "None";
            }
            cout << "\n";
            return;
        }

        else if (node->course.courseNum.compare(courseNum) > 0 && node->left != nullptr) {
            node = node->left;
        }
    
        else if (node->course.courseNum.compare(courseNum) < 0 && node->right != nullptr) {
            node = node->right;
        }
        else {
            cout << "Course not found \n";
            return;
        }
    }

    if (root == nullptr) {
        cout << "Error \n";
        return;
    }
}


///------------------------------------------------------
///Load Data (from file into bst)
///------------------------------------------------------
bool BST::loadData() {


    ifstream file;
    file.open("CS 300 ABCU_Advising_Program_Input.txt");

    if (file.is_open()) {
      
        while (!file.eof()) {
        
            vector<string> courseLine;
          
            string line;

           
            getline(file, line);
          
            while (line.length() > 0) {
                unsigned int delim = line.find(',');
               
                if (delim < 100) {
             
                    courseLine.push_back(line.substr(0, delim));
                    line.erase(0, delim + 1);
                }
            
                else {
                    courseLine.push_back(line.substr(0, line.length()));
                    line = "";
                }
            }

            Course course;
            
            course.courseNum = courseLine[0];
            course.courseName = courseLine[1];
           
            for (unsigned int i = 2; i < courseLine.size(); i++) {
                course.PreReqs.push_back(courseLine[i]);
            }
           
            insert(course);
        }
        return true;
    }
    if (!file) {
        cout << "Error \n";
        return false;
    }
    file.close();
}

bool BST::validatePreReqs(Course course) {
   
    Node* current = root;
    if (current->course.PreReqs.size() > 0) {
       
        for (int i = 0; i < course.PreReqs.size(); i++) {
            while (current != nullptr) {
               
                if (course.PreReqs[i] == current->course.courseNum) {
                    return true;
                }
           
                else if (course.PreReqs[i].compare(current->course.courseNum) > 0 && current->left != nullptr) {
                    current = current->left;
                }
              
                else if (course.PreReqs[i].compare(current->course.courseNum) < 0 && current->right != nullptr) {
                    current = current->right;
                }
                
                else {
                    cout << "Prerequisite not found. \n";
                    return false;
                }
            }
        }
    }
    else {
     
        return true;
    }
}

int main()
{
   
    BST* bst = new BST();
 
    string courseNum;
   
    int choice = 0;

    cout << "Welcome to the course schedule! \n\n";

    while (choice != 4) {
      
        cout << "MENU\n";
        cout << "1 - Load Data Structure\n";
        cout << "2 - Print Course List\n";
        cout << "3 - Print Course\n";
        cout << "9 - Exit\n";
        cout << "Please select an option: ";
        cin >> choice;

        switch (choice) {
         
        case 1:
            bst->loadData();
            break;
            
        case 2:
            cout << "\nHere is the schedule: \n";
       
            bst->InOrder();
            cout << "\n";
            break;
            
        case 3:
            cout << "Please enter the course number you would like to search: ";
            cin >> courseNum;
            bst->PrintCourse(courseNum);
            cout << "\n";
            break;
         
        case 9:
            cout << "\n Good bye!\n";
          
        }
    }
    return 0;
}

