//
// Created by asus on 2016/8/16.
//

#ifndef HOOKMANAGER_TOOLS_H
#define HOOKMANAGER_TOOLS_H

#include "globals.h"
#include "dex_file.h"
#include "android/MyLog.h"
#include <unistd.h>
#include <pthread.h>
void skipULeb128(const uint8_t *&ptr);
int parsePositiveDecimalInt(const char *str);
char * my_strrev(char *str);
int readUnsignedLeb128(int &size, const u1 *&ptr);
int readUnsignedLeb128(const u1 *ptr,int& size);
int readSignedLeb128(int& size,const u1 *&ptr);
int readSignedLeb128(const u1 *ptr,int& size);
int unsignedLeb128Size(u4 data);
u1* writeUnsignedLeb128(u1* ptr, u4 data);

int dexUtf8Cmp(const char *s1, const char *s2);

std::string getProtoSig(const u4 index, const art::DexFile *dexFile);
char *toJavaClassName(const char *clsChars);

void getProtoString(const art::DexFile::ProtoId &protoId,
                    const art::DexFile* dexFile, std::string &protoType);
void logMethod(const art::DexFile::MethodId& methodId,const art::DexFile* dexFile);


#endif //HOOKMANAGER_TOOLS_H
