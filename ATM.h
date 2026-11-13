#ifndef ATM_H_INCLUDED_
#define ATM_H_INCLUDED_

#include <string>

#include "QuanLyAdmin.h"
#include "QuanLyTheTu.h"
#include "TheTu.h"
#include "TaiKhoan.h"
#include "QuanLyTaiKhoan.h"

using namespace std;

/**********************************************************
* @Description Lop dieu khien chuong trinh may ATM: nap du lieu,
*              menu chinh, dang nhap Admin / User, menu User
* @attention Cac chuc nang Xem thong tin, Rut tien, Chuyen tien,
*            Xem giao dich cua User chua cai dat (TODO)
**********************************************************/
class ATM {
private:
	QuanLyAdmin _quanLyAdmin;
	QuanLyTheTu _quanLyTheTu;
	QuanLyTaiKhoan _quanLyTaiKhoan;
	bool _bThoat;

	/**********************************************************
	* @Description Nap Admin.txt va TheTu.txt; neu chua co TheTu.txt
	*              thi tao 10 the tu mau cung file [ID].txt, LichSu[ID].txt
	*
	* @return false neu khong nap/khoi tao duoc du lieu
	**********************************************************/
	bool taiDuLieu();
	bool khoiTaoDuLieuMau();

	void hienThiMenuChinh() const;
	void hienThiMenuUser() const;

	void dangNhapAdmin();
	void dangNhapUser();
	void chayMenuUser(TheTu& theTu);

	/**********************************************************
	* @Description Bat buoc doi ma PIN mac dinh o lan dang nhap dau tien
	*
	* @return false neu doi that bai (phien dang nhap bi huy)
	**********************************************************/
	bool doiPinLanDau(TheTu& theTu);

	/**********************************************************
	* @Description Doi ma PIN tu menu User: xac nhan PIN cu truoc khi doi
	**********************************************************/
	void doiPinTuMenu(TheTu& theTu);

	/**********************************************************
	* @Description Nhap ma PIN moi 2 lan, kiem tra va cap nhat (ghi TheTu.txt)
	*
	* @return true neu doi thanh cong
	**********************************************************/
	bool nhapVaDoiPin(TheTu& theTu);

	/**********************************************************
	* @Description Kiem tra ma PIN moi hop le
	*
	* @return Chuoi rong neu hop le; nguoc lai la noi dung loi
	**********************************************************/
	string kiemTraPinMoi(const TheTu& theTu,
		const string& strPinMoi,
		const string& strXacNhan) const;
public:
	ATM();
	void chay();
};

#endif