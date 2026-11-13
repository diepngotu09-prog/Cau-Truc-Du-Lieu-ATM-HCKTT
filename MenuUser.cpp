#include "MenuUser.h"

#include "ConsoleUtil.h"
#include "TheTu.h"
#include "QuanLyTaiKhoan.h"
#include "TaiKhoan.h"

using namespace std;

namespace {
    const int USER_XEM_THONG_TIN = 1;
    const int USER_RUT_TIEN = 2;
    const int USER_CHUYEN_TIEN = 3;
    const int USER_XEM_GIAO_DICH = 4;
    const int USER_DOI_MA_PIN = 5;
    const int USER_THOAT = 6;

    int docLuaChon(int iMin, int iMax) {
        while (true) {
            const long long llLuaChon =
                ConsoleUtil::nhapSoNguyen(" Lua chon: ");

            if (llLuaChon >= iMin && llLuaChon <= iMax) {
                return static_cast<int>(llLuaChon);
            }

            ConsoleUtil::inLoi(
                "Lua chon khong hop le, vui long nhap lai!"
            );
        }
    }
}

// Constructor
MenuUser::MenuUser(
    QuanLyTheTu& quanLyTheTu,
    const string& strID
) : _quanLyTheTu(quanLyTheTu), _strID(strID) {
}

// Chay menu
void MenuUser::chay() {
    bool bTiepTuc = true;

    while (bTiepTuc) {
        ConsoleUtil::xoaManHinh();
        this->hienThiMenu();

        switch (docLuaChon(USER_XEM_THONG_TIN, USER_THOAT)) {
        case USER_XEM_THONG_TIN:
            this->xemThongTin();
            break;

        case USER_RUT_TIEN:
            this->rutTien();
            break;

        case USER_CHUYEN_TIEN:
            this->chuyenTien();
            
            break;

        case USER_XEM_GIAO_DICH:
            this->xemGiaoDich();
            break;

        case USER_DOI_MA_PIN:
            this->doiMaPin();
            break;

        case USER_THOAT:
            bTiepTuc = false;
            break;

        default:
            break;
        }
    }
}

// Hien thi menu
void MenuUser::hienThiMenu() const {
    ConsoleUtil::inTieuDe("MENU USER");

    ConsoleUtil::inLuaChon(" 1. Xem thong tin tai khoan");
    ConsoleUtil::inLuaChon(" 2. Rut tien");
    ConsoleUtil::inLuaChon(" 3. Chuyen tien");
    ConsoleUtil::inLuaChon(" 4. Xem lich su giao dich");
    ConsoleUtil::inLuaChon(" 5. Doi ma PIN");
    ConsoleUtil::inLuaChon(" 6. Thoat");
}

void MenuUser::xemThongTin() {
    ConsoleUtil::xoaManHinh();
    ConsoleUtil::inTieuDe("THONG TIN TAI KHOAN");

    QuanLyTaiKhoan quanLyTaiKhoan;
    TaiKhoan tk;

    if (quanLyTaiKhoan.docFile(_strID, tk)) {
        quanLyTaiKhoan.xuatThongTin(tk);
    }
    else {
        ConsoleUtil::inLoi("Khong tim thay tai khoan!");
    }

    ConsoleUtil::tamDung();
}

void MenuUser::doiMaPin() {
    ConsoleUtil::xoaManHinh();
    ConsoleUtil::inTieuDe("DOI MA PIN");

    string strPINCu = ConsoleUtil::nhapDong(" Nhap PIN cu: ");
    string strPINMoi1 = ConsoleUtil::nhapDong(" Nhap PIN moi: ");
    string strPINMoi2 = ConsoleUtil::nhapDong(" Nhap lai PIN moi: ");

    if (_quanLyTheTu.doiPIN(
        _strID,
        strPINCu,
        strPINMoi1,
        strPINMoi2
    )) {
        ConsoleUtil::inThanhCong("Doi ma PIN thanh cong!");
    }
    else {
        ConsoleUtil::inLoi("Doi ma PIN that bai!");
    }

    ConsoleUtil::tamDung();
}
bool MenuUser::kiemTraSoTien(long long llSoTien) const {
    if (llSoTien <= 0) {
        ConsoleUtil::inLoi("So tien phai lon hon 0!");
        return false;
    }

    return true;
}

void MenuUser::rutTien() {
    ConsoleUtil::inLoi("Chuc nang rut tien chua duoc cai dat.");
    ConsoleUtil::tamDung();
}

void MenuUser::chuyenTien() {
    ConsoleUtil::inLoi("Chuc nang chuyen tien chua duoc cai dat.");
    ConsoleUtil::tamDung();
}

void MenuUser::xemGiaoDich() {
    ConsoleUtil::inLoi("Chuc nang xem giao dich chua duoc cai dat.");
    ConsoleUtil::tamDung();
}