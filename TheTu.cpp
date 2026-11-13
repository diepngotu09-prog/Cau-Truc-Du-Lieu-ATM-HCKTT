#include "TheTu.h"

TheTu::TheTu() {
    this->_strID = "";
    this->_strPIN = "123456";
    this->_bBiKhoa = false;
    this->_bDoiPINLanDau = true;
}

TheTu::TheTu(const string& strID, const string& strPIN, bool bBiKhoa, bool bDoiPINLanDau) {
    this->_strID = strID;
    this->_strPIN = strPIN;
    this->_bBiKhoa = bBiKhoa;
    this->_bDoiPINLanDau = bDoiPINLanDau;
}

string TheTu::getID() const { return this->_strID; }
string TheTu::getPIN() const { return this->_strPIN; }

bool TheTu::getBiKhoa() const { return this->_bBiKhoa; }
bool TheTu::getDoiPINLanDau() const { return this->_bDoiPINLanDau; }
bool TheTu::setPIN(const string& strPIN) {
    if (!TheTu::kiemTraDinhDangPIN(strPIN)) {
        return false;
    }
    this->_strPIN = strPIN;
    this->_bDoiPINLanDau = (strPIN == "123456");
    return true;
}

void TheTu::setBiKhoa(bool bBiKhoa) { this->_bBiKhoa = bBiKhoa; }
void TheTu::setDoiPINLanDau(bool bDoiPINLanDau) { this->_bDoiPINLanDau = bDoiPINLanDau; }

bool TheTu::kiemTraID(const string& strID) {
    if (strID.length() != 14) {
        return false;
    }

    for (char cKyTu : strID) {
        if (cKyTu < '0' || cKyTu > '9') {
            return false;
        }
    }
    return true;
}

bool TheTu::kiemTraDinhDangPIN(const string& strPIN) {
    if (strPIN.length() != 6) {
        return false;
    }

    for (char cKyTu : strPIN) {
        if (cKyTu < '0' || cKyTu > '9')
        {
            return false;
        }
    }
    return true;
}

bool TheTu::kiemTraPIN(const string& strPINNhap) const {
    if (this->_bBiKhoa) {
        return false;
    }
    return this->_strPIN == strPINNhap;
}

bool TheTu::doiPIN(const string& strPINCu, const string& strPINMoi1, const string& strPINMoi2) {
    if (this->_bBiKhoa) return false;

    if (strPINCu != this->_strPIN) return false;

    if (strPINMoi1 != strPINMoi2) return false;

    if (!TheTu::kiemTraDinhDangPIN(strPINMoi1)) return false;

    if (strPINMoi1 == this->_strPIN || strPINMoi1 == "123456") return false;

    this->_strPIN = strPINMoi1;
    this->_bDoiPINLanDau = false;

    return true;
}

void TheTu::khoaThe() { this->_bBiKhoa = true; }
void TheTu::moKhoaThe() { this->_bBiKhoa = false; }

bool TheTu::operator==(const TheTu& other) const {
    return this->_strID == other._strID;
}