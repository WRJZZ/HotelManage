#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include <string>
#include "Room.h"
#include "Guest.h"

class Manager {
private:
    std::vector<Room> rooms; // 存储房间信息的向量
    std::vector<std::pair<int, Guest>> guests; // 存储客人信息的向量，键值对形式存储房间号和客人对象

public:
    Manager() {} // 默认构造函数

    void start(); // 启动管理系统的入口方法
    void addRoom(); // 添加房间的方法
    void checkIn(); // 办理入住的方法
    void checkOut(); // 办理退房结算的方法
    void browseRooms(); // 浏览所有房间的方法
    void queryRoom(); // 查询房间的方法
    void modifyRoom(); // 修改房间信息的方法
    void deleteRoom(); // 删除房间的方法

    // 新增的文件操作方法
    void saveData(); // 保存数据到文件的方法
    void loadData(); // 从文件加载数据的方法

    // 辅助函数
    Room* findRoomById(int roomId); // 根据房间号查找房间的方法
    Guest* findGuestByName(const std::string& name); // 根据名字查找客人的方法
};

#endif // MANAGER_H