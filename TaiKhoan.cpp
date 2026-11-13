#include "TaiKhoan.h"

// Hàm khởi tạo mặc định
TaiKhoan::TaiKhoan() {
    ID = "";
    tenChuTaiKhoan = "";
    soDu = 0;
    loaiTienTe = "VND";
}

// Hàm khởi tạo có tham số
TaiKhoan::TaiKhoan(string id, string ten, double tien, string loai) {
    ID = id;
    tenChuTaiKhoan = ten;
    soDu = tien;
    loaiTienTe = loai;
}

// Getter
string TaiKhoan::getID() const {
    return ID;
}

string TaiKhoan::getTenChuTaiKhoan() const {
    return tenChuTaiKhoan;
}

double TaiKhoan::getSoDu() const {
    return soDu;
}

string TaiKhoan::getLoaiTienTe() const {
    return loaiTienTe;
}

// Setter
void TaiKhoan::setID(string id) {
    ID = id;
}

void TaiKhoan::setTenChuTaiKhoan(string ten) {
    tenChuTaiKhoan = ten;
}

void TaiKhoan::setSoDu(double tien) {
    soDu = tien;
}

void TaiKhoan::setLoaiTienTe(string loai) {
    loaiTienTe = loai;
}