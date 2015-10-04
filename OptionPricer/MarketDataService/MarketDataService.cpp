// MarketDateService.cpp : Defines the exported functions for the DLL application.

#include "stdafx.h"

#include "MarketDataService.h"

// TODO prepared statements

void EquityPrice::calculateVol() 
{
	MYSQL mysql;
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");

	if(mysql_real_connect(&mysql,"localhost","root","","marketdata",0,NULL,0)) {
		char requete[150] = "";

		sprintf_s(requete, "SELECT min(price), max(price), avg(price) FROM market_data WHERE symbol = '%s' ", this->getMnemo().c_str());

		mysql_query(&mysql, requete);

		MYSQL_RES *result = NULL;
		MYSQL_ROW row;

		result = mysql_store_result(&mysql);
		row = mysql_fetch_row(result);

		// calculating historical vol and set this one.
		this->setVol((stod(row[1]) - stod(row[0])) / stod(row[2]));

		mysql_close(&mysql);

	} else {
		printf("Une erreur s'est produite lors de la connexion à la BDD!");
		this->setVol(-1.0);
	}
}

void EquityPrice::calculateSpot() {
	
	MYSQL mysql;
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");

	if(mysql_real_connect(&mysql,"localhost","root","","marketdata",0,NULL,0)) {
		char requete[150] = "";

		sprintf_s(requete, "SELECT price FROM `market_data` WHERE symbol = '%s' and timestamp = (select max(timestamp) from market_data where symbol = '%s')", this->getMnemo().c_str(), this->getMnemo().c_str());

		mysql_query(&mysql, requete);

		MYSQL_RES *result = NULL;
		MYSQL_ROW row;

		result = mysql_store_result(&mysql);
		row = mysql_fetch_row(result);

		this->setSpot(stod(row[0]));

		mysql_close(&mysql);

	} else {
		printf("Une erreur s'est produite lors de la connexion à la BDD!");
		this->setSpot(-1.0);
	}
}

void EquityPrice::calculateTaux() 
{
	MYSQL mysql;
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "option");

	if(mysql_real_connect(&mysql,"localhost","root","","marketdata",0,NULL,0)) {
		char requete[300] = "";

		sprintf_s(requete, "SELECT valeur FROM `taux_euribor` WHERE date = (select max(date) from taux_euribor where periode = '%s') and periode = '%s'", this->getPeriode().c_str(), this->getPeriode().c_str());

		mysql_query(&mysql, requete);

		MYSQL_RES *result = NULL;
		MYSQL_ROW row;

		result = mysql_store_result(&mysql);
		row = mysql_fetch_row(result);

		this->setTaux(stod(row[0]));

		mysql_close(&mysql);

	} else {
		printf("Une erreur s'est produite lors de la connexion à la BDD!");
		this->setTaux(-1.0);
	}
}

// Extern EquityPrice getter function
extern "C" MARKET_DATA_SERVICES_API IMarketData* __stdcall GetEquityPrice(LPCSTR mnemo, LPCSTR periode) {
	IMarketData *ep = new EquityPrice(mnemo, periode);
	return ep;
}


