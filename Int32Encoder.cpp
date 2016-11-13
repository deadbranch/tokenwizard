//
// Created by origin on 29.10.16.
//

#include "Int32Encoder.h"

char Int32Encoder::encodeMap[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_";
uint Int32Encoder::decodeMap[256];

Int32Encoder encoder;