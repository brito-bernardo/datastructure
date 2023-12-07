#include "hospital.h"

Hospital::Hospital() { }

void Hospital::addDoctor(const Doctor& d) {
	doctors.push_back(d);
}

void Hospital::addPatient(const Patient& p) {
    patients.push_back(p);
}

void Hospital::addOldPatient(const Patient& p) {
    oldPatients.insert(p);
}

void Hospital::addStackConsultations(const stack<Consultation>& s) {
    consultations.push_back(s);
}

vector<Doctor> Hospital::getDoctors() const {
	return doctors;
}

list<Patient> Hospital::getPatients() const {
    return patients;
}

set<Patient> Hospital::getOldPatients() const {
    return oldPatients;
}

list<stack<Consultation>> Hospital::getConsultations() const {
    return consultations;
}

void Hospital::setConsultations(const list<stack<Consultation>>& consults) {
    consultations = consults;
}


// --------------------------------------------------------------------

//TODO
void Hospital::sortDoctors()
{
   std::sort(doctors.begin(), doctors.end(), [](const Doctor& a, const Doctor& b){
       if (a.getPatientsToAttend().size() == b.getPatientsToAttend().size())
       {
           return a.getID()< b.getID();
       }
       return a.getPatientsToAttend().size() > b.getPatientsToAttend().size();
   });
}


// TODO
float Hospital::averageNPatients(string sp) const
{
    int totalPatients = 0;
    int countDoctors = 0;
    float avg = 0.0;

    for(const Doctor& doc: doctors)
    {
        if (doc.getSpecialty() == sp)
        {
            totalPatients += doc.getPatientsToAttend().size();
            countDoctors++;
        }
    }
    if (countDoctors == 0) return 0.0;
    avg = totalPatients/countDoctors;
    return avg;


}

// TODO
int Hospital::removePatients(int minC)
{
    int removedPatients = 0;

    for (auto it = patients.begin(); it != patients.end(); ) {
        if (it->getNumConsultations() < minC) {
            it = patients.erase(it);
            removedPatients++;
        } else {
            ++it;
        }
    }
    return removedPatients;
}


// TODO
vector<Patient> Hospital::getOldPatients(int y) const {
    vector<Patient> res;
    return res;
}


// TODO
void Hospital::processConsultation(Consultation c) {

}


// TODO
bool Hospital::addDoctor(int id2, string sp2, int id1) {
    return true;
}
