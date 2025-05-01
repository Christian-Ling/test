#include "geneBank.h"

// =================================== PUBLIC FUNCTIONS =======================================================

GENE_BANK::GENE_BANK() 
{
    this->fileSize = 0;
    this->entryByte = sizeof(Sample);
}

GENE_BANK::~GENE_BANK() 
{
    cout << "Destructing ..." << endl;
}

void GENE_BANK::sort(Sample array[], int fileSize)
{
    if (fileSize != 0)
        this->p_timSort(array, fileSize);
    else
        throw MyException("ERROR: Empty file to sort!");
}

void GENE_BANK::indexSamples(Sample array[], int indexArray[]) 
{
    this->p_index(array, indexArray);
}

void GENE_BANK::displayResearcher(int speciesCode, int offset, char* filename) 
{
    bool checkSample;

    checkSample = searchSample(speciesCode, offset, filename);

    if(checkSample){
        p_displayResearcher(speciesCode, offset, filename);
    } else {
        cout << "Sample record doesn't exist! Can't display researcher name." << endl;
    }
}

bool GENE_BANK::searchSample(int speciesCode, int offset, char* filename) 
{

}


void GENE_BANK::updateResearcher(int speciesCode, int offset, char* newName, char* filename) 
{
    bool checkSample;

    checkSample = this->searchSample(speciesCode, offset, filename);

    if(checkSample){
        p_updateResearcher(speciesCode, offset, newName, filename);
    } else {
        cout << "Sample record to be updated doesn't exist!" << endl;
        p_updateResearcher(speciesCode, offset, newName, filename);
    }
}

void GENE_BANK::deleteSample(int speciesCode, int offset, char* filename)
{
    bool checkSample;

    checkSample = this->searchSample(speciesCode, offset, filename);

    if(checkSample){
        p_deleteSample(speciesCode, offset, filename);
    } else {
        cout << "Sample record to be deletesd doesn't exist!" << endl;
    }
}

void GENE_BANK::printSampleRange(int speciesCode, int startIndex, int endIndex, char* filename) 
{
    if(startIndex >= endIndex)
        throw MyException("ERROR: start index is larger than end index!");
    else
        this->p_printRange(speciesCode, startIndex, endIndex, filename);
}

// =================================== PRIVATE FUNCTIONS =======================================================

void GENE_BANK::p_timSort(Sample array[], int fileSize) 
{

}

void GENE_BANK::p_insertionSort(Sample array[], int beg, int end) 
{

}

void GENE_BANK::p_merge(Sample array[], int beg, int mid, int end) 
{

}

void GENE_BANK::p_index(Sample array[], int indexArray[]) 
{

}

void GENE_BANK::p_displayResearcher(int speciesCode, int offset, char* filename) 
{
    /* These are the 5 unique species codes
        0 - H_SAP
        1 - M_MUS
        2 - D_MEL
        3 - E_COL
        4 - A_THA
    */

}

void GENE_BANK::p_updateResearcher(int speciesCode, int offset, char* newName, char* filename) 
{

}

void GENE_BANK::p_deleteSample(int speciesCode, int offset, char* filename) 
{

}

void GENE_BANK::p_printRange(int speciesCode, int startIndex, int endIndex, char* filename) 
{

}
