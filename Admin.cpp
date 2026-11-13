#include "Admin.h"

#include <sstream>

using namespace std;

Admin::Admin() {
	this->_strUser = "";
	this->_strPass = "";
}

Admin::Admin(const string& strUser, const string& strPass) {
	this->_strUser = strUser;
	this->_strPass = strPass;
}
Admin::Admin(const Admin& other) {
	this->_strUser = other._strUser;
	this->_strPass = other._strPass;
}

const string& Admin::getUser() const {
	return this->_strUser;
}

const string& Admin::getPass() const {
	return this->_strPass;
}

void Admin::setUser(const string& strUser) {
	this->_strUser = strUser;
}

void Admin::setPass(const string& strPass) {
	this->_strPass = strPass;
}

bool Admin::kiemTraMatKhau(const string& strPass) const {
	return this->_strPass == strPass;
}

string Admin::toFileLine() const {
	return this->_strUser + " " + this->_strPass;
}

bool Admin::parse(const string& strLine, Admin& admin) {
	istringstream issLine(strLine);
	string strUser;
	string strPass;

	// operator>> tu dong bo qua khoang trang, '\r' va '\t' thua
	if (!(issLine >> strUser >> strPass)) {
		return false;
	}

	admin.setUser(strUser);
	admin.setPass(strPass);
	return true;
}