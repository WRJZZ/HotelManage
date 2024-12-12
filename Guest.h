#ifndef GUEST_H
#define GUEST_H

#include <string>
#include <fstream>

class Guest {
private:
    std::string name; // 客人的姓名
    std::string idNumber; // 客人的身份证号
    std::string checkInTime; // 入住时间
    std::string checkOutTime; // 退房时间
    int roomId; // 房间号
    double prePayment; // 预付款
    double finalCharge; // 最终费用（正数为退款，负数为需补交）
    int daysBooked; // 预定天数
    int actualDaysStayed; // 实际居住天数
    bool isSettled; // 是否已完成结算

public:
    // 默认构造函数
    Guest();

    // 带参数的构造函数
    Guest(const std::string& name, const std::string& idNumber,
          const std::string& checkInTime, int roomId, int daysBooked, double prePayment);

    // Getters
    std::string getName() const; // 获取客人姓名
    std::string getIdNumber() const; // 获取客人身份证号
    std::string getCheckInTime() const; // 获取入住时间
    std::string getCheckOutTime() const; // 获取退房时间
    int getRoomId() const; // 获取房间号
    double getPrePayment() const; // 获取预付款
    double getFinalCharge() const; // 获取最终费用
    int getDaysBooked() const; // 获取预定天数
    int getActualDaysStayed() const; // 获取实际居住天数
    bool isSettlementCompleted() const; // 检查是否已完成结算

    // Setters
    void setCheckOutTime(const std::string& time); // 设置退房时间
    void setFinalCharge(double charge); // 设置最终费用
    void setActualDaysStayed(int days); // 设置实际居住天数
    void markAsSettled(); // 标记为已结算

    // 序列化方法
    friend std::ostream& operator<<(std::ostream &os, const Guest &guest); // 输出流操作符重载
    friend std::istream& operator>>(std::istream &is, Guest &guest); // 输入流操作符重载
};

#endif // GUEST_H