/*
FastCraft - Minecraft SMP Server
Copyright (C) 2011  Michael Albrecht aka Sprenger120

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/

/*
* This class handles player thread assignment and slot management.
*/
#ifndef _FASTCRAFTHEADER_PLAYERPOOL
#define _FASTCRAFTHEADER_PLAYERPOOL
#include <iostream>
#include <vector>
#include <queue>
#include <Poco/Net/StreamSocket.h>
#include <Poco/ThreadPool.h>
#include <Poco/Runnable.h>
#include "EntityProvider.h"
#include "ServerTime.h"
#include "PackingThread.h"

class SettingsHandler;
class PlayerThread;
class ChunkRoot;
struct QueueJob;

using std::vector;
using std::string;
using std::queue;

struct ChatEntry {
	std::string Message;
	int X;
	int Z;
};

class PlayerPool : public Poco::Runnable {
private:
	EntityProvider _EntityProvider;
	Poco::ThreadPool _ThreadPool;
	ServerTime _ServerTime;
	vector<PlayerThread*> _vPlayerThreads;
	queue<ChatEntry> _qChat;
	PackingThread _PackingThread;

	ChunkRoot* _pChunkRoot;
public:
	PlayerPool(SettingsHandler*); //Constructor
	~PlayerPool(); //Destructor

	virtual void run(); // Thread main
	
	bool isAnySlotFree(); //Returns true if there is any free slot
	void Assign(Poco::Net::StreamSocket&); //Assigns a connection to a free thread

	void Chat(string,PlayerThread*,bool = true);
private:
	int getFreeSlot(); //Returns -1 if there is no free slot
	void sendMessageToAll(string&);
};
#endif