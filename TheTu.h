#ifndef THETU_H
#define THETU_H

#include <string>

using namespace std;

class TheTu {
private:
    string _strID;
    string _strPIN;
    bool _bBiKhoa;
    bool _bDoiPINLanDau;

public:
    TheTu();
    TheTu(const string& strID, const string& strPIN, bool bBiKhoa = false, bool bDoiPINLanDau = true);
    string getID() const;
    string getPIN() const;
    bool getBiKhoa() const;
    bool getDoiPINLanDau() const;
    bool setPIN(const string& strPIN);

    void setBiKhoa(bool bBiKhoa);
    void setDoiPINLanDau(bool bDoiPINLanDau);

    static bool kiemTraID(const string& strID);
    static bool kiemTraDinhDangPIN(const string& strPIN);

    bool kiemTraPIN(const string& strPINNhap) const;
    bool doiPIN(const string& strPINCu, const string& strPINMoi1, const string& strPINMoi2);

    void khoaThe();
    void moKhoaThe();

    bool operator==(const TheTu& other) const;
};

#endif
