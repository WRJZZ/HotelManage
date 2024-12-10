#include "Manager.h"
#include <iostream>
#include <iomanip>
#include "Guest.h"
#include "Room.h"
using namespace std;

void Manager::start() {
    loadData(); // 加载数据

    char choice;
    do {
        cout << "宾馆客房管理系统\n"
                << "1. 添加房间\n"
                << "2. 客人入住登记\n"
                << "3. 客人退房结算\n"
                << "4. 浏览全部客房信息\n"
                << "5. 查询客房信息\n"
                << "6. 修改客房信息\n"
                << "7. 删除客房信息\n"
                << "0. 退出\n"
                << "请选择: ";
        cin >> choice;
        switch (choice) {
            case '1': addRoom();
                break;
            case '2': checkIn();
                break;
            case '3': checkOut();
                break;
            case '4': browseRooms();
                break;
            case '5': queryRoom();
                break;
            case '6': modifyRoom();
                break;
            case '7': deleteRoom();
                break;
            case '0': cout << "感谢使用！再见。\n";
                break;
            default: cout << "无效选项，请重新选择。\n";
        }
    } while (choice != '0');

    saveData(); // 保存数据
}

// 添加房间
void Manager::addRoom() {
    int id, typeChoice;
    RoomType type;
    double price = 0.0;

    cout << "请输入房间号：";
    cin >> id;

    // 检查是否已存在相同ID的房间
    if (findRoomById(id) != nullptr) {
        cout << "该房间号已存在，请重新输入。\n";
        return;
    }

    cout << "请选择房间类型：\n"
            << "1 - 单人间（100元/天）\n"
            << "2 - 双人间（200元/天）\n"
            << "3 - 家庭房（300元/天）\n"
            << "4 - 总统套房（500元/天）\n"
            << "请选择：";
    cin >> typeChoice;

    switch (typeChoice) {
        case 1:
            type = RoomType::SINGLE;
            price = 100.0;
            break;
        case 2:
            type = RoomType::DOUBLE;
            price = 200.0;
            break;
        case 3:
            type = RoomType::FAMILY;
            price = 300.0;
            break;
        case 4:
            type = RoomType::PRESIDENTIAL_SUITE;
            price = 500.0;
            break;
        default:
            cout << "无效选项，请重新选择。\n";
            return;
    }

    rooms.emplace_back(id, type, price); // 使用更新后的构造函数
    cout << "房间添加成功。\n";
}

// 客人入住登记
void Manager::checkIn() {
    int roomId;
    string name, idNumber, checkInTime;
    double prePayment;

    cout << "请输入入住的房间号：";
    cin >> roomId;
    Room *room = findRoomById(roomId);

    if (room == nullptr || room->getIsOccupied()) {
        cout << "该房间不存在或已被占用。\n";
        return;
    }

    cout << "请输入客人姓名：";
    cin.ignore();
    getline(cin, name);
    cout << "请输入客人身份证号：";
    getline(cin, idNumber);
    cout << "请输入入住时间（格式：YYYY-MM-DD HH:MM）：";
    getline(cin, checkInTime);
    cout << "请输入预付费用：";
    cin >> prePayment;

    guests.emplace_back(roomId, Guest(name, idNumber, checkInTime, prePayment));
    room->setIsOccupied(true);
    cout << "入住登记完成。\n";
}

// 客人退房结算
void Manager::checkOut() {
    int roomId;
    string checkOutTime;
    cout << "请输入退房的房间号：";
    cin >> roomId;
    Room *room = findRoomById(roomId);

    if (room == nullptr || !room->getIsOccupied()) {
        cout << "该房间不存在或未被占用。\n";
        return;
    }

    for (auto it = guests.begin(); it != guests.end(); ++it) {
        if (it->first == roomId) {
            cout << "请输入退房时间（格式：YYYY-MM-DD HH:MM）：";
            cin.ignore();
            getline(cin, checkOutTime);
            it->second.setCheckOutTime(checkOutTime);
            room->setIsOccupied(false);
            cout << "退房结算完成。\n";
            guests.erase(it);
            break;
        }
    }
}

// 浏览全部客房信息
void Manager::browseRooms() {
    cout << "所有客房信息如下：\n";
    for (const auto &room: rooms) {
        room.show();
    }
}

// 查询客房信息
void Manager::queryRoom() {
    int choice;
    cout << "查询方式：\n1. 查询空房间\n2. 按姓名查询\n3. 按房间号查询\n请选择：";
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "空闲房间如下：\n";
            for (const auto &room: rooms) {
                if (!room.getIsOccupied()) {
                    room.show();
                }
            }
            break;
        case 2: {
            string name;
            cout << "请输入要查询的客人姓名：";
            cin.ignore();
            getline(cin, name);
            bool found = false;
            for (const auto &guestPair: guests) {
                if (guestPair.second.getName() == name) {
                    Room *room = findRoomById(guestPair.first);
                    if (room != nullptr) {
                        room->show();
                        cout << "客人：" << guestPair.second.getName()
                                << ", 入住时间：" << guestPair.second.getCheckInTime()
                                << ", 预付费用：" << guestPair.second.getPrePayment() << "\n";
                        found = true;
                    }
                }
            }
            if (!found) {
                cout << "未找到该客人。\n";
            }
            break;
        }
        case 3: {
            int roomId;
            cout << "请输入要查询的房间号：";
            cin >> roomId;
            Room *room = findRoomById(roomId);
            if (room != nullptr) {
                room->show();
                for (const auto &guestPair: guests) {
                    if (guestPair.first == roomId) {
                        cout << "客人：" << guestPair.second.getName()
                                << ", 入住时间：" << guestPair.second.getCheckInTime()
                                << ", 预付费用：" << guestPair.second.getPrePayment() << "\n";
                    }
                }
            } else {
                cout << "未找到该房间。\n";
            }
            break;
        }
        default:
            cout << "无效选项，请重新选择。\n";
    }
}

// 修改客房信息
void Manager::modifyRoom() {
    int roomId, typeChoice;
    RoomType type;
    double price = 0.0;

    cout << "请输入要修改的房间号：";
    cin >> roomId;
    Room *room = findRoomById(roomId);

    if (room == nullptr) {
        cout << "该房间不存在。\n";
        return;
    }

    cout << "请选择新的房间类型：\n"
            << "1 - 单人间（100元/天）\n"
            << "2 - 双人间（200元/天）\n"
            << "3 - 家庭房（300元/天）\n"
            << "4 - 总统套房（500元/天）\n"
            << "请选择：";
    cin >> typeChoice;

    switch (typeChoice) {
        case 1:
            type = RoomType::SINGLE;
            price = 100.0;
            break;
        case 2:
            type = RoomType::DOUBLE;
            price = 200.0;
            break;
        case 3:
            type = RoomType::FAMILY;
            price = 300.0;
            break;
        case 4:
            type = RoomType::PRESIDENTIAL_SUITE;
            price = 500.0;
            break;
        default:
            cout << "无效选项，请重新选择。\n";
            return;
    }

    room->setType(type);
    room->setPrice(price);
    cout << "房间信息修改成功。\n";
}

// 删除客房信息
void Manager::deleteRoom() {
    int roomId;
    cout << "请输入要删除的房间号：";
    cin >> roomId;
    Room *room = findRoomById(roomId);

    if (room == nullptr) {
        cout << "该房间不存在。\n";
        return;
    }

    if (room->getIsOccupied()) {
        cout << "该房间当前有客人入住，无法删除。\n";
        return;
    }

    // 删除房间信息
    for (auto it = rooms.begin(); it != rooms.end(); ++it) {
        if (it->getId() == roomId) {
            rooms.erase(it);
            cout << "房间删除成功。\n";
            break;
        }
    }
}

//通过ID查找
Room *Manager::findRoomById(int roomId) {
    for (auto &room: rooms) {
        if (room.getId() == roomId) {
            return &room;
        }
    }
    return nullptr;
}

//通过名字查找
Guest *Manager::findGuestByName(const string &name) {
    for (auto &guestPair: guests) {
        if (guestPair.second.getName() == name) {
            return &guestPair.second;
        }
    }
    return nullptr;
}

// 保存数据
void Manager::saveData() {
    ofstream roomFile("rooms.dat", ios::binary);
    for (const auto &room: rooms) {
        roomFile << room << endl;
    }
    roomFile.close();

    ofstream guestFile("guests.dat", ios::binary);
    for (const auto &guestPair: guests) {
        guestFile << guestPair.second << endl;
    }
    guestFile.close();

    cout << "数据保存成功。\n";
}

// 加载数据
void Manager::loadData() {
    ifstream roomFile("rooms.dat", ios::binary);
    if (roomFile.is_open()) {
        Room room;
        while (roomFile >> room) {
            rooms.push_back(room);
        }
        roomFile.close();
    }

    ifstream guestFile("guests.dat", ios::binary);
    if (guestFile.is_open()) {
        Guest guest;
        int roomId;
        while (guestFile >> guest) {
            cin.ignore(); // 忽略换行符
            guests.emplace_back(roomId, guest); // 假设这里需要关联房间号，实际应用中需要根据具体情况调整
        }
        guestFile.close();
    }

    cout << "数据加载成功。\n";
}
