//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef SCOPED_SET_RETURN_VALUE_H__QM
#define SCOPED_SET_RETURN_VALUE_H__QM

class ScopedSetReturnValue
{
public:
	ScopedSetReturnValue(ModAssert::Response response)
	{
		oldResponse = ModAssertTestHandler::GetReturnValue();
		ModAssertTestHandler::SetReturnValue(response);
	}
	~ScopedSetReturnValue()
	{
		ModAssertTestHandler::SetReturnValue(oldResponse);
	}
private:
	ModAssert::Response oldResponse;
};

#endif // #ifndef SCOPED_SET_RETURN_VALUE_H__QM













