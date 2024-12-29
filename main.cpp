#include <algorithm>
#include "Student.h"
#include <map>
#include <fstream>
#include <iostream>
/*说明
 * Github仓库地址：github.com/Ethanol14514/Design-StudentManage
 * 欢迎Star
 * 提issue基本不看
 */
/*更新日志
 *1. Student类添加展示平均成绩等等的函数成员
 *2. 添加删除前二次确认
 *3. 添加排序功能（按学号、平均成绩、学分）
 *4. 添加已删除的信息文件（即删除后的备份）
 */

using namespace std;


void simpleDisplay(map<int, Student> &students) {
    cout << "\n === Students List === " << endl;
    for (const auto &entry : students) {
        cout << "ID: " << entry.first << ", Name: " << entry.second.getName() <<endl;
    }
}
// 添加学生
void addStudent(map<int, Student> &students) {
    int id;
    string name, majorName, className;
    vector<double> grades(3);
    double credit;

    cout << "Enter ID: ";
    cin >> id;
    if (students.find(id) != students.end()) {
        cout << "Error: A student with this ID already exists!" << endl;
        return;
    }

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Major Name: ";
    getline(cin, majorName);
    cout << "Enter Class Name: ";
    getline(cin, className);
    cout << "Enter 3 grades: ";
    for (double &grade : grades) {
        cin >> grade;
    }
    cout << "Enter Credit: ";
    cin >> credit;

    students[id] = Student(id, name, majorName, className, grades, credit);
    cout << "Student added successfully!" << endl;
}

// 查找学生
void searchStudent(const map<int, Student> &students, int id) {
    auto it = students.find(id);
    if (it == students.end()) {
        cout << "Student with ID " << id << " not found!" << endl;
    } else {
        it->second.display();
    }
}

// 排序
void sortStudent(map<int, Student> &students) {
    if (students.empty()) {
        cout << "There is no student to sort!" << endl;
        return;
    }
    vector<pair<int, Student>> studentList(students.begin(), students.end());
    cout << "Which method would you like to sort?" << endl;
    cout << "[A] By average grade\n[I] By ID\n[C] By credit\nChoose one:";
    char choice;
    cin >> choice;
    switch (choice) {
        case 'A':
        case 'a': {
            sort(studentList.begin(), studentList.end(),
                [](const pair<int, Student> &a, const pair<int, Student> &b) {
                return a.second.getAverageGrade() > b.second.getAverageGrade();
            });
            cout << "\n === Students sorted by Average grade ===" << endl;
            break;
        }
        case 'I':
        case 'i': {
            sort(studentList.begin(), studentList.end(),[](const pair<int, Student> &a, const pair<int, Student> &b) {
                return a.second.getId() > b.second.getId();
            });
            cout << "\n === Students sorted by ID ===" << endl;
            break;
        }
        case 'C':
        case 'c': {
            sort(studentList.begin(), studentList.end(),[](const pair<int, Student> &a, const pair<int, Student> &b) {
                return a.second.getCredit() > b.second.getCredit();
            });
            cout << "\n === Students sorted by Credit ===" << endl;
            break;
        }
        default: {
            cout << "Invalid Choice!" << endl;
        }
    }

    for (const auto &entry : studentList) {
        entry.second.display();
    }
}
// 删除学生
void deleteStudent(map<int, Student> &students) {
    if (students.empty()) {
        cout << "There is no student to delete!" << endl;
        return;
    }
    simpleDisplay(students);
    int id;
    cout << "Enter ID: ";
    cin >> id;
    auto it = students.find(id);
    if (it == students.end()) {
        cout << "Student with ID " << id << " not found!" << endl;
    }
    else {
        cout << "Do you really want to delete [Y/n]?";
        char answer;
        cin >> answer;
        if (answer == 'Y' || answer == 'y') {
            ofstream deletedFile("Deletion.txt",ios::app);
            if (deletedFile.is_open()) {
                deletedFile << "Deleted Student:" << endl;
                deletedFile << "ID: " << it->first << endl;
                deletedFile << "Name: " << it->second.getName() << endl;
                deletedFile << "Major: " << it->second.getMajorName() << endl;
                deletedFile << "Class: " << it->second.getClassName() << endl;
                deletedFile << "Grades: ";
                for (const auto &grade : it->second.getGrades()) {
                    deletedFile << grade << " ";
                }
                deletedFile << endl;
                deletedFile << "Average grade: " << it->second.getAverageGrade() << endl;
                deletedFile << "------------------------------------------------------" << endl;
                deletedFile.close();
                cout << "Student's information has been saved to Deletion.txt" << endl;
            }
            else {
                cerr << "Error opening file!" << endl;
            }
            if (students.erase(id)) {
                cout << "Student with ID " << id << " deleted successfully ." << endl;
            } else{
                cout << "Student with ID " << id << " not found!" << endl;
            }
        }
        else {
            cout << "Operation aborted.\n";
        }
    }

}

// 修改学生信息
void modifyStudent(map<int, Student> &students) {
    simpleDisplay(students);
    int id;
    cout << "Enter ID: ";
    cin >> id;
    auto it = students.find(id);
    if (it == students.end()) {
        cout << "Student with ID " << id << " not found!" << endl;
        return;
    }

    Student &student = it->second;
    int choice;
    cout << "1. Modify Name\n2. Modify Major Name\n3. Modify Class Name\n4. Modify Grades\n5. Modify Credit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1: {
            cout << "Current Name: " << student.getName() << endl;
            string name;
            cout << "Enter new Name: ";
            cin.ignore();
            getline(cin, name);
            student.setName(name);
            break;
        }
        case 2: {
            cout << "Current Major Name: " << student.getMajorName() << endl;
            string majorName;
            cout << "Enter new Major Name: ";
            cin.ignore();
            getline(cin, majorName);
            student.setMajorName(majorName);
            break;
        }
        case 3: {
            cout << "Current Class Name: " << student.getClassName() << endl;
            string className;
            cout << "Enter new Class Name: ";
            cin.ignore();
            getline(cin, className);
            student.setClassName(className);
            break;
        }
        case 4: {
            cout << "Current Grades: ";
            for (const auto &grade : student.getGrades()) {
                cout << grade << " ";
            }
            vector<double> grades(3);
            cout << "Enter 3 new grades: ";
            for (double &grade : grades) {
                cin >> grade;
            }
            student.setGrades(grades);
            break;
        }
        case 5: {
            cout << "Current Credit: " << student.getCredit() << endl;
            double credit;
            cout << "Enter new Credit: ";
            cin >> credit;
            student.setCredit(credit);
            break;
        }
        default:
            cout << "Invalid choice!" << endl;
    }
}

// 显示所有学生
void displayStudents(const map<int, Student> &students) {
    if (students.empty()) {
        cout << "No students to display!" << endl;
    } else {
        for (const auto &entry : students) {
            entry.second.display();
        }
    }
}

// 保存到文件
void saveToFile(const map<int, Student> &students, const string &filename) {
    ofstream out(filename);
    if (!out) {
        cerr << "Error: Unable to open file for saving!" << endl;
        return;
    }
    out << students.size() << '\n';
    for (const auto &entry : students) {
        entry.second.saveToFile(out);
    }
    out.close();
    cout << "Data saved to " << filename << "!" << endl;
}

// 加载文件
void loadFromFile(map<int, Student> &students, const string &filename) {
    ifstream in(filename);
    if (!in) {
        cerr << "Error: Unable to open file for loading!" << endl;
        return;
    }
    size_t count;
    in >> count;
    in.ignore();
    for (size_t i = 0; i < count; ++i) {
        Student student;
        student.loadFromFile(in);
        students[student.getId()] = student;
    }
    in.close();
    cout << "Data loaded from " << filename << "!" << endl;
}

// 主函数
int main() {
    map<int, Student> students;
    string filename = "students.txt";

    loadFromFile(students, filename);

    while (true) {
        cout << "\n=== Student Management System ===" << endl;
        cout << "[A] Add Student\n[L] List All Students\n[F] Find Student\n[D] Delete Student\n";
        cout << "[M] Modify Student\n[S] Sort\n[Q] Save and Exit\n";
        cout << "Enter your choice: ";
        char choice;
        cin >> choice;
        system("cls");
        switch (choice){
            case 'A':
            case 'a': {
                addStudent(students);
                saveToFile(students, "students.txt");
                break;
            }
            case 'L':
            case 'l': {
                displayStudents(students);
                break;
            }
            case 'F':
            case 'f': {
                int id;
                cout << "Enter ID to search: ";
                cin >> id;
                searchStudent(students, id);
                break;
            }
            case 'D':
            case 'd': {
                deleteStudent(students);
                saveToFile(students, "students.txt");
                break;
            }
            case 'M':
            case 'm': {
                modifyStudent(students);
                saveToFile(students, "students.txt");
                break;
            }
            case 'S':
            case 's': {
                sortStudent(students);
                saveToFile(students, "students.txt");
                break;
            }
            case 'Q':
            case 'q': {
                goto end;
            }
            default:{
                cout << "Invalid choice!" << endl;
            }
        }
        system("pause");
        system("cls");
    }
end:
    return 0;
}
