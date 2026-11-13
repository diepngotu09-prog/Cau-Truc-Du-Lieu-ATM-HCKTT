#include "QuanLyAdmin.h"

#include <filesystem>
#include <fstream>
#include <system_error>

#include "ConsoleUtil.h"

using namespace std;

namespace {
	const char* const DEFAULT_ADMIN_FILE = "data/Admin.txt";

	const char* const DEFAULT_ADMIN_USER_1 = "admin1";
	const char* const DEFAULT_ADMIN_PASS_1 = "admin123";
	const char* const DEFAULT_ADMIN_USER_2 = "admin2";
	const char* const DEFAULT_ADMIN_PASS_2 = "admin456";
	const char* const DEFAULT_ADMIN_USER_3 = "admin3";
	const char* const DEFAULT_ADMIN_PASS_3 = "admin789";
}

QuanLyAdmin::QuanLyAdmin() {
	this->_strFilePath = DEFAULT_ADMIN_FILE;
}

QuanLyAdmin::QuanLyAdmin(const string& strFilePath) {
	this->_strFilePath = strFilePath;
}

QuanLyAdmin::QuanLyAdmin(const QuanLyAdmin& other) {
	this->_strFilePath = other._strFilePath;
	this->_dsAdmin = other._dsAdmin;
}

bool QuanLyAdmin::taiDuLieu() {
	bool bDocDuoc = this->docFile();
	if (bDocDuoc && !this->_dsAdmin.rong()) {
		return true;
	}

	// File chua co hoac rong -> tao du lieu mac dinh
	return this->khoiTaoMacDinh();
}

bool QuanLyAdmin::docFile() {
	ifstream fileIn(this->_strFilePath);
	if (!fileIn.is_open()) {
		return false;
	}

	this->_dsAdmin.xoaTatCa();

	string strLine;
	while (getline(fileIn, strLine)) {
		Admin admin;
		if (!Admin::parse(strLine, admin)) {
			continue;
		}
		if (this->tonTai(admin.getUser())) {
			continue;
		}
		this->_dsAdmin.themCuoi(admin);
	}

	fileIn.close();
	return true;
}

bool QuanLyAdmin::ghiFile() const {
	filesystem::path pathFile(this->_strFilePath);
	if (pathFile.has_parent_path()) {
		error_code errCode;
		filesystem::create_directories(pathFile.parent_path(), errCode);
	}

	ofstream fileOut(this->_strFilePath);
	if (!fileOut.is_open()) {
		return false;
	}

	for (Node<Admin>* pNode = this->_dsAdmin.getHead(); pNode != nullptr; pNode = pNode->getNext()) {
		fileOut << pNode->getData().toFileLine() << '\n';
	}

	fileOut.close();
	return true;
}

bool QuanLyAdmin::khoiTaoMacDinh() {
	this->_dsAdmin.xoaTatCa();
	this->_dsAdmin.themCuoi(Admin(DEFAULT_ADMIN_USER_1, DEFAULT_ADMIN_PASS_1));
	this->_dsAdmin.themCuoi(Admin(DEFAULT_ADMIN_USER_2, DEFAULT_ADMIN_PASS_2));
	this->_dsAdmin.themCuoi(Admin(DEFAULT_ADMIN_USER_3, DEFAULT_ADMIN_PASS_3));

	return this->ghiFile();
}

bool QuanLyAdmin::dangNhap(const string& strUser, const string& strPass) const {
	Admin* pAdmin = this->_dsAdmin.timKiemTheo([&strUser](const Admin& admin) {
			return admin.getUser() == strUser;
		});

	if (pAdmin == nullptr) {
		return false;
	}
	return pAdmin->kiemTraMatKhau(strPass);
}

bool QuanLyAdmin::dangNhapAdmin() const {
	while (true) {
		ConsoleUtil::inTieuDe("DANG NHAP ADMIN");
		const string strUser = ConsoleUtil::nhapDong(" User: ");
		const string strPass = ConsoleUtil::nhapMatKhau(" Pin: ");

		if (this->dangNhap(strUser, strPass)) {
			return true;
		}

		ConsoleUtil::inThongBao("User hoac mat khau khong dung!");
		if (!ConsoleUtil::xacNhan("Ban co muon dang nhap lai")) {
			return false;
		}
		ConsoleUtil::xoaManHinh();
	}
}

bool QuanLyAdmin::tonTai(const string& strUser) const {
	return this->_dsAdmin.timKiemTheo([&strUser](const Admin& admin) {
			return admin.getUser() == strUser;
		}) != nullptr;
}

int QuanLyAdmin::soLuong() const {
	return this->_dsAdmin.kichThuoc();
}

const LinkedList<Admin>& QuanLyAdmin::getDanhSach() const {
	return this->_dsAdmin;
}