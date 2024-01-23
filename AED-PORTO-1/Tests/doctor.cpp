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
void Doctor::moveToFront(int idP)
{
     Patient paciente(idP);
     queue<Patient> aux;
     bool find = false;

     while(!toAttend.empty())
     {
         Patient pt = toAttend.front();
         if (pt.getID() == idP)
         {
             find = true;
         }
         else
         {
             aux.push(pt);
         }
         toAttend.pop();
     }

    if (find)
    {
        toAttend.push(paciente);
    }

    while (!aux.empty())
    {
        toAttend.push(aux.front());
        aux.pop();
    }

}
