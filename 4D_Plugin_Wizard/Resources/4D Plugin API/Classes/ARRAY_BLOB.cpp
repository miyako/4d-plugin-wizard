/*
 *  ARRAY_BLOB.cpp
 *  4D Plugin
 *
 *  Created by miyako on 31/10/14.
 *
 */

#include "ARRAY_BLOB.h"

void ARRAY_BLOB::fromParamAtIndex(PackagePtr pParams, uint32_t index)
{	
	if(index)		
	{
		PA_Variable arr = *((PA_Variable*) pParams[index - 1]);
		
		this->setSize(0);		
		
		if(arr.fType == eVK_ArrayBlob)
		{	
			uint32_t i;
			
			PA_Unistring str;
			
			for(i = 0; i <= (uint32_t)arr.uValue.fArray.fNbElements; i++)
			{				
				str = (*(PA_Unistring **) (arr.uValue.fArray.fData))[i];
				CUTF16String u = CUTF16String(str.fString, str.fLength);
				this->_CUTF16StringArray->push_back(u);
			}
			
		}

	}
	
}

void ARRAY_BLOB::toParamAtIndex(PackagePtr pParams, uint32_t index)
{
	if(index)		
	{
		PA_Variable arr = *((PA_Variable*) pParams[index - 1]);
		PA_Variable *param = ((PA_Variable *)pParams[index - 1]);
		
		switch (arr.fType) 
		{
			case eVK_ArrayBlob:
				break;
			case eVK_Undefined:
				PA_ClearVariable(&arr);				
				arr = PA_CreateVariable(eVK_ArrayBlob);
				param->fType = arr.fType;
				break;				
			
			default:
				break;
		}
		
		if(arr.fType == eVK_ArrayBlob)
		{
			
			PA_ResizeArray(&arr, this->_CBLOBArray->empty() ? 0 : (uint32_t)(this->_CBLOBArray->size() - 1));
			
			uint32_t i;
			
			for(i = 0; i < this->_CBLOBArray->size(); i++)
			{
				C_BLOB blob = this->_CBLOBArray->at(i));
                
                PA_SetBlobInArray(arr, i, );
                
				PA_SetStringInArray(arr, i, &str);					
			}
			
			param->fFiller = 0;
			param->uValue.fArray.fCurrent = arr.uValue.fArray.fCurrent;
			param->uValue.fArray.fNbElements = arr.uValue.fArray.fNbElements;
			param->uValue.fArray.fData = arr.uValue.fArray.fData;			
			
		}
		
	}
	
}

void ARRAY_BLOB::appendDataValue(&C_BLOB dataValue)
{
    this->_CBLOBArray->push_back(dataValue);	
}

void ARRAY_BLOB::setDataValueAtIndex(&C_BLOB dataValue, uint32_t index)
{
    if(index < this->_CBLOBArray->size())
    {
        
        std::vector<int>::iterator it = this->_CBLOBArray->begin();
        it += index;
        
        this->_CBLOBArray->insert(this->_CBLOBArray->erase(it), dataValue);
        
    }
}

void ARRAY_BLOB::getDataValueAtIndex(&C_BLOB dataValue, uint32_t index)	
{
    if(index < this->_CBLOBArray->size())
    {
        dataValue = C_BLOB(this->_CBLOBArray->at(index));
    }
}

uint32_t ARRAY_BLOB::getSize()
{
	return (uint32_t)this->_CBLOBArray->size();		
}

void ARRAY_BLOB::setSize(uint32_t size)
{	
	this->_CBLOBArray->resize(size);
}

ARRAY_BLOB::ARRAY_BLOB() : _CBLOBArray(new CBLOBArray)
{
	
}

ARRAY_BLOB::~ARRAY_BLOB()
{ 
	delete _CBLOBArray; 
}