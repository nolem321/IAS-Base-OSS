/*
 * File: IAS-CommonLib/src/commonlib/containers/FolderBasedContent.h
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
/* ChangeLog:
 * 
 */

#ifndef _IAS_FolderBasedContent_H_
#define _IAS_FolderBasedContent_H_

#include "HashMapStringToPointer.h"
#include "commonlib/types.h"
#include "commonlib/memory/memory.h"
#include "commonlib/tools/TypeTools.h"
#include "commonlib/exception/ItemNotFoundException.h"
#include "commonlib/exception/BadUsageException.h"

#include <stack>

namespace IAS {

/*************************************************************************************/

template<class T, char cDelimiter='/'>
class FolderBasedContent {
public:

	static const char CDelimiter = cDelimiter;

	FolderBasedContent() {};
	virtual ~FolderBasedContent() {};

	typedef String Path;
	typedef StringList PathList;
	typedef T          ContentType;
	typedef HashMapStringToPointer<FolderBasedContent> FoldersMap;
	typedef HashMapWithStringKey<T*> Index;

	/*************************************************************************************/
	FolderBasedContent* getFolder(const Path& aPath) const {
		IAS_TRACER;
		FolderBasedContent *pOutput;

		bool bResult = getFolder(aPath, pOutput);

		if (!bResult)
			IAS_THROW(ItemNotFoundException(String("getFolder: ") += aPath));

		return pOutput;
	}

	/*************************************************************************************/
	bool getFolder(const Path& aPath, FolderBasedContent* &refPointer) const {
		IAS_TRACER;

		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(), "looking for ["<<aPath<<"]");

		StringList lstPath;

		TypeTools::Tokenize(aPath, lstPath, cDelimiter);

		refPointer = this;

		StringList::const_iterator it = lstPath.begin();

		while (it != lstPath.end()) {
			if (!refPointer->getFolderAtThisLevel(*it++, refPointer))
				return false;
		}

		return true;
	}
	/*************************************************************************************/
	FolderBasedContent* createFolder(const Path& aPath, bool bIgnoreIfExists = false){
		IAS_TRACER;

		StringList lstPath;

		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(), "creating ["<<aPath<<"]:"<<bIgnoreIfExists);

		TypeTools::Tokenize(aPath, lstPath, cDelimiter);

		StringList::const_iterator it = lstPath.begin();
		FolderBasedContent *pNewFolder = this;

		while (it != lstPath.end()) {
			if (pNewFolder->getFolderAtThisLevel(*it, pNewFolder)){
				if(!bIgnoreIfExists)
					IAS_THROW(BadUsageException(String("Already exists: ")+=aPath));
			}else{
				pNewFolder=pNewFolder->createSubFolderAtThisLevel(*it);
			}
			it++;
		}


		return pNewFolder;
	}
	/*************************************************************************************/
	void removeFolder(const Path& aPath,bool bIgnoreIfNotFound = false){
		IAS_TRACER;

		FolderBasedContent *pParent = this;
		String strChild;

		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(), "removing ["<<aPath<<"]:"<<bIgnoreIfNotFound);

		if(!getParentFolder(aPath, pParent, strChild)){

			if(!bIgnoreIfNotFound){
				IAS_THROW(ItemNotFoundException(String("Folder not found: ")+=aPath));
			}else{
				return;
			}

		}

		if(pParent->hmFolders.count(strChild)==0)
			if(!bIgnoreIfNotFound)
				IAS_THROW(ItemNotFoundException(String("Folder not found: ")+=aPath));

		pParent->hmFolders.erase(strChild);
	}
	/*************************************************************************************/
	void removeContent(const Path& aPath,bool bIgnoreIfNotFound = false){
		IAS_TRACER;

		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(), "removing ["<<aPath<<"]:"<<bIgnoreIfNotFound);

		FolderBasedContent *pParent = this;
		String strChild;

		if(!getParentFolder(aPath, pParent, strChild))
			if(!bIgnoreIfNotFound)
				IAS_THROW(ItemNotFoundException(String("Folder not found: ")+=aPath));

		if(pParent->hmContent.count(strChild)==0)
			if(!bIgnoreIfNotFound)
				IAS_THROW(ItemNotFoundException(String("Folder not found: ")+=aPath));

		pParent->hmContent.erase(strChild);
	}

	/*************************************************************************************/
	const FoldersMap& getFolders()const{
		return hmFolders;
	}
	/*************************************************************************************/
	typedef HashMapStringToPointer<T> ContentMap;

	const ContentMap& getContent()const{
		return hmContent;
	}

	/*************************************************************************************/
	void addContent(const Path& aPath,
					T* pContent,
					bool bCreatePathIfNeeded = false){
		IAS_TRACER;

		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(), "adding ["<<aPath<<"]:"<<bCreatePathIfNeeded);

		FolderBasedContent *pParent = this;

		String strChild;
		if(!getParentFolder(aPath,pParent,strChild,bCreatePathIfNeeded))
			IAS_THROW(ItemNotFoundException(String("Folder not found for: ")+=aPath));

		pParent->hmContent[strChild]=pContent;

	};
	/*************************************************************************************/
	bool getContent(const Path& aPath, const T*& refOutput)const{
		IAS_TRACER;

		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(), "getting ["<<aPath<<"]");


		const FolderBasedContent *pParent = this;
		String strChild;

		if(!getParentFolder(aPath, pParent, strChild))
			return false;

		if(pParent->hmContent.count(strChild)==0)
			return false;

		refOutput=pParent->hmContent.at(strChild);

		return true;
	};

	/*************************************************************************************/
	bool getContent(const Path& aPath,  T*& refOutput){
		return static_cast<const FolderBasedContent<T,cDelimiter> *>(this)->
				getContent(aPath, const_cast< const T* &>(refOutput));
	}
	/*************************************************************************************/
	const T* getContent(const Path& aPath)const{
		IAS_TRACER;
		const T *pOutput;

		bool bResult = getContent(aPath, pOutput);

		if (!bResult)
			IAS_THROW(ItemNotFoundException(String("getContent:") += aPath));

		return pOutput;
	};
	/*************************************************************************************/
	T* getContent(const Path& aPath){
		return const_cast< T* >(static_cast<const FolderBasedContent<T,cDelimiter> *>(this)->
				getContent(aPath));
	}

	/*************************************************************************************/
	bool getContent(const PathList& lstPath, const String& strName, const T*& refOutput)const{
		IAS_TRACER;

		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(), "lstPath.size()="<<lstPath.size());

		for(PathList::const_iterator it=lstPath.begin();
			it != lstPath.end();
			it++){

			if(getContent((*it)+cDelimiter+strName,refOutput))
				return true;
		}

		return false;
	}
	/*************************************************************************************/
	bool getContent(const PathList& lstPath, const String& strName, T*& refOutput){
		return static_cast<const FolderBasedContent<T,cDelimiter> *>(this)->
						getContent(lstPath, strName, const_cast< const T* &>(refOutput));
	}
	/*************************************************************************************/
	T* getContent(const PathList& lstPath, const String& strName)const{
			IAS_TRACER;
			T *pOutput;

			bool bResult = getContent(lstPath, strName, pOutput);

			if (!bResult)
				IAS_THROW(ItemNotFoundException(String("getContent (from a list)")));

			return pOutput;
		};
	/*************************************************************************************/
	T* getContent(const PathList& lstPath, const String& strName){
		return const_cast< T* >(static_cast<const FolderBasedContent<T,cDelimiter> *>(this)->
				getContent(lstPath,strName));
	}

	/************************************************************************************/
	Index* createIndex()const{
		IAS_TRACER;

		typename IAS_DFT_FACTORY<Index>::PtrHolder ptrIndex;

		ptrIndex= IAS_DFT_FACTORY<Index>::Create();

		fillIndex("",ptrIndex, this);
		return ptrIndex.pass();
	}
	/************************************************************************************/

	static FolderBasedContent* Create(){
		IAS_TRACER;
		typename IAS_DFT_FACTORY<FolderBasedContent>::PtrHolder ptrFolderBasedContent;

		ptrFolderBasedContent = IAS_DFT_FACTORY<FolderBasedContent>::Create();

		return ptrFolderBasedContent.pass();
	}

	/*************************************************************************************/

protected:
	FoldersMap hmFolders;
	ContentMap hmContent;

	/*************************************************************************************/
	bool getFolderAtThisLevel(const String& strFolder, const FolderBasedContent* &refPointer) const{
		IAS_TRACER;

		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(), "getting ["<<strFolder<<"]"<<hmFolders.count(strFolder));

		if(hmFolders.count(strFolder) == 0)
			return false;

		refPointer=hmFolders.at(strFolder);
		return true;
	}

	/*************************************************************************************/
	bool getFolderAtThisLevel(const String& strFolder, FolderBasedContent* &refPointer){
		IAS_TRACER;

		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(), "getting ["<<strFolder<<"]"<<hmFolders.count(strFolder));

		if(hmFolders.count(strFolder) == 0)
			return false;

		refPointer=hmFolders.at(strFolder);
		return true;
	}

	/*************************************************************************************/
	FolderBasedContent* createSubFolderAtThisLevel(const String& strFolder){
		IAS_TRACER;
		FolderBasedContent* pSubFolder = IAS_DFT_FACTORY<FolderBasedContent>::Create();
		hmFolders[strFolder]=pSubFolder;
		return pSubFolder;
	}
	/*************************************************************************************/


	bool getParentFolder(const Path& aPath, FolderBasedContent* &refPointer, String& strChild, bool bCreatePathIfNeeded=false) {
		IAS_TRACER;

		StringList lstPath;

		TypeTools::Tokenize(aPath, lstPath, cDelimiter);

		refPointer = this;

		StringList::const_iterator it = lstPath.begin();

		do {
			strChild = *it;

			if (++it != lstPath.end()) {

				if (!refPointer->getFolderAtThisLevel(strChild, refPointer))
					if (bCreatePathIfNeeded) {
						refPointer = refPointer->createSubFolderAtThisLevel(strChild);
					} else {
						return false;
					}

			}

		} while (it != lstPath.end());

		return true;
	}

	/*************************************************************************/

	bool getParentFolder(const Path& aPath, const FolderBasedContent* &refPointer, String& strChild) const {
			IAS_TRACER;

			StringList lstPath;

			TypeTools::Tokenize(aPath, lstPath, cDelimiter);

			refPointer = this;

			StringList::const_iterator it = lstPath.begin();

			do {
				strChild = *it;

				if (++it != lstPath.end()) {

					if (!refPointer->getFolderAtThisLevel(strChild, refPointer))
							return false;

				}

			} while (it != lstPath.end());

			return true;
		}

	/*************************************************************************/

	void fillIndex(const String& strPrefix, Index *pIndex, const FolderBasedContent<T, CDelimiter> *pFolder)const{
		IAS_TRACER;

		for(typename FoldersMap::const_iterator it=pFolder->hmFolders.begin();
			it != pFolder->hmFolders.end();
			it++){
				String strTmp(strPrefix);
				strTmp+=it->first;
				strTmp+=cDelimiter;
				fillIndex(strTmp,pIndex, it->second);
		}

		for(typename ContentMap::const_iterator it=pFolder->hmContent.begin();
			it != pFolder->hmContent.end();
			it++){
				String strTmp(strPrefix);
				strTmp+=it->first;
				(*pIndex)[strTmp]=it->second;
			}

	}

};

/*************************************************************************************/

};/* namespace IAS */

#endif /* _IAS_FolderBasedContent_H_ */
