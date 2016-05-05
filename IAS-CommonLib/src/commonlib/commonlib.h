/*
 * File: IAS-CommonLib/src/commonlib/commonlib.h
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
/* IAS_COPYRIGHT */

/* ChangeLog:
 *
 */


#ifndef IAS_COMMONLIB_H_
#define IAS_COMMONLIB_H_

#include "commonlib/types.h"
#include "commonlib/config.h"

#include "commonlib/logger/logger.h"
#include "commonlib/logger/TracerStats.h"

#include "commonlib/memory/memory.h"

#include "commonlib/memory/ma/Allocator.h"
#include "commonlib/memory/ma/ExplicitAllocatorFactory.h"

#include "commonlib/memory/mm/MemoryManager.h"
#include "commonlib/memory/mm/RegionMemoryManager.h"
#include "commonlib/memory/mm/PowerOfTwoMemoryManager.h"

#include "commonlib/containers/PtrVector.h"
#include "commonlib/containers/HashMapOfPointers.h"
#include "commonlib/containers/HashMapStringToPointer.h"
#include "commonlib/containers/HashMapStringPairToPointer.h"
#include "commonlib/containers/FolderBasedContent.h"

#include "commonlib/memory/sharable/SharedContent.h"

#include "commonlib/exception/Exception.h"
#include "commonlib/exception/DataException.h"
#include "commonlib/exception/EndOfDataException.h"
#include "commonlib/exception/InternalException.h"
#include "commonlib/exception/MemoryException.h"
#include "commonlib/exception/SystemException.h"
#include "commonlib/exception/ConfigException.h"
#include "commonlib/exception/ItemNotFoundException.h"
#include "commonlib/exception/AlreadyExists.h"
#include "commonlib/exception/BadUsageException.h"

#include "commonlib/configfile/Properties.h"
#include "commonlib/configfile/PropertiesProvider.h"
#include "commonlib/configfile/PropertiesProviderFromFile.h"
#include "commonlib/configfile/PropertiesProviderFromFileByEnvVar.h"

#include "commonlib/threads/Thread.h"
#include "commonlib/threads/Runnable.h"
#include "commonlib/threads/Mutex.h"
#include "commonlib/threads/Condition.h"
#include "commonlib/threads/BackgroundJob.h"
#include "commonlib/threads/BackgroundJobsExecutor.h"

#include "commonlib/time/Timestamp.h"
#include "commonlib/time/Time.h"
#include "commonlib/time/DateTime.h"
#include "commonlib/time/Date.h"

#include "commonlib/tools/Buffer.h"
#include "commonlib/tools/MiscTools.h"
#include "commonlib/tools/ProgramParameters.h"
#include "commonlib/tools/TypeTools.h"
#include "commonlib/tools/EnvTools.h"
#include "commonlib/tools/Template.h"
#include "commonlib/tools/SerializationHelper.h"
#include "commonlib/tools/PrimeNumbers.h"

#include "commonlib/caches/SimpleCache.h"
#include "commonlib/caches/SimpleCacheSynchronized.h"

#include "commonlib/streams/InputFile.h"
#include "commonlib/streams/InputFileTail.h"
#include "commonlib/streams/OutputFile.h"
#include "commonlib/streams/Directory.h"

#include "commonlib/geometry/Geometry.h"

#include "commonlib/time/TimeSamplesRegister.h"

#include "commonlib/types/BitMap.h"

#include "commonlib/sys/Signal.h"
#include "commonlib/sys/DynamicLibrary.h"
#include "commonlib/sys/DynamicLibraryStore.h"
#include "commonlib/sys/proc/Process.h"
#include "commonlib/sys/proc/Executor.h"

#include "commonlib/callbacks/CallbacksRegister.h"
#include "commonlib/testcase/TestUnit.h"
#include "commonlib/testcase/TestSuite.h"

#include "commonlib/misc/InstanceFeature.h"

#include "commonlib/ui/UserMessage.h"
#include "commonlib/ui/MessageCatalog.h"

#include "commonlib/net/net.h"

#include "net/async/InputDataPump.h"
#include "net/async/OutputDataPump.h"

#ifndef NULL
#define NULL ((void*)0)
#endif

#endif /*COMMONLIB_H_*/
