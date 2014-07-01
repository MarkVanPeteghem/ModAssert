ModAssert
=========

In C and C++ the traditional assert function is used to tell the user
that something unexpected happened, that might cause the program to
fail. Macros were written in other packages to extend this mechanism,
like ASSERT_EQUAL(a,b), ASSERT_NOT_EQUAL(a,b), ASSERT_LESS(a,b), ...,
to give a short explanation like "lefthand is <9>, righthand is <10>".
However, if we want similar VERIFY macros which still evaluate their
arguments in non-debug mode, we get VERIFY_EQUAL, VERIFY_NOT_EQUAL,
..., or macros that add a message like ASSERT_EQUAL_MSG,
ASSERT_NOT_EQUAL_MSG, ..., so we could end up with hundreds of macros.
Clearly this is not practical.

The Modular Assertion macros solve this problem. They cannot only have
a simple boolean expression as their argument, but also a Rich
Boolean, that checks a condition, and if it fails, it holds an
analysis of why it fails. E.g., the Rich Boolean rbEQUAL(a,b) could
hold the information "`a':<1> == `b':<2> nok" after a failed
assertion. The assertion macros themselves only vary in their extra
arguments (expressions, messages, level, group, optional action). This
package has 128 different types of assertion macros (MOD_ASSERT,
MOD_VERIFY, MOD_CHECK, MOD_ASSERT_P, ...). So one could write
MOD_ASSERT(rbEQUAL(a,b)), MOD_VERIFY(rbLESS(foo(), 10)),
MOD_ASSERT_PG(a, ModAssert::Fatal, rbEQUAL(bar(a),b)) etc. 128 may
seem like too much, but there are 8 basic assertions, that each have 4
optional attributes (making 16 variations), so they are easy to learn.

The macros allow an arbitray number of expressions to be evaluated and
shown when an assertion or check fails. A level can be assigned to
each assertion (Info, Warning, Error or Fatal). Groups can be defined
and assigned to assertions. An assertion can have an optional action.
Displaying and logging of assertions can each be controlled at runtime
per case, level, group, source code file or all at once. This can also
be done at compiletime per level, group, source code file or all at
once, to reduce the size of the executable.

Failed assertions are processed by objects that implement a given
interface, so handling of assertions is pluggable. There is a
distinction between objects that inform the user and ask what action
to undertake, and objects that simply log the information. Three
implementations of the first are provided, one for console
applications, one for Win32 and one for wxWidgets. Two implementations
of the second are provided, and another specific for wxWidgets. You
can add a filter to a responder or a logger, to filter out certain
assertions.

ModAssert makes a distinction between assertions and checks.
Assertions are meant for detecting bugs, while checks are meant for
detecting other errors, e.g. invalid input by the user. Checks have a
failure action, that is executed if the condition fails. Loggers and
responders are aware of this distinction through an argument.

ModAssert doesn't have compile time assertions, because that is an
entirely different kind of assertion.

It is released under the wxWindows Licence, so it can be used in
both open source and commercial applications, without requiring
provision of source, or runtime acknowledgements.
