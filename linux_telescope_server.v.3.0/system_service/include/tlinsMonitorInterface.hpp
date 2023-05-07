#ifndef __tlinsMonitorInterface_hpp__
#define __tlinsMonitorInterface_hpp__

#include <memory>
#include <thread>
#include <vector>

class tlinsMonitorInterface {
  public:
	virtual ~tlinsMonitorInterface()
	{
	}
};

template <typename T> class tlinsMonitorItem : public tlinsMonitorInterface {
  private:
	T           item;
	std::thread th;

  public:
	template <typename... _Args> tlinsMonitorItem(_Args &&... _args) : item{_args...}
	{
		th = std::move(std::thread{[this]() { this->item.run(); }});
	}

	virtual ~tlinsMonitorItem(){};
};

class tlinsMonitorManager {
  private:
	std::vector<std::unique_ptr<tlinsMonitorInterface>> instances;

  private:
	tlinsMonitorManager()
	{
	}

	static tlinsMonitorManager &getInstance()
	{
		static tlinsMonitorManager instance;
		return instance;
	}

  public:
	template <typename T, typename... _Args> static void add(_Args &&... _args)
	{
		std::unique_ptr<tlinsMonitorInterface> obj{new tlinsMonitorItem<T>{_args...}};

		auto &ins = tlinsMonitorManager::getInstance();
		ins.instances.push_back(std::move(obj));
	}

	virtual ~tlinsMonitorManager()
	{
	}
};

#endif