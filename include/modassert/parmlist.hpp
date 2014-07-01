//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef VALUE_LIST_H__QM
#define VALUE_LIST_H__QM

#include "richbool/portability.hpp"

namespace ModAssert
{
	class SubString
	{
	public:
		SubString(const char *b, const char *e):
			begin_(b), end_(e)
		{}
		SubString(const char *szText):
			begin_(szText), end_(szText)
		{
			while (*end_) ++end_;
		}

		SubString& operator=(const char *szText)
		{
			begin_ = end_ = szText;
			while (*end_) ++end_;
			return *this;
		}

		bool operator==(const SubString& str) const;

		const char* begin() const { return begin_; }
		const char* end() const { return end_; }
		size_t size() const { return end_-begin_; }

		operator RichBool::detail::String() const
		{
			return RichBool::detail::String(begin_, end_);
		}

		friend RB_CONVERSION_HEADER(SubString);
	private:
		const char *begin_, *end_;
	};

	class ParameterList
	{
	public:
		ParameterList();
		ParameterList(const char *expressions);
		virtual ~ParameterList();

		void AddCommaSeparatedList(const char *expressions);

		template<typename T>
		ParameterList& operator<<(const T &t)
		{
			Add(t);
			return *this;
		}

		template <class HoldReferences>
		ParameterList& AddParameters(const HoldReferences &hr)
		{
			hr.AddToParameterList(*this);
			return *this;
		}

		void AddMessage(const char *msg);

		virtual ParameterList* clone() const;

		enum MessageType { eMessage, eValue };

		class Message
		{
		public:
			Message(const char *str):
				message(str), next(0) {}
			Message(const char *begin, const char *end):
				message(begin, end), next(0) {}
			Message(const Message &msg):
				message(msg.message), next(0) {}

			virtual ~Message()
			{
				delete next;
			}
			virtual MessageType GetType() const
			{
				return eMessage;
			}
			virtual Message* clone() const
			{
				return new Message(*this);
			}
			void SetMessage(const char *text)
			{
				message = text;
			}
			bool operator==(const Message &msg) const
			{
				if (GetType()!=msg.GetType())
					return false;
				return ThisEqual(msg) && NextEqual(msg);
			}
			const SubString& GetMessage() const { return message; }
			const Message* GetNext() const { return next; }
			Message* GetNext() { return next; }

		protected:
			friend class ParameterList;

			SubString message;
			Message* next;

			virtual bool ThisEqual(const Message &msg) const
			{
				return message==msg.message;
			}
			bool NextEqual(const Message &msg) const
			{
				if (next==0)
					return (msg.next==0);
				else
					return msg.next ? (*next==*msg.next) : false;
			}
		};

		class Value: public Message
		{
		public:
			Value(const char *begin, const char *end):
			Message(begin, end)
			{}

			Value(const char *begin, const char *end,
				const RichBool::detail::String &value_):

			Message(begin, end), value(value_)
			{}

			virtual ~Value() {}
			const RichBool::detail::String& GetValue() const { return value; }
			virtual const char* GetValuePtr() const;
			virtual MessageType GetType() const
			{
				return eValue;
			}
			virtual Message* clone() const
			{
				return new Value(message.begin(), message.end(), value);
			}

		protected:
			friend class ParameterList;

			RichBool::detail::String value;
			void SetValue(const RichBool::detail::String &value_)
			{
				value = value_;
			}

			virtual bool ThisEqual(const Message &msg) const
			{
				const Value &val = (const Value&)msg;
				return (message==msg.GetMessage()) && (strcmp(GetValuePtr(), val.GetValuePtr())==0);
			}
		};

		const Message* GetFirst() const { return messages; }

		bool operator==(const ParameterList &valueList) const;
		virtual bool Equals(const ParameterList &valueList) const;

		static bool IsStringLiteral(const char *str);
		static bool IsStringLiteral(const char *begin, const char *end);

		friend RB_CONVERSION_HEADER(ParameterList)
		{
			val.streamout(str);
			return str;
		}

	protected:
		Message *messages, *lastMessage, *cur;

		void AddExpression(const char *begin, const char *end,
			bool stringLiteral);
		void AddMessage(Message *msg);

		void ParseExpressions(const char *expressions);

		template<typename T>
		void Add(const T &t)
		{
			if ((cur->GetType()==eValue) )
				((Value*)cur)->SetValue(RichBool::detail::EscapeString(RichBool::ToString(t)));
			cur = cur->GetNext();
		}

		void Add(const char *text)
		{
			if (cur->GetType()==eValue)
				((Value*)cur)->SetValue(RichBool::detail::EscapeString(text));
			else
				cur->SetMessage(text);
			cur = cur->GetNext();
		}

		void streamout(RichBool::detail::OutStream &str) const;

		friend class CreateParameterList; // for testing
	};
}

#endif // #ifndef VALUE_LIST_H__QM
