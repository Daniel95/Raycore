#pragma once

#include "eventpp/callbacklist.h"
#include "eventpp/eventdispatcher.h"
#include "eventpp/eventqueue.h"
#include "Core/Utilities/Log.h"

#include <iostream>

struct BaseEventArgs
{
    BaseEventArgs()
    {
        type = 13;
    }

    int type;
};

struct MouseEventArgs : public BaseEventArgs
{
    MouseEventArgs(int number)
    {
        mousebutton = number;
    }

    int mousebutton;
};

void TestEvents() 
{
    eventpp::CallbackList<void(BaseEventArgs*)> callbackListCustom;

    callbackListCustom.append([](BaseEventArgs* args)
    {
        MouseEventArgs* mouseArgs = static_cast<MouseEventArgs*>(args);
        LOG_ENGINE_WARN("Type={0} & MouseButton={1}", mouseArgs->type, mouseArgs->mousebutton);
    });

    callbackListCustom(new MouseEventArgs(8));

	eventpp::CallbackList<void(const std::string&, const bool)> callbackList;
	callbackList.append([](const std::string& s, const bool b) {
		b;
		LOG_ENGINE_WARN(s);
	});
	callbackList.append([](std::string s, int b) {
		b;
		LOG_ENGINE_WARN(s);
	});
	callbackList("Hello world", true);

	///----------

    eventpp::EventDispatcher<int, void(const int)> dispatcherTest;

    dispatcherTest.appendListener(3, [](const int a)
    {
        LOG_ENGINE_WARN("Got another event 3! {0}", a);
    });

    dispatcherTest.dispatch(5, 1123);

	eventpp::EventDispatcher<int, void()> dispatcher;

    dispatcher.appendListener(3, []()
    {
        LOG_ENGINE_WARN("Got another event 3!");
    });

	dispatcher.appendListener(3, []() {
		LOG_ENGINE_WARN("Got another event 3!");
	});
	dispatcher.appendListener(5, []() {
		std::cout << "Got event 5." << std::endl;
		LOG_ENGINE_WARN("Got event 5!");

	});
	dispatcher.appendListener(5, []() {
		LOG_ENGINE_WARN("Got another event 5!");
	});
	// dispatch event 3
	dispatcher.dispatch(3);
	// dispatch event 5
	dispatcher.dispatch(5);
}