#ifdef MARKETDATASERVICE_EXPORTS
#define MARKET_DATA_SERVICES_API __declspec(dllexport)
#else
#define MARKET_DATA_SERVICES_API __declspec(dllimport)
#endif

#ifndef MARKET_DATA_SERVICES_H_
#define MARKET_DATA_SERVICES_H_

#include <vector>
#include <string>

#include <ctime>
#include <mysql.h>

using namespace std;



struct IMarketData 
{

public:
	// Constructeurs
	IMarketData() {}
	IMarketData(string) {}

	// Destructeur
	virtual ~IMarketData() {}

	// Méthodes
	virtual void calculateVol() = 0;
	virtual void calculateTaux() = 0;
	virtual void calculateSpot() = 0;
};


class EquityPrice : public IMarketData
{
	string mnemo;
	double spot;
	double vol;
	double taux;
	string periode;
	

	// private setters
	void setMnemo(string m){
		mnemo = m;
	}

	void setSpot(double s){
		spot = s;
	}

	void setTaux(double t){
		taux = t;
	}

	void setVol(double v){
		vol = v;
	}

	void setPeriode(string p){
		periode = p;
	}

public:
	EquityPrice(){this->mnemo = ""; this->spot = 0.0; this->vol = 0.0; this->taux = 0.0;}
	EquityPrice(LPCSTR mnemo, LPCSTR periode){this->mnemo = mnemo; this->periode = periode; this->spot = 0.0; this->vol = 0.0; this->taux = 0.0;}
	virtual ~EquityPrice(){}

	// Implement pure virtual interface
	virtual void calculateVol();
	virtual void calculateTaux();
	virtual void calculateSpot();


	// public getters
	string getMnemo(){
		return mnemo;
	}

	double getSpot(){
		return spot;
	}

	double getTaux(){
		return taux;
	}

	double getVol(){
		return vol;
	}

	string getPeriode(){
		return periode;
	}

};

extern "C" 	MARKET_DATA_SERVICES_API IMarketData* _stdcall GetEquityPrice(LPCSTR mnemo, LPCSTR periode);

#endif