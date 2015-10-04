
#include "stdafx.h"
#include "PricingService.h"

// Due to VBA/C++ communication which doesn't recognize bool type
bool getBoolIsCall(LONG isCall) 
{
	if(isCall == 1) {
		return true;
	} else {
		return false;
	}
}

// MarketData calls
extern "C" PRICING_SERVICES_API double __stdcall getSpot(LPCSTR mnemo, LPCSTR periode)
{
	double result = 0.0;
	EquityPrice *ep = (EquityPrice*)::GetEquityPrice(mnemo, periode);
	if(ep) {
		ep->calculateSpot();
		result = ep->getSpot();
		delete ep;
	} else {
		result = -1.0;
	}

	return result;
}

extern "C" PRICING_SERVICES_API double __stdcall getVol(LPCSTR mnemo, LPCSTR periode)
{
	double result = 0.0;
	EquityPrice *ep = (EquityPrice*)::GetEquityPrice(mnemo, periode);
	if(ep) {
		ep->calculateVol();
		result = ep->getVol();
		delete ep;
	} else {
		result = -1.0;
	}

	return result;
} 

extern "C" PRICING_SERVICES_API double __stdcall getTaux(LPCSTR mnemo, LPCSTR periode)
{
	double result = 0.0;
	EquityPrice *ep = (EquityPrice*)::GetEquityPrice(mnemo, periode);
	if(ep) {
		ep->calculateTaux();
		result = ep->getTaux();
		delete ep;
	} else {
		result = -1.0;
	}

	return result;
}


// QuantModel calls
extern "C" PRICING_SERVICES_API double __stdcall getDelta(double S, double K, double vol, double taux, double T, LONG isCall)
{
	bool isCallBool = getBoolIsCall(isCall);
	double result = 0.0;
	CQuantModelServices *qm = (CQuantModelServices*)::GetQuantModel();

	if(qm) {
		qm->calculateDelta(S, K, vol, taux, T, isCallBool);
		result = qm->getDelta();
		delete qm;
	} else {
		result = -1.0;
	}

	return result;
}

extern "C" PRICING_SERVICES_API double __stdcall getGamma(double S, double K, double vol, double taux, double T, LONG isCall)
{
	bool isCallBool = getBoolIsCall(isCall);
	double result = 0.0;
	CQuantModelServices *qm = (CQuantModelServices*)::GetQuantModel();

	if(qm) {
		qm->calculateGamma(S, K, vol, taux, T, isCallBool);
		result = qm->getGamma();
		delete qm;
	} else {
		result = -1.0;
	}

	return result;
}

extern "C" PRICING_SERVICES_API double __stdcall getVega(double S, double K, double vol, double taux, double T, LONG isCall)
{
	bool isCallBool = getBoolIsCall(isCall);
	double result = 0.0;
	CQuantModelServices *qm = (CQuantModelServices*)::GetQuantModel();

	if(qm) {
		qm->calculateVega(S, K, vol, taux, T, isCallBool);
		result = qm->getVega();
		delete qm;
	} else {
		result = -1.0;
	}
	
	return result;
}

extern "C" PRICING_SERVICES_API double __stdcall getRho(double S, double K, double vol, double taux, double T, LONG isCall)
{
	bool isCallBool = getBoolIsCall(isCall);
	double result = 0.0;
	CQuantModelServices *qm = (CQuantModelServices*)::GetQuantModel();

	if(qm) {
		qm->calculateRho(S, K, vol, taux, T, isCallBool);
		result = qm->getRho();
		delete qm;
	} else {
		result = -1.0;
	}

	return result;
}

extern "C" PRICING_SERVICES_API double __stdcall getTheta(double S, double K, double vol, double taux, double T, LONG isCall)
{
	bool isCallBool = getBoolIsCall(isCall);
	double result = 0.0;
	CQuantModelServices *qm = (CQuantModelServices*)::GetQuantModel();

	if(qm) {
		qm->calculateTheta(S, K, vol, taux, T, isCallBool);
		result = qm->getTheta();
		delete qm;
	} else {
		result = -1.0;
	}

	return result;
}

extern "C" PRICING_SERVICES_API double __stdcall getBlackAndScholes(double S, double K, double vol, double taux, double T, LONG isCall)
{
	bool isCallBool = getBoolIsCall(isCall);
	double result = 0.0;
	CQuantModelServices *qm = (CQuantModelServices*)::GetQuantModel();

	if(qm) {
		qm->calculateBlackAndScholes(S, K, vol, taux, T, isCallBool);
		result = qm->getBlackAndScholes();
	} else {
		result = -1.0;
	}

	return result;
}