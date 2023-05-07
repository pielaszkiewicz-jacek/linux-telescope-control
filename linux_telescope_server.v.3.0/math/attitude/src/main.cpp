
#include <iostream>
#include <tlinBaseIteration.hpp>
#include <tlinmUtilsClass.hpp>
#include <tlinm_testUtilty.hpp>
#include <tlinsEnvironment.hpp>
#include <tlinsObservationPlace.hpp>

#include <tlinmUtilsClass.hpp>

#include <Eigen/Eigenvalues>
#include <Eigen/Geometry>

#include <tlinProcess.hpp>
#include <tlinmMeasurement.hpp>

#include <tlinAttitudeProcess.hpp>

#include <tlinmUtilsClass.hpp>

using namespace Eigen;

using namespace std;
/// home/jacek/development/project/clang-format/clang-format
int main(void)
{
	// Parametery loggera
	auto &loggerInstance = tlinsLogger::instance();
	loggerInstance.setLoggerStd();
	loggerInstance.setLogLevel(tlinsLogger::LOG_LEVEL_DEBUG);

	cout << "######################################################################################" << endl;
	cout << "######################################################################################" << endl;
	cout << "######################################################################################" << endl;

	double errorLevel = 360.0 * 60.0 * 1.0;

	{
		//
		// 1. Nowy obiekt procesu - glebokosc historii 200
		//
		attitude ::tlinAttitudeProcess process(200);

		//
		// 2. Miejsce obserwacji
		//
		auto &op = tlinsObservationPlace::getInstance();
		op.setLatitude(tlinsCoordinate{false, 52, 13, 47.17});
		op.setLongitude(tlinsCoordinate{false, 21, 00, 42.41});

		//
		// 3. Warunki srodowiskowe
		//
		tlinsEnvironment ::setAmbientPressure(900.0);
		tlinsEnvironment ::setRealHumidity(40.0);
		tlinsEnvironment ::setTemperature(10.0);

		//
		// 4. Generacja danych testowych
		//
		// tlinmTestUtility trans(0.4, 0.3, 0.2);
		// tlinmTestUtility trans(0.3, 0.4, 0.2);
		// tlinmTestUtility trans(0.3, 0.2, 0.4);

		tlinmTestUtility trans(0.2, 0.3, 0.4);

		// tlinmTestUtility trans(0.2, 0.4, 0.3);

		//
		// 5. Obiekty referencyjne
		//
		std::vector<tlinmTestUtility::Object> refObjects;
		std::set<int>                         items{1, 2, 3, 4};

		// std::set<int>                         items{1};
		populatePrdefinedList(refObjects, items);

		//
		// 6. generacja danych pomiarowych na podstawie obiektow referencyjnych
		//
		trans.generateTestData2(0.0, 30, errorLevel, 3, refObjects);

		//
		// 7. Generowanie macierzy z danych pomiaroeych
		//
		auto &measurments = trans.getNewMeasurements();

		std ::vector<attitude ::tlinAttitudeMeasurement> newMeasurements;

		attitude ::tlinAttitudeMeasurement last;
		for (auto &item : measurments) {
			LOG_DEBUG("");
			LOG_DEBUG(">>>>>>>>> START <<<<<<<<");
			LOG_DEBUG(">>>>>>>>> START <<<<<<<<");
			LOG_DEBUG(">>>>>>>>> START <<<<<<<<");

			process.registerMeasurment(item.getReferenceVector(), item.getObservationVector(),
			                           item.getObservationVectorError(), item.getRotationSpeed(),
			                           item.getRotationSpeedError(), item.getObservationTime(), item.getWeight(),
			                           item.getDeltaM(), item.getAngleX(), item.getAngleY(), item.getAngleZ());

			last = item;

			tlinmUtilsClass::printMatrix(item.getReferenceVector(), "item.getReferenceVector()", "%f");
			tlinmUtilsClass::printMatrix(item.getObservationVector(), "item.getObservationVector()", "%f");
			tlinmUtilsClass::printMatrix(item.getObservationVectorError(), "item.getObservationVectorError()", "%f");

			LOG_DEBUG(">>>>>>>>>  END  <<<<<<<<");
			LOG_DEBUG(">>>>>>>>>  END  <<<<<<<<");
			LOG_DEBUG(">>>>>>>>>  END  <<<<<<<<");
		}


		Eigen::Vector3d ref = last.getReferenceVector();

		double pi    = 3.14159265358979323846264338327950;
		double pi_2  = 2.0 * pi;
		double mTime = 0.0;

		for (int i = 0; i < 100000; i++) {
			double angle = 3.966235 + mTime / (24.0 * 3600.0) * 2 * pi;

			while (angle > pi_2)
				angle -= pi_2;

			Eigen::Matrix3d zRotaionMatrix;
			tlinmUtilsClass ::buildZRotaionMatrix(angle, zRotaionMatrix);
			Eigen::Vector3d rRef = zRotaionMatrix * ref;


			Eigen::Vector3d outVector; // = process.getAttitude() * rRef;

			// tlinmUtilsClass::printMatrix(rRef,      "REF   ", "%15.9f");
			// tlinmUtilsClass::printMatrix(rRef,      "REF R ", "%15.9f");
			// tlinmUtilsClass::printMatrix(outVector, "DEV   ", "%15.9f");

			Eigen::Vector2d out;
			tlinmUtilsClass::toSpeherical(outVector, out);
			printf("%2.9f;%+3.12f;%+3.12f\n", angle, out(0), out(1));

			//            printf("-------------------------------------------------------------------\n");

			mTime += 1.0;
		}


		// void tlinmTestUtility::transformVector(const Eigen::Vector3d &inVector, Eigen::Vector3d &outVector)
		// {
		// 	// Wyznaczanie wektora w nowym ukladzie wspolrzednych
		// 	tlinmUtilsClass::printMatrix(inVector,     "IN Transfor matrix ", "%15.9f");
		// 	tlinmUtilsClass::printMatrix(rotaionMatrix, "Transfor matrix   ", "%15.9f");
		// 	outVector = rotaionMatrix * inVector;
		// 	tlinmUtilsClass::printMatrix(outVector,     "OUT Transfor matrix ", "%15.9f");
		// }
	}

	/*

	*/
	return 0;
}
