// Fill out your copyright notice in the Description page of Project Settings.


#include "SendTcpServer.h"

DECLARE_CYCLE_STAT(TEXT("SendServerStatus"), STAT_SendServerStatus, STATGROUP_Game);

SendTcpServer::SendTcpServer()
{
    // 서버 IP와 포트를 초기화합니다.
    ServerIP = TEXT("127.0.0.1");  // 예시로 localhost를 사용합니다.
    ServerPort = 7777;  // 예시로 포트 번호 12345를 사용합니다.
}

SendTcpServer::~SendTcpServer()
{
}

FString SendTcpServer::GetServerStatus()
{
    // 서버 상태를 나타내는 문자열을 반환하는 코드
    FString ServerStatus = FString::Printf(TEXT("Server is running at %s:%d"), *ServerIP, ServerPort);
    return ServerStatus;
}

void SendTcpServer::SendServerStatus(const FString& DediIP, const int32 Port)
{
    // Create socket
    FSocket* Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);
    if (!Socket)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create socket!"));
        return;
    }

    // Connect to server
    TSharedPtr<FInternetAddr> ServerAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
    bool bIsValid;
    ServerAddr->SetIp(*DediIP, bIsValid);
    ServerAddr->SetPort(Port);
    if (!bIsValid)
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid IP address!"));
        return;
    }

    if (!Socket->Connect(*ServerAddr))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to connect to server!"));
        return;
    }

    // Send server status in a new thread
    FString ServerStatus = GetServerStatus(); // Function to get server status as a string
    FGraphEventRef Task = FFunctionGraphTask::CreateAndDispatchWhenReady([&]()
        {
            int32 BytesSent = 0;
            bool bSuccessful = Socket->Send((uint8*)TCHAR_TO_UTF8(*ServerStatus), ServerStatus.Len(), BytesSent);
            if (!bSuccessful)
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to send server status!"));
            }
        }, TStatId(), nullptr, ENamedThreads::AnyThread);

    TGraphTask<FNullGraphTask>::CreateTask().ConstructAndDispatchWhenReady(
        [Task]()
        {
            FTaskGraphInterface::Get().WaitUntilTaskCompletes(Task);
        },
        ENamedThreads::GameThread
            );

    // Close socket
    Socket->Close();
    ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(Socket);
}