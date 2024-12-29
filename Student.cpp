#include "Student.h"

// 构造函数
Student::Student() : id(0), grades(3, 0.0), averageGrade(0.0), credit(0.0) {}

Student::Student(int id, const std::string &name, const std::string &majorName,
                 const std::string &className, const std::vector<double> &grades, double credit)
    : id(id), name(name), majorName(majorName), className(className), grades(grades), credit(credit) {
    calculateAverage();
}

// 计算平均分
void Student::calculateAverage() {
    double sum = 0.0;
    for (double grade : grades) {
        sum += grade;
    }
    averageGrade = grades.empty() ? 0.0 : sum / grades.size();
}

// 显示学生信息
void Student::display() const {
    std::cout << "ID: " << id << "\nName: " << name
              << "\nMajor: " << majorName << "\nClass: " << className
              << "\nGrades: ";
    for (double grade : grades) {
        std::cout << grade << " ";
    }
    std::cout << "\nAverage Grade: " << std::fixed << std::setprecision(2) << averageGrade
              << "\nCredit: " << credit << "\n" << std::endl;
}

// Getter 和 Setter 实现
int Student::getId() const {
    return id;
}

double Student::getAverageGrade() const {
    return averageGrade;
}

double Student::getCredit() const {
    return credit;
}

std::string Student::getName() const {
    return name;
}

std::string Student::getMajorName() const {
    return majorName;
}

std::string Student::getClassName() const {
    return className;
}

std::vector<double> Student::getGrades() const {
    return grades;
}

void Student::setGrades(const std::vector<double> &grades) {
    this->grades = grades;
    calculateAverage();
}

void Student::setCredit(double credit) {
    this->credit = credit;
}

void Student::setName(const std::string &name) {
    this->name = name;
}

void Student::setMajorName(const std::string &majorName) {
    this->majorName = majorName;
}

void Student::setClassName(const std::string &className) {
    this->className = className;
}

// 保存到文件
void Student::saveToFile(std::ofstream &out) const {
    out << id << '\n' << name << '\n' << majorName << '\n' << className << '\n';
    for (double grade : grades) {
        out << grade << " ";
    }
    out << '\n' << credit << '\n';
}

// 从文件加载
void Student::loadFromFile(std::ifstream &in) {
    grades.resize(3);
    in >> id;
    in.ignore();
    std::getline(in, name);
    std::getline(in, majorName);
    std::getline(in, className);
    for (double &grade : grades) {
        in >> grade;
    }
    in >> credit;
    calculateAverage();
}
