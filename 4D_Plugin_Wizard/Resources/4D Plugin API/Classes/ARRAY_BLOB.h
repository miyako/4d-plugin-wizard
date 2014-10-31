/*
 *  ARRAY_BLOB.h
 *  4D Plugin
 *
 *  Created by miyako on 31/10/14.
 *
 */

#ifndef __ARRAY_BLOB_H__
#define __ARRAY_BLOB_H__ 1

#include "4DPluginAPI.h"
#include "C_BLOB.h"

#ifdef __cplusplus
extern "C" {
#endif

	typedef std::vector<C_BLOB> CBLOBArray;
	typedef std::vector<C_BLOB> CBLOBArray;		
	
class ARRAY_BLOB
{

private:

	CBLOBArray* _CBLOBArray;
        
public:
 
    void fromParamAtIndex(PackagePtr pParams, uint16_t index);
    void toParamAtIndex(PackagePtr pParams, uint16_t index);	
    
    void appendDataValue(&C_BLOB dataValue);	
    
    void setDataValueAtIndex(&C_BLOB dataValue, uint32_t index);	
    void getDataValueAtIndex(&C_BLOB dataValue, uint32_t index);
	
	uint32_t getSize();
	void setSize(uint32_t size);
	
	ARRAY_BLOB();
	~ARRAY_BLOB();

};

#ifdef __cplusplus
}
#endif

#endif