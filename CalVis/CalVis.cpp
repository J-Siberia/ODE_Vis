// CalVis.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <windows.h>
#include <fstream>
#include <iomanip> 
#include <cmath>

int main()
{
	// 時間計測用
	LARGE_INTEGER frequency;
	LARGE_INTEGER start;
	LARGE_INTEGER end;

	std::cout << std::fixed;
	std::cout << std::setprecision(18);

	// y = -2.0 / (x^2 + 400.0)の解を求める
	// dy/dx = xy^2, y(0) = -0.005であるときの y(40) の解を求める
	// y(40) の解析解は y(40) = -0.001

	long double a = 0.0;
	long double b = 40.0;
	long double y0 = -0.005;
	long double gt = -0.001;
	int n = 8000;
	long double h = (b - a) / n;

	std::cout << "刻み幅:" << h << std::endl;
	std::cout << "x=40における真値:" << gt << std::endl;
	
	//オイラー法
	long double y = y0;
	long double x = a;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);
	for (int i = 0; i <= n - 1;i++) {
		long double fi = x * y * y;
		y = y + h * fi;
		x = x + h;
	}
	QueryPerformanceCounter(&end);
	long double yEuler = y;
	long double errorEuler = abs(yEuler - gt);
	long double secondsEuler = (end.QuadPart - start.QuadPart) / (long double)frequency.QuadPart;
	std::cout << "オイラー法の計算時間:" << secondsEuler << std::endl;
	std::cout << "オイラー法で計算した解:" << yEuler << std::endl;
	std::cout << "オイラー法の誤差:" << errorEuler << std::endl;

	//ホイン法
	y = y0;
	x = a;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);
	for (int i = 0; i <= n - 1; i++) {
		long double fi = x * y * y;
		long double x1 = x + h;
		long double y1 = y + h * fi;
		long double fi1 = x1 * y1 * y1;

		y = y + (h / 2.0) * (fi + fi1);
		x = x + h;
	}
	QueryPerformanceCounter(&end);
	long double yHeun = y;
	long double errorHeun = abs(yHeun - gt);
	long double secondsHeun = (end.QuadPart - start.QuadPart) / (long double)frequency.QuadPart;
	std::cout << "ホイン法の計算時間:" << secondsHeun << std::endl;
	std::cout << "ホイン法で計算した解:" << yHeun << std::endl;
	std::cout << "ホイン法の誤差:" << errorHeun << std::endl;

	//3段3次のルンゲ・クッタ法
	y = y0;
	x = a;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);
	for (int i = 0; i <= n - 1; i++) {
		long double fi = x * y * y;
		long double k1 = fi;
		long double k2 = (x + h / 2.0) * (y + h / 2.0 * k1) * (y + h / 2.0 * k1);
		long double k3 = (x + h) * (y - h * k1 + 2.0 * h * k2) * (y - h * k1 + 2.0 * h * k2);

		y = y + (h / 6.0) * (k1 + 4.0 * k2 + k3);
		x = x + h;
	}
	QueryPerformanceCounter(&end);
	long double yRK3 = y;
	long double errorRK3 = abs(yRK3 - gt);
	long double secondsRK3 = (end.QuadPart - start.QuadPart) / (long double)frequency.QuadPart;
	std::cout << "3段3次のルンゲ・クッタ法の計算時間:" << secondsRK3 << std::endl;
	std::cout << "3段3次のルンゲ・クッタ法で計算した解:" << yRK3 << std::endl;
	std::cout << "3段3次のルンゲ・クッタ法の誤差:" << errorRK3 << std::endl;

	//4段4次のルンゲ・クッタ法
	y = y0;
	x = a;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);
	for (int i = 0; i <= n - 1; i++) {
		long double fi = x * y * y;
		long double k1 = fi;
		long double k2 = (x + h / 2.0) * (y + h / 2.0 * k1) * (y + h / 2.0 * k1);
		long double k3 = (x + h / 2.0) * (y + h / 2.0 * k2) * (y + h / 2.0 * k2);
		long double k4 = (x + h) * (y + h * k3) * (y + h * k3);

		y = y + (h / 6.0) * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
		x = x + h;
	}
	QueryPerformanceCounter(&end);
	long double yRK4 = y;
	long double errorRK4 = abs(yRK4 - gt);
	long double secondsRK4 = (end.QuadPart - start.QuadPart) / (long double)frequency.QuadPart;
	std::cout << "4段4次のルンゲ・クッタ法の計算時間:" << secondsRK4 << std::endl;
	std::cout << "4段4次のルンゲ・クッタ法で計算した解:" << yRK4 << std::endl;
	std::cout << "4段4次のルンゲ・クッタ法の誤差:" << errorRK4 << std::endl;

	//アダムス・バッシュフォース法（3段）
	y = y0;
	x = a;
	long double ab_fi, ab_fi1, ab_fi2;
	ab_fi1 = 0.0;
	ab_fi2 = 0.0;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);
	for (int i = 0; i <= n - 1; i++) {
		ab_fi = x * y * y;

		if (i < 2) {	//3点求まるまではオイラー法
			y = y + h * ab_fi;
		}
		else {
			y = y + (h / 12.0) * (23.0 * ab_fi - 16.0 * ab_fi1 + 5.0 * ab_fi2);
		}
		ab_fi2 = ab_fi1;
		ab_fi1 = ab_fi;

		x = x + h;
	}
	QueryPerformanceCounter(&end);
	long double yAdBa3 = y;
	long double errorAdBa3 = abs(yAdBa3 - gt);
	long double secondsAdBa3 = (end.QuadPart - start.QuadPart) / (long double)frequency.QuadPart;
	std::cout << "アダムス・バッシュフォース法（3段）法の計算時間:" << secondsAdBa3 << std::endl;
	std::cout << "アダムス・バッシュフォース法（3段）法で計算した解:" << yAdBa3 << std::endl;
	std::cout << "アダムス・バッシュフォース法（3段）法の誤差:" << errorAdBa3 << std::endl;

	//アダムス・バッシュフォース法（4段）
	y = y0;
	x = a;
	long double ab_fi3;
	ab_fi1 = 0.0;
	ab_fi2 = 0.0;
	ab_fi3 = 0.0;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);
	for (int i = 0; i <= n - 1; i++) {
		ab_fi = x * y * y;

		if (i < 3) {	//4点求まるまではオイラー法
			y = y + h * ab_fi;
		}
		else {
			y = y + (h / 24.0) * (55.0 * ab_fi - 59.0 * ab_fi1 + 37.0 * ab_fi2 - 9.0 * ab_fi3);
		}
		ab_fi3 = ab_fi2;
		ab_fi2 = ab_fi1;
		ab_fi1 = ab_fi;

		x = x + h;
	}
	QueryPerformanceCounter(&end);
	long double yAdBa4 = y;
	long double errorAdBa4 = abs(yAdBa4 - gt);
	long double secondsAdBa4 = (end.QuadPart - start.QuadPart) / (long double)frequency.QuadPart;
	std::cout << "アダムス・バッシュフォース法（4段）法の計算時間:" << secondsAdBa4 << std::endl;
	std::cout << "アダムス・バッシュフォース法（4段）法で計算した解:" << yAdBa4 << std::endl;
	std::cout << "アダムス・バッシュフォース法（4段）法の誤差:" << errorAdBa4 << std::endl;

	//予測子修正子法
	y = y0;
	x = a;
	long double pre_fi, pre_fi_m2, pre_fi_m1, pre_fi_p1;
	pre_fi_m2 = 0.0;
	pre_fi_m1 = 0.0;
	pre_fi = 0.0;
	pre_fi_p1 = 0.0;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);
	for (int i = 0; i <= n - 1; i++) {
		pre_fi = x * y * y;

		if (i < 2) {	//3点求まるまではオイラー法+ホイン法
			pre_fi_p1 = (x + h) * (y + h * pre_fi) * (y + h * pre_fi);
			y = y + (h / 2.0) * (pre_fi + pre_fi_p1);
		}
		else {
			//アダムス・バッシュフォース法（3段）法の計算
			long double y1 = y + (h / 12.0) * (23.0 * pre_fi - 16.0 * pre_fi_m1 + 5.0 * pre_fi_m2);
			pre_fi_p1 = (x + h) * y1 * y1;

			//アダムス・ムルトン法の計算
			y = y + (h / 24.0) * (9.0 * pre_fi_p1 + 19.0 * pre_fi - 5.0 * pre_fi_m1 + pre_fi_m2);
		}
		pre_fi_m2 = pre_fi;
		pre_fi_m1 = pre_fi;

		x = x + h;
	}
	QueryPerformanceCounter(&end);
	long double yPreCor4 = y;
	long double errorPreCor4 = abs(yPreCor4 - gt);
	long double secondsPreCor4 = (end.QuadPart - start.QuadPart) / (long double)frequency.QuadPart;
	std::cout << "予測子修正子法の計算時間:" << secondsPreCor4 << std::endl;
	std::cout << "予測子修正子法で計算した解:" << yPreCor4 << std::endl;
	std::cout << "予測子修正子法の誤差:" << errorPreCor4 << std::endl;

	//計算結果をファイルに出力
	std::ofstream ofs("result.csv");
	ofs << std::fixed;
	ofs << std::setprecision(18);
	ofs << "手法名,計算結果,誤差,計算時間" << std::endl;
	ofs << "オイラー法," << yEuler << "," << errorEuler << "," << secondsEuler << std::endl;
	ofs << "ホイン法," << yHeun << "," << errorHeun << "," << secondsHeun << std::endl;
	ofs << "3段3次のルンゲ・クッタ法," << yRK3 << "," << errorRK3 << "," << secondsRK3 << std::endl;
	ofs << "4段4次のルンゲ・クッタ法," << yRK4 << "," << errorRK4 << "," << secondsRK4 << std::endl;
	ofs << "アダムス・バッシュフォース法（3段）," << yAdBa3 << "," << errorAdBa3 << "," << secondsAdBa3 << std::endl;
	ofs << "アダムス・バッシュフォース法（4段）," << yAdBa4 << "," << errorAdBa4 << "," << secondsAdBa4 << std::endl;
	ofs << "予測子修正子法," << yPreCor4 << "," << errorPreCor4 << "," << secondsPreCor4 << std::endl;
}
