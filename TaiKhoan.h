#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class TaiKhoan {
private:
    string ID;
    string tenChuTaiKhoan;
    double soDu;
    string loaiTienTe;

public:
    TaiKhoan();

    TaiKhoan(string id, string ten, double tien, string loai);

    string getID() const;
    string getTenChuTaiKhoan() const;
    double getSoDu() const;
    string getLoaiTienTe() const;

    void setID(string id);
    void setTenChuTaiKhoan(string ten);
    void setSoDu(double tien);
    void setLoaiTienTe(string loai);
};