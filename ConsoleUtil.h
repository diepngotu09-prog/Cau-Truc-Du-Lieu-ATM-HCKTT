#ifndef CONSOLEUTIL_H_INCLUDED_
#define CONSOLEUTIL_H_INCLUDED_

#include <cstddef>
#include <string>

/**********************************************************
* @Description Ma mau console (0-15, trung voi bang mau Windows)
**********************************************************/
enum ConsoleColor {
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	YELLOW = 6,
	WHITE = 7,
	GRAY = 8,
	LIGHT_BLUE = 9,
	LIGHT_GREEN = 10,
	LIGHT_CYAN = 11,
	LIGHT_RED = 12,
	LIGHT_MAGENTA = 13,
	LIGHT_YELLOW = 14,
	BRIGHT_WHITE = 15
};

/**********************************************************
* @Description Cac ham tien ich cho giao dien console: mau sac, tieu de,
*              nhap mat khau an (*), nhap so, xac nhan Y/N
* @attention Class chi chua ham static, khong tao doi tuong.
*            Ho tro Windows (conio, WinAPI) va Linux/macOS (termios, ANSI).
*            Bang mau cua chuong trinh nam trong ConsoleUtil.cpp
*            (COLOR_TITLE, COLOR_SUCCESS, COLOR_ERROR, COLOR_WARNING)
**********************************************************/
class ConsoleUtil {
public:
	ConsoleUtil() = delete;

	static void xoaManHinh();

	/**********************************************************
	* @Description Doi mau chu cua console (giu nguyen mau nen)
	**********************************************************/
	static void setMau(ConsoleColor eMau);

	/**********************************************************
	* @Description Tra mau chu ve mau mac dinh ban dau cua console
	**********************************************************/
	static void resetMau();

	/**********************************************************
	* @Description In tieu de trong khung dau sao (mau tieu de)
	**********************************************************/
	static void inTieuDe(const std::string& strTieuDe);

	/**********************************************************
	* @Description In mot dong thong bao thuong
	**********************************************************/
	static void inThongBao(const std::string& strNoiDung);

	/**********************************************************
	* @Description In cac lua chon (mau tim)
	**********************************************************/
	static void inLuaChon(const std::string& strNoiDung);

	/**********************************************************
	* @Description In mot dong thong bao thanh cong (mau xanh la)
	**********************************************************/
	static void inThanhCong(const std::string& strNoiDung);

	/**********************************************************
	* @Description In mot dong thong bao loi (mau do)
	**********************************************************/
	static void inLoi(const std::string& strNoiDung);

	/**********************************************************
	* @Description In mot dong canh bao / huy thao tac (mau vang)
	**********************************************************/
	static void inCanhBao(const std::string& strNoiDung);

	/**********************************************************
	* @Description Nhap mat khau/PIN, moi ky tu hien thi thanh dau '*'
	*
	* @return Chuoi mat khau that nguoi dung nhap
	* @attention iDoDaiToiDa = 0: khong gioi han do dai.
	*            bChiNhanSo = true: chi nhan ky tu '0'-'9' (dung cho PIN).
	*            Ho tro phim Backspace, ket thuc bang Enter
	**********************************************************/
	static std::string nhapMatKhau(const std::string& strNhan,
		std::size_t iDoDaiToiDa = 0, bool bChiNhanSo = false);

	/**********************************************************
	* @Description Hien nhan va doc mot dong van ban (da bo khoang trang 2 dau)
	**********************************************************/
	static std::string nhapDong(const std::string& strNhan);

	/**********************************************************
	* @Description Nhap so nguyen khong am, lap lai den khi hop le
	**********************************************************/
	static long long nhapSoNguyen(const std::string& strNhan);

	/**********************************************************
	* @Description Doc so nguyen khong am tu chuoi
	*
	* @return false neu chuoi rong, co ky tu khong phai so, hoac qua dai
	**********************************************************/
	static bool chuyenSoNguyen(const std::string& strChuoi, long long& llGiaTri);

	/**********************************************************
	* @Description Hoi xac nhan Y/N, lap lai den khi nhap y/Y/n/N
	*
	* @return true neu chon Y
	**********************************************************/
	static bool xacNhan(const std::string& strCauHoi);

	/**********************************************************
	* @Description Dung man hinh den khi nguoi dung nhan Enter
	**********************************************************/
	static void tamDung();

private:
	static int docPhim();
	static void inVoiMau(const std::string& strNoiDung, ConsoleColor eMau);
};

#endif