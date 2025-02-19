//
// Created by Nicolò Vanzo on 13/02/25.
//
#include "../headers/RobotCat.h"
#include <sys/socket.h>

void RoboCat::Write(OutputMemoryStream &inStream) const {
    inStream.Write(mHealth);
    inStream.Write(mMeowCount);
    //TODO: solution for homebase
    inStream.Write(mName, 128);
    //TODO: solution for mMiceIndices
}

void RoboCat::Read(InputMemoryStream &inStream) {
    inStream.Read(mHealth);
    inStream.Read(mMeowCount);
    //TODO: solution for homebase
    inStream.Read(mName, 128);
    //TODO: solution for mMiceIndices
}

void SendRoboCat(int socket, const RoboCat* inRoboCat) {
    OutputMemoryStream stream;
    inRoboCat->Write(stream);
    send(socket, stream.GetBufferPtr(), stream.GetLength(), 0);
}
int kMaxPacketSize = 1470;

void ReceiveRoboCat(int inSocket, RoboCat* outRoboCat)
{
    char* temporaryBuffer = static_cast<char*>(malloc(sizeof(kMaxPacketSize)));
    size_t receivedByteCount = recv(inSocket, temporaryBuffer, kMaxPacketSize, 0);
    if(receivedByteCount > 0) {
        InputMemoryStream stream(temporaryBuffer, static_cast<uint32_t>(receivedByteCount));
        outRoboCat->Read(stream);
    } else {
        free(temporaryBuffer);
    }
}

