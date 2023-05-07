#include "tlinscommunicationthread.h"
#include <QDebug>
#include <tlinsBacktrace.hpp>
#include <tlinsLogger.hpp>

namespace TlinsAstroBase {

//
// ------------------------------
//
long tlinsCommunicationThread::getId()
{
    std::unique_lock<std::mutex> lock(counterMtx);
    id++;
    return id;
}

void tlinsCommunicationThread::confirm(long id)
{
    std::unique_lock<std::mutex> lock(mtx);
    waitingRequests.erase(id);
}

void tlinsCommunicationThread::push(std::unique_ptr<tlinsCommunicationThreadRequest>& request, bool priority)
{
    std::unique_lock<std::mutex> lock(mtx);
    //	qDebug() << "Request name = " << QString:: fromStdString( request -> name() ) << "; Queue size = " << QString:: fromStdString( std:: to_string( requests.size() + 1 ) );

    if (priority)
        requests.push_front(std::move(request));
    else
        requests.push_back(std::move(request));

    //	qDebug() << "Request name = " << "; Queue size = " << QString:: fromStdString( std:: to_string( requests.size() ) );

    cv.notify_all();
}

std::unique_ptr<tlinsCommunicationThreadRequest> tlinsCommunicationThread::pop()
{
    auto result = std::move(requests.front());
    requests.pop_front();
    return result;
}

// Zatrzymanie watku
void tlinsCommunicationThread::stop()
{
    // Zakonczenie watku
    end = true;

    // Ewnetualne odblokowanie zmiennej warunkowej
    cv.notify_all();
}

// Funkcja implementuje petle glowna watku
void tlinsCommunicationThread::run()
{
    while (!end) {
        // Oczekiwanie na dane
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] { return !this->requests.empty(); });
        }

        std::unique_ptr<tlinsCommunicationThreadRequest> request;
        {
            std::unique_lock<std::mutex> lock(mtx);
            if (requests.empty()) {
                continue;
            }

            // Pobranie danych z kolejki
            request = pop();
        }

        if (request->isAsynchronuus()) {
            auto id_ = getId();
            request->setRequestId(id_);
            waitingRequests[id_] = std::move(request);

            // Uruchomienie operacji

            //			qDebug() << "[" << requests.size() << "]; Before : " << QString:: fromStdString( waitingRequests[id_] -> name() );
            (*waitingRequests[id_])();
            //			qDebug() << "[" << requests.size() << "]; After  : " << QString:: fromStdString( waitingRequests[id_] -> name() );

        } else {
            // Uruchomienie operacji
            //			qDebug() << "[" << requests.size() << "]; Before : " << QString:: fromStdString( request -> name() );
            (*request)();
            //			qDebug() << "[" << requests.size() << "]; After  : " << QString:: fromStdString( request -> name() );
        }
    }
}

tlinsCommunicationThread::tlinsCommunicationThread()
    : thread { &tlinsCommunicationThread::run, this }
    , id { 0 }
{
}

tlinsCommunicationThread::~tlinsCommunicationThread()
{
    stop();
    if (thread.joinable())
        thread.join();
}

}
