
/*
 * tlinsTimeInfo.cpp
 *
 *  Created on: 4 kwi 2016
 *      Author: jacek
 */

#include <cmath>
#include <ctime>
#include <iostream>
#include <sofa.h>
#include <sofam.h>
#include <sys/time.h>

#include <tlinsBacktrace.hpp>
#include <tlinsIERSInfo.hpp>
#include <tlinsIERSInfoManager.hpp>
#include <tlinsLogger.hpp>
#include <tlinsTimeInfo.hpp>

#include <stdio.h>

double tlinsTimeInfo::getUt() const
{
	return ut;
}

double tlinsTimeInfo::getDtr() const
{
	return dtr;
}

double tlinsTimeInfo::getTdb1() const
{
	return tdb1;
}

double tlinsTimeInfo::getTdb2() const
{
	return tdb2;
}

double tlinsTimeInfo::getTcb1() const
{
	return tcb1;
}

double tlinsTimeInfo::getTcb2() const
{
	return tcb2;
}

int tlinsTimeInfo::getYear() const
{
	return year;
}

int tlinsTimeInfo::getMonth() const
{
	return month;
}

int tlinsTimeInfo::getDay() const
{
	return day;
}

int tlinsTimeInfo::getHour() const
{
	return hour;
}

int tlinsTimeInfo::getMinute() const
{
	return minute;
}

double tlinsTimeInfo::getSeconds() const
{
	return seconds;
}

const std::string &tlinsTimeInfo::getScale() const
{
	return scale;
}

double tlinsTimeInfo::getTai1() const
{
	return tai1;
}

double tlinsTimeInfo::getTai2() const
{
	return tai2;
}

double tlinsTimeInfo::getTt1() const
{
	return tt1;
}

double tlinsTimeInfo::getTt2() const
{
	return tt2;
}

double tlinsTimeInfo::getUtc1() const
{
	return utc1;
}

double tlinsTimeInfo::getUtc2() const
{
	return utc2;
}

double tlinsTimeInfo::getD1() const
{
	return d1;
}

double tlinsTimeInfo::getD2() const
{
	return d2;
}

double tlinsTimeInfo::getCurrentTimeSecends() const
{
	struct timeval tv;
	gettimeofday(&tv, nullptr);
	return (double) (tv.tv_sec) + (double) (tv.tv_usec) / 1000000.0;
}

void tlinsTimeInfo::setDateTime(int y_, int mm_, int d_, int h_, int mi_, double s_, const std::string &sc)
{
	tlinsTimeInfo::year    = y_;
	tlinsTimeInfo::month   = mm_;
	tlinsTimeInfo::day     = d_;
	tlinsTimeInfo::hour    = h_;
	tlinsTimeInfo::minute  = mi_;
	tlinsTimeInfo::seconds = s_;
	tlinsTimeInfo::scale   = sc;

	tlinsTimeInfo::calculate();
}

void tlinsTimeInfo::getDateTime(int &y_, int &mm_, int &d_, int &h_, int &mi_, double &s_, std::string &sc) const
{
	y_  = year;
	mm_ = month;
	d_  = day;
	h_  = hour;
	mi_ = minute;
	s_  = seconds;
	sc  = scale;
}

void tlinsTimeInfo::calculate(void)
{
	// Lock time object
	std::lock_guard<std::mutex> lock(tlinsTimeInfo::timeMutex);

	auto rc = ::iauDtf2d(scale.c_str(), year, month, day, hour, minute, seconds, &utc1, &utc2);
	if (rc) {
		__THROW__(tlinsAstroException(
		    std::string("Error calculate UTC1 and UTC2 -->> ") + std::to_string(rc) + std::string{" ++ "} +
		        std::to_string(year) + std::string{"-"} + std::to_string(month) + std::string{"-"} +
		        std::to_string(day) + std::string{" "} + std::to_string(hour) + std::string{":"} +
		        std::to_string(minute) + std::string{":"} + std::to_string(seconds) + std::string{":"} + scale,
		    tlinsAstroException::ASTRO_ERROR_DATE_UTC1_UTC2));
	}

	// TT date
	if (::iauUtctai(utc1, utc2, &tai1, &tai2)) {
		__THROW__(tlinsAstroException(std::string("Error calculate TT"), tlinsAstroException::ASTRO_ERROR_DATE_TT));
	}

	if (::iauTaitt(tai1, tai2, &tt1, &tt2)) {
		__THROW__(tlinsAstroException(std::string("Error calculate TT"), tlinsAstroException::ASTRO_ERROR_DATE_TT));
	}

	tlinsIERSInfo iers;
	auto	     &ins = tlinsIERSInfoManager::getInstance();
	ins.get(getYear(), getMonth(), getMinute(), iers);

	if (::iauUtcut1(utc1, utc2, iers.getDeltaUt(), &ut11, &ut12)) {
		__THROW__(tlinsAstroException(std::string("Error calculate UT"), tlinsAstroException::ASTRO_ERROR_DATE_UT));
	}

	if (::iauTttcg(tt1, tt2, &tcg1, &tcg2)) {
		__THROW__(tlinsAstroException(std::string("Error calculate TCG"), tlinsAstroException::ASTRO_ERROR_DATE_TCG));
	}

	// UT
	ut = ::fmod(::fmod(ut11, 1.0) + ::fmod(ut12, 1.0), 1.0) + 0.5;

	// DTR
	auto &placeInstance = tlinsObservationPlace::getInstance();

	tlinsTimeInfo::dtr = ::iauDtdb(tt1, tt2, ut, placeInstance.getLongitudeRad(), placeInstance.getU() / 1e3,
	                               placeInstance.getV() / 1e3);

	// TT -> TDB -> TCB.
	if (::iauTttdb(tt1, tt2, dtr, &tdb1, &tdb2)) {
		__THROW__(tlinsAstroException(std::string("Error calculate TCB"), tlinsAstroException::ASTRO_ERROR_DATE_TCB));
	}

	if (::iauTdbtcb(tdb1, tdb2, &tcb1, &tcb2)) {
		__THROW__(tlinsAstroException(std::string("Error calculate TCB"), tlinsAstroException::ASTRO_ERROR_DATE_TCB));
	}

	// Data Julianska
	if (iauCal2jd(year, month, day, &d1, &d2)) {
		__THROW__(
		    tlinsAstroException(std::string("Error calculate TCB"), tlinsAstroException::ASTRO_ERROR_DATE_JULIAN));
	}

	double d;
	if (iauTf2d('+', hour, minute, seconds, &d)) {
		__THROW__(
		    tlinsAstroException(std::string("Error calculate TCB"), tlinsAstroException::ASTRO_ERROR_DATE_JULIAN));
	}
	d2 += d;
}

void tlinsTimeInfo::update(struct timeval &tv)
{
	// Konwersja do UTC
	std::tm *ttm = std::gmtime(&tv.tv_sec);
	if (ttm == nullptr) {
		__THROW__(tlinsAstroException(std::string("Error conver timt into UTC"),
		                              tlinsAstroException::ASTRO_ERROR_DATE_GET_TIME));
	}

	// Czas UTC
	scale   = scale_utc;
	year    = ttm->tm_year + 1900;
	month   = ttm->tm_mon + 1;
	day     = ttm->tm_mday;
	hour    = ttm->tm_hour;
	minute  = ttm->tm_min;
	seconds = static_cast<double>(ttm->tm_sec) + static_cast<double>(tv.tv_usec) / 1000000.0;

	calculate();
}

void tlinsTimeInfo::update()
{
	// Czas systemowy
	struct timeval tv;
	if (::gettimeofday(&tv, nullptr) < 0) {
		__THROW__(tlinsAstroException(std::string("Error get time"), tlinsAstroException::ASTRO_ERROR_DATE_GET_TIME));
	}
	update(tv);
}

void tlinsTimeInfo::update2(const double delta)
{
	// Czas systemowy
	struct timeval tv;
	if (::gettimeofday(&tv, nullptr) < 0) {
		__THROW__(tlinsAstroException(std::string("Error get time"), tlinsAstroException::ASTRO_ERROR_DATE_GET_TIME));
	}

	double tS = static_cast<double>(tv.tv_sec) + static_cast<double>(tv.tv_usec) / 1000000.0 + delta;

	double SS   = 0.0;
	double miSS = ::modf(tS, &SS);

	// Konwersja do UTC
	std::tm *ttm = std::gmtime(&tv.tv_sec);
	if (ttm == nullptr) {
		__THROW__(tlinsAstroException(std::string("Error conver timt into UTC"),
		                              tlinsAstroException::ASTRO_ERROR_DATE_GET_TIME));
	}

	// Czas UTC
	scale   = scale_utc;
	year    = ttm->tm_year + 1900;
	month   = ttm->tm_mon + 1;
	day     = ttm->tm_mday;
	hour    = ttm->tm_hour;
	minute  = ttm->tm_min;
	seconds = static_cast<double>(ttm->tm_sec) + static_cast<double>(tv.tv_usec) / 1000000.0 + delta;

	calculate();
}

void tlinsTimeInfo ::update(const double timeDate)
{
	double sec{0.0};
	double secPart = ::modf(timeDate, &sec);

	// Konwersja do UTC
	auto     secVal = static_cast<time_t>(sec);
	std::tm *ttm    = std ::gmtime(&secVal);
	if (ttm == nullptr) {
		__THROW__(tlinsAstroException(std::string("Error conver timt into UTC"),
		                              tlinsAstroException::ASTRO_ERROR_DATE_GET_TIME));
	}

	scale   = scale_utc;
	year    = ttm->tm_year + 1900;
	month   = ttm->tm_mon + 1;
	day     = ttm->tm_mday;
	hour    = ttm->tm_hour;
	minute  = ttm->tm_min;
	seconds = secPart;

	calculate();
}
