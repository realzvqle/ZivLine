#include "header/zivline.h"



DWORD convertRegType(char* dwtype) {
    dwtype = toLowerCase(dwtype);
    if (strcmp(dwtype, "dword") == 0) {
        return REG_DWORD;
    }
    else if (strcmp(dwtype, "sz") == 0) {
        return REG_SZ;
    }
    else if (strcmp(dwtype, "expand_sz") == 0) {
        return REG_EXPAND_SZ;
    }
    else{
        printf("Type Can be a dword, sz, or expand_sz\nDEFAULT: setting as sz...\n");
        return REG_SZ;
    }

}

BOOL createReg(char* hkey, char* regpath){
    HKEY key;
    HKEY closing;
    if(strcmp(hkey, "HKLM") == 0){
        key = HKEY_LOCAL_MACHINE;
    }
    else if(strcmp(hkey, "HKCR") == 0){
        key = HKEY_CLASSES_ROOT;
    }
    else if(strcmp(hkey, "HKCU") == 0){
        key = HKEY_CURRENT_USER;
    }
    else if(strcmp(hkey, "HKU") == 0){
        key = HKEY_USERS;
    }
    else if(strcmp(hkey, "HKCC") == 0){
        key = HKEY_CURRENT_CONFIG;
    }
    else{
        printf("Invalid Registry Key, hkey can be HKCR, HKCU, HKLM, HKU, or HKCC\n");
        return FALSE;
    }

    LSTATUS checkResult = RegOpenKeyExA(
        key,
        regpath,
        0,
        KEY_READ,
        &closing
    );
    if (checkResult == ERROR_SUCCESS) {
        printf("Registry key already exists: %s\\%s\n", hkey, regpath);
        RegCloseKey(closing);
        return FALSE;
    }

    LSTATUS result = RegCreateKeyA(
        key,
        regpath,
        &closing
    );
    if(result == ERROR_SUCCESS){
        RegCloseKey(closing);
        return TRUE;
    }
    else{
        RegCloseKey(closing);
        printf("Can't Create Key, Error Code %d\n", result);
        return TRUE;
    }


}

BOOL deleteReg(char* hkey, char* regpath){
    HKEY key;
    HKEY closing;
    if(strcmp(hkey, "HKLM") == 0){
        key = HKEY_LOCAL_MACHINE;
    }
    else if(strcmp(hkey, "HKCR") == 0){
        key = HKEY_CLASSES_ROOT;
    }
    else if(strcmp(hkey, "HKCU") == 0){
        key = HKEY_CURRENT_USER;
    }
    else if(strcmp(hkey, "HKU") == 0){
        key = HKEY_USERS;
    }
    else if(strcmp(hkey, "HKCC") == 0){
        key = HKEY_CURRENT_CONFIG;
    }
    else{
        printf("Invalid Registry Key, hkey can be HKCR, HKCU, HKLM, HKU, or HKCC\n");
        return FALSE;
    }

    LSTATUS checkResult = RegOpenKeyExA(
        key,
        regpath,
        0,
        KEY_SET_VALUE,
        &closing
    );

    if (checkResult != ERROR_SUCCESS) {
        printf("Cannot Open Key: %s\\%s, Error Code %d\n", hkey, regpath, checkResult);
        RegCloseKey(closing);
        return FALSE;
    }
    LSTATUS result = RegDeleteKeyA(
        key,
        regpath
    );
    if (result != ERROR_SUCCESS) {
        printf("Cannot Delete Key: %s\\%s, Error Code %d\n", hkey, regpath, result);
        RegCloseKey(closing);
        return FALSE;
    }
    return TRUE;


}

BOOL writeReg(char* hkey, char* regpath) {
    HKEY key;
    HKEY closing;
    if (strcmp(hkey, "HKLM") == 0) {
        key = HKEY_LOCAL_MACHINE;
    } else if (strcmp(hkey, "HKCR") == 0) {
        key = HKEY_CLASSES_ROOT;
    } else if (strcmp(hkey, "HKCU") == 0) {
        key = HKEY_CURRENT_USER;
    } else if (strcmp(hkey, "HKU") == 0) {
        key = HKEY_USERS;
    } else if (strcmp(hkey, "HKCC") == 0) {
        key = HKEY_CURRENT_CONFIG;
    } else {
        printf("Invalid Registry Key, hkey can be HKCR, HKCU, HKLM, HKU, or HKCC\n");
        return FALSE;
    }
    char* keypath = strtok(regpath, " ");
    char* valuename = strtok(NULL, " ");
    char* dwtype = strtok(NULL, " ");
    char* lpdata = strtok(NULL, " \n");

    if (!valuename || !dwtype) {
        printf("reg -w takes two extra parameters, the name of the value and what type of data\n");
        return FALSE;
    }

    DWORD cbdata;
    if (!lpdata) {
        cbdata = 0;
    } else {
        cbdata = strlen(lpdata);
    }
    LSTATUS checkResult = RegOpenKeyExA(
        key,
        keypath,
        0,
        KEY_SET_VALUE,
        &closing
    );

    if (checkResult != ERROR_SUCCESS) {
        printf("Cannot Open Key: %s\\%s, Error Code %d\n", hkey, keypath, checkResult);
        RegCloseKey(closing);
        return FALSE;
    }
    // THIS HAS NO SUPPORT IN XP, But it works well
    // LSTATUS result = RegSetKeyValueA(
    //     closing,
    //     NULL,
    //     valuename,
    //     convertRegType(dwtype),
    //     lpdata,
    //     cbdata
    // );
    LSTATUS result = RegSetValueExA(
        closing,
        valuename,
        0,
        convertRegType(dwtype),
        lpdata,
        cbdata
    );



    if (result != ERROR_SUCCESS) {
        printf("Cannot Set Key: %s\\%s, Error Code %d\n", hkey, keypath, result);
        RegCloseKey(closing);
        return FALSE;
    }

    RegCloseKey(closing);
    return TRUE;
}


void editReg(ziv *pointer){
    if(!CheckAdmin()){
        printf("Please Run ZivLine As An Administrator To Use the reg Command!\n");
        return;
    }
    if(!pointer->args){
        printf("reg *dowhat *hkey *regpath ^valuename (only for -w) ^datatype (only for -w)\ndowhat path can be -c to create a reg, -d to delete, and -w to write\nhkey can be HKCR, HKCU, HKLM, HKU, or HKCC\npath is the path to the registry key\n");
        return;
    }
    char* dowhat = strtok(pointer->args, " ");
    char* hkey = strtok(NULL, " ");
    char* regpath = strtok(NULL, "\n");

    if(!dowhat || !hkey || !regpath){
        printf("reg *dowhat *hkey *regpath\ndowhat path can be -c to create a reg, -d to delete, and -w to write\nhkey can be HKCR, HKCU, HKLM, HKU, or HKCC\npath is the path to the registry key\n");
        return;
    }
    if(strcmp(dowhat, "-c") == 0){
        if(!createReg(hkey, regpath)){
            printf("Error Creating Registry Key!\n");
            return;
        }
        printf("Succsessfully Created %s\\%s\n", hkey, regpath);
        return;
    }
    else if(strcmp(dowhat, "-d") == 0){
        if(!deleteReg(hkey, regpath)){
            printf("Error Deleting Registry Key!\n");
            return;
        }
        printf("Succsessfully Deleted %s\\%s\n", hkey, regpath);
        return;
    }
    else if(strcmp(dowhat, "-w") == 0){
        if(!writeReg(hkey, regpath)){
            printf("Error Writing Into Registry Key!\n");
            return;
        }
        printf("Succsessfully Written Into %s\\%s\n", hkey, regpath);
        return;
    }
    else{
        printf("%s is an invalid argument, use either -c to create, -d to delete, or -w to write\n");
        return;
    }
}
