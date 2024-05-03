#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>

using namespace std;

struct User {
    string username;
    string password;
    int role; // 0 - client , 1 - admin 
    int access; // 0 - no register, 1 - register

    static void updateFile(const vector<User>& users) {
        ofstream file("users.txt");
        for (const auto& user : users) {
         
                file << user.username << " " << user.password << " " << user.role << " " << user.access << endl;
            
        }
        file.close();
    }
    static int checkUserRole(const vector<User>& users, string login, string password) {
        for (const auto& user : users) {
            if (user.username == login && user.password == password) {
                return user.role;
            }
        }
        return -1; // User not found or password incorrect
    }
};
class Admin: public User {
public:
    Admin(const string& username) {
        this->username = username;
        this->role = 1;
        this->access = 1;
    }
 
    void verification(vector<User>& users, const string& username) {
        for (auto& user : users) {
            if (user.username == username) {
                user.access = 1; 
                cout << "User: " << username << " is verified" << endl;
                updateFile(users);
                return;
            }
        }
        cout << "User not found." << endl;
    }
    void viewNoVerificationUsers(const vector<User>& users)
    {
        cout << "No verificational users:" << endl;
        for (const auto& user : users) {
            if (user.access == 0) {
                cout << "Username: " << user.username << ", Role: " << user.role << endl;
            }
            
        }

    }
    void viewAllUsers(const vector<User>& users) {
        cout << "All users:" << endl;
        for (const auto& user : users) {
            if (user.access == 1) {

                cout << "Username: " << user.username << ", Role: " << user.role << endl;
            }
        }

    }

    void addUser(vector<User>& users, const string& username, const string& password, int role) {
        if (username == this->username)
        {

            cout << "User with this login already exists" << endl;
            return;
        }
        users.push_back({ username, password, role });
       
        updateFile(users);
        cout << "User '" << username << "' added successfully." << endl;

    }

    void editUser(vector<User>& users, const string& username, const string& newPassword, int newRole) {
        for (auto& user : users) {
            if (user.username == username) {
                user.password = newPassword;
                user.role = newRole;
                cout << "User '" << username << "' edited successfully." << endl;
                updateFile(users);
                return;
            }
        }

        cout << "User not found." << endl;
    }

    void deleteUser(vector<User>& users, const string& username) {
       
        
        if (this->username == username)
        {

            cout << "You cant delete your account " << endl;
            return;
        }
        for (auto it = users.begin(); it != users.end(); ++it) {
            
            if (it->username == username) {
                users.erase(it);
                cout << "User '" << username << "' deleted successfully." << endl;
                updateFile(users);
                return;
            }
        }
        cout << "User not found." << endl;
    }
private:
 
 
};
int main() {
    vector<User> users;
    ifstream file("users.txt");

    string username;
    string pass;
    int userRole;
    int access;

    int choise;


    while (file >> username >> pass >> userRole>>access) {
        users.push_back(User{ username, pass, userRole,access });
    }
    cout << "click 1 to sign in" << endl;
    cout << "click 2 to sign up" << endl;
    cin >> choise;
    if (choise == 1)
    {


    


    string inputUsername, inputPassword;
    cout << "Enter username: ";
    cin >> inputUsername;
    cout << "Enter password: ";
    inputPassword = "";
    char ch;
    while ((ch = _getch()) != '\r') { // Для Windows используем _getch() вместо getch()
        if (ch == '\b') { // Обработка клавиши Backspace
            if (inputPassword.length() > 0) {
                inputPassword.pop_back();
                cout << "\b \b"; // Стереть символ на экране
            }
        }
        else {
            inputPassword.push_back(ch);
            cout << "*"; // Выводить звездочку вместо символа
        }
    }

    cout << endl;

    userRole = User::checkUserRole(users, inputUsername, inputPassword);
    if (userRole == -1) {
        cout << "Invalid username or password." << endl;
    }
    else if (userRole == 0) {
        cout << "-------------------------Client menu-----------------------------" << endl;
    }
   
 

    if (userRole == 1)
    {

        Admin admin(inputUsername);
        int choise;
        do {
            cout << "-------------------------Admin menu-----------------------------" << endl;
            cout << "1.view all users"<<endl;
            cout << "2.add user" << endl;
            cout << "3.edit user" << endl;
            cout << "4.delete user" << endl;
            cout << "5.verifiacation " << endl;
            cout << "6.quit programm" << endl;

            cout << "enter you choise:" << endl;

            cin >> choise;
           
            switch (choise)
            {

            case 1: admin.viewAllUsers(users);
                break;
            case 2:
            {
                string username, password;
                int role;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                cout << "Enter role (0 for client, 1 for admin): ";
                cin >> role;
                admin.addUser(users, username, password, role);
            }
            break;
            case 3: {
                string username, newPassword;
                int newRole;
                cout << "Enter username of user to edit: ";
                cin >> username;
                cout << "Enter new password: ";
                cin >> newPassword;
                cout << "Enter new role (0 for client, 1 for admin): ";
                cin >> newRole;
                admin.editUser(users, username, newPassword, newRole);
            }
                break;
            case 4: {
                string username;
                cout << "Enter username of user to delete: ";
                cin >> username;
               
                admin.deleteUser(users, username);
            }
                  break;
            case 5:
            {
            

                admin.viewNoVerificationUsers(users);
                string username;
                cout << "Enter username of user to verifiction (Enter 0 to leave)" << endl;
                cin >> username;
                if (username == "0")
                {
                    break;
                }
                admin.verification(users, username);
                

            }
                break;
            case 6: return 0;
            }
        } while (choise != 6);
        return 0;



    }

    }

    if (choise == 2)
    {

        string username, password;
        int role = 0;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        cout << "Wait for administrator verification ";
        User user{};
      
        user.username = username;
        user.password = password;
        users.push_back(User{ username, pass, userRole = 0,access = 0 });
        user.updateFile(users);
      
    }
    else {
        cout << "Err";
    }
    return 0;
}
