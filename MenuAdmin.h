#ifndef MENUADMIN_H_INCLUDED_
#define MENUADMIN_H_INCLUDED_

#include <string>

#include "QuanLyTheTu.h"

using namespace std;

/**********************************************************
* @Description Menu chuc nang cua Admin: xem danh sach, them, xoa,
*              mo khoa tai khoan (thao tac tren QuanLyTheTu)
* @attention Chi tao sau khi Admin da dang nhap thanh cong
**********************************************************/
class MenuAdmin {
private:
	QuanLyTheTu& _quanLyTheTu;

	void hienThiMenu() const;
	void xemDanhSach() const;
	void themTaiKhoan();
	void xoaTaiKhoan();
	void moKhoaTaiKhoan();

	/**********************************************************
	* @Description Nhap ID 14 chu so
	*
	* @return false neu ID sai dinh dang (da thong bao loi)
	**********************************************************/
	bool nhapId(string& strId) const;

public:
	explicit MenuAdmin(QuanLyTheTu& quanLyTheTu);

	void chay();
};

#endif