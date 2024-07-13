#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
class SportsEquipment {
	
	vector<int> EquipmentId;
	vector<string>EquipmentName;
	vector<string>Type;
	vector<string>Brand;
	vector<int>NumberofCopies;
	int lastId;
	public:
		SportsEquipment() {
			loadFile("equipment.txt");
			if(EquipmentId.empty()) {
				lastId = 0;
			}
			else {
				lastId = EquipmentId.back();
			}
		}
	
	void insertEquipment() {
		system("cls");
		cout<<"[1]New Sports Equipment\n\n";
		lastId++;
		int copy;
		string name, type, brand;
		cout<<"Equipment ID: "<<lastId<<endl;
		
		cout<<"Equipment Name: ";
		cin.ignore();
		getline(cin,name);
		cout<<"Type: ";
		getline(cin,type);
		cout<<"Brand: ";
		getline(cin,brand);
		cout<<"Number of copies: ";
		cin>>copy;
		cout<<endl;
	    EquipmentId.push_back(lastId);
		EquipmentName.push_back(name);
		Type.push_back(type);
		Brand.push_back(brand);
		NumberofCopies.push_back(copy);	
		saveFile("equipment.txt");
	}
	
	void RentEquipment() {
		while (isEmpty()) {
			cout<<"There is no equipment yet\n";
				break;
		}
		
		system("cls");
		
		cout<<"[2]Rent a Sports Equipment\n\n";
		char choice;
		
		do {
		int rentId;
		cout<<"Video ID: ";
		cin>>rentId;
		bool found = false;
		for (int i = 0; i<EquipmentId.size(); i++) {
			if (rentId == EquipmentId[i]) {
					found = true;
				if(NumberofCopies[i] == 0) { 
				cout<<"No more copies for this Sport Equipment.";
				}
				
				else {
				cout<<"Equipment Name: "<<EquipmentName[i];
				NumberofCopies[i]--;
				cout<<"\nNumber of Copies: "<<NumberofCopies[i];
				saveFile("equipment.txt");	
			
				}
				
			}
		if (!found) {
				cout<<"Equipment ID "<<rentId<<" does not exist."<<endl;
			}
		}
		
		
		cout<<"\nRent another Video? ";
		cin>>choice;
		cout<<endl;
		}
		while (choice != 'N' && choice !='n');	
	}
	
	void returnEquipment() {
	
	}

	
	
	
	
	
	//File handling & extra functions
	void saveFile(const string& filename) {   //saving the data to txt
            ofstream outFile(filename);
            if (outFile.is_open()) {
                for (size_t i = 0; i < EquipmentId.size(); ++i) {
                    outFile <<EquipmentId[i] << "\t"
                            << EquipmentName[i] << "\t"
                            << Type[i] << "\t"
                            << Brand[i] << "\t"
                            << NumberofCopies[i] << "\t"<<endl;
                }
                outFile.close();
            } else {
                cout << "File might not be existing or cannot be accessed." << endl;
            }
        }
        
        
        void loadFile(const string& filename) { // getting the data from txt
        ifstream inFile(filename);
        if (inFile.is_open()) {
            int id, copy;
            string name, type, brand;
            while (inFile >> id >> name >> type >> brand >> copy) {
                EquipmentId.push_back(id);
                EquipmentName.push_back(name);
                Type.push_back(type);
                Brand.push_back(brand);
                NumberofCopies.push_back(copy);
            }
            inFile.close();
        } else {
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

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	system("cls");
	SportsEquipment sport;
	int choice;
	
	do {
		cout<<"[1]New Sports Equipment\n[2]Rent a Sports Equipment\n[3]Return a Sports Equipment\n[4]Show Sports Equipment Details\n[5]Display All Sports Equipment\n[6]Check Sports Equipment Availability\n[7]Customer Maintenance\n[8]Exit Program\nEnter your Choice: ";
		cin>>choice;
		
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
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				break;
		
		}
	}
	while (choice != 8);
	return 0;
}
