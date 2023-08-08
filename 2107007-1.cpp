#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Patient
{
private:
    int id;
    string name;
    int age;

public:
    Patient(int id, string name, int age) : id(id), name(name), age(age) {}

    int getId() const
    {
        return id;
    }
    string getName() const
    {
        return name;
    }
    int getAge() const
    {
        return age;
    }

    friend class PatientList;
};

class Doctor
{
private:
    string name;
    string specialty;

public:
    Doctor(string name, string specialty) : name(name), specialty(specialty) {}

    string getName() const
    {
        return name;
    }
    string getSpecialty() const
    {
        return specialty;
    }

    friend class DoctorList;
};

class Appointment
{
public:
    Patient patient;
    Doctor doctor;
    string appointmentDate;
    string appointmentTime;

    Appointment(Patient patient, Doctor doctor, string date, string time)
        : patient(patient), doctor(doctor), appointmentDate(date), appointmentTime(time) {}

    void displayAppointment() const
{

        cout << "Patient: " << patient.getName() <<"\nDoctor: " << doctor.getName() <<"\nDate: " << appointmentDate << "\nTime: " << appointmentTime << endl;
    }
};

class PatientList
{
private:
    vector<Patient> patients;
    int nextId;

public:
    PatientList() : nextId(1) {}

    void addPatient(string name, int age)
    {
        patients.push_back(Patient(nextId, name, age));
        cout << "Patient " << name << " added with ID: " << nextId << endl;
        nextId++;
    }

    void showAllPatients()
    {
        cout << "Patients list:" << endl;
        for (const auto &patient : patients)
        {
            cout << "ID: " << patient.getId() << ", Name: " << patient.getName() << ", Age: " << patient.getAge() << endl;
        }
    }

     Patient findPatient(int patientId)
    {
        for (const auto &patient : patients)
        {
            if (patient.getId() == patientId)
            {
                return patient;
            }
        }
        return Patient(-1, "", -1);
    }
};

class DoctorList
{
private:
    vector<Doctor> doctors;

public:
    void addDoctor(string name, string specialty)
    {
        doctors.push_back(Doctor(name, specialty));
        cout << "Doctor " << name << " added" << endl;
    }

    void showAllDoctors()
    {
        cout << "Doctors list:" << endl;
        for (const auto &doctor : doctors)
        {
            cout << "Name: " << doctor.getName() << ", Specialty: " << doctor.getSpecialty() << endl;
        }
    }

    Doctor searchDoctor(string doctorName)
    {
        for (const auto &doctor : doctors)
        {
            if (doctor.getName() == doctorName)
            {
                return doctor;
            }
        }
        return Doctor("", "");
    }
};

int main()
{
    PatientList patientList;
    DoctorList doctorList;
    vector<Appointment> appointments;

    int choice;
    do
    {
        cout << "\n**TELEMEDICINE SERVICE**" << endl;
        cout << "-------------------------" << endl;
        cout << "\n";
        cout << "Select your Option:" << endl;
        cout << "1. Create a patient account" << endl;
        cout << "2. Join as a doctor" << endl;
        cout << "3. Show Doctor list" << endl;
        cout << "4. Show Patient details" << endl;
        cout << "5. Log in with patient id" << endl;
        cout << "6. Book Appointment" << endl;
        cout << "7. Scheduled Appointment" << endl;
        cout << "8. Exit" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            string name;
            int age;
            cout << "Enter patient name: ";
            cin >> name;
            cout << "Enter patient age: ";
            cin >> age;
            patientList.addPatient(name, age);
            break;
        }
        case 2:
        {
            string name, specialty;
            cout << "Enter doctor name: ";
            cin>>name;
            cin.ignore();
            cout << "Enter doctor specialty: ";
            getline(cin, specialty);
            doctorList.addDoctor(name, specialty);
            break;
        }
        case 3:
            doctorList.showAllDoctors();
            break;
        case 4:
            patientList.showAllPatients();
            break;
        case 5:
        {
            int ID;
            cout << "Enter patient Id: ";
            cin >> ID;
            Patient patient = patientList.findPatient(ID);
            if (patient.getId() == -1)
            {
                cout << "Patient not found with ID: " << ID << endl;
            }
            else
            {
                cout << "Patient details:" << endl;
                cout << "ID: " << patient.getId() << ", Name: " << patient.getName() << ", Age: " << patient.getAge() << endl;
            }
            break;
        }
        case 6:
        {
            int patientId;
            string doctorName, appointmentDate, appointmentTime;
            cout << "Enter patient Id: ";
            cin >> patientId;
            Patient patient = patientList.findPatient(patientId);
            if (patient.getId() == -1)
            {
                cout << "Patient not found with ID: " << patientId << endl;
                break;
            }

            cin.ignore();
            cout << "Enter doctor name: ";
            getline(cin, doctorName);
            Doctor doctor = doctorList.searchDoctor(doctorName);
            if (doctor.getName() == "")
            {
                cout << "Doctor not found with name: " << doctorName << endl;
                break;
            }

            cout << "Enter appointment date: ";
            getline(cin, appointmentDate);

            cout << "Enter appointment time: ";
            getline(cin, appointmentTime);

            appointments.push_back(Appointment(patient, doctor, appointmentDate, appointmentTime));
            cout << "Appointment booked successfully." << endl;
            cout << "Please complete your payment process" << endl;
            break;
        }
        case 7:
        {
            int patientId;
            cout << "Enter patient Id: ";
            cin >> patientId;
            Patient patient = patientList.findPatient(patientId);
            if (patient.getId() == -1)
            {
                cout << "Patient not found with ID: " << patientId << endl;
                break;
            }

            cout << "Previous booked appointments for patient ID " << patientId << ":" << endl;
            bool foundAppointment = false;
            for (const auto &appointment : appointments)
            {
                if (appointment.patient.getId() == patientId)
                {
                    appointment.displayAppointment();
                    foundAppointment = true;
                }
            }

            if (!foundAppointment)
            {
                cout << "No appointments found for patient ID " << patientId << endl;
            }
            break;
        }
        case 8:
            cout << "Exiting.." << endl;
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 8);

    return 0;
}


