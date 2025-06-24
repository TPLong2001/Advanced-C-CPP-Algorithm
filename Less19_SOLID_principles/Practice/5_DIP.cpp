#include <iostream>

using namespace std;


// Vi phạm Dependency Inversion Principle
// Module cấp thấp
class MySQLDatabase_ViPham {
public:
    void saveData(const string& data) {
        cout << "Saving " << data << " to MySQL\n";
    }
};

// Module cấp cao phụ thuộc trực tiếp vào module cấp thấp
class UserManager_ViPham {
    MySQLDatabase_ViPham db; // Phụ thuộc cụ thể
public:
    void saveUser(const string& username) {
        db.saveData(username);
    }
}; 





// Áp dụng Dependency Inversion Principle   
// Interface abstraction
class Database {
public:
    virtual void save(const string& data) = 0;
    virtual ~Database() = default;
};

// Concrete implementation
class MySQL : public Database {
public:
    void save(const string& data) override {
        cout << "Saving " << data << " to MySQL\n";
    }
};

// Concrete implementation
class MongoDB : public Database {
public:
    void save(const string& data) override {
        cout << "Saving " << data << " to MongoDB\n";
    }
};

//  Module cấp cao phụ thuộc vào abstraction thay vì phụ thuộc trực tiếp vào module cấp thấp
class UserManager {
    Database* db; // Sử dụng abstraction
public:
    UserManager(Database* db) : db(db) {}
    void saveUser(const string& username) {
        db->save(username);
    }
};


int main() {
    MySQL mysqlDb;
    MongoDB mongoDb;

    UserManager userManager(&mysqlDb); // có thể thay đổi database dễ dàng
    userManager.saveUser("alice");

    UserManager userManager2(&mongoDb); // dùng MongoDB dễ dàng
    userManager2.saveUser("bob");

    return 0;
}





