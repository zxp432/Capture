#pragma once
#include "stdafx.h"
using namespace System;
char *StringToCharArray(String ^origin) {
	char *result = new char[origin->Length + 1];
	int i = 0;
	for (i = 0; i < origin->Length; i++) {
		result[i] = origin[i];
	}
	result[i] = '\0';
	return result;
}
