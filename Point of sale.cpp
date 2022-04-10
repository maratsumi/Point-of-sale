#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Product {
private:
	string prodName;
	int prodAmt = 0;
	float prodPrice = 0;
public:
	string getProdName() {
		return prodName;
	}
	int getProdAmt() {
		return prodAmt;
	}
	float getProdPrice() {
		return prodPrice;
	}
	void setProdName(string value) {
		prodName = value;
	}
	void setProdAmt(int value) {
		prodAmt = value;
	}
	void setProdPrice(float value) {
		prodPrice = value;
	}
};

class Account {
private:
	string firstName, lastName, username, password, type;
public:
	string getFirstName() {
		return firstName;
	}
	string getLastName() {
		return lastName;
	}
	string getUsername() {
		return username;
	}
	string getPassword() {
		return password;
	}
	string getType() {
		return type;
	}
	void setFirstName(string value) {
		firstName = value;
	}
	void setLastName(string value) {
		lastName = value;
	}
	void setUserName(string value) {
		username = value;
	}
	void setPassword(string value) {
		password = value;
	}
	void setType(string value) {
		type = value;
	}

};

int main() 
{
	Product productList[8];
	Account accountList;
	bool loginReq = false;

	productList[0].setProdName("Cheeseburger");
	productList[0].setProdPrice(6.99f);
	productList[0].setProdAmt(20);
	productList[1].setProdName("Hamburger");
	productList[1].setProdPrice(4.99f);
	productList[1].setProdAmt(35);
	productList[2].setProdName("French Fries");
	productList[2].setProdPrice(3.99f);
	productList[2].setProdAmt(50);
	productList[3].setProdName("Regular Soda");
	productList[3].setProdPrice(2.50f);
	productList[3].setProdAmt(50);
	productList[4].setProdName("Large Soda");
	productList[4].setProdPrice(3.50f);
	productList[4].setProdAmt(35);
	productList[5].setProdName("Coffee");
	productList[5].setProdPrice(1.50f);
	productList[5].setProdAmt(25);
	productList[6].setProdName("1 Pc. Chicken w/ Rice");
	productList[6].setProdPrice(5.99f);
	productList[6].setProdAmt(35);
	productList[7].setProdName("2 Pc. Chicken w/ Rice");
	productList[7].setProdPrice(7.99f);
	productList[7].setProdAmt(10);

	cout << "Welcome to Vitug's Point of sale system" << endl;

	while (!loginReq) {
		char loginOpt;
		bool cashierReq = false;
		bool adminReq = false;

		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "* Kindly use the corresponding character when selecting *" << endl;
		cout << "Select an option from the menu below: " << endl;
		cout << "C > Cashier Login" << endl;
		cout << "A > Admin Login" << endl;
		cout << "Q > Quit" << endl;
		cout << "Input: ";
		cin >> loginOpt;
		cin.ignore();

		if (loginOpt == 'c' || loginOpt == 'C') {
			string userId, userPass;
			cout << "~~ Cashier Login ~~" << endl;
			cout << "Username: ";
			getline(cin, userId);

			cout << "Password: ";
			getline(cin, userPass);

			ifstream readFile(userId + ".txt");
			if (readFile.is_open()) {
				string tempName;
				getline(readFile, tempName);
				string tempPass;
				getline(readFile, tempPass);
				string tempType;
				getline(readFile, tempType);

				if (tempPass == userPass && tempName == userId && tempType == "Cashier") {
					char cashierOpt;

					while (!cashierReq) {
						float changeAmt = 0, paidAmt = 0, totalPrice = 0;

						cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
						cout << "* Kindly use the corresponding character when selecting *" << endl;
						cout << "Select an option from the menu below: " << endl;
						cout << "B > Start a sale" << endl;
						cout << "S > Search a product" << endl;
						cout << "Q > Quit" << endl;
						cout << "Input: ";
						cin >> cashierOpt;

						if (cashierOpt == 'b' || cashierOpt == 'B') {
							int indexSearch;
							int  quantity = 0;
							char exitChar;
							bool saleReq = false;

							cout << "Enter the index of the product you want to add to cart." << endl;
							for (int i = 0; i < 8; i++) {
								cout << i << " > " << productList[i].getProdName() << endl;
								cout << "Price: " << productList[i].getProdPrice() << endl;
								cout << "Amount: " << productList[i].getProdAmt() << endl;
							}
							while (!saleReq) {
								cout << "Input: ";
								cin >> indexSearch;

								if (indexSearch >= 0 || indexSearch <= 7) {
									float tempPrice;
									int tempAmt;

									cout << productList[indexSearch].getProdName() << endl;
									cout << productList[indexSearch].getProdPrice() << endl;
									cout << productList[indexSearch].getProdAmt() << endl;

									tempAmt = productList[indexSearch].getProdAmt();
									if (tempAmt <= 0) {
										cout << "That product is unavailable and out of stock." << endl;
									}
									else {
										tempPrice = productList[indexSearch].getProdPrice();

										productList[indexSearch].setProdAmt(tempAmt - 1);
										totalPrice = totalPrice + tempPrice;
										++quantity;

										cout << "Cart Total Price: " << totalPrice << endl;
										cout << "New Product Amount: " << productList[indexSearch].getProdAmt() << endl;

										cout << "Enter 'c' to continue, 'q' to stop adding to cart (DELETES CART) or 'b' to checkout." << endl;
										cout << "Input exit character: ";
										cin >> exitChar;
										if (exitChar == 'c' || exitChar == 'C') {
											continue;
										}
										else if (exitChar == 'q' || exitChar == 'Q') {
											saleReq = true;
											break;
										}
										else if (exitChar == 'b' || exitChar == 'B') {
											bool priceReach = false;

											while (!priceReach) {
												cout << "Total amount of items: " << quantity << endl;
												cout << "Total Price: " << totalPrice << endl;
												cout << "Enter amount to pay: ";
												cin >> paidAmt;
												if (paidAmt > totalPrice) {
													changeAmt = paidAmt - totalPrice;
													cout << "Change due: " << changeAmt << endl;
													priceReach = true;
													saleReq = true;
													break;
												}
												else {
													cout << "Amount to pay doesn't match total price. Please pay exact or exceeding amount than the total." << endl;
												}
											}
										}
										else {
											cout << "Invalid input. Try again." << endl;
										}
									}
								}
								else {
									cout << "Invalid Input. Try Again." << endl;
								}
							}
						}
						else if (cashierOpt == 's' || cashierOpt == 'S') {
							int indexSearch;
							bool searchReq = false;
							char exitChar;

							cout << "Enter the index of the product you want information for." << endl;
							for (int i = 0; i < 8; i++) {
								cout << i << " > " << productList[i].getProdName() << endl;
							}
							while (!searchReq) {
								cout << "Input index: ";
								cin >> indexSearch;

								if (indexSearch >= 0 && indexSearch <= 7) {
									cout << "Name: " << productList[indexSearch].getProdName() << endl;
									cout << "Price: " << productList[indexSearch].getProdPrice() << endl;
									cout << "Amount: " << productList[indexSearch].getProdAmt() << endl;

									cout << "Enter 'c' to continue or 'q' to stop searching." << endl;
									cout << "Input exit character: ";
									cin >> exitChar;
									if (exitChar == 'c' || exitChar == 'C') {
										continue;
									}
									else if (exitChar == 'q' || exitChar == 'Q') {
										searchReq = true;
										break;
									}
									else {
										cout << "Invalid input. Try again." << endl;
									}
								}
								else {
									cout << "Invalid Input. Try again." << endl;
								}
							}
						}
						else if (cashierOpt == 'q' || cashierOpt == 'Q') {
							cashierReq = true;
						}
						else {
							cout << "Invalid input" << endl;
						}
					}
				}
				else if (cashierReq == true) {
					loginReq = true;
				}
				else {
					cout << "Login information incorrect or account type is invalid." << endl;
				}
				readFile.close();
			}
			else {
				cout << "Login information incorrect or account type is invalid." << endl;
			}
		}
		else if (loginOpt == 'a' || loginOpt == 'A') {
			string userId, userPass;
			cout << "~~ Admin Login ~~" << endl;
			cout << "Username: ";
			getline(cin, userId);

			cout << "Password: ";
			getline(cin, userPass);

			ifstream readFile(userId + ".txt");
			if (readFile.is_open()) {
				string tempName;
				getline(readFile, tempName);
				string tempPass;
				getline(readFile, tempPass);
				string tempType;
				getline(readFile, tempType);

				if (tempPass == userPass && tempName == userId && tempType == "Admin") {
					char adminOpt;
					while (!adminReq) {
						cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
						cout << "* Kindly use the corresponding character when selecting *" << endl;
						cout << "Select an option from the menu below: " << endl;
						cout << "A > Modify Accounts" << endl;
						cout << "P > Modify Products" << endl;
						cout << "Q > Quit" << endl;
						cout << "Input: ";
						cin >> adminOpt;

						if (adminOpt == 'a' || adminOpt == 'A') {
							char accountOpt;
							bool accountReq = false;
							
							while (!accountReq) {
								cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
								cout << "* Kindly use the corresponding character when selecting *" << endl;
								cout << "Select an option from the menu below: " << endl;
								cout << "A > Add Account" << endl;
								cout << "C > Modify Account" << endl;
								cout << "R > Delete Account" << endl;
								cout << "Q > Quit" << endl;
								cout << "Input: ";
								cin >> accountOpt;
								cin.ignore();

								if (accountOpt == 'a' || accountOpt == 'A') {
									string firstNameReg, lastNameReg, userReg, passReg, typeReg;
									cout << "~~ Account Creation ~~" << endl;
									
									cout << "First Name: ";
									getline(cin, firstNameReg);
									accountList.setFirstName(firstNameReg);

									cout << "Last Name: ";
									getline(cin, lastNameReg);
									accountList.setLastName(lastNameReg);

									cout << "Username: ";
									getline(cin, userReg);
									accountList.setUserName(userReg);

									cout << "Password: ";
									getline(cin, passReg);
									accountList.setPassword(passReg);

									cout << "**THIS IS CASE SENSITIVE. THE ACCOUNT WILL NOT WORK PROPERLY IF NOT FOLLOWED.**" << endl;
									cout << "If you want to assign account as cashier, type 'Cashier'. Type 'Admin' for admin." << endl;
									cout << "Type: ";
									getline(cin, typeReg);
									accountList.setType(typeReg);

									ofstream writeFile(userReg + ".txt");
									writeFile << accountList.getUsername() << endl;
									writeFile << accountList.getPassword() << endl;
									writeFile << accountList.getType() << endl;
									writeFile << accountList.getFirstName() << endl;
									writeFile << accountList.getLastName() << endl;
									writeFile.close();
								}
								else if (accountOpt == 'c' || accountOpt == 'C') {
									string modUser, modPass;
									string firstNameMod, lastNameMod, userMod, passMod, typeMod;
									cout << "~~ Account Modification ~~" << endl;
									cout << "Username: ";
									getline(cin, modUser);

									cout << "Password: ";
									getline(cin, modPass);

									ifstream readFile(modUser + ".txt");
									if (readFile.is_open()) {
										string tempUser;
										getline(readFile, tempUser);
										string tempPass;
										getline(readFile, tempPass);

										if (tempUser == modUser && tempPass == modPass) {
											cout << "Account login successful. You may modify this account." << endl;

											cout << "First Name: ";
											getline(cin, firstNameMod);
											accountList.setFirstName(firstNameMod);

											cout << "Last Name: ";
											getline(cin, lastNameMod);
											accountList.setLastName(lastNameMod);

											cout << "Username: ";
											getline(cin, userMod);
											accountList.setUserName(userMod);

											cout << "Password: ";
											getline(cin, passMod);
											accountList.setPassword(passMod);

											cout << "**THIS IS CASE SENSITIVE. THE ACCOUNT WILL NOT WORK PROPERLY IF NOT FOLLOWED.**" << endl;
											cout << "If you want to assign account as cashier, type 'Cashier'. Type 'Admin' for admin." << endl;
											cout << "Type: ";
											getline(cin, typeMod);
											accountList.setType(typeMod);

											ofstream writeFile(userMod + ".txt");
											writeFile << accountList.getUsername() << endl;
											writeFile << accountList.getPassword() << endl;
											writeFile << accountList.getType() << endl;
											writeFile << accountList.getFirstName() << endl;
											writeFile << accountList.getLastName() << endl;
											writeFile.close();

											remove((modUser + ".txt").c_str());
											cout << "Account successfully modified." << endl;
										}
										else {
											cout << "Login information is incorrect." << endl;
										}
										readFile.close();
									}
									else {
										cout << "Login information is incorrect." << endl;
									}

								}
								else if (accountOpt == 'r' || accountOpt == 'R') {
									string removeUser, removePass;
									cout << "~~ Account deletion ~~" << endl;
									cout << "Username: ";
									getline(cin, removeUser);
									cout << "You are about to delete " << removeUser << ". Type the accounts' password to confirm deletion." << endl;
									cout << "Password: ";
									getline(cin, removePass);

									ifstream readFile(removeUser + ".txt");
									if (readFile.is_open()) {
										string tempName;
										getline(readFile, tempName);
										string tempPass;
										getline(readFile, tempPass);

										if (tempPass == removePass && tempName == removeUser) {
											remove((removeUser + ".txt").c_str());
											cout << "Account successfully deleted!" << endl;
										}
										else {
											cout << "Account deletion is unsuccessful. Information was incorrect, please try again." << endl;
										}
										readFile.close();
									}
									else {
										cout << "Account deletion is unsuccessful. Information was incorrect, please try again." << endl;
									}
								}
								else if (accountOpt == 'q' || accountOpt == 'Q') {
									accountReq = true;
								}
								else {
									cout << "Invalid Input." << endl;
								}
							}
						}
						else if (adminOpt == 'p' || adminOpt == 'P') {
							char productOpt;
							bool productReq = false;

							while (!productReq) {
								cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
								cout << "* Kindly use the corresponding character when selecting *" << endl;
								cout << "Select an option from the menu below: " << endl;
								cout << "A > Add/Modify Products" << endl;
								cout << "R > Remove Products" << endl;
								cout << "Q > Quit" << endl;
								cout << "Input: ";
								cin >> productOpt;
								cin.ignore();

								if (productOpt == 'a' || productOpt == 'A') {
									int indexSearch;
									cout << "Existing product list: " << endl;
									for (int i = 0; i < 8; i++) {
										cout << i << " > " << productList[i].getProdName() << endl;
										cout << "Price: " << productList[i].getProdPrice() << endl;
										cout << "Amount: " << productList[i].getProdAmt() << endl;
									}
									cout << "Input the index of the product you want to add/modify." << endl;
									cout << "Input: ";
									cin >> indexSearch;
									cin.ignore();

									if (indexSearch >= 0 && indexSearch <= 7) {
										string prodName;
										float prodPrice;
										int prodAmt;
										cout << "Product name: ";
										getline(cin, prodName);
										productList[indexSearch].setProdName(prodName);

										cout << "Product price: ";
										cin >> prodPrice;
										productList[indexSearch].setProdPrice(prodPrice);

										cout << "Product amount: ";
										cin >> prodAmt;
										productList[indexSearch].setProdAmt(prodAmt);
									}
									else {
										cout << "Invalid input." << endl;
									}
								}
								else if (productOpt == 'r' || productOpt == 'R') {
									int indexSearch;
									for (int i = 0; i < 8; i++) {
										cout << i << " > " << productList[i].getProdName() << endl;
										cout << "Price: " << productList[i].getProdPrice() << endl;
										cout << "Amount: " << productList[i].getProdAmt() << endl;
									}
									cout << "Input the index of the product you want to remove." << endl;
									cout << "Input: ";
									cin >> indexSearch;
									cin.ignore();

									if (indexSearch >= 0 && indexSearch <= 7) {
										productList[indexSearch].setProdName("Empty Product");
										productList[indexSearch].setProdPrice(0.0f);
										productList[indexSearch].setProdAmt(0);
									}
									else {
										cout << "Invalid input." << endl;
									}
								}
								else if (productOpt == 'q' || productOpt == 'Q') {
									productReq = true;
								}
								else {
									cout << "Invalid input." << endl;
								}
							}
						}
						else if (adminOpt == 'q' || adminOpt == 'Q') {
							adminReq = true;
						}
						else {
							cout << "Invalid Input." << endl;
						}
					}
				}
				else {
					cout << "Login information incorrect or account type is invalid." << endl;
				}
			}
			else {
				cout << "Login information incorrect or account type is invalid." << endl;
			}
		}
		else if (loginOpt == 'q' || loginOpt == 'Q') {
			cout << "Quitting..." << endl;
			loginReq = true;
			return 0;
		}
		else {
			cout << "Invalid Input" << endl;
		}
	}

	return 0;
}