//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef DemoWxApp_H
#define DemoWxApp_H

// Define a new application type, each program should derive a class from wxApp
class DemoWxApp : public wxApp
{
public:
    DemoWxApp();
    virtual ~DemoWxApp();

    // override base class virtuals
    // ----------------------------

    // this one is called on application startup and is a good place for the app
    // initialization (doing it here and not in the ctor allows to have an error
    // return: if OnInit() returns false, the application terminates)
    virtual bool OnInit();
	virtual int OnExit();

	virtual void OnAssertFailure(const wxChar *file, int line, const char *func,
			const wxChar *cond, const wxChar *msg);
};

DECLARE_APP(DemoWxApp)

#endif // DemoWxApp_H
