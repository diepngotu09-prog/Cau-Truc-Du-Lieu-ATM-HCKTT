#ifndef QUANLYADMIN_H_INCLUDED_
#define QUANLYADMIN_H_INCLUDED_

#include <string>

#include "Admin.h"
#include "LinkedList.h"

using namespace std;
/**********************************************************
* @Description Quan ly danh sach Admin (LinkedList<Admin>) va file Admin.txt
* @attention Neu Admin.txt chua ton tai hoac rong, taiDuLieu() se tu dong
*            tao file voi 3 Admin mac dinh (xem khoiTaoMacDinh)
**********************************************************/
class QuanLyAdmin {
private:
	string _strFilePath;
	LinkedList<Admin> _dsAdmin;
public:
	QuanLyAdmin();
	explicit QuanLyAdmin(const string& strFilePath);
	QuanLyAdmin(const QuanLyAdmin& other);

	/**********************************************************
	* @Description Nap danh sach Admin tu file; neu file khong co hoac
	*              rong thi tao du lieu mac dinh va ghi ra file
	*
	* @return true neu sau khi goi, danh sach co du lieu va file hop le
	**********************************************************/
	bool taiDuLieu();

	/**********************************************************
	* @Description Doc file Admin.txt vao danh sach (xoa du lieu cu)
	*
	* @return false neu khong mo duoc file
	* @attention Bo qua dong sai dinh dang va user bi trung
	**********************************************************/
	bool docFile();

	/**********************************************************
	* @Description Ghi toan bo danh sach Admin ra file Admin.txt
	*
	* @return false neu khong mo duoc file de ghi
	* @attention Tu tao thu muc cha (data/) neu chua co
	**********************************************************/
	bool ghiFile() const;

	/**********************************************************
	* @Description Tao 3 Admin mac dinh va ghi ra file
	*
	* @return false neu ghi file that bai
	**********************************************************/
	bool khoiTaoMacDinh();

	/**********************************************************
	* @Description Kiem tra dang nhap Admin (khong tuong tac console)
	*
	* @return true neu user ton tai trong danh sach va pass dung
	**********************************************************/
	bool dangNhap(const string& strUser, const string& strPass) const;


	/**********************************************************
	* @Description Hien man hinh DANG NHAP ADMIN: nhap user, nhap pass
	*              (hien thi dau *), cho nhap sai toi da 3 lan
	*
	* @return true neu dang nhap thanh cong; false neu sai qua 3 lan
	**********************************************************/
	bool dangNhapAdmin() const;

	bool tonTai(const string& strUser) const;

	int soLuong() const;

	const LinkedList<Admin>& getDanhSach() const;
};

#endif