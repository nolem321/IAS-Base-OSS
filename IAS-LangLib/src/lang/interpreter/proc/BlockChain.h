/*
 * File: IAS-LangLib/src/lang/interpreter/proc/BlockChain.h
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
#ifndef _IAS_AS_Lang_Interpreter_Proc_BLOCKCHAIN_H_
#define _IAS_AS_Lang_Interpreter_Proc_BLOCKCHAIN_H_

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>
#include<vector>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe{
namespace Dec{
class DeclarationBlockFeature;
}
}
namespace Proc {
/*************************************************************************/
/** The class. */
 class BlockChain {
public:

	virtual ~BlockChain() throw();

	void findVariable(const String& strVariable,
						int& iOffset,
						const DM::Property* &pRefProperty,
						const DM::ComplexType* &pRefType);

	void pushBlock(const Exe::Dec::DeclarationBlockFeature *pBlock);
	void popBlock();

protected:
	BlockChain();

	typedef std::vector<const Exe::Dec::DeclarationBlockFeature*> BlockChainList;
	BlockChainList                                    lstBlockChain;

public:
	/*************************************************************************/
	struct AutoPopUp {
		AutoPopUp(BlockChain *pBlockChain, Exe::Dec::DeclarationBlockFeature *pBlock):pBlockChain(pBlockChain){
			pBlockChain->pushBlock(pBlock);
		};

		~AutoPopUp() { pBlockChain->popBlock(); };
	private:
		BlockChain *pBlockChain;
	};
	friend class ::IAS::Factory<BlockChain>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Interpreter_Proc_BLOCKCHAIN_H_ */
