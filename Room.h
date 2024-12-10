#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <fstream>

enum class RoomType {
    SINGLE,
    DOUBLE,
    FAMILY,
    PRESIDENTIAL_SUITE
};

class Room {
private:
    int id;
    RoomType type;
    double price;
    bool isOccupied;

public:
    Room();
    Room(int id, RoomType type, double price);

    // Getters and Setters
    int getId() const;
    RoomType getType() const;
    void setType(RoomType type);
    double getPrice() const;
    void setPrice(double price);
    bool getIsOccupied() const;
    void setIsOccupied(bool occupied);

    // 显示房间信息
    void show() const;

    // 序列化方法
    friend std::ostream& operator<<(std::ostream &os, const Room &room);
    friend std::istream& operator>>(std::istream &is, Room &room);
};

#endif // ROOM_H