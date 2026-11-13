#include "QuanLyTaiKhoan.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool QuanLyTaiKhoan::docFile(string ID, TaiKhoan& tk) {
    string tenFile = "data/" + ID + ".txt";
    ifstream file(tenFile);

    if (!file.is_open()) {
        return false;
    }

    string dong;

    // Doc ID
    if (!getline(file, dong)) return false;
    size_t viTri = dong.find(':');
    if (viTri == string::npos) return false;
    tk.setID(dong.substr(viTri + 1));

    // Doc ten tai khoan
    if (!getline(file, dong)) return false;
    viTri = dong.find(':');
    if (viTri == string::npos) return false;
    tk.setTenChuTaiKhoan(dong.substr(viTri + 1));

    // Doc so du
    if (!getline(file, dong)) return false;
    viTri = dong.find(':');
    if (viTri == string::npos) return false;

    try {
        tk.setSoDu(stod(dong.substr(viTri + 1)));
    }
    catch (...) {
        return false;
    }

    // Doc don vi tien te
    if (!getline(file, dong)) return false;
    viTri = dong.find(':');
    if (viTri == string::npos) return false;
    tk.setLoaiTienTe(dong.substr(viTri + 1));

    file.close();
    return true;
}

bool QuanLyTaiKhoan::ghiFile(const TaiKhoan& tk) {
    string tenFile = "data/" + tk.getID() + ".txt";
    ofstream file(tenFile);

    if (!file.is_open()) return false;

    file << "ID: " << tk.getID() << endl;
    file << "Ten tai khoan: " << tk.getTenChuTaiKhoan() << endl;
    file << "So du tai khoan: " << tk.getSoDu() << endl;
    file << "Don vi: " << tk.getLoaiTienTe() << endl;

    file.close();
    return true;
}

void QuanLyTaiKhoan::xuatThongTin(const TaiKhoan& tk) {
    cout << "ID: " << tk.getID() << endl;
    cout << "Ten tai khoan: " << tk.getTenChuTaiKhoan() << endl;
    cout << "So du tai khoan: " << tk.getSoDu() << endl;
    cout << "Don vi: " << tk.getLoaiTienTe() << endl;
}

vector<string> QuanLyTaiKhoan::docDanhSachID() {
    vector<string> dsID;
    ifstream file("Data/DanhSachID.txt");

    string ID;
    while (getline(file, ID)) {
        if (!ID.empty())
            dsID.push_back(ID);
    }

    file.close();
    return dsID;
}

bool QuanLyTaiKhoan::kiemTraTrungID(string ID) {
    vector<string> dsID = docDanhSachID();

    for (const string& id : dsID) {
        if (id == ID) {
            return true; // ID đã tồn tại
        }
    }

    return false; // ID chưa tồn tại
}