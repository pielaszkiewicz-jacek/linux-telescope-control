#ifndef __tlinsIERSInfoManager_hpp__
#define __tlinsIERSInfoManager_hpp__

#include <tlinsIERSInfo.hpp>

#include <map>
#include <mutex>
#include <string>

class tlinsIERSInfoManager {
  private:
	std::map<std::string, tlinsIERSInfo> iersiInfo;
	std::mutex                           mtx;

  private:
	tlinsIERSInfoManager() = default;

  public:
	static tlinsIERSInfoManager &getInstance()
	{
		static tlinsIERSInfoManager instance{};
		return instance;
	}

	void clear();
	void upload_url(const std::string &url);
	void upload_xml(const std::string &file);
	void add(const tlinsIERSInfo &item);
	bool get(const int y, const int m, const int d, tlinsIERSInfo &item);

	void restoreFromFile(const std::string &file);
	void storeIntoFile(const std::string &file);

	void restoreFromFile();
	void storeIntoFile();

	tlinsIERSInfoManager(const tlinsIERSInfoManager &v) = delete;
	virtual ~tlinsIERSInfoManager()                     = default;
};

#endif
