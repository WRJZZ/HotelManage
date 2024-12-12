#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <map>
#include <utility> // for std::pair

enum class RoomType {
    SINGLE, // 单人间
    DOUBLE, // 双人间
    FAMILY, // 家庭房
    PRESIDENTIAL_SUITE // 总统套房
};

class Room {
private:
    int id; // 房间号
    RoomType type; // 房间类型
    double price; // 房间价格
    bool isOccupied; // 是否被占用

public:
    // 默认构造函数
    Room();

    // 带参数的构造函数
    Room(int id, RoomType type, double price);

    // Getters
    int getId() const; // 获取房间号
    RoomType getType() const; // 获取房间类型
    void setType(RoomType type); // 设置房间类型
    double getPrice() const; // 获取房间价格
    void setPrice(double price); // 设置房间价格
    bool getIsOccupied() const; // 检查房间是否被占用
    void setIsOccupied(bool occupied); // 设置房间占用状态

    // 显示房间信息
    void show() const; // 打印房间信息的方法

    // 序列化方法
    friend std::ostream& operator<<(std::ostream &os, const Room &room); // 输出流操作符重载
    friend std::istream& operator>>(std::istream &is, Room &room); // 输入流操作符重载
};

// 全局静态变量定义
extern const std::map<RoomType, std::pair<std::string, double>> roomTypeInfo;

#endif // ROOM_H