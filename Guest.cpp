#include "Guest.h"

// 默认构造函数，初始化所有成员变量为默认值
Guest::Guest()
    : name(""), idNumber(""), checkInTime(""), checkOutTime(""),
      roomId(0), prePayment(0.0), finalCharge(0.0),
      daysBooked(0), actualDaysStayed(0), isSettled(false) {}

// 带参数的构造函数，初始化客人信息
Guest::Guest(const std::string& name, const std::string& idNumber,
             const std::string& checkInTime, int roomId, int daysBooked, double prePayment)
    : name(name), idNumber(idNumber), checkInTime(checkInTime), roomId(roomId),
      daysBooked(daysBooked), prePayment(prePayment),
      checkOutTime(""), finalCharge(0.0), actualDaysStayed(0), isSettled(false) {}

// Getter 方法
std::string Guest::getName() const { return name; }
std::string Guest::getIdNumber() const { return idNumber; }
std::string Guest::getCheckInTime() const { return checkInTime; }
std::string Guest::getCheckOutTime() const { return checkOutTime; }
int Guest::getRoomId() const { return roomId; }
double Guest::getPrePayment() const { return prePayment; }
double Guest::getFinalCharge() const { return finalCharge; }
int Guest::getDaysBooked() const { return daysBooked; }
int Guest::getActualDaysStayed() const { return actualDaysStayed; }
bool Guest::isSettlementCompleted() const { return isSettled; }

// Setter 方法
void Guest::setCheckOutTime(const std::string& time) { checkOutTime = time; }
void Guest::setFinalCharge(double charge) { finalCharge = charge; }
void Guest::setActualDaysStayed(int days) { actualDaysStayed = days; }
void Guest::markAsSettled() { isSettled = true; }

// 序列化方法实现
std::ostream& operator<<(std::ostream &os, const Guest &guest) {
    os << guest.name << ' ' << guest.idNumber << ' ' << guest.checkInTime << ' '
       << guest.checkOutTime << ' ' << guest.roomId << ' ' << guest.prePayment << ' '
       << guest.finalCharge << ' ' << guest.daysBooked << ' ' << guest.actualDaysStayed << ' '
       << (guest.isSettled ? 1 : 0); // 使用整数表示布尔值
    return os;
}

std::istream& operator>>(std::istream &is, Guest &guest) {
    int settledInt;
    is >> guest.name >> guest.idNumber >> guest.checkInTime >> guest.checkOutTime
       >> guest.roomId >> guest.prePayment >> guest.finalCharge
       >> guest.daysBooked >> guest.actualDaysStayed >> settledInt;
    guest.isSettled = settledInt != 0;
    return is;
}