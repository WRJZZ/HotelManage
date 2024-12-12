#include "Manager.h"
#include <iostream>
#include <iomanip>
#include "Guest.h"
#include "Room.h"
#include <algorithm>
#include <sstream>
using namespace std;

void Manager::start() {
    loadData(); // 加载数据

    char choice;
    do {
        cout << "\n宾馆客房管理系统\n"
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
    int daysBooked = 0; // 初始化预定天数为0
    double prePayment;

    cout << "请输入入住的房间号：";
    cin >> roomId;
    Room *room = findRoomById(roomId);

    if (room == nullptr || room->getIsOccupied()) {
        cout << "该房间不存在或已被占用。\n";
        return;
    }

    cout << "请输入客人姓名：";
    cin.ignore(); // 忽略之前的换行符
    getline(cin, name);
    cout << "请输入客人身份证号：";
    getline(cin, idNumber);
    cout << "请输入入住时间（格式：YYYY-MM-DD HH:MM）：";
    getline(cin, checkInTime);

    // 提示用户输入预定天数
    cout << "请输入预定天数：";
    cin >> daysBooked;

    cout << "请输入预付费用：";
    cin >> prePayment;

    // 正确地使用 emplace_back 添加新客人到 guests 向量中
    guests.emplace_back(std::piecewise_construct,
                        std::forward_as_tuple(roomId),
                        std::forward_as_tuple(name, idNumber, checkInTime, roomId, daysBooked, prePayment));

    room->setIsOccupied(true);
    cout << "入住登记完成。\n";
}

// 客人退房结算
void Manager::checkOut() {
    int roomId;
    std::cout << "请输入退房的房间号：";
    std::cin >> roomId;

    // 查找房间并检查是否已被占用
    Room *room = findRoomById(roomId);
    if (room == nullptr || !room->getIsOccupied()) {
        std::cout << "该房间不存在或未被占用。\n";
        return;
    }

    // 查找对应房间的客人信息
    auto it = guests.begin();
    for (; it != guests.end(); ++it) {
        if (it->first == roomId) {
            break;
        }
    }

    // 如果找到了对应的客人信息
    if (it != guests.end()) {
        // 显示客人的基本信息
        std::cout << "姓名：" << it->second.getName()
                << " 身份证号：" << it->second.getIdNumber()
                << " 房间号：" << it->second.getRoomId()
                << " 预定天数：" << it->second.getDaysBooked()
                << " 房间类型：" << roomTypeInfo.at(room->getType()).first
                << " 预付费用：" << it->second.getPrePayment() << std::endl;

        // 提示用户输入实际居住天数
        std::cout << "顾客实际住了几天：";
        int actualDaysStayed;
        std::cin >> actualDaysStayed;

        // 计算最终费用
        double pricePerDay = room->getPrice(); // 获取房间单价
        double totalCharge = actualDaysStayed * pricePerDay; // 计算总费用
        double finalCharge = it->second.getPrePayment() - totalCharge; // 计算最终费用

        // 设置实际居住天数和最终费用
        it->second.setActualDaysStayed(actualDaysStayed);
        it->second.setFinalCharge(finalCharge);
        it->second.markAsSettled();

        // 输出最终费用情况
        if (finalCharge > 0) {
            std::cout << "需要退还顾客 " << finalCharge << " 元" << std::endl;
        } else if (finalCharge < 0) {
            std::cout << "顾客还需要支付 " << -finalCharge << " 元" << std::endl;
        } else {
            std::cout << "费用已结清" << std::endl;
        }

        // 更新房间状态为空闲
        room->setIsOccupied(false);

        // 移除客人信息
        guests.erase(it);

        std::cout << "退房结算完成。\n";
    } else {
        std::cout << "没有找到该房间的客人信息。\n";
    }
}

// 浏览全部客房信息
void Manager::browseRooms() {
    cout << "所有客房信息如下：\n";
    if (rooms.empty()) {
        cout << "当前无任何客房信息。\n";
    } else {
        for (const auto &room: rooms) {
            room.show();
        }
    }
}

void Manager::queryRoom() {
    int choice;
    cout << "查询方式：\n1. 查询空房间\n2. 按姓名查询\n3. 按房间号查询\n请选择：";
    cin >> choice;

    switch (choice) {
        case 1: {
            cout << "空闲房间如下：\n";
            bool found = false;
            for (const auto &room: rooms) {
                if (!room.getIsOccupied()) {
                    room.show();
                    found = true;
                }
            }
            if (!found) {
                cout << "当前无空闲房间。\n";
            }
            break;
        }
        case 2: {
            string name;
            cout << "请输入要查询的客人姓名：";
            cin.ignore(); // 忽略之前的换行符
            getline(cin, name);
            bool found = false;
            for (const auto &[roomId, guest]: guests) {
                if (guest.getName() == name) {
                    Room *room = findRoomById(roomId);
                    if (room != nullptr) {
                        room->show();
                        cout << "客人：" << guest.getName()
                                << ", 入住时间：" << guest.getCheckInTime()
                                << ", 预付费用：" << guest.getPrePayment() << "\n";
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
                if (room->getIsOccupied()) {
                    for (const auto &[id, guest]: guests) {
                        if (id == roomId) {
                            cout << "客人：" << guest.getName()
                                    << ", 入住时间：" << guest.getCheckInTime()
                                    << ", 预付费用：" << guest.getPrePayment() << "\n";
                            break;
                        }
                    }
                } else {
                    cout << "该房间当前为空闲状态。\n";
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

void Manager::modifyRoom() {
    int roomId, typeChoice;
    RoomType type;
    double price = 0.0;

    cout << "请输入要修改的房间号（输入0取消）：";
    cin >> roomId;

    if (roomId == 0) {
        cout << "取消修改。\n";
        return;
    }

    Room *room = findRoomById(roomId);

    if (room == nullptr) {
        cout << "该房间不存在。\n";
        return;
    }

    cout << "当前房间信息：\n";
    room->show();

    cout << "请选择新的房间类型（输入0保持不变）：\n"
            << "1 - 单人间（100元/天）\n"
            << "2 - 双人间（200元/天）\n"
            << "3 - 家庭房（300元/天）\n"
            << "4 - 总统套房（500元/天）\n"
            << "请选择：";
    cin >> typeChoice;

    if (typeChoice == 0) {
        cout << "房间类型未更改。\n";
        return;
    }

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

void Manager::deleteRoom() {
    int roomId;
    cout << "请输入要删除的房间号（输入0取消）：";
    cin >> roomId;

    if (roomId == 0) {
        cout << "取消删除。\n";
        return;
    }

    auto it = std::find_if(rooms.begin(), rooms.end(), [roomId](const Room &room) {
        return room.getId() == roomId;
    });

    if (it == rooms.end()) {
        cout << "该房间不存在。\n";
        return;
    }

    if (it->getIsOccupied()) {
        cout << "该房间当前有客人入住，无法删除。\n";
        return;
    }

    // 删除房间信息
    rooms.erase(it);
    cout << "房间删除成功。\n";
}

//通过ID查找
Room *Manager::findRoomById(int roomId) {
    auto it = std::find_if(rooms.begin(), rooms.end(), [roomId](const Room &room) {
        return room.getId() == roomId;
    });
    return it != rooms.end() ? &(*it) : nullptr;
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
    ofstream roomFile("rooms.dat", ios::binary | ios::trunc);
    if (!roomFile.is_open()) {
        cerr << "无法打开房间数据文件进行保存。\n";
        return;
    }
    for (const auto &room: rooms) {
        roomFile << room << endl;
    }
    roomFile.close();

    ofstream guestFile("guests.dat", ios::binary | ios::trunc);
    if (!guestFile.is_open()) {
        cerr << "无法打开客人数据文件进行保存。\n";
        return;
    }
    for (const auto &[roomId, guest]: guests) {
        guestFile << roomId << ' ' << guest << endl;
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
    } else {
        cout << "没有找到房间数据文件，将从头开始。\n";
    }

    ifstream guestFile("guests.dat", ios::binary);
    if (guestFile.is_open()) {
        int roomId;
        Guest guest;
        std::string line;
        while (getline(guestFile, line)) {
            std::istringstream iss(line);
            if (iss >> roomId >> guest) {
                guests.emplace_back(roomId, guest);
            }
        }
        guestFile.close();
    } else {
        cout << "没有找到客人数据文件，将从头开始。\n";
    }

    cout << "数据加载成功。\n";
}
