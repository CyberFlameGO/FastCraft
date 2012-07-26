/*
FastCraft - Minecraft SMP Server
Copyright (C) 2011 - 2012 Michael Albrecht aka Sprenger120

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/
#include "NBTTagByteArray.h"
#include "NBTConstants.h"
#include "NetworkOut.h"
#include "FCRuntimeException.h"

NBTTagByteArray::NBTTagByteArray(string sName,char * pData,int iLen) :
	NBTTagBase(sName,FC_NBT_TYPE_BYTEARRAY)
{
	if (pData == NULL) {throw FCRuntimeException("Nullpointer");}
	if (iLen <= 0) {throw FCRuntimeException("Illegal lenght");}
	_pData = pData;
	_iLen = iLen;
}

NBTTagByteArray::~NBTTagByteArray() {
	delete [] _pData;
}

void NBTTagByteArray::write(string& rStr,char iType,bool fHeaderless)  {
	string sTemp("");
	string& rTarget = ( iType == FC_NBT_IO_RAW ? rStr : sTemp);

	if (!fHeaderless) {
		rTarget.append(1,FC_NBT_TYPE_BYTEARRAY); //Tag Type
		addHeaderlessString(rTarget,_sName);//Name
	} 
	NetworkOut::addInt(rTarget,_iLen);
	rTarget.append(_pData,_iLen);

	if(iType != FC_NBT_IO_RAW) {
		try {
			NBTTagBase::compress(rTarget,iType); 
		}catch(FCRuntimeException& ex) {
			ex.rethrow();
		}
		rStr.assign(rTarget);
	}
}

char* NBTTagByteArray::getDataRef() {
	return _pData;
}

char NBTTagByteArray::operator[] (int index) {
	if (index > _iLen-1) { throw FCRuntimeException("Index out of bound!"); }
	return _pData[index];
}
