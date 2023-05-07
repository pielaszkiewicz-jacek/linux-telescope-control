#include <tlinsLogger.hpp>
#include <tlinsSystemServiceClient.hpp>

tlinsSystemServiceClient::EventJoystick::~EventJoystick()
{
}

tlinsSystemServiceClient::EventJoystick::EventJoystick()
{
}

tlinsSystemServiceClient::EventJoystick::EventJoystick(const EventJoystick &v)
{
	value  = v.value;
	type   = v.type;
	number = v.number;
}

tlinsSystemServiceClient::EventJoystick &tlinsSystemServiceClient::EventJoystick::operator=(const EventJoystick &v)
{
	value  = v.value;
	type   = v.type;
	number = v.number;
	return *this;
}

//
// ------------------------------------
//

tlinsSystemServiceClient::EventKyeboard::~EventKyeboard()
{
}

tlinsSystemServiceClient::EventKyeboard::EventKyeboard()
{
}

tlinsSystemServiceClient::EventKyeboard::EventKyeboard(const EventKyeboard &v)
{
	keyId     = v.keyId;
	keyStatus = v.keyStatus;
}

tlinsSystemServiceClient::EventKyeboard &tlinsSystemServiceClient::EventKyeboard::operator=(const EventKyeboard &v)
{
	keyId     = v.keyId;
	keyStatus = v.keyStatus;
	return *this;
}

tlinsSystemServiceClient::Event::~Event()
{
}

// ------------------------------------

void tlinsSystemServiceClient::stop()
{
	end = true;
}

void tlinsSystemServiceClient::readKeyboardEvent(const tlins::tlinsEventInfo &      event,
                                                 std::function<void(const Event &)> fun)
{
	if (!event.has_keyboard())
		return;

	Event ev;
	ev.eventType = tlinsSystemServiceClient::EventType::KEYBOARD;
	ev.keyId     = event.keyboard().keyid().value();
	ev.keyStatus = event.keyboard().keystatus().value();

	try {
		fun(ev);
	}
	catch (...) {
	}
}

void tlinsSystemServiceClient::readJoystickEvent(const tlins::tlinsEventInfo &      event,
                                                 std::function<void(const Event &)> fun)
{
	if (!event.has_joystick())
		return;

	Event ev;
	ev.eventType = tlinsSystemServiceClient::EventType::JOYSTICK;
	ev.value     = event.joystick().value().value();
	ev.type      = event.joystick().type().value();
	ev.number    = event.joystick().number().value();

	try {
		fun(ev);
	}
	catch (...) {
	}
}

void tlinsSystemServiceClient::threadFun()
{
	reader = std::move(connectionStub->readEvents(&context, enentsTypeList));

	while (!end.load()) {
		tlins::tlinsEventInfo event;

		if (!reader->Read(&event)) {
			serverEnded = true;
			break;
		}

		switch (event.eventtype()) {
		case tlins::tlinsEventType::_KEYBOARD:
			// fun(event);
			readKeyboardEvent(event, inFunction);
			break;

		case tlins::tlinsEventType::_JOYSTICK:
			// fun(event);
			readJoystickEvent(event, inFunction);
			break;
		}
	}
}

// Konstruktor klasy
tlinsSystemServiceClient::tlinsSystemServiceClient(std::shared_ptr<grpc::Channel> &                             channel,
                                                   const std::vector<tlinsSystemServiceClient::EventType> &     events,
                                                   std::function<void(const tlinsSystemServiceClient::Event &)> fun)
    : end{false}, serverEnded{false}, inFunction{fun}
{
	connectionStub = tlins::tlinsRpcSystemServiceRecipient::NewStub(channel);

	for (auto item : events) {
		switch (item) {
		case tlinsSystemServiceClient::EventType::KEYBOARD:
			enentsTypeList.add_types(tlins::tlinsEventType::_KEYBOARD);
			break;

		case tlinsSystemServiceClient::EventType::JOYSTICK:
			enentsTypeList.add_types(tlins::tlinsEventType::_JOYSTICK);
			break;
		}
	}

	thread = std::move(std::thread{[this]() { this->threadFun(); }});
}

// Destruktor klasy
tlinsSystemServiceClient::~tlinsSystemServiceClient()
{
	end.store(true);
	context.TryCancel();
	if (thread.joinable())
		thread.join();
}
