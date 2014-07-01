//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/logger.hpp"
#include "modassert/handler.hpp"

#ifndef STUB_LOGGER_H__QM
#define STUB_LOGGER_H__QM

class StubLogger: public ModAssert::Logger
{
public:
	StubLogger(bool add=false): called(false)
	{
		if (add)
			ModAssert::AddLogger(this);
	}
	~StubLogger()
	{
	}

	virtual void OnAssert(const ModAssert::Properties &,
			const ModAssert::Result &) const
	{
		called = true;
	}

	virtual void AddMessage(const RichBool::detail::String &) const
	{
	}

	bool CheckCalled()
	{
		bool rv = called;
		called = false;
		return rv;
	}

	void Clear()
	{
		called = false;
	}

protected:
	mutable bool called;
};

class NoMessagesLogger: public ModAssert::Logger
{
	ModAssert::Logger *logger;
public:
	NoMessagesLogger(ModAssert::Logger &logger_): logger(&logger_) {}

	virtual void OnAssert(const ModAssert::Properties &properties,
			const ModAssert::Result &assertionResult) const
	{
		logger->OnAssert(properties, assertionResult);
	}

	virtual void AddMessage(const RichBool::detail::String &) const
	{
		// ignored !!
	}
};

#endif // #ifndef STUB_LOGGER_H__QM
