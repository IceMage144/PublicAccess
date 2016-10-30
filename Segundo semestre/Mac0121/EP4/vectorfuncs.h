/*
	Biblioteca feita por João Gabriel Basi
*/

#ifndef __VECTORFUNCS_H__
#define __VECTORFUNCS_H__

typedef struct entry_t {
	char *key;
	int value;
} Entry;

typedef struct vectorst_t {
	int top, maxPos;
	Entry *data;
} VectorSTable;

#define VST VectorSTable

VST *VTableCreate ();

void VTableDestroy (VST *Table);

int valcompV (Entry *Entry1, Entry *Entry2);

int strcompV (Entry *Entry1, Entry *Entry2);

void mergeSortV (VST *Table, int beg, int end, int (*comp)(Entry*, Entry*));

#endif