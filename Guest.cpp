#include "Guest.h"
Guest::Guest(){}
Guest::Guest(const std::string& name, const std::string& idNumber, const std::string& checkInTime, double prePayment)
    : name(name), idNumber(idNumber), checkInTime(checkInTime), prePayment(prePayment), checkOutTime("") {}

std::string Guest::getName() const { return name; }
std::string Guest::getIdNumber() const { return idNumber; }
std::string Guest::getCheckInTime() const { return checkInTime; }
std::string Guest::getCheckOutTime() const { return checkOutTime; }
double Guest::getPrePayment() const { return prePayment; }
void Guest::setCheckOutTime(const std::string& time) { checkOutTime = time; }

// 序列化方法实现
std::ostream& operator<<(std::ostream &os, const Guest &guest) {
    os << guest.name << ' ' << guest.idNumber << ' ' << guest.checkInTime << ' ' << guest.checkOutTime << ' ' << guest.prePayment;
    return os;
}

std::istream& operator>>(std::istream &is, Guest &guest) {
    getline(is, guest.name, ' ');
    getline(is, guest.idNumber, ' ');
    getline(is, guest.checkInTime, ' ');
    getline(is, guest.checkOutTime, ' ');
    is >> guest.prePayment;
    return is;
}