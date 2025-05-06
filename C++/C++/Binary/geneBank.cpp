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
    fstream file(filename, ios::in|ios::binary);

    if (!file) {
        throw MyException("ERROR: File not found!");
    }

    int pos = (speciesCode + offset) * sizeof(Sample);
    file.seekg(pos, ios::beg);

    Sample tmp;
    file.read((char*)&tmp, sizeof(Sample));

    if (file.gcount() < sizeof(Sample)) {
        file.close();
        return false;
    }

    cout << "Sample ID: " << tmp.sampleID << endl;
    cout << "Species Code: " << tmp.speciesCode << endl;
    cout << "Purity Score: " << tmp.purityScore << endl;
    cout << "Researcher: " << tmp.researcher << endl;
    file.close();
    return true;
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
    for (int i = 0; i < fileSize; i += 32) 
        p_insertionSort(array, i, min((i + 32 - 1), (fileSize - 1)));
    for (int size = 32; size < fileSize; size *= 2) 
    {
        for (int left = 0; left < fileSize; left += 2 * size) 
        {
            int mid = min(left + size - 1, fileSize - 1);
            int right = min((left + 2 * size - 1), (fileSize - 1));
            if (mid < right) 
                p_merge(array, left, mid, right);
        }
    }
}

void GENE_BANK::p_insertionSort(Sample array[], int beg, int end) 
{
    for (int i = beg + 1; i <= end; i++)
    {
        Sample temp = array[i];
        int j = i - 1;
        while (j >= beg && array[j].sampleID > temp.speciesCode) 
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = temp;
    }
}

void GENE_BANK::p_merge(Sample array[], int beg, int mid, int end) 
{
    int leftSize = mid - beg + 1;
    int rightSize = end - mid;

    Sample* leftArray = new Sample[leftSize];
    Sample* rightArray = new Sample[rightSize];

    for (int i = 0; i < leftSize; i++)
        leftArray[i] = array[beg + i];
    for (int j = 0; j < rightSize; j++)
        rightArray[j] = array[mid + 1 + j];

    int i = 0, j = 0, k = beg;
    while (i < leftSize && j < rightSize) 
    {
        if (leftArray[i].sampleID <= rightArray[j].sampleID) 
        {
            array[k] = leftArray[i];
            i++;
        } else 
        {
            array[k] = rightArray[j];
            j++;
        }
        k++;
    }

    while (i < leftSize) 
    {
        array[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < rightSize) 
    {
        array[k] = rightArray[j];
        j++;
        k++;
    }

    delete[] leftArray;
    delete[] rightArray;
}

void GENE_BANK::p_index(Sample array[], int indexArray[]) 
{
    int index = 0;
    for (int i = 0; i < 5; i++)
    {
        indexArray[i] = -1;
     indexArray[i] = -1;
    }
     
     for (int i = 0; i < fileSize; i++)
            if (indexArray[array[i].speciesCode] == -1) 
                indexArray[array[i].speciesCode] = i;
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

    fstream file(filename, ios::in|ios::binary);
    if (!file) {
        throw MyException("ERROR: File not found!");
    }

    Sample tmp;
    file.seekg((speciesCode + offset) * sizeof(Sample), ios::beg);
    file.read((char*)&tmp, sizeof(Sample));

    if (file.gcount() < sizeof(Sample)) {
        cout << "Record not found!" << endl; 
    } else {
        cout << "researcher: " << tmp.researcher << endl;
    }
    file.close();

}

void GENE_BANK::p_updateResearcher(int speciesCode, int offset, char* newName, char* filename) 
{
    fstream file(filename, ios::in|ios::out|ios::binary);
    if (!file) {
        throw MyException("ERROR: File not found!");
    }

    Sample tmp;
    file.seekg((speciesCode + offset) * sizeof(Sample), ios::beg);
    file.read((char*)&tmp, sizeof(Sample));

    strncpy(tmp.researcher, newName, MAX_RESEARCHER_NAME);
    file.seekp((speciesCode + offset) * sizeof(Sample), ios::beg);
    file.write((char*)&tmp, sizeof(Sample));
    
    file.close();
}

void GENE_BANK::p_deleteSample(int speciesCode, int offset, char* filename) 
{
    fstream file(filename, ios::in|ios::out|ios::binary);
    if (!file) {
        throw MyException("ERROR: File not found!");
    }

    Sample blank = {0, 0, 0.0, "Deleted"};
    file.seekp((speciesCode + offset) * sizeof(Sample), ios::beg);
    file.write((char*)&blank, sizeof(Sample));

    
    file.close();
}

void GENE_BANK::p_printRange(int speciesCode, int startIndex, int endIndex, char* filename) 
{
    fstream file(filename, ios::in|ios::binary);
    if (!file) {
        throw MyException("ERROR: File not found!");
    }

    Sample tmp;
    for (int i = startIndex; i <= endIndex; i++) 
    {
        file.seekg((speciesCode + i) * sizeof(Sample), ios::beg);
        file.read((char*)&tmp, sizeof(Sample));

        if (strncmp(tmp.researcher, "Deleted", 7) != 0) 
        {
        cout << "Sample ID: " << tmp.sampleID << endl;
        cout << "Species Code: " << tmp.speciesCode << endl;
        cout << "Purity Score: " << tmp.purityScore << endl;
        cout << "Researcher: " << tmp.researcher << endl;
        cout << endl;
        }
    }
    file.close();
}
