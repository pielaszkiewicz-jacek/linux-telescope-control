#ifndef TLINSCOMMUNICATIONTHREAD_H
#define TLINSCOMMUNICATIONTHREAD_H

#include "tlinsconnection.h"
#include <condition_variable>
#include <list>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

//using tlinsRequest = std:: function<void(tlinsConnection &)>;

namespace TlinsAstroBase {

class tlinsCommunicationThreadRequest;

class tlinsCommunicationThread {
private:
    // Zmienna warunkowa kontrolujaca czytanie danych z kolejki
    std::condition_variable cv;
    std::mutex mtx;

    // kontroluje petle glowa watku
    std::atomic<bool> end;

    // Kolejka rzadan wejsciowych
    std::list<std::unique_ptr<tlinsCommunicationThreadRequest>> requests;

    // Mapa rzadan oczekujacych na potwierdzenie - tryb asynchroniczny
    std::map<long, std::unique_ptr<tlinsCommunicationThreadRequest>> waitingRequests;

    std::thread thread;
    std::mutex counterMtx;
    long id;

private:
    long getId();

public:
    // Obsluga kolejki rzadan
    void push(std::unique_ptr<tlinsCommunicationThreadRequest>& requests, bool priority = false);
    std::unique_ptr<tlinsCommunicationThreadRequest> pop();

    // Zatrzymanie watku
    void stop();

    // Funkcja implementuje petle glowna watku
    void run();

    void confirm(long id);

    static tlinsCommunicationThread& getInstance()
    {
        static tlinsCommunicationThread inst;
        return inst;
    }

private:
    tlinsCommunicationThread();

public:
    virtual ~tlinsCommunicationThread();
};

class tlinsCommunicationThreadRequest {
private:
    long id;

public:
    void confirm()
    {
        tlinsCommunicationThread::getInstance().confirm(id);
    }

    void setRequestId(long v)
    {
        id = v;
    }

    virtual void operator()() noexcept = 0;
    virtual bool isAsynchronuus() = 0;
    virtual std::string name() = 0;

    virtual ~tlinsCommunicationThreadRequest()
    {
    }
};

}

#endif // TLINSCOMMUNICATIONTHREAD_H
