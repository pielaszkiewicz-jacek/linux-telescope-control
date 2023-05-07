#include <parameters/tlinsParametersList.hpp>
#include <tlinsBacktrace.hpp>

//
// ----------------------------------------------------------------
// ----------------------------------------------------------------
//

bool tlinsParametersList::setParameter(const std::string &name, const std::string &value, bool)
{
	std::string val;

	if (getParameterValue(name, val)) {
		return false;
	}

	parameters[name] = value;

	return true;
}

bool tlinsParametersList::getParameterValue(const std::string &name, std::string &val)
{
	auto iter = parameters.find(std::string(name));

	if (iter == parameters.end()) {
		return false;
	}

	val = iter->second;
	return true;
}

void tlinsParametersList::copy(const tlinsParametersList &val)
{
	map<std::string, std::string>::const_iterator iter = val.parameters.begin();
	parameters.clear();
	for (; iter != val.parameters.end(); iter++) {
		parameters[iter->first] = iter->second;
	}
}

tlinsParametersList &tlinsParametersList::operator=(const tlinsParametersList &val)
{
	copy(val);
	return *this;
}

tlinsParametersList::tlinsParametersList(const tlinsParametersList &val)
{
	copy(val);
}
