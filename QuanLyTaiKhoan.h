#pragma once
#include "TaiKhoan.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class QuanLyTaiKhoan {
public:
    bool docFile(string ID, TaiKhoan& tk);
    bool ghiFile(const TaiKhoan& tk);
    void xuatThongTin(const TaiKhoan& tk);

    vector<string> docDanhSachID();
    bool kiemTraTrungID(string ID);
};