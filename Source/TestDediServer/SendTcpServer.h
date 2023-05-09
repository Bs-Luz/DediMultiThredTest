// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "PacketHandler.h"
#include "Async/Async.h"
#include "stats/stats.h"

/**
 * 
 */
class TESTDEDISERVER_API SendTcpServer : public FRunnable
{
public:
	SendTcpServer();
	~SendTcpServer();

	void SendServerStatus(const FString& ServerIP, const int32 Port);

	FString GetServerStatus();

	FString ServerIP;
	int32 ServerPort;
};