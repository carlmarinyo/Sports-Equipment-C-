#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
class Customer;
class SportsEquipment {

	vector<int> EquipmentId;
	vector<string>EquipmentName;
	vector<string>Type;
	vector<string>Brand;              //datas for sports equipment
	vector<int>NumberofCopies;
	int lastId;
	
	//value holder for loading data on the customer adt
	vector<int> CustomerId;
	vector<string> Name;
	vector<string> Address;

public:
	SportsEquipment() {
		loadFile("equipment.txt");
		if (EquipmentId.empty()) {
			lastId = 0;
		}
		else {
			lastId = EquipmentId.back();
		}
		loadCustomer("customer.txt");
	}

	void insertEquipment() {
		system("cls");
		cout << "[1]New Sports Equipment\n\n";
		lastId++;
		int copy;
		string name, type, brand;
		cout << "Equipment ID: " << lastId << endl;
		cout << "Equipment Name: ";
		cin.ignore();
		getline(cin, name);
		cout << "Type: ";
		getline(cin, type);
		cout << "Brand: ";
		getline(cin, brand);
		cout << "Number of copies: ";
		cin >> copy;
		cin.ignore();
		cout << endl;
		EquipmentId.push_back(lastId);
		EquipmentName.push_back(name);
		Type.push_back(type);
		Brand.push_back(brand);
		NumberofCopies.push_back(copy);
		saveFile("equipment.txt");
	}

  void RentEquipment() {
        system("cls");
        
        cout << "[2] Rent a Sports Equipment\n\n";
        char choice;
        do {
        	
            int rentId,cId;
            cout<<"Customer Id: ";
            cin>>cId;
            bool cfound = false;
            for (int i = 0; i < CustomerId.size();i++) {
            	if (cId == CustomerId[i]) {
            		cout<<"Name: "<<Name[i]<<endl;
            		cout<<"Address: "<<Address[i]<<endl;
				}
				
			}
			
			
			
			
			
            cout << "Sports Equipment ID: ";
            cin >> rentId;
            bool found = false;

            for (int i = 0; i < EquipmentId.size(); i++) {
                if (rentId == EquipmentId[i]) {
                    found = true;
                    if (NumberofCopies[i] == 0) {
                        cout << "No more copies for this Sports Equipment.";
                    } else {
                        cout << "Equipment Name: " << EquipmentName[i];
                        NumberofCopies[i]--;
                        cout << "\nNumber of Copies: " << NumberofCopies[i];
                        saveFile("equipment.txt");

                        // Record rental in customer's rental history
                        RecordRental(cId, rentId);

                        break;
                    }
                }
            }

            if (!found) {
                cout << "Equipment with ID " << rentId << " not found.\n";
            }

            cout << "\nRent another Equipment? (Y/N): ";
            cin >> choice;
            cout << endl;
        } while (choice == 'Y' || choice == 'y');
    }

     
    void RecordRental(int customerId, int equipmentId) {
        // Append customerId and equipmentId to a text file or database for rental history
        ofstream rentalFile("customer-rent.txt", ios::app);
        if (rentalFile.is_open()) {
            rentalFile << customerId << " " << equipmentId << endl;
            rentalFile.close();
        } else {
            cout << "Unable to record rental history." << endl;
        }
    }
    
    
	void showEquipmentDetails() {
		ifstream inFile("equipment.txt");
		if (inFile.is_open()) {
			int id, copy, searchID;
			string name, type, brand;
			bool found = false;
			cout << "Equipment ID: ";
			cin >> searchID;
			while (inFile >> id >> name >> type >> brand >> copy) {
				if (searchID == id) {
					cout << "\n\t\t\tSports Equipment Details\n\n";
					cout << "ID\tName\t\tType\t\tBrand\t\tCopies\n";
					cout << id << "\t" << name << "\t\t" << type << "\t\t" << brand << "\t\t" << copy << endl << endl;
					found = true;
					break;
				}
			}
			if (found == false) {
				cout << "Sports Equipment ID: " << searchID << " not found\n\n";
			}
			inFile.close();
		}
		else {
			cout << "Can't Open file'" << endl;
		}
	}

	void displayAllEquipment() {
	  for (size_t i = 0; i < EquipmentId.size(); ++i) {
            cout << EquipmentId[i] << "\t"
                 << EquipmentName[i] << "\t\t"
                 << Type[i] << "\t\t"
                 << Brand[i] << "\t\t"
                 << NumberofCopies[i] << endl << endl;
        }
	}

	void CheckAvailability() {
		ifstream inFile("equipment.txt");
		if (inFile.is_open()) {
			int id, copy, searchID;
			string name, type, brand;
			bool found = false;
			cout << "Video ID: ";
			cin >> searchID;
			while (inFile >> id >> name >> type >> brand >> copy) {
				if (searchID == id) {
					cout << "\n\t\t\tCheck Availability of Sports Equipment\n\n";
					cout << "ID\tName\t\tType\t\tBrand\t\tCopies\t\tAvailability\n";
					cout << id << "\t" << name << "\t\t" << type << "\t\t" << brand << "\t\t" << copy;
					if (copy == 0) {
						cout << "\t\tUnavailable\n\n";
					}
					else {
						cout << "\t\tAvailable\n\n";
					}
					found = true;
					break;
				}

			}
			if (found == false) {
				cout << "Sports Equipment ID: " << searchID << " not found\n\n";
			}
			inFile.close();
		}
		else {
			cout << "Can't Open file'" << endl;
		}
	}
	


	void saveFile(const string& filename) {
		ofstream outFile(filename);
		if (outFile.is_open()) {
			for (size_t i = 0; i < EquipmentId.size(); ++i) {
				outFile << EquipmentId[i] <<endl
					<< EquipmentName[i] <<endl
					<< Type[i] <<endl
					<< Brand[i] <<endl
					<< NumberofCopies[i] <<endl<< endl;
			}
			outFile.close();
		}
		else {
			cout << "File might not be existing or cannot be accessed." << endl;
		}
	}
	
	void loadCustomer(const string& filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        CustomerId.clear();
        Name.clear();
        Address.clear();
        
        int id;
        string name, address;
        while (inFile >> id) {
            inFile.ignore(); // Consume newline after id
            getline(inFile, name); // Read name
            getline(inFile, address); // Read address
            
            CustomerId.push_back(id);
            Name.push_back(name);
            Address.push_back(address);
            
            // Skip blank line separator if present
            string line;
            getline(inFile, line);
        }
        inFile.close();
    } else {
        cout << "Unable to open file: " << filename << endl;
    }
}

	void loadFile(const string& filename) {
		ifstream inFile(filename);
		if (inFile.is_open()) {
			EquipmentId.clear();
			EquipmentName.clear();
			Type.clear();
			Brand.clear();
			NumberofCopies.clear();
			
			int id, copy;
			string name, type, brand;
			
			while (inFile >> id) {
				inFile.ignore();
				getline(inFile, name);
				getline(inFile, type);
				getline(inFile, brand);
				 inFile >> copy;
				 
				EquipmentId.push_back(id);
				EquipmentName.push_back(name);
				Type.push_back(type);
				Brand.push_back(brand);
				NumberofCopies.push_back(copy);
			
			}
			inFile.close();
		}
		else {
			cout << "Unable to open file: " << filename << endl;
		}
	}
	
	
	bool isEmpty() {
		bool n = true;
		if (!EquipmentId.size()) {
			return true;
		}
		else {
			return false;
		}
	}


};

class Customer {
	vector <int> CustomerId;
	vector <string>Name;
	vector <string>Address;
	int lastId;
	public:
			Customer() {
			 loadFile("customer.txt");
			if(CustomerId.empty()) {
				lastId = 0;
			}
			
			else {
				lastId = CustomerId.back();
			}
		}
			void addCustomer() {
		system("cls");
	   	cout<<"[7-1]Add New Customer\n\n";
		lastId++;
		string name, address;
		cout<<"Customer ID: "<<lastId<<endl;
		cout<<"Customer Name: ";
		cin.ignore();
		getline(cin,name);
		cout<<"Customer Address: ";
		getline(cin,address);
		cout<<endl;
	    CustomerId.push_back(lastId);
		Name.push_back(name);
		Address.push_back(address);
		saveFile("customer.txt");
		cout<<"Succesfully added Customer "<<lastId<<endl;
			}
			
		void showDetails() {
			system("cls");
			cout<<"[7-2]Show the Customer details\n\n";
			int search;
			cout<<"Customer ID: ";
			cin>>search;
			search;
			bool found = false;
			for (int i = 0; i < CustomerId.size();i++) {
			if (search == CustomerId[i]) {
				found = true;
				cout<<"Name: "<<Name[i];
				cout<<"\nAddress: "<<Address[i];
				cout<<endl<<endl;
				break;
			}
			}
			
			if (!found) {
				cout<<"Customer ["<<search<<"] is not existing and cannot be found.\n\n";
			}
			
		}
			void displayAllCustomers() {
				cout<<"\nAll Customers\n";
	for (size_t i = 0; i < CustomerId.size(); ++i) {
            cout << CustomerId[i] << "\t"
                 << Name[i] << "\t\t"
                 << Address[i] << "\t\t"<<endl;
        }
	}
			
			
			bool customerExists(int customerId) {
        for (int i = 0; i < CustomerId.size(); ++i) {
            if (CustomerId[i] == customerId) {
                return true;
            }
        }
        return false;
    }
			 void listRentedVideos(int customerId) {
        // Implementation to list rented videos
    }
			
			
			
	//File handling & extra functions
void saveFile(const string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (size_t i = 0; i < CustomerId.size(); ++i) {
            outFile << CustomerId[i] << endl
                    << Name[i] << endl
                    << Address[i] << endl
                    << endl; // Blank line as separator between customers
        }
        outFile.close();
    } else {
        cout << "Unable to open file: " << filename << endl;
    }
}
        
        
 void loadFile(const string& filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        CustomerId.clear();
        Name.clear();
        Address.clear();
        
        int id;
        string name, address;
        while (inFile >> id) {
            inFile.ignore(); // Consume newline after id
            getline(inFile, name); // Read name
            getline(inFile, address); // Read address
            
            CustomerId.push_back(id);
            Name.push_back(name);
            Address.push_back(address);
            
            // Skip blank line separator if present
            string line;
            getline(inFile, line);
        }
        inFile.close();
    } else {
        cout << "Unable to open file: " << filename << endl;
    }
}
    
    
};

int main(int argc, char** argv) {
	system("cls");
	SportsEquipment sport;
	Customer customer;
	int choice;

	do {
		cout
			<< "\nSports Equipment Rental System\n"
			<< "[1]New Sports Equipment\n"
			<< "[2]Rent a Sports Equipment\n"
			<< "[3]Return a Sports Equipment\n"
			<< "[4]Show Sports Equipment Details\n"
			<< "[5]Display All Sports Equipment\n"
			<< "[6]Check Sports Equipment Availability\n"
			<< "[7]Customer Maintenance\n"
			<< "[8]Exit Program\n"
			<< "Enter your Choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			sport.insertEquipment();
			break;
		case 2:
            sport.RentEquipment();
			break;
		case 3:
			break;
		case 4:
			sport.showEquipmentDetails();
			break;
		case 5:
			sport.displayAllEquipment();
			break;
		case 6:
			sport.CheckAvailability();
			break;
		case 7:
			int subChoice;
			cout
				<< "\nCustomer Maintenance Menu:\n"
				<< "1. Add New Customer\n"
				<< "2. Show Customer Details\n"
				<< "3. Display All Customers\n"
				<< "4. List All Equipment Rented by a Customer\n"
				<< "Enter your choice: ";
			cin >> subChoice;

			switch (subChoice) {
			case 1:
				customer.addCustomer();
				break;
			case 2:
				customer.showDetails();
				break;
			case 3:
				customer.displayAllCustomers();
				break;
			case 4:
				// operation for list all equipment rented by a customer
				break;
			default:
				cout << "Invalid option.";
				break;
			}
			break;
		case 8:
			break;
		default:
			cout << "Invalid option.";
			break;
		}
	} while (choice != 8);
	return 0;
}
