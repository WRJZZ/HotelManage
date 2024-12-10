#ifndef GUEST_H
#define GUEST_H

#include <string>
#include <fstream>

class Guest {
private:
    std::string name;
    std::string idNumber;
    std::string checkInTime;
    std::string checkOutTime;
    double prePayment;

public:
    Guest();

    Guest(const std::string& name, const std::string& idNumber, const std::string& checkInTime, double prePayment);

    // Getters and Setters
    std::string getName() const;
    std::string getIdNumber() const;
    std::string getCheckInTime() const;
    std::string getCheckOutTime() const;
    double getPrePayment() const;
    void setCheckOutTime(const std::string& time);

    // 序列化方法
    friend std::ostream& operator<<(std::ostream &os, const Guest &guest);
    friend std::istream& operator>>(std::istream &is, Guest &guest);
};

#endif // GUEST_H