#include "doctor.h"

Doctor::Doctor(int id, string sp): idDoctor(id), specialty(sp)
{}

int Doctor::getID() const {
	return idDoctor;
}

string Doctor::getSpecialty() const {
	return specialty;
}

queue<Patient> Doctor::getPatientsToAttend() const {
	return toAttend;
}

void Doctor::setSpecialty(string sp) {
    specialty = sp;
};

void Doctor::setPatientsToAttend(queue<Patient> toAtt) {
    toAttend = toAtt;
}

void Doctor::addPatientToAttend(const Patient& p1) {
	toAttend.push(p1);
}


//--------------------------------------------------------------------------

//TODO
void Doctor::moveToFront(int idP) {

}
