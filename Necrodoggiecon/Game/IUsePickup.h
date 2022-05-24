#pragma once
class IUsePickup
{
public:
	virtual void UsePickup(const std::string& pickupToUse, float activeTime) = 0;
};
