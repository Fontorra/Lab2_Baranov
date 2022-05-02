#pragma once
#include <iostream>
#include <time.h>

#define PersonID char*

class Student {
private:
	PersonID id = 0;
	char* firstName = nullptr;
	char* middleName = nullptr;
	char* lastName = nullptr;
	time_t person8te = 0;
	char* Group = nullptr;

public:

	Student() {
		
	}

	Student(PersonID id, char* firstName, char* middleName, char* lastName, time_t person8te, char* Group) {
		this->id = id;
		this->firstName = firstName;
		this->middleName = middleName;
		this->lastName = lastName;
		this->person8te = person8te;
		this->Group = Group;
	}

	PersonID GetID() {
		return id;
	}

	char* GetFirstName() {
		return firstName;
	}

	char* GetMiddleName() {
		return middleName;
	}

	char* GetLastName() {
		return lastName;
	}

	time_t GetPerson8te() {
		return person8te;
	}
	char* GetGroup() {
		return Group;

	}

	bool operator ==(Student& person) {
		if (this->id = person.id,
			this->firstName = person.firstName,
			this->middleName = person.middleName,
			this->lastName = person.lastName,
			this->person8te = person.person8te,
			this->Group == person.Group) return true;
		return false;
	}

	bool operator != (Student& student) {
		return !(*this == student);
	}
};

class Teacher{
private:
	PersonID id = 0;
	char* firstName = nullptr;
	char* middleName = nullptr;
	char* lastName = nullptr;
	time_t person8te = 0;
	char* Subject = nullptr;

public:

	Teacher() {
		
	}

	Teacher(PersonID id, char* firstName, char* middleName, char* lastName, time_t person8te, char* Subject) {
		this->id = id;
		this->firstName = firstName;
		this->middleName = middleName;
		this->lastName = lastName;
		this->person8te = person8te;
		this->Subject= Subject;
	}

	PersonID GetID() {
		return id;
	}

	char* GetFirstName() {
		return firstName;
	}

	char* GetMiddleName() {
		return middleName;
	}

	char* GetLastName() {
		return lastName;
	}

	time_t GetPerson8te() {
		return person8te;
	}
	char* GetSubject() {
		return Subject;

	}

	bool operator ==(Teacher& person) {
		if (this->id = person.id,
			this->firstName = person.firstName,
			this->middleName = person.middleName,
			this->lastName = person.lastName,
			this->person8te = person.person8te,
			this->Subject == person.Subject) return true;
		return false;
	}

	bool operator != (Teacher& teacher) {
		return !(*this == teacher);
	}
};


class Complex {
private:

	double Re = 0;
	double Im = 0;

public:

	Complex(double Re, double Im) {
		this->Re = Re;
		this->Im = Im;
	}

	Complex() {

		this->Re = 0;
		this->Im = 0;
	
	}

	Complex& operator = (Complex & complex) {
		this->Re = complex.Re;
		this->Im = complex.Im;
		return (*this);
	}

	double GetRe() {
		return Re;
	}

	double GetIm() {
		return Im;
	}

	void Set(double Re, double Im) {
		this->Re = Re;
		this->Im = Im;
	}


	bool operator == (const Complex& complex) {
		if (Re == complex.Re && Im == complex.Im) return true;
		return false;
	}

	bool operator != (const Complex& complex) {
		return !(*this == complex);
	}

	std::ostream& operator<< (std::ostream& os) {
		return os << "Re = "  << Re << "Im = " << Im << std::endl;
	}

};
