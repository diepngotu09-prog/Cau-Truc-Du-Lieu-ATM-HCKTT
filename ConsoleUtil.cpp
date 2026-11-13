#include "ConsoleUtil.h"

#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#ifdef _WIN32
#define NOMINMAX
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

namespace {
	const int KEY_ENTER_CR = 13;
	const int KEY_ENTER_LF = 10;
	const int KEY_BACKSPACE_WIN = 8;
	const int KEY_BACKSPACE_UNIX = 127;
	const int KEY_SPECIAL_1 = 0;
	const int KEY_SPECIAL_2 = 224;
	const int KEY_PRINTABLE_MIN = 32;
	const int KEY_PRINTABLE_MAX = 126;

	const int TITLE_STAR_COUNT = 21;
	const size_t MAX_DIGITS_NUMBER = 18;
	const char* const WHITESPACE_CHARS = " \t\r\n";

	// Bang mau cua chuong trinh: doi mau chi can sua o day
	const ConsoleColor COLOR_TITLE = LIGHT_CYAN;
	const ConsoleColor COLOR_SUCCESS = LIGHT_GREEN;
	const ConsoleColor COLOR_ERROR = LIGHT_RED;
	const ConsoleColor COLOR_WARNING = LIGHT_YELLOW;
	const ConsoleColor COLOR_INF = LIGHT_BLUE;
	const ConsoleColor COLOR_OPTION = LIGHT_MAGENTA;

#ifdef _WIN32
	const WORD WIN_ATTR_COLOR_MASK = 0x000F;
	const WORD WIN_ATTR_FALLBACK = 7;

	/**********************************************************
	* @Description Lay thuoc tinh mau mac dinh cua console (chi lay 1 lan,
	*              truoc khi chuong trinh doi mau)
	**********************************************************/
	WORD layThuocTinhMacDinh() {
		static const WORD wMacDinh = []() {
			CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
			if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo)) {
				return csbiInfo.wAttributes;
			}
			return WIN_ATTR_FALLBACK;
			}();
		return wMacDinh;
	}
#endif
}

void ConsoleUtil::xoaManHinh() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void ConsoleUtil::setMau(ConsoleColor eMau) {
#ifdef _WIN32
	// Giu mau nen, chi doi mau chu
	const WORD wMacDinh = layThuocTinhMacDinh();
	const WORD wMauMoi = (wMacDinh & ~WIN_ATTR_COLOR_MASK) | static_cast<WORD>(eMau);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wMauMoi);
#else
	// Windows: bit 1 = blue, 2 = green, 4 = red; ANSI: 1 = red, 2 = green, 4 = blue
	const int iBase = static_cast<int>(eMau) & 7;
	const int iAnsi = ((iBase & 4) ? 1 : 0) | ((iBase & 2) ? 2 : 0) | ((iBase & 1) ? 4 : 0);
	const int iCode = (static_cast<int>(eMau) >= 8 ? 90 : 30) + iAnsi;
	cout << "\033[" << iCode << "m";
#endif
}

void ConsoleUtil::resetMau() {
#ifdef _WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), layThuocTinhMacDinh());
#else
	cout << "\033[0m";
#endif
}

void ConsoleUtil::inTieuDe(const string& strTieuDe) {
	string strBorder;
	for (int iIndex = 0; iIndex < TITLE_STAR_COUNT; ++iIndex) {
		strBorder += "* ";
	}

	ConsoleUtil::setMau(COLOR_TITLE);
	cout << strBorder << '\n';
	cout << " * " << strTieuDe << " *" << '\n';
	cout << strBorder << '\n';
	ConsoleUtil::resetMau();
}

void ConsoleUtil::inThongBao(const string& strNoiDung) {
	ConsoleUtil::inVoiMau(strNoiDung, COLOR_INF);
}

void ConsoleUtil::inLuaChon(const string& strNoiDung) {
	ConsoleUtil::inVoiMau(strNoiDung, COLOR_OPTION);
}

void ConsoleUtil::inThanhCong(const string& strNoiDung) {
	ConsoleUtil::inVoiMau(strNoiDung, COLOR_SUCCESS);
}

void ConsoleUtil::inLoi(const string& strNoiDung) {
	ConsoleUtil::inVoiMau(strNoiDung, COLOR_ERROR);
}

void ConsoleUtil::inCanhBao(const string& strNoiDung) {
	ConsoleUtil::inVoiMau(strNoiDung, COLOR_WARNING);
}

string ConsoleUtil::nhapMatKhau(const string& strNhan, size_t iDoDaiToiDa, bool bChiNhanSo) {
	string strMatKhau;
	cout << strNhan << flush;

	while (true) {
		const int iKey = ConsoleUtil::docPhim();
		if (iKey == KEY_ENTER_CR || iKey == KEY_ENTER_LF) {
			break;
		}

		if (iKey == KEY_BACKSPACE_WIN || iKey == KEY_BACKSPACE_UNIX) {
			if (!strMatKhau.empty()) {
				strMatKhau.pop_back();
				cout << "\b \b" << flush;
			}
			continue;
		}

#ifdef _WIN32
		// Phim dac biet (mui ten, F1...) tra ve 2 ma, bo qua ma thu hai
		if (iKey == KEY_SPECIAL_1 || iKey == KEY_SPECIAL_2) {
			ConsoleUtil::docPhim();
			continue;
		}
#endif

		if (iKey < KEY_PRINTABLE_MIN || iKey > KEY_PRINTABLE_MAX) {
			continue;
		}
		if (bChiNhanSo && !isdigit(iKey)) {
			continue;
		}
		if (iDoDaiToiDa > 0 && strMatKhau.size() >= iDoDaiToiDa) {
			continue;
		}

		strMatKhau += static_cast<char>(iKey);
		cout << '*' << flush;
	}

	cout << '\n';
	return strMatKhau;
}

string ConsoleUtil::nhapDong(const string& strNhan) {
	cout << strNhan << flush;

	string strLine;
	getline(cin, strLine);

	const size_t iFirst = strLine.find_first_not_of(WHITESPACE_CHARS);
	if (iFirst == string::npos) {
		return "";
	}
	const size_t iLast = strLine.find_last_not_of(WHITESPACE_CHARS);
	return strLine.substr(iFirst, iLast - iFirst + 1);
}

long long ConsoleUtil::nhapSoNguyen(const string& strNhan) {
	long long llGiaTri = 0;
	while (!ConsoleUtil::chuyenSoNguyen(ConsoleUtil::nhapDong(strNhan), llGiaTri)) {
		ConsoleUtil::inLoi("Gia tri khong hop le, vui long nhap lai!");
	}
	return llGiaTri;
}

bool ConsoleUtil::chuyenSoNguyen(const string& strChuoi, long long& llGiaTri) {
	if (strChuoi.empty() || strChuoi.size() > MAX_DIGITS_NUMBER) {
		return false;
	}

	long long llKetQua = 0;
	for (size_t iIndex = 0; iIndex < strChuoi.size(); ++iIndex) {
		const char cChar = strChuoi[iIndex];
		if (!isdigit(static_cast<unsigned char>(cChar))) {
			return false;
		}
		llKetQua = llKetQua * 10 + (cChar - '0');
	}

	llGiaTri = llKetQua;
	return true;
}

bool ConsoleUtil::xacNhan(const string& strCauHoi) {
	while (true) {
		const string strTraLoi = ConsoleUtil::nhapDong(strCauHoi + " (Y/N): ");
		if (strTraLoi == "Y" || strTraLoi == "y") {
			return true;
		}
		if (strTraLoi == "N" || strTraLoi == "n") {
			return false;
		}
		ConsoleUtil::inLoi("Chi nhap Y hoac N!");
	}
}

void ConsoleUtil::tamDung() {
	cout << "Nhan Enter de tiep tuc..." << flush;
	string strBoQua;
	getline(cin, strBoQua);
}

int ConsoleUtil::docPhim() {
#ifdef _WIN32
	return _getch();
#else
	termios termOld;
	tcgetattr(STDIN_FILENO, &termOld);

	termios termRaw = termOld;
	termRaw.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &termRaw);

	const int iKey = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &termOld);
	return iKey;
#endif
}

void ConsoleUtil::inVoiMau(const string& strNoiDung, ConsoleColor eMau) {
	ConsoleUtil::setMau(eMau);
	cout << strNoiDung << '\n';
	ConsoleUtil::resetMau();
}