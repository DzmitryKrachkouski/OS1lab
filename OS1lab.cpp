#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

struct employee {
    int num;
    char name[10];
    double hours;
};

void Creator(const std::string& binfilename, int n) {
    FILE* out;
    const char* c = binfilename.c_str();
    out = fopen(c, "wb");
    std::cout << "Введите номер, имя (до 10 символов), часы работы для сотрудника :" << ":\n";
    for (int i = 0; i < n; ++i) {
        employee emp;
        std::cin >> emp.num >> emp.name >> emp.hours;
        fwrite(&emp, sizeof(struct employee), 1, out);
    }
    fclose(out);
}

void Reporter(const std::string& binfilename, const std::string& txtfilename, int m, int n) {

    FILE* in;
    const char* c = binfilename.c_str();
    in = fopen(c, "rb");
    std::ofstream out(txtfilename);

    double z;
    employee emp;
    out << "Отчет о сотрудниках:\n";
    for (int i = 0; i < n; ++i) {
        fread(&emp, sizeof(struct employee), 1, in);
        z = m * emp.hours;
        out << "Номер: " << emp.num << ", Имя: " << emp.name << ", Часы: " << emp.hours << ", Запрлата: " << z << "\n";
    }

    fclose(in);
    out.close();
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::string binfilename;
    int n;
    std::cout << "Введите имя бинарного файла и количество записей в этом файле:\n";
    std::cin >> binfilename >> n;
    Creator(binfilename, n);
    FILE* in;
    const char* c = binfilename.c_str();
    in = fopen(c, "rb");
    employee emp;
    for (int i = 0;i < n;i++) {
        fread(&emp, sizeof(struct employee), 1, in);
        std::cout << "Номер: " << emp.num << ", Имя: " << emp.name << ", Часы: " << emp.hours << "\n";
    }
    int m;
    std::string txtfilename;
    std::cout << "Введите имя текстового файла и оплата за час работы:\n";
    std::cin >> txtfilename >> m;
    Reporter(binfilename, txtfilename, m, n);
    return 0;
}