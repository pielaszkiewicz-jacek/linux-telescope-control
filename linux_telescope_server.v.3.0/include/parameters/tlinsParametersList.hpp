#ifndef __tlinsParametersList_hpp__
#define __tlinsParametersList_hpp__

#include <map>
#include <string>

#include <parameters/tlinsParametersException.hpp>

/*
 * ---------------------------------------------------------------------------
 * Listy parameterow
 * ---------------------------------------------------------------------------
 */
class tlinsParametersList {
  private:
	map<std::string, std::string> parameters;

  private:
	void copy(const tlinsParametersList &val);

  public:
	bool setParameter(const std::string &name, const std::string &value, bool over = false);
	bool getParameterValue(const std::string &name, std::string &val);

	tlinsParametersList &operator=(const tlinsParametersList &val);

	tlinsParametersList() = default;
	tlinsParametersList(const tlinsParametersList &val);
	virtual ~tlinsParametersList() = default;
};

#endif
