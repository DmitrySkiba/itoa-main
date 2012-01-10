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

#include "AndroidOS.h"

BEGIN_NAMESPACE(android)

///////////////////////////////////////////////////////////////////// Message

#define JB_CURRENT_CLASS Message

JB_DEFINE_WRAPPER_CLASS(
    "android/os/Message"
    ,
    Fields
    (
        What,
        "what","I"
    )
    (
        Target,
        "target","Landroid/os/Handler;"
    )
    ,
    Methods
    (
        ObtainCopy,
        "+obtain",
        "(Landroid/os/Message;)Landroid/os/Message;"
    )
)

Message::Message(const jni::LObject& object):
    java::Object(object)
{
}

int32_t Message::GetWhat() const {
    return JB_GET(IntField,*this,What);    
}

PHandler Message::GetTarget() const {
    return PHandler::Wrap(JB_GET(ObjectField,*this,Target));
}

PMessage Message::Obtain(PMessage message) {
    return PMessage::Wrap(JB_CALL_STATIC(ObjectMethod,ObtainCopy,message));
}

#undef JB_CURRENT_CLASS

///////////////////////////////////////////////////////////////////// MessageQueue

#define JB_CURRENT_CLASS MessageQueue

JB_DEFINE_WRAPPER_CLASS(
    "android/os/MessageQueue"
    ,
    Fields
    (
        QuitAllowed,
        "mQuitAllowed","Z"
    )
    (
        Quiting,
        "mQuiting","Z"
    )
    ,
    NoMethods
)

MessageQueue::MessageQueue(const jni::LObject& object):
    java::Object(object)
{
}

bool MessageQueue::IsQuitAllowed() const {
    return JB_GET(BooleanField,*this,QuitAllowed);
}

void MessageQueue::SetQuitAllowed(bool allowed) {
    JB_SET(BooleanField,*this,QuitAllowed,allowed);    
}

void MessageQueue::ResetQuiting() {
    JB_SET(BooleanField,*this,Quiting,false);
}

#undef JB_CURRENT_CLASS

///////////////////////////////////////////////////////////////////// Looper

#define JB_CURRENT_CLASS Looper

JB_DEFINE_WRAPPER_CLASS(
    "android/os/Looper"
    ,
    NoFields
    ,
    Methods
    (
        Quit,
        "quit","()V"
    )
    (
        MyLooper,
        "+myLooper","()Landroid/os/Looper;"
    )
    (
        MyQueue,
        "+myQueue","()Landroid/os/MessageQueue;"
    )
    (
        Loop,
        "+loop","()V"
    )
)

Looper::Looper(const jni::LObject& object): 
    Object(object)
{
}

void Looper::Quit() {
    JB_CALL(VoidMethod,*this,Quit);
    MyQueue()->ResetQuiting();
}

void Looper::Loop() {
    JB_CALL_STATIC(VoidMethod,Loop);
}

PLooper Looper::MyLooper() {
    return new Looper(JB_CALL_STATIC(ObjectMethod,MyLooper));
}

PMessageQueue Looper::MyQueue() {
    return new MessageQueue(JB_CALL_STATIC(ObjectMethod,MyQueue));
}

#undef JB_CURRENT_CLASS

///////////////////////////////////////////////////////////////////// Handler

#define JB_CURRENT_CLASS Handler

JB_DEFINE_WRAPPER_CLASS(
    "android/os/Handler"
    ,
    NoFields
    ,
    Methods
    (
        SendEmptyMessageDelayed,
        "sendEmptyMessageDelayed","(IJ)Z"
    )
    (
        SendMessageDelayed,
        "sendMessageDelayed","(Landroid/os/Message;J)Z"
    )
    (
        RemoveMessages,
        "removeMessages","(I)V"
    )
)

Handler::Handler(const jni::LObject& object):
    java::Object(object)
{
}

Handler::Handler(const jni::LObject& object,jfieldID instanceFieldID):
    java::Object(object,instanceFieldID)
{
}

bool Handler::SendEmptyMessage(int32_t what) {
    return SendEmptyMessageDelayed(what,0);
}

bool Handler::SendEmptyMessageDelayed(int32_t what,int64_t delay) {
    return JB_CALL(BooleanMethod,*this,SendEmptyMessageDelayed,what,delay);
}

bool Handler::SendMessage(PMessage message) {
    return SendMessageDelayed(message,0);
}

bool Handler::SendMessageDelayed(PMessage message,int64_t delay) {
    return JB_CALL(BooleanMethod,*this,SendMessageDelayed,message,delay);
}

void Handler::RemoveMessages(int32_t what) {
    JB_CALL(VoidMethod,*this,RemoveMessages,what);
}

#undef JB_CURRENT_CLASS

/////////////////////////////////////////////////////////////////////

END_NAMESPACE(android)
