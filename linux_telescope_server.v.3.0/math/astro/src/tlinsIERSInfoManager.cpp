#include <tlinsIERSInfoManager.hpp>

#include <tlinsBacktrace.hpp>

#include <fstream>
#include <iostream>
#include <regex>

static void __get_key(const int y, const int m, const int d, std::string &outkey)
{
	char key[512];
	sprintf(key, "%d::%d::%d", y, m, d);
	outkey = key;
}

static void __get_key(const tlinsIERSInfo &item, std::string &outkey)
{
	char key[512];
	sprintf(key, "%d::%d::%d", item.getYear(), item.getMonth(), item.getDay());
	outkey = key;
}

void tlinsIERSInfoManager::upload_url(const std::string &)
{
	// TODO
	// TODO
	// TODO
}

void tlinsIERSInfoManager::upload_xml(const std::string &)
{
	// TODO
	// TODO
	// TODO
}

void tlinsIERSInfoManager::restoreFromFile(const std::string &file)
{
	// Otwarcie pliku
	std::ifstream istrm(file);
	if (!istrm) {
		// Blad otwarci apliku
		return;
	}

	auto &inst = tlinsIERSInfoManager::getInstance();
	inst.clear();

	while (!istrm.eof()) {
		std::string line;
		if (std::getline(istrm, line)) {
			// CVzytanie lini
			try {
				std::regex ws_re{";"};
				auto       iter = std::sregex_token_iterator(line.begin(), line.end(), ws_re, -1);

				int Year = std::stoi(*iter);
				iter++;
				int Month = std::stoi(*iter);
				iter++;
				int Day = std::stoi(*iter);
				iter++;
				double DeltaUt = std::stod(*iter);
				iter++;
				double DEpsilon = std::stod(*iter);
				iter++;
				double DPsi = std::stod(*iter);
				iter++;
				double Dx = std::stod(*iter);
				iter++;
				double Dy = std::stod(*iter);
				iter++;
				double PmX = std::stod(*iter);
				iter++;
				double PmY = std::stod(*iter);
				iter++;

				tlinsIERSInfo iers{Year, Month, Day, PmX, PmY, DeltaUt, DPsi, DEpsilon, Dx, Dy};
				inst.add(iers);
			}
			catch (...) {
			}
		}
	}
}

void tlinsIERSInfoManager::storeIntoFile(const std::string &file)
{
	// Otwarcie pliku
	std::ofstream ostrm(file);
	if (!ostrm) {
		// Blad otwarci apliku
		return;
	}

	for (auto &item : iersiInfo) {
		auto &data = item.second;

		std::string line{};
		line += std::to_string(data.getYear()) + std::string{";"};
		line += std::to_string(data.getMonth()) + std::string{";"};
		line += std::to_string(data.getDay()) + std::string{";"};
		line += std::to_string(data.getDeltaUt()) + std::string{";"};
		line += std::to_string(data.getDEpsilon()) + std::string{";"};
		line += std::to_string(data.getDPsi()) + std::string{";"};
		line += std::to_string(data.getDx()) + std::string{";"};
		line += std::to_string(data.getDy()) + std::string{";"};
		line += std::to_string(data.getPmX()) + std::string{";"};
		line += std::to_string(data.getPmY());
		ostrm << line << std::endl;
	}
}

void tlinsIERSInfoManager::restoreFromFile()
{
}

void tlinsIERSInfoManager::storeIntoFile()
{
}

void tlinsIERSInfoManager::clear()
{
	std::unique_lock<std::mutex> lock(mtx);
	iersiInfo.clear();
}

void tlinsIERSInfoManager::add(const tlinsIERSInfo &item)
{
	std::string key;
	__get_key(item, key);

	std::unique_lock<std::mutex> lock(mtx);
	iersiInfo[key] = item;
}

bool tlinsIERSInfoManager::get(const int y, const int m, const int d, tlinsIERSInfo &item)
{
	std::string key;
	__get_key(y, m, d, key);

	std::unique_lock<std::mutex> lock(mtx);

	auto iter = tlinsIERSInfoManager::iersiInfo.find(key);
	if (iter == tlinsIERSInfoManager::iersiInfo.end()) {
		return false;
	}

	item = iter->second;
	return true;
}
