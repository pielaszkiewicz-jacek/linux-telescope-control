#include "tlinspluginsstate.h"
#include <tlinsconfiguration.h>

#include <mutex>

namespace tlinsAstroPilot
{

void tlinsPluginsState :: executeCb(const VALUE_TYPE v)
{
    std::unique_lock<std::recursive_mutex> lock{mtx};

    for(auto &item: callbacks) {
        item(v);
    }
}

void tlinsPluginsState :: addCallback(std::function<void(const VALUE_TYPE)> fun)
{
    std::unique_lock<std::recursive_mutex> lock{mtx};
    callbacks.push_back(fun);
}

tlinsPluginsState &tlinsPluginsState :: getInstance()
{
	static tlinsPluginsState instance{};
	return instance;
}

bool tlinsPluginsState :: getSpeedMode()
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};
	return speedMode;
}

void tlinsPluginsState :: setSpeedMode( const bool v )
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};
	speedMode = v;
    executeCb(VALUE_TYPE::__speedMode__);
}

void tlinsPluginsState :: updateSpeedMode( const bool v )
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};
    speedMode = v;
}

void tlinsPluginsState :: setInSteps( const bool v )
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};
	inSteps = v;
    executeCb(VALUE_TYPE::__inSteps__);
}

void tlinsPluginsState :: updateInSteps( const bool v )
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};
    inSteps = v;
}

bool tlinsPluginsState :: getInSteps()
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};
	return inSteps;
}

double tlinsPluginsState :: getXDegrisDelta()
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};
	return xDegrisDelta;
}

double tlinsPluginsState :: getYDegrisDelta()
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};
	return yDegrisDelta;
}

double tlinsPluginsState :: getXDegrisSpeed()
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};
	return xDegrisSpeed;
}

double tlinsPluginsState :: getYDegrisSpeed()
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};
	return yDegrisSpeed;
}

long tlinsPluginsState :: getXStepsDelta()
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};
	return xStepsDelta;
}

long tlinsPluginsState :: getYStepsDelta()
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};
	return yStepsDelta;
}

long tlinsPluginsState :: getXStepsSpeed()
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};
	return xStepsSpeed;
}

long tlinsPluginsState :: getYStepsSpeed()
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};
	return yStepsSpeed;
}

bool tlinsPluginsState :: setXDegrisDelta( const double v )
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};

	if( ( xDegrisDelta + v ) < 0.0 )
		return false;

	xDegrisDelta += v;
    executeCb(VALUE_TYPE::__xDegrisDelta__);
	return true;
}

bool tlinsPluginsState :: updateXDegrisDelta( const double v )
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};
    xDegrisDelta = v;
    return true;
}

bool tlinsPluginsState :: setYDegrisDelta( const double v )
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};

	if( ( yDegrisDelta + v ) < 0.0 )
		return false;

	yDegrisDelta += v;
    executeCb(VALUE_TYPE::__yDegrisDelta__);
	return true;
}

bool tlinsPluginsState :: updateYDegrisDelta( const double v )
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};
    yDegrisDelta = v;
    return true;
}

bool tlinsPluginsState :: setXDegrisSpeed( const double v )
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};

	if( ( xDegrisSpeed + v ) < 0.0 )
		return false;

	xDegrisSpeed += v;
    executeCb(VALUE_TYPE::__xDegrisSpeed__);
	return true;
}

bool tlinsPluginsState :: updateXDegrisSpeed( const double v )
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};
    xDegrisSpeed = v;
    return true;
}

bool tlinsPluginsState :: setYDegrisSpeed( const double v )
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};

	if( ( yDegrisSpeed + v ) < 0.0 )
		return false;

	yDegrisSpeed += v;
    executeCb(VALUE_TYPE::__yDegrisSpeed__);
	return true;
}

bool tlinsPluginsState :: updateYDegrisSpeed( const double v )
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};
    yDegrisSpeed = v;
    return true;
}

bool tlinsPluginsState :: setXStepsDelta( const long v )
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};

	if( ( xStepsDelta + v ) < 0 )
		return false;

	xStepsDelta += v;
    executeCb(VALUE_TYPE::__xStepsDelta__);
	return true;
}

bool tlinsPluginsState :: updateXStepsDelta( const long v )
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};
    xStepsDelta = v;
    return true;
}

bool tlinsPluginsState :: setYStepsDelta( const long v )
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};

	if( ( yStepsDelta + v ) < 0 )
		return false;

	yStepsDelta += v;
    executeCb(VALUE_TYPE::__yStepsDelta__);
	return true;
}

bool tlinsPluginsState :: updateYStepsDelta( const long v )
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};
    yStepsDelta = v;
    return true;
}

bool tlinsPluginsState :: setXStepsSpeed( const long v )
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};

	if( ( xStepsSpeed + v ) < 0 )
		return false;

	xStepsSpeed += v;
    executeCb(VALUE_TYPE::__xStepsSpeed__);
	return true;
}

bool tlinsPluginsState :: updateXStepsSpeed( const long v )
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};
    xStepsSpeed = v;
    return true;
}

bool tlinsPluginsState :: setYStepsSpeed( const long v )
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};

	if( ( yStepsSpeed + v ) < 0 )
		return false;

	yStepsSpeed += v;
    executeCb(VALUE_TYPE::__yStepsSpeed__);
	return true;
}


int tlinsPluginsState :: getXScale()
{
    return xScale;
}
int tlinsPluginsState :: getYScale()
{
    return yScale;
}

bool tlinsPluginsState :: updateXScale(const int v)
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};
    xScale = v;
    return true;
}

bool tlinsPluginsState :: updateYScale(const int v)
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};
    yScale = v;
    return true;
}

bool tlinsPluginsState :: setXScale(const int v)
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};

    if( ( xScale + v ) < 0 )
        return false;

    xScale += v;
    executeCb(VALUE_TYPE::__xScale__);
    return true;
}

bool tlinsPluginsState :: setYScale(const int v)
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};

    if( ( yScale + v ) < 0 )
        return false;

    yScale += v;
    executeCb(VALUE_TYPE::__yScale__);
    return true;
}



bool tlinsPluginsState :: updateYStepsSpeed( const long v )
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};
    yStepsSpeed = v;
    return true;
}

double tlinsPluginsState :: getRaDelta()
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};
	return raDelta;
}

double tlinsPluginsState :: getDcDelta()
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};
	return dcDelta;
}

bool tlinsPluginsState :: setRaDelta( const double v )
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};

	if( ( raDelta + v ) < 0.0 )
		return false;

	if( ( raDelta + v ) >= 24.0 )
		return false;

	raDelta += v;
    executeCb(VALUE_TYPE::__raDelta__);
	return true;
}

bool tlinsPluginsState :: updateRaDelta( const double v )
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};
    raDelta = v;
    return true;
}

bool tlinsPluginsState :: setDcDelta( const double v )
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};

	if( ( dcDelta + v ) < 0.0 )
		return false;

	dcDelta += v;
    executeCb(VALUE_TYPE::__dcDelta__);
	return true;
}

bool tlinsPluginsState :: updateDcDelta( const double v )
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};
    dcDelta = v;
    return true;
}

double tlinsPluginsState :: getRaSpeed()
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};
	return raSpeed;
}

double tlinsPluginsState :: getDcSpeed()
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};
	return dcSpeed;
}

bool tlinsPluginsState :: setRaSpeed( const double v )
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};

	if( (raSpeed + v) < 0.0 )
		return false;

	raSpeed += v;
    executeCb(VALUE_TYPE::__raSpeed__);
	return true;
}

bool tlinsPluginsState :: updateRaSpeed( const double v )
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};
    raSpeed = v;
    return true;
}

bool tlinsPluginsState :: setDcSpeed( const double v )
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};

	if( ( dcSpeed + v ) < 0.0 )
		return false;

	dcSpeed += v;
    executeCb(VALUE_TYPE::__dcSpeed__);
	return true;
}

bool tlinsPluginsState :: updateDcSpeed( const double v )
{
    std :: unique_lock<std :: recursive_mutex> lock{mtx};
    dcSpeed = v;
    return true;
}

tlinsPluginsState :: tlinsPluginsState()
{
	calibrationObjectId = 0;

	//
	// Odczyt domyslnej konfiguracji astro
	//
	auto &instanceCfg = TlinsAstroBase :: tlinsConfiguration :: getInstance();

	speedMode = true;
	inSteps   = false;

	raDelta = instanceCfg.getDouble( TlinsAstroBase :: tlinsConfiguration :: PILOT_PARAMETER_GROUP,
	                                 TlinsAstroBase :: tlinsConfiguration :: PILOT_PARAMETER_ASTRO_RA);

	dcDelta = instanceCfg.getDouble( TlinsAstroBase :: tlinsConfiguration :: PILOT_PARAMETER_GROUP,
	                                 TlinsAstroBase :: tlinsConfiguration :: PILOT_PARAMETER_ASTRO_DC);

	raSpeed = instanceCfg.getDouble( TlinsAstroBase :: tlinsConfiguration :: PILOT_PARAMETER_GROUP,
	                                 TlinsAstroBase :: tlinsConfiguration :: PILOT_PARAMETER_ASTRO_RA_V );

	dcSpeed = instanceCfg.getDouble( TlinsAstroBase :: tlinsConfiguration :: PILOT_PARAMETER_GROUP,
	                                 TlinsAstroBase :: tlinsConfiguration :: PILOT_PARAMETER_ASTRO_DC_V );

	//
	// Odczyt domyslnej konfiguracji nie astro
	//
	xDegrisDelta = instanceCfg.getDouble( TlinsAstroBase :: tlinsConfiguration :: PILOT_PARAMETER_GROUP,
	                                      TlinsAstroBase :: tlinsConfiguration :: PILOT_PARAMETER_DEGRIS_X );

	yDegrisDelta = instanceCfg.getDouble( TlinsAstroBase :: tlinsConfiguration :: PILOT_PARAMETER_GROUP,
	                                      TlinsAstroBase :: tlinsConfiguration :: PILOT_PARAMETER_DEGRIS_Y );

	xDegrisSpeed = instanceCfg.getDouble( TlinsAstroBase :: tlinsConfiguration :: PILOT_PARAMETER_GROUP,
	                                      TlinsAstroBase :: tlinsConfiguration :: PILOT_PARAMETER_DEGRIS_X_V );

	yDegrisSpeed = instanceCfg.getDouble( TlinsAstroBase :: tlinsConfiguration :: PILOT_PARAMETER_GROUP,
	                                      TlinsAstroBase :: tlinsConfiguration :: PILOT_PARAMETER_DEGRIS_Y_V );

	xStepsDelta = instanceCfg.getInt( TlinsAstroBase :: tlinsConfiguration :: PILOT_PARAMETER_GROUP,
	                                  TlinsAstroBase :: tlinsConfiguration :: PILOT_PARAMETER_STEPS_X );

	yStepsDelta = instanceCfg.getInt( TlinsAstroBase :: tlinsConfiguration :: PILOT_PARAMETER_GROUP,
	                                  TlinsAstroBase :: tlinsConfiguration :: PILOT_PARAMETER_STEPS_Y );

	xStepsSpeed = instanceCfg.getInt( TlinsAstroBase :: tlinsConfiguration :: PILOT_PARAMETER_GROUP,
	                                  TlinsAstroBase :: tlinsConfiguration :: PILOT_PARAMETER_STEPS_X_V );

	yStepsSpeed = instanceCfg.getInt( TlinsAstroBase :: tlinsConfiguration :: PILOT_PARAMETER_GROUP,
	                                  TlinsAstroBase :: tlinsConfiguration :: PILOT_PARAMETER_STEPS_Y_V );
}

};
