/*
 * Copyright (C) 2011 Dmitry Skiba
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _ANDROIDOS_INCLUDED_
#define _ANDROIDOS_INCLUDED_

#include "CommonIncludes.h"

BEGIN_NAMESPACE(android)

///////////////////////////////////////////////////////////////////// Message

class Handler;
typedef java::ObjectPointer<Handler> PHandler;

class Message;
typedef java::ObjectPointer<Message> PMessage;

class Message: public java::Object {
    JB_WRAPPER_CLASS(Message);
public:
    explicit Message(const jni::LObject& object);
    int32_t GetWhat() const;
    PHandler GetTarget() const;
    static PMessage Obtain(PMessage message);
};

///////////////////////////////////////////////////////////////////// MessageQueue

class MessageQueue: public java::Object {
    JB_WRAPPER_CLASS(MessageQueue);
public:
    explicit MessageQueue(const jni::LObject& object);
    bool IsQuitAllowed() const;
    void SetQuitAllowed(bool allowed);
    void ResetQuiting();
};

typedef java::ObjectPointer<MessageQueue> PMessageQueue;

///////////////////////////////////////////////////////////////////// Looper

class Looper: public java::Object {
    JB_WRAPPER_CLASS(Looper);
    typedef java::ObjectPointer<Looper> PLooper;
public:
    void Quit();
    static PLooper MyLooper();
    static PMessageQueue MyQueue();
    static void Loop();
private:
    Looper(const jni::LObject& object);
};

typedef java::ObjectPointer<Looper> PLooper;

///////////////////////////////////////////////////////////////////// Handler

class Handler: public java::Object {
    JB_WRAPPER_CLASS(Handler);
public:
    Handler(const jni::LObject& object);
    bool SendEmptyMessage(int32_t what);
    bool SendEmptyMessageDelayed(int32_t what,int64_t delay);
    bool SendMessage(PMessage message);
    bool SendMessageDelayed(PMessage message,int64_t delay);
    void RemoveMessages(int32_t what);
    static void Loop();
protected:
    Handler(const jni::LObject&,jfieldID);
};

typedef java::ObjectPointer<Handler> PHandler;

/////////////////////////////////////////////////////////////////////

END_NAMESPACE(android)

#endif // _ANDROIDOS_INCLUDED_
