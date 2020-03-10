//
//  JuceThread.cpp
//  Blocks
//
//  Created by Urban Lienert on 23.02.20.
//  Copyright © 2020 Urban Lienert. All rights reserved.
//

#include "JuceThread.hpp"

using namespace juce;

JuceThread::JuceThread (const String &threadName, t_outlet *a, t_outlet *b, t_outlet *c, t_outlet *d, size_t threadStackSize)
    :Thread(threadName, threadStackSize)
{
    out_A = a;
    out_B = b;
    out_C = c;
    out_D = d;
}

JuceThread::~JuceThread() {
}

void JuceThread::startThread() {
    Thread::startThread();
}

bool JuceThread::stopThread(int timeOutMilliseconds) {
    return Thread::stopThread(timeOutMilliseconds);
}

void JuceThread::run() {
    ScopedJuceInitialiser_GUI platform;
    
    if (!MessageManager::getInstanceWithoutCreating()->isThisTheMessageThread()) {
        error("there's already a 'blocks' object running");
        return;
    }
    
    mBlockFinder = {std::make_unique<BlockFinder>()};
    mBlockFinder->out_A = out_A;
    mBlockFinder->out_B = out_B;
    mBlockFinder->out_C = out_C;
    mBlockFinder->out_D = out_D;

    do
    {
        MessageManager::getInstanceWithoutCreating()->runDispatchLoopUntil(10);
    }
    while (!threadShouldExit());
    mBlockFinder = nullptr;
}
