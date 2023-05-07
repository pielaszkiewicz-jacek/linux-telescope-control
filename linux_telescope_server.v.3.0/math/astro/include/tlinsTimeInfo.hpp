/*
 * tlinsTimeInfo.hpp
 *
 *  Created on: 4 kwi 2016
 *      Author: jacek
 */

#ifndef __tlinsTimeInfo_hpp__
#define __tlinsTimeInfo_hpp__

#include <tlinsAstroException.hpp>
#include <tlinsBacktrace.hpp>
#include <tlinsIERSInfo.hpp>
#include <tlinsObservationPlace.hpp>

#include <memory>
#include <mutex>

class tlinsTimeInfo {
  private:
	std::mutex  timeMutex;
	std::string scale;
	int         year{0};
	int         month{0};
	int         day{0};
	int         hour{0};
	int         minute{0};
	double      seconds{0.0};
	double      ut{0.0};
	double      ut11{0.0};
	double      ut12{0.0};
	double      tcg1{0.0};
	double      tcg2{0.0};
	double      d1{0.0};
	double      d2{0.0};
	double      utc1{0.0};
	double      utc2{0.0};
	double      tt1{0.0};
	double      tt2{0.0};
	double      tai1{0.0};
	double      tai2{0.0};
	double      dtr{0.0};
	double      tdb1{0.0};
	double      tdb2{0.0};
	double      tcb1{0.0};
	double      tcb2{0.0};
	std::string scale_utc{"UTC"};
	std::string scale_tai{"TAI"};

  public:
	int                getYear() const;
	int                getMonth() const;
	int                getDay() const;
	int                getHour() const;
	int                getMinute() const;
	double             getSeconds() const;
	const std::string &getScale() const;

	double getTai1() const;
	double getTai2() const;
	double getTt1() const;
	double getTt2() const;
	double getUtc1() const;
	double getUtc2() const;

	double getUt() const;
	double getDtr() const;

	double getTdb1() const;
	double getTdb2() const;
	double getTcb1() const;
	double getTcb2() const;

	double getD1() const;
	double getD2() const;

	double getCurrentTimeSecends() const;

	void setDateTime(const int y_, const int mm_, const int d_, const int h_, const int mi_, const double s_,
	                 const std::string &sc);

	void getDateTime(int &y_, int &mm_, int &d_, int &h_, int &mi_, double &s_, std::string &sc) const;

	void calculate();
	void update();
	void update2(const double delta);
	void update(const double timeDate);
	void update(struct timeval &tv);

	static tlinsTimeInfo &getInstance()
	{
		static tlinsTimeInfo instance;
		return instance;
	};

	static std ::unique_ptr<tlinsTimeInfo> getInstanceObj()
	{
		auto instance = std::make_unique<tlinsTimeInfo>();
		instance->update();
		return instance;
	}

	static std::unique_ptr<tlinsTimeInfo> getInstance(const int y_, const int mm_, const int d_, const int h_,
	                                                  const int mi_, const double s_, const std::string &sc)
	{
		auto ptr = std::make_unique<tlinsTimeInfo>();
		ptr->setDateTime(y_, mm_, d_, h_, mi_, s_, sc);
		return ptr;
	};

	static std::unique_ptr<tlinsTimeInfo> getInstanceNoSet()
	{
		return std::make_unique<tlinsTimeInfo>();
	};

	tlinsTimeInfo()          = default;
	virtual ~tlinsTimeInfo() = default;
};

#endif
