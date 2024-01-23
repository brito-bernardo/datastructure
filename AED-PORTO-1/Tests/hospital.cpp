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

bool compare(const Doctor &a, const Doctor &b)
{
    if (a.getPatientsToAttend().size() == b.getPatientsToAttend().size())
    {
        return a.getID() < b.getID();
    }

    return a.getPatientsToAttend().size() > b.getPatientsToAttend().size();
}

//TODO
void Hospital::sortDoctors()
{
    sort(doctors.begin(),doctors.end(),compare);
}

// TODO
float Hospital::averageNPatients(string sp) const
{
    int sum = 0;
    int countDoc = 0;

    for (int i = 0; i < doctors.size(); i++)
    {
        if (doctors[i].getSpecialty() == sp)
        {
            sum += doctors[i].getPatientsToAttend().size();
            countDoc++;
        }
    }

    if (countDoc == 0){
        return 0.0;
    }
    else{
        return sum/countDoc;
    }
}


// TODO
int Hospital::removePatients(int minC)
{
    int count = 0;
    for(auto it = patients.begin(); it != patients.end();)
    {
        if (it->getNumConsultations() < minC)
        {
            it = patients.erase(it);
            count++;
        }
        else
        {
            it++;
        }
    }
    return count;
}

// TODO
vector<Patient> Hospital::getOldPatients(int y) const {
    vector<Patient> res;
    for(auto paciente: oldPatients)
    {
        if (paciente.getLastConsultationYear() < y)
        {
            res.push_back(paciente);
        }
    }

    return res;
}


// TODO
void Hospital::processConsultation(Consultation c) {

}


// TODO
bool Hospital::addDoctor(int id2, string sp2, int id1) {
    return true;
}
