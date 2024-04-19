#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Property {
private:
    int id; // номер недвижимости
    string address; //адрес
    int area; //площадь объекта недвижимости
    int rooms; // кол-во комнат
    float price; // цена в $
    string status; // статус taken or free

public:
    Property(int id, string address, int area, int rooms, float price, string status) :
        id(id), address(address), area(area), rooms(rooms), price(price), status(status) {}

    // getters and setters
    int getId() const { return id; }
    string getAddress() const { return address; }
    int getArea() const { return area; }
    int getRooms() const { return rooms; }
    float getPrice() const { return price; }
    string getStatus() const { return status; }
    void setAddress(string address) { this->address = address; }
    void setArea(int area) { this->area = area; }
    void setRooms(int rooms) { this->rooms = rooms; }
    void setPrice(float price) { this->price = price; }
    void setStatus(string status) { this->status = status; }
    Property& operator++();
    Property operator++(int);
    bool operator!() const //проверяет свободен ли объект 
    {
        return getStatus()== "free";
    }
    virtual void printPropertyInfo() const 
    {
        cout << "Property ID: " << id << ", Address: " << address << ", Area: " << area << ", Rooms: " << rooms << ", Price: " << price << ", Status: " << status << endl;
    }
};

class User {
    private:
    static int userCount;
protected:
    int id; // номер пользователя
    string name; //имя пользователя
    string email; //почта

public:
    User(int id, string name, string email) :
        id(id), name(name), email(email) {userCount++;}

    // getters and setters
    int getId() const { return id; }
    string getName() const { return name; }
    string getEmail() const { return email; }

    void setName(string name) { this->name = name; }
    void setEmail(string email) { this->email = email; }
    virtual void printUserInfo() const {
        cout << "User ID: " << id << ", Name: " << name << ", Email: " << email << endl;
    }
    static int getUserCount() 
    {
        return userCount;
    }
};

class Owner : public User {
private:
    vector<Property*> properties; // список недвижимостей, принадлежащих владельцу

public:
    Owner(int id, string name, string email) : User(id, name, email) {}

    void addProperty(Property* property) 
    {
        properties.push_back(property); 
    }

    void removeProperty(Property* property) 
    {
        properties.erase(remove_if(properties.begin(), properties.end(), [property](Property* p) { return p == property; }), properties.end()); //удаление недвижимости
    }

    // getters and setters
    vector<Property*> getProperties() const { return properties; } //возвращает список недвижимостей владельца

    // виртуальная функция
    void printUserInfo() const override {
        cout << "Owner ID: " << id << ", Name: " << name << ", Email: " << email << endl;
    }

    //перекрытая функция 
    void printPropertyInfo() const {
        cout << "Owner ID: " << id << ", Name: " << name << ", Email: " << email << endl;
        cout << "Properties:" << endl;
        for (const auto& property : properties) {
            property->printPropertyInfo();
        }
    }
    float cost_sum()
    {
        float sum=0;
        for (const auto& property : properties) {
            sum+=property->getPrice();
        }
        return sum;
    }
};

class Tenant : public User {
private:
    vector<Property*> bookings; //список бронирований, осуществленных арендатором

public:
    Tenant(int id, string name, string email) : User(id, name, email) {}

    void addBooking(Property* booking) {
        bookings.push_back(booking);
    }

    void removeBooking(Property* booking) {
        bookings.erase(remove_if(bookings.begin(), bookings.end(), [booking](Property* p) { return p == booking; }), bookings.end());
    }

    // getters and setters
    vector<Property*> getBookings() const { return bookings; }

    void printUserInfo() const override {
        cout << "Tenant ID: " << id << ", Name: " << name << ", Email: " << email << endl;
    }

    void printtenantInfo() const {
        cout << "Owner ID: " << id << ", Name: " << name << ", Email: " << email << endl;
        cout << "Properties:" << endl;
        for (const auto& property : bookings) {
            property->printPropertyInfo();
        }
    }
};

class Booking {
private:
    int id; //уникальный идентификатор бронирования
    Property* property; // недвижимость, забронированная в рамках бронирования
    Tenant* tenant; //арендатор, осуществивший бронирование
    string startDate; // дата начала бронирования
    string endDate; // дата окончания бронирования
    string status; //approve or expect

public:
    Booking(const Booking& other) : id(other.id), property(other.property), tenant(other.tenant), startDate(other.startDate), endDate(other.endDate), status(other.status) {}
    Booking() : id(0), property(nullptr), tenant(nullptr), startDate(""), endDate(""), status("") {}
    Booking(int id, Property* property, Tenant* tenant, string startDate, string endDate, string status) :
        id(id), property(property), tenant(tenant), startDate(startDate), endDate(endDate), status(status) {
            property->setStatus("taken");
        }

    // getters and setters
    int getId() const { return id; }
    Property* getProperty() const { return property; }
    Tenant* getTenant() const { return tenant; }
    string getStartDate() const { return startDate; }
    string getEndDate() const { return endDate; }
    string getStatus() const { return status; }

    void setProperty(Property* property) { this->property = property; }
    void setTenant(Tenant* tenant) { this->tenant = tenant; }
    void setStartDate(string startDate) { this->startDate = startDate; }
    void setEndDate(string endDate) { this->endDate = endDate; }
    void setStatus(string status) { this->status = status; }
};

class Payment {
private:
    Tenant* tenant;
    int id; //уникальный идентификатор платежа
    Booking* booking; //бронирование, для которого осуществлен платеж
    float amount; //сумма платежа

public:
    Payment(Tenant* tenant,int id, Booking* booking, float amount=0) :
        tenant(tenant),id(id), booking(booking), amount(amount){}


    // getters and setters
    int getId() const { return id; }
    Booking* getBooking() const { return booking; }
    float getAmount() const { return amount; }
    string approve(float k)
    {
        if (booking->getProperty()->getPrice() > k) 
        {
            booking->setStatus("paid");
            return "payment is verify"  ;        
        }
        else return "payment is rejected";
    }
    void setBooking(Booking* booking) { this->booking = booking; }
    void setAmount(float amount) { this->amount = amount; }
};

class Admin : public User {
public:
    Admin(int id, string name, string email) : User(id, name, email) {}
        void owner_property_list(Owner owner)
        {
            owner.printPropertyInfo();
        }
        void tenant_bookings_list(Tenant tenant)
        {
            tenant.printtenantInfo();

        }
};

// перегрузка операций
Property& Property::operator++() {
    setPrice(getPrice() + 10000);
    return *this;
}

Property Property::operator++(int) {
    Property temp(*this);
    setPrice(getPrice() + 10000);
    return temp;
}


ostream& operator<<(ostream& os, const Property& property) {
    os << "ID: " << property.getId() << ", Address: " << property.getAddress() << ", Area: " << property.getArea() << ", Rooms: " << property.getRooms() << ", Price: " << property.getPrice() << ", Status: " << property.getStatus();
    return os;
}

// перегрузка оператора ==
bool operator==(const Property& p1, const Property& p2) {
    return p1.getId() == p2.getId();
}

// перегрузка оператора +  сумма стоимости для оценки своих сил
float operator+(const Property& p1, const Property& p2) {
    float price = p1.getPrice() + p2.getPrice();
    return price;
}

float operator+(Owner owner) {
    
    return owner.cost_sum();
}
// перегрузка оператора << для класса User
ostream& operator<<(ostream& os, const User& user) {
    os << "ID: " << user.getId() << ", Name: " << user.getName() << ", Email: " << user.getEmail();
    return os;
}

// перегрузка оператора == для класса User
bool operator==(const User& u1, const User& u2) {
    return u1.getId() == u2.getId();
}

// перегрузка оператора << для класса Booking
ostream& operator<<(ostream& os, const Booking& booking) {
    os << "ID: " << booking.getId() << ", Property: " << *(booking.getProperty()) << ", Tenant: " << *(booking.getTenant()) << ", Start date: " << booking.getStartDate() << ", End date: " << booking.getEndDate() << ", Status: " << booking.getStatus();
    return os;
}

// перегрузка оператора == для класса Booking
bool operator==(const Booking& b1, const Booking& b2) {
    return b1.getId() == b2.getId();
}

// перегрузка оператора + для класса Booking
Booking operator+(const Booking& b1, const Booking& b2) {
    float price = b1.getProperty()->getPrice() + b2.getProperty()->getPrice();
    return Booking(-1, b1.getProperty(), b1.getTenant(), "2023-01-01", "2023-01-31", "booked");

}

// перегрузка оператора << для класса Payment
ostream& operator<<(ostream& os, const Payment& payment) {
    os << "ID: " << payment.getId() << ", Booking: " << *(payment.getBooking()) << ", Amount: " << payment.getAmount();
    return os;
}

// перегрузка оператора == для класса Payment
bool operator==(const Payment& p1, const Payment& p2) {
    return p1.getId() == p2.getId();
}

// перегрузка оператора + для класса Payment
// Payment operator+(const Payment& p1, const Payment& p2) {
//     float amount = p1.getAmount() + p2.getAmount();
//     return Payment(-1, p1.getBooking(), amount, "");
// }



int User::userCount = 0;
int main() {
     try {
        Property property1(1, "Moscow, Lenina 15", 50, 2, 5000, "free");
        Property property2(2, "Moscow, Lenina 16", 60, 3, 6000, "free");
        Property property3(3, "Moscow, Lenina 16", 60, 3, 6000, "free");

        if (property1.getPrice()<=0 || property2.getPrice()<=0)
            throw runtime_error("incorect data");

        Owner owner(2, "Ivanov", "ivanov@mail.ru");
        owner.addProperty(&property1);
        owner.addProperty(  &property2);
        //перегруженная функция

        cout<<property1+property2<< endl;
        cout<<+owner<< endl;


    Tenant tenant(3, "Petrov", "petrov@mail.ru");
    Booking booking1(1, &property1, &tenant, "01-04-2023", "29-04-2023", "not paid");
    Booking booking2(2, &property2, &tenant, "01-04-2023", "29-04-2023", "not paid");
        if (stoi(booking1.getStartDate().substr(0,2))>31 || stoi(booking1.getStartDate().substr(0,2))<0 || stoi(booking1.getEndDate().substr(0,2))>31 || stoi(booking1.getEndDate().substr(0,2))<0) 
            throw runtime_error("incorect data");
    tenant.addBooking(&property1);
    tenant.addBooking(&property2);
    tenant.addBooking(&property3);
        Payment payment1(&tenant,1, &booking1);
        Payment payment2(&tenant,2, &booking2);
        cout<<payment1.approve(5000) << " status of payment  " << booking1.getStatus() << endl;
        cout<<payment2.approve(400) <<" status of payment    "<< booking2.getStatus() << endl;
        if (!property1 || !property2) //унарный оператор
            throw runtime_error("Error system");

        // проверка создания объектов
        // cout << property1 << endl<< endl;
        // cout << property2 << endl<< endl;
        // cout << owner << endl << endl;
        // cout << tenant << endl << endl;
        // cout << booking1 << endl << endl;
        // cout << booking2 << endl << endl;
        // cout << payment1 << endl << endl;
        // cout << payment2 << endl << endl;
        // cout << property1 << endl << endl;
        // // перегруженные операции
        
        //проверка бинарной операции == и префиксной и постфиксной операций
        cout << ++property1 << endl;
        cout << property1++ << endl;
        float potential_sum = property1 + property2; //бинарная операция
        cout << potential_sum << endl;
        if (property1 == property2) 
            throw runtime_error("property are equal incorect data");

        User user1(1, "Ivanov", "ivanov@mail.ru");
        User user2(2, "Petrov", "petrov@mail.ru");
        if (user1 == user2) {
            throw runtime_error("Users are equal incorect data");
        }
        if (booking1 == booking2) {
            throw runtime_error("bokkings are equal incorect data");
        }
        // Payment payment3 = payment1 + payment2;
        // cout << payment3 << endl;

        if (payment1 == payment2) {
            throw runtime_error("payments are equal incorect data");}


        //проверка унарной операции

        // проверка статическая функция
        cout << "Количество пользователей в системе:"<< User::getUserCount()<<endl;
                Admin admin(3,"sokolov","ad.mail.ru");
                admin.owner_property_list(owner);
                admin.tenant_bookings_list(tenant);

     }
    catch (const exception& ex) {
        cerr << "Error: " << ex.what() << endl;
    }

    // проверка виртуальной функции
    Owner owner(1, "Ivanov", "ivanov@mail.ru");
    owner.printUserInfo(); // Выведет "Owner ID: 1, Name: Ivanov, Email: ivanov@mail.ru"

    Tenant tenant(2, "Petrov", "petrov@mail.ru");
    tenant.printUserInfo(); // Выведет "Tenant ID: 2, Name: Petrov, Email: petrov@mail.ru"

    return 0;
}
