#include <iostream>
#include <string>

using namespace std;

// Vi phạm Single Responsibility Principle
class UserManager_ViPham {
public:
    void addUser(const string& username) {
        // Trách nhiệm 1: thêm user vào DB
        cout << "Added user: " << username << endl;
        
        // Trách nhiệm 2: Gửi email thông báo
        cout << "Email sent to: " << username << endl;
    }
};




// Áp dụng Single Responsibility Principle
// Chỉ đảm nhiệm việc gửi email
class EmailService {
public:
    void sendEmail(const string& to, const string& message) {
        cout << "Email sent to " << to << ": " << message << endl;
    }
};

// Chỉ đảm nhiệm quản lý người dùng
class UserManager {
public:
    void addUser(const string& username) {
        cout << "Added user: " << username << endl;
    }
};

// Cách dùng rõ ràng hơn
int main() {
    UserManager userManager;
    EmailService emailService;

    string username = "alice@example.com";
    userManager.addUser(username);
    emailService.sendEmail(username, "Welcome to our service!");

    return 0;
}
