// QuantModelService.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "QuantModelService.h"

// Gaussian (normal) distribution function
double n(double x) 
{ 
	double A = 1.0/sqrt(2.0 * 3.1415);
	return A * exp(-x*x*0.5);
}

// The approximation to the cumulative normal distribution function
double N(double x)
{ 
	double a1 = 0.4361836;
	double a2 = -0.1201676;
	double a3 = 0.9372980;

	double k = 1.0/(1.0 + (0.33267 * x));
	
	if (x >= 0.0) {
		return 1.0 - n(x)* (a1*k + (a2*k*k) + (a3*k*k*k));
	} else {
		return 1.0 - N(-x);
	}
}




// Black and Scholes
void CQuantModelServices::calculateBlackAndScholes(double S, double K, double vol, double R, double T, bool isCall)
{
	if(isCall) {
		this->setBlackAndScholes(CQuantModelServices::calculateCallBlackAndScholes(S, K, vol, R, T));
	} else {
		this->setBlackAndScholes(CQuantModelServices::calculatePutBlackAndScholes(S, K, vol, R, T));
	}
}

double CQuantModelServices::calculateCallBlackAndScholes(double S, double K, double volatility, double freeRiskRate, double maturity)
{
	double d1 = (log( S / K ) + (freeRiskRate + pow(volatility, 2) / 2) * maturity/48) / (volatility * sqrt(maturity/48));
	double d2 = d1 - volatility * sqrt(maturity/48);

	return S * N(d1) * exp(-freeRiskRate * maturity/48) - K * exp(- freeRiskRate * maturity/48) * N(d2);
}

double CQuantModelServices::calculatePutBlackAndScholes(double S, double K, double volatility, double freeRiskRate, double maturity)
{
	double d1 = (log( S / K ) + (freeRiskRate + pow(volatility, 2) / 2) * maturity/48) / (volatility * sqrt(maturity/48));
	double d2 = d1 - volatility * sqrt(maturity/48);

	return K * exp(- freeRiskRate * maturity/48) * N(-d2) - S * N(-d1) * exp(-freeRiskRate * maturity/48);
}



// Delta
void CQuantModelServices::calculateDelta(double S, double K, double vol, double R, double T, bool isCall)
{
	if(isCall) {
		this->setDelta(CQuantModelServices::calculateCallDelta(S, K, vol, R, T));
	} else {
		this->setDelta(CQuantModelServices::calculatePutDelta(S, K, vol, R, T));
	}
}

double CQuantModelServices::calculateCallDelta(double S, double K, double vol, double R, double T)
{
	double d1 = (log( S / K ) + (R + pow(vol, 2) / 2) * T/48) / (vol * sqrt(T/48));
	return exp(-R*T/48) * N(d1);
}

double CQuantModelServices::calculatePutDelta(double S, double K, double vol, double R, double T)
{
	double d1 = (log( S / K ) + (R + pow(vol, 2) / 2) * T/48) / (vol * sqrt(T/48));
	return exp(-R*T/48) * (N(d1) - 1.0);
}



// Gamma
void CQuantModelServices::calculateGamma(double S, double K, double vol, double R, double T, bool isCall)
{
	double d1 = (log( S / K ) + (R + pow(vol, 2) / 2) * T/48) / (vol * sqrt(T/48));
	this->setGamma(n(d1) / (S * vol * sqrt(T/48)));
}



// Théta
void CQuantModelServices::calculateTheta(double S, double K, double vol, double R, double T, bool isCall)
{
	if(isCall) {
		this->setTheta(CQuantModelServices::calculateCallTheta(S, K, vol, R, T));
	} else {
		this->setTheta(CQuantModelServices::calculatePutTheta(S, K, vol, R, T));
	}
}

double CQuantModelServices::calculateCallTheta(double S, double K, double vol, double R, double T)
{
	double d1 = (log( S / K ) + (R + pow(vol, 2) / 2) * T/48) / (vol * sqrt(T/48));
	double d2 = d1 - vol * sqrt(T/48);

	return (- S * n(d1) * vol)/2*sqrt(T/48) - R * K *exp(-R*T/48) * N(d2);
}

double CQuantModelServices::calculatePutTheta(double S, double K, double vol, double R, double T)
{
	double d1 = (log( S / K ) + (R + pow(vol, 2) / 2) * T/48) / (vol * sqrt(T/48));
	double d2 = d1 - vol * sqrt(T/48);

	return (- S * n(d1) * vol)/2*sqrt(T/48) + R * K *exp(-R*T/48) * N(-d2);
}


// Rho
void CQuantModelServices::calculateRho(double S, double K, double vol, double R, double T, bool isCall)
{
	if(isCall) {
		this->setRho(CQuantModelServices::calculateCallRho(S, K, vol, R, T));
	} else {
		this->setRho(CQuantModelServices::calculatePutRho(S, K, vol, R, T));
	}
}

double CQuantModelServices::calculateCallRho(double S, double K, double vol, double R, double T)
{
	double d1 = (log( S / K ) + (R + pow(vol, 2) / 2) * T/48) / (vol * sqrt(T/48));
	double d2 = d1 - vol * sqrt(T/48);
	
	return K * exp(-R * T/48) * N(d2);
}

double CQuantModelServices::calculatePutRho(double S, double K, double vol, double R, double T)
{
	double d1 = (log( S / K ) + (R + pow(vol, 2) / 2) * T/48) / (vol * sqrt(T/48));
	double d2 = d1 - vol * sqrt(T/48);

	return - K * exp(-R * T/48) * N(-d2);
}


// Vega
void CQuantModelServices::calculateVega(double S, double K, double vol, double R, double T, bool isCall)
{
	double d1 = (log( S / K ) + (R + pow(vol, 2) / 2) * T/48) / (vol * sqrt(T/48));
	this->setVega(S * sqrt(T/48) * n(d1));
}




// Extern QuantModel getter function
extern "C" QUANT_MODEL_SERVICES_API IQuantModel* __stdcall GetQuantModel()
{
	IQuantModel *qm = new CQuantModelServices();
	return qm;
}
