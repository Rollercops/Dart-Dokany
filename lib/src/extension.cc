
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

const char* getCStringFromField(Dart_Handle object, Dart_Handle field) {
	Dart_Handle dart_tmp = HandleError(Dart_GetField(object, field));
	const char* str;
	HandleError(Dart_StringToCString(dart_tmp, &str));
	printf("CString %s\n", str);
	printf("len %d\n", strlen(str));
	return str;
}

LPCWCHAR transformCharStarToLPCWCHAR(const char* str) {
	size_t len = strlen(str);
	WCHAR* new_str = (WCHAR*)malloc(sizeof(WCHAR) * (len + 1));
	int i = 0;
	for (i = 0; i < len; i++) {
		new_str[i] = str[i];
	}
	new_str[i] = '\0';
	return new_str;
}

Dart_Handle dart_operations;

static int DOKAN_CALLBACK
ExtCreateFile(
	LPCWSTR					FileName,
	DWORD					AccessMode,
	DWORD					ShareMode,
	DWORD					CreationDisposition,
	DWORD					FlagsAndAttributes,
	PDOKAN_FILE_INFO		DokanFileInfo) {
	printf("Ext Create File\n");
	return 0;
}

static int DOKAN_CALLBACK
ExtCreateDirectory(
	LPCWSTR					FileName,
	PDOKAN_FILE_INFO		DokanFileInfo) {
	printf("Ext Create Directory\n");
	return 0;
}

static int DOKAN_CALLBACK
ExtOpenDirectory(
	LPCWSTR					FileName,
	PDOKAN_FILE_INFO		DokanFileInfo) {
	printf("Ext Open Directory\n");
	return 0;
}

static int DOKAN_CALLBACK
ExtCloseFile(
	LPCWSTR					FileName,
	PDOKAN_FILE_INFO		DokanFileInfo) {
	printf("Ext Close File\n");
	return 0;
}

static int DOKAN_CALLBACK
ExtCleanup(
	LPCWSTR					FileName,
	PDOKAN_FILE_INFO		DokanFileInfo) {
	printf("Ext Cleanup\n");
	return 0;
}

static int DOKAN_CALLBACK
ExtReadFile(
	LPCWSTR				FileName,
	LPVOID				Buffer,
	DWORD				BufferLength,
	LPDWORD				ReadLength,
	LONGLONG			Offset,
	PDOKAN_FILE_INFO	DokanFileInfo) {
	printf("Ext Read File\n");
	return 0;
}

static int DOKAN_CALLBACK
ExtWriteFile(
	LPCWSTR		FileName,
	LPCVOID		Buffer,
	DWORD		NumberOfBytesToWrite,
	LPDWORD		NumberOfBytesWritten,
	LONGLONG			Offset,
	PDOKAN_FILE_INFO	DokanFileInfo) {
	printf("Ext Write File\n");
	return 0;
}

static int DOKAN_CALLBACK
ExtFlushFileBuffers(
	LPCWSTR		FileName,
	PDOKAN_FILE_INFO	DokanFileInfo) {
	printf("Ext Flush File Buffers\n");
	return 0;
}

static int DOKAN_CALLBACK
ExtGetFileInformation(
	LPCWSTR							FileName,
	LPBY_HANDLE_FILE_INFORMATION	HandleFileInformation,
	PDOKAN_FILE_INFO				DokanFileInfo) {
	printf("Ext Get File Information\n");
	return 0;
}

static int DOKAN_CALLBACK
ExtFindFiles(
	LPCWSTR				FileName,
	PFillFindData		FillFindData, // function pointer
	PDOKAN_FILE_INFO	DokanFileInfo) {
	printf("Ext Find Files\n");
	return 0;
}

static int DOKAN_CALLBACK
ExtDeleteFile(
	LPCWSTR				FileName,
	PDOKAN_FILE_INFO	DokanFileInfo) {
	printf("Ext Delete File\n");
	return 0;
}

static int DOKAN_CALLBACK
ExtDeleteDirectory(
	LPCWSTR				FileName,
	PDOKAN_FILE_INFO	DokanFileInfo) {
	printf("Ext Delete Directory\n");
	return 0;
}

static int DOKAN_CALLBACK
ExtMoveFile(
	LPCWSTR				FileName, // existing file name
	LPCWSTR				NewFileName,
	BOOL				ReplaceIfExisting,
	PDOKAN_FILE_INFO	DokanFileInfo) {
	printf("Ext Move File\n");
	return 0;
}

static int DOKAN_CALLBACK
ExtLockFile(
	LPCWSTR				FileName,
	LONGLONG			ByteOffset,
	LONGLONG			Length,
	PDOKAN_FILE_INFO	DokanFileInfo) {
	printf("Ext Lock File\n");
	return 0;
}

static int DOKAN_CALLBACK
ExtSetEndOfFile(
	LPCWSTR				FileName,
	LONGLONG			ByteOffset,
	PDOKAN_FILE_INFO	DokanFileInfo) {
	printf("Ext Set End Of File\n");
	return 0;
}

static int DOKAN_CALLBACK
ExtSetAllocationSize(
	LPCWSTR				FileName,
	LONGLONG			AllocSize,
	PDOKAN_FILE_INFO	DokanFileInfo) {
	printf("Ext Set Allocation Size\n");
	return 0;
}

static int DOKAN_CALLBACK
ExtSetFileAttributes(
	LPCWSTR				FileName,
	DWORD				FileAttributes,
	PDOKAN_FILE_INFO	DokanFileInfo) {
	printf("Ext Set File Attributes\n");
	return 0;
}

static int DOKAN_CALLBACK
ExtSetFileTime(
	LPCWSTR				FileName,
	CONST FILETIME*		CreationTime,
	CONST FILETIME*		LastAccessTime,
	CONST FILETIME*		LastWriteTime,
	PDOKAN_FILE_INFO	DokanFileInfo) {
	printf("Ext Set File Time\n");
	return 0;
}

static int DOKAN_CALLBACK
ExtUnlockFile(
	LPCWSTR				FileName,
	LONGLONG			ByteOffset,
	LONGLONG			Length,
	PDOKAN_FILE_INFO	DokanFileInfo) {
	printf("Ext Unlock File\n");
	return 0;
}

static int DOKAN_CALLBACK
ExtGetFileSecurity(
	LPCWSTR					FileName,
	PSECURITY_INFORMATION	SecurityInformation,
	PSECURITY_DESCRIPTOR	SecurityDescriptor,
	ULONG				BufferLength,
	PULONG				LengthNeeded,
	PDOKAN_FILE_INFO	DokanFileInfo) {
	printf("Ext get File Security\n");
	return 0;
}

static int DOKAN_CALLBACK
ExtSetFileSecurity(
	LPCWSTR					FileName,
	PSECURITY_INFORMATION	SecurityInformation,
	PSECURITY_DESCRIPTOR	SecurityDescriptor,
	ULONG				SecurityDescriptorLength,
	PDOKAN_FILE_INFO	DokanFileInfo) {
	printf("Ext Set File Security\n");
	return 0;
}

static int DOKAN_CALLBACK
ExtGetVolumeInformation(
	LPWSTR		VolumeNameBuffer,
	DWORD		VolumeNameSize,
	LPDWORD		VolumeSerialNumber,
	LPDWORD		MaximumComponentLength,
	LPDWORD		FileSystemFlags,
	LPWSTR		FileSystemNameBuffer,
	DWORD		FileSystemNameSize,
	PDOKAN_FILE_INFO	DokanFileInfo) {
	printf("Ext Get Volume Information\n");
	return 0;
}

static int DOKAN_CALLBACK
ExtUnmount(
	PDOKAN_FILE_INFO	DokanFileInfo) {
	printf("Ext Unmount\n");
	return 0;
}

void DartDokanMain(Dart_NativeArguments arguments) {
	Dart_EnterScope();

	Dart_Handle dokan_options = HandleError(Dart_GetNativeArgument(arguments, 0));
	dart_operations = HandleError(Dart_GetNativeArgument(arguments, 1));

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
	const char* MountPoint = getCStringFromField(dokan_options, HandleError(Dart_NewStringFromCString("mountPoint")));

	ZeroMemory(dokanOptions, sizeof(DOKAN_OPTIONS));
	dokanOptions->Version = (USHORT)Version;
	dokanOptions->ThreadCount = (USHORT)ThreadCount;
	dokanOptions->Options = (USHORT)Options;
	dokanOptions->GlobalContext = (USHORT)GlobalContext;
	dokanOptions->MountPoint = transformCharStarToLPCWCHAR(MountPoint);

	ZeroMemory(dokanOperations, sizeof(DOKAN_OPERATIONS));
	dokanOperations->CreateFile = ExtCreateFile;
	dokanOperations->OpenDirectory = ExtOpenDirectory;
	dokanOperations->CreateDirectory = ExtCreateDirectory;
	dokanOperations->Cleanup = ExtCleanup;
	dokanOperations->CloseFile = ExtCloseFile;
	dokanOperations->ReadFile = ExtReadFile;
	dokanOperations->WriteFile = ExtWriteFile;
	dokanOperations->FlushFileBuffers = ExtFlushFileBuffers;
	dokanOperations->GetFileInformation = ExtGetFileInformation;
	dokanOperations->FindFiles = ExtFindFiles;
	dokanOperations->FindFilesWithPattern = NULL;
	dokanOperations->SetFileAttributes = ExtSetFileAttributes;
	dokanOperations->SetFileTime = ExtSetFileTime;
	dokanOperations->DeleteFile = ExtDeleteFile;
	dokanOperations->DeleteDirectory = ExtDeleteDirectory;
	dokanOperations->MoveFile = ExtMoveFile;
	dokanOperations->SetEndOfFile = ExtSetEndOfFile;
	dokanOperations->SetAllocationSize = ExtSetAllocationSize;
	dokanOperations->LockFile = ExtLockFile;
	dokanOperations->UnlockFile = ExtUnlockFile;
	dokanOperations->GetFileSecurity = ExtGetFileSecurity;
	dokanOperations->SetFileSecurity = ExtSetFileSecurity;
	dokanOperations->GetDiskFreeSpace = NULL;
	dokanOperations->GetVolumeInformation = ExtGetVolumeInformation;
	dokanOperations->Unmount = ExtUnmount;

	printf("dokanOptions->Version %d\n", dokanOptions->Version);
	printf("dokanOptions->ThreadCount %d\n", dokanOptions->ThreadCount);
	printf("dokanOptions->Options %d\n", dokanOptions->Options);
	printf("dokanOptions->GlobalContext %lld\n", dokanOptions->GlobalContext);
	printf("dokanOptions->MountPoint %ls\n", dokanOptions->MountPoint);

	int status = DokanMain(dokanOptions, dokanOperations);

	Dart_SetReturnValue(arguments, HandleError(Dart_NewInteger(status)));
	free(dokanOptions);
	free(dokanOperations);
	Dart_ExitScope();
}

Dart_NativeFunction ResolveName(Dart_Handle name, int argc, bool* auto_setup_scope) {
	if (!Dart_IsString(name)) return NULL;
	Dart_NativeFunction result = NULL;
	const char* cname;
	HandleError(Dart_StringToCString(name, &cname));

	if (strcmp("DokanMain", cname) == 0) result = DartDokanMain;
	return result;
}
