#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

class Student {
private:
    int id;                          // 学号
    std::string name;                // 姓名
    std::string majorName;           // 专业名称
    std::string className;           // 班级
    std::vector<double> grades;       // 3门课成绩
    double averageGrade;              // 平均分
    double credit;                    // 学分

    void calculateAverage();         // 私有函数：计算平均分

public:
    Student();
    Student(int id, const std::string &name, const std::string &majorName, const std::string &className,
            const std::vector<double> &grades, double credit);

    void display() const;            // 显示学生信息

    // Getter 和 Setter
    int getId() const;
    double getAverageGrade() const;
    double getCredit() const;
    std::string getName() const;
    std::string getMajorName() const;
    std::string getClassName() const;
    std::vector<double> getGrades() const;
    void setGrades(const std::vector<double> &grades);
    void setCredit(double credit);
    void setName(const std::string &name);
    void setMajorName(const std::string &majorName);
    void setClassName(const std::string &className);

    // 文件操作
    void saveToFile(std::ofstream &out) const;
    void loadFromFile(std::ifstream &in);
};

#endif // STUDENT_H
