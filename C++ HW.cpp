#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Applier {
public:
    string _name = "";
    int _age = 0;
    string _speciality = "";
    string _text = "";

    Applier(string name, int age, string speciality, string text)
        : _name(name), _age(age), _speciality(speciality), _text(text) {}
};

class Company {
    vector<Applier*> appliers;

public:
    void hireUp(Applier* cv) {
        appliers.push_back(cv);
    }

    void showAllCV() {
        for (const auto& applier : appliers) {
            cout << "Ad: " << applier->_name << ", Yas: " << applier->_age
                << ", Sahe: " << applier->_speciality << ", Haqqinda: " << applier->_text << endl;
        }
    }

    void writeToFile(string filename) {
        ofstream file(filename, ios::out);
        if (!file) {
            cout << "File acilmadi." << endl;
            return;
        }

        for (const auto& applier : appliers) {
            file << applier->_name << ' ' << applier->_age << ' '
                << applier->_speciality << ' ' << applier->_text << '\n';
        }

        file.close();
    }

    void readToFile(string filename) {
        ifstream file(filename, ios::in);
        if (!file) {
            cout << "File acilmadi." << endl;
            return;
        }

        string name, speciality, text;
        int age;

        while (file >> name >> age >> speciality >> text) {
            Applier* cv = new Applier(name, age, speciality, text);
            appliers.push_back(cv);
        }

        file.close();
    }

    ~Company() {
        for (auto& cv : appliers) {
            delete cv;
        }
    }
};

int main() {
    Applier* cv1 = new Applier("Ceyhun", 18, "IT", "Empty1");
    Applier* cv2 = new Applier("Sebine", 17, "Designer", "Empty2");

    Company company;
    company.hireUp(cv1);
    company.hireUp(cv2);

    company.writeToFile("company.txt");
    company.readToFile("company.txt");
    company.showAllCV();

    delete cv1;
    delete cv2;

    return 0;
}