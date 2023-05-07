#include <tlinsAstroEngineInterface.hpp>

void tlinsAstroEngineInterface::getCalibrationState(tlinsCalibrarionStateInfo &responseOut)
{
	tlins::Void                            request;
	tlins::tlinsEngineCalibrarionStateInfo response;

	// Wyslanie rzadania
	grpc::ClientContext context;
	auto                result = connectionStub->getCalibrationState(&context, request, &response);

	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error get astro engine state."),
		                                  tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status().status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(response.status().errordescription(),
		                                  tlinsInterfaceException::ERROR_ASTRO_READ_DEVICE_STATUS));
	}

	switch (response.state().state().state()) {
	case tlins::tlinsEngineStateValue_::_STATE_CALIBRATION:
		responseOut.set_engineState(tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_CALIBRATION);
		break;

	case tlins::tlinsEngineStateValue_::_STATE_REGULAR:
		responseOut.set_engineState(tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_REGULAR);
		break;
	}

	responseOut.set_isTrackingActive(response.istrackingenabled().value());

	responseOut.set_iterationCount(response.state().iterationcount().value());
}

void tlinsAstroEngineInterface::getState(tlinsEngineStateInfo &responseOut, const bool suspend)
{
	tlins::tlinsBoolValue       request;
	tlins::tlinsEngineStateInfo response;

	// Wyslanie rzadania
	grpc::ClientContext context;

	// Domyslnie kontroler jest zatrzymywany
	request.set_value(suspend);
	auto result = connectionStub->getState(&context, request, &response);

	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error get astro engine state."),
		                                  tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status().status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(response.status().errordescription(),
		                                  tlinsInterfaceException::ERROR_ASTRO_READ_DEVICE_STATUS));
	}

	auto &instate = response.state();

	// 1. Macierz transformacji
	if (instate.has_attitude()) {

		auto                                                     &attitude = instate.attitude();
		tlinsAstroEngineInterface::tlinsEngineStateInfo::d23array att;
		att[0][0] = attitude.a00().value();
		att[0][1] = attitude.a01().value();
		att[0][2] = attitude.a02().value();
		att[1][0] = attitude.a10().value();
		att[1][1] = attitude.a11().value();
		att[1][2] = attitude.a12().value();
		att[2][0] = attitude.a20().value();
		att[2][1] = attitude.a21().value();
		att[2][2] = attitude.a22().value();

		responseOut.set_attitude(att);
	}

	// Aktualna pozycja
	if (instate.has_deviceposition()) {
		tlinsDevicePosition pos;

		auto &deviceposition = response.state().deviceposition();
		pos.set_x(deviceposition.x().value());
		pos.set_y(deviceposition.y().value());
		pos.set_xEncoder(deviceposition.xencoder().value());
		pos.set_yEncoder(deviceposition.yencoder().value());
		responseOut.set_devicePosition(pos);
	}

	// Biezacy cel
	if (instate.has_currenttarget()) {
		auto &currenttarget = instate.currenttarget().target();

		tlinsTarget      target;
		tlinsAstroObject astroObject;

		tlinsCoordinate dc;
		dc.set_sign(currenttarget.object().declination().sign().value());
		dc.set_degris(currenttarget.object().declination().degris().value());
		dc.set_minutes(currenttarget.object().declination().minutes().value());
		dc.set_seconds(currenttarget.object().declination().seconds().value());

		tlinsCoordinate ra;
		ra.set_sign(currenttarget.object().hourangle().sign().value());
		ra.set_degris(currenttarget.object().hourangle().degris().value());
		ra.set_minutes(currenttarget.object().hourangle().minutes().value());
		ra.set_seconds(currenttarget.object().hourangle().seconds().value());

		astroObject.set_declination(dc);
		astroObject.set_hourAngle(ra);

		astroObject.set_properMotionRA(currenttarget.object().propermotionra().value());
		astroObject.set_properMotionDC(currenttarget.object().propermotiondc().value());
		astroObject.set_parallax(currenttarget.object().parallax().value());
		astroObject.set_radialVelocity(currenttarget.object().radialvelocity().value());
		astroObject.set_catalogType(currenttarget.object().catalogtype().value());

		target.set_object(astroObject);
		target.set_delta(currenttarget.delta().value());
		target.set_speed(currenttarget.speed().value());
		target.set_aceleration(response.state().currenttarget().target().aceleration().value());

		responseOut.set_currentTarget(target);
	}

	// tryb silnika
	if (instate.has_mode()) {
		switch (instate.mode().mode()) {
		case tlins::tlinsEngineMode_::_MODE_NONE:
			responseOut.set_mode(tlinsEngineMode::MODE_NONE);
			break;

		case tlins::tlinsEngineMode_::_MODE_STANDARD:
			responseOut.set_mode(tlinsEngineMode::MODE_STANDARD);
			break;

		case tlins::tlinsEngineMode_::_MODE_EXTERNAL_SUPPORT:
			responseOut.set_mode(tlinsEngineMode::MODE_EXTERNAL_SUPPORT);
			break;
		}
	}

	// tryb silnika
	if (instate.has_state()) {
		switch (instate.state().state()) {
		case tlins::tlinsEngineStateValue_::_STATE_CALIBRATION:
			responseOut.set_state(tlinsEngineStateValue::STATE_CALIBRATION);
			break;

		case tlins::tlinsEngineStateValue_::_STATE_REGULAR:
			responseOut.set_state(tlinsEngineStateValue::STATE_REGULAR);
			break;
		}
	}

	// tryb silnika
	if (instate.has_multiplefinal()) {
		switch (instate.multiplefinal().multiple()) {
		case tlins::tlinsMultipleModeFinall_::_SWITCH_TO_STANDARD:
			responseOut.set_multipleFinal(tlinsMultipleModeFinall::SWITCH_TO_STANDARD);
			break;

		case tlins::tlinsMultipleModeFinall_::_SWITCH_TO_EXTERNAL:
			responseOut.set_multipleFinal(tlinsMultipleModeFinall::SWITCH_TO_EXTERNAL);
			break;
		}
	}

	responseOut.set_xReverse(instate.xreverse().value());
	responseOut.set_yReverse(instate.yreverse().value());
}

void tlinsAstroEngineInterface::restoreState(const tlinsEngineStateInfo &inRequest)
{
	tlins::tlinsEngineState request;
	tlins::tlinsRpcStatus   response;

	auto attitude = request.mutable_attitude();

	//
	// Macierz transformacji
	//
	auto att = inRequest.get_attitude();

	attitude->mutable_a00()->set_value(att[0][0]);
	attitude->mutable_a01()->set_value(att[0][1]);
	attitude->mutable_a02()->set_value(att[0][2]);

	attitude->mutable_a10()->set_value(att[1][0]);
	attitude->mutable_a11()->set_value(att[1][1]);
	attitude->mutable_a12()->set_value(att[1][2]);

	attitude->mutable_a20()->set_value(att[2][0]);
	attitude->mutable_a21()->set_value(att[2][1]);
	attitude->mutable_a22()->set_value(att[2][2]);

	//
	// Target
	//
	auto target = request.mutable_currenttarget()->mutable_target();

	// -- Object
	auto object = target->mutable_object();

	auto declination     = object->mutable_declination();
	auto declinationData = inRequest.get_currentTarget().get_object().get_declination();
	declination->mutable_sign()->set_value(declinationData.get_sign());
	declination->mutable_degris()->set_value(declinationData.get_degris());
	declination->mutable_minutes()->set_value(declinationData.get_minutes());
	declination->mutable_seconds()->set_value(declinationData.get_seconds());

	auto hourangle     = object->mutable_hourangle();
	auto hourAngleData = inRequest.get_currentTarget().get_object().get_hourAngle();
	hourangle->mutable_sign()->set_value(hourAngleData.get_sign());
	hourangle->mutable_degris()->set_value(hourAngleData.get_degris());
	hourangle->mutable_minutes()->set_value(hourAngleData.get_minutes());
	hourangle->mutable_seconds()->set_value(hourAngleData.get_seconds());

	object->mutable_propermotionra()->set_value(inRequest.get_currentTarget().get_object().get_properMotionRA());
	object->mutable_propermotiondc()->set_value(inRequest.get_currentTarget().get_object().get_properMotionDC());
	object->mutable_parallax()->set_value(inRequest.get_currentTarget().get_object().get_parallax());
	object->mutable_radialvelocity()->set_value(inRequest.get_currentTarget().get_object().get_radialVelocity());
	object->mutable_catalogtype()->set_value(inRequest.get_currentTarget().get_object().get_catalogType());

	// Delta, speed, aceleration, katalog, ...
	target->mutable_delta()->set_value(inRequest.get_currentTarget().get_delta());
	target->mutable_speed()->set_value(inRequest.get_currentTarget().get_speed());
	target->mutable_aceleration()->set_value(inRequest.get_currentTarget().get_aceleration());

	//
	// Pozycja urzadzenia
	//
	auto devPosition = request.mutable_deviceposition();
	devPosition->mutable_x()->set_value(inRequest.get_devicePosition().get_x());
	devPosition->mutable_y()->set_value(inRequest.get_devicePosition().get_y());
	devPosition->mutable_xencoder()->set_value(inRequest.get_devicePosition().get_xEncoder());
	devPosition->mutable_yencoder()->set_value(inRequest.get_devicePosition().get_yEncoder());

	//
	// Tryb
	//
	switch (inRequest.get_mode()) {
	case tlinsAstroEngineInterface::tlinsEngineMode::MODE_NONE:
		request.mutable_mode()->set_mode(tlins::tlinsEngineMode_::_MODE_NONE);
		break;

	case tlinsAstroEngineInterface::tlinsEngineMode::MODE_STANDARD:
		request.mutable_mode()->set_mode(tlins::tlinsEngineMode_::_MODE_STANDARD);
		break;

	case tlinsAstroEngineInterface::tlinsEngineMode::MODE_EXTERNAL_SUPPORT:
		request.mutable_mode()->set_mode(tlins::tlinsEngineMode_::_MODE_EXTERNAL_SUPPORT);
		break;
	}

	//
	// Stan
	//
	switch (inRequest.get_state()) {
	case tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_CALIBRATION:
		request.mutable_state()->set_state(tlins::tlinsEngineStateValue_::_STATE_CALIBRATION);
		break;

	case tlinsAstroEngineInterface::tlinsEngineStateValue::STATE_REGULAR:
		request.mutable_state()->set_state(tlins::tlinsEngineStateValue_::_STATE_REGULAR);
		break;
	}

	//
	// Multiple
	//
	switch (inRequest.get_multipleFinal()) {
	case tlinsAstroEngineInterface::tlinsMultipleModeFinall::SWITCH_TO_STANDARD:
		request.mutable_multiplefinal()->set_multiple(tlins::tlinsMultipleModeFinall_::_SWITCH_TO_STANDARD);
		break;

	case tlinsAstroEngineInterface::tlinsMultipleModeFinall::SWITCH_TO_EXTERNAL:
		request.mutable_multiplefinal()->set_multiple(tlins::tlinsMultipleModeFinall_::_SWITCH_TO_EXTERNAL);
		break;
	}

	//
	// Znaczniki czy kierunek obrotu osi jest przeciwny
	//
	request.mutable_xreverse()->set_value(inRequest.get_xReverse());
	request.mutable_yreverse()->set_value(inRequest.get_yReverse());


	//
	// Wyslanie rzadania
	//
	grpc::ClientContext context;
	auto                result = connectionStub->restoreState(&context, request, &response);

	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error restore device status."),
		                                  tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(response.errordescription(),
		                                  tlinsInterfaceException::ERROR_ASTRO_RESTORE_DEVICE_STATUS));
	}
}

void tlinsAstroEngineInterface::startTracking()
{
	tlins::Void           request;
	tlins::tlinsRpcStatus response;

	// Wyslanie rzadania
	grpc::ClientContext context;
	auto                result = connectionStub->startTracking(&context, request, &response);

	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error get astro engine state."),
		                                  tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(
		    tlinsInterfaceException(response.errordescription(), tlinsInterfaceException::ERROR_ASTRO_START_TRACKING));
	}
}

void tlinsAstroEngineInterface::stopTracking()
{
	tlins::Void           request;
	tlins::tlinsRpcStatus response;

	// Wyslanie rzadania
	grpc::ClientContext context;
	auto                result = connectionStub->stopTracking(&context, request, &response);

	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error get astro engine state."),
		                                  tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(
		    tlinsInterfaceException(response.errordescription(), tlinsInterfaceException::ERROR_ASTRO_STOP_TRACKING));
	}
}

void tlinsAstroEngineInterface::setTarget(const tlinsTarget &inRequest, const bool isDelta)
{
	tlins::tlinsTarget    request;
	tlins::tlinsRpcStatus response;

	// -- Object
	auto object = request.mutable_object();

	auto  declination     = object->mutable_declination();
	auto &declinationData = inRequest.get_object().get_declination();
	declination->mutable_sign()->set_value(declinationData.get_sign());
	declination->mutable_degris()->set_value(declinationData.get_degris());
	declination->mutable_minutes()->set_value(declinationData.get_minutes());
	declination->mutable_seconds()->set_value(declinationData.get_seconds());

	auto  hourangle     = object->mutable_hourangle();
	auto &hourAngleData = inRequest.get_object().get_hourAngle();
	hourangle->mutable_sign()->set_value(hourAngleData.get_sign());
	hourangle->mutable_degris()->set_value(hourAngleData.get_degris());
	hourangle->mutable_minutes()->set_value(hourAngleData.get_minutes());
	hourangle->mutable_seconds()->set_value(hourAngleData.get_seconds());

	object->mutable_propermotionra()->set_value(inRequest.get_object().get_properMotionRA());
	object->mutable_propermotiondc()->set_value(inRequest.get_object().get_properMotionDC());
	object->mutable_parallax()->set_value(inRequest.get_object().get_parallax());
	object->mutable_radialvelocity()->set_value(inRequest.get_object().get_radialVelocity());
	object->mutable_catalogtype()->set_value(inRequest.get_object().get_catalogType());

	// Delta, speed, aceleration, katalog, ...
	request.mutable_delta()->set_value(inRequest.get_delta());
	request.mutable_speed()->set_value(inRequest.get_speed());
	request.mutable_aceleration()->set_value(inRequest.get_aceleration());
	request.mutable_isincrement()->set_value(isDelta);

	// Wyslanie rzadania
	grpc::ClientContext context;
	auto                result = connectionStub->setTarget(&context, request, &response);

	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(
		    tlinsInterfaceException(std::string("Error get set target."), tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(
		    tlinsInterfaceException(response.errordescription(), tlinsInterfaceException::ERROR_ASTRO_SET_TARGET));
	}
}

void tlinsAstroEngineInterface::getTarget(tlinsTarget &target)
{
	tlins::Void                   request;
	tlins::tlinsCurrentTargetInfo response;

	// Wyslanie rzadania
	grpc::ClientContext context;
	auto                result = connectionStub->getTarget(&context, request, &response);
	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error get target."), tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status().status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(response.status().errordescription(),
		                                  tlinsInterfaceException::ERROR_ASTRO_GET_TARGET));
	}

	target.set_aceleration(0.0);
	target.set_speed(0.0);
	target.set_delta(0);

	// DC
	tlinsCoordinate dc{};
	dc.set_sign(response.target().object().declination().sign().value());
	dc.set_degris(response.target().object().declination().degris().value());
	dc.set_minutes(response.target().object().declination().minutes().value());
	dc.set_seconds(response.target().object().declination().seconds().value());

	// RA
	tlinsCoordinate ra{};
	ra.set_sign(response.target().object().hourangle().sign().value());
	ra.set_degris(response.target().object().hourangle().degris().value());
	ra.set_minutes(response.target().object().hourangle().minutes().value());
	ra.set_seconds(response.target().object().hourangle().seconds().value());

	//
	// Objet astro
	//
	tlinsAstroObject astroObject{};
	astroObject.set_declination(dc);
	astroObject.set_hourAngle(ra);
	astroObject.set_properMotionRA(response.target().object().propermotionra().value());
	astroObject.set_properMotionDC(response.target().object().propermotiondc().value());
	astroObject.set_parallax(response.target().object().parallax().value());
	astroObject.set_radialVelocity(response.target().object().radialvelocity().value());
	astroObject.set_catalogType(response.target().object().catalogtype().value());

	target.set_object(astroObject);
}

void tlinsAstroEngineInterface::registerMeserment(const tlinsMeserment &inRequest, const bool hesInput)
{
	tlins::tlinsMeserment request;
	tlins::tlinsRpcStatus response;

	auto  reference     = request.mutable_reference();
	auto  declination   = reference->mutable_declination();
	auto &inDeclination = inRequest.get_reference().get_declination();

	declination->mutable_sign()->set_value(inDeclination.get_sign());
	declination->mutable_degris()->set_value(inDeclination.get_degris());
	declination->mutable_minutes()->set_value(inDeclination.get_minutes());
	declination->mutable_seconds()->set_value(inDeclination.get_seconds());

	auto  hourAngle   = reference->mutable_hourangle();
	auto &inHourAngle = inRequest.get_reference().get_hourAngle();
	hourAngle->mutable_sign()->set_value(inHourAngle.get_sign());
	hourAngle->mutable_degris()->set_value(inHourAngle.get_degris());
	hourAngle->mutable_minutes()->set_value(inHourAngle.get_minutes());
	hourAngle->mutable_seconds()->set_value(inHourAngle.get_seconds());

	// Ruch wlasny
	auto &inReference = inRequest.get_reference();
	reference->mutable_propermotionra()->set_value(inReference.get_properMotionRA());
	reference->mutable_propermotiondc()->set_value(inReference.get_properMotionDC());
	reference->mutable_parallax()->set_value(inReference.get_parallax());
	reference->mutable_radialvelocity()->set_value(inReference.get_radialVelocity());
	reference->mutable_catalogtype()->set_value(inReference.get_catalogType());

	// Blad wejsciowy
	auto inputError = request.mutable_inputerror();

	auto &devlongitudeErr = inRequest.get_inputError().get_longitude();
	auto &devlatitudeErr  = inRequest.get_inputError().get_latitude();

	auto oLongitudeErr = inputError->mutable_longitude();
	oLongitudeErr->mutable_sign()->set_value(devlongitudeErr.get_sign());
	oLongitudeErr->mutable_degris()->set_value(devlongitudeErr.get_degris());
	oLongitudeErr->mutable_minutes()->set_value(devlongitudeErr.get_minutes());
	oLongitudeErr->mutable_seconds()->set_value(devlongitudeErr.get_seconds());

	auto oLatitudeErr = inputError->mutable_latitude();
	oLatitudeErr->mutable_sign()->set_value(devlatitudeErr.get_sign());
	oLatitudeErr->mutable_degris()->set_value(devlatitudeErr.get_degris());
	oLatitudeErr->mutable_minutes()->set_value(devlatitudeErr.get_minutes());
	oLatitudeErr->mutable_seconds()->set_value(devlatitudeErr.get_seconds());

	// Waga
	request.mutable_w()->set_value(inRequest.get_w());

	if (hesInput) {
		// Wspolrzedne wejscia
		auto  input        = request.mutable_input();
		auto &devlongitude = inRequest.get_input().get_longitude();
		auto &devlatitude  = inRequest.get_input().get_latitude();
		auto  oLongitude   = input->mutable_longitude();

		oLongitude->mutable_sign()->set_value(devlongitude.get_sign());
		oLongitude->mutable_degris()->set_value(devlongitude.get_degris());
		oLongitude->mutable_minutes()->set_value(devlongitude.get_minutes());
		oLongitude->mutable_seconds()->set_value(devlongitude.get_seconds());

		auto oLatitude = input->mutable_latitude();
		oLatitude->mutable_sign()->set_value(devlatitude.get_sign());
		oLatitude->mutable_degris()->set_value(devlatitude.get_degris());
		oLatitude->mutable_minutes()->set_value(devlatitude.get_minutes());
		oLatitude->mutable_seconds()->set_value(devlatitude.get_seconds());
	}

	// Wyslanie rzadania
	grpc::ClientContext context;
	auto                result = connectionStub->registerMeserment(&context, request, &response);

	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error register measurment."),
		                                  tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(response.errordescription(),
		                                  tlinsInterfaceException::ERROR_ASTRO_REGISTER_MEASURMENT));
	}
}

void tlinsAstroEngineInterface::registerMesermentDefered(const tlinsMeserment &inRequest)
{
	tlins::tlinsMeserment request;
	tlins::tlinsRpcStatus response;

	auto  reference     = request.mutable_reference();
	auto  declination   = reference->mutable_declination();
	auto &inDeclination = inRequest.get_reference().get_declination();

	declination->mutable_sign()->set_value(inDeclination.get_sign());
	declination->mutable_degris()->set_value(inDeclination.get_degris());
	declination->mutable_minutes()->set_value(inDeclination.get_minutes());
	declination->mutable_seconds()->set_value(inDeclination.get_seconds());

	auto  hourAngle   = reference->mutable_hourangle();
	auto &inHourAngle = inRequest.get_reference().get_hourAngle();
	hourAngle->mutable_sign()->set_value(inHourAngle.get_sign());
	hourAngle->mutable_degris()->set_value(inHourAngle.get_degris());
	hourAngle->mutable_minutes()->set_value(inHourAngle.get_minutes());
	hourAngle->mutable_seconds()->set_value(inHourAngle.get_seconds());

	// Ruch wlasny
	auto &inReference = inRequest.get_reference();
	reference->mutable_propermotionra()->set_value(inReference.get_properMotionRA());
	reference->mutable_propermotiondc()->set_value(inReference.get_properMotionDC());
	reference->mutable_parallax()->set_value(inReference.get_parallax());
	reference->mutable_radialvelocity()->set_value(inReference.get_radialVelocity());
	reference->mutable_catalogtype()->set_value(inReference.get_catalogType());

	// Blad wejsciowy
	auto  inputError      = request.mutable_inputerror();
	auto &devlongitudeErr = inRequest.get_inputError().get_longitude();
	auto &devlatitudeErr  = inRequest.get_inputError().get_latitude();
	auto  oLongitudeErr   = inputError->mutable_longitude();

	oLongitudeErr->mutable_sign()->set_value(devlongitudeErr.get_sign());
	oLongitudeErr->mutable_degris()->set_value(devlongitudeErr.get_degris());
	oLongitudeErr->mutable_minutes()->set_value(devlongitudeErr.get_minutes());
	oLongitudeErr->mutable_seconds()->set_value(devlongitudeErr.get_seconds());

	auto oLatitudeErr = inputError->mutable_latitude();
	oLatitudeErr->mutable_sign()->set_value(devlatitudeErr.get_sign());
	oLatitudeErr->mutable_degris()->set_value(devlatitudeErr.get_degris());
	oLatitudeErr->mutable_minutes()->set_value(devlatitudeErr.get_minutes());
	oLatitudeErr->mutable_seconds()->set_value(devlatitudeErr.get_seconds());

	// Wyslanie rzadania
	grpc::ClientContext context;
	auto                result = connectionStub->registerMesermentDefered(&context, request, &response);

	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error register measurment."),
		                                  tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(response.errordescription(),
		                                  tlinsInterfaceException::ERROR_ASTRO_REGISTER_MEASURMENT));
	}
}

void tlinsAstroEngineInterface::confirmDeferedMeserment()
{
	tlins::Void           request;
	tlins::tlinsRpcStatus response;

	// Wyslanie rzadania
	grpc::ClientContext context;
	auto                result = connectionStub->confirmDeferedMeserment(&context, request, &response);

	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error confirm measurment."),
		                                  tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(response.errordescription(),
		                                  tlinsInterfaceException::ERROR_ASTRO_REGISTER_MEASURMENT));
	}
}

void tlinsAstroEngineInterface::closeCalibration()
{
	tlins::Void           request;
	tlins::tlinsRpcStatus response;

	// Wyslanie rzadania
	grpc::ClientContext context;
	auto                result = connectionStub->closeCalibration(&context, request, &response);

	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(
		    tlinsInterfaceException(std::string("Error close calibration."), tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(response.errordescription(),
		                                  tlinsInterfaceException::ERROR_ASTRO_CLOSE_CALIBRATION));
	}
}

void tlinsAstroEngineInterface::setEnvironment(const tlinsEnvironment &inRequest)
{
	tlins::tlinsEnvironment request;
	tlins::tlinsRpcStatus   response;

	request.mutable_ambientpressure()->set_value(inRequest.get_ambientPressure());
	request.mutable_temperature()->set_value(inRequest.get_temperature());
	request.mutable_realhumidity()->set_value(inRequest.get_realHumidity());
	request.mutable_effectivecolor()->set_value(inRequest.get_effectiveColor());

	// Wyslanie rzadania
	grpc::ClientContext context;
	auto                result = connectionStub->setEnvironment(&context, request, &response);

	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error set environment parameters."),
		                                  tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(
		    tlinsInterfaceException(response.errordescription(), tlinsInterfaceException::ERROR_ASTRO_SET_ENVIRONMENT));
	}
}

void tlinsAstroEngineInterface::setIERSInfo(const tlinsIERSListItems &inRequest)
{
	tlins::tlinsIERSList  request;
	tlins::tlinsRpcStatus response;

	request.mutable_storelocaly()->set_value(inRequest.get_localStore());
	request.mutable_overwrite()->set_value(inRequest.get_overwrite());

	for (auto &inItem : inRequest) {
		auto item = request.add_items();

		item->mutable_year()->set_value(inItem.get_year());
		item->mutable_month()->set_value(inItem.get_month());
		item->mutable_day()->set_value(inItem.get_day());
		item->mutable_pmx()->set_value(inItem.get_pmX());
		item->mutable_pmy()->set_value(inItem.get_pmY());
		item->mutable_deltaut()->set_value(inItem.get_deltaUT());
		item->mutable_dpsi()->set_value(inItem.get_dPsi());
		item->mutable_depsilon()->set_value(inItem.get_dEpsilon());
		item->mutable_dx()->set_value(inItem.get_dx());
		item->mutable_dy()->set_value(inItem.get_dy());
	}

	// Wyslanie rzadania
	grpc::ClientContext context;
	auto                result = connectionStub->setIERSInfo(&context, request, &response);

	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(
		    tlinsInterfaceException(std::string("Error set IERS info."), tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(
		    tlinsInterfaceException(response.errordescription(), tlinsInterfaceException::ERROR_ASTRO_SET_IERS_INFO));
	}
}

void tlinsAstroEngineInterface::setObservationPlace(const tlinsObservationPlace &inRequest)
{
	tlins::tlinsObservationPlace request;
	tlins::tlinsRpcStatus        response;

	auto lo = request.mutable_longitude();
	lo->mutable_sign()->set_value(inRequest.get_longitude().get_sign());
	lo->mutable_degris()->set_value(inRequest.get_longitude().get_degris());
	lo->mutable_minutes()->set_value(inRequest.get_longitude().get_minutes());
	lo->mutable_seconds()->set_value(inRequest.get_longitude().get_seconds());

	auto la = request.mutable_latitude();
	la->mutable_sign()->set_value(inRequest.get_latitude().get_sign());
	la->mutable_degris()->set_value(inRequest.get_latitude().get_degris());
	la->mutable_minutes()->set_value(inRequest.get_latitude().get_minutes());
	la->mutable_seconds()->set_value(inRequest.get_latitude().get_seconds());

	request.mutable_hm()->set_value(inRequest.get_hm());

	switch (inRequest.get_epType()) {
	case tlinsElipsoideType::WGS_84:
		request.mutable_eptype()->set_value(tlins::tlinsElipsoideType::_WGS_84);
		break;

	case tlinsElipsoideType::GRS_80:
		request.mutable_eptype()->set_value(tlins::tlinsElipsoideType::_GRS_80);
		break;

	case tlinsElipsoideType::WGS_72:
		request.mutable_eptype()->set_value(tlins::tlinsElipsoideType::_WGS_72);
		break;
	}

	// Wyslanie rzadania
	grpc::ClientContext context;
	auto                result = connectionStub->setObservationPlace(&context, request, &response);

	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error set observation place."),
		                                  tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(response.errordescription(),
		                                  tlinsInterfaceException::ERROR_ASTRO_SET_OBSERVATION_PLACE));
	}
}

void tlinsAstroEngineInterface::setMode(const tlinsEngineMode inRequest)
{
	tlins::tlinsEngineMode request;
	tlins::tlinsRpcStatus  response;

	switch (inRequest) {
	case tlinsAstroEngineInterface::tlinsEngineMode::MODE_NONE:
		request.set_mode(tlins::tlinsEngineMode_::_MODE_NONE);
		break;

	case tlinsAstroEngineInterface::tlinsEngineMode::MODE_STANDARD:
		request.set_mode(tlins::tlinsEngineMode_::_MODE_STANDARD);
		break;

	case tlinsAstroEngineInterface::tlinsEngineMode::MODE_EXTERNAL_SUPPORT:
		request.set_mode(tlins::tlinsEngineMode_::_MODE_EXTERNAL_SUPPORT);
		break;

	case tlinsAstroEngineInterface::tlinsEngineMode::MODE_STANDARD_SPEED:
		request.set_mode(tlins::tlinsEngineMode_::_MODE_STANDARD_SPEED);
		break;
	}

	// Wyslanie rzadania
	grpc::ClientContext context;
	auto                result = connectionStub->setMode(&context, request, &response);

	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error set astro engine mode."),
		                                  tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(
		    tlinsInterfaceException(response.errordescription(), tlinsInterfaceException::ERROR_ASTRO_SET_ENGINE_MODE));
	}
}

// Resetowanie kalibracji
void tlinsAstroEngineInterface::resetCalibration(const ReverseDevice x, const ReverseDevice y)
{
	tlins::tlinsResetCalibration request;
	tlins::tlinsRpcStatus        response;


	// DEVICE_SETTINGS = 1, DEVICE_NO_REVERSE = 2, DEVICE_REVERSE

	tlins::BoolValueExtendCodes xx;
	switch (x) {
	case ReverseDevice::DEVICE_SETTINGS:
		xx = tlins::BoolValueExtendCodes::_DERIVED;
		break;
	case ReverseDevice::DEVICE_NO_REVERSE:
		xx = tlins::BoolValueExtendCodes::_FALSE;
		break;
	case ReverseDevice::DEVICE_REVERSE:
		xx = tlins::BoolValueExtendCodes::_TRUE;
		break;
	}

	tlins::BoolValueExtendCodes yy;
	switch (y) {
	case ReverseDevice::DEVICE_SETTINGS:
		yy = tlins::BoolValueExtendCodes::_DERIVED;
		break;
	case ReverseDevice::DEVICE_NO_REVERSE:
		yy = tlins::BoolValueExtendCodes::_FALSE;
		break;
	case ReverseDevice::DEVICE_REVERSE:
		yy = tlins::BoolValueExtendCodes::_TRUE;
		break;
	}
	request.mutable_reversedevicex()->set_value(xx);
	request.mutable_reversedevicey()->set_value(yy);

	// Wyslanie rzadania
	grpc::ClientContext context;
	auto                result = connectionStub->resetCalibration(&context, request, &response);

	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(
		    tlinsInterfaceException(std::string("Error reset calibration."), tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(response.errordescription(),
		                                  tlinsInterfaceException::ERROR_ASTRO_RESET_CALIBRATIUON));
	}
}

void tlinsAstroEngineInterface::setTargetForCurrentPosition(void)
{
	tlins::Void           request;
	tlins::tlinsRpcStatus response;

	// Wyslanie rzadania
	grpc::ClientContext context;
	auto                result = connectionStub->setTargetForCurrentPosition(&context, request, &response);

	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error set current target based on current telescope position."),
		                                  tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(response.errordescription(),
		                                  tlinsInterfaceException::ERROR_ASTRO_RESET_CALIBRATIUON));
	}
}

void tlinsAstroEngineInterface::setTracking(const double ra, const double dec)
{
	tlins::tlinsTracking  request;
	tlins::tlinsRpcStatus response;

	request.mutable_ra()->set_value(ra);
	request.mutable_dec()->set_value(dec);

	// Wyslanie rzadania
	grpc::ClientContext context;
	auto                result = connectionStub->setTracking(&context, request, &response);

	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error set tracking parameters."),
		                                  tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(
		    tlinsInterfaceException(response.errordescription(), tlinsInterfaceException::ERROR_ASTRO_TRACKING_SET));
	}
}

void tlinsAstroEngineInterface::setTrackingState(const bool state)
{
	tlins::tlinsBoolValue request;
	tlins::tlinsRpcStatus response;

	request.set_value(state);

	// Wyslanie rzadania
	grpc::ClientContext context;
	auto                result = connectionStub->setTrackingState(&context, request, &response);

	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error set tracking state."),
		                                  tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(
		    tlinsInterfaceException(response.errordescription(), tlinsInterfaceException::ERROR_ASTRO_TRACKING_STATE));
	}
}

void tlinsAstroEngineInterface::getTrackingState(bool &state, double &ra, double &dec) const
{
	tlins::Void                request;
	tlins::tlinsTrackingStatus response;

	// Wyslanie rzadania
	grpc::ClientContext context;
	auto                result = connectionStub->getTrackingState(&context, request, &response);

	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error set tracking state."),
		                                  tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status().status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(response.status().errordescription(),
		                                  tlinsInterfaceException::ERROR_ASTRO_TRACKING_STATE));
	}

	state = response.trackingstatus().value();
	ra    = response.ra().value();
	dec   = response.dec().value();
}

//
// --- Guider interface ---
//
tlinsAstroEngineInterface::GuiderStatus tlinsAstroEngineInterface::guideNorth(const long interval)
{
	tlins::tlinsIntValue     request;
	tlins::tlinsGuiderStatus response;

	// Wyslanie rzadania
	grpc::ClientContext context;
	request.set_value(interval);
	auto result = connectionStub->guideNorth(&context, request, &response);

	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error set guider correction."),
		                                  tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status().status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		switch (response.guiderstatus()) {
		case tlins::tlinsGuiderStatus_::_GUIDER_IN_PROGRESS:
			return tlinsAstroEngineInterface::GuiderStatus::IN_PROGRESS;

		case tlins::tlinsGuiderStatus_::_GUIDER_NO_TARGET:
			return tlinsAstroEngineInterface::GuiderStatus::NO_TARGET;

		case tlins::tlinsGuiderStatus_::_GUIDER_ERROR:
			return tlinsAstroEngineInterface::GuiderStatus::ERROR;
		}
	}
	return tlinsAstroEngineInterface::GuiderStatus::SET;
}

tlinsAstroEngineInterface::GuiderStatus tlinsAstroEngineInterface::guideSounth(const long interval)
{
	tlins::tlinsIntValue                    request;
	tlins::tlinsGuiderStatus                response;
	tlinsAstroEngineInterface::GuiderStatus gStatus;

	// Wyslanie rzadania
	grpc::ClientContext context;
	request.set_value(interval);
	auto result = connectionStub->guideSounth(&context, request, &response);

	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error set guider correction."),
		                                  tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status().status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		switch (response.guiderstatus()) {
		case tlins::tlinsGuiderStatus_::_GUIDER_IN_PROGRESS:
			return tlinsAstroEngineInterface::GuiderStatus::IN_PROGRESS;

		case tlins::tlinsGuiderStatus_::_GUIDER_NO_TARGET:
			return tlinsAstroEngineInterface::GuiderStatus::NO_TARGET;

		case tlins::tlinsGuiderStatus_::_GUIDER_ERROR:
			return tlinsAstroEngineInterface::GuiderStatus::ERROR;
		}
	}
	return tlinsAstroEngineInterface::GuiderStatus::SET;
}

tlinsAstroEngineInterface::GuiderStatus tlinsAstroEngineInterface::guideEst(const long interval)
{
	tlins::tlinsIntValue                    request;
	tlins::tlinsGuiderStatus                response;
	tlinsAstroEngineInterface::GuiderStatus gStatus;

	// Wyslanie rzadania
	grpc::ClientContext context;
	request.set_value(interval);
	auto result = connectionStub->guideEst(&context, request, &response);

	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error set guider correction."),
		                                  tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status().status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		switch (response.guiderstatus()) {
		case tlins::tlinsGuiderStatus_::_GUIDER_IN_PROGRESS:
			return tlinsAstroEngineInterface::GuiderStatus::IN_PROGRESS;

		case tlins::tlinsGuiderStatus_::_GUIDER_NO_TARGET:
			return tlinsAstroEngineInterface::GuiderStatus::NO_TARGET;

		case tlins::tlinsGuiderStatus_::_GUIDER_ERROR:
			return tlinsAstroEngineInterface::GuiderStatus::ERROR;
		}
	}
	return tlinsAstroEngineInterface::GuiderStatus::SET;
}

tlinsAstroEngineInterface::GuiderStatus tlinsAstroEngineInterface::guideWest(const long interval)
{
	tlins::tlinsIntValue                    request;
	tlins::tlinsGuiderStatus                response;
	tlinsAstroEngineInterface::GuiderStatus gStatus;

	// Wyslanie rzadania
	grpc::ClientContext context;
	request.set_value(interval);
	auto result = connectionStub->guideWest(&context, request, &response);

	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error set guider correction"),
		                                  tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status().status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		switch (response.guiderstatus()) {
		case tlins::tlinsGuiderStatus_::_GUIDER_IN_PROGRESS:
			return tlinsAstroEngineInterface::GuiderStatus::IN_PROGRESS;

		case tlins::tlinsGuiderStatus_::_GUIDER_NO_TARGET:
			return tlinsAstroEngineInterface::GuiderStatus::NO_TARGET;

		case tlins::tlinsGuiderStatus_::_GUIDER_ERROR:
			return tlinsAstroEngineInterface::GuiderStatus::ERROR;
		}
	}
	return tlinsAstroEngineInterface::GuiderStatus::SET;
}

void tlinsAstroEngineInterface::manualCorrectionReset()
{
	tlins::Void           request;
	tlins::tlinsRpcStatus response;
	grpc::ClientContext   context;
	auto                  result = connectionStub->manualCorrectionReset(&context, request, &response);

	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error set guider correction"),
		                                  tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		__THROW__(tlinsInterfaceException(std::string("Error set guider correction"),
		                                  tlinsInterfaceException::ERROR_RPC_ERROR));
	}
}

void tlinsAstroEngineInterface::manualCorrection(double raCorrection, double decCorrection)
{
	tlins::tlinsManualCorrection request;
	tlins::tlinsRpcStatus        response;

	grpc::ClientContext context;
	request.mutable_ra()->set_value(raCorrection);
	request.mutable_dec()->set_value(decCorrection);
	auto result = connectionStub->manualCorrection(&context, request, &response);

	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error set manual correction"),
		                                  tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		__THROW__(tlinsInterfaceException(std::string("Error set manual correction"),
		                                  tlinsInterfaceException::ERROR_RPC_ERROR));
	}
}

void tlinsAstroEngineInterface::sync(const double ra, const double dec)
{
	tlins::tlinsSync      request;
	tlins::tlinsRpcStatus response;

	grpc::ClientContext context;
	request.mutable_ra()->set_value(ra);
	request.mutable_dec()->set_value(ra);
	auto result = connectionStub->sync(&context, request, &response);

	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error sync device"), tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		__THROW__(tlinsInterfaceException(std::string("Error sync device"), tlinsInterfaceException::ERROR_RPC_ERROR));
	}
}

void tlinsAstroEngineInterface::guiderRatioSet(const double ra, const double dec, const bool useRaForDec)
{
	tlins::tlinsGuiderConfigSet request;
	tlins::tlinsRpcStatus       response;

	grpc::ClientContext context;
	request.mutable_raratio()->set_value(ra);
	request.mutable_decratio()->set_value(dec);
	request.mutable_userafordec()->set_value(useRaForDec);
	auto result = connectionStub->guiderRatioSet(&context, request, &response);

	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(
		    tlinsInterfaceException(std::string("Error set guider ratio"), tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		__THROW__(
		    tlinsInterfaceException(std::string("Error set guider ratio"), tlinsInterfaceException::ERROR_RPC_ERROR));
	}
}

void tlinsAstroEngineInterface::guiderRatioGet(double &ra, double &dec, bool &useRaForDec)
{
	tlins::Void                    request;
	tlins::tlinsGuiderConfigStatus response;

	grpc::ClientContext context;
	auto                result = connectionStub->guiderRatioGet(&context, request, &response);

	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(
		    tlinsInterfaceException(std::string("Error set guider ratio"), tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status().status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		__THROW__(
		    tlinsInterfaceException(std::string("Error set guider ratio"), tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	ra          = response.raratio().value();
	dec         = response.decratio().value();
	useRaForDec = response.userafordec().value();
}

void tlinsAstroEngineInterface::manualCorrectionGet(double &raCorrection, double &decCorrection)
{
	tlins::Void                        request;
	tlins::tlinsManualCorrectionStatus response;

	grpc::ClientContext context;
	auto                result = connectionStub->manualCorrectionGet(&context, request, &response);

	if (!result.ok()) {
		// Blad rejestrowania potwierdzenia
		__THROW__(tlinsInterfaceException(std::string("Error get manual correction configuration"),
		                                  tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	if (response.status().status() != tlins::ErrorCodes::_ERROR_CODE_SUCCESS) {
		__THROW__(tlinsInterfaceException(std::string("Error get manual correction configuration"),
		                                  tlinsInterfaceException::ERROR_RPC_ERROR));
	}

	raCorrection  = response.ra().value();
	decCorrection = response.dec().value();
}


tlinsAstroEngineInterface::tlinsAstroEngineInterface(std::shared_ptr<grpc::Channel> &channel)
    : connectionStub{tlins::tlinsRpcAstroService::NewStub(channel)}
{
}

tlinsAstroEngineInterface::~tlinsAstroEngineInterface()
{
}
