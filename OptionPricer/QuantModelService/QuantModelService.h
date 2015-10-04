#ifdef QUANTMODELSERVICE_EXPORTS
#define QUANT_MODEL_SERVICES_API __declspec(dllexport)
#else
#define QUANT_MODEL_SERVICES_API __declspec(dllimport)
#endif

#ifndef QUANT_MODEL_SERVICES_H_
#define QUANT_MODEL_SERVICES_H_

#include <cmath>

struct IQuantModel {
public:
	// Constructeurs
	IQuantModel() {}
	
	// Destructeur
	virtual ~IQuantModel() {}

	// Méthodes
	virtual void calculateBlackAndScholes(double S, double K, double vol, double R, double T, bool isCall) = 0;
	virtual void calculateDelta(double S, double K, double vol, double R, double T, bool isCall) = 0;
	virtual void calculateGamma(double S, double K, double vol, double R, double T, bool isCall) = 0;
	virtual void calculateTheta(double S, double K, double vol, double R, double T, bool isCall) = 0;
	virtual void calculateRho(double S, double K, double vol, double R, double T, bool isCall) = 0;
	virtual void calculateVega(double S, double K, double vol, double R, double T, bool isCall) = 0;
};


class CQuantModelServices : public IQuantModel 
{

	double delta;
	double gamma;
	double theta;
	double rho;
	double vega;
	double blackAndScholes;


	// private methods	
	double calculateCallBlackAndScholes(double S, double K, double volatility, double freeRiskRate, double maturity);
	double calculatePutBlackAndScholes(double S, double K, double volatiliy, double freeRiskRate, double maturity);

	double calculateCallDelta(double S, double K, double vol, double R, double T);
	double calculatePutDelta(double S, double K, double vol, double R, double T);

	double calculateCallTheta(double S, double K, double vol, double R, double T);
	double calculatePutTheta(double S, double K, double vol, double R, double T);

	double calculateCallRho(double S, double K, double vol, double R, double T);
	double calculatePutRho(double S, double K, double vol, double R, double T);


	// private setters
	void setDelta(double d) {
		delta = d;
	}

	void setGamma(double g) {
		gamma = g;
	}

	void setTheta(double t) {
		theta = t;
	}

	void setRho(double r) {
		rho = r;
	}

	void setVega(double v) {
		vega = v;
	}

	void setBlackAndScholes(double bas) {
		blackAndScholes = bas;
	}


public:
	CQuantModelServices() {this->delta = 0.0; this->gamma = 0.0; this->theta = 0.0; this->rho = 0.0; this->vega = 0.0; this->blackAndScholes = 0.0;}
	virtual ~CQuantModelServices() {}

	// Implement pure virtual interface
	virtual void calculateBlackAndScholes(double S, double K, double vol, double R, double T, bool isCall);
	virtual void calculateDelta(double S, double K, double vol, double R, double T, bool isCall);
	virtual void calculateGamma(double S, double K, double vol, double R, double T, bool isCall);
	virtual void calculateTheta(double S, double K, double vol, double R, double T, bool isCall);
	virtual void calculateRho(double S, double K, double vol, double R, double T, bool isCall);
	virtual void calculateVega(double S, double K, double vol, double R, double T, bool isCall);

	// public getters
	double getDelta() {
		return delta;
	}

	double getGamma() {
		return gamma;
	}

	double getTheta() {
		return theta;
	}

	double getRho() {
		return rho;
	}
	
	double getVega() {
		return vega;
	}
	
	double getBlackAndScholes() {
		return blackAndScholes;
	}
	
};

extern "C" QUANT_MODEL_SERVICES_API IQuantModel* __stdcall GetQuantModel();

// Gaussian (normal) distribution function
double n(double x);

// The approximation to the cumulative normal distribution function
double N(double x);

#endif