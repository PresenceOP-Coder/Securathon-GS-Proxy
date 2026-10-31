//This is a decompiled code , it is non-executable and will show error if put in use without setup.


void dump_strings_from_file(WIN32_FIND_DATAA *pFindData,LPCSTR filePath)

{
  DWORD dwMessageId;
  int buf_idx;
  int iVar1;
  HANDLE hFile;
  FILE *_File;
  uint uVar2;
  longlong lVar3;
  int ascii_start_idx;
  longlong buf_offset;
  ulonglong uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  LPDWORD lpNumberOfBytesRead;
  int unicode_start_idx;
  int total_bytes_processed;
  DWORD bytes_read [2];
  char *pErrBuffer;
  LONG low_offset;
  LONG high_offset [3];
  char auStack_10038 [65536];
  
  total_bytes_processed = 0;
  if ((pFindData->dwFileAttributes & 0x10) == 0) {
    uVar6 = 3;
    uVar5 = 0;
    hFile = CreateFileA(filePath,0x80000000,3,(LPSECURITY_ATTRIBUTES)0x0,3,0,(HANDLE)0x0);
    pErrBuffer = hFile;
    if (hFile == (HANDLE)0xffffffffffffffff) {
      print_formatted_output(0x14005ab90,filePath,uVar6,uVar5);
      dwMessageId = GetLastError();
      uVar6 = 0x400;
      uVar4 = (ulonglong)dwMessageId;
      FormatMessageA(0x1100,(LPCVOID)0x0,dwMessageId,0x400,(LPSTR)&pErrBuffer,0,(va_list *)0x0);
      print_formatted_output(0x14005ab68,pErrBuffer,uVar4,uVar6);
      LocalFree(pErrBuffer);
    }
    else {
      g_matching_files_count = g_matching_files_count + 1;
      uVar4 = (ulonglong)g_matching_files_count / 500;
      if (g_matching_files_count == (int)uVar4 * 500) {
        if (g_spinner_index == 3) {
          print_formatted_output(0x14005aba8,uVar4,uVar6,uVar5);
          g_spinner_index = 0;
        }
        else {
          g_spinner_index = g_spinner_index + 1;
          print_formatted_output(0x14005abb0,uVar4,uVar6,uVar5);
        }
        _File = (FILE *)__acrt_iob_func(1);
        fflush(_File);
      }
      if (g_file_starting_offset != 0) {
        low_offset = (LONG)g_file_starting_offset;
        high_offset[0] = (LONG)((ulonglong)g_file_starting_offset >> 0x20);
        SetFilePointer(hFile,low_offset,high_offset,0);
      }
      if (g_bytes_to_scan == 0xffffffffffffffff) {
        uVar2 = 0xffff;
      }
      else {
        uVar2 = (uint)g_bytes_to_scan;
        if (0xffff < g_bytes_to_scan) {
          uVar2 = 0xffff;
        }
      }
      ascii_start_idx = -1;
      lpNumberOfBytesRead = bytes_read;
      uVar4 = (ulonglong)uVar2;
      unicode_start_idx = -1;
      buf_idx = ReadFile(hFile,auStack_10038,uVar2,lpNumberOfBytesRead,(LPOVERLAPPED)0x0);
      while (((buf_idx != 0 && (bytes_read[0] != 0)) && (g_min_string_length <= (int)bytes_read[0]))
            ) {
        buf_idx = 0;
        buf_offset = 0;
        if (0 < (int)bytes_read[0]) {
          do {
            if ((g_scan_unicode != '\0') &&
               ((ascii_start_idx == -1 || (buf_idx - ascii_start_idx < g_min_string_length)))) {
              iVar1 = is_printable_char_w((uint)*(ushort *)(auStack_10038 + buf_offset));
              if ((iVar1 == 0) && (*(short *)(auStack_10038 + buf_offset) != 0x7e)) {
                if (unicode_start_idx != -1) {
                  if (g_min_string_length * 2 <= buf_idx - unicode_start_idx) {
                    if (g_has_wildcard != '\0') {
                      print_formatted_output(0x14005abb4,filePath,uVar4,lpNumberOfBytesRead);
                    }
                    if (g_print_file_offset != '\0') {
                      print_formatted_output
                                (0x14005abbc,
                                 (ulonglong)(uint)(unicode_start_idx + total_bytes_processed),uVar4,
                                 lpNumberOfBytesRead);
                    }
                    for (lVar3 = (longlong)unicode_start_idx; lVar3 < buf_offset; lVar3 = lVar3 + 2)
                    {
                      _fputwchar((short)auStack_10038[lVar3]);
                    }
                    _fputchar(10);
                    g_strings_found_flag = 1;
                  }
                  unicode_start_idx = -1;
                }
              }
              else {
                iVar1 = buf_idx;
                if (unicode_start_idx != -1) {
                  iVar1 = unicode_start_idx;
                }
                unicode_start_idx = iVar1;
                buf_idx = buf_idx + 1;
                buf_offset = buf_offset + 1;
              }
            }
            if ((g_scan_ascii != '\0') &&
               ((unicode_start_idx == -1 || (buf_idx - unicode_start_idx < g_min_string_length)))) {
              if ((byte)(auStack_10038[buf_offset] - 0x20U) < 0x5f) {
                iVar1 = buf_idx;
                if (ascii_start_idx != -1) {
                  iVar1 = ascii_start_idx;
                }
                ascii_start_idx = iVar1;
              }
              else if (ascii_start_idx != -1) {
                if (g_min_string_length <= buf_idx - ascii_start_idx) {
                  if (g_has_wildcard != '\0') {
                    print_formatted_output(0x14005abb4,filePath,uVar4,lpNumberOfBytesRead);
                  }
                  if (g_print_file_offset != '\0') {
                    print_formatted_output
                              (0x14005abbc,
                               (ulonglong)(uint)(ascii_start_idx + total_bytes_processed),uVar4,
                               lpNumberOfBytesRead);
                  }
                  for (lVar3 = (longlong)ascii_start_idx; lVar3 < buf_offset; lVar3 = lVar3 + 1) {
                    _fputchar((int)auStack_10038[lVar3]);
                  }
                  _fputchar(10);
                  g_strings_found_flag = 1;
                }
                ascii_start_idx = -1;
              }
            }
            buf_idx = buf_idx + 1;
            buf_offset = buf_offset + 1;
          } while (buf_idx < (int)bytes_read[0]);
        }
        if ((g_scan_unicode != '\0') &&
           ((((bytes_read[0] < 0xffff && (unicode_start_idx != -1)) || (unicode_start_idx == 0)) &&
            (g_min_string_length * 2 <= buf_idx - unicode_start_idx)))) {
          if (g_has_wildcard != '\0') {
            print_formatted_output(0x14005abb4,filePath,uVar4,lpNumberOfBytesRead);
          }
          if (g_print_file_offset != '\0') {
            print_formatted_output
                      (0x14005abc4,(ulonglong)(uint)(unicode_start_idx + total_bytes_processed),
                       uVar4,lpNumberOfBytesRead);
          }
          for (buf_offset = (longlong)unicode_start_idx; buf_offset < buf_idx;
              buf_offset = buf_offset + 2) {
            _fputwchar((short)auStack_10038[buf_offset]);
          }
          if (unicode_start_idx != 0) {
            _fputchar(10);
            unicode_start_idx = -1;
          }
          g_strings_found_flag = 1;
        }
        if ((g_scan_ascii != '\0') &&
           ((((bytes_read[0] < 0xffff && (ascii_start_idx != -1)) || (ascii_start_idx == 0)) &&
            (g_min_string_length <= buf_idx - ascii_start_idx)))) {
          if (g_has_wildcard != '\0') {
            print_formatted_output(0x14005abb4,filePath,uVar4,lpNumberOfBytesRead);
          }
          if (g_print_file_offset != '\0') {
            print_formatted_output
                      (0x14005abc4,(ulonglong)(uint)(ascii_start_idx + total_bytes_processed),uVar4,
                       lpNumberOfBytesRead);
          }
          for (buf_offset = (longlong)ascii_start_idx; buf_offset < buf_idx;
              buf_offset = buf_offset + 1) {
            _fputchar((int)auStack_10038[buf_offset]);
          }
          if (ascii_start_idx != 0) {
            _fputchar(10);
            ascii_start_idx = -1;
          }
          g_strings_found_flag = 1;
        }
        hFile = pErrBuffer;
        total_bytes_processed = total_bytes_processed + bytes_read[0];
        if (bytes_read[0] == 0xffff) {
          if (ascii_start_idx < 1) {
            if (0 < unicode_start_idx) {
              SetFilePointer(pErrBuffer,unicode_start_idx + -0xffff,(PLONG)0x0,1);
              total_bytes_processed = total_bytes_processed + (unicode_start_idx - bytes_read[0]);
              unicode_start_idx = 0;
            }
          }
          else {
            SetFilePointer(pErrBuffer,ascii_start_idx + -0xffff,(PLONG)0x0,1);
            total_bytes_processed = total_bytes_processed + (ascii_start_idx - bytes_read[0]);
            ascii_start_idx = 0;
          }
        }
        if ((g_bytes_to_scan == 0xffffffffffffffff) ||
           (0xffff < g_bytes_to_scan - (longlong)total_bytes_processed)) {
          uVar2 = 0xffff;
        }
        else {
          uVar2 = (int)g_bytes_to_scan - total_bytes_processed;
        }
        uVar4 = (ulonglong)uVar2;
        lpNumberOfBytesRead = bytes_read;
        buf_idx = ReadFile(hFile,auStack_10038,uVar2,lpNumberOfBytesRead,(LPOVERLAPPED)0x0);
      }
      CloseHandle(hFile);
    }
  }
  return;
}

