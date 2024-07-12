#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
class SportsEquipment {
	private:
		list<int> EquipmentId; 
		list<string> EquipmentName;    
		list<string> EquipmentBrand;       //creates a linked list for each of the data required (id,name,brand,genre,copies)
		list<string> EquipmentGenre;
		list<int> NumberofCopies;
	
		
		public:
			SportsEquipment() {
				  cout << "Constructor called. Loading file..." << endl;
        loadFile();  // Call the function that loads the data from the txt file
        cout << "Loaded " << EquipmentId.size() << " equipment items from the file." << endl;
			}
			void InsertEquipment() {   //add equipment function
			string name,brand, prod;
			int id = getId(), copy;
			
			cout<<"\nEquipment ID: "<<id;    //pushes the current ID
			EquipmentId.push_back(id);
		
			cout<<"\nEquipment Name: ";  //ask the user to input the name, and then will push it to the list afterwards
			cin.ignore();
			getline(cin,name);
			EquipmentName.push_back(name);
			
			cout<<"Brand: ";
			getline(cin,brand); //ask the user to input the brand, and then will push it to the list afterwards
			EquipmentBrand.push_back(brand);
			
			cout<<"Genre: ";
			getline(cin,prod); //ask the user to input the genre, and then will push it to the list afterwards
			EquipmentGenre.push_back(prod);
			
			cout<<"Number of Copies: ";
			cin >> copy; //ask the user to input the number of copies, and then will push it to the list afterwards
			NumberofCopies.push_back(copy);
			saveFile();  //saves the data into the txt file
			}
			
			
			void saveFile() {  // Function to save the inserted equipment data to a text file
    ofstream file("equipment.txt", ios::app); 
    if (file.is_open()) { 
        // Writes the inputted data into the txt file, seperated by "," to easily 
        file << EquipmentId.back() << ","   
             << EquipmentName.back() << "," 
             << EquipmentBrand.back() << "," 
             << EquipmentGenre.back() << "," 
             << NumberofCopies.back() << endl;  
        file.close();
    }
}
          	 void loadFile() { 
        ifstream file("equipment.txt");
        if (file.is_open()) {
        	cout << "File opened successfully." << endl;
            int id;
            string name, brand, gen;
            int copy;

            while (file >> id >> ws && getline(file, name, ',') && getline(file, brand, ',') &&
                   getline(file, gen, ',') && file >> copy) {
                EquipmentId.push_back(id);
                EquipmentName.push_back(name);
                EquipmentBrand.push_back(brand);
                EquipmentGenre.push_back(gen);
                NumberofCopies.push_back(copy);
            }

            file.close();
        }
    }  int getId() {
            	if(EquipmentId.empty()) {
            		return 1;   // if there is no equipment yet, it will initialize the id to 1
				}
				else {
					return EquipmentId.back()+1;  //if there is already an equipment, it will get the last id and increment by 1 for the next id
				}
			}
			
			
		
	
	
	
	
	 void displayAll() {
	 	system("cls");
	 	if (EquipmentId.empty()) {
	 		cout<<"\nThere is no record of equipments yet.";
		 }    
		 else {
		 	cout << "Equipment ID\tEquipment Name\tBrand\tGenre\tNumber of Copies" << endl;
		 list<int>::iterator iterId = EquipmentId.begin();
   list<string>::iterator iterName = EquipmentName.begin();
   list<string>::iterator iterBrand = EquipmentBrand.begin();
    list<string>::iterator iterGenre = EquipmentGenre.begin();
    list<int>::iterator iterCopies = NumberofCopies.begin();
    
    
    while (iterId != EquipmentId.end()) {
    cout << *iterId << "\t\t" << *iterName << "\t\t" << *iterBrand << "\t" << *iterGenre << "\t" << *iterCopies << endl;
    
        ++iterId;
        ++iterName;
        ++iterBrand;
        ++iterGenre;
        ++iterCopies;
	}
    
		 }
		    
    }
    
    
    
    
    
    
    
    
    
    
};
			
		
		
			
int main(int argc, char** argv) {
	int choice;
		SportsEquipment equip;
	do {
		
	cout<<"\n[1]New Equipment\n[2]Rent an Equipment\n[3]Return an Equipment\n[4]Show Equipment Details\n[5]Display all Equipments\n[6]Check Video Availability\n[7]Customer Maintenance\n[8]Exit Program\nYour Choice: ";
	cin>>choice;
	switch (choice) {
		case 1:
			equip.InsertEquipment();
			break;
		case 5:
			equip.displayAll();
			break;
	}
	}
while (choice != 8);
	return 0;
}
