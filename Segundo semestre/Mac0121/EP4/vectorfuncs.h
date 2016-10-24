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

#endif