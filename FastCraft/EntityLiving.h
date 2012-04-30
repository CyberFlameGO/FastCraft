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

#ifndef _FASTCRAFTHEADER_ENTITYLIVING
#define _FASTCRAFTHEADER_ENTITYLIVING
#include "Entity.h"
#include "EntityFlags.h"
#include <vector>
#include "ItemInformationProvider.h"

class ItemSlot;

/* 
* It have to be a vector of 5 elements
* Indexes:  0 = item in hand
            1 = helmet
            2 = chestplate
            3 = leggins
            4 = boots
* If a slot should be empty, set it to NULL
*/
typedef std::vector<ItemSlot*> EquipmentArray;


class EntityLiving : public Entity {
protected:
	char _iType;
	short _iHealth;
	EquipmentArray _vpHeld;
	EntityFlags _Flags;
public:
	/*
	* Constructor
	* Throws Poco::RuntimeException if typeID is invalid
	
	Parameter:
	@1 : Type of entity (/Entity/Alive/TypeID/)
	@2 : a valid MinecraftServer instance
	@3 : pointer to a World class that the entity is in
	*/
	EntityLiving(char,MinecraftServer*,World*);


	/*
	* Destructor
	*/
	virtual ~EntityLiving();


	/*
	* Returns true if entity has health points (class is derived from EntityLiving)
	*/
	bool isAlive();


	/*
	* Returns height
	*/
	virtual float getHeight();


	/*
	* Returns width
	*/
	virtual float getWidth();


	/*
	* Returns name
	*/
	virtual string getName();


	/*
	* Sends spawn packet to given client
	*/
	virtual void spawn(NetworkOut&);


	/*
	* Adds the mob specific metadata to NetworkOut buffer
	*/
	virtual void appendMetadata(NetworkOut&);


	/*
	* Returns actual health points
	*/
	short getHealth();


	/*
	* Returns maximal health points
	*/
	virtual short getMaxHealth();


	/*
	* Writes equipment packages to network

	Parameter:
	@1 : NetworkOut instance
	*/
	void sendEquipment(NetworkOut&);


	/*
	* Sends update equip packages if actual and given is different
	* Throws Poco::RuntimeException if array hasn't the coorect size

	Parameter:
	@1 : a NetworkOut instance
	@2 : old equipment
	*/
	void updateEquipment(NetworkOut&,EquipmentArray&);


	/*
	* Sets the equipment
	* Throws Poco::RuntimeException if index is out of bound
	* Rethrows all ItemSlot exception

	Parameter:
	@1 : index      (see EquipmentArray definition)
	@2 : new ItemID (FC_EMPTYITEMID for empty slots)
	*/
	void setEquipment(char,ItemID);


	/*
	* Returns the slot's itemID
	* Throws Poco::RuntimeException if index is out of bound
	* Returns FC_EMPTYITEMID if slot is empty

	Parameter:
	@1 : index      (see EquipmentArray definition)
	*/
	ItemID getEquipment(char);
};
#endif