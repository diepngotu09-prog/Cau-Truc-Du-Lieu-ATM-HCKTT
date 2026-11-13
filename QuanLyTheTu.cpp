#include "QuanLyTheTu.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cctype>

static string trim(const string& strChuoi) {
    size_t iDau = strChuoi.find_first_not_of(" \t\r\n");
    if (iDau == string::npos) return "";

    size_t iCuoi = strChuoi.find_last_not_of(" \t\r\n");

    return strChuoi.substr(iDau, iCuoi - iDau + 1);
}

static string layGiaTri(const string& strDong) {
    size_t iViTri = strDong.find(':');

    if (iViTri == string::npos) return "";

    return trim(strDong.substr(iViTri + 1));
}

static bool fileDaTonTai(const string& strDuongDan) {
    ifstream file(strDuongDan.c_str());
    return file.good();
}

bool QuanLyTheTu::docFile(const string& strDuongDan) {
    ifstream file(strDuongDan.c_str());

    if (!file.is_open()) return false;

    this->_lstDanhSachThe.xoaTatCa();
    this->_mapSoLanNhapSai.clear();

    const string DEFAULT_PIN = "123456";

    string strDongID;
    string strDongPIN;

    while (getline(file, strDongID)) {
        if (!getline(file, strDongPIN)) {
            break;
        }

        if (strDongID.find("Ma so tai khoan (ID):") != 0 || strDongPIN.find("Ma PIN:") != 0) {
            continue;
        }

        string strID = layGiaTri(strDongID);
        string strPIN = layGiaTri(strDongPIN);

        if (!TheTu::kiemTraID(strID) || !TheTu::kiemTraDinhDangPIN(strPIN)) {
            continue;
        }

        if (this->tonTai(strID)) {
            continue;
        }

        // Khoi tao the tu
        TheTu theTu(strID, strPIN, false, strPIN == DEFAULT_PIN);

        this->_lstDanhSachThe.themCuoi(theTu);
        this->_mapSoLanNhapSai[strID] = 0;
    }

    file.close();
    return true;
}

bool QuanLyTheTu::ghiFile(const string& strDuongDan) const {
    ofstream file(strDuongDan.c_str());

    if (!file.is_open()) return false;

    for (Node<TheTu>* pCurrent = this->_lstDanhSachThe.getHead(); pCurrent != nullptr; pCurrent = pCurrent->getNext()) {
        const TheTu& theTu = pCurrent->getData();
        file << "Ma so tai khoan (ID): " << theTu.getID() << '\n';
        file << "Ma PIN: " << theTu.getPIN() << '\n';
    }

    file.close();
    return true;
}

void QuanLyTheTu::hienThiDanhSach() const {
    cout << "\n========== DANH SACH THE TU ==========\n";

    if (this->_lstDanhSachThe.rong()) {
        cout << "Danh sach the tu trong!\n";
        return;
    }

    int iSTT = 1;

    for (Node<TheTu>* pCurrent = this->_lstDanhSachThe.getHead(); pCurrent != nullptr; pCurrent = pCurrent->getNext()) {
        const TheTu& theTu = pCurrent->getData();

        cout << "\nThe tu thu " << iSTT++ << '\n';
        cout << "ID: " << theTu.getID() << '\n';
        cout << "PIN: ******\n";

        cout << "Trang thai: " << (theTu.getBiKhoa() ? "Bi khoa" : "Hoat dong") << '\n';
    }
}

TheTu* QuanLyTheTu::timTheoID(const string& strID) {
    Node<TheTu>* pCurrent = this->_lstDanhSachThe.getHead();

    while (pCurrent != nullptr) {
        TheTu& theTu = pCurrent->getData();

        if (theTu.getID() == strID) {
            return &theTu;
        }
        pCurrent = pCurrent->getNext();
    }
    return nullptr;
}

const TheTu* QuanLyTheTu::timTheoID(const string& strID) const {
    Node<TheTu>* pCurrent = this->_lstDanhSachThe.getHead();

    while (pCurrent != nullptr) {
        const TheTu& theTu = pCurrent->getData();
        if (theTu.getID() == strID) {
            return &theTu;
        }
        pCurrent = pCurrent->getNext();
    }
    return nullptr;
}

bool QuanLyTheTu::tonTai(const string& strID) const {
    return this->timTheoID(strID) != nullptr;
}

bool QuanLyTheTu::themTaiKhoan(const string& strID, const string& strTenTaiKhoan, long long llSoDu, const string& strLoaiTien) {
    if (!TheTu::kiemTraID(strID) || strTenTaiKhoan.empty() || strLoaiTien.empty() || llSoDu < 0) {
        return false;
    }

    if (this->tonTai(strID)) {
        return false;
    }

    const string strDuongDanTaiKhoan = "data/" + strID + ".txt";
    const string strDuongDanLichSu = "data/LichSu" + strID + ".txt";

    // Khong ghi de file tai khoan da co
    if (fileDaTonTai(strDuongDanTaiKhoan) || fileDaTonTai(strDuongDanLichSu)) {
        return false;
    }

    ofstream fileTaiKhoan(strDuongDanTaiKhoan.c_str());

    if (!fileTaiKhoan.is_open()) {
        return false;
    }

    fileTaiKhoan << "Ma so tai khoan (ID): " << strID << '\n';
    fileTaiKhoan << "Ten chu tai khoan: " << strTenTaiKhoan << '\n';
    fileTaiKhoan << "So du: " << llSoDu << '\n';
    fileTaiKhoan << "Loai tien: " << strLoaiTien << '\n';

    fileTaiKhoan.close();

    ofstream fileLichSu(strDuongDanLichSu.c_str());

    if (!fileLichSu.is_open()) {
        std::remove(strDuongDanTaiKhoan.c_str());
        return false;
    }

    fileLichSu.close();

    TheTu theTu(strID, "123456", false, true);

    this->_lstDanhSachThe.themCuoi(theTu);
    this->_mapSoLanNhapSai[strID] = 0;

    if (!this->ghiFile()) {
        int iViTri = 0;
        Node<TheTu>* pCurrent = this->_lstDanhSachThe.getHead();

        while (pCurrent != nullptr) {
            if (pCurrent->getData().getID() == strID) break;

            pCurrent = pCurrent->getNext();
            ++iViTri;
        }

        if (pCurrent != nullptr) {
            this->_lstDanhSachThe.xoaTheoViTri(iViTri);
        }

        this->_mapSoLanNhapSai.erase(strID);

        std::remove(strDuongDanTaiKhoan.c_str());
        std::remove(strDuongDanLichSu.c_str());

        return false;
    }

    return true;
}

bool QuanLyTheTu::xoaTheTu(const string& strID) {
    TheTu* pTheTu = this->timTheoID(strID);

    if (pTheTu == nullptr) {
        return false;
    }

    TheTu theTuCu = *pTheTu;

    bool bDaXoa = false;

    int iViTri = 0;
    Node<TheTu>* pCurrent = this->_lstDanhSachThe.getHead();

    while (pCurrent != nullptr) {
        if (pCurrent->getData().getID() == strID) {
            this->_lstDanhSachThe.xoaTheoViTri(iViTri);

            bDaXoa = true;
            break;
        }
        pCurrent = pCurrent->getNext();
        ++iViTri;
    }

    if (!bDaXoa) return false;

    if (!this->ghiFile()) {
        this->_lstDanhSachThe.themCuoi(theTuCu);
        this->ghiFile();
        return false;
    }

    const string strDuongDanTaiKhoan = "data/" + strID + ".txt";

    std::remove(strDuongDanTaiKhoan.c_str());

    this->_mapSoLanNhapSai.erase(strID);

    return true;
}

bool QuanLyTheTu::moKhoa(const string& strID) {
    TheTu* pTheTu = this->timTheoID(strID);
    if (pTheTu == nullptr) {
        return false;
    }
    pTheTu->moKhoaThe();
    this->_mapSoLanNhapSai[strID] = 0;
    return true;
}

bool QuanLyTheTu::kiemTraDangNhap(const string& strID, const string& strPIN) {
    const int MAX_LAN_NHAP_SAI = 3;

    TheTu* pTheTu = this->timTheoID(strID);

    if (pTheTu == nullptr || pTheTu->getBiKhoa()) {
        cout << "The khong ton tai hoac da bi khoa!\n";
        return false;
    }

    if (pTheTu->kiemTraPIN(strPIN)) {
        this->_mapSoLanNhapSai[strID] = 0;
        return true;
    }

    ++this->_mapSoLanNhapSai[strID];

    int iSoLanConLai = MAX_LAN_NHAP_SAI - this->_mapSoLanNhapSai[strID];

    if (this->_mapSoLanNhapSai[strID] >= MAX_LAN_NHAP_SAI) {
        pTheTu->khoaThe();
        cout << "The da bi khoa do nhap sai PIN 3 lan!\n";
        return false;
    }

    cout << "PIN khong chinh xac! Ban con " << iSoLanConLai << " lan thu.\n";
    return false;
}

bool QuanLyTheTu::doiPIN(const string& strID, const string& strPINCu, const string& strPINMoi1, const string& strPINMoi2) {
    TheTu* pTheTu = this->timTheoID(strID);

    if (pTheTu == nullptr) return false;

    string strPINDaLuu = pTheTu->getPIN();
    bool bTrangThaiDoiPIN = pTheTu->getDoiPINLanDau();

    if (!pTheTu->doiPIN(strPINCu, strPINMoi1, strPINMoi2)) return false;

    if (!this->ghiFile()) {
        pTheTu->setPIN(strPINDaLuu);
        pTheTu->setDoiPINLanDau(bTrangThaiDoiPIN);

        return false;
    }
    return true;
}

int QuanLyTheTu::getSoLuongThe() const {
    return this->_lstDanhSachThe.kichThuoc();
}