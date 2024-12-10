#include "Room.h"
#include <iostream>
#include <map>
#include <iomanip>
#include <sstream>

const std::map<RoomType, std::pair<std::string, double>> roomTypeInfo = {
    {RoomType::SINGLE, {"单人间", 100.0}},
    {RoomType::DOUBLE, {"双人间", 200.0}},
    {RoomType::FAMILY, {"家庭房", 300.0}},
    {RoomType::PRESIDENTIAL_SUITE, {"总统套房", 500.0}}
};
Room::Room(){}
Room::Room(int id, RoomType type, double price)
    : id(id), type(type), price(price), isOccupied(false) {}

int Room::getId() const { return id; }
RoomType Room::getType() const { return type; }
void Room::setType(RoomType type) {
    this->type = type;
    this->price = roomTypeInfo.at(type).second; // 根据类型更新价格
}
double Room::getPrice() const { return price; }
void Room::setPrice(double price) { this->price = price; }
bool Room::getIsOccupied() const { return isOccupied; }
void Room::setIsOccupied(bool occupied) { isOccupied = occupied; }

void Room::show() const {
    auto info = roomTypeInfo.at(type);
    std::cout << "房间号: " << id
              << ", 类型: " << info.first
              << ", 价格: " << info.second
              << ", 状态: " << (isOccupied ? "已占用" : "空闲")
              << std::endl;
}

// 序列化方法实现
std::ostream& operator<<(std::ostream &os, const Room &room) {
    os << room.id << ' ' << static_cast<int>(room.type) << ' ' << room.price << ' ' << room.isOccupied;
    return os;
}

std::istream& operator>>(std::istream &is, Room &room) {
    int typeInt;
    is >> room.id >> typeInt >> room.price >> room.isOccupied;
    room.type = static_cast<RoomType>(typeInt);
    return is;
}