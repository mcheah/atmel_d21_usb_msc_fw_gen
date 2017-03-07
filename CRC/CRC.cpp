// CRC.cpp : Defines the entry point for the console application.
//
// Copyright Mickey Cheah
// 03-06-2017

#include "stdafx.h"
#define _CRT_SECURE_NO_WARNINGS
extern "C"
{
#include "checksum.h"
#include "precalc.h"
#include <string.h>
#include <cstdio>
#include <stdlib.h>
}

int main(int argc, char *argv[])
{
	init_crc32_tab();
	uint32_t crcoutput;
	//unsigned char crcinput[] = { 0x00,0x00,0x00,0x00 };
	char filename[1024] = "";
	printf("%d\r\n", argc);
	if (argc < 2)
		strcpy(filename, "firmware_input.bin");
	else
		strcpy(filename, argv[1]);
	FILE *fid = fopen(filename,"r+b");
	if (fid == NULL)
		return -1;
	fseek(fid, 0, SEEK_END);
	size_t lSize = ftell(fid);
	//size_t lSize = 3324;
	rewind(fid);
	//unsigned char buffer[4000]="";
	unsigned char *buffer = (unsigned char *)malloc(sizeof(char)*lSize);
	if (buffer == NULL)
		return -1;
	size_t result = fread(buffer, 1, lSize, fid);
	//result = fread(&(buffer[280]), 1, 2000, fid);
	int err = ferror(fid);
	int eoff = feof(fid);
	fclose(fid);
	crcoutput = crc_32(buffer, lSize);
	printf("File Size = %lu CRC output = %08lX\r\n",lSize,  crcoutput);
	char *Pfind = strstr(filename, "input");
	char filename_out[1024] = "";
	if (Pfind != NULL)
	{
		strncpy(filename_out, filename, Pfind - filename);
		strcpy(filename_out + (Pfind - filename), "output");
		strcpy(filename_out + (Pfind - filename) + strlen("output"), Pfind + strlen("input"));
	}
	else
	{
		Pfind = strrchr(filename, '.');
		if (Pfind != NULL)
		{
			strncpy(filename_out, filename, Pfind - filename);
			strcpy(filename_out + (Pfind-filename), "_output");
			strcpy(filename_out + (Pfind-filename)+strlen("_output"), Pfind);
		}
		else
		{
			strcpy(filename_out, filename);
			strcpy(filename_out+strlen(filename), "_output");
		}
	}
	fid = fopen(filename_out, "w+b");
	fwrite((uint8_t *)&crcoutput, 1, 4, fid);
	fwrite(("ATMEL SAMD21"), 1, 12, fid);
	fwrite(buffer, 1, lSize, fid);
	fflush(fid);
	fclose(fid);


    return 0;
}

