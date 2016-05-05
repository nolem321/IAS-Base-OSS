/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCFolderBasedContent.cpp
 * 
 * Copyright (C) 2015, Albert Krzymowski
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "commonlib/commonlib.h"

#include "TCFolderBasedContent.h"

namespace IAS{
namespace TCT{

/*************************************************************************/
TCFolderBasedContent::TCFolderBasedContent(TestSuite* pTestSuite):theTestRunner(this){

	IAS_TRACER;
	theTestRunner.addCase("test01",&::IAS::TCT::TCFolderBasedContent::test01);
	theTestRunner.addCase("test02",&::IAS::TCT::TCFolderBasedContent::test02);
	TestUnit::init("TCFolderBasedContent",&theTestRunner,pTestSuite);
}
/*************************************************************************/
TCFolderBasedContent::~TCFolderBasedContent() throw(){
	IAS_TRACER;
}
/*************************************************************************/
TCFolderBasedContent::Content::Content(const String& i):i(i){}
/*************************************************************************/
void TCFolderBasedContent::printFolder(FoldersType* pFolder, const String& strPrefix){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pFolder);

	const FoldersType::FoldersMap& hmFolders = pFolder->getFolders();
	const FoldersType::ContentMap& hmContent = pFolder->getContent();

	std::cerr<<strPrefix<<":("<<hmFolders.size()<<","<<hmContent.size()<<")"<<std::endl;

	for(FoldersType::FoldersMap::const_iterator it= hmFolders.begin();
		it != hmFolders.end();
		it++){
		String strNewPrefix(strPrefix);
		strNewPrefix+=FoldersType::CDelimiter;
		strNewPrefix+=it->first;
		printFolder(it->second,strNewPrefix);
	}


	for(FoldersType::ContentMap::const_iterator it= hmContent.begin();
		it != hmContent.end();
		it++){
		std::cerr<<strPrefix<<FoldersType::CDelimiter<<it->first<<"="<<it->second->i<<std::endl;
		}

}
/*************************************************************************/
void TCFolderBasedContent::test01(){
	IAS_TRACER;

	IAS_DFT_FACTORY<FoldersType>::PtrHolder ptrRootFolder(IAS_DFT_FACTORY<FoldersType>::Create());

	ptrRootFolder->createFolder("Documents.Pictures")->createFolder("Holidays");

	try{
		ptrRootFolder->createFolder("Documents.Music");
		IAS_THROW(InternalException("test01 failed:1"));
	}catch(BadUsageException& e){}

	ptrRootFolder->createFolder("Documents.Music.Jazz",true)->addContent("Coltrane",IAS_DFT_FACTORY<Content>::Create("John"));
	ptrRootFolder->createFolder("Documents.Music.Rock",true)->addContent("Zappa",IAS_DFT_FACTORY<Content>::Create("Frank"));
	printFolder(ptrRootFolder);

	ptrRootFolder->addContent("Documents.Music.Rock.Buckethead",IAS_DFT_FACTORY<Content>::Create("Mask"));
	ptrRootFolder->addContent("hidden files",IAS_DFT_FACTORY<Content>::Create(":)"));

	printFolder(ptrRootFolder);

	Content *pContent;

	if(!ptrRootFolder->getContent("Documents.Music.Rock.Buckethead",pContent))
		IAS_THROW(InternalException("test01 failed:2"));

	ptrRootFolder->removeContent("Documents.Music.Rock.Buckethead");

	try{
		ptrRootFolder->getContent("Documents.Music.Rock.Buckethead");
		IAS_THROW(InternalException("test01 failed:3"));
	}catch(ItemNotFoundException& e){}

	ptrRootFolder->removeFolder("Documents.Music");

	try{
		ptrRootFolder->getContent("Documents.Music");
		IAS_THROW(InternalException("test01 failed:4"));
	}catch(ItemNotFoundException& e){}


	printFolder(ptrRootFolder);
}
/*************************************************************************/
void TCFolderBasedContent::test02(){
	IAS_TRACER;

	IAS_DFT_FACTORY<FoldersType>::PtrHolder ptrRootFolder(IAS_DFT_FACTORY<FoldersType>::Create());


	ptrRootFolder->createFolder("Documents.Pictures")->createFolder("Holidays");

	try{
		ptrRootFolder->createFolder("Documents.Music");
		IAS_THROW(InternalException("test01 failed:1"));
	}catch(BadUsageException& e){}

	ptrRootFolder->createFolder("Documents.Music.Jazz",true)->addContent("Coltrane",IAS_DFT_FACTORY<Content>::Create("John"));
	ptrRootFolder->createFolder("Documents.Music.Rock",true)->addContent("Zappa",IAS_DFT_FACTORY<Content>::Create("Frank"));
	printFolder(ptrRootFolder);

	ptrRootFolder->addContent("Documents.Music.Rock.Buckethead",IAS_DFT_FACTORY<Content>::Create("Mask"));
	ptrRootFolder->addContent("hidden files",IAS_DFT_FACTORY<Content>::Create(":)"));

	printFolder(ptrRootFolder);

	IAS_DFT_FACTORY<FoldersType::Index>::PtrHolder ptrIndex(ptrRootFolder->createIndex());

	std::cerr<<"Index:"<<ptrIndex->size()<<std::endl;
	for(FoldersType::Index::const_iterator it = ptrIndex->begin();
		it != ptrIndex->end();
		it++){
		std::cerr<<it->first<<"="<<it->second->i<<std::endl;
	}

}
/*************************************************************************/

} /* namespace TCT */
} /* namespace IAS */
