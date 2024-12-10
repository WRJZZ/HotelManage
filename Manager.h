#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include <string>
#include "Room.h"
#include "Guest.h"

class Manager {
private:
    std::vector<Room> rooms;
    std::vector<std::pair<int, Guest>> guests;

public:
    Manager() {}
    void start();
    void addRoom();
    void checkIn();
    void checkOut();
    void browseRooms();
    void queryRoom();
    void modifyRoom();
    void deleteRoom();

    // 新增的文件操作方法
    void saveData();
    void loadData();

    // 辅助函数
    Room* findRoomById(int roomId);
    Guest* findGuestByName(const std::string& name);
};

#endif // MANAGER_H