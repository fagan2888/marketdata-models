#ifdef PRICINGSERVICE_EXPORTS
#define PRICING_SERVICES_API __declspec(dllexport)
#else
#define PRICING_SERVICES_API __declspec(dllimport)
#endif

#ifndef PRICING_SERVICES_H_
#define PRICING_SERVICES_H_

#include <string>

#include "include/QuantModelService.h"
#include "include/MarketDataService.h"

// Called by VBA code 
extern "C" PRICING_SERVICES_API double __stdcall getSpot(LPCSTR mnemo, LPCSTR periode);
extern "C" PRICING_SERVICES_API double __stdcall getVol(LPCSTR mnemo, LPCSTR periode);
extern "C" PRICING_SERVICES_API double __stdcall getTaux(LPCSTR mnemo, LPCSTR periode);

extern "C" PRICING_SERVICES_API double __stdcall getDelta(double S, double K, double vol, double taux, double T, LONG isCall);
extern "C" PRICING_SERVICES_API double __stdcall getGamma(double S, double K, double vol, double taux, double T, LONG isCall);
extern "C" PRICING_SERVICES_API double __stdcall getVega(double S, double K, double vol, double taux, double T, LONG isCall);
extern "C" PRICING_SERVICES_API double __stdcall getRho(double S, double K, double vol, double taux, double T, LONG isCall);
extern "C" PRICING_SERVICES_API double __stdcall getTheta(double S, double K, double vol, double taux, double T, LONG isCall);
extern "C" PRICING_SERVICES_API double __stdcall getBlackAndScholes(double S, double K, double vol, double taux, double T, LONG isCall);


#endif