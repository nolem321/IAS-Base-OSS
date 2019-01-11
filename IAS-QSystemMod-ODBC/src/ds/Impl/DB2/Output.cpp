/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-DB2/src/ds/Impl/DB2/Output.cpp 
 *
 * Licensed under the Invenire Aude Commercial License (the "License");
 * you may not use this file except in compliance with the License. 
 * You may find the license terms and conditions in the LICENSE.txt file.
 * or at http://www.invenireaude.com/licenses/license.txt
 * 
 * This file and any derived form, including but not limited to object
 * executable, represents the Confidential Materials.
 * 
 */
#include "Output.h"


namespace IAS {
namespace DS {
namespace Impl {
namespace DB2 {

/*************************************************************************/
Output::Output(Statement& statement):Input(statement){
	IAS_TRACER;
}
/*************************************************************************/
Output::~Output() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Output::addOutput(const String& strTag, DM::Tools::Setter *pSetter){
	IAS_TRACER;

	tabOutputHolders.push_back(Holder::Base::Create(&statement,pSetter,false));
	tabOutputHolders.back()->bind(iNum++,SQL_PARAM_OUTPUT);
	//tabOutputHolders.back()->define(tabOutputHolders.size()+tabInputOutputHolders.size());

}
/*************************************************************************/
void Output::addInputOutput(const String& strTag, DM::Tools::Setter *pSetter){
	IAS_TRACER;

	tabInputOutputHolders.push_back(Holder::Base::Create(&statement,pSetter,false));
	tabInputOutputHolders.back()->bind(iNum++,SQL_PARAM_INPUT_OUTPUT);
	//tabInputOutputHolders.back()->define(tabOutputHolders.size()+tabInputOutputHolders.size());

}
/*************************************************************************/
void Output::feedInputs(DM::DataObjectPtr& dm){
	IAS_TRACER;

	for(Holder::Base::Table::iterator it=tabHolders.begin();
		it != tabHolders.end(); it++){

		(*it)->feed(dm);
	}

	for(Holder::Base::Table::iterator it=tabInputOutputHolders.begin();
		it != tabInputOutputHolders.end(); it++){

		(*it)->feed(dm);
	}

}
/*************************************************************************/
void Output::fetch(DM::DataObjectPtr& dm){
	IAS_TRACER;


	for(Holder::Base::Table::iterator it=tabOutputHolders.begin();
		it != tabOutputHolders.end(); it++){

		(*it)->fetch(dm);
	}

	for(Holder::Base::Table::iterator it=tabInputOutputHolders.begin();
		it != tabInputOutputHolders.end(); it++){

		(*it)->fetch(dm);
	}

}
/*************************************************************************/
}
}
}
}
