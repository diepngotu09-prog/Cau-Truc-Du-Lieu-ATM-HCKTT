#ifndef ADMIN_H_INCLUDED_
#define ADMIN_H_INCLUDED_

#include <string>
using namespace std;
/**********************************************************
* @Description Thong tin mot tai khoan Admin (user, pass)
* @attention Dinh dang 1 dong trong Admin.txt: "<user> <pass>"
*            (user va pass khong duoc chua khoang trang)
**********************************************************/
class Admin {
private:
	string _strUser;
	string _strPass;
public:
	Admin();
	Admin(const string& strUser, const string& strPass);
	Admin(const Admin& other);

	const string& getUser() const;
	const string& getPass() const;

	void setUser(const string& strUser);
	void setPass(const string& strPass);

	/**********************************************************
	* @Description Kiem tra mat khau nhap vao co khop voi pass cua Admin
	*
	* @return true neu khop
	**********************************************************/
	bool kiemTraMatKhau(const string& strPass) const;

	/**********************************************************
	* @Description Chuyen Admin thanh 1 dong de ghi vao file
	*
	* @return Chuoi dang "<user> <pass>" (khong co ky tu xuong dong)
	**********************************************************/
	string toFileLine() const;

	/**********************************************************
	* @Description Doc 1 dong cua file Admin.txt thanh doi tuong Admin
	*
	* @return true neu dong hop le (du user va pass); false neu ngc lai
	* @attention Dong rong hoac thieu pass se tra ve false, admin giu nguyen
	**********************************************************/
	static bool parse(const string& strLine, Admin& admin);

};

#endif