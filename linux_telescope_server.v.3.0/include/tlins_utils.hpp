#ifndef __tlins_utils_hpp__
#define __tlins_utils_hpp__

#include <tlinsBacktrace.hpp>

#define __GET__(type, name)                             \
	const type &get_##name() const                      \
	{                                                   \
		return name;                                    \
	}

#define __get__(obj, name) (obj).get_##name()

#define __SET__(type, name)                             \
	void set_##name(const type &v)                      \
	{                                                   \
		name = v;                                       \
	}

#define __ITEM__(type, name)                            \
  private:                                              \
	type name;                                          \
                                                        \
  public:                                               \
	__GET__(type, name);                                \
	__SET__(type, name)

#define __DEF_CONSTRUCTOR__(name)                       \
	name()                                              \
	{                                                   \
	}

#define __DEF_DESTRUCTOR__(name)                        \
	virtual ~name()                                     \
	{                                                   \
	}

#endif
