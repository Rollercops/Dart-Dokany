
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <winbase.h>

#include "dokan.h"

#include "include/dart_api.h"
#include "include/dart_native_api.h"

Dart_NativeFunction ResolveName(Dart_Handle name, int argc, bool* auto_setup_scope);

DART_EXPORT Dart_Handle extension_Init(Dart_Handle parent_library) {
	if (Dart_IsError(parent_library)) return parent_library;

	Dart_Handle result_code =
		Dart_SetNativeResolver(parent_library, ResolveName, NULL);
	if (Dart_IsError(result_code)) return result_code;

	return Dart_Null();
}

Dart_Handle HandleError(Dart_Handle handle) {
	if (Dart_IsError(handle)) Dart_PropagateError(handle);
	return handle;
}

//void TestExtension(Dart_NativeArguments arguments) {
//	Dart_EnterScope();
//	Dart_Handle object = HandleError(Dart_GetNativeArgument(arguments, 0));
//
//	Dart_Handle field_name = HandleError(Dart_NewStringFromCString("_test"));
//	Dart_Handle value_name = HandleError(Dart_NewStringFromCString("swag"));
//	HandleError(Dart_SetField(object, field_name, value_name));
//	
//	Dart_Handle name = HandleError(Dart_NewStringFromCString("test"));
//	Dart_Handle args = HandleError(Dart_NewList(0));
//	Dart_Handle result = HandleError(Dart_Invoke(object, name, 0, NULL));
//
//	Dart_ExitScope();
//}

int64_t getInt64FromField(Dart_Handle object, Dart_Handle field) {
	Dart_Handle dart_tmp = HandleError(Dart_GetField(object, field));
	bool fits = false;
	HandleError(Dart_IntegerFitsIntoInt64(dart_tmp, &fits));
	if (!fits) {
		return - 1;
	}
	int64_t tmp;
	HandleError(Dart_IntegerToInt64(dart_tmp, &tmp));
	return tmp;
}

uint8_t* getCStringFromField(Dart_Handle object, Dart_Handle field) {
	Dart_Handle dart_tmp = HandleError(Dart_GetField(object, field));
	uint8_t* str;
	intptr_t length;
	HandleError(Dart_StringToUTF8(dart_tmp, &str, &length));
	str[length] = '\0';
	return str;
}

void DokanStart(Dart_NativeArguments arguments) {
	//Dart_EnterScope();

	Dart_Handle dokan_options = HandleError(Dart_GetNativeArgument(arguments, 0));
	Dart_Handle dokan_operations = HandleError(Dart_GetNativeArgument(arguments, 1));

	PDOKAN_OPERATIONS dokanOperations =
		(PDOKAN_OPERATIONS)malloc(sizeof(DOKAN_OPERATIONS));
	if (dokanOperations == NULL) {
		Dart_SetReturnValue(arguments, HandleError(Dart_NewInteger(-1)));
		return;
	}
	PDOKAN_OPTIONS dokanOptions =
		(PDOKAN_OPTIONS)malloc(sizeof(DOKAN_OPTIONS));
	if (dokanOptions == NULL) {
		free(dokanOperations);
		Dart_SetReturnValue(arguments, HandleError(Dart_NewInteger(-1)));
		return;
	}
	
	int64_t Version = getInt64FromField(dokan_options, HandleError(Dart_NewStringFromCString("version")));
	int64_t ThreadCount = getInt64FromField(dokan_options, HandleError(Dart_NewStringFromCString("threadCount")));
	int64_t Options = getInt64FromField(dokan_options, HandleError(Dart_NewStringFromCString("options")));
	int64_t GlobalContext = getInt64FromField(dokan_options, HandleError(Dart_NewStringFromCString("globalContext")));
	uint8_t* MountPoint = getCStringFromField(dokan_options, HandleError(Dart_NewStringFromCString("mountPoint")));

	dokanOptions->Version = (USHORT)Version;
	dokanOptions->ThreadCount = (USHORT)ThreadCount;
	dokanOptions->Options = (USHORT)Options;
	dokanOptions->GlobalContext = (USHORT)GlobalContext;
	dokanOptions->MountPoint = (LPCWSTR)MountPoint;

	printf("MountPoint %s\n", MountPoint);

	int status = DokanMain(dokanOptions, dokanOperations);

	Dart_SetReturnValue(arguments, HandleError(Dart_NewInteger(status)));
	free(dokanOptions);
	free(dokanOperations);
	//Dart_ExitScope();
}

Dart_NativeFunction ResolveName(Dart_Handle name, int argc, bool* auto_setup_scope) {
	if (!Dart_IsString(name)) return NULL;
	Dart_NativeFunction result = NULL;
	const char* cname;
	HandleError(Dart_StringToCString(name, &cname));

	if (strcmp("DokanStart", cname) == 0) result = DokanStart;
	return result;
}
